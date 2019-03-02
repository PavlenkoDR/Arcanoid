#ifndef APP_H
#define APP_H

#include <SFML/Graphics.hpp>
#include <vector>

enum GameEvent
{
    NONE,
    WIN,
    GAME_OVER,
    EXIT
};

struct Size
{
    size_t width;
    size_t height;
};

class App
{
public:
    App( Size mod, std::string title );
    ~App();
    bool IsOpen();
    bool PollEvent( sf::Event& e );
    void Close();
    void Start();
    const Size& GetSize() const;
    sf::RenderWindow& GetRenderWindow();
    static sf::Texture LoadTexture( std::string textureFile );
private:
    sf::RenderWindow app;

    Size windowSize;
};

#endif // APP_H
