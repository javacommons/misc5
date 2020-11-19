/* strconv2.h v0.9.1               */
/* Last Modified: 2020/07/01 03:17 */
#ifndef STRCONV2_H
#define STRCONV2_H

#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

static inline wchar_t *cp_to_wide(const char *s, UINT codepage)
{
    int in_length = (int)strlen(s);
    int out_length = MultiByteToWideChar(codepage, 0, s, in_length, 0, 0);
    wchar_t *result = (wchar_t *)malloc(sizeof(wchar_t) * (out_length+1));
    if (out_length) MultiByteToWideChar(codepage, 0, s, in_length, result, out_length);
    result[out_length] = L'\0';
    return result;
}
static inline char *wide_to_cp(const wchar_t *s, UINT codepage)
{
    int in_length = (int)wcslen(s);
    int out_length = WideCharToMultiByte(codepage, 0, s, in_length, 0, 0, 0, 0);
    char *result = (char *)malloc(sizeof(char) * (out_length+1));
    if (out_length) WideCharToMultiByte(codepage, 0, s, in_length, result, out_length, 0, 0);
    result[out_length] = '\0';
    return result;
}

static inline char *cp_to_utf8(const char *s, UINT codepage)
{
    if (codepage == CP_UTF8) return _strdup(s);
    wchar_t *wide = cp_to_wide(s, codepage);
    char *result = wide_to_cp(wide, CP_UTF8);
    free(wide);
    return result;
}
static inline char *utf8_to_cp(const char *s, UINT codepage)
{
    if (codepage == CP_UTF8) return _strdup(s);
    wchar_t *wide = cp_to_wide(s, CP_UTF8);
    char *result = wide_to_cp(wide, codepage);
    free(wide);
    return result;
}

static inline char *cp_to_ansi(const char *s, UINT codepage)
{
    if (codepage == CP_ACP) return _strdup(s);
    wchar_t *wide = cp_to_wide(s, codepage);
    char *result = wide_to_cp(wide, CP_ACP);
    free(wide);
    return result;
}
static inline char *ansi_to_cp(const char *s, UINT codepage)
{
    if (codepage == CP_UTF8) return _strdup(s);
    wchar_t *wide = cp_to_wide(s, CP_ACP);
    char *result = wide_to_cp(wide, codepage);
    free(wide);
    return result;
}

static inline wchar_t *ansi_to_wide(const char *s)
{
    return cp_to_wide(s, CP_ACP);
}
static inline char *wide_to_ansi(const wchar_t *s)
{
    return wide_to_cp(s, CP_ACP);
}

static inline wchar_t *sjis_to_wide(const char *s)
{
    return cp_to_wide(s, 932);
}
static inline char *wide_to_sjis(const wchar_t *s)
{
    return wide_to_cp(s, 932);
}

static inline wchar_t *utf8_to_wide(const char *s)
{
    return cp_to_wide(s, CP_UTF8);
}
static inline char *wide_to_utf8(const wchar_t *s)
{
    return wide_to_cp(s, CP_UTF8);
}

static inline char *ansi_to_utf8(const char *s)
{
    return cp_to_utf8(s, CP_ACP);
}
static inline char *utf8_to_ansi(const char *s)
{
    return utf8_to_cp(s, CP_ACP);
}

static inline char *sjis_to_utf8(const char *s)
{
    return cp_to_utf8(s, 932);
}
static inline char *utf8_to_sjis(const char *s)
{
    return utf8_to_cp(s, 932);
}

static inline wchar_t *strconv_getenvW(const wchar_t *name) {
    const wchar_t *p = _wgetenv(name);
    if(!p) return _wcsdup(L"");
    return _wcsdup(p);
}

static inline char *strconv_getenv(const char *name) {
    wchar_t *nameW = utf8_to_wide(name);
    wchar_t *value = strconv_getenvW(nameW);
    free(nameW);
    char *result = wide_to_utf8(value);
    free(value);
    return result;
}

static inline wchar_t *strconv_parent_programW()
{
    DWORD myPID = GetCurrentProcessId();
    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if(hProcessSnap == INVALID_HANDLE_VALUE) return _wcsdup(L"");
    PROCESSENTRY32W pe32;
    pe32.dwSize = sizeof( pe32 );
    DWORD parentPID = 0;
    if(!Process32FirstW(hProcessSnap, &pe32)) {
        CloseHandle(hProcessSnap);
        return _wcsdup(L"");
    }
    do {
        if(pe32.th32ProcessID == myPID) {
            parentPID = pe32.th32ParentProcessID;
        }
    } while(Process32NextW(hProcessSnap, &pe32));
    const wchar_t *result = NULL;
    if(!Process32FirstW(hProcessSnap, &pe32)) {
        CloseHandle(hProcessSnap);
        return _wcsdup(L"");
    }
    do {
        if(pe32.th32ProcessID == parentPID) {
            result = _wcsdup(pe32.szExeFile);
        }
    } while(Process32NextW(hProcessSnap, &pe32));
    CloseHandle(hProcessSnap);
    if(!result) return _wcsdup(L"");
    return _wcsdup(result);
}

static inline char *strconv_parent_program()
{
    wchar_t *wide = strconv_parent_programW();
    char *result = wide_to_utf8(wide);
    free(wide);
    return result;
}

typedef struct strconv_io {
    FILE *m_ostrm;
    UINT m_codepage;
    CRITICAL_SECTION m_csect;
} strconv_io;

static inline strconv_io *strconv_io_create(FILE *ostrm) {
    strconv_io *this_p = (strconv_io *)malloc(sizeof(strconv_io));
    this_p->m_ostrm = ostrm;
    wchar_t *program = strconv_parent_programW();
    wchar_t *term = strconv_getenvW(L"TERM");
    BOOL use_utf8 = ((wcscmp(program, L"bash.exe")==0 || wcscmp(program,  L"zsh.exe")==0) && wcscmp(term, L"cygwin")!=0);
    free(program);
    free(term);
    this_p->m_codepage = use_utf8 ? CP_UTF8 : GetConsoleCP();
    InitializeCriticalSectionAndSpinCount(&this_p->m_csect, 0x00000400);
    return this_p;
}

static inline void strconv_io_delete(strconv_io *this_p) {
    DeleteCriticalSection(&this_p->m_csect);
    free(this_p);
}

static inline BOOL _strconv_is_console(FILE *ostrm) {
    return (ostrm == stdout) || (ostrm == stderr);
}

static inline UINT _strconv_out_codepage(strconv_io *this_p, FILE *ostrm) {
    if(_strconv_is_console(ostrm)) return this_p->m_codepage; else return CP_UTF8;
}

/* https://github.com/ivanrad/getline */
static inline ssize_t _strconv_getdelim(char **lineptr, size_t *n, int delim, FILE *stream) {
    char *cur_pos, *new_lineptr;
    size_t new_lineptr_len;
    int c;
    if (lineptr == NULL || n == NULL || stream == NULL) {
        errno = EINVAL;
        return -1;
    }
    if (*lineptr == NULL) {
        *n = 128; /* init len */
        if ((*lineptr = (char *)malloc(*n)) == NULL) {
            errno = ENOMEM;
            return -1;
        }
    }
    cur_pos = *lineptr;
    for (;;) {
        c = getc(stream);
        if (ferror(stream) || (c == EOF && cur_pos == *lineptr))
            return -1;
        if (c == EOF)
            break;
        if ((*lineptr + *n - cur_pos) < 2) {
            if (SSIZE_MAX / 2 < *n) {
#ifdef EOVERFLOW
                errno = EOVERFLOW;
#else
                errno = ERANGE; /* no EOVERFLOW defined */
#endif
                return -1;
            }
            new_lineptr_len = *n * 2;
            if ((new_lineptr = (char *)realloc(*lineptr, new_lineptr_len)) == NULL) {
                errno = ENOMEM;
                return -1;
            }
            cur_pos = new_lineptr + (cur_pos - *lineptr);
            *lineptr = new_lineptr;
            *n = new_lineptr_len;
        }
        *cur_pos++ = (char)c;
        if (c == delim)
            break;
    }
    *cur_pos = '\0';
    return (ssize_t)(cur_pos - *lineptr);
}

/* https://github.com/ivanrad/getline */
static inline ssize_t _strconv_getline(char **lineptr, size_t *n, FILE *stream) {
    return _strconv_getdelim(lineptr, n, '\n', stream);
}

static inline void strconv_printfW(strconv_io *this_p, const wchar_t *format, ...)
{
    va_list args;
    va_start(args, format);
    int v_len = _vsnwprintf(NULL, 0, format, args);
    wchar_t *v_str = (wchar_t *)malloc(sizeof(wchar_t)*(v_len + 1));
    _vsnwprintf(v_str, v_len + 1, format, args);
    va_end(args);
    char *v_out = wide_to_cp(v_str, _strconv_out_codepage(this_p, this_p->m_ostrm));
    EnterCriticalSection(&this_p->m_csect);
    fprintf(this_p->m_ostrm, "%s", v_out);
    fflush(this_p->m_ostrm);
    free(v_str);
    free(v_out);
    LeaveCriticalSection(&this_p->m_csect);
}

static inline void strconv_fprintfW(strconv_io *this_p, FILE *ostrm, const wchar_t *format, ...)
{
    va_list args;
    va_start(args, format);
    int v_len = _vsnwprintf(NULL, 0, format, args);
    wchar_t *v_str = (wchar_t *)malloc(sizeof(wchar_t)*(v_len + 1));
    _vsnwprintf(v_str, v_len + 1, format, args);
    va_end(args);
    char *v_out = wide_to_cp(v_str, _strconv_out_codepage(this_p, ostrm));
    EnterCriticalSection(&this_p->m_csect);
    fprintf(ostrm, "%s", v_out);
    fflush(ostrm);
    free(v_str);
    free(v_out);
    LeaveCriticalSection(&this_p->m_csect);
}

static inline void strconv_printf(strconv_io *this_p, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    int v_len = _vsnprintf(NULL, 0, format, args);
    char *v_str = (char *)malloc(sizeof(char)*(v_len + 1));
    _vsnprintf(v_str, v_len + 1, format, args);
    va_end(args);
    char *v_out = utf8_to_cp(v_str, _strconv_out_codepage(this_p, this_p->m_ostrm));
    EnterCriticalSection(&this_p->m_csect);
    fprintf(this_p->m_ostrm, "%s", v_out);
    fflush(this_p->m_ostrm);
    free(v_str);
    free(v_out);
    LeaveCriticalSection(&this_p->m_csect);
}

static inline void strconv_fprintf(strconv_io *this_p, FILE *ostrm, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    int v_len = _vsnprintf(NULL, 0, format, args);
    char *v_str = (char *)malloc(sizeof(char)*(v_len + 1));
    _vsnprintf(v_str, v_len + 1, format, args);
    va_end(args);
    char *v_out = utf8_to_cp(v_str, _strconv_out_codepage(this_p, ostrm));
    EnterCriticalSection(&this_p->m_csect);
    fprintf(ostrm, "%s", v_out);
    fflush(ostrm);
    free(v_str);
    free(v_out);
    LeaveCriticalSection(&this_p->m_csect);
}

static inline void strconv_writeW(strconv_io *this_p, const wchar_t *s) {
    strconv_printfW(this_p, L"%s", s);
}

static inline void strconv_fwriteW(strconv_io *this_p, FILE *ostrm, const wchar_t *s) {
    strconv_fprintfW(this_p, ostrm, L"%s", s);
}

static inline void strconv_write(strconv_io *this_p, const char *s) {
    strconv_printf(this_p, "%s", s);
}

static inline void strconv_fwrite(strconv_io *this_p, FILE *ostrm, const char *s) {
    strconv_fprintf(this_p, ostrm, "%s", s);
}

static inline void strconv_writelnW(strconv_io *this_p, const wchar_t *s) {
    strconv_printfW(this_p, L"%s\n", s);
}

static inline void strconv_fwritelnW(strconv_io *this_p, FILE *ostrm, const wchar_t *s) {
    strconv_fprintfW(this_p, ostrm, L"%s\n", s);
}

static inline void strconv_writeln(strconv_io *this_p, const char *s) {
    strconv_printf(this_p, "%s\n", s);
}

static inline void strconv_fwriteln(strconv_io *this_p, FILE *ostrm, const char *s) {
    strconv_fprintf(this_p, ostrm, "%s\n", s);
}

static inline wchar_t *strconv_getsW(strconv_io *this_p, const wchar_t *prompt) {
    EnterCriticalSection(&this_p->m_csect);
    if(prompt == NULL) prompt = L"";
    if(wcscmp(prompt, L"")!=0) {
        char *promptCP = wide_to_cp(prompt, this_p->m_codepage);
        fprintf(stderr, "%s", promptCP);
        fflush(stderr);
        free(promptCP);
    }
    char *line = NULL;
    size_t n = 256;
    ssize_t ret = _strconv_getline(&line, &n, stdin);
    wchar_t *result = NULL;
    if(ret<=0) {
        result = _wcsdup(L"");
    } else {
        if(line[ret-1]=='\n') line[ret-1] = '\0';
        result = cp_to_wide(line, this_p->m_codepage);
        free(line);
    }
    LeaveCriticalSection(&this_p->m_csect);
    return result;
}

static inline char *strconv_gets(strconv_io *this_p, const char *prompt) {
    EnterCriticalSection(&this_p->m_csect);
    if(prompt == NULL) prompt = "";
    if(strcmp(prompt, "")!=0) {
        char *promptCP = utf8_to_cp(prompt, this_p->m_codepage);
        fprintf(stderr, "%s", promptCP);
        fflush(stderr);
        free(promptCP);
    }
    char *line = NULL;
    size_t n = 256;
    ssize_t ret = _strconv_getline(&line, &n, stdin);
    char *result = NULL;
    if(ret<=0) {
        result = _strdup("");
    } else {
        if(line[ret-1]=='\n') line[ret-1] = '\0';
        result = cp_to_utf8(line, this_p->m_codepage);
        free(line);
    }
    LeaveCriticalSection(&this_p->m_csect);
    return result;
}

static inline char *strconv_to_consoleW(strconv_io *this_p, const wchar_t *s) {
    return wide_to_cp(s, this_p->m_codepage);
}

static inline char *strconv_to_console(strconv_io *this_p, const char *s) {
    return utf8_to_cp(s, this_p->m_codepage);
}

static inline wchar_t *strconv_sprintfW(strconv_io *this_p, const wchar_t *format, ...)
{
    (void)this_p;
    va_list args;
    va_start(args, format);
    int v_len = _vsnwprintf(NULL, 0, format, args);
    wchar_t *v_str = (wchar_t*)malloc(sizeof(wchar_t*)*(v_len + 1));
    _vsnwprintf(v_str, v_len + 1, format, args);
    va_end(args);
    return v_str;
}

static inline char *strconv_sprintf(strconv_io *this_p, const char *format, ...)
{
    (void)this_p;
    va_list args;
    va_start(args, format);
    int v_len = _vsnprintf(NULL, 0, format, args);
    char *v_str = (char *)malloc(sizeof(char)*(v_len + 1));
    _vsnprintf(v_str, v_len + 1, format, args);
    va_end(args);
    return v_str;
}

typedef struct strconv_buffer {
    char *m_buffer;
} strconv_buffer;

static inline strconv_buffer *strconv_buffer_start() {
    strconv_buffer *v_stream = (strconv_buffer *)malloc(sizeof(strconv_buffer));
    v_stream->m_buffer = _strdup("");
    return v_stream;
}

static inline wchar_t *strconv_buffer_endW(strconv_buffer *stream) {
    wchar_t *v_result = utf8_to_wide(stream->m_buffer);
    free(stream->m_buffer);
    free(stream);
    return v_result;
}

static inline char *strconv_buffer_end(strconv_buffer *stream) {
    char *v_result = stream->m_buffer;
    free(stream);
    return v_result;
}

static inline void strconv_buffer_printfW(strconv_buffer *stream, const wchar_t *format, ...)
{
    va_list args;
    va_start(args, format);
    int v_len = _vsnwprintf(NULL, 0, format, args);
    wchar_t *v_str = (wchar_t *)malloc(sizeof(wchar_t)*(v_len + 1));
    _vsnwprintf(v_str, v_len + 1, format, args);
    va_end(args);
    char *v_utf8 = wide_to_utf8(v_str);
    free(v_str);
    char *v_new = strconv_sprintf(NULL, "%s%s", stream->m_buffer, v_utf8);
    free(v_utf8);
    free(stream->m_buffer);
    stream->m_buffer = v_new;
}

static inline void strconv_buffer_printf(strconv_buffer *stream, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    int v_len = _vsnprintf(NULL, 0, format, args);
    char *v_str = (char *)malloc(sizeof(char)*(v_len + 1));
    _vsnprintf(v_str, v_len + 1, format, args);
    va_end(args);
    char *v_new = strconv_sprintf(NULL, "%s%s", stream->m_buffer, v_str);
    free(v_str);
    free(stream->m_buffer);
    stream->m_buffer = v_new;
}

static inline void strconv_buffer_writeW(strconv_buffer *stream, const wchar_t *s) {
    strconv_buffer_printfW(stream, L"%s", s);
}

static inline void strconv_buffer_write(strconv_buffer *stream, const char *s) {
    strconv_buffer_printf(stream, "%s", s);
}

static inline void strconv_strem_writelnW(strconv_buffer *stream, const wchar_t *s) {
    strconv_buffer_printfW(stream, L"%s\n", s);
}

static inline void strconv_buffer_writeln(strconv_buffer *stream, const char *s) {
    strconv_buffer_printf(stream, "%s\n", s);
}

#endif /* STRCONV2_H */
