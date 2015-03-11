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
#ifndef SBTOOLBAR_H
#define SBTOOLBAR_H


#include <SBPanel.h>


class GUI_DEF SBToolBar
        : public SBPanel
{
    Q_OBJECT
    public:

        SBToolBar(QWidget* pParent = nullptr);
        ~SBToolBar();

        void Add(QWidget* pWidget);

    private:

        struct Private;
        /// A pointer to the private implementation.
        Private* m_pPrivate;
};//class SBToolBar
#endif // SBTOOLBAR_H

