#pragma once
#include <SFML/Graphics.hpp>

//����� �������
class Planet
{
private:
    sf::Texture* texture; //������� �������
    const double G = 6.67408E-11; //����. ����������
    double rotation; //�������� �������

    void InitSprite(); //������������� �������
public:
    sf::Sprite *sprite; //������ �������
    sf::Vector2f* position; //������� �������
    sf::Vector2f* v; //�������� �������
    sf::Vector2f* a; //��������� �������
    double mass; //����� �������
    double d; //������� �������

    Planet(sf::Texture texture, sf::Vector2f pos, double mass, double d, double rotation); //����������� 1
    Planet(sf::Texture texture, sf::Vector2f pos, sf::Vector2f v, sf::Vector2f a, double mass, double d, double rotation); //���������� 2
    static double ToMeter(double num); //������� �������� � �����
    static double ToPixels(double num); //������� ������ � �������
    void Union(Planet& other); //����������� ������
    void ChangePosition(double dt, double mul); //��������� �������
    void Move(); //��������� ������� �������
    void ResetA(); //��������� ���������
    void Correct(Planet& other, double distance); //�������� � ��������� �������� ������ �������
    void Rotate(double dt, double mul); //�������� ������ �������� �������
    double GetDistance(Planet& other); //�������� ���������� ����� ���������
    ~Planet(); //����������
};
