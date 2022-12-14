//
// Created by iaren on 12/6/2022.
//

class Field final{
public:
    Field() { }

    void search_coincidence(int a){
        for (int i = 1; i <= a; i++)
            for (int j = 1; j <= a; j++) {
                if (grid[i][j].kind == grid[i + 1][j].kind)
                    if ((grid[i][j].kind == grid[i - 1][j].kind) or (grid[i - 1][j].kind == 19))
                        for (int n = -1; n <= 1; n++) {
                            grid[i + n][j].match++;
                            if (grid[i-1][j].kind == 19)
                                for (int m = -1; m <= 1; m++) grid[i+n][j+m].match=1;
                        }
                if (grid[i][j].kind == grid[i + 1][j].kind)
                    if ((grid[i][j].kind == grid[i - 1][j].kind) or (grid[i + 1][j].kind == 19))
                        for (int n = -1; n <= 1; n++) {
                            grid[i + n][j].match++;
                            if (grid[i+1][j].kind == 19)
                                for (int m = -1; m <= 1; m++) grid[i+n][j+m].match=1;
                        }
                if ((grid[i-1][j].kind == grid[i + 1][j].kind) and (grid[i][j].kind == 19))
                        for (int n = -1; n <= 1; n++)
                            for(int m = -1; m <= 1; m++)
                                grid[i + n][j + m].match++;

                if (grid[i][j].kind == grid[i][j + 1].kind)
                    if ((grid[i][j].kind == grid[i][j - 1].kind) or (grid[i][j + 1].kind == 19))
                        for (int n = -1; n <= 1; n++) {
                            grid[i][j+n].match++;
                            if (grid[i][j + 1].kind == 19)
                                for (int m = -1; m <= 1; m++) grid[i+m][j+n].match=1;
                        }
                if (grid[i][j].kind == grid[i][j + 1].kind)
                    if ((grid[i][j].kind == grid[i][j - 1].kind) or (grid[i][j - 1].kind == 19))
                        for (int n = -1; n <= 1; n++) {
                            grid[i][j+n].match++;
                            if (grid[i][j - 1].kind == 19)
                                for (int m = -1; m <= 1; m++) grid[i+m][j+n].match=1;
                        }
                if ((grid[i][j - 1].kind == grid[i][j + 1].kind) and (grid[i][j].kind == 19))
                    for (int n = -1; n <= 1; n++)
                        for(int m = -1; m <= 1; m++)
                            grid[i + n][j + m].match++;
            }
    }

    bool animation_move(int a, int ts, bool isMoving) {
        isMoving = false;
        for (int i = 1; i <= a; i++)
            for (int j = 1; j <= a; j++) {
                piece &p = grid[i][j];
                int dx, dy;
                for (int n = 0; n < 5; n++)   //????????????????
                {
                    dx = p.x - p.col * ts;
                    dy = p.y - p.row * ts;
                    if (dx) p.x -= dx / abs(dx);
                    if (dy) p.y -= dy / abs(dy);
                }
                if (dx || dy) isMoving = 1;
            }
    }

    bool animation_delete(int a, bool isMoving) {
        if (!isMoving)
            for (int i = 1; i <= a; i++)
                for (int j = 1; j <= a; j++)
                    if (grid[i][j].match) {
                        if (grid[i][j].kind == 19) {
                            for (int n = -1; n <= 1; n++) {
                                for (int m = -1; m <= 1; m++) {
                                    if (grid[i + n][j + m].alpha > 10) {
                                        grid[i + n][j + m].alpha -= 10;
                                        isMoving = true;
                                    }
                                }
                            }
                        }
                        if (grid[i][j].alpha > 10) {
                                grid[i][j].alpha -= 10;
                                isMoving = true;
                        }
                    }
        return isMoving;
    }

    void update_grid(int a, int ts, bool isMoving) {
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
    }

    void draw_grid(int a, int ts, sf::Sprite gems, sf::Vector2i offset) {
        for (int i = 1; i <= a; i++)
            for (int j = 1; j <= a; j++) {
                piece p = grid[i][j];
                gems.setTextureRect(sf::IntRect(p.kind * 100, 0, 99, 99));
                gems.setColor(sf::Color(255, 255, 255, p.alpha));
                gems.setPosition(p.x, p.y);
                gems.move(offset.x - ts, offset.y - ts);
                app.draw(gems);
            }
    }
};
#ifndef AAAAAAAA_FIELD_H
#define AAAAAAAA_FIELD_H

#endif //AAAAAAAA_FIELD_H
