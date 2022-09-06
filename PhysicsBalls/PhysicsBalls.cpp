#include "FallingBalls.h"

int main()
{
    try
    {
        FallingBalls animationBalls(272);
        for (int i = 0; i <3; i++)
        {
            Ball ball(90, 5.0,sf::Vector2f(rand() % 90-50,60));
            ball.setPosition(rand()%1270, rand()%80+500, animationBalls.getGround(), animationBalls.getGravity());
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