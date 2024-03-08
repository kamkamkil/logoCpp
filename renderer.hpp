#include <iostream>
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <cairomm/context.h>
#include <gtkmm/drawingarea.h>
#include <functional>

constexpr double startingX = 100;
constexpr double startingY = 100;


class Renderer : public Gtk::DrawingArea
{
private:
	/* data */
public:
	Renderer(/* args */);
	~Renderer();
	void goUp(int dis);
	void goDown(int dis);
	void goRight(int dis);
	void goLeft(int dis);
	void rotate(float angle);
	void setAngle(float angle);
	void penUp();
	void penDown();
	static Renderer *get();

protected:
	void render(const Cairo::RefPtr<Cairo::Context> &cr, int width, int height);

private:
	void resetCoordinate();
	static Renderer *renderer;
	std::vector<std::function<void(Cairo::RefPtr<Cairo::Context>)>> renderQueue;

	double currentX = startingX;
	double currentY = startingY;
};

Renderer *Renderer::renderer = nullptr;
