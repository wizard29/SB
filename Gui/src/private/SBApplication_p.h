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
#ifndef SBAPPLICATION_P_H
#define SBAPPLICATION_P_H


#include "SBApplication.h"


struct SBApplication::Private
{
    public:

        Private(SBApplication*);
        ~Private();
        static bool MakeFolderStructure(const QString& path);

    public:

        /// A pointer to a host object.
        SBApplication* m_pHost;
        /// The application settings file name.
        QString m_appDataFileName;
        /// The user settings file name.
        QString m_userDataFileName;
};//struct SBApplication::Private
#endif // SBAPPLICATION_P_H

