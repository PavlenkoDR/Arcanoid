#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>
#include <list>

class Level
{
public:
    Level();
    ~Level();
    static std::list<sf::Sprite> GetLevel0( const std::vector<sf::Texture>& blockTextures );

private:
};

#endif // LEVEL_H
