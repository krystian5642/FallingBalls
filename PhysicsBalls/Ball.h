#ifndef BALL_H
#define BALL_H

#include <iostream>
#include <fstream>
#include <memory>
#include <cstdlib>
#include <ctime>

#define _USE_MATH_DEFINES
#include <math.h>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Ball : public sf::CircleShape
{
private:
	//variables
	unsigned mass;                 // kg
    unsigned density;              // kg/m^3 
    unsigned volume;               // m^3
    int totalEnergy;          // J
    unsigned long kineticEnergy;        // J
    int potentialEnergy;      // J
    long double currentSpeed;    // m/s px/s
	float height;                // m
	sf::Vector2<long double> currentSpeedVector;

    //setters
    void setCurrentSpeed(double newCurrentSpeed);
    void setRadius(float radius);  

public:
	//constructors and destructor
	Ball(double radius, unsigned mass, 
        sf::Vector2<long double> = sf::Vector2<long double>(0,0));
	virtual ~Ball();

	//getters and setters
    unsigned getMass() const;
    //we set new mass here, radius doesn't change , density changes,too 
    void setMass(unsigned newMass);

    unsigned getDensity() const;
    //we set new density here, radius doesn't change , mass changes
    void setDensity(unsigned newDensity);

    unsigned getVolume() const;
    //we set new volume here, radius changes , density changes ,mass doesn't change
    void setVolume(unsigned newVolume);

    //energy getters and setters
    int getTotalEnergy() const;
    unsigned long getKineticEnergy() const;
    int getPotentialEnergy() const;

    long double getCurrentSpeed() const;

    float getHeight() const;

    const sf::Vector2<long double>& getCurrentSpeedVector() const;

    void setPosition(float x, float height, const sf::RectangleShape& ground,long double gravity);
    void setPosition(const sf::Vector2f& position, const sf::RectangleShape& ground,long double gravity);

    //update function
    void updateFallingBall(long double dt,
        const sf::RectangleShape& ground, 
        long double gravity = 9.81);

    //These functions are deleted because we set the position above the ground and potential energy changes, too
    void setPosition(float x, float y) = delete;
    void setPosition(const sf::Vector2f& position) = delete;

};



#endif // !BALL_H

