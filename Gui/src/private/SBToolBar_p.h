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


class SBToolBarContentWidget;


struct SBToolBar::Private
{
    public:

        Private(SBToolBar* pHost);
        ~Private();

        void FitToBestSize();

    public:

        /// A pointer to the host widget.
        SBToolBar* m_pHost;
        /// A pointer to the toolbar content.
        SBToolBarContentWidget* m_pContent;
};//struct SBToolBar::Private
#endif // SBTOOLBAR_P_H

