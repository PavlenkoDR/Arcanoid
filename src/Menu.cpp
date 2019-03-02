#include "Menu.h"
#include <iostream>

Menu::Menu( App* app )
{
    m_app = app;
    startTexture.loadFromFile( "images/start.png" );
    backgroundTexture.loadFromFile( "images/background1.jpg" );
    startSprite.setTexture( startTexture );
    startSprite.setPosition( { ( m_app->GetSize().width  - startSprite.getGlobalBounds().width ) / 2,
                               ( m_app->GetSize().height - startSprite.getGlobalBounds().height ) / 2 } );
    backgroundSprite.setTexture( backgroundTexture );
}

Menu::~Menu()
{
}

void Menu::Repaint()
{
    m_app->GetRenderWindow().clear();
    m_app->GetRenderWindow().draw( backgroundSprite );
    m_app->GetRenderWindow().draw( startSprite );
    m_app->GetRenderWindow().display();
}

GameEvent Menu::Start()
{
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

            if ( sf::FloatRect( mouse.x, mouse.y, 12, 12 ).intersects( startSprite.getGlobalBounds() ) )
            {
                std::cout << "GameOver Return" << std::endl;
                return NONE;
            }
        }
        Repaint();
    }
}
