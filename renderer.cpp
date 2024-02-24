#include <iostream>

class renderer
{
private:
    /* data */
public:
    renderer(/* args */);
    void goUp(float dis);
    void goDown(float dis);
    void goRight(float dis);
    void goLeft(float dis);
    void rotate(float angle);
    void setAngle(float angle);
    void penUp();
    void penDown();
    ~renderer();
};

renderer::renderer(/* args */)
{
}

void renderer::goUp(float dis)
{
    std::cout << "go up " << dis << std::endl;
}

void renderer::goDown(float dis)
{
    std::cout << "go down " << dis << std::endl;
}

void renderer::goRight(float dis)
{
    std::cout << "go right " << dis << std::endl;
}

void renderer::goLeft(float dis)
{
    std::cout << "go left " << dis << std::endl;
}

void renderer::rotate(float angle)
{
    std::cout << "rotate " << angle << std::endl;
}

void renderer::setAngle(float angle)
{
    std::cout << "rotate " << angle << std::endl;
}

void renderer::penUp()
{
    std::cout <<"pen up" <<std::endl; 
}

void renderer::penDown()
{
    std::cout <<"pen up" <<std::endl; 
}

renderer::~renderer()
{
}
