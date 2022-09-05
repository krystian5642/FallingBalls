#include "FallingBalls.h"

int main()
{
    try
    {
        FallingBalls animationBalls;
        for (int i = 0; i <400; i++)
        {
            Ball ball(5.0, 5.0,sf::Vector2f(rand() % 200- 100, rand() % 300));
            ball.setPosition(rand()%1270, rand()%80+700, animationBalls.getGround(), animationBalls.getGravity());
            ball.setFillColor(sf::Color::Green);
            animationBalls.addBall(ball);
        }
        animationBalls.startAnimation();
    }
    catch (std::exception& error)
    {
        std::cerr << error.what() << std::endl;
    }
	return 0;
}