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
#ifndef SBMDIMANAGER_H
#define SBMDIMANAGER_H


#include <guidef.h>
#include <qobject.h>


class GUI_DEF SBMDIManager
        : public QObject
{
    Q_OBJECT
    public:

        SBMDIManager(QObject* pParent = nullptr);
        ~SBMDIManager();

    private:

        struct Private;
        /// A pointer to a private implementation.
        Private* m_pPrivate;
};//class SBMDIManager
#endif // SBMDIMANAGER_H

