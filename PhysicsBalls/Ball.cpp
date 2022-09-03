#include "Ball.h"

Ball::Ball(float radius, float mass) : sf::CircleShape(radius)
{
	
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
	density = mass / volume;
}

float Ball::getTotalEnergy() const
{
	return totalEnergy;
}

void Ball::setTotalEnergy(float newTotalEnergy)
{
	totalEnergy = newTotalEnergy;
}

float Ball::getKineticEnergy() const
{
	return kineticEnergy;
}

void Ball::setKineticEnergy(float newKineticEnergy)
{
	kineticEnergy = newKineticEnergy;
}

float Ball::getPotentialEnergy() const
{
	return potentialEnergy;
}

void Ball::setPotentialEnergy(float newPotentialEnergy)
{
}

float Ball::getCurrentSpeed() const
{
	return currentSpeed;
}

void Ball::setCurrentSpeed(float newCurrentSpeed)
{
	currentSpeed = newCurrentSpeed;
}

float Ball::getHeight() const
{
	return height;
}

void Ball::setHeight(float newHeight)
{
}

const sf::Vector2f& Ball::getAccelerationVector() const
{
	return accelerationVector;
}

void Ball::setAccelerationVector(const sf::Vector2f& newAccelerationVector)
{
	accelerationVector = newAccelerationVector;
}

const sf::Vector2f& Ball::getCurrentSpeedVector() const
{
	return currentSpeedVector;
}

void Ball::setCurrentSpeedVector(const sf::Vector2f& newCurrentSpeedVector)
{
	currentSpeedVector = newCurrentSpeedVector;
}
