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
#include "SBMDIManager_p.h"
#include "SBApplication.h"
#include <SBWidget.h>
#include <SBPanel.h>
#include <qevent.h>


//------------------------------------------------------------------------------
/**
 * @struct SBMDIManager::Private
 * @ingroup Gui
 * @brief The SBMDIManager::Private struct contains internal object data
 * and provides accessory functionality.
 */
//------------------------------------------------------------------------------
/**
 * @brief Constructor.
 * @param pHost - a pointer to a host object. Must not be a null pointer.
 */
SBMDIManager::Private::Private(SBMDIManager* pHost)
    : m_pHost(pHost)
    , m_pActiveWidget(nullptr)
{
    Q_ASSERT(m_pHost);
    sbApp->installEventFilter(m_pHost);
}

//------------------------------------------------------------------------------
/**
 * @brief Destructor.
 */
SBMDIManager::Private::~Private()
{
}

//------------------------------------------------------------------------------
/**
 * @brief Activates a widget.
 * @param pWidget - a pointer to a managed widget.
 */
void SBMDIManager::Private::Activate(SBWidget* pWidget)
{
    QObject* pObject = qobject_cast<QObject*>(pWidget);
    if (m_pActiveWidget != pObject)
    {        
        if (m_pActiveWidget)
        {
            SBWidget* pActiveWidget = qobject_cast<SBWidget*>(m_pActiveWidget);
            Q_ASSERT(pActiveWidget);
            pActiveWidget->overrideWindowState(pActiveWidget->windowState() &
                                               (~Qt::WindowActive));
            QWidget* pFocusWidget = SBApplication::focusWidget();
            if (pFocusWidget && (pFocusWidget ==
                                 qobject_cast<QWidget*>(pActiveWidget) ||
                                 pActiveWidget->isAncestorOf(pFocusWidget)))
            {
                pFocusWidget->clearFocus();
            }
        }
        Q_ASSERT(pObject);
        Q_ASSERT(m_widgetSet.contains(pObject));                
        m_pActiveWidget = pObject;
        if (m_pActiveWidget)
        {
            SBWidget* pActiveWidget = pWidget;
            pActiveWidget->raise();
            pActiveWidget->overrideWindowState(pActiveWidget->windowState() |
                                               (Qt::WindowActive));
            Raise(pActiveWidget);
			if (pWidget->windowFlags().testFlag(Qt::Window))
			{
				MovePanelsTo(pWidget);
			}
        }
        emit m_pHost->WidgetActivated(pWidget);
    }
}

//------------------------------------------------------------------------------
/**
 * @brief Activates next managed widget.
 */
void SBMDIManager::Private::ActivateNext()
{
    if (!m_widgets.isEmpty())
    {
        SBWidget* pWindow = qobject_cast<SBWidget*>(m_widgets.last());
        Q_ASSERT(pWindow);
        Activate(pWindow);
    }
}

//------------------------------------------------------------------------------
/**
 * @brief Activates previous managed widget.
 */
void SBMDIManager::Private::ActivatePrev()
{
    if (m_widgets.size() > 1)
    {
        SBWidget* pWindow = qobject_cast<SBWidget*>(m_widgets[1]);
        Q_ASSERT(pWindow);
        Activate(pWindow);
        pWindow = qobject_cast<SBWidget*>(m_widgets[1]);
        Q_ASSERT(pWindow);
        Lower(pWindow);
    }
}

//------------------------------------------------------------------------------
/**
 * @brief Adds a managed widget.
 * @param pWidget - a pointer to the widget.
 */
void SBMDIManager::Private::Add(SBWidget* pWidget)
{
    Q_ASSERT(pWidget);
    QObject* pObject = qobject_cast<QObject*>(pWidget);
    if (!m_widgetSet.contains(pObject))
    {
        m_widgets.push_back(pObject);
        m_widgetSet.insert(pObject);
        pObject->installEventFilter(m_pHost);
        Activate(pWidget);
        connect(pObject, SIGNAL(destroyed(QObject*)),
                m_pHost, SLOT(OnDestroyed(QObject*)));
    }
}

//------------------------------------------------------------------------------
/**
 * @brief Adds a panel under control.
 * @param pWidget - a pointer to the panel.
 */
void SBMDIManager::Private::Add(SBPanel* pWidget)
{
    Q_ASSERT(pWidget);
    QObject* pObject = qobject_cast<QObject*>(pWidget);
    if (!m_panelSet.contains(pObject))
    {
        m_panelSet.insert(pObject);
        connect(pObject, SIGNAL(destroyed(QObject*)),
                m_pHost, SLOT(OnPanelDestroyed(QObject*)));
        if (m_pActiveWidget)
        {
            Q_ASSERT(qobject_cast<SBWidget*>(m_pActiveWidget));
            MovePanelToWidget(pWidget, qobject_cast<SBWidget*>(m_pActiveWidget));
        }
    }
}

//------------------------------------------------------------------------------
/**
 * @brief Removes a managed widget.
 * @param pWidget - a pointer to the widget.
 * The managed widget removes from MDI manager control but not delete the widget.
 */
void SBMDIManager::Private::Remove(SBWidget* pWidget)
{
    Q_ASSERT(pWidget);
    QObject* pObject = qobject_cast<QObject*>(pWidget);
    if (m_pActiveWidget == pObject)
    {
        m_pActiveWidget = nullptr;
    }
    m_widgets.removeOne(pObject);
    m_widgetSet.remove(pObject);
    pObject->removeEventFilter(m_pHost);
    disconnect(pObject, SIGNAL(destroyed(QObject*)),
               m_pHost, SLOT(OnDestroyed(QObject*)));
    ActivateNext();
}

//------------------------------------------------------------------------------
/**
 * @brief Removes a panel from control.
 * @param pWidget - a pointer to the panel.
 * This call removes parent widget of the panel but keeps window flags.
 */
void SBMDIManager::Private::Remove(SBPanel* pWidget)
{
    Q_ASSERT(pWidget);
    QObject* pObject = qobject_cast<QObject*>(pWidget);
    Q_ASSERT(m_panelSet.contains(pObject));
    m_panelSet.remove(pObject);
    disconnect(pObject, SIGNAL(destroyed(QObject*)),
               m_pHost, SLOT(OnPanelDestroyed(QObject*)));
    Qt::WindowFlags f = pWidget->windowFlags();
    pWidget->setParent(nullptr, f);
}

//------------------------------------------------------------------------------
/**
 * @brief Calls when a managed widget has destroyed.
 * @param pObject - a pointer to the managed widget.
 */
void SBMDIManager::Private::Destroyed(QObject* pObject)
{
    Q_ASSERT(m_widgetSet.contains(pObject));
    m_widgets.removeOne(pObject);
    m_widgetSet.remove(pObject);
    if (m_pActiveWidget == pObject)
    {
        m_pActiveWidget = nullptr;
    }
    ActivateNext();
}

//------------------------------------------------------------------------------
/**
 * @brief Calls when a managed panel has destroyed.
 * @param pObject - a pointer to the managed panel.
 */
void SBMDIManager::Private::PanelDestroyed(QObject* pObject)
{
    Q_ASSERT(m_panelSet.contains(pObject));
    m_panelSet.remove(pObject);
}

//------------------------------------------------------------------------------
/**
 * @brief Filters events of managed objects.
 * @param pObject - a pointer to a watched object.
 * @param pEvent - an object event.
 * @return True if the event handled successfully on this level.
 */
bool SBMDIManager::Private::eventFilter(QObject* pObject, QEvent* pEvent)
{
    if (m_widgetSet.contains(pObject))
    {
        SBWidget* pWidget = qobject_cast<SBWidget*>(pObject);
        Q_ASSERT(pWidget);
        switch (pEvent->type())
        {
            case QEvent::WindowStateChange:
            {
                QWindowStateChangeEvent* pSC =
                        static_cast<QWindowStateChangeEvent*>(pEvent);
                if (!pSC->oldState().testFlag(Qt::WindowActive) &&
                    pWidget->windowState().testFlag(Qt::WindowActive))
                {
                    if (pObject != m_pActiveWidget)
                    {
                        Activate(pWidget);
                    }
                    else
                    {
                        pWidget->overrideWindowState(pWidget->windowState() &
                                                     (~Qt::WindowActive));
                    }
                }
            }
                break;
            case QEvent::ActivationChange:
            {
                if (pWidget->isActiveWindow())
                {
                    if (pObject != m_pActiveWidget)
                    {                        
                        Activate(pWidget);
                    }
                    else
                    {
                        pWidget->overrideWindowState(pWidget->windowState() |
                                                     (Qt::WindowActive));
                    }
                }
                else
                {
                    pWidget->overrideWindowState(pWidget->windowState() &
                                                 (~Qt::WindowActive));
                }
            }
                break;
            case QEvent::Close:
                Remove(pWidget);
                break;
            default:
                break;

        }
    }
    else
    {
        SBApplication* pApp = qobject_cast<SBApplication*>(pObject);
        if (pApp)
        {
            switch (pEvent->type())
            {
                case QEvent::ApplicationActivate:
                    break;
                case QEvent::ApplicationDeactivate:
                    break;
                default:
                    break;
            }
        }
    }
    return false;
}

//------------------------------------------------------------------------------
/**
 * @brief Raises a widget.
 * @param pWidget - the target widget.
 */
void SBMDIManager::Private::Raise(SBWidget* pWidget)
{
    QObject* pObject = qobject_cast<QObject*>(pWidget);
    Q_ASSERT(pObject);
    Q_ASSERT(m_widgets.contains(pObject));
    m_widgets.removeOne(pObject);
    m_widgets.push_front(pObject);
}

//------------------------------------------------------------------------------
/**
 * @brief Lowers a widget.
 * @param pWidget - the target widget.
 */
void SBMDIManager::Private::Lower(SBWidget* pWidget)
{
    QObject* pObject = qobject_cast<QObject*>(pWidget);
    Q_ASSERT(pObject);
    Q_ASSERT(m_widgets.contains(pObject));
    m_widgets.removeOne(pObject);
    m_widgets.push_back(pObject);
}

//------------------------------------------------------------------------------
bool SBMDIManager::Private::HasVisibleTopLevel() const
{
    return static_cast<bool>(std::count_if(m_widgetSet.begin(), m_widgetSet.end(),
                                           [](QObject* pObject)
    {
        QWidget* pWidget = qobject_cast<SBWidget*>(pObject);
        Q_ASSERT(pWidget);
        if (pWidget->windowFlags().testFlag(Qt::Window))
        {
            return static_cast<int>(pWidget->isVisible());
        }
        return 0;
    }));
}

//------------------------------------------------------------------------------
/**
 * @brief Move all floating panels to a widget.
 * @param pWidget - a pointer to a widget.
 */
void SBMDIManager::Private::MovePanelsTo(SBWidget* pWidget)
{
    Q_ASSERT(pWidget);
    Q_ASSERT(m_widgets.contains(qobject_cast<QObject*>(pWidget)));
    // go through all panels
    QSet<QObject*>::iterator pos = m_panelSet.begin();
    QSet<QObject*>::iterator end = m_panelSet.end();
    for (; pos != end; ++pos)
    {
        SBPanel* pPanel = qobject_cast<SBPanel*>(*pos);
        Q_ASSERT(pPanel);
        MovePanelToWidget(pPanel, pWidget);
    }
}

//------------------------------------------------------------------------------
/**
 * @brief Moves a panel to a target widget.
 * @param pPanel - a pointer to the source panel.
 * @param pWidget - a pointer to the target widget.
 */
void SBMDIManager::Private::MovePanelToWidget(SBPanel* pPanel, SBWidget* pWidget)
{
    if (pPanel->IsFloating())
    {
        bool visibility = pPanel->isVisible();
        Qt::WindowFlags f = pPanel->windowFlags();
        pPanel->setParent(pWidget, f);
        if (visibility)
        {
            pPanel->show();
        }
    }
}
//------------------------------------------------------------------------------
