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
    SBWidget widget;
    widget.show();
    return app.exec();
}
//------------------------------------------------------------------------------


