//==============================================================================
// Copyright: Reksoft Ltd.
//==============================================================================
//
// Author:              $Author:$
// Creation date:       2015.03.11
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
#include "SBToolBarContent_p.h"
#include <qlabel.h>
#include <qgridlayout.h>
#include <qevent.h>


//------------------------------------------------------------------------------
/**
 * @class SBToolBarContentWidget
 * @ingroup Gui
 * @brief The SBToolBarContentWidget class implements a widget that manages
 * a general toolbar content layout. Widgtes without main grid layout do not
 * managed.
 */
//------------------------------------------------------------------------------
/**
 * @brief Constructor.
 */
SBToolBarContentWidget::SBToolBarContentWidget(QWidget* pParent)
    : QWidget(pParent)
    , m_pContent(nullptr)
    , m_pExpand(nullptr)
    , m_managed(false)
{
    QGridLayout* pGrid = new QGridLayout(this);
    pGrid->setContentsMargins(0, 0, 0, 0);
    pGrid->setSpacing(0);
    m_pContent = new QWidget(this);
    pGrid->addWidget(m_pContent, 0, 0);
    QGridLayout* pLabelLayout = new QGridLayout;
    pGrid->addLayout(pLabelLayout, 0, 1);
    pLabelLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding), 0, 0);
    pLabelLayout->setHorizontalSpacing(0);
    pLabelLayout->setContentsMargins(0, 3, 3, 3);
    m_pExpand = new QLabel(this);
    m_pExpand->setText(QString::fromLatin1(">"));
    pLabelLayout->addWidget(m_pExpand, 0, 1);
    m_pExpand->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    m_pExpand->setVisible(false);
    m_pContent->installEventFilter(this);
}

//------------------------------------------------------------------------------
/**
 * @brief Destructor.
 */
SBToolBarContentWidget::~SBToolBarContentWidget()
{
}

//------------------------------------------------------------------------------
/**
 * @brief Returns a pointer to the managed content.
 */
QWidget* SBToolBarContentWidget::GetContent()
{
    return m_pContent;
}

//------------------------------------------------------------------------------
/**
 * @brief Returns the best contents size.
 */
QSize SBToolBarContentWidget::GetBestSize() const
{
    QSize result;
    Q_ASSERT(m_pContent);
    QGridLayout* pGrid = qobject_cast<QGridLayout*>(m_pContent->layout());
    if (pGrid)
    {
        int width = 0;
        int height = 0;
        int count = pGrid->columnCount();
        int visibleCount = 0;
        for (int i = 0; i < count; ++i)
        {
            QLayoutItem* pItem = pGrid->itemAtPosition(0, i);
            Q_ASSERT(pItem);
            QWidget* pWidget = pItem->widget();
            if (pWidget)
            {
                ++visibleCount;
                QSize bestSize = GetBestWidgetSize(pWidget);
                width += bestSize.width();
                height = qMax(height, bestSize.height());
            }
        }
        if (visibleCount)
        {
            width += (visibleCount - 1) * pGrid->horizontalSpacing();
        }
        QMargins margins = pGrid->contentsMargins();
        result.setWidth(width + margins.left() + margins.right());
        result.setHeight(height + margins.top() + margins.bottom());
    }
    return result;
}

//------------------------------------------------------------------------------
/**
 * @brief Reimplemented method.
 * Manages Add/Remove childs of the managed content widget.
 * Manages Show/Hide events of the managed content widget childs.
 */
bool SBToolBarContentWidget::eventFilter(QObject* pWatched, QEvent* pEvent)
{
    QWidget* pWidget = qobject_cast<QWidget*>(pWatched);
    if (pWidget)
    {
        if (pWidget == m_pContent)
        {
            switch (pEvent->type())
            {
                case QEvent::ChildAdded:
                case QEvent::ChildRemoved:
                    contentChildEvent(static_cast<QChildEvent*>(pEvent));
                default:
                    break;
            }
        }
        else if (pWidget->parentWidget() == m_pContent)
        {
            switch (pEvent->type())
            {
                case QEvent::Show:
                case QEvent::Hide:
                    if (pWidget->parent() == m_pContent)
                    {
                        if (!m_managed)
                        {
                            pEvent->ignore();
                            ManageContentLayout(m_pContent->size());
                            return true;
                        }
                    }
                    break;
                default:
                    break;
            }
        }
    }
    return QWidget::eventFilter(pWatched, pEvent);
}

//------------------------------------------------------------------------------
/**
 * @brief Reimplemented method.
 * Runs layout management if it is needed.
 */
void SBToolBarContentWidget::resizeEvent(QResizeEvent* pEvent)
{
    QWidget::resizeEvent(pEvent);
    if (!m_managed)
    {
        ManageContentLayout(pEvent->size());
    }
}

//------------------------------------------------------------------------------
/**
 * @brief Reimplemented method.
 * Sets the event filter for child widgets.
 */
void SBToolBarContentWidget::contentChildEvent(QChildEvent* pEvent)
{
    if (pEvent->added())
    {
        QWidget* pWidget = qobject_cast<QWidget*>(pEvent->child());
        if (pWidget)
        {
            pWidget->installEventFilter(this);
        }
    }
    else if (pEvent->removed())
    {
        QWidget* pWidget = qobject_cast<QWidget*>(pEvent->child());
        if (pWidget)
        {
            pWidget->removeEventFilter(this);
        }
    }
    QWidget::childEvent(pEvent);
}

//------------------------------------------------------------------------------
/**
 * @brief Reimplemented method.
 * Runs layout management if it is needed.
 */
void SBToolBarContentWidget::showEvent(QShowEvent* pEvent)
{
    QWidget::showEvent(pEvent);
    if (!m_managed)
    {
        ManageContentLayout(size());
    }
}

//------------------------------------------------------------------------------
/**
 * @brief Manages a widgte's layout.
 * @param newSize - new widget size.
 */
void SBToolBarContentWidget::ManageContentLayout(const QSize& newSize)
{
    m_managed = true;
    Q_ASSERT(m_pContent);
    QGridLayout* pGrid = qobject_cast<QGridLayout*>(m_pContent->layout());
    if (pGrid)
    {
        int width = GetMinimumSizeHint().width();
        int maxW = newSize.width() - pGrid->contentsMargins().right() - pGrid->contentsMargins().left();
        if (width >= maxW)
        {
            int count = pGrid->columnCount();
            if (count > 0)
            {
                Shrink(width, maxW);
            }
        }
        else
        {
            int count = pGrid->columnCount();
            if (count > 0)
            {
                // go through all widgets and try to show some of them.
                if (!Expand(width, maxW))
                {
                    Shrink(width, maxW);
                }
            }
        }
    }
    m_managed = false;
}

//------------------------------------------------------------------------------
/**
 * @brief Returns minimum size hint for this widget.
 */
QSize SBToolBarContentWidget::GetMinimumSizeHint()
{
    Q_ASSERT(m_pContent);
    QGridLayout* pGrid = qobject_cast<QGridLayout*>(m_pContent->layout());
    if (pGrid)
    {
        int width = 0;
        int height = 0;
        int count = pGrid->columnCount();
        int visibleCount = 0;
        for (int i = 0; i < count; ++i)
        {
            QLayoutItem* pItem = pGrid->itemAtPosition(0, i);
            Q_ASSERT(pItem);
            QWidget* pWidget = pItem->widget();
            if (pWidget)
            {
                if (pWidget->isVisibleTo(parentWidget()))
                {
                    ++visibleCount;
                    width += GetMinimumWidth(pWidget);
                }
            }
            height = qMax(height, pItem->minimumSize().height());
        }
        if (visibleCount)
        {
            width += (visibleCount - 1) * pGrid->horizontalSpacing();
        }
        return QSize(width, height);
    }
    return QSize();
}

//------------------------------------------------------------------------------
/**
 * @brief Returns a size hint of expand widget's part.
 */
QSize SBToolBarContentWidget::GetExpandSizeHint() const
{
    QGridLayout* pGrid = qobject_cast<QGridLayout*>(layout());
    Q_ASSERT(pGrid);
    QLayoutItem* pItem = pGrid->itemAtPosition(0, 1);
    Q_ASSERT(pItem);
    QGridLayout* pLabelLayout = qobject_cast<QGridLayout*>(pItem->layout());
    Q_ASSERT(pLabelLayout);
    QMargins margins = pLabelLayout->contentsMargins();
    QSize result = m_pExpand->minimumSizeHint();
    result.setWidth(result.width() + margins.left() + margins.right());
    result.setHeight(result.height() + margins.top() + margins.bottom());
    return result;
}

//------------------------------------------------------------------------------
/**
 * @brief Shrinks the managed layout.
 * @param width - current size hint width.
 * @param maxWidth - new maximum width.
 * @return True if the managed layout will be expanded.
 */
bool SBToolBarContentWidget::Shrink(int width, int maxWidth)
{
    Q_ASSERT(m_pContent);
    bool shrinked = true;
    QGridLayout* pGrid = qobject_cast<QGridLayout*>(m_pContent->layout());
    if (pGrid)
    {
        int count = pGrid->columnCount();
        if (count > 0)
        {
            QSize expandSizeHint = GetExpandSizeHint();
            maxWidth -= expandSizeHint.width();
            if (width > maxWidth)
            {
                // go through all widgets and try to hide some of them.
                shrinked = false;
                for (int i = count - 1; i >= 0; --i)
                {
                    QLayoutItem* pItem = pGrid->itemAtPosition(0, i);
                    QWidget* pWidget = pItem->widget();
                    if (pWidget)
                    {
                        if (pWidget->isVisible() ||
                            pWidget->isVisibleTo(parentWidget()))
                        {
                            width -= GetMinimumWidth(pWidget);
                            if (i != 0)
                            {
                                width -= pGrid->horizontalSpacing();
                            }
                            shrinked = true;
                            pWidget->setVisible(false);
                            if (maxWidth >= width)
                            {
                                break;
                            }
                        }
                    }
                }
                Q_ASSERT(m_pExpand);
                m_pExpand->setVisible(true);
            }
        }
    }
    return shrinked;
}

//------------------------------------------------------------------------------
/**
 * @brief Expands the managed layout.
 * @param width - current size hint width.
 * @param maxWidth - new maximum width.
 * @return True if the managed layout will be expanded.
 */
bool SBToolBarContentWidget::Expand(int width, int maxWidth)
{
    Q_ASSERT(m_pContent);
    bool expanded = true;
    QGridLayout* pGrid = qobject_cast<QGridLayout*>(m_pContent->layout());
    if (pGrid)
    {
        int count = pGrid->columnCount();
        if (count > 0)
        {
            QSize expandSizeHint = GetExpandSizeHint();
            int expandedMaxW = maxWidth - expandSizeHint.width();
            // go through all widgets and try to show some of them.
            for (int i = 0; i < count && expanded; ++i)
            {
                QLayoutItem* pItem = pGrid->itemAtPosition(0, i);
                QWidget* pWidget = pItem->widget();
                if (pWidget)
                {
                    if (!(pWidget->isVisible() ||
                          pWidget->isVisibleTo(parentWidget())))
                    {
                        expanded = false;
                        width += GetMinimumWidth(pWidget);
                        if (i != 0)
                        {
                            width += pGrid->horizontalSpacing();
                        }
                        if (maxWidth > width)
                        {
                            if (i == count - 1)
                            {
                                // last widget is visible we must hide expand label
                                expanded = true;
                                pWidget->setVisible(true);
                                m_pExpand->setVisible(false);
                            }
                            else
                            {
                                // non last widget is visible we must
                                // check other maxW
                                if (expandedMaxW > width)
                                {
                                    expanded = true;
                                    pWidget->setVisible(true);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return expanded;
}

//------------------------------------------------------------------------------
/**
 * @brief Returns minimum width for a managed widget.
 * @param pWidget - a pointer to the widget.
 */
int SBToolBarContentWidget::GetMinimumWidth(QWidget* pWidget)
{
    Q_ASSERT(pWidget);
    QSize hint = pWidget->minimumSizeHint();
    QSize size = pWidget->minimumSize();
    if (size.width() == 0 && hint.width() != 0)
    {
        return hint.width();
    }
    return size.width();
}

//------------------------------------------------------------------------------
/**
 * @brief Returns the best size of a widget.
 * @param pWidget - a pointer to the widget.
 */
QSize SBToolBarContentWidget::GetBestWidgetSize(QWidget* pWidget)
{
    Q_ASSERT(pWidget);
    QSize hint = pWidget->sizeHint();
    QSize maxSize = pWidget->maximumSize();
    QSize minSize = pWidget->minimumSize();
    int width = qBound(minSize.width(), hint.width(), maxSize.width());
    int height = qBound(minSize.height(), hint.height(), maxSize.height());
    return QSize(width, height);
}
//------------------------------------------------------------------------------
