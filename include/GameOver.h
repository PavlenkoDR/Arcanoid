#ifndef GAMEOVER_H
#define GAMEOVER_H

#include "App.h"

class GameOver
{
public:
    GameOver( App* app );
    virtual ~GameOver();
    GameEvent Start();
    void Repaint();
    void SetScore( size_t score );

private:
    App* m_app;

    sf::Texture retryTexture;
    sf::Sprite  retrySprite;
    sf::Font font;
    sf::Text scoreText;

    size_t gameOverScore = 0;
};

#endif // GAMEOVER_H
