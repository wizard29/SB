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
#include <SBWidget.h>
#include <SBPanel.h>


//------------------------------------------------------------------------------
/**
 * @class SBMDIManager
 * @ingroup Gui
 * @brief The SBMDIManager class provides a windows management system for
 * the application above the OS window management system.
 */
//------------------------------------------------------------------------------
/**
 * @brief Constructor.
 * @param pParent - a pointer to a parent object.
 */
SBMDIManager::SBMDIManager(QObject* pParent)
    : QObject(pParent)
    , m_pPrivate(nullptr)
{
    m_pPrivate = new Private(this);
}

//------------------------------------------------------------------------------
/**
 * @brief Destructor.
 */
SBMDIManager::~SBMDIManager()
{
    Q_ASSERT(m_pPrivate);
    delete m_pPrivate;
}

//------------------------------------------------------------------------------
/**
 * @brief Creates an MDI area widget.
 * @return A pointer to an MDI area widget.
 */
QWidget* SBMDIManager::CreateMDIArea()
{
    return nullptr;
}

//------------------------------------------------------------------------------
/**
 * @brief Adds a widget under the MDI manager control.
 * @param pWidget - a pointer to a widget.
 */
void SBMDIManager::Add(SBWidget* pWidget)
{
    Q_ASSERT(m_pPrivate);
    m_pPrivate->Add(pWidget);
}

//------------------------------------------------------------------------------
/**
 * @brief Adds a panel widget under MDI manager control.
 * @param pWidget - a pointer to a panel widget.
 */
void SBMDIManager::Add(SBPanel* pWidget)
{
    Q_ASSERT(m_pPrivate);
    m_pPrivate->Add(pWidget);
}

//------------------------------------------------------------------------------
/**
 * @brief Removes a widget from the MDI manager control.
 * @param pWidget - a pointer to a widget.
 */
void SBMDIManager::Remove(SBWidget* pWidget)
{
    Q_ASSERT(m_pPrivate);
    m_pPrivate->Remove(pWidget);
}

//------------------------------------------------------------------------------
/**
 * @brief Removes a panel from the MDI manager control.
 * @param pWidget - a pointer to a panel widget.
 */
void SBMDIManager::Remove(SBPanel* pWidget)
{
    Q_ASSERT(m_pPrivate);
    m_pPrivate->Remove(pWidget);
}

//------------------------------------------------------------------------------
/**
 * @brief Returns a list of managed widgets.
 */
QList<SBWidget*> SBMDIManager::Widgets()
{
    Q_ASSERT(m_pPrivate);
    QList<SBWidget*> result;
    auto cast = [](QObject* pObject)->SBWidget*
    {
        return qobject_cast<SBWidget*>(pObject);
    };
    std::transform(m_pPrivate->m_widgets.begin(),
                   m_pPrivate->m_widgets.end(), std::back_inserter(result), cast);
    return result;
}

//------------------------------------------------------------------------------
/**
 * @brief Activates a controlled widget.
 * @param pWidget - a pointer to a widget.
 */
void SBMDIManager::Activate(SBWidget* pWidget)
{
    Q_ASSERT(m_pPrivate);
    m_pPrivate->Activate(pWidget);
}

//------------------------------------------------------------------------------
/**
 * @brief Activates next order widget.
 */
void SBMDIManager::ActivateNext()
{
    Q_ASSERT(m_pPrivate);
    m_pPrivate->ActivateNext();
}

//------------------------------------------------------------------------------
/**
 * @brief Activates previous order widget.
 */
void SBMDIManager::ActivatePrev()
{
    Q_ASSERT(m_pPrivate);
    m_pPrivate->ActivatePrev();
}

//------------------------------------------------------------------------------
/**
 * @brief Reimplemented method.
 * @see The QObject::eventFilter for more details.
 */
bool SBMDIManager::eventFilter(QObject* pObject, QEvent* pEvent)
{
    Q_ASSERT(m_pPrivate);
    return m_pPrivate->eventFilter(pObject, pEvent);
}

//------------------------------------------------------------------------------
/**
 * @brief Calls when a managed widget has destroyed.
 * @param pObject - a pointer to the managed widget.
 */
void SBMDIManager::OnDestroyed(QObject* pObject)
{
    Q_ASSERT(m_pPrivate);
    m_pPrivate->Destroyed(pObject);
}

//------------------------------------------------------------------------------
/**
 * @brief Calls when a managed panel has destroyed.
 * @param pObject - a pointer to the managed panel.
 */
void SBMDIManager::OnPanelDestroyed(QObject* pObject)
{
    Q_ASSERT(m_pPrivate);
    m_pPrivate->PanelDestroyed(pObject);
}
//------------------------------------------------------------------------------
