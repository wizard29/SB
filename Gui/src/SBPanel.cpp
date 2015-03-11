//==============================================================================
// Copyright: Reksoft Ltd.
//==============================================================================
//
// Author:              $Author:$
// Creation date:       2015.03.10
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
#include "SBPanel_p.h"
#include <qevent.h>


//------------------------------------------------------------------------------
/**
 * @class SBPanel
 * @ingroup Gui
 * @brief The SBPanel class provides a widget that can be docked inside an another
 * widget or floated as a top-level window on the desktop.
 */
//------------------------------------------------------------------------------
/**
 * @brief Constructor.
 * @param pParent - a pointer to a parent widget.
 * @param titlePos - a titlebar position.
 */
SBPanel::SBPanel(QWidget* pParent, SBWidget::TitlePosition titlePos)
    : SBWidget(pParent, Qt::Tool, titlePos)
    , m_pPrivate(nullptr)
{
    m_pPrivate = new Private(this);
}

//------------------------------------------------------------------------------
/**
 * @brief Destructor.
 */
SBPanel::~SBPanel()
{
    Q_ASSERT(m_pPrivate);
    delete m_pPrivate;
}

//------------------------------------------------------------------------------
/**
 * @brief Returns a floating state.
 */
bool SBPanel::IsFloating() const
{
    Q_ASSERT(m_pPrivate);
    return m_pPrivate->m_floating;
}

//------------------------------------------------------------------------------
/**
 * @brief Sets floating state.
 * @param state - a floating state.
 */
void SBPanel::SetFloating(bool state)
{
    Q_ASSERT(m_pPrivate);
    m_pPrivate->SetFloating(state);
}

//------------------------------------------------------------------------------
/**
 * @brief Reimplemented method.
 * Skips close event and calls widget hide.
 */
void SBPanel::closeEvent(QCloseEvent* pEvent)
{
    pEvent->ignore();
    hide();
}
//------------------------------------------------------------------------------
