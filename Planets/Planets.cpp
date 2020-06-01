#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "Planet.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "Planets");
	sf::Clock timer;
	std::vector<Planet> planets;
	planets.reserve(1000);

	sf::Vector2f sunPos(395, 395);
	sf::Vector2f sunV(0, 0);
	sf::Vector2f sunA(0, 0);
	Planet* sun = new Planet(sunPos, sunV, sunA, 500000, 10);
	sun->texture->setFillColor(sf::Color::Yellow);
	planets.push_back(*sun);



	sf::Vector2f planetPos(330, 395);
	sf::Vector2f planetV(0, -100);
	sf::Vector2f planetA(0, 0);
	Planet* planet = new Planet(planetPos, planetV, planetA, 500, 5);
	planet->texture->setFillColor(sf::Color::Cyan);
	planets.push_back(*planet);



	sf::Vector2f planetPos2(560, 395);
	sf::Vector2f planetV2(0, 50);
	sf::Vector2f planetA2(0, 0);
	Planet* planet2 = new Planet(planetPos2, planetV2, planetA2, 5000, 5);
	planet2->texture->setFillColor(sf::Color::Red);
	planets.push_back(*planet2);




	for (int i = 0; i < planets.size(); i++)
	{
		planets.at(i).texture->setPosition(*planets.at(i).position);
	}

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		double dt = timer.getElapsedTime().asMicroseconds();
		dt = dt / 1000000;
		timer.restart();


		for (int i = 0; i < planets.size(); i++)
		{
			planets.at(i).ResetA();
		}

		for (int i = 0; i < planets.size(); i++)
		{
			for (int j = 0; j < planets.size(); j++)
			{
				if (i == j)
				{
					continue;
				}
				planets.at(i).Correct(planets.at(j));
			}
		}

		for (int i = 0; i < planets.size(); i++)
		{
			planets.at(i).Move(dt);
			planets.at(i).texture->setPosition(*planets.at(i).position);
		}


		window.clear();
		for (int i = 0; i < planets.size(); i++)
		{
			window.draw(*planets.at(i).texture);
		}
		window.display();
	}

	return 0;
}