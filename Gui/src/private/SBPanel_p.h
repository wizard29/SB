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
#ifndef SBPANEL_P_H
#define SBPANEL_P_H


#include "SBPanel.h"


struct SBPanel::Private
{
    public:

        Private(SBPanel* pHost);
        ~Private();

        void SetFloating(bool state);

    public:

        /// A pointer to the host object.
        SBPanel* m_pHost;
        /// The floating state.
        bool m_floating;
};//struct SBPanel::Private
#endif // SBPANEL_P_H

