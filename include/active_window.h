#ifndef ACTIVE_WINDOW_H
#define ACTIVE_WINDOW_H

#include <X11/Xlib.h>
#include <string>

namespace SPL
{
    class ActiveWindow
    {
    private:
        const int MAXLEN = 1024;
        const char *_NET_ACTIVE_WINDOW = "_NET_ACTIVE_WINDOW";
        const char *_NET_WM_PID = "_NET_WM_PID";
        Display *display;
        Window root_window;
        unsigned char *prop;
        void get_string_property(const char *name, Window window);
        unsigned long get_long_property(const char *name, Window window);
        unsigned long get_active_window_pid();

    public:
        ActiveWindow();
        std::string get_active_window_name();
    };
}
#endif