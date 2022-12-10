#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include "Game.h"
#include "Score.h"
#include "Field.h"
#include "Control.h"

Score score1 = Score();
Field field = Field();
Control control = Control();

int main() {
    srand(time(0));
    int a = 7;
    app.setFramerateLimit(60);

//    sf::Music music;//создаем объект музыки
//    music.openFromFile("C:/prop.mp3");//загружаем файл
//    music.play();//воспроизводим музыку

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

    while (app.isOpen()) {
        // Закрытие приложения и проверка нажатия кнопки мыши
        control.mouse_event(click, isSwap, isMoving, pos);

        app.clear();

        // Управление мышью
        control.click(x0, y0, x, y, ts, score1, click, isSwap, isMoving, pos, offset);

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