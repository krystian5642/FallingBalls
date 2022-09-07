#include "FallingBalls.h" 

sf::Vector2u windowSize;

void FallingBalls::initWindow()
{
    srand(time(NULL));
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
    windowSize = window->getSize();
}

void FallingBalls::initGround()
{
    ground.setSize(sf::Vector2f(window->getSize().x,70));
    ground.setPosition(sf::Vector2f(0, window->getSize().y - 70));
    ground.setFillColor(sf::Color::Black);
}

FallingBalls::FallingBalls(double gravity)
{
    initWindow();
    initGround();
    updateDt();
    setGravity(gravity);   
    setCoefficientOfFriction(0);
}

FallingBalls::~FallingBalls()
{
}

double FallingBalls::getGravity() const
{
	return gravity;
}

void FallingBalls::setGravity(double newGravity)
{
	gravity = newGravity;
}

float FallingBalls::getCoefficientOfFriction() const
{
    return coefficientOfFriction;
}

void FallingBalls::setCoefficientOfFriction(float newCoefficientOfFriction)
{
    if (newCoefficientOfFriction < 0 || newCoefficientOfFriction > 1)
    {
        throw std::logic_error("newCoefficientOfFriction cannot be less than 0 and greater than 1");
    }
    coefficientOfFriction = newCoefficientOfFriction;
}

size_t FallingBalls::getBallNumber() const
{
    return Balls.size();
}

const sf::RectangleShape& FallingBalls::getGround() const
{
    return ground;
}

void FallingBalls::setGround(const sf::RectangleShape& newGround)
{
    ground = newGround;
}

void FallingBalls::updateDt()
{
	dt = animationClock.restart().asSeconds();
}

void FallingBalls::update()
{
    //it updates ball collisions , it changes their speed 
    updateBallCollisions();

    //updateDt
    updateDt();

    //update balls
    for (auto& ball : Balls)
    {
        ball.updateFallingBall(dt,ground,gravity,coefficientOfFriction);
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

void FallingBalls::addBall(const Ball& newBall)
{
    Balls.push_back(newBall);
}

void FallingBalls::deleteBall(auto& ball)
{
    Balls.erase(ball);
}

void FallingBalls::updateBallCollisions()
{
    float distance;
    float collisionDistance;
    for (auto firstBall = Balls.begin(); firstBall != Balls.end(); firstBall++)
    {
        for (auto secondBall = firstBall + 1; secondBall != Balls.end(); secondBall++)
        {
            distance = vectorLenght(sf::Vector2f(firstBall->getPosition().x - secondBall->getPosition().x,
                  firstBall->getPosition().y - secondBall->getPosition().y));

            sf::Vector2f Vd(firstBall->getPosition().x - secondBall->getPosition().x,
                + firstBall->getPosition().y - secondBall->getPosition().y);

            collisionDistance = firstBall->getRadius() + secondBall->getRadius();
            sf::Vector2f Vr(Vd.x/distance * collisionDistance,Vd.y/distance * collisionDistance);

            if (distance < collisionDistance)
            {
                sf::Vector2f correctionVector = Vr - Vd + sf::Vector2f(Vd.x / distance, Vd.y / distance);
                firstBall->move(correctionVector);
                setSpeedAfterCollision(firstBall, secondBall);
            }
        }
    }
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
