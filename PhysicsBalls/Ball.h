#ifndef BALL_H
#define BALL_H

#include <iostream>
#include <fstream>
#include <memory>

#define _USE_MATH_DEFINES
#include <math.h>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Ball : public sf::CircleShape
{
private:
	//variables
	double mass;            // kg
    double density;         // kg/m^3 
    double volume;          // m^3
    double totalEnergy;     // J
    double kineticEnergy;   // J
    double potentialEnergy; // J
    double currentSpeed;    // m/s px/s
	float height;           // m
	sf::Vector2f currentSpeedVector;

    //setters
    void setCurrentSpeed(double newCurrentSpeed);
    void setRadius(float radius);  

public:
	//constructors and destructor
	Ball(double radius, double mass, sf::Vector2f initialVelocity = sf::Vector2f(0,0));
	virtual ~Ball();

	//getters and setters
    double getMass() const;
    //we set new mass here, radius doesn't change , density changes,too 
    void setMass(double newMass);

    double getDensity() const;
    //we set new density here, radius doesn't change , mass changes
    void setDensity(double newDensity);

    double getVolume() const;
    //we set new volume here, radius changes , density changes ,mass doesn't change
    void setVolume(double newVolume);

    //energy getters and setters
    double getTotalEnergy() const;
    double getKineticEnergy() const;
    double getPotentialEnergy() const;

    double getCurrentSpeed() const;

    double getHeight() const;
    void setHeight(double newHeight,float groundHeight, float windowHeight, unsigned long long gravity = 9.81);

    const sf::Vector2f& getCurrentSpeedVector() const;

    //update function
    void updateFallingBall(long double dt, unsigned long long gravity = 9.81);

};



#endif // !BALL_H

