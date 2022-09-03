#ifndef BALL_H
#define BALL_H

#include <iostream>
#include <fstream>
#include <memory>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Ball : public sf::CircleShape
{
private:
	//variables
	float mass;            // kg
	float density;         // kg/m^3 
	float volume;          // m^3
	float totalEnergy;     // J
	float kineticEnergy;   // J
	float potentialEnergy; // J
	float currentSpeed;    // m/s px/s
	float height;          // m
	sf::Vector2f accelerationVector;
	sf::Vector2f currentSpeedVector;

public:
	//constructor and destructor
	Ball();
	~Ball();

};



#endif // !BALL_H

