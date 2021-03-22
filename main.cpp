#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

sf::Texture openTexture(const char *NAME_IMAGE)
{
    sf:: Texture TEXTURE;
    if(!TEXTURE.loadFromFile(NAME_IMAGE))
    {
        std::cout << "error image " << NAME_IMAGE << std::endl;
    }
    return TEXTURE;
}

int main()
{
    sf::Texture blockImg;
    sf::Music clack;
    sf::Sprite petitBlock, grosBlock;
    sf::RenderWindow WINDOW(sf::VideoMode(800, 600), "Pi Collide");
    const char *NAME_MUSIC = "Collisions.wav";
    const char *NAME_IMAGE = "block.png";

    blockImg = openTexture(NAME_IMAGE);
    if(!clack.openFromFile(NAME_MUSIC)){std::cout << "error sound" << NAME_MUSIC << std::endl;}

    petitBlock.setTexture(blockImg);
    grosBlock.setTexture(blockImg);
    grosBlock.move(sf::Vector2f(100.f, 100.f));
    WINDOW.setFramerateLimit(60);

    while(WINDOW.isOpen())
    {
        sf::Event event;
        while(WINDOW.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                WINDOW.close();
            }
        }
        WINDOW.clear();
        WINDOW.draw(petitBlock);
        WINDOW.draw(grosBlock);
        WINDOW.display();
    }
}