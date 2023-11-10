#include "board.h"
#include <iostream>

Board::Board() {
    setup();
}

void Board::drawUI() {
    m_window.clear(sf::Color(250, 248, 239));

    sf::Texture boardTxt;
    boardTxt.loadFromFile("board.png");

    sf::Sprite boardImg;
    boardImg.setTexture(boardTxt);
    boardImg.setPosition(0, 102);
    m_window.draw(boardImg);

    sf::RectangleShape scoreBox(sf::Vector2f(150, 80));
    scoreBox.setPosition(10, 10);
    scoreBox.setFillColor(sf::Color(187, 173, 160, 100));
    m_window.draw(scoreBox);

    sf::Font font;
    if (!font.loadFromFile("digital-7.ttf")) {
        std::cout << "nie udalo sie zaladowac czcionki";
    }

    sf::Text title;
    title.setString("2048");
    title.setCharacterSize(80);
    title.setPosition(440, 0);
    title.setFont(font);
    title.setFillColor(sf::Color::Black);
    m_window.draw(title);
}

void Board::captureKeyboardInput() {
    sf::Event event;
    sf::Keyboard keyboard;
    while (m_window.isOpen()) {
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                m_window.close();
            }
        }
    }
}


void Board::setup() {
    m_window.create(sf::VideoMode(600, 700), "2048");
    drawUI();
    m_window.display();
    captureKeyboardInput();
}