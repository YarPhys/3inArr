//
// Created by iaren on 12/5/2022.
//

#include <iostream>
struct piece
{
    int x, y, col, row, kind, match, alpha;

    piece() { match = 0; alpha = 255; }
} grid[30][30];

void swap(piece p1, piece p2)
{
    std::swap(p1.col, p2.col);
    std::swap(p1.row, p2.row);

    grid[p1.row][p1.col] = p1;
    grid[p2.row][p2.col] = p2;
}

void GetDesktopResolution(int& horizontal, int& vertical) {
    RECT desktop;
    const HWND hDesktop = GetDesktopWindow();
    GetWindowRect(hDesktop, &desktop);
    horizontal = desktop.right;
    vertical = desktop.bottom;
}

#ifndef AAAAAAAA_GAME_H
#define AAAAAAAA_GAME_H

#endif //AAAAAAAA_GAME_H
