#include "Ball.h"

extern sf::Vector2u windowSize;

Ball::Ball(double radius, float mass, sf::Vector2f initialVelocity) : sf::CircleShape(radius)
{
	this->mass = mass;
	this->volume = 4.f / 3.f * M_PI * pow(radius, 3);
	this->density = this->mass / this->volume;
	setOrigin(radius,radius);
	currentSpeed = sqrt(pow(initialVelocity.x,2) + pow(initialVelocity.y, 2));
	currentSpeedVector = initialVelocity;
	kineticEnergy = mass * pow(currentSpeed, 2) / 2;
	totalEnergy = kineticEnergy;
}

Ball::~Ball()
{
}

float Ball::getMass() const
{
	return mass;
}

void Ball::setMass(float newMass)
{
	mass = newMass;
	density = mass / volume;
}

float Ball::getDensity() const
{
	return density;
}

void Ball::setDensity(float newDensity)
{
	density = newDensity;
	mass = density * volume;
}

float Ball::getVolume() const
{
	return volume;
}

void Ball::setVolume(float newVolume)
{
	volume = newVolume;
	setRadius(pow(3.f/4.f * (unsigned)volume/M_PI, 1.f/3.f));
	density = mass / volume;
}

//energy getters and setters
float Ball::getTotalEnergy() const
{
	return totalEnergy;
}

float Ball::getKineticEnergy() const
{
	return kineticEnergy;
}

float Ball::getPotentialEnergy() const
{
	return potentialEnergy;
}

double Ball::getCurrentSpeed() const
{
	return currentSpeed;
}

void Ball::setCurrentSpeed(double newCurrentSpeed)
{
	currentSpeed = newCurrentSpeed;
	kineticEnergy = mass * currentSpeed * currentSpeed / 2;
}

void Ball::setRadius(float radius)
{
	sf::CircleShape::setRadius(radius);
}

float Ball::getHeight() const
{
	return height;
}

const sf::Vector2f& Ball::getCurrentSpeedVector() const
{
	return currentSpeedVector;
}

void Ball::setPosition(float x, float height, const sf::RectangleShape& ground,double gravity)
{
	setPosition(sf::Vector2f(x, height), ground,gravity);
}

void Ball::setPosition(const sf::Vector2f& position, const sf::RectangleShape& ground,double gravity)
{
	height = windowSize.y - ground.getSize().y - position.y;
	sf::Vector2f positionOnMap = sf::Vector2f(position.x, height);
	sf::CircleShape::setPosition(positionOnMap);
	potentialEnergy = mass * gravity * height;
	totalEnergy += potentialEnergy;
}

//update function
void Ball::updateFallingBall(long double dt, const sf::RectangleShape& ground, double gravity)
{
	//update energy , height and other thing
	move(currentSpeedVector.x*dt, currentSpeedVector.y * dt + gravity * pow<long double>(dt, 2) / 2);
	height = windowSize.y - ground.getSize().y -getPosition().y;
	currentSpeedVector = sf::Vector2f(currentSpeedVector.x, currentSpeedVector.y + gravity * dt);
	currentSpeed = sqrt(pow(currentSpeedVector.x, 2) + pow(currentSpeedVector.y, 2));
	float coefficientOfFriction = 0.5;
	if (getPosition().y + getRadius() > windowSize.y - ground.getSize().y && currentSpeedVector.y > 0 
		|| getPosition().y - getRadius() < 0 && currentSpeedVector.y < 0)
	{
		currentSpeedVector.x = (1-coefficientOfFriction) * currentSpeedVector.x;
		currentSpeedVector.y = -(1-coefficientOfFriction) * currentSpeedVector.y;
	}
	if (getPosition().x + getRadius() > windowSize.x && currentSpeedVector.x > 0 
		|| getPosition().x - getRadius() < 0 && currentSpeedVector.x < 0)
	{
		currentSpeedVector.y = (1 - coefficientOfFriction) * currentSpeedVector.y;
		currentSpeedVector.x = -(1 - coefficientOfFriction) * currentSpeedVector.x;
	}
	totalEnergy = 0;
    potentialEnergy = mass * gravity * height;	
	kineticEnergy = mass * pow(currentSpeed, 2)/2;
	totalEnergy = potentialEnergy + kineticEnergy;
}