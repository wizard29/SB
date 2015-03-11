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
#include "SBToolBar_p.h"
#include "SBToolBarContent.h"
#include <SBTitleBar.h>
#include <qtoolbutton.h>


//------------------------------------------------------------------------------
/**
 * @struct SBToolBar::Private
 * @ingroup Gui
 * @brief The SBToolBar::Private struct contains the internal title bar data
 * and provides the accessory functionality.
 */
//------------------------------------------------------------------------------
/**
 * @brief Constructor.
 * @param pHost - a pointer to a host object. Must not be a null pointer.
 */
SBToolBar::Private::Private(SBToolBar* pHost)
    : m_pHost(pHost)
{
    QToolButton* pCloseBtn = m_pHost->CloseButton();
    if (pCloseBtn)
    {
        pCloseBtn->hide();
    }
    SBTitleBar* pTitle = m_pHost->TitleBar();
    if (pTitle)
    {
        pTitle->SetTitleVisible(false);
        pTitle->SetIconVisible(false);
    }
    m_pHost->IgnoreResize(true);
    m_pHost->ReplaceContent(new SBToolBarContent(m_pHost));
    m_pHost->resize(m_pHost->sizeHint());
}

//------------------------------------------------------------------------------
/**
 * @brief Destructor.
 */
SBToolBar::Private::~Private()
{    
}

//------------------------------------------------------------------------------
void SBToolBar::Private::Add(QWidget* pWidget)
{
    Q_UNUSED(pWidget);
}
//------------------------------------------------------------------------------
