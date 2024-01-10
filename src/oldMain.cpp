//#include <SFML/Graphics.hpp>
//#include <imgui-SFML.h>
//#include <imgui.h>
//#include <math.h>
//#include <utility>
//#include <array>
//#include "hueShift.h"
//
///*
//Credits:
//SFML TUTORIAL: https://youtube.com/playlist?list=PL21OsoBLPpMOO6zyVlxZ4S4hwkY_SLRW9&si=a5a36BH9Cb73GeOj
//*/
//
////Set Up Screen Res and Scaling
//const std::pair<uint32_t, uint32_t> SCREEN_RES = { 320, 200 }; //resolution of window
//const std::pair<uint32_t, uint32_t> SCREEN_SIZE = { 1280, 800 }; //dimensions of window
//const int xPixelRatio = SCREEN_SIZE.first / SCREEN_RES.first;
//const int yPixelRatio = SCREEN_SIZE.second / SCREEN_RES.second;
//
//int main()
//{
//    auto window = sf::RenderWindow{ {SCREEN_SIZE.first, SCREEN_SIZE.second}, "Raycasting" };
//    window.setFramerateLimit(60);
//    //ImGui::SFML::Init(window);
//
//    //Set up world
//
//
//    int gridSizeX = 64;
//    int gridArea = gridSizeX * gridSizeX;
//
//    std::vector<sf::RectangleShape> rectVector;
//    rectVector.reserve(gridArea);
//    float squareSize = SCREEN_SIZE.second / gridSizeX;
//    for (int index = 0; index < gridArea; ++index)
//    {
//        sf::RectangleShape square{ sf::Vector2f(squareSize, squareSize) };
//        square.setPosition(index % gridSizeX * squareSize, index / gridSizeX * squareSize);
//        const double hueShiftDegrees = (double)index / gridArea * 30.0f;
//        sf::Color squareColor = hueShift::hueShift(sf::Color(150, 0, 0, 255), hueShiftDegrees);
//        square.setFillColor(squareColor);
//        rectVector.emplace_back(square);
//    }
//
//    sf::Clock clock;
//    while (window.isOpen())
//    {
//        for (auto event = sf::Event{}; window.pollEvent(event);)
//        {
//            //ImGui::SFML::ProcessEvent(window, event);
//
//            if (event.type == sf::Event::Closed)
//            {
//                window.close();
//            }
//        }
//
//        //ImGui::SFML::Update(window, clock.restart());
//
//        //ImGui::Begin("Hello, world!");
//        //ImGui::Button("Look at this pretty button");
//        //ImGui::End();
//
//        window.clear();
//
//        //ImGui::SFML::Render(window);
//
//
//        for (sf::RectangleShape& rect : rectVector)
//        {
//            sf::Color rectColor = rect.getFillColor();
//            rect.setFillColor(hueShift::hueShift(rectColor, 1.));
//            window.draw(rect);
//
//        }
//        window.display();
//    }
//
//    //ImGui::SFML::Shutdown();
//}
//
