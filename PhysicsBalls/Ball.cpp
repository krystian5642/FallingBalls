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

void Ball::setCurrentSpeedVector(sf::Vector2f& newCurrentSpeedVector)
{
	currentSpeedVector = newCurrentSpeedVector;
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
	if (getPosition().y + getRadius() > windowSize.y - ground.getSize().y && currentSpeedVector.y > 0)
	{
		currentSpeedVector.x = (1 - coefficientOfFriction) * currentSpeedVector.x;
		currentSpeedVector.y = -(1 - coefficientOfFriction) * currentSpeedVector.y;
		sf::CircleShape::setPosition(sf::Vector2f(getPosition().x, windowSize.y - ground.getSize().y-getRadius()));
	}
	if(getPosition().y - getRadius() < 0 && currentSpeedVector.y < 0)
	{
		currentSpeedVector.x = (1-coefficientOfFriction) * currentSpeedVector.x;
		currentSpeedVector.y = -(1-coefficientOfFriction) * currentSpeedVector.y;
		sf::CircleShape::setPosition(sf::Vector2f(getPosition().x, getRadius()));
	}
	if (getPosition().x + getRadius() > windowSize.x && currentSpeedVector.x > 0)
	{
		currentSpeedVector.y = (1 - coefficientOfFriction) * currentSpeedVector.y;
		currentSpeedVector.x = -(1 - coefficientOfFriction) * currentSpeedVector.x;
		sf::CircleShape::setPosition(sf::Vector2f(windowSize.x - getRadius(), getPosition().y));
	}
	if (getPosition().x - getRadius() < 0 && currentSpeedVector.x < 0)
	{
		currentSpeedVector.y = (1 - coefficientOfFriction) * currentSpeedVector.y;
		currentSpeedVector.x = -(1 - coefficientOfFriction) * currentSpeedVector.x;
		sf::CircleShape::setPosition(sf::Vector2f(getRadius(), getPosition().y));
	}

	totalEnergy = 0;
    potentialEnergy = mass * gravity * height;	
	kineticEnergy = mass * pow(currentSpeed, 2)/2;
	totalEnergy = potentialEnergy + kineticEnergy;
}

void setSpeedAfterCollision(std::vector<Ball>::iterator firstBall, std::vector<Ball>::iterator secondBall)
{
	//Phi is the contact angle
	float distance = sqrt(pow(firstBall->getPosition().x - secondBall->getPosition().x, 2)
		+ pow(firstBall->getPosition().y - secondBall->getPosition().y, 2));

	double sinPhi = (firstBall->getPosition().y - secondBall->getPosition().y) / distance;
	double cosPhi = (firstBall->getPosition().x - secondBall->getPosition().x) / distance;

	//current speed vectors
	const sf::Vector2f firstBallCurrentSpeedVector = firstBall->getCurrentSpeedVector();
	const sf::Vector2f secondBallCurrentSpeedVector = secondBall->getCurrentSpeedVector();

	float currentVelocity1 = sqrt(pow(firstBallCurrentSpeedVector.x,2) + pow(firstBallCurrentSpeedVector.y, 2));
    float currentVelocity2 = sqrt(pow(secondBallCurrentSpeedVector.x, 2) + pow(secondBallCurrentSpeedVector.y, 2));

	//Theta is the movement angle
	double sinTheta1 = firstBallCurrentSpeedVector.y / currentVelocity1;
	double cosTheta1 = firstBallCurrentSpeedVector.x / currentVelocity1;
	double sinTheta2 = secondBallCurrentSpeedVector.y / currentVelocity2;
	double cosTheta2 = secondBallCurrentSpeedVector.x / currentVelocity2;

	//The new Vx1 adn Vy1 and the new speedVector1
	float vx1 = (currentVelocity1 * (cosTheta1 * cosPhi + sinTheta1 * sinPhi)
		* (firstBall->getMass() - secondBall->getMass()) + 2 * secondBall->getMass() * currentVelocity2
			* (cosTheta2 * cosPhi + sinTheta2 * sinPhi)) * cosPhi/(firstBall->getMass() + secondBall->getMass()) 
		- currentVelocity1 * (sinTheta1 * cosPhi - sinPhi * cosTheta1) * sinPhi;

	float vy1 = (currentVelocity1 * (cosTheta1 * cosPhi + sinTheta1 * sinPhi)
		* (firstBall->getMass() - secondBall->getMass()) + 2 * secondBall->getMass() * currentVelocity2
		* (cosTheta2 * cosPhi + sinTheta2 * sinPhi)) * sinPhi / (firstBall->getMass() + secondBall->getMass())
		+ currentVelocity1 * (sinTheta1 * cosPhi - sinPhi * cosTheta1) * cosPhi;

	sf::Vector2f newSpeedVector1(vx1, vy1);
	firstBall->setCurrentSpeedVector(newSpeedVector1);

	//The new Vx2 adn Vy2 and the new speedVector2
	float vx2 = (currentVelocity2 * (cosTheta2 * cosPhi + sinTheta2 * sinPhi)
		* (secondBall->getMass() - firstBall->getMass()) + 2 * firstBall->getMass() * currentVelocity1
		* (cosTheta1 * cosPhi + sinTheta1 * sinPhi)) * cosPhi / (firstBall->getMass() + secondBall->getMass())
		- currentVelocity2 * (sinTheta2 * cosPhi - sinPhi * cosTheta2) * sinPhi;

	float vy2 = (currentVelocity2 * (cosTheta2 * cosPhi + sinTheta2 * sinPhi)
		* (secondBall->getMass() - firstBall->getMass()) + 2 * firstBall->getMass() * currentVelocity1
		* (cosTheta1 * cosPhi + sinTheta1 * sinPhi)) * sinPhi / (firstBall->getMass() + secondBall->getMass())
		+ currentVelocity2 * (sinTheta2 * cosPhi - sinPhi * cosTheta2) * cosPhi;

	sf::Vector2f newSpeedVector2(vx2, vy2);
	secondBall->setCurrentSpeedVector(newSpeedVector2);
}
