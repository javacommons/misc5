const puppeteer = require('puppeteer');
const fs = require('fs');
const { createObjectCsvWriter } = require('csv-writer');
const moment = require("moment");

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

  for (let sr_item of sr) {
    let rec = await parseSearchResult(sr_item);
    console.log("rec=", rec);
    data.push(rec);
  }

  let result1 = await jsonRequest(BROWSER, "http://javacommons.html-5.me/+test/01-json.php");
  console.log("result1=", result1);

  let result2 = await jsonRequest(BROWSER, "http://javacommons.html-5.me/+test/02-json-get.php", data, false, 5);
  console.log("result2=", result2);

  BROWSER.close();

  await urlTest();

  console.log(moment().toISOString());
  console.log(moment().format());

})();

async function parseSearchResult(sr_item) {
  let result = {};
  //text = await (await sr_item.getProperty('textContent')).jsonValue();
  //text = text.replace(/[\s　]/g, "");
  //console.log(text);
  const header = await getTextBySelector(sr_item, ".searchResult_header");
  //console.log(header);
  let m = header.match(/^.+が(.+)に投稿$/);
  //console.log(m);
  result.post = ''
  if (m) {
    //console.log(m[1]);
    result.post = m[1];
  }
  const title = await getTextBySelector(sr_item, ".searchResult_itemTitle");
  //console.log(title);
  result.title = title;
  const title_a = await sr_item.$("div.searchResult_main > h1 > a");
  const href = await (await title_a.getProperty('href')).jsonValue();
  //console.log(href);
  result.url = href;
  //console.log(href.split('/')[3]);
  result.user = href.split('/')[3];
  //console.log(href.split('/')[5]);
  result.uuid = href.split('/')[5];
  const sr_sub = await sr_item.$(".searchResult_sub");
  const lgtm = await getTextByXPath(sr_sub, "*\/li/text()");
  //console.log(lgtm);
  result.lgtm = parseInt(lgtm);
  const tags = await sr_item.$$(".tagList_item");
  let tagList = "";
  for (let tag of tags) {
    const tagName = await (await tag.getProperty('textContent')).jsonValue();
    //console.log(tagName);
    if (tagList != "") tagList += ",";
    tagList += tagName;
  }
  result.tags = tagList;
  let dt = new Date();
  //console.log(datetostr(dt, 'Y/MM/DD-hh:mm:ss', false));
  //result.ts = datetostr(dt, 'Y/MM/DD-hh:mm:ss', false);
  //console.log(moment().format());
  result.ts = moment().format();
  return result;
}

async function jsonRequestOnce(browser, url, data = null, debug = false) {
  try {
    let json = JSON.stringify(data);
    let url2 = new URL(url);
    url2.searchParams.append("data", json);
    let result = null;
    let page = await browser.newPage();
    page.on('response', async (response) => {
      if (!response.url().startsWith(url + "?")) return;
      if (debug) console.log('XHR response received: ' + response.url());
      const text = await response.text();
      if (text.startsWith("{") || text.startsWith("[")) {
        result = JSON.parse(text);
      } else {
        console.log('XHR illegal response received: ' + response.url());
        console.log("response.text=", text);
      }
    });
    await page.setCacheEnabled(false);
    await page.goto(url2, { waitUntil: "domcontentloaded" });
    await page.close();
    return result;
  } catch (e) {
    return null;
  }
}

async function jsonRequest(browser, url, data = null, debug = false, retry = 0) {
  let result = null;
  if (retry < 0) retry = 0;
  let count = retry + 1;
  while (result === null && (count--) > 0) {
    result = await jsonRequestOnce(BROWSER, url, data, debug);
  }
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
