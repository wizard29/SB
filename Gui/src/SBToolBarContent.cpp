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
#include "SBToolBarContent_p.h"


//------------------------------------------------------------------------------
/**
 * @class SBToolBarContent
 * @ingroup Gui
 * @brief The SBToolBarContent class provides a manipulating of toolbar contents
 * data.
 */
//------------------------------------------------------------------------------
/**
 * @brief Constructor.
 * @param pParent - a pointer to the host widget.
 * @param f - window flags.
 */
SBToolBarContent::SBToolBarContent(QWidget* pParent, Qt::WindowFlags f)
    : QWidget(pParent, f)
    , m_pPrivate(nullptr)
{
    m_pPrivate = new Private(this);
}

//------------------------------------------------------------------------------
/**
 * @brief SBToolBarContent::~SBToolBarContent
 */
SBToolBarContent::~SBToolBarContent()
{
    Q_ASSERT(m_pPrivate);
    delete m_pPrivate;
}

//------------------------------------------------------------------------------
