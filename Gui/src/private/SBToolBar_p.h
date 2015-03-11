//==============================================================================
// Copyright: Reksoft Ltd.
//==============================================================================
//
// Author:              $Author:$
// Creation date:       2015.03.11
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
#ifndef SBTOOLBAR_P_H
#define SBTOOLBAR_P_H


#include "SBToolBar.h"


struct SBToolBar::Private
{
    public:

        Private(SBToolBar* pHost);
        ~Private();

        void Add(QWidget* pWidget);

    public:

        /// A pointer to the host widget.
        SBToolBar* m_pHost;
};//struct SBToolBar::Private
#endif // SBTOOLBAR_P_H

