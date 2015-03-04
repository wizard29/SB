//==============================================================================
// Copyright: Reksoft Ltd.
//==============================================================================
//
// Author:              $Author:$
// Creation date:       2015.03.04
// Modification date:   $Date$
// Module:              Core
// Platform:            MS Windows 7, Linux, MAC OS X 10.6.x
//
//------------------------------------------------------------------------------
// Note:
//------------------------------------------------------------------------------
// Warning:
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
#ifndef COREDEF_H
#define COREDEF_H


#include <qglobal.h>


//------------------------------------------------------------------------------
/**
 * @defgroup Core
 * @brief The Core module contains core data structures, objects, managers and
 * factories.
 */
//------------------------------------------------------------------------------
#ifdef Q_OS_WIN
#ifdef CORE_NODLL
# define CORE_DEF
#else
# ifdef CORE_BUILD
#    define CORE_DEF __declspec(dllexport)
# else
#    define CORE_DEF __declspec(dllimport)
# endif
#endif
#else
#  define CORE_DEF
#endif

#endif //COREDEF_H
