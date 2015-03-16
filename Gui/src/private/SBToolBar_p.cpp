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
#include "SBToolBarContent_p.h"
#include <SBTitleBar.h>
#include <qlayout.h>
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
    m_pContent = new SBToolBarContentWidget(m_pHost);
    m_pHost->ReplaceContent(m_pContent);    
}

//------------------------------------------------------------------------------
/**
 * @brief Destructor.
 */
SBToolBar::Private::~Private()
{    
}

//------------------------------------------------------------------------------
/**
 * @brief Fits toolbar to the best size.
 */
void SBToolBar::Private::FitToBestSize()
{
    if (m_pHost->windowFlags().testFlag(Qt::Window))
    {
        Q_ASSERT(m_pContent);
        QSize size = m_pContent->GetBestSize();
        SBTitleBar* pTitle = m_pHost->TitleBar();
        if (pTitle)
        {
            QSize titleBestSize = pTitle->sizeHint();
            int width = titleBestSize.width() + size.width();
            int height = qMax(titleBestSize.height(), size.height());
            m_pHost->resize(width, height);
        }
        m_pHost->resize(size.width(), size.height());
    }
}
//------------------------------------------------------------------------------
