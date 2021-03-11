#include <windows.h>
#include <string>
#include <shlobj.h>
#include <iostream>
#include <sstream>

#include "strconv.h"

static int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{

    if (uMsg == BFFM_INITIALIZED)
    {
        std::string tmp = (const char *)lpData;
        std::cout << "path: " << tmp << std::endl;
        SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lpData);
    }

    return 0;
}

std::string BrowseFolder(std::string saved_path)
{
    wchar_t path[MAX_PATH];

    const char *path_param = saved_path.c_str();

    BROWSEINFOW bi = {0};
    bi.hwndOwner = nullptr;
    bi.lpszTitle = (L"Browse for folder...");
    bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
    bi.lpfn = BrowseCallbackProc;
    bi.lParam = (LPARAM)path_param;

    LPITEMIDLIST pidl = SHBrowseForFolderW(&bi);

    if (pidl != 0)
    {
        //get the name of the folder and put it in path
        SHGetPathFromIDListW(pidl, path);

        //free memory used
        IMalloc *imalloc = 0;
        if (SUCCEEDED(SHGetMalloc(&imalloc)))
        {
            imalloc->Free(pidl);
            imalloc->Release();
        }

        return wide_to_utf8(path);
    }

    return "";
}

std::string BrowseForFile()
{
    static __thread OPENFILENAMEW ofn;
    wchar_t szPathName[MAX_PATH];
    LARGE_INTEGER liSize;
    MEMORYSTATUSEX msex = {sizeof(MEMORYSTATUSEX)};
    DWORD dwBytesRead;
    DWORD ErrCode;
    wchar_t szErrMsg[64];

    ofn.lStructSize = sizeof(OPENFILENAMEW);
    ofn.hwndOwner = nullptr;
    ofn.lpstrFilter = L"テキストファイル(*.TXT)\0*.txt\0\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFile = szPathName;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrInitialDir = NULL;
    ofn.lpstrTitle = L"ファイルを開く";
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (!GetOpenFileNameW(&ofn))
    {
        ErrCode = CommDlgExtendedError();
        if (ErrCode)
        {
            std::wstring errMsg = format(L"エラーコード : %d", ErrCode);
            MessageBoxW(NULL, errMsg.c_str(), L"GetOpenFileName", MB_OK);
            return FALSE;
        }
        // キャンセルした場合
        return "";
    }
    return wide_to_utf8(szPathName);
}

int main(int argc, const char *argv[])
{
    std::string path = BrowseFolder(argv[1]);
    std::cout << path << std::endl;
    std::string file = BrowseForFile();
    std::cout << file << std::endl;
    return 0;
}
