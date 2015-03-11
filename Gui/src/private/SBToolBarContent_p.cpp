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
 * @struct SBToolBarContent::Private
 * @ingroup Gui
 * @brief The SBToolBarContent::Private struct contains the internal title bar data
 * and provides the accessory functionality.
 */
//------------------------------------------------------------------------------
/**
 * @brief Constructor.
 * @param pHost - a pointer to the host widget.
 */
SBToolBarContent::Private::Private(SBToolBarContent* pHost)
    : m_pHost(pHost)
{
    Q_ASSERT(m_pHost);
}

//------------------------------------------------------------------------------
/**
 * @brief Destructor.
 */
SBToolBarContent::Private::~Private()
{
}
//------------------------------------------------------------------------------


