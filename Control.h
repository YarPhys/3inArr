//
// Created by iaren on 12/6/2022.
//

class Control final {
public:
    Control() { }

    void click(int &x0, int &y0, int &x, int &y, int &ts, Score &score1, int &click, bool &isSwap, bool &isMoving,
              sf::Vector2i &pos, sf::Vector2i &offset) {
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
    }

    void mouse_event(int &click, bool &isSwap, bool &isMoving, sf::Vector2i &pos) {
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
    }
};
#ifndef AAAAAAAA_CONTROL_H
#define AAAAAAAA_CONTROL_H

#endif //AAAAAAAA_CONTROL_H
