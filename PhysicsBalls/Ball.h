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

    //private getters and setters
    void setTotalEnergy(float newTotalEnergy);
    void setKineticEnergy(float newKineticEnergy);
    void setPotentialEnergy(float newPotentialEnergy);

public:
	//constructors and destructor
	Ball(float radius,float mass);
	~Ball();

	//getters and setters
    float getMass() const;
    void setMass(float newMass);

    float getDensity() const;
    void setDensity(float newDensity);

    float getVolume() const;
    void setVolume(float newVolume);

    float getTotalEnergy() const;

    float getKineticEnergy() const;

    float getPotentialEnergy() const;

    float getCurrentSpeed() const;
    void setCurrentSpeed(float newCurrentSpeed);

    float getHeight() const;
    void setHeight(float newHeight);

    const sf::Vector2f& getAccelerationVector() const;
    void setAccelerationVector(const sf::Vector2f& newAccelerationVector);

    const sf::Vector2f& getCurrentSpeedVector() const;
    void setCurrentSpeedVector(const sf::Vector2f& newCurrentSpeedVector);

};



#endif // !BALL_H

