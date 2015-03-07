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
#include <qgridlayout.h>
#include <qlabel.h>
#include <qstyleoption.h>


//------------------------------------------------------------------------------
const QMargins SBTitleBar::Private::BORDERMARGINS = QMargins(5, 0, 5, 0);

//------------------------------------------------------------------------------
/**
 * @struct SBTitleBar::Private
 * @ingroup Gui
 * @brief The SBTitleBar::Private struct contains the internal title bar data
 * and provides the accessory functionality.
 */
//------------------------------------------------------------------------------
/**
 * @brief Constructor.
 * @param pHost - a pointer to a host object. Must not be a null pointer.
 */
SBTitleBar::Private::Private(SBTitleBar* pHost)
    : m_pHost(pHost)
    , m_pText(nullptr)
    , m_pIcon(nullptr)
    , m_pHRZLayout(nullptr)
    , m_pVRTLayout(nullptr)
    , m_pContent(nullptr)
{
    Q_ASSERT(m_pHost);
    QGridLayout* pGrid = new QGridLayout(m_pHost);
    pGrid->setSpacing(0);
    pGrid->setMargin(0);
    m_pContent = new QWidget(m_pHost);
    m_pContent->setObjectName("TITLECONTENT");
    m_pContent->setMouseTracking(true);
    pGrid->addWidget(m_pContent);
    pGrid = new QGridLayout(m_pContent);
    m_pIcon = new QLabel(m_pContent);
    m_pIcon->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    m_pIcon->setVisible(false);
    m_pIcon->setCursor(Qt::ArrowCursor);
    QStyle* pStyle = m_pHost->style();
    if (pStyle)
    {
        QStyleOption opt;
        opt.initFrom(m_pHost);
        int size = pStyle->pixelMetric(QStyle::PM_SmallIconSize, &opt, m_pHost);
        m_pIcon->setMaximumSize(size, size);
    }
    m_pText = new QLabel(m_pContent);
    m_pText->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    pGrid->setMargin(0);    
    pGrid->setContentsMargins(BORDERMARGINS);
    pGrid->setSpacing(3);
    pGrid->setVerticalSpacing(0);
#ifndef Q_OS_MAC
    pGrid->addWidget(m_pIcon, 0, 0);
    pGrid->addWidget(m_pText, 0, 1);
    pGrid->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Maximum), 0, 2);
    m_pHRZLayout = new QGridLayout;
    m_pVRTLayout = new QGridLayout;
    pGrid->addLayout(m_pHRZLayout, 0, 3);
    pGrid->addLayout(m_pVRTLayout, 1, 0, 1, 4);
    m_pHRZLayout->setContentsMargins(0, 0, 0, 0);
    m_pHRZLayout->setSpacing(3);
    m_pVRTLayout->setContentsMargins(0, 0, 0, 0);
    m_pVRTLayout->setSpacing(0);
    m_pHost->setAttribute(Qt::WA_TranslucentBackground);
#else// mac os layout
    m_pHRZLayout = new QGridLayout;
    m_pVRTLayout = new QGridLayout;
    pGrid->addLayout(m_pHRZLayout, 0, 0);
    pGrid->addWidget(m_pIcon, 0, 1);
    pGrid->addWidget(m_pText, 0, 2);
    pGrid->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Maximum), 0, 3);
    pGrid->addLayout(m_pVRTLayout, 1, 0, 1, 4);
    m_pHRZLayout->setContentsMargins(0, 0, 0, 0);
    m_pHRZLayout->setSpacing(3);
    m_pVRTLayout->setContentsMargins(0, 0, 0, 0);
    m_pVRTLayout->setSpacing(0);
    m_pHost->setAttribute(Qt::WA_TranslucentBackground);
#endif
}

//------------------------------------------------------------------------------
/**
 * @brief Destructor.
 */
SBTitleBar::Private::~Private()
{
}
//------------------------------------------------------------------------------
