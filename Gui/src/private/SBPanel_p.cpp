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
#include <qtoolbutton.h>


//------------------------------------------------------------------------------
/**
 * @struct SBPanel::Private
 * @ingroup Gui
 * @brief The SBPanel::Private struct contains the internal title bar data
 * and provides the accessory functionality.
 */
//------------------------------------------------------------------------------
SBPanel::Private::Private(SBPanel* pHost)
    : m_pHost(pHost)
    , m_floating(false)
{
    Q_ASSERT(pHost);
    QToolButton* pCloseBtn = m_pHost->CloseButton();
    if (pCloseBtn)
    {
        pCloseBtn->setToolTip(tr("Hide"));
    }
}

//------------------------------------------------------------------------------
/**
 * @brief Destructor.
 */
SBPanel::Private::~Private()
{
}

//------------------------------------------------------------------------------
/**
 * @brief Sets floating state of the panel.
 * @param state - a floating state.
 */
void SBPanel::Private::SetFloating(bool state)
{
    if (m_floating != state)
    {
        m_floating = state;
        if (m_floating)
        {
            m_pHost->setWindowFlags(m_pHost->windowFlags() | Qt::Window);
        }
        else
        {
            m_pHost->setWindowFlags(m_pHost->windowFlags() &
                                    (~Qt::Window));
        }
        emit m_pHost->FloatingChanged(m_floating);
    }
}
//------------------------------------------------------------------------------


