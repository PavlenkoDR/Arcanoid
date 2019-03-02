#include <iostream>

#include "GameOver.h"

GameOver::GameOver( App* app )
{
    m_app = app;
    retryTexture.loadFromFile( "images/retry.png" );
    retrySprite.setTexture( retryTexture );
    retrySprite.setPosition( { ( m_app->GetSize().width  - retrySprite.getGlobalBounds().width ) / 2,
                               ( m_app->GetSize().height - retrySprite.getGlobalBounds().height ) * 2 / 3 } );

    font.loadFromFile("fonts/CyrilicOld.TTF");

    scoreText.setFont(font);
    scoreText.setCharacterSize( 60 );
    scoreText.setFillColor( sf::Color::White );
}

GameOver::~GameOver()
{
}

void GameOver::Repaint()
{
    m_app->GetRenderWindow().clear();
    m_app->GetRenderWindow().draw( scoreText );
    m_app->GetRenderWindow().draw( retrySprite );
    m_app->GetRenderWindow().display();
}

void GameOver::SetScore( size_t score )
{
    gameOverScore = score;
}

GameEvent GameOver::Start()
{
    scoreText.setString( "Score: " + std::to_string( gameOverScore ) );
    scoreText.setPosition( ( m_app->GetSize().width  - scoreText.getGlobalBounds().width ) / 2,
                           retrySprite.getPosition().y - retrySprite.getGlobalBounds().height );

    while ( m_app->IsOpen() )
    {
        sf::Event e;
        while ( m_app->PollEvent( e ) )
        {
            if ( e.type == sf::Event::Closed )
            {
                m_app->Close();
                return EXIT;
            }
        }
        if ( sf::Mouse::isButtonPressed( sf::Mouse::Left ) )
        {
            std::cout << "x " << sf::Mouse::getPosition().x << " y " << sf::Mouse::getPosition().y << std::endl;

            sf::Vector2f mouse = m_app->GetRenderWindow().mapPixelToCoords( sf::Mouse::getPosition( m_app->GetRenderWindow() ) );

            if ( sf::FloatRect( mouse.x, mouse.y, 12, 12 ).intersects( retrySprite.getGlobalBounds() ) )
            {
                std::cout << "GameOver Return" << std::endl;
                return NONE;
            }
        }
        Repaint();
    }
}
