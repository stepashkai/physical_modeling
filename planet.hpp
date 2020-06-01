#pragma once
#include <SFML/Graphics.hpp>

//класс планеты
class Planet
{
private:
    sf::Texture* texture; //тектура планеты
    const double G = 6.67408E-11; //грав. постоянная
    double rotation; //вращение планеты

    void InitSprite(); //инициализация спрайта
public:
    sf::Sprite *sprite; //объект спрайта
    sf::Vector2f* position; //позиция планеты
    sf::Vector2f* v; //скорость планеты
    sf::Vector2f* a; //ускорение планеты
    double mass; //масса планеты
    double d; //диаметр планеты

    Planet(sf::Texture texture, sf::Vector2f pos, double mass, double d, double rotation); //конструктор 1
    Planet(sf::Texture texture, sf::Vector2f pos, sf::Vector2f v, sf::Vector2f a, double mass, double d, double rotation); //конструтор 2
    static double ToMeter(double num); //перевод пикселей в метры
    static double ToPixels(double num); //перевод метров в пиксели
    void Union(Planet& other); //объединение планет
    void ChangePosition(double dt, double mul); //изменение позиции
    void Move(); //установка позиции спрайта
    void ResetA(); //обнуление ускорения
    void Correct(Planet& other, double distance); //добавить в ускорение влияение другой планеты
    void Rotate(double dt, double mul); //изменить градус вращение планеты
    double GetDistance(Planet& other); //получить расстояние между планетами
    ~Planet(); //деструктор
};
