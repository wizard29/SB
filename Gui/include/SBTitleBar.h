//==============================================================================
// Copyright: Reksoft Ltd.
//==============================================================================
//
// Author:              $Author:$
// Creation date:       2015.03.07
// Modification date:   $Date:$
// Module:              Gui
// Platform:            MS Windows 7, Linux, MAC OS X 10.6.x
//
//------------------------------------------------------------------------------
// Note:
//------------------------------------------------------------------------------
// Warning:
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
#ifndef SBTITLEBAR_H
#define SBTITLEBAR_H


#include <guidef.h>
#include <qwidget.h>


class QToolButton;


class GUI_DEF SBTitleBar
        : public QWidget
{
    Q_OBJECT
    public:

        SBTitleBar(QWidget* pParent = NULL);
        ~SBTitleBar();

        void SetTitle(const QString& text);
        void SetIcon(const QIcon& icon);
        void ReplaceBackground(QWidget* pWidget);
        QToolButton* AddButton(const QIcon&, Qt::Alignment align = Qt::AlignLeft,
                               const QString& toolTip = QString());
        QToolButton* AddButton(Qt::Alignment align = Qt::AlignLeft,
                               const QString& toolTip = QString());
        void AddWidget(QWidget* pWidget, Qt::Alignment align = Qt::AlignLeft);
        void SetContentsMargins(int, int, int, int);

    signals:

        /**
         * @brief Emits when user double clicked on the title bar.
         */
        void DoubleClicked(Qt::MouseButton);

    protected:

        void mouseDoubleClickEvent(QMouseEvent*);

    private:

        struct Private;
        /// A pointer to the private implementation.
        Private* m_pPrivate;
};//class SBTitleBar;
#endif // SBTITLEBAR_H
