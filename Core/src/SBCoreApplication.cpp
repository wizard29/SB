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
#include <qfileinfo.h>
#include <qsettings.h>
#include <qprocess.h>


//------------------------------------------------------------------------------
/**
 * @class SBCoreApplication
 * @ingroup Core
 * @brief The SBCoreApplication class is the QCoreApplication superstructure and
 * provides transparent application data manipulation.
 */
//------------------------------------------------------------------------------
/**
 * @brief Constructor.
 * @param argc - an application argument number.
 * @param argv - an application argument list.
 */
SBCoreApplication::SBCoreApplication(int& argc, char** argv)
    : QCoreApplication(argc, argv)
    , m_pPrivate(nullptr)
{
    m_pPrivate = new Private(this);
    // initialize user and app data folders
    QString appDataPath;
    QString userDataPath;
#ifdef Q_OS_WIN
    QProcessEnvironment pe(QProcessEnvironment::systemEnvironment());
    QString str = pe.value(QString("LOCALAPPDATA"));
    if (str.isNull() || str.isEmpty())
    {
        str = QDir::homePath();
        str += QDir::toNativeSeparators(QString("/AppData/Local/SmartBatch"));
    }
    else
    {
        str += QDir::toNativeSeparators(QString("/SmartBatch"));
    }
    appDataPath = str;
    userDataPath = QDir::homePath() +
            QDir::toNativeSeparators(QString("/AppData/Local/SmartBatch"));
#endif
    SetDataFolder(appDataPath);
    SetDataFolder(userDataPath);
}

//------------------------------------------------------------------------------
/**
 * @brief Destructor.
 */
SBCoreApplication::~SBCoreApplication()
{
    Q_ASSERT(m_pPrivate);
    delete m_pPrivate;
}

//------------------------------------------------------------------------------
/**
 * @brief Returns a pointer to the application instance.
 */
SBCoreApplication* SBCoreApplication::GetInstance()
{
    return qobject_cast<SBCoreApplication*>(qApp);
}

//------------------------------------------------------------------------------
/**
 * @brief Sets application data folder.
 * @param absolutePath - an application data folder.
 */
void SBCoreApplication::SetDataFolder(const QString& absolutePath)
{
    if (absolutePath != GetDataFolder())
    {
        SBCoreApplication* pInstance = sbApp;
        if (pInstance)
        {
            Q_ASSERT(pInstance->m_pPrivate);
            pInstance->m_pPrivate->m_appDataFileName =
                    QDir::toNativeSeparators(absolutePath + QDir::separator() +
                                             QString::fromLatin1("app.ini"));
            Private::MakeFolderStructure(absolutePath);
        }
    }
}

//------------------------------------------------------------------------------
/**
 * @brief Returns application data folder.
 */
QString SBCoreApplication::GetDataFolder()
{
    SBCoreApplication* pInstance = sbApp;
    if (pInstance)
    {
        Q_ASSERT(pInstance->m_pPrivate);
        QFileInfo fi(pInstance->m_pPrivate->m_appDataFileName);
        return fi.absoluteFilePath();
    }
    return QString();
}

//------------------------------------------------------------------------------
/**
 * @brief Sets application user data folder.
 * @param absolutePath - an application user data folder.
 */
void SBCoreApplication::SetUserDataFolder(const QString& absolutePath)
{
    if (absolutePath != GetUserDataFolder())
    {
        SBCoreApplication* pInstance = sbApp;
        if (pInstance)
        {
            Q_ASSERT(pInstance->m_pPrivate);
            pInstance->m_pPrivate->m_userDataFileName =
                    QDir::toNativeSeparators(absolutePath + QDir::separator() +
                                             QString::fromLatin1("user.ini"));
            Private::MakeFolderStructure(absolutePath);
        }
    }
}

//------------------------------------------------------------------------------
/**
 * @brief Returns application user data folder.
 */
QString SBCoreApplication::GetUserDataFolder()
{
    SBCoreApplication* pInstance = sbApp;
    if (pInstance)
    {
        Q_ASSERT(pInstance->m_pPrivate);
        QFileInfo fi(pInstance->m_pPrivate->m_userDataFileName);
        return fi.absoluteFilePath();
    }
    return QString();
}

//------------------------------------------------------------------------------
/**
 * @brief Writes the application value of \i key. If the \i key already exists,
 * the previous value will be overwritten.
 * @param key - settings key.
 * @param value - new value of \i key.
 */
void SBCoreApplication::SetAppicationValue(const QString& key,
                                           const QVariant& value)
{
    SBCoreApplication* pInstance = sbApp;
    if (pInstance)
    {
        Q_ASSERT(pInstance->m_pPrivate);
        QSettings settings(pInstance->m_pPrivate->m_appDataFileName,
                           QSettings::IniFormat);
        settings.setValue(key, value);
    }
}

//------------------------------------------------------------------------------
/**
 * @brief Reads value of the application for \i key. If the \i key doesn't exist,
 * returns \i defaultValue.
 * @param key - settings key.
 * @param defaultValue - default value.
 */
QVariant SBCoreApplication::GetApplicationValue(const QString& key,
                                                const QVariant& defaultValue)
{
    SBCoreApplication* pInstance = sbApp;
    if (pInstance)
    {
        Q_ASSERT(pInstance->m_pPrivate);
        QSettings settings(pInstance->m_pPrivate->m_appDataFileName,
                           QSettings::IniFormat);
        return settings.value(key, defaultValue);
    }
    return defaultValue;
}

//------------------------------------------------------------------------------
/**
 * @brief Writes the user value of \i key. If the \i key already exists,
 * the previous value will be overwritten.
 * @param key - settings key.
 * @param value - new value of \i key.
 */
void SBCoreApplication::SetUserValue(const QString& key, const QVariant& value)
{
    SBCoreApplication* pInstance = sbApp;
    if (pInstance)
    {
        Q_ASSERT(pInstance->m_pPrivate);
        QSettings settings(pInstance->m_pPrivate->m_userDataFileName,
                           QSettings::IniFormat);
        settings.setValue(key, value);
    }
}

//------------------------------------------------------------------------------
/**
 * @brief Reads value of the application for \i key. If the \i key doesn't exist,
 * returns \i defaultValue.
 * @param key - settings key.
 * @param defaultValue - default value.
 */
QVariant SBCoreApplication::GetUserValue(const QString& key,
                                         const QVariant& defaultValue)
{
    SBCoreApplication* pInstance = sbApp;
    if (pInstance)
    {
        Q_ASSERT(pInstance->m_pPrivate);
        QSettings settings(pInstance->m_pPrivate->m_userDataFileName,
                           QSettings::IniFormat);
        return settings.value(key, defaultValue);
    }
    return defaultValue;
}
//------------------------------------------------------------------------------
