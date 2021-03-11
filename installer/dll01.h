#ifndef DLL01_H
#define DLL01_H

#include "dll01_global.h"

class DLL01_EXPORT Dll01
{
public:
    Dll01();
};

extern "C" DLL01_EXPORT const char *get_app_dir();

#endif // DLL01_H
