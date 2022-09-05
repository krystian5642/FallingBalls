#include "Ball.h"

extern sf::Vector2u windowSize;

Ball::Ball(double radius, unsigned mass, sf::Vector2<long double> initialVelocity) : sf::CircleShape(radius)
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

unsigned Ball::getMass() const
{
	return mass;
}

void Ball::setMass(unsigned newMass)
{
	mass = newMass;
	density = mass / volume;
}

unsigned Ball::getDensity() const
{
	return density;
}

void Ball::setDensity(unsigned newDensity)
{
	density = newDensity;
	mass = density * volume;
}

unsigned Ball::getVolume() const
{
	return volume;
}

void Ball::setVolume(unsigned newVolume)
{
	volume = newVolume;
	setRadius(pow(3.f/4.f * (unsigned)volume/M_PI, 1.f/3.f));
	density = mass / volume;
}

//energy getters and setters
unsigned long Ball::getTotalEnergy() const
{
	return totalEnergy;
}

unsigned long Ball::getKineticEnergy() const
{
	std::cout << "sdsdsd" << std::endl;
	return kineticEnergy;
}

unsigned long Ball::getPotentialEnergy() const
{
	return potentialEnergy;
}

long double Ball::getCurrentSpeed() const
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

const sf::Vector2<long double>& Ball::getCurrentSpeedVector() const
{
	return currentSpeedVector;
}

void Ball::setPosition(float x, float height, const sf::RectangleShape& ground,long double gravity)
{
	setPosition(sf::Vector2f(x, height), ground,gravity);
}

void Ball::setPosition(const sf::Vector2f& position, const sf::RectangleShape& ground,long double gravity)
{
	sf::Vector2f positionOnMap = sf::Vector2f(position.x, windowSize.y - ground.getSize().y - position.y);
	sf::CircleShape::setPosition(positionOnMap);
}

//update function
void Ball::updateFallingBall(long double dt, const sf::RectangleShape& ground, long double gravity)
{
	//update energy , height and other thing
	move(0, currentSpeedVector.y * dt + gravity * pow<long double>(dt, 2) / 2);
	height = windowSize.y - ground.getSize().y -getPosition().y - getRadius();
	currentSpeedVector = sf::Vector2<long double>(currentSpeedVector.x, currentSpeedVector.y + gravity * dt);
	currentSpeed = sqrt(pow(currentSpeedVector.x, 2) + pow(currentSpeedVector.y, 2));
	if (getPosition().y + getRadius() > windowSize.y - ground.getSize().y)
	{
		currentSpeedVector = -currentSpeedVector;
	}
	totalEnergy = 0;
	if (mass * gravity * height < 0)
	{
		potentialEnergy = 0;
	}
	else
	{
		potentialEnergy = mass * gravity * height;
	}	
	kineticEnergy = mass * pow(currentSpeed, 2)/2;
	totalEnergy = potentialEnergy + kineticEnergy;
	std::cout << potentialEnergy << "  " << kineticEnergy << std::endl;
}