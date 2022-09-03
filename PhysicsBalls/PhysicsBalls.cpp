#include "FallingBalls.h"

int main()
{
    try
    {
        FallingBalls animationBalls;
        animationBalls.startAnimation();
    }
    catch (std::exception& error)
    {
        std::cerr << error.what() << std::endl;
    }
	return 0;
}