//==============================================================================
// Copyright: Reksoft Ltd.
//==============================================================================
//
// Author:              $Author:$
// Creation date:       2015.03.10
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
#ifndef SBPANEL_H
#define SBPANEL_H


#include <SBWidget.h>


class GUI_DEF SBPanel
        : public SBWidget
{
    Q_OBJECT        
    Q_PROPERTY(bool floating READ IsFloating WRITE SetFloating NOTIFY FloatingChanged)
    public:

        SBPanel(QWidget* pParent = nullptr,
                SBWidget::TitlePosition titlePos = SBWidget::TopTitleBar);
        ~SBPanel();

        bool IsFloating() const;
        void SetFloating(bool);

    signals:

        /**
         * @brief Emits when the floating state has changed.
         */
        void FloatingChanged(bool);

    protected:

        void closeEvent(QCloseEvent*);

    private:

        struct Private;
        /// A pointer to a private implementation.
        Private* m_pPrivate;
};//class SBPanel
#endif // SBPANEL_H

