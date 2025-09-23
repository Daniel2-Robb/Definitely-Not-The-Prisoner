
#include <SFML/Graphics.hpp>

#include "Game.h"

int main()
{
    //std::cout << "Hello World!" << std::endl;

    sf::RenderWindow window(sf::VideoMode(1080, 720), "Definitely-Not-The-Prisoner");
    window.setKeyRepeatEnabled(false);

    Game game(window);

    if (!game.init())
    {
        return -1;
    }

    sf::Clock clock;

    while (window.isOpen())
    {
        // Calculate delta time
        sf::Time time = clock.restart();
        float dt = time.asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed ||
                event.type == sf::Event::KeyReleased)
            {
                game.keyboardInput(event);
            }
        }

        game.update(dt);

        window.clear(sf::Color::Cyan);
        game.render();
        window.display();
    }
    
    return 0;
}