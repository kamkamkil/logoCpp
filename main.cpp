#include "interpreter.cpp"
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm/drawingarea.h>

#include <gtkmm/drawingarea.h>

// class MyArea : public Gtk::DrawingArea
// {
// public:
//   MyArea();
//   virtual ~MyArea();

// protected:
//   void on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);
// };

class ExampleWindow : public Gtk::Window
{
public:
    ExampleWindow();

protected:
    Renderer *m_area;
};

ExampleWindow::ExampleWindow()
{
    m_area = Renderer::get();
    set_title("DrawingArea");
    set_child(*m_area);
}

int main(int argc, char **argv)
{
    auto app = Gtk::Application::create("org.gtkmm.example");
    Interpreter in("../../testFile.txt");
    in.interpret();

    return app->make_window_and_run<ExampleWindow>(argc, argv);
}
