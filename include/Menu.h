#ifndef MENU_H
#define MENU_H

#include "App.h"

class Menu
{
public:
    Menu( App* app );
    virtual ~Menu();
    GameEvent Start();
    void Repaint();

private:
    App* m_app;

    sf::Texture startTexture;
    sf::Texture backgroundTexture;

    sf::Sprite  startSprite;
    sf::Sprite backgroundSprite;
};
#endif // MENU_H
