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
#include <qwidget.h>


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
void SBMDIManager::Private::Activate(QWidget* pWidget)
{
    if (m_pActiveWidget != pWidget)
    {
        Q_ASSERT(pWidget);
        Q_ASSERT(m_widgetSet.contains(pWidget));
        // rise widget to the top
        m_widgets.removeOne(pWidget);
        m_widgets.push_front(pWidget);
        pWidget->raise();
        pWidget->activateWindow();
        if (pWidget->windowFlags().testFlag(Qt::Window))
        {
            MovePanelsTo(pWidget);
            pWidget->setFocus();
        }
        m_pActiveWidget = pWidget;
        emit m_pHost->WidgetActivated(pWidget);
    }
}

//------------------------------------------------------------------------------
/**
 * @brief Activates next managed widget.
 */
void SBMDIManager::Private::ActivateNext()
{
}

//------------------------------------------------------------------------------
/**
 * @brief Activates previous managed widget.
 */
void SBMDIManager::Private::ActivatePrev()
{
}

//------------------------------------------------------------------------------
/**
 * @brief Move all floating panels to a widget.
 * @param pWidget - a pointer to a widget.
 */
void SBMDIManager::Private::MovePanelsTo(QWidget* pWidget)
{
    Q_ASSERT(pWidget);
    Q_ASSERT(m_widgets.contains(pWidget));
    // go through all panels
    int count = m_panels.size();
    for (int i = 0; i < count; ++i)
    {
        QWidget* pPanel = m_panels[i];
        Q_ASSERT(pPanel);
        if (pPanel->property("floating").toBool())
        {
            Qt::WindowFlags f = pPanel->windowFlags();
            pPanel->setParent(pWidget, f);
        }
    }
}
//------------------------------------------------------------------------------
