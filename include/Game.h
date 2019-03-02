#ifndef GAME_H
#define GAME_H

#include<list>

#include "App.h"

class Game
{
public:
    Game( App* app );
    ~Game();
    GameEvent Start();
    void Repaint();
    void SetLevel( size_t lvl );
    size_t GetScore() const;

private:
    App* m_app;

    sf::Texture backgroundTexture;
    sf::Texture ballTexture;
    sf::Texture paddleTexture;
    sf::Texture heartTexture;
    std::vector<sf::Texture> blockTextures;

    sf::Sprite backgroundSprite;
    sf::Sprite ballSprite;
    sf::Sprite paddleSprite;
    std::list<sf::Sprite> blockSprites;
    std::vector<sf::Sprite> heartSprites;

    size_t lifes = 5;
    size_t score = 0;
    size_t gameOverScore = 0;
    int lvlCount = 0;

    sf::Font font;
    sf::Text scoreText;
};

#endif // GAME_H
