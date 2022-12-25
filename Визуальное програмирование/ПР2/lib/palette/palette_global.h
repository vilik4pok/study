#ifndef PALETTE_GLOBAL_H
#define PALETTE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(PALETTE_LIBRARY)
#  define PALETTESHARED_EXPORT Q_DECL_EXPORT
#else
#  define PALETTESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // PALETTE_GLOBAL_H
