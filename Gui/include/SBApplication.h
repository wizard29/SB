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
#ifndef SBAPPLICATION_H
#define SBAPPLICATION_H


#include <guidef.h>
#include <qapplication.h>
#include <qvariant.h>


#ifdef sbApp
    #undef sbApp
#endif
#define sbApp SBApplication::GetInstance()


class GUI_DEF SBApplication
        : public QApplication
{
    Q_OBJECT
    public:

        SBApplication(int& argc, char** argv);
        ~SBApplication();

    public:

        static SBApplication* GetInstance();
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
};//class SBApplication
#endif // SBAPPLICATION_H

