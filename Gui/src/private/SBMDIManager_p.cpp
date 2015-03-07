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
{
    Q_ASSERT(m_pHost);
}

//------------------------------------------------------------------------------
/**
 * @brief Destructor.
 */
SBMDIManager::Private::~Private()
{
}
//------------------------------------------------------------------------------
