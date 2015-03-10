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
#include <qdockwidget.h>


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

    SBWidget widget1;
    widget1.setWindowTitle("w1");
    widget1.show();
    SBWidget widget2;
    widget2.setWindowTitle("w2");
    widget2.show();
    QDockWidget panel;
    panel.setWindowTitle("panel");
    panel.show();
    panel.setFloating(true);

    man.Add(&widget1);
    man.Add(&widget2);
    man.AddPanel(&panel);
    return app.exec();
}
//------------------------------------------------------------------------------


