#include <windows.h>
#include <wininet.h>
#include <assert.h>
#include <string>
#include <sstream>

#pragma comment(lib, "wininet.lib")

#define URLBUFFER_SIZE (4096)
#define READBUFFER_SIZE (4096)

bool HttpRequest(std::string strUserAgent,
                 std::string strUrl,
                 bool bIsHttpVerbGet,
                 std::string strParameter,
                 std::string &rstrResult)
{
    // アウトプットの初期化
    rstrResult = "";

    // 変数
    HINTERNET hInternetOpen = NULL;
    HINTERNET hInternetConnect = NULL;
    HINTERNET hInternetRequest = NULL;
    //const char*			pszOptional = NULL;
    URL_COMPONENTS urlcomponents;
    std::string strServer;
    std::string strObject;
    INTERNET_PORT nPort;
    std::string strVerb;
    std::string strHeaders;
    std::stringstream ssRead;

    // URL解析
    ZeroMemory(&urlcomponents, sizeof(URL_COMPONENTS));
    urlcomponents.dwStructSize = sizeof(URL_COMPONENTS);
    TCHAR szHostName[URLBUFFER_SIZE];
    TCHAR szUrlPath[URLBUFFER_SIZE];
    urlcomponents.lpszHostName = szHostName;
    urlcomponents.lpszUrlPath = szUrlPath;
    urlcomponents.dwHostNameLength = URLBUFFER_SIZE;
    urlcomponents.dwUrlPathLength = URLBUFFER_SIZE;
    if (!InternetCrackUrlA(strUrl.c_str(),
                           (DWORD)strUrl.length(),
                           0,
                           &urlcomponents))
    { // URLの解析に失敗
        assert(!"URL解析に失敗");
        return false;
    }
    strServer = urlcomponents.lpszHostName;
    strObject = urlcomponents.lpszUrlPath;
    nPort = urlcomponents.nPort;

    // HTTPかHTTPSかそれ以外か
    DWORD dwFlags = 0;
    if (INTERNET_SCHEME_HTTP == urlcomponents.nScheme)
    {                                               // HTTP
        dwFlags = INTERNET_FLAG_RELOAD              // 要求されたファイル、オブジェクト、またはフォルダ一覧を、キャッシュからではなく、元のサーバーから強制的にダウンロードします。
                  | INTERNET_FLAG_DONT_CACHE        // 返されたエンティティをキャシュへ追加しません。
                  | INTERNET_FLAG_NO_AUTO_REDIRECT; // HTTP だけで使用され、リダイレクトが HttpSendRequest で処理されないことを指定します。
    }
    else if (INTERNET_SCHEME_HTTPS == urlcomponents.nScheme)
    {                                                      // HTTPS
        dwFlags = INTERNET_FLAG_RELOAD                     // 要求されたファイル、オブジェクト、またはフォルダ一覧を、キャッシュからではなく、元のサーバーから強制的にダウンロードします。
                  | INTERNET_FLAG_DONT_CACHE               // 返されたエンティティをキャシュへ追加しません。
                  | INTERNET_FLAG_NO_AUTO_REDIRECT         // HTTP だけで使用され、リダイレクトが HttpSendRequest で処理されないことを指定します。
                  | INTERNET_FLAG_SECURE                   // 安全なトランザクションを使用します。これにより、SSL/PCT を使うように変換され、HTTP 要求だけで有効です。
                  | INTERNET_FLAG_IGNORE_CERT_DATE_INVALID // INTERNET_FLAG_IGNORE_CERT_DATE_INVALID、INTERNET_FLAG_IGNORE_CERT_CN_INVALID
                  | INTERNET_FLAG_IGNORE_CERT_CN_INVALID;  // は、証明書に関する警告を無視するフラグ
    }
    else
    {
        assert(!"HTTPでもHTTPSでもない");
        return false;
    }

    // GETかPOSTか
    if (bIsHttpVerbGet)
    { // GET
        strVerb = "GET";
        strHeaders = "";
        if (0 != strParameter.length())
        { // オブジェクトとパラメータを「?」で連結
            strObject += "?" + strParameter;
        }
    }
    else
    { // POST
        strVerb = "POST";
        strHeaders = "Content-Type: application/x-www-form-urlencoded";
    }

    // WinInetの初期化
    hInternetOpen = InternetOpenA(strUserAgent.c_str(),
                                  INTERNET_OPEN_TYPE_PRECONFIG,
                                  NULL, NULL, 0);
    if (NULL == hInternetOpen)
    {
        assert(!"WinInetの初期化に失敗");
        goto LABEL_ERROR;
    }

    // HTTP接続
    hInternetConnect = InternetConnect(hInternetOpen,
                                       strServer.c_str(),
                                       nPort,
                                       NULL,
                                       NULL,
                                       INTERNET_SERVICE_HTTP,
                                       0,
                                       0);
    if (NULL == hInternetConnect)
    {
        assert(!"HTTP接続に失敗");
        goto LABEL_ERROR;
    }

    // HTTP接続を開く
    hInternetRequest = HttpOpenRequestA(hInternetConnect,
                                        strVerb.c_str(),
                                        strObject.c_str(),
                                        NULL,
                                        NULL,
                                        NULL,
                                        dwFlags,
                                        0);
    if (NULL == hInternetRequest)
    {
        assert(!"HTTP接続を開くに失敗");
        goto LABEL_ERROR;
    }

    // HTTP要求送信
    if (!HttpSendRequestA(hInternetRequest,
                          strHeaders.c_str(),
                          (DWORD)strHeaders.length(),
                          (LPVOID)(strParameter.length() == 0 ? 0 : (char *)strParameter.c_str()),
                          strParameter.length()))
    {
        assert(!"HTTP要求送信に失敗");
        goto LABEL_ERROR;
    }

    // HTTP要求に対応するステータスコードの取得
    DWORD dwStatusCode;
    {
        DWORD dwLength = sizeof(DWORD);
        if (!HttpQueryInfo(hInternetRequest,
                           HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER,
                           &dwStatusCode,
                           &dwLength,
                           0))
        {
            assert(!"HTTP要求に対応するステータスコードの取得に失敗");
            goto LABEL_ERROR;
        }
    }
    if (HTTP_STATUS_OK != dwStatusCode)
    {
        printf("dwStatusCode=%u\n", dwStatusCode);
        assert(!"ステータスコードがOKでない");
        goto LABEL_ERROR;
    }

    // HTTPファイル読み込み
    char szReadBuffer[READBUFFER_SIZE + 1];
    while (1)
    {
        DWORD dwRead = 0;
        if (!InternetReadFile(hInternetRequest, szReadBuffer, READBUFFER_SIZE, &dwRead))
        {
            assert(!"HTTPファイル読み込みに失敗");
            goto LABEL_ERROR;
        }
        if (0 == dwRead)
        {
            break;
        }
        std::string packet(szReadBuffer, dwRead);
        ssRead << packet;
    }

    rstrResult = ssRead.str();

    InternetCloseHandle(hInternetRequest);
    InternetCloseHandle(hInternetConnect);
    InternetCloseHandle(hInternetOpen);
    return true;

LABEL_ERROR:
    InternetCloseHandle(hInternetRequest);
    InternetCloseHandle(hInternetConnect);
    InternetCloseHandle(hInternetOpen);
    return false;
}

int main(int argc, char *argv[])
{
    std::string strUserAgent = "HttpRequestTest";
    //tstring strUrl = _T("http://weather.livedoor.com/forecast/webservice/json/v1");
    std::string strUrl = "https://www.google.com/";
    bool bIsHttpVerbGet = true;
    //tstring strParameter = _T("city=400040");
    std::string strParameter = "";

    std::string strResult;
    if (!HttpRequest(strUserAgent,
                     strUrl,
                     bIsHttpVerbGet,
                     strParameter,
                     strResult))
    {
        return false;
    }

    printf("%s\n", strResult.c_str());

    return 0;
}
