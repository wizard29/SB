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
#ifndef SBTOOLBARCONTENT_P_H
#define SBTOOLBARCONTENT_P_H


#include <qwidget.h>


class QLabel;


class SBToolBarContentWidget
        : public QWidget
{
    Q_OBJECT
    public:

        SBToolBarContentWidget(QWidget* pParent);
        ~SBToolBarContentWidget();

        QWidget* GetContent();
        QSize GetBestSize() const;

    protected:

        bool eventFilter(QObject*, QEvent*);
        void resizeEvent(QResizeEvent* pEvent);
        void contentChildEvent(QChildEvent* pEvent);
        void showEvent(QShowEvent* pEvent);

    private:

        void ManageContentLayout(const QSize& newSize);
        QSize GetMinimumSizeHint();
        QSize GetExpandSizeHint() const;
        bool Shrink(int width, int maxWidth);
        bool Expand(int width, int maxWidth);
        static int GetMinimumWidth(QWidget* pWidget);
        static QSize GetBestWidgetSize(QWidget* pWidget);

    private:

        /// A pointer to the managed content.
        QWidget* m_pContent;
        /// A pointer to the expand label.
        QLabel* m_pExpand;
        /// Sets inside the ManageLayout function to prevents processing events
        /// into the eventFilter call.
        bool m_managed;
};// class SBToolBarContentWidget
#endif // SBTOOLBARCONTENT_P_H

