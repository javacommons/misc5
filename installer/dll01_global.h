#ifndef DLL01_GLOBAL_H
#define DLL01_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(DLL01_LIBRARY)
#  define DLL01_EXPORT Q_DECL_EXPORT
#else
#  define DLL01_EXPORT Q_DECL_IMPORT
#endif

#endif // DLL01_GLOBAL_H
