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
#include <qtoolbutton.h>
#include <qgridlayout.h>


//------------------------------------------------------------------------------
const int SBWidget::Private::FADETIMERSTEP = 40;

//------------------------------------------------------------------------------
const QMargins SBWidget::Private::BORDERMARGINS = QMargins(3, 0, 3, 3);


//------------------------------------------------------------------------------
/**
 * @brief Constructor.
 * @param pHost - a pointer to a host object. Must not be a null pointer.
 * @param titlePos - a title bar position.
 */
SBWidget::Private::Private(SBWidget* pHost, SBWidget::TitlePosition titlePos)
    : m_pHost(pHost)
    , m_pTitleBar(nullptr)
    , m_pContent(nullptr)
    , m_pWidget(nullptr)
    , m_dragDelta()
    , m_drag(false)
    , m_dragState(false)
    , m_resizeDelta()
    , m_resize(false)
    , m_resizeState(false)
    , m_resizeMode(static_cast<int>(None))
    , m_cursorMode(static_cast<int>(Default))
    , m_pCloseBtn(nullptr)
    , m_pMinimizedBtn(nullptr)
    , m_pMaximizedBtn(nullptr)
    , m_pRestoreBtn(nullptr)
    , m_ignoreMoveFromTitle(false)
    , m_ignoreResize(false)
    , m_fadeState(FadeNone)
    , m_fadeTimerID(-1)
    , m_fadeTime(0)
    , m_intensifyTime(0)
    , m_fadeStep(1.0)
    , m_intensifyStep(1.0)
    , m_titlePos(titlePos)
{
}

//------------------------------------------------------------------------------
/**
 * @brief Creates a widget's content.
 */
void SBWidget::Private::Init()
{
    Q_ASSERT(m_pHost);
#ifdef Q_OS_MACX
    m_pHost->setAttribute(Qt::WA_NoBackground);
#else
    m_pHost->setAttribute(Qt::WA_TranslucentBackground);
#endif
    QGridLayout* pMainGrid = new QGridLayout(m_pHost);
    pMainGrid->setSpacing(0);
    pMainGrid->setMargin(0);
    m_pHost->setMouseTracking(true);
    m_pTitleBar = new SBTitleBar(m_pHost);
    m_pTitleBar->setCursor(Qt::ArrowCursor);
    switch (m_titlePos)
    {
        case SBWidget::TopTitleBar:
        case SBWidget::BottomTitleBar:
            m_pTitleBar->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
            break;
        case SBWidget::LeftTitleBar:
        case SBWidget::RightTitleBar:
            m_pTitleBar->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
            break;
    }
    m_pTitleBar->setMouseTracking(true);
    m_pWidget = new QWidget(m_pHost);
    m_pWidget->setObjectName("WIDGETMAINCONTENT");
    m_pWidget->setCursor(Qt::ArrowCursor);
    QGridLayout* pGrid = new QGridLayout(m_pWidget);
    pGrid->setContentsMargins(BORDERMARGINS);
    m_pContent = new QWidget(m_pWidget);
    m_pContent->setObjectName("WIDGETCONTENT");
    m_pContent->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    pGrid->addWidget(m_pContent, 0, 0);
    m_pContent->setAutoFillBackground(true);
    m_pContent->setCursor(Qt::ArrowCursor);
    m_pWidget->setAutoFillBackground(true);
    m_pWidget->setMouseTracking(true);
    SetupTitleBar();
    m_pHost->setWindowOpacity(0.0);
    switch (m_titlePos)
    {
        case SBWidget::TopTitleBar:
            pMainGrid->addWidget(m_pTitleBar, 0, 0);
            pMainGrid->addWidget(m_pWidget, 1, 0);
            break;
        case SBWidget::BottomTitleBar:
            pMainGrid->addWidget(m_pWidget, 0, 0);
            pMainGrid->addWidget(m_pTitleBar, 1, 0);
            break;
        case SBWidget::LeftTitleBar:
            pMainGrid->addWidget(m_pTitleBar, 0, 0);
            pMainGrid->addWidget(m_pWidget, 0, 1);
            break;
        case SBWidget::RightTitleBar:
            pMainGrid->addWidget(m_pWidget, 0, 0);
            pMainGrid->addWidget(m_pTitleBar, 0, 1);
            break;
    }
    m_pTitleBar->installEventFilter(m_pHost);
    m_pContent->installEventFilter(m_pHost);
    m_pWidget->installEventFilter(m_pHost);
    m_pHost->installEventFilter(m_pHost);
}

//------------------------------------------------------------------------------
/**
 * @brief Destructor.
 */
SBWidget::Private::~Private()
{
}

//------------------------------------------------------------------------------
/**
 * @brief Initializes the drag parameters.
 * @param pos - the mouse press position (in widget coordinate system)
 */
void SBWidget::Private::InitDrag(const QPoint& pos)
{
    m_dragDelta = pos;
    m_dragState = true;
    m_drag = false;    
}

//------------------------------------------------------------------------------
/**
 * @brief Starts the drag action.
 */
void SBWidget::Private::StartDrag()
{    
    m_drag = true;    
}

//------------------------------------------------------------------------------
/**
 * @brief Finishes the drag action.
 */
void SBWidget::Private::EndDrag()
{
    m_dragState = false;
    m_drag = false;    
}

//------------------------------------------------------------------------------
/**
 * @brief Initializes the resize parameters.
 * @param pos - the mouse press position (in widget coordinate system)
 */
void SBWidget::Private::InitResize(const QPoint& pos)
{
    m_resizeMode = ResizeMode(pos);
    m_resizeDelta = ResizeDelta(pos);
    m_resizeState = true;
    m_resize = false;    
}

//------------------------------------------------------------------------------
/**
 * @brief Starts the resize action.
 */
void SBWidget::Private::StartResize()
{
    m_resize = true;    
}

//------------------------------------------------------------------------------
/**
 * @brief Finishes the resize action.
 */
void SBWidget::Private::EndResize()
{
    m_resizeState = false;
    m_resize = false;
    m_resizeMode = None;    
}

//------------------------------------------------------------------------------
/**
 * @brief Calculates the resize mode.
 * @param pos - the mouse position (in widget coordinate system)
 * @return Resize mode type.
 */
int SBWidget::Private::ResizeMode(const QPoint& pos) const
{    
    QRect r1 = m_pHost->frameGeometry();
    QRect r2 = r1.adjusted(BorderWidthLeft(), BorderWidthTop(),
                           -BorderWidthRight(), -BorderWidthBottom());
    if (pos.x() >= r1.left() && pos.x() <= r2.left() &&
        pos.y() >= r2.top() && pos.y() <= r2.bottom())
    {
        if (m_pHost->minimumWidth() != m_pHost->maximumWidth())
        {
            return Left;
        }
    }
    else if (pos.x() >= r2.right() && pos.x() <= r1.right() &&
             pos.y() >= r2.top() && pos.y() <= r2.bottom())
    {
        if (m_pHost->minimumWidth() != m_pHost->maximumWidth())
        {
            return Right;
        }
    }
    else if (pos.x() >= r2.left() && pos.x() <= r2.right() &&
             pos.y() >= r2.bottom() && pos.y() <= r1.bottom())
    {
        if (m_pHost->minimumHeight() != m_pHost->maximumHeight())
        {
            return Bottom;
        }
    }
    else if (pos.x() >= r2.left() && pos.x() <= r2.right() &&
             pos.y() <= r2.top() && pos.y() >= r1.top())
    {
        if (m_pHost->minimumHeight() != m_pHost->maximumHeight())
        {
            return Top;
        }
    }
    r2 = r2.adjusted(BorderWidthLeft(), BorderWidthTop(),
                     -BorderWidthRight(), -BorderWidthBottom());
    if (pos.x() >= r1.left() && pos.x() <= r2.left() &&
        pos.y() >= r2.bottom() && pos.y() <= r1.bottom())
    {
        if (m_pHost->minimumWidth() != m_pHost->maximumWidth() &&
            m_pHost->minimumHeight() == m_pHost->maximumHeight())
        {
            return Left;
        }
        else if (m_pHost->minimumWidth() == m_pHost->maximumWidth() &&
                 m_pHost->minimumHeight() != m_pHost->maximumHeight())
        {
            return Bottom;
        }
        else if (m_pHost->minimumWidth() != m_pHost->maximumWidth() &&
                 m_pHost->minimumHeight() != m_pHost->maximumHeight())
        {
            return BottomLeft;
        }
    }
    else if (pos.x() >= r2.right() && pos.x() <= r1.right() &&
             pos.y() >= r2.bottom() && pos.y() <= r1.bottom())
    {
        if (m_pHost->minimumWidth() != m_pHost->maximumWidth() &&
            m_pHost->minimumHeight() != m_pHost->maximumHeight())
        {
            return BottomRight;
        }
        else if (m_pHost->minimumWidth() != m_pHost->maximumWidth() &&
                 m_pHost->minimumHeight() == m_pHost->maximumHeight())
        {
            return Right;
        }
        else if (m_pHost->minimumWidth() == m_pHost->maximumWidth() &&
                 m_pHost->minimumHeight() != m_pHost->maximumHeight())
        {
            return Bottom;
        }
    }
    else if (pos.x() >= r1.left() && pos.x() <= r2.left() &&
             pos.y() >= r1.top() && pos.y() <= r2.top())
    {
        if (m_pHost->minimumWidth() != m_pHost->maximumWidth() &&
            m_pHost->minimumHeight() == m_pHost->maximumHeight())
        {
            return Left;
        }
        else if (m_pHost->minimumWidth() == m_pHost->maximumWidth() &&
                 m_pHost->minimumHeight() != m_pHost->maximumHeight())
        {
            return Top;
        }
        else if (m_pHost->minimumWidth() != m_pHost->maximumWidth() &&
                 m_pHost->minimumHeight() != m_pHost->maximumHeight())
        {
            return TopLeft;
        }
    }
    else if (pos.x() >= r2.right() && pos.x() <= r1.right() &&
             pos.y() >= r1.top() && pos.y() <= r2.top())
    {
        if (m_pHost->minimumWidth() != m_pHost->maximumWidth() &&
            m_pHost->minimumHeight() != m_pHost->maximumHeight())
        {
            return TopRight;
        }
        else if (m_pHost->minimumWidth() != m_pHost->maximumWidth() &&
                 m_pHost->minimumHeight() == m_pHost->maximumHeight())
        {
            return Right;
        }
        else if (m_pHost->minimumWidth() == m_pHost->maximumWidth() &&
                 m_pHost->minimumHeight() != m_pHost->maximumHeight())
        {
            return Top;
        }
    }
    return None;
}

//------------------------------------------------------------------------------
/**
 * @brief Resizes the host widget.
 * @param pos - the global mouse position.
 */
void SBWidget::Private::Resize(const QPoint& point)
{
    QRect r = m_pHost->rect();
    r.setTopLeft(m_pHost->mapToParent(r.topLeft()));
    r.setBottomRight(m_pHost->mapToParent(r.bottomRight()));
    QPoint pt = m_pHost->mapFromGlobal(point);
    QPoint parentPt = m_pHost->mapToParent(pt);
    QSize minSize = m_pHost->minimumSizeHint();
    switch (m_resizeMode)
    {
        case Left:
            r.setLeft(parentPt.x() + m_resizeDelta.x());
            if (r.width() < minSize.width())
            {
                r.setLeft(r.right() - minSize.width() + 1);
            }
            break;
        case Right:
            r.setRight(parentPt.x() + m_resizeDelta.x());
            if (r.width() < minSize.width())
            {
                r.setRight(r.left() + minSize.width() - 1);
            }
            break;
        case Bottom:
            r.setBottom(parentPt.y() + m_resizeDelta.y());
            if (r.height() < minSize.height())
            {
                r.setBottom(r.top() + minSize.height() - 1);
            }
            break;
        case Top:
            r.setTop(parentPt.y() + m_resizeDelta.y());
            if (r.height() < minSize.height())
            {
                r.setTop(r.bottom() - minSize.height() + 1);
            }
            break;
        case BottomLeft:
            r.setBottomLeft(parentPt + m_resizeDelta);
            if (r.width() < minSize.width())
            {
                r.setLeft(r.right() - minSize.width() + 1);
            }
            if (r.height() < minSize.height())
            {
                r.setBottom(r.top() + minSize.height() - 1);
            }
            break;
        case TopLeft:
            r.setTopLeft(parentPt + m_resizeDelta);
            if (r.width() < minSize.width())
            {
                r.setLeft(r.right() - minSize.width() + 1);
            }
            if (r.height() < minSize.height())
            {
                r.setTop(r.bottom() - minSize.height() + 1);
            }
            break;
        case BottomRight:
            r.setBottomRight(parentPt + m_resizeDelta);
            if (r.width() < minSize.width())
            {
                r.setRight(r.left() + minSize.width() - 1);
            }
            if (r.height() < minSize.height())
            {
                r.setBottom(r.top() + minSize.height() - 1);
            }
            break;
        case TopRight:
            r.setTopRight(parentPt + m_resizeDelta);
            if (r.width() < minSize.width())
            {
                r.setRight(r.left() + minSize.width() - 1);
            }
            if (r.height() < minSize.height())
            {
                r.setTop(r.bottom() - minSize.height() + 1);
            }
            break;
        default:
            break;
    }
    if (m_resizeMode != None)
    {
        m_pHost->setGeometry(r);
    }
}

//------------------------------------------------------------------------------
/**
 * @brief Returns the virtual left border width.
 * Used to detect the left resize border.
 */
int SBWidget::Private::BorderWidthLeft() const
{
    return 4;
}

//------------------------------------------------------------------------------
/**
 * @brief Returns the virtual right border width.
 * Used to detect the right resize border.
 */
int SBWidget::Private::BorderWidthRight() const
{
    return 4;
}

//------------------------------------------------------------------------------
/**
 * @brief Returns the virtual top border width.
 * Used to detect the top resize border.
 */
int SBWidget::Private::BorderWidthTop() const
{
    return 4;
}

//------------------------------------------------------------------------------
/**
 * @brief Returns the virtual bottom border width.
 * Used to detect the bottom resize border.
 */
int SBWidget::Private::BorderWidthBottom() const
{
    return 4;
}

//------------------------------------------------------------------------------
/**
 * @brief Returns cursor mode by the given cursor position.
 * @param pos - the mouse position (in widget coordinate system)
 */
int SBWidget::Private::CursorModeByPos(const QPoint& pos) const
{
    if (m_ignoreResize || m_pHost->isMaximized() || m_pHost->isMinimized())
    {
        return Default;
    }
    int resizeMode = ResizeMode(pos);
    int result = Default;
    switch (resizeMode)
    {
        case Left:
        case Right:
            result = HorizontalResize;
            break;
        case Top:
        case Bottom:
            result = VerticalResize;
            break;
        case BottomLeft:
        case TopRight:
            result = BDiagResize;
            break;
        case BottomRight:
        case TopLeft:
            result = FDiagResize;
            break;        
        default:
            result = Default;
            break;
    }
    return result;
}

//------------------------------------------------------------------------------
/**
 * @brief Sets cursor type that depends on the cursor position.
 * @param pos - the mouse position (in widget coordinate system)
 */
void SBWidget::Private::SetCursorByPos(const QPoint& pos)
{
    int currMode = CursorModeByPos(pos);
    if (currMode != m_cursorMode)
    {
        m_cursorMode = currMode;
        SetCursor(m_cursorMode);
    }
}

//------------------------------------------------------------------------------
/**
 * @brief Returns a resize cursor delta.
 * @param pos - the mouse position (in widget coordinate system)
 */
QPoint SBWidget::Private::ResizeDelta(const QPoint& pos) const
{
    int resizeMode = ResizeMode(pos);
    QRect contentGeometry = m_pHost->frameGeometry();
    QPoint result;
    switch (resizeMode)
    {
        case Left:
            result.setX(contentGeometry.left() - pos.x());
            break;
        case Right:
            result.setX(contentGeometry.right() - pos.x());
            break;
        case Bottom:
            result.setY(contentGeometry.bottom() - pos.y());
            break;
        case Top:
            result.setY(contentGeometry.top() - pos.y());
            break;
        case BottomLeft:
            result = contentGeometry.bottomLeft() - pos;
            break;
        case BottomRight:
            result = contentGeometry.bottomRight() - pos;
            break;
        case TopLeft:
            result = contentGeometry.topLeft() - pos;
            break;
        case TopRight:
            result = contentGeometry.topRight() - pos;
            break;
        default:
            break;
    }
    return result;
}

//------------------------------------------------------------------------------
/**
 * @brief Setups the title bar.
 */
void SBWidget::Private::SetupTitleBar()
{
#ifdef Q_OS_WIN
    m_pCloseBtn = m_pTitleBar->AddButton(Qt::AlignRight, tr("Close"));
#else
    m_pCloseBtn = m_pTitleBar->AddButton(Qt::AlignLeft, tr("Close"));
#endif
    m_pCloseBtn->setObjectName("CLOSEBUTTON");
    m_pCloseBtn->setFocusPolicy(Qt::NoFocus);
    connect(m_pCloseBtn, SIGNAL(clicked()), m_pHost, SLOT(close()));
}

//------------------------------------------------------------------------------
/**
 * @brief Sets cursor to the content widget by cursor mode.
 * @param cursorMode - the cursor mode.
 */
void SBWidget::Private::SetCursor(int cursorMode)
{
    if (m_ignoreResize)
    {
        cursorMode = Default;
    }    
    switch (cursorMode)
    {
        case Default:
            m_pWidget->setCursor(Qt::ArrowCursor);
            m_pTitleBar->setCursor(Qt::ArrowCursor);
            break;
        case HorizontalResize:
            m_pWidget->setCursor(Qt::SizeHorCursor);
            m_pTitleBar->setCursor(Qt::SizeHorCursor);
            break;
        case VerticalResize:
            m_pWidget->setCursor(Qt::SizeVerCursor);
            m_pTitleBar->setCursor(Qt::SizeVerCursor);
            break;
        case BDiagResize:
            m_pWidget->setCursor(Qt::SizeBDiagCursor);
            m_pTitleBar->setCursor(Qt::SizeBDiagCursor);
            break;
        case FDiagResize:
            m_pWidget->setCursor(Qt::SizeFDiagCursor);
            m_pTitleBar->setCursor(Qt::SizeFDiagCursor);
            break;
        default:
            m_pWidget->setCursor(Qt::ArrowCursor);
            m_pTitleBar->setCursor(Qt::ArrowCursor);
            break;
    }
}

//------------------------------------------------------------------------------
/**
 * @brief Appends the minimize button.
 */
void SBWidget::Private::AddMinimizeButton()
{
#ifdef Q_OS_WIN
    m_pMinimizedBtn = m_pHost->TitleBar()->AddButton(Qt::AlignRight, tr("Minimize"));
#else
    m_pMinimizedBtn = m_pHost->TitleBar()->AddButton(Qt::AlignLeft, tr("Minimize"));
#endif
    m_pMinimizedBtn->setObjectName("MINIMIZEBUTTON");
    m_pMinimizedBtn->setFocusPolicy(Qt::NoFocus);
    connect(m_pMinimizedBtn, SIGNAL(clicked()), m_pHost, SLOT(ShowMinimized()));
}

//------------------------------------------------------------------------------
/**
 * @brief Appends the maximize button.
 */
void SBWidget::Private::AddMaximizeButton()
{
#ifdef Q_OS_WIN
    m_pMaximizedBtn = m_pHost->TitleBar()->AddButton(Qt::AlignRight, tr("Maximize"));
#else
    m_pMaximizedBtn = m_pHost->TitleBar()->AddButton(Qt::AlignLeft, tr("Maximize"));
#endif
    m_pMaximizedBtn->setObjectName("MAXIMIZEBUTTON");
    m_pMaximizedBtn->setFocusPolicy(Qt::NoFocus);
    connect(m_pMaximizedBtn, SIGNAL(clicked()), m_pHost, SLOT(ShowMaximized()));
}

//------------------------------------------------------------------------------
/**
 * @brief Appends the restore button.
 */
void SBWidget::Private::AddRestoreButton()
{
#ifdef Q_OS_WIN
    m_pRestoreBtn = m_pHost->TitleBar()->AddButton(Qt::AlignRight, tr("Restore"));
#else
    m_pRestoreBtn = m_pHost->TitleBar()->AddButton(Qt::AlignLeft, tr("Restore"));
#endif
    m_pRestoreBtn->setObjectName("RESTOREBUTTON");
    m_pRestoreBtn->setFocusPolicy(Qt::NoFocus);
    connect(m_pRestoreBtn, SIGNAL(clicked()), m_pHost, SLOT(ShowNormal()));
}

//------------------------------------------------------------------------------
/**
 * @brief Show window handler. (fade functionality)
 */
void SBWidget::Private::Show()
{
    m_fadeState = FadeShow;
    RestartFadeTimer();    
    emit m_pHost->FadeStateChanged(m_fadeState);
}

//------------------------------------------------------------------------------
/**
 * @brief Hide window handler. (fade functionality)
 */
void SBWidget::Private::Hide()
{
    m_fadeState = FadeHide;
    RestartFadeTimer();    
    emit m_pHost->FadeStateChanged(m_fadeState);
}

//------------------------------------------------------------------------------
/**
 * @brief Close window handler. (fade functionality)
 */
void SBWidget::Private::Close()
{
    RestartFadeTimer();
    m_fadeState = FadeClose;
    emit m_pHost->FadeStateChanged(m_fadeState);
}

//------------------------------------------------------------------------------
/**
 * @brief Setups the fade time in milliseconds.
 * @param msec - the time value.
 * The default value of this parameter is equal to 0 ms.
 */
void SBWidget::Private::SetFadeTime(int msec)
{
    if (msec < 0)
    {
        msec = 0;
    }
    m_fadeTime = msec;
    qreal timeStep = (qreal)m_fadeTime / (qreal)FADETIMERSTEP;
    if (timeStep)
    {
        m_fadeStep = 1.0 / timeStep;
    }
    else
    {
        m_fadeStep = 1.0;
    }
}

//------------------------------------------------------------------------------
/**
 * @brief Setups the intensify time in milliseconds.
 * @param msec - the time value.
 * The default value of this parameter is equal to 0 ms.
 */
void SBWidget::Private::SetIntensifyTime(int msec)
{
    if (msec < 0)
    {
        msec = 0;
    }
    m_intensifyTime = msec;
    qreal timeStep = (qreal)m_intensifyTime / (qreal)FADETIMERSTEP;
    if (timeStep)
    {
        m_intensifyStep = 1.0 / timeStep;
    }
    else
    {
        m_intensifyStep = 1.0;
    }
}

//------------------------------------------------------------------------------
/**
 * @brief Executes the next intesify iteration.
 */
void SBWidget::Private::ShowIteration()
{
    qreal opacity = m_pHost->windowOpacity();
    opacity += m_intensifyStep;
    if (opacity >= 1.0)
    {
        opacity = 1.0;
        m_fadeState = FadeNormal;
        emit m_pHost->FadeStateChanged(m_fadeState);
        StopFadeTimer();
    }
    m_pHost->setWindowOpacity(opacity);
}

//------------------------------------------------------------------------------
/**
 * @brief Executes the next fade iteration.
 */
void SBWidget::Private::HideIteration()
{
    qreal opacity = m_pHost->windowOpacity();
    opacity -= m_fadeStep;
    if (opacity <= 0.0)
    {
        opacity = 0.0;
        m_fadeState = FadeNormal;
        emit m_pHost->FadeStateChanged(m_fadeState);
        StopFadeTimer();
    }
    m_pHost->setWindowOpacity(opacity);
}

//------------------------------------------------------------------------------
/**
 * @brief Executes the next close(fade) iteration.
 */
void SBWidget::Private::CloseIteration()
{
    qreal opacity = m_pHost->windowOpacity();
    opacity -= m_fadeStep;
    if (opacity <= 0.0)
    {
        opacity = 0.0;
        m_fadeState = FadeNone;
        emit m_pHost->FadeStateChanged(m_fadeState);
    }
    m_pHost->setWindowOpacity(opacity);
    if (m_fadeState == FadeNone)
    {
        m_pHost->close();
    }
}

//------------------------------------------------------------------------------
/**
 * @brief Restarts fade timer.
 */
void SBWidget::Private::RestartFadeTimer()
{
    if (m_fadeTimerID != -1)
    {
        m_pHost->killTimer(m_fadeTimerID);
    }
    m_fadeTimerID = m_pHost->startTimer(FADETIMERSTEP);
}

//------------------------------------------------------------------------------
/**
 * @brief Stops fade timer.
 */
void SBWidget::Private::StopFadeTimer()
{
    if (m_fadeTimerID != -1)
    {
        m_pHost->killTimer(m_fadeTimerID);
        m_fadeTimerID = -1;
    }
}

//------------------------------------------------------------------------------
/**
 * @brief Cancles the fade action.
 */
void SBWidget::Private::FadeCancel(bool fl)
{
    StopFadeTimer();
    if (fl)
    {
        m_pHost->setWindowOpacity(1.0);
        m_pHost->show();
    }
    else
    {
        m_pHost->setWindowOpacity(0.0);
        m_pHost->hide();
    }
}

//------------------------------------------------------------------------------
/**
 * @brief Sets the title bar text.
 * @param title - the title text.
 */
void SBWidget::Private::SetTitleBarText(const QString& title)
{
    m_pTitleBar->SetTitle(title);
}

//------------------------------------------------------------------------------
/**
 * @brief Returns title rectangle for drag operations.
 */
QRect SBWidget::Private::GetTitleRectForDrag() const
{
    QRect result(0, 0, -1, -1);
    if (!m_ignoreMoveFromTitle)
    {
        if (m_ignoreResize)
        {
            result = m_pTitleBar->rect();
        }
        else
        {
            switch (m_titlePos)
            {
                case SBWidget::TopTitleBar:
                    result = m_pTitleBar->rect()
                            .adjusted(BorderWidthLeft() + 1,
                                      BorderWidthTop() + 1,
                                      -BorderWidthRight() - 1, 0);
                    break;
                case SBWidget::BottomTitleBar:
                    result = m_pTitleBar->rect()
                            .adjusted(BorderWidthLeft() + 1,
                                      0, -BorderWidthRight() - 1,
                                      -BorderWidthBottom() - 1);
                    break;
                case SBWidget::LeftTitleBar:
                    result = m_pTitleBar->rect()
                            .adjusted(BorderWidthLeft() + 1,
                                      BorderWidthTop() + 1,
                                      0,
                                      -BorderWidthBottom() - 1);
                    break;
                case SBWidget::RightTitleBar:
                    result = m_pTitleBar->rect()
                            .adjusted(0,
                                      BorderWidthTop() + 1,
                                      -BorderWidthRight() - 1,
                                      -BorderWidthBottom() - 1);
                    break;
            }
        }
    }
    return result;
}
//------------------------------------------------------------------------------
