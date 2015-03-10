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
#ifndef SBMDIMANAGER_P_H
#define SBMDIMANAGER_P_H


#include "SBMDIManager.h"


struct SBMDIManager::Private
{
    public:

        Private(SBMDIManager* pHost);
        ~Private();

        void Activate(QWidget* pWidget);
        void ActivateNext();
        void ActivatePrev();
        void MovePanelsTo(QWidget* pWidget);
        void Add(QWidget* pWidget);
        void Remove(QWidget* pWidget);
        void AddPanel(QWidget* pWidget);
        void RemovePanel(QWidget* pWidget);

    public:

        /// A pointer to a host object.
        SBMDIManager* m_pHost;
        /// List of managed widgets.
        QList<QWidget*> m_widgets;
        /// Set of managed widgets.
        QSet<QWidget*> m_widgetSet;
        /// List of managed panels.
        QList<QWidget*> m_panels;
        /// Set of managed panels.
        QSet<QWidget*> m_paneltSet;
        /// A pointer to current active widget.
        QWidget* m_pActiveWidget;
};//struct SBMDIManager::Private
#endif // SBMDIMANAGER_P_H

