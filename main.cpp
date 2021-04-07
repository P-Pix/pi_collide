#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

sf::Texture openTexture(const char *NAME_IMAGE)
{
    sf:: Texture TEXTURE;
    if(!TEXTURE.loadFromFile(NAME_IMAGE))
    {
        std::cout << "error image " << NAME_IMAGE << std::endl;
    }
    return TEXTURE;
}

sf::Font openFont(const char *NAME_FONT)
{
    sf::Font font;
    if(!font.loadFromFile(NAME_FONT))
    {
        std::cout << "error font " << NAME_FONT << std::endl;
    }
    return font;
}

bool collideBlock(sf::Vector2f gros, sf::Vector2f petit)
{
    petit.x = petit.x +80.f;
    return (gros.x -1.f < petit.x && petit.x < gros.x +1.f);
}

bool collideWall(sf::Vector2f petit)
{
    sf::Vector2f WALL(50.f, 0.f);
    return (petit.x - 1.f < WALL.x && WALL.x < petit.x +1.f);
}

int main()
{
    sf::Texture blockImg;
    sf::Music clack;
    sf::Sprite petitBlock, grosBlock;
    sf::Font FONT;
    sf::Text TEXTE;
    sf::RenderWindow WINDOW(sf::VideoMode(800, 600), "Pi Collide");

    const char *NAME_MUSIC = "sound/Collisions.wav";
    const char *NAME_IMAGE = "image/block.png";
    const char *NAME_FONT = "font/lemon_milk.otf";
    float vitesse = -1.f;
    int collision_nece = 100;
    int counter = 0, direction = 0, collision = 0;
    blockImg = openTexture(NAME_IMAGE);
    if(!clack.openFromFile(NAME_MUSIC)){std::cout << "error sound" << NAME_MUSIC << std::endl;}

    petitBlock.setTexture(blockImg);
    grosBlock.setTexture(blockImg);

    petitBlock.setScale(0.5, 0.5);

    petitBlock.move(sf::Vector2f(200.f, 275.f));
    grosBlock.move(sf::Vector2f(600.f, 200.f));

    WINDOW.setFramerateLimit(600);

    FONT = openFont(NAME_FONT);

    TEXTE.setFont(FONT);
    TEXTE.setCharacterSize(50);
    TEXTE.move(sf::Vector2f(50.f, 500.f));

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
        grosBlock.move(sf::Vector2f(vitesse, 0.f));
        if(collideBlock(grosBlock.getPosition(), petitBlock.getPosition()))
        {
            direction = 1;
            if(vitesse < 0)
            {
                vitesse /= 2;
            }
            else
            {
                vitesse *= 2;
            }
            collision += 1;
            counter ++;
            if(collision_nece / 2 == collision)
            {
                vitesse *= -collision_nece;
                collision += 1;
            }
        }
        if(collideWall(petitBlock.getPosition()))
        {
            direction = -1;
            counter ++;
        }
        if(direction == 1)
        {
            petitBlock.move(sf::Vector2f(-1.f, 0.f));
        }
        else if(direction == - 1)
        {
            petitBlock.move(sf::Vector2f(1.f, 0.f));
        }
        std::string text = std::to_string(counter);
        TEXTE.setString(text);
        WINDOW.clear();
        WINDOW.draw(petitBlock);
        WINDOW.draw(grosBlock);
        WINDOW.draw(TEXTE);
        WINDOW.display();
    }
}