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


class SBWidget;
class SBPanel;


class GUI_DEF SBMDIManager
        : public QObject
{
    Q_OBJECT
    public:

        SBMDIManager(QObject* pParent = nullptr);
        ~SBMDIManager();

        QWidget* CreateMDIArea();
        void Add(SBWidget* pWidget);
        void Add(SBPanel* pWidget);
        void Remove(SBWidget* pWidget);
        void Remove(SBPanel* pWidget);
        QList<SBWidget*> Widgets();

    public slots:

        void Activate(SBWidget* pWidget);
        void ActivateNext();
        void ActivatePrev();

    signals:

        /**
         * @brief Emits when a managed widget has activated.
         * @param pWidget - a pointer to the managed widget.
         */
        void WidgetActivated(SBWidget* pWidget);

    protected:

        bool eventFilter(QObject*, QEvent*);

    private slots:

        void OnDestroyed(QObject* pWidget);
        void OnPanelDestroyed(QObject* pWidget);

    private:

        struct Private;
        /// A pointer to a private implementation.
        Private* m_pPrivate;
};//class SBMDIManager
#endif // SBMDIMANAGER_H

