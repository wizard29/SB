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
#include "SBTitleBar_p.h"
#include <qevent.h>
#include <qlabel.h>
#include <qtoolbutton.h>
#include <qgridlayout.h>


//------------------------------------------------------------------------------
/**
 * @class SBTitleBar
 * @ingroup Gui
 * @brief The SBTitleBar class is title bar widget. It widget gives the access
 * to customization of title bar.
 */
//------------------------------------------------------------------------------
/**
 * @brief Constructor.
 */
SBTitleBar::SBTitleBar(QWidget* pParent)
    : QWidget(pParent)
    , m_pPrivate(nullptr)
{
    m_pPrivate = new Private(this);
}

//------------------------------------------------------------------------------
/**
 * @brief Destructor.
 */
SBTitleBar::~SBTitleBar()
{
    Q_ASSERT(m_pPrivate);
    delete m_pPrivate;
}

//------------------------------------------------------------------------------
/**
 * @brief Sets the title bar title text.
 * @param - a new title text.
 */
void SBTitleBar::SetTitle(const QString& text)
{
    m_pPrivate->m_pText->setText(text);
}

//------------------------------------------------------------------------------
/**
 * @brief Sets the title icon.
 * @param icon - the title icon.
 */
void SBTitleBar::SetIcon(const QIcon& icon)
{
    if (!icon.isNull())
    {
        int size = m_pPrivate->m_pIcon->maximumWidth();
        m_pPrivate->m_pIcon->setPixmap(icon.pixmap(size, size));
        m_pPrivate->m_pIcon->setVisible(true);
    }
    else
    {
        m_pPrivate->m_pIcon->setPixmap(QPixmap());
        m_pPrivate->m_pIcon->setVisible(false);
    }
}

//------------------------------------------------------------------------------
/**
 * @brief Replaces a background widget.
 * @param pWidget - a pointer to a widget.
 */
void SBTitleBar::ReplaceBackground(QWidget* pWidget)
{
    Q_ASSERT(m_pPrivate);
    Q_ASSERT(m_pPrivate->m_pContent);
    Q_ASSERT(pWidget);    
    QGridLayout* pGrid = qobject_cast<QGridLayout*>(m_pPrivate->m_pContent->layout());
    Qt::WindowFlags iconFlags = m_pPrivate->m_pIcon->windowFlags();
    Qt::WindowFlags textFlags = m_pPrivate->m_pText->windowFlags();
    bool iconVisibility = m_pPrivate->m_pIcon->isVisible();
    bool textVisibility = m_pPrivate->m_pText->isVisible();
    if (pGrid)
    {
        // remove all child widgets from the content layout.
        pGrid->removeWidget(m_pPrivate->m_pIcon);
        pGrid->removeWidget(m_pPrivate->m_pText);
        pGrid->removeItem(m_pPrivate->m_pHRZLayout);
        m_pPrivate->m_pHRZLayout->setParent(NULL);
        pGrid->removeItem(m_pPrivate->m_pVRTLayout);
        m_pPrivate->m_pVRTLayout->setParent(NULL);
    }
    m_pPrivate->m_pIcon->setParent(pWidget, iconFlags);
    m_pPrivate->m_pIcon->setVisible(iconVisibility);
    m_pPrivate->m_pText->setParent(pWidget, textFlags);
    m_pPrivate->m_pText->setVisible(textVisibility);
    int count = m_pPrivate->m_leftWidgets.size();
    for (int i = 0; i < count; ++i)
    {
        QWidget* pChild = m_pPrivate->m_leftWidgets[i];
        if (pChild)
        {
            Qt::WindowFlags flags = pChild->windowFlags();
            bool isVisible = pChild->isVisible();
            pChild->setParent(pWidget, flags);
            pChild->setVisible(isVisible);
        }
    }
    count = m_pPrivate->m_rightWidgets.size();
    for (int i = 0; i < count; ++i)
    {
        QWidget* pChild = m_pPrivate->m_rightWidgets[i];
        if (pChild)
        {
            Qt::WindowFlags flags = pChild->windowFlags();
            bool isVisible = pChild->isVisible();
            pChild->setParent(pWidget, flags);
            pChild->setVisible(isVisible);
        }
    }
    if (pWidget->layout())
    {
        delete pWidget->layout();
    }
    pGrid = new QGridLayout(pWidget);
    pGrid->setMargin(0);    
    pGrid->setContentsMargins(Private::BORDERMARGINS);
    pGrid->setSpacing(3);
    pGrid->setVerticalSpacing(1);
#ifndef Q_OS_MAC
    pGrid->addWidget(m_pPrivate->m_pIcon, 0, 0);
    pGrid->addWidget(m_pPrivate->m_pText, 0, 1);
    pGrid->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Maximum), 0, 2);
    pGrid->addLayout(m_pPrivate->m_pHRZLayout, 0, 3);
    pGrid->addLayout(m_pPrivate->m_pVRTLayout, 1, 0, 1, 4);
#else // mac os layout
    pGrid->addLayout(m_pPrivate->m_pHRZLayout, 0, 0);
    pGrid->addWidget(m_pPrivate->m_pIcon, 0, 1);
    pGrid->addWidget(m_pPrivate->m_pText, 0, 2);
    pGrid->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Maximum), 0, 3);
    pGrid->addLayout(m_pPrivate->m_pVRTLayout, 1, 0, 1, 4);
#endif
    pGrid = qobject_cast<QGridLayout*>(layout());
    if (pGrid)
    {
        pGrid->addWidget(pWidget);
    }
    Qt::WindowFlags flags = m_pPrivate->m_pContent->windowFlags();
    delete m_pPrivate->m_pContent;
    m_pPrivate->m_pContent = pWidget;
    m_pPrivate->m_pContent->setObjectName("TITLECONTENT");
    pWidget->setParent(this, flags);
    pWidget->setMouseTracking(true);
}

//------------------------------------------------------------------------------
/**
 * @brief Adds button to the title bar.
 * @param icon - the button icon.
 * @param align - the button aligment.
 * @param toolTip - the button tool tip.
 * @return A pointer to the inserted button.
 */
QToolButton* SBTitleBar::AddButton(const QIcon& icon, Qt::Alignment align,
                                   const QString& toolTip)
{    
    QToolButton* pBtn = new QToolButton(m_pPrivate->m_pContent);
    pBtn->setIcon(icon);    
    pBtn->setToolTip(toolTip);    
    AddWidget(pBtn, align);
    return pBtn;
}

//------------------------------------------------------------------------------
/**
 * @brief Adds button to the title bar.
 * @param align - the button aligment.
 * @param toolTip - the button tool tip.
 * @return A pointer to the inserted button.
 */
QToolButton* SBTitleBar::AddButton(Qt::Alignment align, const QString& toolTip)
{
    QToolButton* pBtn = new QToolButton(m_pPrivate->m_pContent);
    pBtn->setToolTip(toolTip);
    AddWidget(pBtn, align);
    return pBtn;
}

//------------------------------------------------------------------------------
/**
 * @brief Adds widget to the title bar.
 * @param pWidget - a pointer to the widget.
 * @param align - the widget aligment.
 */
void SBTitleBar::AddWidget(QWidget* pWidget, Qt::Alignment align)
{    
    if (align == Qt::AlignBottom)
    {
        m_pPrivate->m_pVRTLayout->addWidget(pWidget, m_pPrivate->m_bottomWidgets.size(), 0);
        m_pPrivate->m_bottomWidgets.append(pWidget);
    }
    else if (align == Qt::AlignLeft)
    {
        m_pPrivate->m_pHRZLayout->addWidget(pWidget, 0, m_pPrivate->m_leftWidgets.size());
        m_pPrivate->m_leftWidgets.append(pWidget);
    }
    else if (align)
    {
        m_pPrivate->m_pHRZLayout->addWidget(pWidget, 0, 1000 - m_pPrivate->m_rightWidgets.size());
        m_pPrivate->m_rightWidgets.append(pWidget);
    }
    pWidget->setCursor(Qt::ArrowCursor);
}

//------------------------------------------------------------------------------
/**
 * @brief Sets margins for the content part of the title bar.
 * @param left - left margin.
 * @param top - top margin.
 * @param right - right margin.
 * @param bottom - bottom margin.
 */
void SBTitleBar::SetContentsMargins(int left, int top, int right, int bottom)
{
    QGridLayout* pGrid = qobject_cast<QGridLayout*>(m_pPrivate->m_pContent->layout());
    if (pGrid)
    {
        pGrid->setContentsMargins(left, top, right, bottom);
    }
}

//------------------------------------------------------------------------------
/**
 * @brief Shows/hides title bar label.
 */
void SBTitleBar::SetTitleVisible(bool state)
{
    Q_ASSERT(m_pPrivate);
    m_pPrivate->m_pText->setVisible(state);
}

//------------------------------------------------------------------------------
/**
 * @brief Shows/hides title bar icon.
 */
void SBTitleBar::SetIconVisible(bool state)
{
    Q_ASSERT(m_pPrivate);
    m_pPrivate->m_pIcon->setVisible(state);
}

//------------------------------------------------------------------------------
/**
 * @brief Double click event handler.
 * @see QWidget::mouseDoubleClickEvent for more details.
 */
void SBTitleBar::mouseDoubleClickEvent(QMouseEvent* pEvent)
{
    emit DoubleClicked(pEvent->button());
    QWidget::mouseDoubleClickEvent(pEvent);
}
//------------------------------------------------------------------------------
