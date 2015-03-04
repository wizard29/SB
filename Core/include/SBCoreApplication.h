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
#ifndef SBCOREAPPLICATION_H
#define SBCOREAPPLICATION_H


#include <coredef.h>
#include <qcoreapplication.h>
#include <qvariant.h>


#define sbApp SBCoreApplication::GetInstance()

class CORE_DEF SBCoreApplication
        : public QCoreApplication
{
    Q_OBJECT
    public:

        SBCoreApplication(int& argc, char** argv);
        ~SBCoreApplication();

    public:

        static SBCoreApplication* GetInstance();
        static void SetDataFolder(const QString& absolutePath);
        static QString GetDataFolder();
        static void SetUserDataFolder(const QString& absolutePath);
        static QString GetUserDataFolder();
        static void SetAppicationValue(const QString& key, const QVariant& value);
        static QVariant GetApplicationValue(const QString& key,
                                            const QVariant& defaultValue = QVariant());
        static void SetUserValue(const QString& key, const QVariant& value);
        static QVariant GetUserValue(const QString& key,
                                     const QVariant& defaultValue = QVariant());

    private:

        struct Private;
        /// A pointer to a private implementation.
        Private* m_pPrivate;
};//class SBCoreApplication
#endif // SBCOREAPPLICATION_H

