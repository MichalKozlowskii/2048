#include "board.h"
#include <iostream>

Board::Board() {
    setup();
}

void Board::fillGrid() {
    for (int y = 1; y <= 4; y++) {
        for (int x = 1; x <= 4; x++) {
            Node tile(x, y, 0);
            m_grid.push_back(tile);
        }
    }
}

void Board::spawnTile() {
    int randomX, randomY, state = 0;
    bool wasSpawned = false;

    if ((1 + (rand() % 10)) == 1) {
        state = 4;
    }
    else {
        state = 2;
    }

    while (!wasSpawned) {
        randomX = 1 + (rand() % 4);
        randomY = 1 + (rand() % 4);
        for (std::list<Node>::iterator it = m_grid.begin(); it != m_grid.end(); it++) {
            if (randomX == it->getX() && randomY == it->getY()) {
                if (it->getState() == 0) {
                    it->setState(state);
                    it->setSpawnStatus(true);
                    wasSpawned = true;
                }
            }
        }
    }
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
            if (m_canMove) {
                if (keyboard.isKeyPressed(keyboard.W) || keyboard.isKeyPressed(keyboard.Up)) {
                    move(UP);
                }
                else if (keyboard.isKeyPressed(keyboard.S) || keyboard.isKeyPressed(keyboard.Down)) {
                    move(DOWN);
                }
                else if (keyboard.isKeyPressed(keyboard.A) || keyboard.isKeyPressed(keyboard.Left)) {
                    move(LEFT);
                }
                else if (keyboard.isKeyPressed(keyboard.D) || keyboard.isKeyPressed(keyboard.Right)) {
                    move(RIGHT);
                }
            }
        }
    }
}


void Board::move(Direction dir) {
    m_canMove = false;
    bool wasMoveMade = false;

    for (int counter = 3; counter >= 0; counter--) { // iteracja 4 razy, poniewa� plansza jest 4x4
        std::vector<Node> currRow; // tworzymy vector, w kt�rym b�d� wszystkie kom�rki danego rz�du/kolumny
        for (std::list<Node>::iterator it = m_grid.begin(); it != m_grid.end(); it++) {
            if (dir == RIGHT || dir == LEFT) {
                if (it->getY() == counter + 1) {
                    Node currNode(it->getX(), it->getY(), it->getState());
                    currRow.push_back(currNode); // wpisujemy do vectora wszystkie kom�rki z danego rz�du
                }
            }
            else if (dir == UP || dir == DOWN) {
                if (it->getX() == counter + 1) {
                    Node currNode(it->getX(), it->getY(), it->getState());
                    currRow.push_back(currNode); // wpisujemy do vectora wszystkie kom�rki z danej kolumny
                }
            }
        }
        bool wasMerged = false; // w jednym ruchu mo�emy po��czy� dwie p�ytki ze sob� tylko raz, wi�c deklarujemy zmienn� bool
        if (dir == RIGHT || dir == DOWN) {
            for (int i = 2; i >= 0; i--) { // iteracja od 3. pola do 1. pola
                for (int j = i; j < 3; j++) { // iteracja od numeru aktualnego pola do pola numer 3
                    if (currRow[j].getState() != 0) { // je�li aktualnie rozpatrywana kom�rka ma warto��
                        if (currRow[j].getState() == currRow[j + 1].getState() && !wasMerged) {
                            // je�li nast�pna kom�rka ma warto�� tak� jak aktualna i �adne po��czenie nie zosta�o jeszcze wykonane w tym rz�dzie
                            currRow[j + 1].setState(currRow[j].getState() * 2); // podwajamy warto�� nast�pnej kom�rki
                            currRow[j].setState(0); // ustawiamy warto�� aktualnej na 0
                            // w ten spos�b "��czymy p�ytki"
                            wasMerged = true;
                            wasMoveMade = true;
                        }
                        if (currRow[j + 1].getState() == 0) { // je�li nast�pna kom�rka nie ma warto�ci to
                            currRow[j + 1].setState(currRow[j].getState()); // ustawiamy warto�� nast�pnej kom�rki na warto�� aktualnej kom�rki
                            currRow[j].setState(0); // ustawiamy warto�� aktualnej kom�rki na 0
                            // w ten spos�b p�ytka si� "przesuwa"
                            wasMoveMade = true;
                        }
                    }
                }
            }
        }
        else if (dir == LEFT || dir == UP) {
            for (int i = 1; i < 4; i++) { // iteracja od 2. pola
                for (int j = i; j > 0; j--) { // iteracja od numeru aktualnego pola do pola numer 1
                    if (currRow[j].getState() != 0) {
                        if (currRow[j].getState() == currRow[j - 1].getState() && !wasMerged) {
                            currRow[j - 1].setState(currRow[j].getState() * 2);
                            currRow[j].setState(0);
                            wasMerged = true;
                            wasMoveMade = true;
                        }
                        if (currRow[j - 1].getState() == 0) {
                            currRow[j - 1].setState(currRow[j].getState());
                            currRow[j].setState(0);
                            wasMoveMade = true;
                        }
                    }
                }
            }
        }
        for (std::vector<Node>::iterator it = currRow.begin(); it != currRow.end(); it++) {
            it->insert(m_grid, it->getX(), it->getY(), it->getState()); // kom�rki z wektora aktualnego rz�du/kolumny wpisujemy do listy grid
            // "wrzucamy" je na plansze
        }
    }

    sf::Clock clock;
    while (!m_canMove) {
        sf::Time elapsed = clock.getElapsedTime();

        if (elapsed.asMilliseconds() >= 200) {
            m_canMove = true; // cooldown przed nast�pnym ruchem
        }
    }

    if (wasMoveMade) {
        this->spawnTile(); // je�li uda�o nam si� wykona� ruch to spawnujemy now� p�ytk�
    }
    this->refresh(); // update planszy
}


void Board::setup() {
    fillGrid();
    m_window.create(sf::VideoMode(600, 700), "2048");

    spawnTile();
    spawnTile();
    drawUI();
    refresh();
    captureKeyboardInput();
}

void Board::refresh() {

    drawUI();

    for (std::list<Node>::iterator it = m_grid.begin(); it != m_grid.end(); it++) {
        if (it->getState() != 0) {
            sf::Texture tileTxt;
            tileTxt.loadFromFile("tile" + std::to_string(it->getState()) + ".png");
            sf::Sprite tile;
            tile.setTexture(tileTxt);
            tile.setPosition(it->getPosX(), it->getPosY());

            // zolta obwodka na zespawnowanym kafelku
            if (it->getSpawnedStatus() == true) {
                it->setSpawnStatus(false);
                sf::RectangleShape rect(sf::Vector2f(128, 128));
                rect.setPosition(it->getPosX(), it->getPosY());
                rect.setFillColor(sf::Color::Transparent);
                rect.setOutlineThickness(2);
                rect.setOutlineColor(sf::Color::Yellow);
                m_window.draw(rect);
            }
            m_window.draw(tile);
        }
    }

    m_window.display();
}

