#include "Planet.h"

Planet::Planet(sf::Vector2f pos, double mass, double r)
{
	this->position = new sf::Vector2f(pos);
	this->v = new sf::Vector2f(0, 0);
	this->a = new sf::Vector2f(0, 0);
	this->mass = mass;
	this->r = r;
	texture = new sf::CircleShape(r);
}

Planet::Planet(sf::Vector2f pos, sf::Vector2f v, sf::Vector2f a, double mass, double r)
{
	this->position = new sf::Vector2f(pos);
	this->v = new sf::Vector2f(v);
	this->a = new sf::Vector2f(a);
	this->mass = mass;
	this->r = r;
	texture = new sf::CircleShape(r);
}

void Planet::Move(double dt)
{
	v->x += a->x * dt;
	v->y += a->y * dt;

	position->x += v->x * dt;
	position->y += v->y * dt;
}

void Planet::ResetA()
{
	a->x = 0;
	a->y = 0;
}

void Planet::Correct(Planet& other)
{
	double r = sqrt(pow(position->x - other.position->x, 2) + pow(position->y - other.position->y, 2));

	a->x += other.mass * (other.position->x - position->x) / pow(r, 3);
	a->y += other.mass * (other.position->y - position->y) / pow(r, 3);
}

Planet::~Planet()
{
	delete[] position;
	delete[] v;
	delete[] a;
}
