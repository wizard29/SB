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
#include "SBCoreApplication_p.h"
#include <qdir.h>


//------------------------------------------------------------------------------
/**
 * @struct SBCoreApplication::Private
 * @ingroup Core
 * @brief The SBCoreApplication::Private struct contains internal object data
 * and provides accessory functionality.
 */
//------------------------------------------------------------------------------
/**
 * @brief Constructor.
 * @param pHost - a pointer to a host object. Must not be the nullptr.
 */
SBCoreApplication::Private::Private(SBCoreApplication* pHost)
    : m_pHost(pHost)
{
    Q_ASSERT(pHost);
}

//------------------------------------------------------------------------------
/**
 * @brief Destructor.
 */
SBCoreApplication::Private::~Private()
{
}

//------------------------------------------------------------------------------
/**
 * @brief Creates a folder structure by a given path.
 * @param path - a path.
 */
bool SBCoreApplication::Private::MakeFolderStructure(const QString& path)
{
    QDir dir(path);
    if (!dir.exists())
    {
        return dir.mkpath(QString("./"));
    }
    return true;
}
//------------------------------------------------------------------------------
