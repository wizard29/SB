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
#ifndef SBWIDGET_H
#define SBWIDGET_H


#include <guidef.h>
#include <qwidget.h>


class SBTitleBar;
class QToolButton;


class GUI_DEF SBWidget
        : public QWidget
{
    Q_OBJECT
    Q_ENUMS(TitlePosition)
    Q_PROPERTY(TitlePosition TitlePos READ GetTitlePosition)
    public:

        enum FadeState
        {
            FadeNone = 0,
            FadeShow = 1,
            FadeNormal = 2,
            FadeHide = 3,
            FadeClose = 4
        };

        enum TitlePosition
        {
            TopTitleBar = 0,
            BottomTitleBar,
            LeftTitleBar,
            RightTitleBar
        };

    public:

        SBWidget(QWidget* pParent = nullptr, Qt::WindowFlags f = 0,
                 TitlePosition titlePos = TopTitleBar);
        ~SBWidget();

        void SetFadeTime(int msec);
        void SetIntensifyTime(int msec);
        void CancelFadeAction(bool visible);
        SBTitleBar* TitleBar();
        QWidget* Content();
        bool IsAllowToClose();
        TitlePosition GetTitlePosition();
        virtual void AddMinimizeButton();
        virtual void AddMaximizeButton();
        virtual void AddRestoreButton();        

    public slots:

        void ShowMinimized();
        void ShowNormal();
        void ShowMaximized();

    signals:

        /**
         * @brief Emits when the fade state has been changed.
         */
        void FadeStateChanged(int newState);

    protected:

        void mousePressEvent(QMouseEvent*);
        void mouseMoveEvent(QMouseEvent*);
        void mouseReleaseEvent(QMouseEvent*);
        void showEvent(QShowEvent*);
        void hideEvent(QHideEvent*);
        void closeEvent(QCloseEvent*);
        void timerEvent(QTimerEvent*);
        bool eventFilter(QObject*, QEvent*);
        void ReplaceContent(QWidget* pNewContent);
        void SetMainContentMargins(int left, int top, int right, int bottom);
        void RestoreMainContentMargins();
        void IgnoreTitleMove(bool fl);
        void IgnoreResize(bool fl);
        virtual QToolButton* CloseButton();
        virtual QToolButton* MinimizeButton();
        virtual QToolButton* RestoreButton();
        virtual QToolButton* MaximizeButton();
#if defined(Q_WS_WIN)
        bool winEvent(MSG* message, long* result);
#endif

    private:

        virtual void ShowMinimizedImp();
        virtual void ShowNormalImp();
        virtual void ShowMaximizedImp();
        virtual bool CanClose();

    private:

        struct Private;
        /// A pointer to a private implementation.
        Private* m_pPrivate;
};//class SBWidget
#endif // SBWIDGET_H
