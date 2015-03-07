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
#ifndef SBMDIMANAGER_P_H
#define SBMDIMANAGER_P_H


#include "SBMDIManager.h"


struct SBMDIManager::Private
{
    public:

        Private(SBMDIManager* pHost);
        ~Private();

    public:

        /// A pointer to a host object.
        SBMDIManager* m_pHost;
};//struct SBMDIManager::Private
#endif // SBMDIMANAGER_P_H

