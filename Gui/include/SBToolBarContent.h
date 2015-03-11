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
#ifndef SBTOOLBARCONTENT_H
#define SBTOOLBARCONTENT_H


#include <guidef.h>
#include <qwidget.h>


class GUI_DEF SBToolBarContent
        : public QWidget
{
    Q_OBJECT
    public:

        SBToolBarContent(QWidget* pParent = nullptr, Qt::WindowFlags f = 0);
        ~SBToolBarContent();

    private:

        struct Private;
        /// A pointer to the private implementation.
        Private* m_pPrivate;
};//class SBToolBarContent
#endif // SBTOOLBARCONTENT_H

