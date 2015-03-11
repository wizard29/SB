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
#ifndef SBTOOLBARCONTENT_P_H
#define SBTOOLBARCONTENT_P_H


#include "SBToolBarContent.h"


struct SBToolBarContent::Private
{
    public:

        Private(SBToolBarContent* pHost);
        ~Private();

    public:

        /// A pointer to the host widget.
        SBToolBarContent* m_pHost;
};//struct SBToolBarContent::private
#endif // SBTOOLBARCONTENT_P_H

