#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Window.H>

class Window : Fl_Window
{
    Fl_Button *fl_button;
    Fl_Input *fl_input;
    Fl_Output *fl_output;

public:
    Window(int, int, const char *);
    ~Window();

private:
    static auto copy(Fl_Widget *, void *) -> void;
};

Window::Window(int width, int height, const char *title) : Fl_Window(width, height, title)
{
    fl_button = new Fl_Button(0, 0, 50, 25, "copy");
    fl_input = new Fl_Input(50, 50, 350, 25, "input:");
    fl_output = new Fl_Output(50, 100, 350, 25, "output:");
    fl_button->callback(copy, this);
    show();
}

Window::~Window()
{
    delete fl_button;
    delete fl_input;
    delete fl_output;
}

auto Window::copy(Fl_Widget *, void *vp) -> void
{
    Window *win = (Window *)vp;
    win->fl_output->value(win->fl_input->value());
}

auto main() -> int
{
    new Window(500, 250, "^o^");
    return Fl::run();
}