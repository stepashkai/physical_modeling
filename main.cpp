#include <iostream>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <cmath>
#include <iostream>
#include <string>
#include <list>
#include "planet.hpp"
#include <ctime>

//перечисление с состояниями программы
enum State
{
    SOLAR, SANDBOX, MENU
};


std::list<Planet> planets; //коллекция планет
sf::View defaultCamera; //позиция и размер камеры по умолчанию

//создание планеты
//выходные данные - указатель на созданную планету
//входные данные
//posX - позиция планеты по Х
//posY - позиция планеты по Y
//vX - скорость планеты по X
//vY - скорость планеты по Y
//aX - ускорение планеты по X
//aY - ускорение планеты по Y
//mass - масса планеты
//d - диаметр планеты
//rotation - вращение планеты
//filepath - путь к фалу текстуры
Planet InitPlanet(double posX, double posY, double vX, double vY, double aX, double aY, double mass, double d, double rotation, std::string filepath)
{
    sf::Vector2f pos(posX, posY);
    sf::Vector2f v(vX, vY);
    sf::Vector2f a(aX, aY);
    sf::Texture texture;
    texture.loadFromFile(filepath);
    Planet planet(filepath, pos, v, a, mass, d, rotation);
    return planet;
}

//удаление планеты
//входные данные
//i - индекс планеты в векторе планет
void DeleteAt(std::list<Planet>::iterator it)
{
    if(it != planets.end())
    {
        it = planets.erase(it);
    }
    else
    {
        planets.pop_back();
    }
}

//удаление всех планет в листе планет
void Clear()
{
    std::list<Planet>::iterator i = planets.begin();
    while(planets.size() != 0)
    {
        i = planets.erase(i);
    }
}

//инициализация солнечной системы
void InitSolarSystem()
{
    planets.push_back(InitPlanet(595, 360, 0, 0, 0, 0, 1.989E30, 40, 100, "resources\\planets\\0.png"));//солнце
    planets.push_back(InitPlanet(445, 360, 0, -0.000029783, 0, 0, 5.972E24, 10, 150, "resources\\planets\\1.png"));//земля
    planets.push_back(InitPlanet(537, 360, 0, -0.00004787, 0, 0, 3.33022E23, 4, 100, "resources\\planets\\2.png"));//меркурий
    planets.push_back(InitPlanet(487, 360, 0, -0.00003502, 0, 0, 4.867E24, 12, 150, "resources\\planets\\3.png"));//венера
    planets.push_back(InitPlanet(389, 360, 0, -0.00002413, 0, 0, 6.39E23, 8, -150, "resources\\planets\\4.png"));//марс
    planets.push_back(InitPlanet(-183, 360, 0, -0.00001307, 0, 0, 1.898E27, 30, -70, "resources\\planets\\5.png"));//юпитер
    planets.push_back(InitPlanet(-835, 360, 0, -0.00000969, 0, 0, 5683E26, 30, -50, "resources\\planets\\6.png"));//сатурн
    planets.push_back(InitPlanet(-2266, 360, 0, -0.00000681, 0, 0, 8.681E25, 25, 100, "resources\\planets\\7.png"));//уран
    planets.push_back(InitPlanet(-3955, 360, 0, -0.00000543, 0, 0, 1.024E26, 30, -100, "resources\\planets\\8.png"));//нептун
}

//создание label
//выходные данные - объект типа tgui::Label::Ptr
//входные данные
//text - текст на форме
//x - позиция по X
//y - позиция по Y
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

//создание textbox
//выходные данные - объект типа tgui::TextBox::Ptr
//входные данные
//text - текст на форме
//x - позиция по X
//y - позиция по Y
tgui::TextBox::Ptr CreateTextBox(std::string text, int x, int y)
{
    tgui::TextBox::Ptr textBox = tgui::TextBox::create();
    textBox->setText(text);
    textBox->setSize(100, 20);
    textBox->setPosition(x, y);
    return textBox;
}

//смена статуса приложения на меню
//входные данные
//status - объект перечисления для изменения статуса приложения
//camera - объект камеры
void SetMenu(State &status, sf::View &camera)
{
    camera = sf::View(defaultCamera);
    status = State::MENU;
    Clear();
}

//смена статуса приложения на симуляцию солнечной системы
//входные данные
//status - объект перечисления для изменения статуса приложения
void SetSolar(State &status)
{
    status = State::SOLAR;
    InitSolarSystem();
}



int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(0));


    sf::Texture menuT, sandboxT, exitT, solarT; //инициализация текстур для кнопок меню
    menuT.loadFromFile("resources\\interface\\menu.png"); //установка пути к текстуре
    menuT.setSmooth(true); //устанвка размытия текстуры
    sandboxT.loadFromFile("resources\\interface\\sandbox.png");
    sandboxT.setSmooth(true);
    exitT.loadFromFile("resources\\interface\\exit.png");
    exitT.setSmooth(true);
    solarT.loadFromFile("resources\\interface\\solar.png");
    solarT.setSmooth(true);
    sf::Sprite menu, sandbox, exit, solar, back; //инициализация спратов для кнопок меню
    menu.setTexture(menuT); //установка текстуры в спрайт
    menu.setScale(2.0/3.0, 2.0/3.0); //установка размеров спрайта
    sandbox.setTexture(sandboxT);
    sandbox.setScale(0.75, 0.75);
    exit.setTexture(exitT);
    exit.setScale(0.75, 0.75);
    solar.setTexture(solarT);
    solar.setScale(0.75, 0.75);


    State state = State::MENU; //установка начального статуса приложения


    sf::RenderWindow window(sf::VideoMode(1280, 720), "Planets"); //создание окна
    tgui::Gui gui(window); //создание менеджера интерфейса


    tgui::TextBox::Ptr vXTextBox = CreateTextBox("0", window.getSize().x - 100 - 5, 5); //создание текстбоксов для ввода параметров планет
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

    tgui::Slider::Ptr timerMultiplier = tgui::Slider::create(1, 1000000); //добавление слайдера, которым можно регулировать ускорение времени
    timerMultiplier->setPosition(timerLabel->getSize().x + 10,7);
    timerMultiplier->setStep(1);
    timerMultiplier->setSize(850, timerMultiplier->getSize().y);
    gui.add(timerMultiplier);

    tgui::Label::Ptr mulStatusLabel = CreateLabel("x1", timerLabel->getSize().x + 20 + timerMultiplier->getSize().x, 5);
    gui.add(mulStatusLabel);




    sf::Clock timer; //таймер для симуляции
    sf::View camera; //объект камеры
    camera.setSize((sf::Vector2f)window.getSize());
    bool isDrag = false;
    sf::Vector2i startPos;
    sf::Vector2f oldCenter;
    camera.setCenter(window.getSize().x / 2, window.getSize().y / 2);
    //planets.reserve(1000);
    defaultCamera = sf::View(camera);


    menu.setPosition(sf::Vector2f(0,0)); //установка позиций элементов меню
    solar.setPosition(sf::Vector2f(window.getSize().x/2 - solarT.getSize().x * solar.getScale().x/2, 330));
    sandbox.setPosition(sf::Vector2f(window.getSize().x/2 - sandboxT.getSize().x * sandbox.getScale().x/2, 430));
    exit.setPosition(sf::Vector2f(window.getSize().x/2 - exitT.getSize().x * exit.getScale().x/2, 530));





    for (std::list<Planet>::iterator planet = planets.begin(); planet != planets.end(); planet++)
    {
        planet->sprite.setPosition(planet->position); //установка позиций спрайтов всех планет
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) //обработка событий
        {
            if (event.type == sf::Event::Closed) //событие закрытия окна
            {
                window.close();
            }
            if(state == State::SOLAR || state == State::SANDBOX) //обработка событий, когда активна симуляция
            {
                gui.handleEvent(event);
                if (event.type == sf::Event::MouseWheelMoved) //событие при вращении колесика мыши
                {
                    camera.zoom(1 - (float)event.mouseWheel.delta * 0.05); //изменение размера области отрисовки
                }
                if (event.type == sf::Event::KeyPressed) //обработка событий нажатия клавиш
                {
                    if (event.key.code == sf::Keyboard::D) //если нажата клавиша D
                    {
                        if (planets.size() > 0)
                        {
                            DeleteAt(planets.end()); //удалить последнюю планету
                        }
                    }
                    if (event.key.code == sf::Keyboard::Escape) //если нажата Esc
                    {
                        SetMenu(state, camera); //выйти в меню
                    }
                }
                if (event.type == sf::Event::MouseButtonPressed) //обработка событий нажатия кнопки мыши
                {
                    if (event.mouseButton.button == sf::Mouse::Right) //если нажата правая кнопка
                    {
                        isDrag = true;
                        startPos = sf::Mouse::getPosition(); //запомнить центр камеры и место нажатия для перемещаения области отрисовки
                        oldCenter = camera.getCenter();
                    }
                    if(event.mouseButton.button == sf::Mouse::Left) //если нажата левая кнопка
                    {
                        int x = event.mouseButton.x;
                        int y = event.mouseButton.y;
                        if((y > 30 || x > 1000 ) && (x < 1170 || y > 130))
                        {
                            try //считать введенные данные и создать планету на их основе
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
                if (event.type == sf::Event::MouseButtonReleased) //если кнопка мыши отжата
                {
                    if (event.mouseButton.button == sf::Mouse::Right) //если правая кнопка
                    {
                        isDrag = false; //перетаскивание окончено
                    }
                }
            }
            else //обработка событий в главном меню
            {
                bool isSolar = false;
                bool isSandbox = false;
                bool isExit = false;
                if (sandbox.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) //если мышка находится над спрайтом sandbox
                {
                    sandbox.setColor(sf::Color::Cyan); //изменить цвет на Cyan
                    isSandbox = true;
                }
                else
                {
                    sandbox.setColor(sf::Color::White); //изменить цвет на белый
                }
                if (exit.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) //если мышка находится над спрайтом exit
                {
                    exit.setColor(sf::Color::Cyan); //изменить цвет на Cyan
                    isExit = true;
                }
                else
                {
                    exit.setColor(sf::Color::White); //изменить цвет на белый
                }
                if (solar.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) //если мышка находится над спрайтом solar
                {
                    solar.setColor(sf::Color::Cyan); //изменить цвет на Cyan
                    isSolar = true;
                }
                else
                {
                    solar.setColor(sf::Color::White); //изменить цвет на белый
                }
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) //если нажата левая кнопка мыши
                {
                    if(isSolar) //установить соответствующему спрайту голубой цвет
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
                if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) //если отжата левая кнопка
                {
                    if(isSolar)
                    {
                        SetSolar(state); //инициализировать солнечную систему
                    }
                    else if(isSandbox)
                    {
                        state = State::SANDBOX; //установить режим SANDBOX
                    }
                    else if(isExit)
                    {
                        window.close(); //выйти из приложения
                    }
                }
            }
        }

        if(state == State::SOLAR || state == State::SANDBOX) //если статус приложение SOLAR или SANDBOX
        {

            double dt = (double)timer.getElapsedTime().asMicroseconds() / 1000000.0; //посчитать время прошедшее с прошлого кадра
            timer.restart(); //рестарт таймера
            mulStatusLabel->setText("x" + std::to_string((int)timerMultiplier->getValue())); //установка текущего умножения времени


            for (std::list<Planet>::iterator planet = planets.begin(); planet != planets.end(); planet++)
            {
                planet->ResetA(); //установить планете нулевое ускорения для пересчёта
            }

            for (std::list<Planet>::iterator planetI = planets.begin(); planetI != planets.end(); planetI++) //расчёт влияния каждой планеты на каждую
            {
                for (std::list<Planet>::iterator planetJ = planets.begin(); planetJ != planets.end(); planetJ++)
                {
                    if (planetI == planetJ) //планета не влияет сама на себя
                    {
                        continue;
                    }
                    try
                    {
                        double distance = planetI->GetDistance(*planetJ); //расчёт расстояния между планетами
                        if(distance < planetI->d / 2 + planetJ->d / 2) //если расстояние меньше суммы радиусов планет
                        {
                            if(planetI->mass <= planetJ->mass) //если первая планета весит больше чем вторая
                            {
                                planetJ->Union(*planetI); //объединить планеты
                                if(planetI != planets.end())
                                {
                                    planetI = planets.erase(planetI);
                                    if(planetI != planets.begin())
                                    {
                                        planetI--;
                                    }
                                }
                                else
                                {
                                    planets.pop_back();
                                }
                            }
                            else //если вторая планета весит больше чем первая
                            {
                                planetI->Union(*planetJ); //объединить планеты
                                if(planetJ != planets.end())
                                {
                                    planetJ = planets.erase(planetJ);
                                    if(planetJ != planets.begin())
                                    {
                                        planetJ--;
                                    }
                                }
                                else
                                {
                                    planets.pop_back();
                                }
                            }
                        }
                        else //если расстояние больше суммы радиусов
                        {
                            planetI->Correct(*planetJ, distance); //внести влияние на ускорение одной планеты на друную
                        }
                    }
                    catch(std::exception){}
                }
            }

            for (std::list<Planet>::iterator planet = planets.begin(); planet != planets.end(); planet++)
            {
                planet->ChangePosition(dt, timerMultiplier->getValue()); //изменение позиции планеты по ускорению и множителю времени
                planet->Move(); //изменение позиций спрайтов
                planet->Rotate(dt, timerMultiplier->getValue()); //изменение вращения планеты по таймеру и множителю
            }

            if (isDrag) //если установлен режим перемещения камеры
            {
                sf::Vector2f pos = (sf::Vector2f)(startPos - sf::Mouse::getPosition());
                camera.setCenter(oldCenter + pos);
            }
        }

        window.clear();
        if(state == State::SOLAR || state == State::SANDBOX) //если установлен статус SOLAR или SANDBOX
        {
            if(planets.size() != 0)
            {
                for (std::list<Planet>::iterator planet = planets.begin(); planet != planets.end(); planet++)
                {
                    window.draw(planet->sprite); //отрисовать все планеты
                }
            }
            gui.draw(); //отрисовать интерфейс
        }
        else //если статус MENU
        {
            window.draw(menu); //отрисовать спрайты меню
            window.draw(sandbox);
            window.draw(solar);
            window.draw(exit);
        }
        window.setView(camera); //установка камеры
        window.display();
    }

    return 0;
}
