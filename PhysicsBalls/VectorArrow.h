#ifndef VECTOR_ARROW_H
#define VECTOR_ARROW_H

#include <iostream>
#include <fstream>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

template<class T>
class VectorArrow : public sf::Vector2<T>
{
private:
	//variables
	sf::RectangleShape arrow[3];

public:
	//constructor and destructor
	VectorArrow(sf::Vector2<T> Vector) : sf::Vector2<T>(Vector) {}
	~VectorArrow() {}

	//getters and setters
	void setFillColor(const sf::Color& arrowColor)
	{
		for (auto& rectangle : arrow)
		{
			rectangle.setFillColor(arrowColor);
		}
	}



	//update funtions
	void updateArrow()


};

#endif VECTOR_ARROW_H
