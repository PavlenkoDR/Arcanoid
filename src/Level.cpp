#include <iostream>

#include "Level.h"
#include "Log.h"

Level::Level()
{
    //ctor
}

Level::~Level()
{
    //dtor
}

std::list<sf::Sprite> Level::GetLevel0( const std::vector<sf::Texture>& blockTextures )
{
    std::list<sf::Sprite> blocks;

    for ( size_t i = 1; i <= 10; ++i )
    {
        for ( size_t j = 1; j <= 10; ++j )
        {
            sf::Sprite block;
            block.setTexture( blockTextures[0] );
            block.setPosition( i * ( blockTextures[0].getSize().x + 4 ), 10 + j * ( blockTextures[0].getSize().y + 4 ) );
            blocks.push_back( block );
        }
    }
    Log::GetStreamLog() << "GetLevel0: blocks size" << blocks.size() << "\n";

    return blocks;
}
