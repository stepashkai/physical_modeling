#include "planet.hpp"

//перевод пикселей в метры
//выходные данные - количество метров в num пикселях
//входные данные
//num - количество пикселей
double Planet::ToMeter(double num)
{
    return num * 1000000000;
}

//перевод метров в пиксели
//выходные данные - количество пикселей в num метрах
//входные данные
//num - количество метров
double Planet::ToPixels(double num)
{
    return num / 1000000000;
}

//инициализация спрайта
void Planet::InitSprite()
{
    texture.setSmooth(true); //добавление размытия
    sprite = sf::Sprite(texture); //добавление текстуры спрайту
    double h = texture.getSize().y;
    double coef = d / h;
    sprite.setScale(coef, coef); //изменение размера с учётом диаметра
    sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2); //установка центра вращения на центр спрайта
}

//конструктор 1
//входные данные
//texture - текстура планеты
//pos - позиция планеты
//mass - масса планеты
//d - диаметр планеты
//rotation - вращение планеты в с
Planet::Planet(std::string filepath, sf::Vector2f pos, double mass, double d, double rotation)
{
    this->position = sf::Vector2f(pos);
    this->v =  sf::Vector2f(0, 0);
    this->a =  sf::Vector2f(0, 0);
    this->mass = mass;
    this->d = d;
    this->filepath = filepath;
    this->rotation = rotation;
    this->texture.loadFromFile(filepath);
    InitSprite();
}

//конструктор 2
//входные данные
//texture - текстура планеты
//pos - позиция планеты
//v - скорость планеты
//a - ускорение планеты
//mass - масса планеты
//d - диаметр планеты
//rotation - вращение планеты в с
Planet::Planet(std::string filepath, sf::Vector2f pos, sf::Vector2f v, sf::Vector2f a, double mass, double d, double rotation)
{
    this->position =  sf::Vector2f(pos);
    this->v =  sf::Vector2f(v);
    this->a =  sf::Vector2f(a);
    this->mass = mass;
    this->d = d;
    this->filepath = filepath;
    this->rotation = rotation;
    this->texture.loadFromFile(filepath);
    InitSprite();
}

Planet::Planet(const Planet &other)
{
    this->filepath = other.filepath;
    this->texture.loadFromFile(filepath);
    //this->sprite = sf::Sprite(other.sprite);
    this->rotation = other.rotation;
    this->G = other.G;
    this->position = sf::Vector2f(other.position);
    this->v = sf::Vector2f(other.v);
    this->a = sf::Vector2f(other.a);
    this->mass = other.mass;
    this->d = other.d;
    InitSprite();
}

//объединение планет
//входные данные
//other - ссылка на вторую планету
void Planet::Union(Planet &other)
{
    v.x = (mass * v.x + other.mass * other.v.x) / (mass + other.mass); //расчёт скорости после столкновения по формуле неупругого удара
    v.y = (mass * v.y + other.mass * other.v.y) / (mass + other.mass);

    double c = (mass + other.mass) / mass; //расчёт коэффициента изменения диаметра

    d *= c;

    double h = texture.getSize().y;
    double coef = d / h;
    sprite.setScale(coef, coef); //изменение размера спрайта, согласно новому диаметру

    mass += other.mass; //суммирование масс
}

//изменение позиции планеты
//входные данные
//dt - время
//mul - множитель времени
void Planet::ChangePosition(double dt, double mul)
{
    dt *= mul;
    v.x += a.x * dt;
    v.y += a.y * dt;

    position.x += v.x * dt;
    position.y += v.y * dt;
}

//установка текущей позиции планеты спрайту
void Planet::Move()
{
    sprite.setPosition(position);
}

//обнуление ускорения планеты
void Planet::ResetA()
{
    a.x = 0;
    a.y = 0;
}

//добавление влияния другой планеты на ускорение
//входные данные
//other - ссылка на другую планету
//distance - дистанция до планеты
void Planet::Correct(Planet& other, double distance)
{
    distance = ToMeter(distance);
    a.x += ToPixels(G * other.mass * ToMeter((double)other.position.x - (double)position.x) / pow(distance, 3));
    a.y += ToPixels(G * other.mass * ToMeter((double)other.position.y - (double)position.y) / pow(distance, 3));
}

//изменение градуса вращение планеты
//входные данные
//dt - время
//mul - множитель времени
void Planet::Rotate(double dt, double mul)
{
    sprite.rotate(rotation * dt * mul);
}

//вычисление расстояние между планетами
//входные данные
//other - ссылка на другую планету
double Planet::GetDistance(Planet &other)
{
    return sqrt(pow((double)position.x - (double)other.position.x, 2) + pow((double)position.y - (double)other.position.y, 2));
}
