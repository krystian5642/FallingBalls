#include "FallingBalls.h"

int main()
{
    try
    {
        FallingBalls animationBalls;
        for (int i = 0; i <100; i++)
        {
            Ball ball(5, 5.0,sf::Vector2f(rand() % 90-50,60));
            ball.setPosition(rand()%1270, rand()%80+500, animationBalls.getGround(), animationBalls.getGravity());
            ball.setFillColor(sf::Color::Green);
            animationBalls.addBall(ball);
        }
        animationBalls.setCoefficientOfFriction(0.4);
        animationBalls.startAnimation();
    }
    catch (std::exception& error)
    {
        std::cerr << error.what() << std::endl;
    }
	return 0;
}