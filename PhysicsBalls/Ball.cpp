#include "Ball.h"

Ball::Ball(double radius, double mass,sf::Vector2f initialVelocity) : sf::CircleShape(radius)
{
	setMass(mass);
	setVolume(4.f/3.f*M_PI*pow(radius,3));
	setDensity(mass/volume);
	setOrigin(radius,radius);
	currentSpeed = pow(pow(initialVelocity.x,2) + pow(initialVelocity.y, 2),1.f / 2.f);
	currentSpeedVector = initialVelocity;
	kineticEnergy = mass * pow(currentSpeed, 2) / 2;
	totalEnergy = kineticEnergy;
}

Ball::~Ball()
{
}

double Ball::getMass() const
{
	return mass;
}

void Ball::setMass(double newMass)
{
	mass = newMass;
	density = mass / volume;
}

double Ball::getDensity() const
{
	return density;
}

void Ball::setDensity(double newDensity)
{
	density = newDensity;
	mass = density * volume;
}

double Ball::getVolume() const
{
	return volume;
}

void Ball::setVolume(double newVolume)
{
	volume = newVolume;
	setRadius(pow(3.f/4.f * volume/M_PI, 1.f/3.f));
	density = mass / volume;
}

//energy getters and setters
double Ball::getTotalEnergy() const
{
	return totalEnergy;
}

double Ball::getKineticEnergy() const
{
	return kineticEnergy;
}

double Ball::getPotentialEnergy() const
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

double Ball::getHeight() const
{
	return height;
}

void Ball::setHeight(double newHeight,float groundHeight,float windowHeight, unsigned long long gravity)
{
	setPosition(400/*getPosition().x*/, windowHeight - groundHeight - newHeight);
	totalEnergy -= potentialEnergy;
	potentialEnergy = mass * gravity * height;
	totalEnergy += potentialEnergy;
}

const sf::Vector2f& Ball::getCurrentSpeedVector() const
{
	return currentSpeedVector;
}

//update function
void Ball::updateFallingBall(long double dt, unsigned long long gravity)
{
	//update energy , height and other thing
	setPosition(getPosition().x, getPosition().y + currentSpeedVector.y *dt + gravity * pow(dt,2)/2);
	currentSpeedVector = sf::Vector2f(0, currentSpeedVector.y + gravity * dt);
	if (getPosition().y + getRadius() > 730)
	{
		currentSpeedVector = -currentSpeedVector;
	}
}