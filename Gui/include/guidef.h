//==============================================================================
// Copyright: Reksoft Ltd.
//==============================================================================
//
// Author:              $Author:$
// Creation date:       2015.03.07
// Modification date:   $Date$
// Module:              Gui
// Platform:            MS Windows 7, Linux, MAC OS X 10.6.x
//
//------------------------------------------------------------------------------
// Note:
//------------------------------------------------------------------------------
// Warning:
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
#ifndef GUIDEF_H
#define GUIDEF_H


#include <qglobal.h>


//------------------------------------------------------------------------------
/**
 * @defgroup Gui
 * @brief The Gui module contains gui data structures, objects, managers and
 * factories.
 */
//------------------------------------------------------------------------------
#ifdef Q_OS_WIN
#ifdef GUI_NODLL
# define GUI_DEF
#else
# ifdef GUI_BUILD
#    define GUI_DEF __declspec(dllexport)
# else
#    define GUI_DEF __declspec(dllimport)
# endif
#endif
#else
#  define GUI_DEF
#endif
#endif //GUIDEF_H
