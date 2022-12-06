//
// Created by iaren on 12/6/2022.
//

#include <sstream>
#include "wtypes.h"

class Score final{
private:
    int score;

public:
    Score(): score(400) { }

    sf::Text get_score(int a){
        for (int i = 1; i <= a; i++)
            for (int j = 1; j <= a; j++)
                score += grid[i][j].match / 10;
        sf::Font fnt; //переменная шрифта
        fnt.loadFromFile("C:/Windows/Fonts/STENCIL.TTF");
        std::ostringstream scoreStr;
        scoreStr << score;
        sf::Text TStore(scoreStr.str(), fnt, 20); //Текст|Шрифт|Размер Символа
        TStore.setPosition(10, 10);//позиция на экране
        app.draw(TStore); // рисовает поверх всех элементов
        return TStore;
    }

    int losing_scores() {
        score -= 400;
    }

    void GameOver() {
        if (score < 0) {
            app.close();
        }
    }
};

#ifndef AAAAAAAA_SCORE_H
#define AAAAAAAA_SCORE_H

#endif //AAAAAAAA_SCORE_H
