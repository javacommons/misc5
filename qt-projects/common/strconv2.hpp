/* strconv2.hpp v0.0.0             */
/* Last Modified: 2020/11/09 07:31 */
#ifndef STRCONV2_HPP
#define STRCONV2_HPP

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4996)
#endif

#include <windows.h>
#include <assert.h>
#include <io.h>
#include <tlhelp32.h>
#include <fstream>
#include <iostream>
#include <map>
#include <mutex>
#include <string>
#include <vector>

namespace strconv2 {

#if __cplusplus >= 201103L
static inline std::wstring cp_to_wide(const std::string &s, UINT codepage) {
    int in_length = (int)s.length();
    int out_length = MultiByteToWideChar(codepage, 0, s.c_str(), in_length, 0, 0);
    std::wstring result(out_length, L'\0');
    if (out_length) MultiByteToWideChar(codepage, 0, s.c_str(), in_length, &result[0], out_length);
    return result;
}
static inline std::string wide_to_cp(const std::wstring &s, UINT codepage) {
    int in_length = (int)s.length();
    int out_length = WideCharToMultiByte(codepage, 0, s.c_str(), in_length, 0, 0, 0, 0);
    std::string result(out_length, '\0');
    if (out_length) WideCharToMultiByte(codepage, 0, s.c_str(), in_length, &result[0], out_length, 0, 0);
    return result;
}
#else /* __cplusplus < 201103L */
static inline std::wstring cp_to_wide(const std::string &s, UINT codepage) {
    int in_length = (int)s.length();
    int out_length = MultiByteToWideChar(codepage, 0, s.c_str(), in_length, 0, 0);
    std::vector<wchar_t> buffer(out_length);
    if (out_length) MultiByteToWideChar(codepage, 0, s.c_str(), in_length, &buffer[0], out_length);
    std::wstring result(buffer.begin(), buffer.end());
    return result;
}
static inline std::string wide_to_cp(const std::wstring &s, UINT codepage) {
    int in_length = (int)s.length();
    int out_length = WideCharToMultiByte(codepage, 0, s.c_str(), in_length, 0, 0, 0, 0);
    std::vector<char> buffer(out_length);
    if (out_length) WideCharToMultiByte(codepage, 0, s.c_str(), in_length, &buffer[0], out_length, 0, 0);
    std::string result(buffer.begin(), buffer.end());
    return result;
}
#endif

static inline std::string cp_to_cp(const std::string &s, UINT from, UINT to) {
    if (from == to) return s;
    std::wstring wide = cp_to_wide(s, from);
    return wide_to_cp(wide, to);
}

static inline std::string cp_to_utf8(const std::string &s, UINT codepage) {
    if (codepage == CP_UTF8) return s;
#if 0x0
    std::wstring wide = cp_to_wide(s, codepage);
    return wide_to_cp(wide, CP_UTF8);
#else
    return cp_to_cp(s, codepage, CP_UTF8);
#endif
}
static inline std::string utf8_to_cp(const std::string &s, UINT codepage) {
    if (codepage == CP_UTF8) return s;
#if 0x0
    std::wstring wide = cp_to_wide(s, CP_UTF8);
    return wide_to_cp(wide, codepage);
#else
    return cp_to_cp(s, CP_UTF8, codepage);
#endif
}

static inline std::wstring ansi_to_wide(const std::string &s) {
    return cp_to_wide(s, CP_ACP);
}
static inline std::string wide_to_ansi(const std::wstring &s) {
    return wide_to_cp(s, CP_ACP);
}

static inline std::wstring sjis_to_wide(const std::string &s) {
    return cp_to_wide(s, 932);
}
static inline std::string wide_to_sjis(const std::wstring &s) {
    return wide_to_cp(s, 932);
}

static inline std::wstring utf8_to_wide(const std::string &s) {
    return cp_to_wide(s, CP_UTF8);
}
static inline std::string wide_to_utf8(const std::wstring &s) {
    return wide_to_cp(s, CP_UTF8);
}

static inline std::string ansi_to_utf8(const std::string &s) {
    return cp_to_utf8(s, CP_ACP);
}
static inline std::string utf8_to_ansi(const std::string &s) {
    return utf8_to_cp(s, CP_ACP);
}

static inline std::string sjis_to_utf8(const std::string &s) {
    return cp_to_utf8(s, 932);
}
static inline std::string utf8_to_sjis(const std::string &s) {
    return utf8_to_cp(s, 932);
}

static inline std::wstring formatW(const wchar_t *format, ...) {
    ::va_list args;
    va_start(args, format);
    int v_len = ::_vsnwprintf(nullptr, 0, format, args);
    std::vector<wchar_t> v_buffer(v_len + 1);
    ::_vsnwprintf(&v_buffer[0], v_len + 1, format, args);
    va_end(args);
    return &v_buffer[0];
}
static inline std::string formatJ(const char *format, ...) {
    ::va_list args;
    va_start(args, format);
    int v_len = ::_vsnprintf(nullptr, 0, format, args);
    std::vector<char> v_buffer(v_len + 1);
    ::_vsnprintf(&v_buffer[0], v_len + 1, format, args);
    va_end(args);
    return &v_buffer[0];
}
static inline std::string format(const char *format, ...) {
    ::va_list args;
    va_start(args, format);
    int v_len = ::_vsnprintf(nullptr, 0, format, args);
    std::vector<char> v_buffer(v_len + 1);
    ::_vsnprintf(&v_buffer[0], v_len + 1, format, args);
    va_end(args);
    return &v_buffer[0];
}

class string_io {
    std::ostream* m_ostrm;
    std::istream* m_istrm;
    std::wstring m_parent_program;
    UINT m_console_codepage = 0;
    std::mutex m_mutex;
public:
    explicit string_io(std::ostream& ostrm = std::cout, std::istream& istrm = std::cin): m_ostrm(&ostrm), m_istrm(&istrm) {
        m_parent_program = parent_programW();
        m_console_codepage = ::GetConsoleCP();
    }
    virtual ~string_io() {
    }
protected:
    bool is_console(std::ostream* ostrm) const {
        return (ostrm == &std::cout) || (ostrm == &std::cerr);
    }
    bool is_console(std::istream* istrm) const {
        return (istrm == &std::cin && (m_parent_program == L"bash.exe" || _isatty(_fileno(stdin))));
    }
    UINT out_codepage(std::ostream *ostrm) const {
        if(is_console(ostrm)) return m_console_codepage; else return CP_UTF8;
    }
public:
    void _dump() { // for internal debug
        std::cerr << "string_io { m_parent_program=" << wide_to_ansi(m_parent_program) << ", m_console_codepage=" << m_console_codepage << " }" << std::endl << std::flush;
    }
    void set_out_stream(std::ostream& ostrm) {
        m_ostrm = &ostrm;
    }
    void set_in_stream(std::istream& istrm) {
        m_istrm = &istrm;
    }
    std::wstring getenvW(const std::wstring &name) const {
        const wchar_t *p = ::_wgetenv(name.c_str());
        if(!p) return L"";
        return p;
    }
    std::string getenvJ(const std::string &name) const {
        return wide_to_sjis(getenvW(sjis_to_wide(name)));
    }
    std::string getenv(const std::string &name) const {
        return wide_to_utf8(getenvW(utf8_to_wide(name)));
    }
    bool setenvW(const std::wstring& name, const std::wstring& value, bool overwrite=true) {
        const wchar_t* p = ::_wgetenv(name.c_str());
        if (!p || overwrite) {
            std::wstring str = formatW(L"%s=%s", name.c_str(), value.c_str());
            return (_wputenv(str.c_str()) == 0);
        }
        return true;
    }
    bool setenvJ(const std::string& name, const std::string& value, bool overwrite = true) {
        return setenvW(sjis_to_wide(name), sjis_to_wide(value), overwrite);
    }
    bool setenv(const std::string& name, const std::string& value, bool overwrite = true) {
        return setenvW(utf8_to_wide(name), utf8_to_wide(value), overwrite);
    }
    std::wstring parent_programW() const
    {
        DWORD myPID = ::GetCurrentProcessId();
        HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if(hProcessSnap == INVALID_HANDLE_VALUE) return L"";
        PROCESSENTRY32W pe32;
        pe32.dwSize = sizeof(pe32);
        DWORD parentPID = 0;
        std::map<DWORD, std::wstring> ProcessIdVsName;
        if(!::Process32FirstW(hProcessSnap, &pe32)) {
            ::CloseHandle(hProcessSnap);
            return L"";
        }
        do {
            std::pair<DWORD, std::wstring> p(pe32.th32ProcessID, pe32.szExeFile);
            /*std::pair<std::map<DWORD, std::wstring>::iterator, bool> result = */ProcessIdVsName.insert(p);
            if(pe32.th32ProcessID == myPID) {
                parentPID = pe32.th32ParentProcessID;
            }
        } while(::Process32NextW(hProcessSnap, &pe32));
        ::CloseHandle(hProcessSnap);
        std::map<DWORD, std::wstring>::iterator parent = ProcessIdVsName.find(parentPID);
        if(parent == ProcessIdVsName.end()) return L"";
        return parent->second;
    }
    std::string parent_programJ() const
    {
        return wide_to_cp(parent_programW(), 932);
    }
    std::string parent_program()
    {
        return wide_to_utf8(parent_programW());
    }
    void printfW(const wchar_t *format, ...)
    {
        ::va_list args;
        va_start(args, format);
        int v_len = ::_vsnwprintf(nullptr, 0, format, args);
        std::vector<wchar_t> v_buffer(v_len + 1);
        ::_vsnwprintf(&v_buffer[0], v_len + 1, format, args);
        va_end(args);
        std::wstring v_str = &v_buffer[0];
        std::string v_out = wide_to_cp(v_str, out_codepage(m_ostrm));
        std::lock_guard<std::mutex> lock(m_mutex);
        (*m_ostrm) << v_out << std::flush;
    }
    void printfJ(const char *format, ...)
    {
        ::va_list args;
        va_start(args, format);
        int v_len = ::_vsnprintf(nullptr, 0, format, args);
        std::vector<char> v_buffer(v_len + 1);
        ::_vsnprintf(&v_buffer[0], v_len + 1, format, args);
        va_end(args);
        std::string v_str = &v_buffer[0];
        std::string v_out = cp_to_cp(v_str, 932, out_codepage(m_ostrm));
        std::lock_guard<std::mutex> lock(m_mutex);
        (*m_ostrm) << v_out << std::flush;
    }
    void printf(const char *format, ...)
    {
        ::va_list args;
        va_start(args, format);
        int v_len = ::_vsnprintf(nullptr, 0, format, args);
        std::vector<char> v_buffer(v_len + 1);
        ::_vsnprintf(&v_buffer[0], v_len + 1, format, args);
        va_end(args);
        std::string v_str = &v_buffer[0];
        std::string v_out = utf8_to_cp(v_str, out_codepage(m_ostrm));
        std::lock_guard<std::mutex> lock(m_mutex);
        (*m_ostrm) << v_out << std::flush;
    }
    void printfW(std::ostream &ostrm, const wchar_t *format, ...)
    {
        ::va_list args;
        va_start(args, format);
        int v_len = ::_vsnwprintf(nullptr, 0, format, args);
        std::vector<wchar_t> v_buffer(v_len + 1);
        ::_vsnwprintf(&v_buffer[0], v_len + 1, format, args);
        va_end(args);
        std::wstring v_str = &v_buffer[0];
        std::string v_out = wide_to_cp(v_str, out_codepage(&ostrm));
        std::lock_guard<std::mutex> lock(m_mutex);
        ostrm << v_out << std::flush;
    }
    void printfJ(std::ostream &ostrm, const char *format, ...)
    {
        ::va_list args;
        va_start(args, format);
        int v_len = ::_vsnprintf(nullptr, 0, format, args);
        std::vector<char> v_buffer(v_len + 1);
        _vsnprintf(&v_buffer[0], v_len + 1, format, args);
        va_end(args);
        std::string v_str = &v_buffer[0];
        std::string v_out = cp_to_cp(v_str, 932, out_codepage(&ostrm));
        std::lock_guard<std::mutex> lock(m_mutex);
        ostrm << v_out << std::flush;
    }
    void printf(std::ostream &ostrm, const char *format, ...)
    {
        ::va_list args;
        va_start(args, format);
        int v_len = ::_vsnprintf(nullptr, 0, format, args);
        std::vector<char> v_buffer(v_len + 1);
        _vsnprintf(&v_buffer[0], v_len + 1, format, args);
        va_end(args);
        std::string v_str = &v_buffer[0];
        std::string v_out = utf8_to_cp(v_str, out_codepage(&ostrm));
        std::lock_guard<std::mutex> lock(m_mutex);
        ostrm << v_out << std::flush;
    }
    void writeW(const std::wstring &s) {
        this->printfW(L"%s", s.c_str());
    }
    void writeJ(const std::string &s) {
        this->printfJ("%s", s.c_str());
    }
    void write(const std::string &s) {
        this->printf("%s", s.c_str());
    }
    void writeW(std::ostream &ostrm, const std::wstring &s) {
        this->printfW(ostrm, L"%s", s.c_str());
    }
    void writeJ(std::ostream &ostrm, const std::string &s) {
        this->printfJ(ostrm, "%s", s.c_str());
    }
    void write(std::ostream &ostrm, const std::string &s) {
        this->printf(ostrm, "%s", s.c_str());
    }
    void writelnW(const std::wstring &s) {
        this->printfW(L"%s\n", s.c_str());
    }
    void writelnJ(const std::string &s) {
        this->printfJ("%s\n", s.c_str());
    }
    void writeln(const std::string &s) {
        this->printf("%s\n", s.c_str());
    }
    void writelnW(std::ostream &ostrm, const std::wstring &s) {
        this->printfW(ostrm, L"%s\n", s.c_str());
    }
    void writelnJ(std::ostream& ostrm, const std::string& s) {
        this->printfJ(ostrm, "%s\n", s.c_str());
    }
    void writeln(std::ostream &ostrm, const std::string &s) {
        this->printf(ostrm, "%s\n", s.c_str());
    }
    bool getlineW(std::wstring &line) {
        if (!is_console(m_istrm) || m_parent_program == L"bash.exe") {
            std::string v_s;
            if (!std::getline(*m_istrm, v_s)) {
                line = L"";
                return false;
            }
            line = utf8_to_wide(v_s);
            return true;
        }
        assert(m_parent_program != L"bash.exe");
        HANDLE std_in = ::GetStdHandle(STD_INPUT_HANDLE);
        wchar_t v_buffer[1];
        DWORD n;
        std::wstring result;
        while(::ReadConsoleW(std_in, v_buffer, 1, &n, NULL)) {
            if (v_buffer[0] == 13) continue;
            if (v_buffer[0] == 10) break;
            result += v_buffer[0];
        }
        line = result;
        return true;
    }
    bool getlineJ(std::string &line) {
        std::wstring result;
        bool b = getlineW(result);
        line = wide_to_sjis(result);
        return b;
    }
    bool getline(std::string &line) {
        std::wstring result;
        bool b = getlineW(result);
        line = wide_to_utf8(result);
        return b;
    }
    std::wstring promptW(const std::wstring &prompt = L"") {
        ::Sleep(100);
        std::lock_guard<std::mutex> lock(m_mutex);
        if(prompt != L"") {
            std::string v_out = wide_to_cp(prompt, m_console_codepage);
            std::cerr << v_out << std::flush;
        }
        std::wstring v_s;
        getlineW(v_s);
        return v_s;
    }
    std::string promptJ(const std::string &prompt = "") {
        std::wstring v_s = promptW(sjis_to_wide(prompt));
        return wide_to_sjis(v_s);
    }
    std::string prompt(const std::string &prompt = "") {
        std::wstring v_s = promptW(utf8_to_wide(prompt));
        return wide_to_utf8(v_s);
    }
    std::string to_consoleW(const std::wstring &s) const {
        return wide_to_cp(s, m_console_codepage);
    }
    std::string to_consoleJ(const std::string &s) const {
        return cp_to_cp(s, 932, m_console_codepage);
    }
    std::string to_console(const std::string &s) const {
        return utf8_to_cp(s, m_console_codepage);
    }
};

} // namespace strconv

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif /* STRCONV2_HPP */
