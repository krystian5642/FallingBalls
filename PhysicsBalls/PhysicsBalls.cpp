#include "FallingBalls.h"

int main()
{
    try
    {
        FallingBalls animationBalls;
        for (int i = 0; i < 3; i++)
        {
            Ball ball(30, 40);
            ball.setPosition(rand()%701+100, rand()%401+200, animationBalls.getGround(), animationBalls.getGravity());
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