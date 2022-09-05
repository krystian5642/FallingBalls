#ifndef FALLING_BALLS
#define FALLING_BALLS

#include "Ball.h"

class FallingBalls
{
private:
	//variables
	std::unique_ptr<sf::RenderWindow> window;
	sf::RectangleShape ground;
	sf::Clock animationClock;
	sf::Event event;
	double gravity;
	long double dt;
	std::vector<Ball> Balls;

	//functions
	void initWindow();
	void initGround();

public:
	//constructor and destructor
	FallingBalls(double gravity = 9.81);
	~FallingBalls();

	//getters and setters
	double getGravity() const;
	void setGravity(double newGravity);

	size_t getBallNumber() const;

	const sf::RectangleShape& getGround() const;
	void setGround(const sf::RectangleShape& newGround);

	//update and render functions
	void updateDt();
	void update();
	void render();

	//add and delete function
	void addBall(const Ball& newBall);
	void deleteBall(auto& ball);

	//start animation function
	void startAnimation();

};

#endif // !FALLING_BALLS