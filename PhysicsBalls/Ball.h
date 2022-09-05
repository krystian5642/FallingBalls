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
	float mass;                 // kg
    float density;              // kg/m^3 
    float volume;               // m^3
    float totalEnergy;               // J
    float kineticEnergy;   // J
    float potentialEnergy;           // J

    double currentSpeed;    // m/s px/s
	float height;                // m
	sf::Vector2f currentSpeedVector;

    //setters
    void setCurrentSpeed(double newCurrentSpeed);
    void setRadius(float radius);  

public:
	//constructors and destructor
	Ball(double radius, float mass, 
        sf::Vector2f = sf::Vector2f(0,0));
	virtual ~Ball();

	//getters and setters
    float getMass() const;
    //we set new mass here, radius doesn't change , density changes,too 
    void setMass(float newMass);

    float getDensity() const;
    //we set new density here, radius doesn't change , mass changes
    void setDensity(float newDensity);

    float getVolume() const;
    //we set new volume here, radius changes , density changes ,mass doesn't change
    void setVolume(float newVolume);

    //energy getters and setters
    float getTotalEnergy() const;
    float getKineticEnergy() const;
    float getPotentialEnergy() const;

    double getCurrentSpeed() const;

    float getHeight() const;

    const sf::Vector2f& getCurrentSpeedVector() const;

    void setPosition(float x, float height, const sf::RectangleShape& ground,double gravity);
    void setPosition(const sf::Vector2f& position, const sf::RectangleShape& ground,double gravity);

    //update function
    void updateFallingBall(long double dt,
        const sf::RectangleShape& ground, 
        double gravity = 9.81);

    //These functions are deleted because we set the position above the ground and potential energy changes, too
    void setPosition(float x, float y) = delete;
    void setPosition(const sf::Vector2f& position) = delete;

};



#endif // !BALL_H

