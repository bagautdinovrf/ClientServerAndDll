#ifndef VOWELS_GLOBAL_H
#define VOWELS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(VOWELS_LIBRARY)
#  define VOWELS_EXPORT Q_DECL_EXPORT
#else
#  define VOWELS_EXPORT Q_DECL_IMPORT
#endif

#endif // VOWELS_GLOBAL_H
