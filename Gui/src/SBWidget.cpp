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
#include "SBWidget_p.h"
#include "SBTitleBar.h"
#include <qevent.h>
#include <qgridlayout.h>
#include <qtoolbutton.h>
#include <qapplication.h>
#include <qdesktopwidget.h>
#if defined(Q_WS_WIN)
#include <windows.h>
#endif


//------------------------------------------------------------------------------
/**
 * @class SBWidget
 * @ingroup Gui
 * @brief The SBWidget class is the base OptiPic widget class that must used
 * as the top-level widget.
 */
//------------------------------------------------------------------------------
/**
 * @brief Constructor.
 */
SBWidget::SBWidget(QWidget* pParent, Qt::WindowFlags f, TitlePosition titlePos)
    : QWidget(pParent, f | Qt::CustomizeWindowHint | Qt::FramelessWindowHint)
    , m_pPrivate(nullptr)
{    
    m_pPrivate = new Private(this, titlePos);
    // this call need to avoid style sheet requests
    m_pPrivate->Init();
}

//------------------------------------------------------------------------------
/**
 * @brief Destructor.
 */
SBWidget::~SBWidget()
{
    Q_ASSERT(m_pPrivate);
    delete m_pPrivate;
}

//------------------------------------------------------------------------------
/**
 * @brief Sets the fade widget time in milliseconds.
 * By default the fade time is equal to 0 ms.
 * @param msec - the fade time in milliseconds.
 */
void SBWidget::SetFadeTime(int msec)
{
    Q_ASSERT(m_pPrivate);
    m_pPrivate->SetFadeTime(msec);
}

//------------------------------------------------------------------------------
/**
 * @brief Sets the intensify widget time in milliseconds.
 * By default the intensify time is equal to 0 ms.
 * @param msec - the intensify time in milliseconds.
 */
void SBWidget::SetIntensifyTime(int msec)
{
    Q_ASSERT(m_pPrivate);
    m_pPrivate->SetIntensifyTime(msec);
}

//------------------------------------------------------------------------------
/**
 * @brief Cancels the fade/intesify action.
 * @param visible - the visibility cancelation flag.
 * If the visible flag is equal to true then the widget stays visible.
 */
void SBWidget::CancelFadeAction(bool visible)
{
    Q_ASSERT(m_pPrivate);
    m_pPrivate->FadeCancel(visible);
}

//------------------------------------------------------------------------------
/**
 * @brief Returns widget's title bar.
 */
SBTitleBar* SBWidget::TitleBar()
{
    Q_ASSERT(m_pPrivate);
    return m_pPrivate->m_pTitleBar;
}

//------------------------------------------------------------------------------
/**
 * @brief Returns the widget's client area.
 */
QWidget* SBWidget::Content()
{
    Q_ASSERT(m_pPrivate);
    return m_pPrivate->m_pContent;
}

//------------------------------------------------------------------------------
/**
 * @brief Returns true if the widget can be closed.
 * The implementation of the close request must be located in the CanClose method.
 */
bool SBWidget::IsAllowToClose()
{
    return CanClose();
}

//------------------------------------------------------------------------------
/**
 * @brief Returns widget's title bar position.
 */
SBWidget::TitlePosition SBWidget::GetTitlePosition()
{
    Q_ASSERT(m_pPrivate);
    return m_pPrivate->m_titlePos;
}

//------------------------------------------------------------------------------
/**
 * @brief Appends the minimize button.
 */
void SBWidget::AddMinimizeButton()
{
    m_pPrivate->AddMinimizeButton();
}

//------------------------------------------------------------------------------
/**
 * @brief Appends the maximize button.
 */
void SBWidget::AddMaximizeButton()
{
    m_pPrivate->AddMaximizeButton();
}

//------------------------------------------------------------------------------
void SBWidget::AddRestoreButton()
{
    m_pPrivate->AddRestoreButton();
}

//------------------------------------------------------------------------------
/**
 * @brief Shows minimized window.
 */
void SBWidget::ShowMinimized()
{
    ShowMinimizedImp();
}

//------------------------------------------------------------------------------
/**
 * @brief Shows normal window.
 */
void SBWidget::ShowNormal()
{
    ShowNormalImp();
}

//------------------------------------------------------------------------------
/**
 * @brief Shows maximized window.
 */
void SBWidget::ShowMaximized()
{
    ShowMaximizedImp();
}

//------------------------------------------------------------------------------
/**
 * @brief Reimplemented method.
 * @see QWidget::mousePressEvent
 */
void SBWidget::mousePressEvent(QMouseEvent* pEvent)
{
    if (pEvent->button() == Qt::LeftButton && !isMaximized() && !isMinimized())
    {
        Q_ASSERT(m_pPrivate);
        QPoint pos = m_pPrivate->m_pTitleBar->mapFrom(this, pEvent->pos());
        QRect titleRect = m_pPrivate->GetTitleRectForDrag();
        if (titleRect.contains(pos))
        {
            m_pPrivate->InitDrag(pEvent->pos());
            return;
        }
        if (m_pPrivate->m_cursorMode != Private::Default &&
            !m_pPrivate->m_ignoreResize)
        {
            m_pPrivate->InitResize(mapToParent(pEvent->pos()));
        }
    }
}

//------------------------------------------------------------------------------
/**
 * @brief Reimplemented method.
 * @see QWidget::mouseMoveEvent
 */
void SBWidget::mouseMoveEvent(QMouseEvent* pEvent)
{
    Q_ASSERT(m_pPrivate);
    if (m_pPrivate->m_dragState && !m_pPrivate->m_drag)
    {
        m_pPrivate->StartDrag();
    }
    if (m_pPrivate->m_drag)
    {
        move(mapToParent(pEvent->pos()) - m_pPrivate->m_dragDelta);
        return;
    }
}

//------------------------------------------------------------------------------
/**
 * @brief Reimplemented method.
 * @see QWidget::mouseReleaseEvent
 */
void SBWidget::mouseReleaseEvent(QMouseEvent* pEvent)
{
    if (pEvent->button() == Qt::LeftButton)
    {
        Q_ASSERT(m_pPrivate);
        if (m_pPrivate->m_dragState)
        {
            m_pPrivate->EndDrag();
        }
        if (m_pPrivate->m_resizeMode)
        {
            m_pPrivate->EndResize();
        }
    }
}

//------------------------------------------------------------------------------
/**
 * @brief Reimplemented method.
 * @see QWidget::showEvent
 */
void SBWidget::showEvent(QShowEvent* pEvent)
{
    Q_ASSERT(m_pPrivate);
    m_pPrivate->Show();
    // note: this is a workaround that fixes an official qt bug QTBUG-17548
    // see https://bugreports.qt-project.org/browse/QTBUG-17548 for more details
    QApplication::postEvent(this, new QEvent(QEvent::UpdateRequest), Qt::LowEventPriority);
    QWidget::showEvent(pEvent);
}

//------------------------------------------------------------------------------
/**
 * @brief Reimplemented method.
 * @see QWidget::hideEvent
 */
void SBWidget::hideEvent(QHideEvent* pEvent)
{
    Q_ASSERT(m_pPrivate);
    m_pPrivate->Hide();
    QWidget::hideEvent(pEvent);
}

//------------------------------------------------------------------------------
/**
 * @brief Reimplemented method.
 * @see QWidget::closeEvent
 */
void SBWidget::closeEvent(QCloseEvent* pEvent)
{
    if (windowOpacity() > 0.0)
    {
        Q_ASSERT(m_pPrivate);
        m_pPrivate->Close();
        pEvent->ignore();
        return;
    }
    QWidget::closeEvent(pEvent);
}

//------------------------------------------------------------------------------
/**
 * @brief Reimplemented method.
 * @see QWidget::timerEvent
 */
void SBWidget::timerEvent(QTimerEvent* pEvent)
{
    Q_ASSERT(m_pPrivate);
    if (pEvent->timerId() == m_pPrivate->m_fadeTimerID)
    {
        switch(m_pPrivate->m_fadeState)
        {
            case FadeShow:
                m_pPrivate->ShowIteration();
                break;
            case FadeHide:
                m_pPrivate->HideIteration();
                break;
            case FadeClose:
                m_pPrivate->CloseIteration();
                break;
            default:
                m_pPrivate->StopFadeTimer();
                break;
        }
        return;
    }
    QWidget::timerEvent(pEvent);
}

//------------------------------------------------------------------------------
/**
 * @brief Reimplemented method.
 * @see QWidget::eventFilter
 */
bool SBWidget::eventFilter(QObject* pObject, QEvent* pEvent)
{
    Q_ASSERT(m_pPrivate);
    if (pObject == qobject_cast<QObject*>(m_pPrivate->m_pWidget))
    {
        switch (pEvent->type())
        {
            case QEvent::MouseMove:
            {
                QMouseEvent* pMoveEvent = static_cast<QMouseEvent*>(pEvent);
                Q_ASSERT(pMoveEvent);
                if (m_pPrivate->m_drag || m_pPrivate->m_dragState)
                {
                    break;
                }
                if (m_pPrivate->m_resizeMode != Private::None)
                {
                    if (m_pPrivate->m_resizeState)
                    {
                        if (!m_pPrivate->m_resize)
                        {
                            m_pPrivate->StartResize();
                        }
                        else
                        {
                            m_pPrivate->Resize(pMoveEvent->globalPos());
                            return true;
                        }
                    }
                }
                QPoint pos = m_pPrivate->m_pWidget->mapToParent(pMoveEvent->pos());
                m_pPrivate->SetCursorByPos(mapToParent(pos));
                return true;
            }
                break;
            default:
                break;
        }
    }
    else if (pObject == qobject_cast<QObject*>(m_pPrivate->m_pContent))
    {
        switch (pEvent->type())
        {
            case QEvent::WindowTitleChange:
                m_pPrivate->SetTitleBarText(m_pPrivate->m_pContent->windowTitle());
                break;
            default:
                break;
        }
    }
    else if (pObject == qobject_cast<QObject*>(this))
    {
        switch(pEvent->type())
        {
            case QEvent::WindowStateChange:
            {
                Qt::WindowStates state = windowState();
                if (m_pPrivate->m_pRestoreBtn)
                {
                    m_pPrivate->m_pRestoreBtn->setVisible(state.testFlag(Qt::WindowMaximized));
                }
                if (m_pPrivate->m_pMaximizedBtn)
                {
                    m_pPrivate->m_pMaximizedBtn->setVisible(!state.testFlag(Qt::WindowMaximized));
                }
            }
                break;
            case QEvent::WindowTitleChange:
                m_pPrivate->SetTitleBarText(windowTitle());
                break;
            case QEvent::Close:
                if (!IsAllowToClose())
                {
                    pEvent->ignore();
                    return true;
                }
                break;
            default:
                break;
        }
    }
    else if (pObject == qobject_cast<QObject*>(m_pPrivate->m_pTitleBar))
    {
        switch (pEvent->type())
        {
            case QEvent::MouseMove:
            {
                QMouseEvent* pMoveEvent = static_cast<QMouseEvent*>(pEvent);
                Q_ASSERT(pMoveEvent);
                if (m_pPrivate->m_drag || m_pPrivate->m_dragState)
                {
                    break;
                }
                if (m_pPrivate->m_resizeMode != Private::None)
                {
                    if (m_pPrivate->m_resizeState)
                    {
                        if (!m_pPrivate->m_resize)
                        {
                            m_pPrivate->StartResize();
                        }
                        else
                        {
                            m_pPrivate->Resize(pMoveEvent->globalPos());
                            return true;
                        }
                    }
                }
                QPoint pos = m_pPrivate->m_pTitleBar->mapToParent(pMoveEvent->pos());
                m_pPrivate->SetCursorByPos(mapToParent(pos));
                return true;
            }
                break;
            default:
                break;
        }
    }
    return QWidget::eventFilter(pObject, pEvent);
}

//------------------------------------------------------------------------------
/**
 * @brief Replaces the content part widget.
 * @param pNewContent - a new content part widget.
 */
void SBWidget::ReplaceContent(QWidget* pNewContent)
{
    Q_ASSERT(m_pPrivate);
    if (m_pPrivate->m_pContent != pNewContent)
    {
        QGridLayout* pGrid = qobject_cast<QGridLayout*>(m_pPrivate->m_pWidget->layout());
        Q_ASSERT(pNewContent);
        m_pPrivate->m_pContent->removeEventFilter(this);
        m_pPrivate->m_pContent->hide();
        m_pPrivate->m_pContent->deleteLater();
        m_pPrivate->m_pContent = pNewContent;
        m_pPrivate->m_pContent->setObjectName("SBWIDGETCONTENT");
        pGrid->addWidget(m_pPrivate->m_pContent, 0, 0);
        m_pPrivate->m_pContent->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        m_pPrivate->m_pContent->setAutoFillBackground(true);
        m_pPrivate->m_pContent->installEventFilter(this);
        m_pPrivate->SetTitleBarText(m_pPrivate->m_pContent->windowTitle());
    }
}

//------------------------------------------------------------------------------
/**
 * @brief Sets main widget content layout margins.
 * @param left - left margin.
 * @param top - top margin.
 * @param right - right margin.
 * @param bottom - bottom margin.
 */
void SBWidget::SetMainContentMargins(int left, int top, int right, int bottom)
{
    Q_ASSERT(m_pPrivate);
    QGridLayout* pGrid = qobject_cast<QGridLayout*>(
                m_pPrivate->m_pWidget->layout());
    Q_ASSERT(pGrid);
    pGrid->setContentsMargins(left, top, right, bottom);
}

//------------------------------------------------------------------------------
/**
 * @brief Restores default layout margins of the main widget content.
 */
void SBWidget::RestoreMainContentMargins()
{
    QGridLayout* pGrid = qobject_cast<QGridLayout*>(
                m_pPrivate->m_pWidget->layout());
    Q_ASSERT(pGrid);
    pGrid->setContentsMargins(Private::BORDERMARGINS);
}

//------------------------------------------------------------------------------
/**
 * @brief Blocks/unblocks move functionality that provides a title bar.
 * By default this functionality is enebaled.
 */
void SBWidget::IgnoreTitleMove(bool fl)
{
    Q_ASSERT(m_pPrivate);
    m_pPrivate->m_ignoreMoveFromTitle = fl;
}

//------------------------------------------------------------------------------
/**
 * @brief Blocks/unblocks move functionality that provides a window border.
 * By default this functionality is enebaled.
 */
void SBWidget::IgnoreResize(bool fl)
{
    Q_ASSERT(m_pPrivate);
    m_pPrivate->m_ignoreResize = fl;
}

//------------------------------------------------------------------------------
/**
 * @brief Returns pointer to the close button.
 */
QToolButton* SBWidget::CloseButton()
{
    Q_ASSERT(m_pPrivate);
    return m_pPrivate->m_pCloseBtn;
}

//------------------------------------------------------------------------------
/**
 * @brief Returns pointer to the minimize button.
 */
QToolButton* SBWidget::MinimizeButton()
{
    Q_ASSERT(m_pPrivate);
    return m_pPrivate->m_pMinimizedBtn;
}

//------------------------------------------------------------------------------
/**
 * @brief Returns pointer to the restore button.
 */
QToolButton* SBWidget::RestoreButton()
{
    Q_ASSERT(m_pPrivate);
    return m_pPrivate->m_pRestoreBtn;
}

//------------------------------------------------------------------------------
/**
 * @brief Returns pointer to the maximize button.
 */
QToolButton* SBWidget::MaximizeButton()
{
    Q_ASSERT(m_pPrivate);
    return m_pPrivate->m_pMaximizedBtn;
}

//------------------------------------------------------------------------------
#if defined(Q_WS_WIN)
/**
 * @brief Reimplemented method. Patches the QTBUG-8361.
 */
bool SBWidget::winEvent(MSG* message, long* result)
{
    QWidget* pParent = parentWidget();
    Qt::WindowFlags flags = windowFlags();
    if (!pParent || QApplication::desktop() == pParent ||
        flags.testFlag(Qt::Window))
    {
        switch (message->message)
        {
            case WM_GETMINMAXINFO:
            {
                // GetSysemMetrics(): http://msdn.microsoft.com/en-us/library/ms724385(VS.85).aspx
                // ptMinTrackSize - The minimum tracking width/height of a window, in pixels.
                // The user cannot drag the window frame to a size smaller than these dimensions.
                // ptMaxTrackSize - The default maximum width/height of a window that has a caption
                // and sizing borders, in pixels. This metric refers to the entire desktop. The user cannot
                // drag the window frame to a size larger than these dimensions.

                // WM_GETMINMAXINFO: http://msdn.microsoft.com/en-us/library/ms632626(VS.85).aspx
                // MINMAXINFO structure: http://msdn.microsoft.com/en-us/library/ms632605(VS.85).aspx

                MINMAXINFO* pMMI = (MINMAXINFO*)(message->lParam);
                QDesktopWidget* pDesktopWidget = QApplication::desktop();
                Q_ASSERT(pDesktopWidget);
                int widgetScreen = pDesktopWidget->screenNumber(this);
                QRect desktop = pDesktopWidget->availableGeometry(widgetScreen);
                pMMI->ptMaxSize.x = desktop.width();
                pMMI->ptMaxSize.y = desktop.height();

                pMMI->ptMaxPosition.x = desktop.x();
                pMMI->ptMaxPosition.y = desktop.y();
                int primaryScreen = pDesktopWidget->primaryScreen();
                if (primaryScreen != widgetScreen)
                {
                    pMMI->ptMaxPosition.x = 0;
                    pMMI->ptMaxPosition.y = 0;
                }

                pMMI->ptMinTrackSize.x = minimumWidth(); // minimum width for our window
                pMMI->ptMinTrackSize.y = minimumHeight(); // minimum height for our window

                pMMI->ptMaxTrackSize.x = desktop.width();
                pMMI->ptMaxTrackSize.y = desktop.height();
                result = 0;
                return true;
            }
                break;
            default:
                break;
        }
    }
    return QWidget::winEvent(message, result);
}
#endif

//------------------------------------------------------------------------------
/**
 * @brief Calls QWidget::showMinimized by default.
 */
void SBWidget::ShowMinimizedImp()
{
    showMinimized();
}

//------------------------------------------------------------------------------
/**
 * @brief Calls QWidget::showNormal by default.
 */
void SBWidget::ShowNormalImp()
{
    showNormal();
}

//------------------------------------------------------------------------------
/**
 * @brief Calls QWidget::showMaximized by default.
 */
void SBWidget::ShowMaximizedImp()
{
    showMaximized();
}

//------------------------------------------------------------------------------
/**
 * @brief The default implementation always returns true.
 */
bool SBWidget::CanClose()
{
    return true;
}
//------------------------------------------------------------------------------
