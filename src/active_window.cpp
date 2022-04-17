#include "../include/active_window.h"
#include <sstream>
#include <fstream>

SPL::ActiveWindow::ActiveWindow()
{
    display = XOpenDisplay(0);
    if (!display)
        printf("Error opening display\n");
    root_window = DefaultRootWindow(display);
}

void SPL::ActiveWindow::get_string_property(const char *name, Window window)
{
    Atom property, req_property = 0L, actual_type;
    int actual_format;
    unsigned long ntimes, bytes_after;

    property = XInternAtom(display, name, 1);
    XGetWindowProperty(display, window, property, 0, MAXLEN, 0,req_property,
			 				&actual_type, &actual_format, &ntimes, &bytes_after, &prop);  
}

unsigned long SPL::ActiveWindow::get_long_property(const char *name, Window window)
{
    get_string_property (name, window);
    return (unsigned long) (prop[0] + (prop[1] << 8) + (prop[2] << 16) + (prop[3] << 24));
}

unsigned long SPL::ActiveWindow::get_active_window_pid()
{
    unsigned long window = get_long_property (_NET_ACTIVE_WINDOW, root_window);
    if (!window)
        return window;
    return get_long_property(_NET_WM_PID, window);
}

std::string SPL::ActiveWindow::get_active_window_name()
{
    unsigned long pid = get_active_window_pid();

    if (pid == 0)
        return "-1";
    
    std::stringstream filename;
    filename << "/proc/" << pid << "/comm";
    
    std::fstream file;
    file.open(filename.str(), std::ios::in);

    if (file.is_open())
    {
        std::string comm;
        file >> comm;

        return comm;
    }
    return "-1";
}