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
}
//------------------------------------------------------------------------------
