#include <iostream>
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <cairomm/context.h>
#include <gtkmm/drawingarea.h>
#include <functional>

class Renderer : public Gtk::DrawingArea
{
private:
	/* data */
public:
	Renderer(/* args */);
	~Renderer();
	void goUp(float dis);
	void goDown(float dis);
	void goRight(float dis);
	void goLeft(float dis);
	void rotate(float angle);
	void setAngle(float angle);
	void penUp();
	void penDown();
	static Renderer *get();
	int main(int argc, char **argv);

protected:
	void render(const Cairo::RefPtr<Cairo::Context> &cr, int width, int height);

private:
	static Renderer *renderer;
	std::vector<std::function<void(Cairo::RefPtr<Cairo::Context>)>> renderQueue;
	double currentX = 0;
	double currentY = 0;
};

Renderer *Renderer::renderer = nullptr;
class ExampleWindow : public Gtk::Window
{
public:
	ExampleWindow();

protected:
	Renderer m_area;
};

ExampleWindow::ExampleWindow()
{
	set_title("DrawingArea");
	set_child(m_area);
}

Renderer::Renderer(/* args */)
{
	set_draw_func(sigc::mem_fun(*this, &Renderer::render));
	renderQueue.push_back([](Cairo::RefPtr<Cairo::Context> context)
						  { context->move_to(0, 0); });
}

void Renderer::goUp(float dis)
{
	renderQueue.push_back([&](Cairo::RefPtr<Cairo::Context> context)
						  { context->line_to(currentX + dis, currentY);
												currentX += dis; });
	std::cout << "go up " << dis << std::endl;
}

void Renderer::goDown(float dis)
{
	renderQueue.push_back([&](Cairo::RefPtr<Cairo::Context> context)
						  { context->line_to(currentX - dis, currentY);
												currentX -= dis; });
	std::cout << "go down " << dis << std::endl;
}

void Renderer::goRight(float dis)
{
	renderQueue.push_back([&](Cairo::RefPtr<Cairo::Context> context)
						  { context->line_to(currentX, currentY + dis);
												currentY += dis; });
	std::cout << "go right " << dis << std::endl;
}

void Renderer::goLeft(float dis)
{
	renderQueue.push_back([&](Cairo::RefPtr<Cairo::Context> context)
						  { context->line_to(currentX, currentY - dis);
												currentY -= dis; });
	std::cout << "go left " << dis << std::endl;
}

void Renderer::rotate(float angle)
{
	std::cout << "rotate " << angle << std::endl;
}

void Renderer::setAngle(float angle)
{
	std::cout << "rotate " << angle << std::endl;
}

void Renderer::penUp()
{
	std::cout << "pen up" << std::endl;
}

void Renderer::penDown()
{
	std::cout << "pen up" << std::endl;
}

void Renderer::render(const Cairo::RefPtr<Cairo::Context> &context, int width, int height)
{
	context->set_line_width(10.0);

	// draw red lines out from the center of the window
	context->set_source_rgb(0.8, 0.0, 0.0);
	renderQueue.push_back([](Cairo::RefPtr<Cairo::Context> context)
						  { context->stroke(); });
	for (auto &&stroke : renderQueue)
	{
		stroke(context);
	}
}

Renderer *Renderer::get()
{
	if (renderer == nullptr)
	{
		renderer = new Renderer;
	}

	return renderer;
}

int Renderer::main(int argc, char **argv)
{
	auto app = Gtk::Application::create("org.gtkmm.example");

	return app->make_window_and_run<ExampleWindow>(argc, argv);
}

Renderer::~Renderer()
{
}
