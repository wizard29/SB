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
#include <qset.h>


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
        void Destroyed(QObject* pObject);
        void PanelDestroyed(QObject* pObject);
        bool eventFilter(QObject*, QEvent*);

    private:

        void Raise(QWidget* pWidget);
        void Lower(QWidget* pWidget);
        static void MovePanelToWidget(QWidget* pPanel, QWidget* pWidget);

    public:

        /// A pointer to a host object.
        SBMDIManager* m_pHost;
        /// Activation order of managed widgets.
        QList<QObject*> m_widgets;
        /// Set of managed widgets.
        QSet<QObject*> m_widgetSet;
        /// Set of managed panels.
        QSet<QObject*> m_panelSet;
        /// A pointer to current active widget.
        QObject* m_pActiveWidget;
};//struct SBMDIManager::Private
#endif // SBMDIMANAGER_P_H

