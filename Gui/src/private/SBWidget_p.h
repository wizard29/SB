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
#ifndef SBWIDGET_P_H
#define SBWIDGET_P_H


#include "SBWidget.h"


//------------------------------------------------------------------------------
/**
 * @struct SBWidget::Private
 * @ingroup Gui
 * @brief The SBWidget::Private struct contains the internal widget data
 * and provides the accessory functionality.
 */
struct SBWidget::Private
{
    public:

        enum ResizeDirection
        {
            None = 0,
            Left = 1,
            Right = 2,
            Bottom = 3,
            BottomLeft = 4,
            BottomRight = 5,
            Top = 6,
            TopLeft = 7,
            TopRight = 8
        };

        enum CursorMode
        {
            Default = 0,
            HorizontalResize = 1,
            VerticalResize = 2,
            BDiagResize = 3,
            FDiagResize = 4
        };

    public:

        Private(SBWidget* pHost);
        ~Private();

        void InitDrag(const QPoint& pos);
        void StartDrag();
        void EndDrag();
        void InitResize(const QPoint& pos);
        void StartResize();
        void EndResize();
        int ResizeMode(const QPoint& pos) const;
        void Resize(const QPoint& pos);
        int BorderWidthLeft() const;
        int BorderWidthRight() const;
        int BorderWidthTop() const;
        int BorderWidthBottom() const;
        int CursorModeByPos(const QPoint& pos) const;
        void SetCursorByPos(const QPoint& pos);
        QPoint ResizeDelta(const QPoint& pos) const;
        void SetupTitleBar();
        void SetCursor(int cursorMode);
        void AddMinimizeButton();
        void AddMaximizeButton();
        void AddRestoreButton();
        void Show();
        void Hide();
        void Close();
        void SetFadeTime(int msec);
        void SetIntensifyTime(int msec);
        void ShowIteration();
        void HideIteration();
        void CloseIteration();
        void RestartFadeTimer();
        void StopFadeTimer();
        void FadeCancel(bool fl);
        void SetTitleBarText(const QString&);

    public:

        /// A pointer to the host widget.
        SBWidget* m_pHost;
        /// A title bar pointer.
        SBTitleBar* m_pTitleBar;
        /// A content widget pointer.
        QWidget* m_pContent;
        /// A pointer to the main content widget.
        QWidget* m_pWidget;
        /// A delta pointer that used within the window dragging.
        QPoint m_dragDelta;
        ///  The drag state indication.
        bool m_drag;
        /// The drage state has initialized indication.
        bool m_dragState;
        /// A delta pointer that used within the window resizing.
        QPoint m_resizeDelta;
        ///  The resize state indication.
        bool m_resize;
        /// The resize state has initialized indication.
        bool m_resizeState;
        /// The current resizing flag.
        int m_resizeMode;
        /// The current cursor flag.
        int m_cursorMode;
        /// A pointer to the close button.
        QToolButton* m_pCloseBtn;
        /// A pointer to the minimized button.
        QToolButton* m_pMinimizedBtn;
        /// A pointer to the maximized button.
        QToolButton* m_pMaximizedBtn;
        /// A pointer to the restore button.
        QToolButton* m_pRestoreBtn;
        /// The title bar move flag.
        bool m_ignoreMoveFromTitle;
        /// The frame resize flag.
        bool m_ignoreResize;
        /// A current fade state.
        FadeState m_fadeState;
        /// The fade timer identifier.
        int m_fadeTimerID;
        /// A value of the fade time.
        int m_fadeTime;
        /// A value of the intensify time.
        int m_intensifyTime;
        /// An opacity fade value.
        qreal m_fadeStep;
        /// An opacity intensify value.
        qreal m_intensifyStep;        
        /// The fade/intensify timer resolution value in milliseconds
        /// By default it is equal to 40 ms.
        static const int FADETIMERSTEP;
        /// The widget's border margins
        static const QMargins BORDERMARGINS;
};//struct SBWidget::Private
#endif // SBWIDGET_P_H
