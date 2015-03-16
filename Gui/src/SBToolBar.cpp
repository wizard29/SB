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


//------------------------------------------------------------------------------
/**
 * @class SBToolBar
 * @ingroup Gui
 * @brief The SBToolBar provides a movable panel that contains a set of controls.
 */
//------------------------------------------------------------------------------
/**
 * @brief Constructor.
 * @param pParent - a pointer to the parent widget.
 */
SBToolBar::SBToolBar(QWidget* pParent)
    : SBPanel(pParent, SBWidget::LeftTitleBar)
    , m_pPrivate(nullptr)
{
    m_pPrivate = new Private(this);
}

//------------------------------------------------------------------------------
/**
 * @brief Destructor.
 */
SBToolBar::~SBToolBar()
{
    Q_ASSERT(m_pPrivate);
    delete m_pPrivate;
}

//------------------------------------------------------------------------------
/**
 * @brief Returns a pointer to the managed content part.
 */
QWidget* SBToolBar::GetManagetContent()
{
    Q_ASSERT(m_pPrivate);
    Q_ASSERT(m_pPrivate->m_pContent);
    return m_pPrivate->m_pContent->GetContent();
}

//------------------------------------------------------------------------------
/**
 * @brief Fits toolbar to the best size.
 */
void SBToolBar::FitToBestSize()
{
    Q_ASSERT(m_pPrivate);
    m_pPrivate->FitToBestSize();
}
//------------------------------------------------------------------------------
