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
#include "SBApplication_p.h"
#include <qdir.h>


//------------------------------------------------------------------------------
/**
 * @struct SBApplication::Private
 * @ingroup Gui
 * @brief The SBApplication::Private struct contains internal object data
 * and provides accessory functionality.
 */
//------------------------------------------------------------------------------
/**
 * @brief Constructor.
 * @param pHost - a pointer to a host object. Must not be the nullptr.
 */
SBApplication::Private::Private(SBApplication* pHost)
    : m_pHost(pHost)
{
    Q_ASSERT(pHost);    
}

//------------------------------------------------------------------------------
/**
 * @brief Destructor.
 */
SBApplication::Private::~Private()
{
}

//------------------------------------------------------------------------------
/**
 * @brief Creates a folder structure by a given path.
 * @param path - a path.
 */
bool SBApplication::Private::MakeFolderStructure(const QString& path)
{
    QDir dir(path);
    if (!dir.exists())
    {
        return dir.mkpath(QString("./"));
    }
    return true;
}
//------------------------------------------------------------------------------
