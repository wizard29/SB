//==============================================================================
// Copyright: Reksoft Ltd.
//==============================================================================
//
// Author:              $Author:$
// Creation date:       2015.03.04
// Modification date:   $Date$
// Module:              Application
// Platform:            MS Windows 7, Linux, MAC OS X 10.6.x
//
//------------------------------------------------------------------------------
// Note:
//------------------------------------------------------------------------------
// Warning:
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
#include <SBApplication.h>
#include <SBWidget.h>
#include <SBMDIManager.h>
#include <SBPanel.h>
#include <SBToolBar.h>

#include "ui_toolbar.h"


//------------------------------------------------------------------------------
/**
 * @brief The application entry point.
 * @param argc - an application argument count.
 * @param argv - an application argument list.
 * @return 0 if the application completes successfully.
 */
int main(int argc, char** argv)
{
    SBApplication app(argc, argv);
    app.LoadTheme();
    SBMDIManager man;

    SBWidget widget1(nullptr);
    widget1.setWindowTitle("w1");
    widget1.AddMaximizeButton();
    widget1.AddRestoreButton();
    widget1.AddMinimizeButton();
    widget1.show();    
    SBWidget widget2;
    widget2.setWindowTitle("w2");
    widget2.AddMaximizeButton();
    widget2.AddRestoreButton();
    widget2.AddMinimizeButton();
    widget2.show();    

    SBPanel panel1;
    panel1.setWindowTitle("panel 1");
    panel1.SetFloating(true);
    panel1.setVisible(true);

    SBToolBar toolBar1;
    toolBar1.setWindowTitle("toolbar 1");
    toolBar1.SetFloating(true);
    toolBar1.setVisible(true);

    man.Add(&widget1);
    man.Add(&widget2);
    man.Add(&panel1);
    man.Add(&toolBar1);

    Ui::ToolBar ui;
    ui.setupUi(toolBar1.GetManagetContent());
    toolBar1.FitToBestSize();
    return app.exec();
}
//------------------------------------------------------------------------------


