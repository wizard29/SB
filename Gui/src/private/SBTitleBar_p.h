//==============================================================================
// Copyright: Reksoft Ltd.
//==============================================================================
//
// Author:              $Author:$
// Creation date:       2015.03.07
// Modification date:   $Date:$
// Module:              Gui
// Platform:            MS Windows 7, Linux, MAC OS X 10.6.x
//
//------------------------------------------------------------------------------
// Note:
//------------------------------------------------------------------------------
// Warning:
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
#ifndef SBTITLEBAR_P_H
#define SBTITLEBAR_P_H


#include "SBTitleBar.h"


class QLabel;
class QGridLayout;


struct SBTitleBar::Private
{

    public:

        Private(SBTitleBar* pHost);
        ~Private();

    public:

        typedef QList<QWidget*> WidgetList;
        /// A pointer to the host widget.
        SBTitleBar* m_pHost;
        /// A pointer to the text label.
        QLabel* m_pText;
        /// A pointer to the icon.
        QLabel* m_pIcon;
        /// A pointer to the horizontal layout.
        QGridLayout* m_pHRZLayout;
        /// A pointer to the vertical layout.
        QGridLayout* m_pVRTLayout;
        /// A pointer to the content widget.
        QWidget* m_pContent;
        /// The left aligned widget list.
        WidgetList m_leftWidgets;
        /// The right aligned widget list.
        WidgetList m_rightWidgets;
        /// The bottom aligned widget list.
        WidgetList m_bottomWidgets;
        /// The widget's border margins
        static const QMargins BORDERMARGINS;
};//struct SBTitleBar::Private
#endif // SBTITLEBAR_P_H
