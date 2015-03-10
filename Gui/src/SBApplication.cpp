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
#include <qfileinfo.h>
#include <qsettings.h>
#include <qprocess.h>


//------------------------------------------------------------------------------
/**
 * @class SBApplication
 * @ingroup Gui
 * @brief The SBApplication class is the QApplication superstructure and
 * provides transparent application data manipulation.
 */
//------------------------------------------------------------------------------
/**
 * @brief Constructor.
 * @param argc - an application argument number.
 * @param argv - an application argument list.
 */
SBApplication::SBApplication(int& argc, char** argv)
    : QApplication(argc, argv)
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
SBApplication::~SBApplication()
{
    Q_ASSERT(m_pPrivate);
    delete m_pPrivate;
}

//------------------------------------------------------------------------------
/**
 * @brief Returns a pointer to the application instance.
 */
SBApplication* SBApplication::GetInstance()
{
    return qobject_cast<SBApplication*>(qApp);
}

//------------------------------------------------------------------------------
/**
 * @brief Loads an application theme.
 */
void SBApplication::LoadTheme()
{
    QDir::addSearchPath(QString::fromLatin1("theme"),
                        GetUserValue(QString::fromLatin1("theme"),
                                     QString::fromLatin1(":/Dark")).toString());
    // load style sheet
    QFile file("theme:style.qss");
    if (file.open(QFile::ReadOnly))
    {
        QString styleSheet = QLatin1String(file.readAll());
        sbApp->setStyleSheet(styleSheet);
    }
}

//------------------------------------------------------------------------------
/**
 * @brief Sets application data folder.
 * @param absolutePath - an application data folder.
 */
void SBApplication::SetDataFolder(const QString& absolutePath)
{
    if (absolutePath != GetDataFolder())
    {
        SBApplication* pInstance = sbApp;
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
QString SBApplication::GetDataFolder()
{
    SBApplication* pInstance = sbApp;
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
void SBApplication::SetUserDataFolder(const QString& absolutePath)
{
    if (absolutePath != GetUserDataFolder())
    {
        SBApplication* pInstance = sbApp;
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
QString SBApplication::GetUserDataFolder()
{
    SBApplication* pInstance = sbApp;
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
void SBApplication::SetAppicationValue(const QString& key,
                                           const QVariant& value)
{
    SBApplication* pInstance = sbApp;
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
QVariant SBApplication::GetApplicationValue(const QString& key,
                                                const QVariant& defaultValue)
{
    SBApplication* pInstance = sbApp;
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
void SBApplication::SetUserValue(const QString& key, const QVariant& value)
{
    SBApplication* pInstance = sbApp;
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
QVariant SBApplication::GetUserValue(const QString& key,
                                         const QVariant& defaultValue)
{
    SBApplication* pInstance = sbApp;
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
