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

        void Activate(SBWidget* pWidget);
        void ActivateNext();
        void ActivatePrev();        
        void Add(SBWidget* pWidget);
        void Add(SBPanel* pWidget);
        void Remove(SBWidget* pWidget);
        void Remove(SBPanel* pWidget);
        void Destroyed(QObject* pObject);
        void PanelDestroyed(QObject* pObject);
        bool eventFilter(QObject*, QEvent*);

    private:

        void Raise(SBWidget* pWidget);
        void Lower(SBWidget* pWidget);
        bool HasVisibleTopLevel() const;
        void MovePanelsTo(SBWidget* pWidget);
        static void MovePanelToWidget(SBPanel* pPanel, SBWidget* pWidget);

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

