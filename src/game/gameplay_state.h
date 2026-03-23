#pragma once

class GamePlayState {
    public:
    int characterX = 0;
    int characterY = 0;
    int screenX = 0;
    int screenY = 0;

    void moveCharacter(int x, int y) { characterX += x; characterY += y; }
    void moveScreen(int x, int y) { screenX += x; screenY += y; }
    void RequestMapChange();
};
