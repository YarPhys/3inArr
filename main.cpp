#include <SFML/Graphics.hpp>
#include <SFML/Audio/Sound.hpp>
#include <ctime>
#include "Game.h"
#include "Score.h"
#include "Field.h"

Score score1 = Score();
Field field = Field();

int main() {
        srand(time(0));
        int a = 6;
        app.setFramerateLimit(60);

//        sf::SoundBuffer buffer;
//        buffer.loadFromFile("C:/prop.mp3");// тут загружаем в буфер что то
//        sf::Sound sound;
//        sound.setBuffer(buffer);
//        sound.play();

        sf::Texture t1, t2;
        t1.loadFromFile("C:/background.png");
        t2.loadFromFile("C:/gem.png");
        sf::Sprite background(t1), gems(t2);

        for (int i = 1; i <= a; i++)
            for (int j = 1; j <= a; j++) {
                grid[i][j].kind = rand() % 20;
                grid[i][j].col = j;
                grid[i][j].row = i;
                grid[i][j].x = j * ts;
                grid[i][j].y = i * ts;
            }

        int x0, y0, x, y;
        int click = 0;
        sf::Vector2i pos;
        bool isSwap = false, isMoving = false;

        while (app.isOpen()) {
            sf::Event e;
            while (app.pollEvent(e)) {
                if (e.type == sf::Event::Closed) {
                    app.close();
                }

                if (e.type == sf::Event::MouseButtonPressed)
                    if (e.key.code == sf::Mouse::Left) {
                        if (!isSwap && !isMoving) click++;
                        pos = sf::Mouse::getPosition(app) - offset;
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
                score1.losing_scores(); // score -= 400
                if (abs(x - x0) + abs(y - y0) == 1) {
                    swap(grid[y0][x0], grid[y][x]);
                    isSwap = 1;
                    click = 0;
                } else click = 1;
            }

            //Поиск совпадений
            field.search_coincidence(a);

            //Анимация движения
            isMoving = field.animation_move(a, ts, isMoving);

            //Анимация удаления
            isMoving = field.animation_delete(a, isMoving);

            //Получить счет
            sf::Text TStore;
            TStore = score1.get_score(a);

            //Второй обмен, если нет совпадения
            if (isSwap && !isMoving) {
                if (!flag) swap(grid[y0][x0], grid[y][x]);
                isSwap = 0;
            }

            //if score < 0 => Game Over
            score1.GameOver();

            //Обновить сетку
            field.update_grid(a, ts, isMoving);

            //Отрисовать фон
            app.draw(background);

            ///ОТРИСУЕМ ПЛАШКИ///
            field.draw_grid(a, ts, gems, offset);

            app.display();
        }
    return EXIT_SUCCESS;
}