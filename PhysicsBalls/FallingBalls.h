#ifndef FALLING_BALLS
#define FALLING_BALLS

#include <iostream>
#include <fstream>
#include <memory>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class FallingBalls
{
private:
	//variables
	std::unique_ptr<sf::RenderWindow> window;
	sf::RectangleShape ground;
	sf::Clock animationClock;
	sf::Event event;
	double gravity;
	double dt;
	float groundHeight;
	//std::vector<Ball> Balls;

	//functions
	void initWindow();
	void initGround();
	void initBalls(const size_t& ballNumber);

public:
	//constructor and destructor
	FallingBalls(size_t ballNumber = 1,double gravity = 9.81);
	~FallingBalls();

	//getters and setters
	double getGravity() const;
	void setGravity(double newGravity);

	size_t getBallNumber() const;

	float getGroundHeight() const;
	void setGroundHeight(float newGroundHeight);

	//update and render functions
	void updateDt();
	void update();
	void render();

	//start animation function
	void startAnimation();

};

#endif // !FALLING_BALLS