#include "Snake.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
using namespace sf;
using namespace std;


void drawingSegment(RenderWindow& window, SEGMENT& seg) {
    RectangleShape square(Vector2f(EDGE, EDGE));
    square.setPosition(seg.getCoord().getX(), seg.getCoord().getY());
    square.setFillColor(Color::Green);
    window.draw(square);
}

void drawingSnake(RenderWindow& window, Snake& snake) {
    for (SEGMENT i : snake) {
        drawingSegment(window, i);
    }
}

void run(RenderWindow& window, Snake& snake) {
    drawingSnake(window, snake);
}

void getRandomFood(COORD& coord) {
    coord.setX(30 * (rand() % 40));
    coord.setY(30 * (rand() % 28));
}

void drawFood(RenderWindow& window, COORD coord) {
    RectangleShape square(Vector2f(EDGE, EDGE));
    square.setPosition(coord.getX(), coord.getY());
    square.setFillColor(Color::Red);
    window.draw(square);
}

void drawBorder(RenderWindow& window, float x1, float y1, float x2, float y2, sf::Color color) {
    sf::VertexArray border(sf::LinesStrip, 5);
    border[0].position = sf::Vector2f(x1, y1);
    border[1].position = sf::Vector2f(x2, y1);
    border[2].position = sf::Vector2f(x2, y2);
    border[3].position = sf::Vector2f(x1, y2);
    border[4].position = sf::Vector2f(x1, y1); 

    for (int i = 0; i < 5; ++i) {
        border[i].color = color;
    }
    window.draw(border);
}



int main() {
    RenderWindow window(VideoMode(1200, 900), "Snake");
    window.setFramerateLimit(60);
    Snake snake(COORD(0, 0));
   
    float x1 = 1.0f;
    float y1 = 1.0f;
    float x2 = MAX_COLUMN;
    float y2 = MAX_ROW;

    sf::Font font;
    if (!font.loadFromFile("UTM Helve.ttf")) {
        return EXIT_FAILURE;
    }

    sf::Text text;
    Text highcore;
    highcore.setFont(font);
    text.setFont(font);
    string hc = "Highest Core: ";
    string str = "Score: 0";
    highcore.setCharacterSize(24);
    highcore.setFillColor(Color::Red);
    highcore.setPosition(150, 850);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Blue);
    text.setPosition(10, 850);
    MOVE move = RIGHT;
    COORD food;
    getRandomFood(food);
    ifstream fin("highcore.txt");
    int x;
    fin >> x;
    fin.close();
    hc = hc + to_string(x);
    bool endgame = false;
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            if (Keyboard::isKeyPressed(Keyboard::Escape))
                window.close();
            if (Keyboard::isKeyPressed(Keyboard::Up))
                move = (move == DOWN ? DOWN : UP);
            else  if (Keyboard::isKeyPressed(Keyboard::Down))
                move = (move == UP ? UP : DOWN);
            else  if (Keyboard::isKeyPressed(Keyboard::Left))
                move = (move == RIGHT ? RIGHT : LEFT);
            else  if (Keyboard::isKeyPressed(Keyboard::Right))
                move = (move == LEFT ? LEFT : RIGHT);
            
        }
        window.clear(Color::White); 
        drawFood(window, food);
        drawBorder(window, x1, y1, x2, y2, Color::Red);
        run(window, snake);
        text.setString(str);
        highcore.setString(hc);
        window.draw(text);
        window.draw(highcore);
        str = "Score: " + std::to_string(snake.getSize() - 1);
        hc = "Highest Score: " + to_string(max(snake.getSize() - 1, x));
        if (snake.getHead()->getCoord().getX() == food.getX() && snake.getHead()->getCoord().getY() == food.getY()) {
            getRandomFood(food);
            snake.append();
        }
        window.display();
        sleep(milliseconds(50));
        if (!snake.move(move)) {
           std::cout << "Game Over!";
           endgame = true;
           break;
        }
    }
    if (snake.getSize() - 1 > x) {
        ofstream fout("highcore.txt");
        fout << snake.getSize() - 1;
        fout.close();
    }
    if (endgame) {
        Text gameover;
        gameover.setFont(font);
        string gv = "GAME OVER";
        gameover.setCharacterSize(60);
        gameover.setFillColor(Color::Red);
        gameover.setPosition(420, 350);
        gameover.setString(gv);
        while (window.isOpen()) {
            window.clear(Color::White);
            window.draw(gameover);
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed)
                    window.close();
                if (Keyboard::isKeyPressed(Keyboard::Escape))
                    window.close();
            }
            window.display();
        }
       
    }
    else
        window.close();
    return 0;
}
