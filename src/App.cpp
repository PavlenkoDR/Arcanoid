#include <time.h>

#include "App.h"
#include "Level.h"
#include "Log.h"
#include "Game.h"
#include "GameOver.h"
#include "Menu.h"

App::App( Size wz, std::string title )
{
    app.create( sf::VideoMode( wz.width, wz.height ), title );
    app.setFramerateLimit( 60 );
    windowSize = wz;
}

App::~App()
{
    Log::PrintLog();
}

bool App::IsOpen()
{
    return app.isOpen();
}

bool App::PollEvent( sf::Event& e )
{
    return app.pollEvent( e );
}

void App::Close()
{
    app.close();
}

void App::Start()
{
    Game game( this );
    GameOver gameOver( this );
    Menu menu( this );
    GameEvent even = MENU;
    while ( IsOpen() )
    {
        game.SetLevel( 0 );
        if ( even == NONE )
        {
        }
        else if ( even == MENU )
        {
            menu.Start();
        }
        else if ( even == GAME_OVER )
        {
            gameOver.SetScore( game.GetScore() );
            even = gameOver.Start();
        }
        else if ( even == EXIT )
        {
            break;
        }
        even = game.Start();
    }
}


sf::RenderWindow& App::GetRenderWindow()
{
    return app;
}

sf::Texture App::LoadTexture( std::string textureFile )
{
    Log::GetStreamLog() << "LoadTexture: " << textureFile << "\n";
    sf::Texture t;
    t.loadFromFile( textureFile );
    return t;
}

const Size& App::GetSize() const
{
    return windowSize;
}
