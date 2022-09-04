#include "FallingBalls.h"

void FallingBalls::initWindow()
{
    std::ifstream ifs("Config\\window.ini");
    std::string window_title = "None";
    sf::VideoMode window_bounds(800, 600, 32);
    unsigned framerate_limit = 60;
    bool vertical_sync_enabled = false;
    if (ifs)
    {
        std::getline(ifs, window_title);
        ifs >> window_bounds.width >> window_bounds.height >> window_bounds.bitsPerPixel;
        ifs >> framerate_limit;
        ifs >> vertical_sync_enabled;
        ifs.close();
    }
    else
    {
        throw std::logic_error("Could not open window.ini file");
    }
    window = std::make_unique<sf::RenderWindow>(window_bounds, window_title);
    window->setFramerateLimit(framerate_limit);
    window->setVerticalSyncEnabled(vertical_sync_enabled);
}

void FallingBalls::initGround()
{
    groundHeight = 70;
    ground.setSize(sf::Vector2f(window->getSize().x, window->getSize().y - groundHeight));
    ground.setPosition(sf::Vector2f(0, window->getSize().y - groundHeight));
    ground.setFillColor(sf::Color::Black);
}

void FallingBalls::initBalls(const size_t& ballNumber)
{
    Ball ball(30,40);
    ball.setHeight(700,groundHeight,window->getSize().y);
    ball.setFillColor(sf::Color::Red);
    Balls.push_back(ball);
}

FallingBalls::FallingBalls(size_t ballNumber, unsigned long long gravity)
{
    initWindow();
    initGround();
    updateDt();
    setGravity(gravity);   
    initBalls(ballNumber);
}

FallingBalls::~FallingBalls()
{
}

double FallingBalls::getGravity() const
{
	return gravity;
}

void FallingBalls::setGravity(unsigned long long newGravity)
{
	gravity = newGravity;
}

size_t FallingBalls::getBallNumber() const
{
    return 0;
}

float FallingBalls::getGroundHeight() const
{
    return groundHeight;
}

void FallingBalls::setGroundHeight(float newGroundHeight)
{
    groundHeight = newGroundHeight;
}

void FallingBalls::updateDt()
{
	dt = animationClock.restart().asSeconds();
}

void FallingBalls::update()
{
    //updateDt
    updateDt();

    //update ground
    if (ground.getSize().y != groundHeight)
    {
        ground.setSize(sf::Vector2f(ground.getSize().x,groundHeight));
        ground.setPosition(sf::Vector2f(0, window->getSize().y - groundHeight));
    }

    //update balls
    for (auto& ball : Balls)
    {
        ball.updateFallingBall(dt,gravity);
    }
}

void FallingBalls::render()
{
    //clear window
    window->clear(sf::Color(0,204,255));

    //render stuff
    window->draw(ground);
    for (auto& ball : Balls)
    {
        window->draw(ball);
    }

    //display stuff
    window->display();
}

void FallingBalls::startAnimation()
{
    while (window->isOpen())
    {
       while (window->pollEvent(event))
       {
          if (event.type == sf::Event::Closed)
          {
                window->close();
          }
       }
      update();
      render();
    }
}
