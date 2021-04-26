const puppeteer = require('puppeteer')
const fs = require('fs')
//require('dotenv').config()
const {createObjectCsvWriter} = require('csv-writer')

const OUTPUT_PATH = "retty"
let BROWSER

const VIEWPORT = {
  width : 1280,
  height: 1024
}

const xpath = {
  searchResult: {
    restaurantLinks: '//a[contains(@class, "restaurant__block-link")]',
    nextPageLink: '//li[contains(@class, "pager__item--current")]/following-sibling::li[1]/a',
    nextPageItem: '//li[contains(@class, "pager__item--current")]/following-sibling::li[1]'
  },
  restaurantDetail: {
    restaurantInformation: '//*[@id="restaurant-info"]/dl[1]',
  }
}

const selector = {
  searchResult: {
    hitCount: '.search-result__hit-count'
  },
  restaurantDetail: {
    lastPageLink: '#js-search-result > div > section > ul > li:last-child > a',
    pagerCurrent: 'li.pager__item.pager__item--current'
  }
}

;(async() => {
  /**** setup ****/
  const options = process.env.HF
    ? {
      headless: false,
      slowMo: 100
    }
    : {}
  BROWSER = await puppeteer.launch(options)
  let page = await BROWSER.newPage()
  let newPage
  await page.setViewport({
    width : VIEWPORT.width,
    height: VIEWPORT.height
  })
  /**** setup ****/

  let data = []

  const url = "https://qiita.com/search?q=created%3A2021-01-01&sort=created"
  await page.goto(url, {waitUntil: "domcontentloaded"})
  //const lastPageNum = await getTextBySelector(page, (selector.restaurantDetail.lastPageLink))
  const hitCount = await getTextBySelector(page, "#main > div > div.searchResultContainer_main > div.searchResultContainer_navigation > ul > li.active > a > span")
  //console.log("総ページ数: " + lastPageNum + ", 総件数: " + hitCount)
  console.log("総件数: " + hitCount)

  const sr = await page.$$("div.searchResult")
  //console.log(sr)
  const sr0 = sr[0]
  console.log(sr[0])
  text = await (await sr0.getProperty('textContent')).jsonValue()
  text = text.replace(/[\s　]/g, "")
  console.log(text)
  const header = await getTextBySelector(sr0, ".searchResult_header")
  console.log(header)
  const title = await getTextBySelector(sr0, ".searchResult_itemTitle")
  console.log(title)
  const title_a = await sr0.$("div.searchResult_main > h1 > a");
  const href = await (await title_a.getProperty('href')).jsonValue();
  console.log(href)
  //console.log(href.split('/'))
  console.log(href.split('/')[3])
  console.log(href.split('/')[5])
  const sr_sub = await sr0.$(".searchResult_sub")
  const lgtm = await getTextByXPath(sr_sub, "*/li/text()")
  console.log(lgtm)

  BROWSER.close()
})()

/**
 * 新しく開いたページを取得
 * @param {page} page もともと開いていたページ
 * @returns {page} 別タブで開いたページ
 */
async function getNewPage(page) {
  const pageTarget = await page.target()
  const newTarget = await BROWSER.waitForTarget(target => target.opener() === pageTarget)
  const newPage = await newTarget.page()
  await newPage.setViewport({
    width : VIEWPORT.width,
    height: VIEWPORT.height
  })
  await newPage.waitForSelector('body')
  return newPage
}

/**
 * 渡したデータをcsvに出力するメソッド。ページ数を渡すことで、ページごとに区別してcsvを出力できる。
 * @param {Object.<string, string>} data csvに書き込まれるデータ。csvのヘッダと対応するkeyと、実際に書き込まれるvalueを持ったobjectになっている。
 * @param {number} pageNumber 現在のページ数
 */
async function csvWrite(data, pageNumber) {
  if (!fs.existsSync(OUTPUT_PATH)) {
    fs.mkdirSync(OUTPUT_PATH)
  }
  var exec = require('child_process').exec
  exec(`touch ${OUTPUT_PATH}/page${pageNumber}.csv`, function(err, stdout, stderr) {
    　　if (err) { console.log(err) }
  })
  const csvfilepath =  `${OUTPUT_PATH}/page${pageNumber}.csv`
  const csvWriter = createObjectCsvWriter({
    path: csvfilepath,
    header: [
      {id: 'id', title: 'No.'},
      {id: 'name', title: '店舗名'},
      {id: 'phone', title: '電話番号'},
      {id: 'address', title: '住所'},
      {id: 'holiday', title: '定休日'},
      {id: 'genre', title: 'ジャンル'},
      {id: 'chairs', title: '座席・設備'},
      {id: 'hours', title: '営業時間'},
      {id: 'url', title: 'URL'}
    ],
    encoding:'utf8',
    append :false,
  })
  csvWriter.writeRecords(data)
  .then(() => {
      console.log('...Done')
  })
}

/**
 * セレクターで指定した要素のテキストを取得できる。
 * @param {page} page 
 * @param {string} paramSelector 
 * @returns {string} 改行と空白を取り除いた要素のテキスト。要素を取得できなかった時は空文字が返る。
 */
async function getTextBySelector(page, paramSelector) {
  const element = await page.$(paramSelector) 
  let text = ""
  if(element) {
    text = await (await element.getProperty('textContent')).jsonValue()
    text = text.replace(/[\s　]/g, "")
  }
  return text
}

/**
 * XPathで指定した要素のテキストを取得できる。
 * @param page 
 * @param {string} xpath 取得したい要素のxpath。
 * @returns {string} 改行と空白を取り除いた要素のテキスト。要素を取得できなかった時は空文字が返る。
 */
async function getTextByXPath(page, xpath) {
  const elements = await page.$x(xpath) 
  let text = ""
  if(elements[0]) {
    text = await (await elements[0].getProperty('textContent')).jsonValue()
    text = text.replace(/[\s　]/g, "")
  }
  return text
}

async function getName(page, nameXpath, rubyXpath) {
  let name = await getTextByXPath(page, nameXpath)
  const nameRuby = await getTextByXPath(page, rubyXpath)
  name += '(' + nameRuby + ')'
  return name
}

function getTableInfoXPath(infoName) {
  return `//dt[contains(text(), "${infoName}")]/following-sibling::dd`
}
