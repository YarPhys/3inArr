#include <sstream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include "wtypes.h"
#include <iostream>
#include <SFML/Audio/Sound.hpp>
#include "Game.h"

using namespace std;
using namespace sf;

int ts = 100;
Vector2i offset(81, 26); // Положение плашек
int score = 0;
bool flag = true;

int main() {
        srand(time(0));
        int a = 6;
        RenderWindow app(VideoMode(1280, 720), "3 in arrow");
        app.setFramerateLimit(60);

//        sf::SoundBuffer buffer;
//        buffer.loadFromFile("C:/prop.mp3");// тут загружаем в буфер что то
//        sf::Sound sound;
//        sound.setBuffer(buffer);
//        sound.play();

        Texture t1, t2, t3;
        t1.loadFromFile("C:/background.png");
        t2.loadFromFile("C:/gem.png");

        Sprite background(t1), gems(t2);

        for (int i = 1; i <= a; i++)
            for (int j = 1; j <= a; j++) {
                grid[i][j].kind = rand() % 6;
                grid[i][j].col = j;
                grid[i][j].row = i;
                grid[i][j].x = j * ts;
                grid[i][j].y = i * ts;
            }

        int x0, y0, x, y;
        int click = 0;
        Vector2i pos;
        bool isSwap = false, isMoving = false;

        while (app.isOpen()) {
            Event e;
            while (app.pollEvent(e)) {
                if (e.type == Event::Closed) {
                    app.close();
                    //flag = -1;
                }

                if (e.type == Event::MouseButtonPressed)
                    if (e.key.code == Mouse::Left) {
                        if (!isSwap && !isMoving) click++;
                        pos = Mouse::getPosition(app) - offset;
                    }
            }
            app.clear();
            // Управление мышью
            if (click == 1) {
                x0 = pos.x / ts + 1;
                y0 = pos.y / ts + 1;
            }
            if (click == 2) {
                x = pos.x / ts + 1;
                y = pos.y / ts + 1;
                score -= 400;
                if (abs(x - x0) + abs(y - y0) == 1) {
                    swap(grid[y0][x0], grid[y][x]);
                    isSwap = 1;
                    click = 0;
                } else click = 1;
            }

            //Поиск совпадений
            for (int i = 1; i <= a; i++)
                for (int j = 1; j <= a; j++) {
                    if (grid[i][j].kind == grid[i + 1][j].kind)
                        if (grid[i][j].kind == grid[i - 1][j].kind)
                            for (int n = -1; n <= 1; n++) grid[i + n][j].match++;

                    if (grid[i][j].kind == grid[i][j + 1].kind)
                        if (grid[i][j].kind == grid[i][j - 1].kind)
                            for (int n = -1; n <= 1; n++) grid[i][j + n].match++;
                }

            //Анимация
            isMoving = false;
            for (int i = 1; i <= a; i++)
                for (int j = 1; j <= a; j++) {
                    piece &p = grid[i][j];
                    int dx, dy;
                    for (int n = 0; n < 5; n++)   //Скорость
                    {
                        dx = p.x - p.col * ts;
                        dy = p.y - p.row * ts;
                        if (dx) p.x -= dx / abs(dx);
                        if (dy) p.y -= dy / abs(dy);
                    }
                    if (dx || dy) isMoving = 1;
                }

            //Удаление анимации
            if (!isMoving)
                for (int i = 1; i <= a; i++)
                    for (int j = 1; j <= a; j++)
                        if (grid[i][j].match)
                            if (grid[i][j].alpha > 10) {
                                grid[i][j].alpha -= 10;
                                isMoving = true;
                            }

            //Получить счет
            for (int i = 1; i <= a; i++)
                for (int j = 1; j <= a; j++)
                    score += grid[i][j].match / 10;
            Font fnt; //переменная шрифта
            fnt.loadFromFile("C:/Windows/Fonts/STENCIL.TTF");
            std::ostringstream scoreStr;
            scoreStr << score;
            Text TStore(scoreStr.str(), fnt, 20); //Текст|Шрифт|Размер Символа
            TStore.setPosition(10, 10);//позиция на экране

            //Второй обмен, если нет совпадения
            if (isSwap && !isMoving) {
                if (!score) swap(grid[y0][x0], grid[y][x]);
                isSwap = 0;
            }

            //if score < 0 => Game Over
            if (score < 0) {
                app.close();
            }

            //Обновить сетку
            if (!isMoving) {
                for (int i = a; i > 0; i--)
                    for (int j = 1; j <= a; j++)
                        if (grid[i][j].match)
                            for (int n = i; n > 0; n--)
                                if (!grid[n][j].match) {
                                    swap(grid[n][j], grid[i][j]);
                                    break;
                                };

                for (int j = 1; j <= a; j++)
                    for (int i = a, n = 0; i > 0; i--)
                        if (grid[i][j].match) {
                            grid[i][j].kind = rand() % 4;
                            grid[i][j].y = -ts * n++;
                            grid[i][j].match = 0;
                            grid[i][j].alpha = 255;
                        }
            }

            app.draw(background);

            ///ОТРИСУЕМ ПЛАШКИ///
            for (int i = 1; i <= a; i++)
                for (int j = 1; j <= a; j++) {
                    piece p = grid[i][j];
                    gems.setTextureRect(IntRect(p.kind * 100, 0, 99, 99));
                    gems.setColor(Color(255, 255, 255, p.alpha));
                    gems.setPosition(p.x, p.y);
                    gems.move(offset.x - ts, offset.y - ts);
                    app.draw(gems);

                }
            app.draw(TStore); // рисовает поверх всех элементов
            app.display();
        }
    return EXIT_SUCCESS;
}