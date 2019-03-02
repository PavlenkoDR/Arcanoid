#include <iostream>

#include "Game.h"
#include "Log.h"
#include "Level.h"

Game::Game( App* app ) :
    m_app( app )
{
    blockTextures.push_back( App::LoadTexture( "images/block01.png" ) );
    backgroundTexture.loadFromFile( "images/background.jpg" );
    ballTexture.loadFromFile( "images/ball.png" );
    paddleTexture.loadFromFile( "images/paddle.png" );
    heartTexture = App::LoadTexture( "images/heart.png" );

    for ( int i = 0; i < 5; ++i )
    {
        sf::Sprite heart;
        heart.setTexture( heartTexture );
        heart.setScale( 0.1, 0.1 );
        heart.setPosition( 5 + ( heart.getGlobalBounds().width + 1 ) * i, 5 );
        Log::GetStreamLog() << "App: " << i << "pos " << heart.getPosition().x << "x" << heart.getPosition().y << "\n";
        heartSprites.push_back( heart );
    }

    backgroundSprite.setTexture( backgroundTexture );

    paddleSprite.setTexture( paddleTexture );
    paddleSprite.setPosition( ( m_app->GetSize().width - paddleSprite.getGlobalBounds().width ) / 2,
                                m_app->GetSize().height - paddleSprite.getGlobalBounds().height );

    ballSprite.setTexture( ballTexture );

    font.loadFromFile("fonts/CyrilicOld.TTF");

    scoreText.setFont(font);
    scoreText.setPosition( heartSprites.back().getPosition().x + heartSprites.back().getGlobalBounds().width + 5, 0 );
    scoreText.setString( "Score: 0" );
    scoreText.setCharacterSize( 20 );
    scoreText.setFillColor( sf::Color::Black );

    lifes = 5;
    score = 0;
    lvlCount = 0;
}

Game::~Game()
{
    //dtor
}

void Game::Repaint()
{
    m_app->GetRenderWindow().clear();
    m_app->GetRenderWindow().draw( backgroundSprite );
    m_app->GetRenderWindow().draw( ballSprite );
    m_app->GetRenderWindow().draw( paddleSprite );

    for ( auto& block : blockSprites )
    {
        m_app->GetRenderWindow().draw( block );
    }

    for ( auto& heart : heartSprites )
    {
        m_app->GetRenderWindow().draw( heart );
    }

    scoreText.setString( "Score: " + std::to_string( score ) );
    m_app->GetRenderWindow().draw( scoreText );

    m_app->GetRenderWindow().display();
}

void Game::SetLevel( size_t lvl )
{
    blockSprites.clear();
    switch( lvl )
    {
    case 0:
        blockSprites = Level::GetLevel0( blockTextures );
        break;
    default:
        blockSprites = Level::GetLevel0( blockTextures );
        break;
    }
}

size_t Game::GetScore() const
{
    return gameOverScore;
}

GameEvent Game::Start()
{
    srand(time(0));
    float dx = 5 + lvlCount;
    float dy = -5 - lvlCount;
    std::cout << lvlCount << std::endl;
    float x = paddleSprite.getPosition().x + paddleSprite.getGlobalBounds().width / 2;
    float y = paddleSprite.getPosition().y - 15;
    ballSprite.setPosition( x, y );

    for ( int i = 0; i < 5; ++i )
    {
        heartSprites[i].setPosition( 5 + ( heartSprites[i].getGlobalBounds().width + 1 ) * i, 5 );
    }

    int lastSpeed = 0;

    bool continueGame = false;

    sf::Vector2i prewPosition = sf::Mouse::getPosition();

    lifes = 5;

    while ( m_app->IsOpen() )
    {
        sf::Event e;
        lastSpeed = 0;

        while ( m_app->PollEvent( e ) )
        {
            if ( e.type == sf::Event::Closed )
            {
                m_app->Close();
                return EXIT;
            }

            sf::Vector2i position = sf::Mouse::getPosition();
            int xDelta = prewPosition.x - position.x;
            int yDelta = prewPosition.y - position.y;

            if ( ( e.type == sf::Event::MouseMoved ) && ( xDelta != 0 ) )
            {
                if ( ( paddleSprite.getPosition().x > 0 ) && ( xDelta < 0 ) )
                {
                    lastSpeed = -6;
                }
                else if ( ( paddleSprite.getPosition().x < m_app->GetSize().width - paddleSprite.getGlobalBounds().width ) &&
                     ( xDelta > 0 ) )
                {
                    lastSpeed = 6;
                }
                prewPosition = position;
                sf::Mouse::setPosition( { m_app->GetSize().width / 2, m_app->GetSize().height / 2 }, m_app->GetRenderWindow() );
            }
        }

        if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) )
        {
            continueGame = true;
        }

        if ( ( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) ) &&
             ( paddleSprite.getPosition().x < m_app->GetSize().width - paddleSprite.getGlobalBounds().width ) )
        {
            lastSpeed = 6;
        }

        if ( ( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) ) &&
             ( paddleSprite.getPosition().x > 0 ) )
        {
            lastSpeed = -6;
        }

        if ( lastSpeed != 0 )
        {
            paddleSprite.move( lastSpeed, 0 );
            if ( !continueGame )
            {
                x += lastSpeed;
            }
        }

        if ( continueGame )
        {
            x += dx;
            bool changeScore = false;
            for ( auto i = blockSprites.begin(); i != blockSprites.end(); i++ )
            {
                if ( sf::FloatRect( x + 3, y + 3, 6, 6 ).intersects( i->getGlobalBounds() ) )
                {
                    i = blockSprites.erase( i );
                    dx = -dx;
                    ++score;
                    std::cout << blockSprites.size() << std::endl;
                }
            }

            y += dy;
            for ( auto i = blockSprites.begin(); i != blockSprites.end(); i++ )
            {
                if ( sf::FloatRect( x + 3, y + 3, 6, 6 ).intersects( i->getGlobalBounds() ) )
                {
                    i = blockSprites.erase( i );
                    dy = -dy;
                    ++score;
                    if ( dx == 0 )
                    {
                        dx = rand() % ( 9 + lvlCount ) - ( 9 + lvlCount ) / 2;
                    }
                    std::cout << blockSprites.size() << std::endl;
                }
            }

            if ( blockSprites.size() == 0 )
            {
                lvlCount++;
                return WIN;
            }

            if ( x <= 0 )
            {
                dx = -dx;
                x = 0;
            }
            if ( x >= m_app->GetSize().width - ballSprite.getGlobalBounds().width )
            {
                dx = -dx;
                x = m_app->GetSize().width - ballSprite.getGlobalBounds().width;
            }
            if ( y < 0 )
            {
                dy = -dy;
                y = 0;
            }
            if ( y > m_app->GetSize().height )
            {
                heartSprites[lifes - 1].setPosition( -100, 0 );
                x = paddleSprite.getPosition().x + paddleSprite.getGlobalBounds().width / 2;
                y = paddleSprite.getPosition().y - 15;
                dy = -dy;
                --lifes;
                continueGame = false;
                if ( lifes == 0 )
                {
                    gameOverScore = score;
                    score = 0;
                    return GAME_OVER;
                }
            }

            if ( sf::FloatRect( x, y, 12, 12 ).intersects( paddleSprite.getGlobalBounds() ) )
            {
                if ( lastSpeed != 0 )
                {
                    dy = -6 - lvlCount;
                    dx = 0;
                }
                else
                {
                    dy = -( rand() % 4 + 2 + lvlCount);
                    if ( dx == 0 )
                    {
                        dx = rand() % ( 9 + lvlCount ) - ( 9 + lvlCount ) / 2;
                    }
                }
            }
        }

        ballSprite.setPosition( x, y );
        Repaint();
    }
}
