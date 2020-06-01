#include "planet.hpp"

//������� �������� � �����
//�������� ������ - ���������� ������ � num ��������
//������� ������
//num - ���������� ��������
double Planet::ToMeter(double num)
{
    return num * 1000000000;
}

//������� ������ � �������
//�������� ������ - ���������� �������� � num ������
//������� ������
//num - ���������� ������
double Planet::ToPixels(double num)
{
    return num / 1000000000;
}

//������������� �������
void Planet::InitSprite()
{
    texture->setSmooth(true); //���������� ��������
    sprite = new sf::Sprite(*texture); //���������� �������� �������
    double h = texture->getSize().y;
    double coef = d / h;
    sprite->setScale(coef, coef); //��������� ������� � ������ ��������
    sprite->setOrigin(texture->getSize().x / 2, texture->getSize().y / 2); //��������� ������ �������� �� ����� �������
}

//����������� 1
//������� ������
//texture - �������� �������
//pos - ������� �������
//mass - ����� �������
//d - ������� �������
//rotation - �������� ������� � �
Planet::Planet(sf::Texture texture, sf::Vector2f pos, double mass, double d, double rotation)
{
    this->position = new sf::Vector2f(pos);
    this->v = new sf::Vector2f(0, 0);
    this->a = new sf::Vector2f(0, 0);
    this->mass = mass;
    this->d = d;
    this->rotation = rotation;
    this->texture = new sf::Texture(texture);
    InitSprite();
}

//����������� 2
//������� ������
//texture - �������� �������
//pos - ������� �������
//v - �������� �������
//a - ��������� �������
//mass - ����� �������
//d - ������� �������
//rotation - �������� ������� � �
Planet::Planet(sf::Texture texture, sf::Vector2f pos, sf::Vector2f v, sf::Vector2f a, double mass, double d, double rotation)
{
    this->position = new sf::Vector2f(pos);
    this->v = new sf::Vector2f(v);
    this->a = new sf::Vector2f(a);
    this->mass = mass;
    this->d = d;
    this->rotation = rotation;
    this->texture = new sf::Texture(texture);
    InitSprite();
}

//����������� ������
//������� ������
//other - ������ �� ������ �������
void Planet::Union(Planet &other)
{
    v->x = (mass * v->x + other.mass * other.v->x) / (mass + other.mass); //������ �������� ����� ������������ �� ������� ���������� �����
    v->y = (mass * v->y + other.mass * other.v->y) / (mass + other.mass);

    double c = (mass + other.mass) / mass; //������ ������������ ��������� ��������

    d *= c;

    double h = texture->getSize().y;
    double coef = d / h;
    sprite->setScale(coef, coef); //��������� ������� �������, �������� ������ ��������

    mass += other.mass; //������������ ����
}

//��������� ������� �������
//������� ������
//dt - �����
//mul - ��������� �������
void Planet::ChangePosition(double dt, double mul)
{
    dt *= mul;
    v->x += a->x * dt;
    v->y += a->y * dt;

    position->x += v->x * dt;
    position->y += v->y * dt;
}

//��������� ������� ������� ������� �������
void Planet::Move()
{
    sprite->setPosition(*position);
}

//��������� ��������� �������
void Planet::ResetA()
{
    a->x = 0;
    a->y = 0;
}

//���������� ������� ������ ������� �� ���������
//������� ������
//other - ������ �� ������ �������
//distance - ��������� �� �������
void Planet::Correct(Planet& other, double distance)
{
    distance = ToMeter(distance);
    a->x += ToPixels(G * other.mass * ToMeter((double)other.position->x - (double)position->x) / pow(distance, 3));
    a->y += ToPixels(G * other.mass * ToMeter((double)other.position->y - (double)position->y) / pow(distance, 3));
}

//��������� ������� �������� �������
//������� ������
//dt - �����
//mul - ��������� �������
void Planet::Rotate(double dt, double mul)
{
    sprite->rotate(rotation * dt * mul);
}

//���������� ���������� ����� ���������
//������� ������
//other - ������ �� ������ �������
double Planet::GetDistance(Planet &other)
{
    return sqrt(pow((double)position->x - (double)other.position->x, 2) + pow((double)position->y - (double)other.position->y, 2));
}

//���������� ������
Planet::~Planet()
{
    delete[] position;
    delete[] v;
    delete[] a;
    delete texture;
    delete[] sprite;
}
