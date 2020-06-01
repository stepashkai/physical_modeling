#include <iostream>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <cmath>
#include <iostream>
#include <string>
#include "planet.hpp"
#include <ctime>

//������������ � ����������� ���������
enum State
{
    SOLAR, SANDBOX, MENU
};


std::vector<Planet*> planets; //��������� ������
sf::View *defaultCamera; //������� � ������ ������ �� ���������

//�������� �������
//�������� ������ - ��������� �� ��������� �������
//������� ������
//posX - ������� ������� �� �
//posY - ������� ������� �� Y
//vX - �������� ������� �� X
//vY - �������� ������� �� Y
//aX - ��������� ������� �� X
//aY - ��������� ������� �� Y
//mass - ����� �������
//d - ������� �������
//rotation - �������� �������
//filepath - ���� � ���� ��������
Planet *InitPlanet(double posX, double posY, double vX, double vY, double aX, double aY, double mass, double d, double rotation, std::string filepath)
{
    sf::Vector2f pos(posX, posY);
    sf::Vector2f v(vX, vY);
    sf::Vector2f a(aX, aY);
    sf::Texture texture;
    texture.loadFromFile(filepath);
    Planet* planet = new Planet(texture, pos, v, a, mass, d, rotation);
    return planet;
}

//�������� �������
//������� ������
//i - ������ ������� � ������� ������
void DeleteAt(int i)
{
    if(i >= 0 && i < planets.size())
    {
        delete planets.at(i);
        planets.erase(planets.begin() + i);
    }
}

//�������� ���� ������ � ������� ������
void Clear()
{
    while(planets.size()> 0)
    {
        DeleteAt(0);
    }
}

//������������� ��������� �������
void InitSolarSystem()
{
    planets.push_back(InitPlanet(595, 360, 0, 0, 0, 0, 1.989E30, 40, 100, "resources\\planets\\0.png"));//������
    planets.push_back(InitPlanet(445, 360, 0, -0.000029783, 0, 0, 5.972E24, 10, 150, "resources\\planets\\1.png"));//�����
    planets.push_back(InitPlanet(537, 360, 0, -0.00004787, 0, 0, 3.33022E23, 4, 100, "resources\\planets\\2.png"));//��������
    planets.push_back(InitPlanet(487, 360, 0, -0.00003502, 0, 0, 4.867E24, 12, 150, "resources\\planets\\3.png"));//������
    planets.push_back(InitPlanet(389, 360, 0, -0.00002413, 0, 0, 6.39E23, 8, -150, "resources\\planets\\4.png"));//����
    planets.push_back(InitPlanet(-183, 360, 0, -0.00001307, 0, 0, 1.898E27, 30, -70, "resources\\planets\\5.png"));//������
    planets.push_back(InitPlanet(-835, 360, 0, -0.00000969, 0, 0, 5683E26, 30, -50, "resources\\planets\\6.png"));//������
    planets.push_back(InitPlanet(-2266, 360, 0, -0.00000681, 0, 0, 8.681E25, 25, 100, "resources\\planets\\7.png"));//����
    planets.push_back(InitPlanet(-3955, 360, 0, -0.00000543, 0, 0, 1.024E26, 30, -100, "resources\\planets\\8.png"));//������
}

//�������� label
//�������� ������ - ������ ���� tgui::Label::Ptr
//������� ������
//text - ����� �� �����
//x - ������� �� X
//y - ������� �� Y
tgui::Label::Ptr CreateLabel(std::string text, int x, int y)
{
    tgui::Label::Ptr label = tgui::Label::create();
    label->setSize(120, 20);
    label->getRenderer()->setTextColor(tgui::Color::White);
    label->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
    label->setText(text);
    label->setPosition(x, y);
    return label;
}

//�������� textbox
//�������� ������ - ������ ���� tgui::TextBox::Ptr
//������� ������
//text - ����� �� �����
//x - ������� �� X
//y - ������� �� Y
tgui::TextBox::Ptr CreateTextBox(std::string text, int x, int y)
{
    tgui::TextBox::Ptr textBox = tgui::TextBox::create();
    textBox->setText(text);
    textBox->setSize(100, 20);
    textBox->setPosition(x, y);
    return textBox;
}

//����� ������� ���������� �� ����
//������� ������
//status - ������ ������������ ��� ��������� ������� ����������
//camera - ������ ������
void SetMenu(State &status, sf::View &camera)
{
    camera = sf::View(*defaultCamera);
    status = State::MENU;
    Clear();
}

//����� ������� ���������� �� ��������� ��������� �������
//������� ������
//status - ������ ������������ ��� ��������� ������� ����������
void SetSolar(State &status)
{
    status = State::SOLAR;
    InitSolarSystem();
}



int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(0));


    sf::Texture menuT, sandboxT, exitT, solarT; //������������� ������� ��� ������ ����
    menuT.loadFromFile("resources\\interface\\menu.png"); //��������� ���� � ��������
    menuT.setSmooth(true); //�������� �������� ��������
    sandboxT.loadFromFile("resources\\interface\\sandbox.png");
    sandboxT.setSmooth(true);
    exitT.loadFromFile("resources\\interface\\exit.png");
    exitT.setSmooth(true);
    solarT.loadFromFile("resources\\interface\\solar.png");
    solarT.setSmooth(true);
    sf::Sprite menu, sandbox, exit, solar, back; //������������� ������� ��� ������ ����
    menu.setTexture(menuT); //��������� �������� � ������
    menu.setScale(2.0/3.0, 2.0/3.0); //��������� �������� �������
    sandbox.setTexture(sandboxT);
    sandbox.setScale(0.75, 0.75);
    exit.setTexture(exitT);
    exit.setScale(0.75, 0.75);
    solar.setTexture(solarT);
    solar.setScale(0.75, 0.75);


    State state = State::MENU; //��������� ���������� ������� ����������


    sf::RenderWindow window(sf::VideoMode(1280, 720), "Planets"); //�������� ����
    tgui::Gui gui(window); //�������� ��������� ����������


    tgui::TextBox::Ptr vXTextBox = CreateTextBox("0", window.getSize().x - 100 - 5, 5); //�������� ����������� ��� ����� ���������� ������
    gui.add(vXTextBox);

    tgui::Label::Ptr vXLabel = CreateLabel("Vx(mln km/c)", window.getSize().x - vXTextBox->getSize().x - 105, 5);
    gui.add(vXLabel);

    tgui::TextBox::Ptr vYTextBox = CreateTextBox("0", window.getSize().x - 100 - 5, 30);
    gui.add(vYTextBox);

    tgui::Label::Ptr vYLabel = CreateLabel("Vy(mln km/c)", window.getSize().x - vYTextBox->getSize().x - 105, 30);
    gui.add(vYLabel);

    tgui::TextBox::Ptr massTextBox = CreateTextBox("1E30", window.getSize().x - 100 - 5, 55);
    gui.add(massTextBox);

    tgui::Label::Ptr massLabel = CreateLabel("Mass (t)", window.getSize().x - massTextBox->getSize().x - 105, 55);
    gui.add(massLabel);

    tgui::TextBox::Ptr diameterTextBox = CreateTextBox("15", window.getSize().x - 100 - 5, 80);
    gui.add(diameterTextBox);

    tgui::Label::Ptr diameterLabel = CreateLabel("D (mln km)", window.getSize().x - diameterTextBox->getSize().x - 105, 80);
    gui.add(diameterLabel);

    tgui::TextBox::Ptr rotationTextBox = CreateTextBox("10", window.getSize().x - 100 - 5, 105);
    gui.add(rotationTextBox);

    tgui::Label::Ptr rotationLabel = CreateLabel("Rot (deg/c)", window.getSize().x - rotationTextBox->getSize().x - 105, 105);
    gui.add(rotationLabel);

    tgui::Label::Ptr timerLabel = CreateLabel("Time Multiplier", 5, 5);
    gui.add(timerLabel);

    tgui::Slider::Ptr timerMultiplier = tgui::Slider::create(1, 1000000); //���������� ��������, ������� ����� ������������ ��������� �������
    timerMultiplier->setPosition(timerLabel->getSize().x + 10,7);
    timerMultiplier->setStep(1);
    timerMultiplier->setSize(850, timerMultiplier->getSize().y);
    gui.add(timerMultiplier);

    tgui::Label::Ptr mulStatusLabel = CreateLabel("x1", timerLabel->getSize().x + 20 + timerMultiplier->getSize().x, 5);
    gui.add(mulStatusLabel);




    sf::Clock timer; //������ ��� ���������
    sf::View camera; //������ ������
    camera.setSize((sf::Vector2f)window.getSize());
    bool isDrag = false;
    sf::Vector2i startPos;
    sf::Vector2f oldCenter;
    camera.setCenter(window.getSize().x / 2, window.getSize().y / 2);
    planets.reserve(1000);
    defaultCamera = new sf::View(camera);


    menu.setPosition(sf::Vector2f(0,0)); //��������� ������� ��������� ����
    solar.setPosition(sf::Vector2f(window.getSize().x/2 - solarT.getSize().x * solar.getScale().x/2, 330));
    sandbox.setPosition(sf::Vector2f(window.getSize().x/2 - sandboxT.getSize().x * sandbox.getScale().x/2, 430));
    exit.setPosition(sf::Vector2f(window.getSize().x/2 - exitT.getSize().x * exit.getScale().x/2, 530));





    for (int i = 0; i < planets.size(); i++)
    {
        planets.at(i)->sprite->setPosition(*planets.at(i)->position); //��������� ������� �������� ���� ������
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) //��������� �������
        {
            if (event.type == sf::Event::Closed) //������� �������� ����
            {
                window.close();
            }
            if(state == State::SOLAR || state == State::SANDBOX) //��������� �������, ����� ������� ���������
            {
                gui.handleEvent(event);
                if (event.type == sf::Event::MouseWheelMoved) //������� ��� �������� �������� ����
                {
                    camera.zoom(1 - (float)event.mouseWheel.delta * 0.05); //��������� ������� ������� ���������
                }
                if (event.type == sf::Event::KeyPressed) //��������� ������� ������� ������
                {
                    if (event.key.code == sf::Keyboard::D) //���� ������ ������� D
                    {
                        if (planets.size() > 0)
                        {
                            DeleteAt(planets.size() - 1); //������� ��������� �������
                        }
                    }
                    if (event.key.code == sf::Keyboard::Escape) //���� ������ Esc
                    {
                        SetMenu(state, camera); //����� � ����
                    }
                }
                if (event.type == sf::Event::MouseButtonPressed) //��������� ������� ������� ������ ����
                {
                    if (event.mouseButton.button == sf::Mouse::Right) //���� ������ ������ ������
                    {
                        isDrag = true;
                        startPos = sf::Mouse::getPosition(); //��������� ����� ������ � ����� ������� ��� ������������ ������� ���������
                        oldCenter = camera.getCenter();
                    }
                    if(event.mouseButton.button == sf::Mouse::Left) //���� ������ ����� ������
                    {
                        int x = event.mouseButton.x;
                        int y = event.mouseButton.y;
                        if((y > 30 || x > 1000 ) && (x < 1170 || y > 130))
                        {
                            try //������� ��������� ������ � ������� ������� �� �� ������
                            {
                                sf::Vector2f pos(event.mouseButton.x, event.mouseButton.y);
                                pos = window.mapPixelToCoords((sf::Vector2i)pos);
                                double posX = pos.x;
                                double posY = pos.y;
                                double vX = std::stod(vXTextBox->getText().toAnsiString());
                                double vY = std::stod(vYTextBox->getText().toAnsiString());
                                double mass = std::stod(massTextBox->getText().toAnsiString());
                                double diameter = std::stod(diameterTextBox->getText().toAnsiString());
                                double rotation = std::stod(rotationTextBox->getText().toAnsiString());
                                planets.push_back(InitPlanet(posX, posY, vX, vY, 0, 0, mass, diameter, rotation, "resources\\planets\\" + std::to_string(rand() % 20) + ".png"));
                                std::cout << "Planet created\nMass: " << mass << " t.\nDiameter: " << diameter << " mln.km.\nPosition: " << "(" << pos.x << "," << pos.y << ")\nV: " << "(" << vX << "," << vY << ")\n\n";
                            }
                            catch(std::exception e)
                            {
                                std::cout << "Failed to create planet due to input error\n\n";
                            }
                        }
                    }
                }
                if (event.type == sf::Event::MouseButtonReleased) //���� ������ ���� ������
                {
                    if (event.mouseButton.button == sf::Mouse::Right) //���� ������ ������
                    {
                        isDrag = false; //�������������� ��������
                    }
                }
            }
            else //��������� ������� � ������� ����
            {
                bool isSolar = false;
                bool isSandbox = false;
                bool isExit = false;
                if (sandbox.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) //���� ����� ��������� ��� �������� sandbox
                {
                    sandbox.setColor(sf::Color::Cyan); //�������� ���� �� Cyan
                    isSandbox = true;
                }
                else
                {
                    sandbox.setColor(sf::Color::White); //�������� ���� �� �����
                }
                if (exit.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) //���� ����� ��������� ��� �������� exit
                {
                    exit.setColor(sf::Color::Cyan); //�������� ���� �� Cyan
                    isExit = true;
                }
                else
                {
                    exit.setColor(sf::Color::White); //�������� ���� �� �����
                }
                if (solar.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) //���� ����� ��������� ��� �������� solar
                {
                    solar.setColor(sf::Color::Cyan); //�������� ���� �� Cyan
                    isSolar = true;
                }
                else
                {
                    solar.setColor(sf::Color::White); //�������� ���� �� �����
                }
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) //���� ������ ����� ������ ����
                {
                    if(isSolar) //���������� ���������������� ������� ������� ����
                    {
                        solar.setColor(sf::Color::Blue);
                    }
                    else if(isSandbox)
                    {
                        sandbox.setColor(sf::Color::Blue);
                    }
                    else if(isExit)
                    {
                        exit.setColor(sf::Color::Blue);
                    }
                }
                if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) //���� ������ ����� ������
                {
                    if(isSolar)
                    {
                        SetSolar(state); //���������������� ��������� �������
                    }
                    else if(isSandbox)
                    {
                        state = State::SANDBOX; //���������� ����� SANDBOX
                    }
                    else if(isExit)
                    {
                        window.close(); //����� �� ����������
                    }
                }
            }
        }

        if(state == State::SOLAR || state == State::SANDBOX) //���� ������ ���������� SOLAR ��� SANDBOX
        {

            double dt = (double)timer.getElapsedTime().asMicroseconds() / 1000000.0; //��������� ����� ��������� � �������� �����
            timer.restart(); //������� �������
            mulStatusLabel->setText("x" + std::to_string((int)timerMultiplier->getValue())); //��������� �������� ��������� �������


            for (int i = 0; i < planets.size(); i++)
            {
                planets.at(i)->ResetA(); //���������� ������� ������� ��������� ��� ���������
            }

            for (int i = 0; i < planets.size(); i++) //������ ������� ������ ������� �� ������
            {
                for (int j = 0; j < planets.size(); j++)
                {
                    if (i == j) //������� �� ������ ���� �� ����
                    {
                        continue;
                    }
                    try
                    {
                        double distance = planets.at(i)->GetDistance(*planets.at(j)); //������ ���������� ����� ���������
                        if(distance < planets.at(i)->d / 2 + planets.at(j)->d / 2) //���� ���������� ������ ����� �������� ������
                        {
                            if(planets.at(i)->mass <= planets.at(j)->mass) //���� ������ ������� ����� ������ ��� ������
                            {
                                planets.at(j)->Union(*planets.at(i)); //���������� �������
                                DeleteAt(i); //������� ������� �� �����
                            }
                            else //���� ������ ������� ����� ������ ��� ������
                            {
                                planets.at(i)->Union(*planets.at(j)); //���������� �������
                                DeleteAt(j); //������� ������� �� �����
                            }
                        }
                        else //���� ���������� ������ ����� ��������
                        {
                            planets.at(i)->Correct(*planets.at(j), distance); //������ ������� �� ��������� ����� ������� �� ������
                        }
                    }
                    catch(std::exception){}
                }
            }

            for (int i = 0; i < planets.size(); i++)
            {
                planets.at(i)->ChangePosition(dt, timerMultiplier->getValue()); //��������� ������� ������� �� ��������� � ��������� �������
                planets.at(i)->Move(); //��������� ������� ��������
                planets.at(i)->Rotate(dt, timerMultiplier->getValue()); //��������� �������� ������� �� ������� � ���������
            }

            if (isDrag) //���� ���������� ����� ����������� ������
            {
                sf::Vector2f pos = (sf::Vector2f)(startPos - sf::Mouse::getPosition());
                camera.setCenter(oldCenter + pos);
            }
        }

        window.clear();
        if(state == State::SOLAR || state == State::SANDBOX) //���� ���������� ������ SOLAR ��� SANDBOX
        {
            for (int i = 0; i < planets.size(); i++)
            {
                window.draw(*planets.at(i)->sprite); //���������� ��� �������
            }
            gui.draw(); //���������� ���������
        }
        else //���� ������ MENU
        {
            window.draw(menu); //���������� ������� ����
            window.draw(sandbox);
            window.draw(solar);
            window.draw(exit);
        }
        window.setView(camera); //��������� ������
        window.display();
    }

    return 0;
}
