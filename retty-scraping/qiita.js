const puppeteer = require('puppeteer');
const fs = require('fs');
const { createObjectCsvWriter } = require('csv-writer');

const OUTPUT_PATH = "qiita.tmp";
let BROWSER;

const VIEWPORT = {
  width: 1280,
  height: 1024
};

(async () => {
  /**** setup ****/
  const options = process.env.HF
    ? {
      headless: false,
      slowMo: 100
    }
    : {};
  BROWSER = await puppeteer.launch(options);
  let page = await BROWSER.newPage();
  //let newPage
  await page.setViewport({
    width: VIEWPORT.width,
    height: VIEWPORT.height
  });
  /**** setup ****/

  let data = [];

  const url = "https://qiita.com/search?q=created%3A2021-01-01&sort=created";
  await page.setCacheEnabled(false);
  await page.goto(url, { waitUntil: "domcontentloaded" });
  const hitCount = await getTextBySelector(page, "#main > div > div.searchResultContainer_main > div.searchResultContainer_navigation > ul > li.active > a > span");
  console.log("総件数: " + hitCount);

  const sr = await page.$$("div.searchResult");
  const sr0 = sr[0];
  text = await (await sr0.getProperty('textContent')).jsonValue();
  text = text.replace(/[\s　]/g, "");
  console.log(text);
  const header = await getTextBySelector(sr0, ".searchResult_header");
  console.log(header);

  let bar = header.match(/^.+が(.+)に投稿$/);
  console.log(bar);
  if (bar) {
    console.log(bar[1]);
  }

  const title = await getTextBySelector(sr0, ".searchResult_itemTitle");
  console.log(title);
  const title_a = await sr0.$("div.searchResult_main > h1 > a");
  const href = await (await title_a.getProperty('href')).jsonValue();
  console.log(href);
  //console.log(href.split('/'));
  console.log(href.split('/')[3]);
  console.log(href.split('/')[5]);
  const sr_sub = await sr0.$(".searchResult_sub");
  const lgtm = await getTextByXPath(sr_sub, "*/li/text()");
  console.log(lgtm);
  const tags = await sr0.$$(".tagList_item");
  for (let tag of tags) {
    const tagName = await (await tag.getProperty('textContent')).jsonValue();
    console.log(tagName);
  }

  /*
  let page2 = await BROWSER.newPage();
  page2.on('response', async (response) => {
    if (!response.url().startsWith("http://javacommons.html-5.me/01-json.php?")) return;
    console.log('XHR1 response received:' + response.url());
    const json = await response.text();
    if (!json.startsWith("<html>")) {
      console.log(json);
      console.log(JSON.parse(json));
    }
  });
  await page2.setCacheEnabled(false);
  await page2.goto("http://javacommons.html-5.me/01-json.php?t=1&i=2", { waitUntil: "domcontentloaded" });
  await page2.close();
  */

  let result1 = await jsonRequest(BROWSER, "http://javacommons.html-5.me/01-json.php");
  console.log("result1=", result1);

  let result2 = await jsonRequest(BROWSER, "http://javacommons.html-5.me/01-json.php", { url: href });
  console.log("result2=", result2);

  BROWSER.close();

  await urlTest();

})();

async function jsonRequest(browser, url, data = null) {
  let json = JSON.stringify(data);
  let url2 = new URL(url);
  url2.searchParams.append("json", json);
  let result = null;
  let page = await browser.newPage();
  page.on('response', async (response) => {
    if (!response.url().startsWith(url + "?")) return;
    console.log('XHR response received:' + response.url());
    const json = await response.text();
    if (!json.startsWith("<html>")) {
      //console.log(json);
      //console.log(JSON.parse(json));
      result = JSON.parse(json);
    }
  });
  await page.setCacheEnabled(false);
  await page.goto(url2, { waitUntil: "domcontentloaded" });
  await page.close();
  return result;
}

async function urlTest() {
  const myUrlWithParams = new URL("https://qiita.com/search");
  myUrlWithParams.searchParams.append("q", "created:2021-01-01");
  myUrlWithParams.searchParams.append("sort", "created");
  console.log(myUrlWithParams.href);
  const parser = new URL(myUrlWithParams.href);
  if (parser.searchParams.has("q"))
    console.log(parser.searchParams.get("q"));
}

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
    width: VIEWPORT.width,
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
  exec(`touch ${OUTPUT_PATH}/page${pageNumber}.csv`, function (err, stdout, stderr) {
    if (err) { console.log(err) }
  })
  const csvfilepath = `${OUTPUT_PATH}/page${pageNumber}.csv`
  const csvWriter = createObjectCsvWriter({
    path: csvfilepath,
    header: [
      { id: 'id', title: 'No.' },
      { id: 'name', title: '店舗名' },
      { id: 'phone', title: '電話番号' },
      { id: 'address', title: '住所' },
      { id: 'holiday', title: '定休日' },
      { id: 'genre', title: 'ジャンル' },
      { id: 'chairs', title: '座席・設備' },
      { id: 'hours', title: '営業時間' },
      { id: 'url', title: 'URL' }
    ],
    encoding: 'utf8',
    append: false,
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
  if (element) {
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
  if (elements[0]) {
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
