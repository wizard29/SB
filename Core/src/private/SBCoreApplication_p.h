//==============================================================================
// Copyright: Reksoft Ltd.
//==============================================================================
//
// Author:              $Author:$
// Creation date:       2015.03.04
// Modification date:   $Date$
// Module:              Core
// Platform:            MS Windows 7, Linux, MAC OS X 10.6.x
//
//------------------------------------------------------------------------------
// Note:
//------------------------------------------------------------------------------
// Warning:
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
#ifndef SBCOREAPPLICATION_P_H
#define SBCOREAPPLICATION_P_H


#include "SBCoreApplication.h"


struct SBCoreApplication::Private
{
    public:

        Private(SBCoreApplication*);
        ~Private();
        static bool MakeFolderStructure(const QString& path);

    public:

        /// A pointer to a host object.
        SBCoreApplication* m_pHost;
        /// The application settings file name.
        QString m_appDataFileName;
        /// The user settings file name.
        QString m_userDataFileName;
};//struct SBCoreApplication::Private
#endif // SBCOREAPPLICATION_P_H

