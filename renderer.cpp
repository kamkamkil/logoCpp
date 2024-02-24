#include <iostream>

class Renderer
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
private:
    static Renderer* renderer;
};

Renderer::Renderer(/* args */)
{
}

void Renderer::goUp(float dis)
{
    std::cout << "go up " << dis << std::endl;
}

void Renderer::goDown(float dis)
{
    std::cout << "go down " << dis << std::endl;
}

void Renderer::goRight(float dis)
{
    std::cout << "go right " << dis << std::endl;
}

void Renderer::goLeft(float dis)
{
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
    std::cout <<"pen up" <<std::endl; 
}

void Renderer::penDown()
{
    std::cout <<"pen up" <<std::endl; 
}

Renderer *Renderer::get()
{
    if (renderer == nullptr)
    {
        renderer = new Renderer;
    }
    
    return renderer;
}

Renderer::~Renderer()
{
}
