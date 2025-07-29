#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    std::cout << "=== Pi Collide - Version Simplifiée ===" << std::endl;
    
    // Fenêtre
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Pi Collide - Test");
    window.setFramerateLimit(60);
    
    // Rectangles colorés simples
    sf::RectangleShape smallBlock(sf::Vector2f(60, 48));
    sf::RectangleShape largeBlock(sf::Vector2f(120, 96));
    sf::RectangleShape wall(sf::Vector2f(10, 400));
    sf::RectangleShape ground(sf::Vector2f(1200, 20));
    
    // Couleurs vives
    smallBlock.setFillColor(sf::Color::Blue);
    smallBlock.setOutlineColor(sf::Color::White);
    smallBlock.setOutlineThickness(2);
    smallBlock.setPosition(250, 400);
    
    largeBlock.setFillColor(sf::Color::Red);
    largeBlock.setOutlineColor(sf::Color::White);
    largeBlock.setOutlineThickness(2);
    largeBlock.setPosition(700, 350);
    
    wall.setFillColor(sf::Color::Green);
    wall.setPosition(80, 350);
    
    ground.setFillColor(sf::Color::Yellow);
    ground.setPosition(0, 700);
    
    // Police et texte
    sf::Font font;
    sf::Text text;
    text.setString("Pi Collide - Test Visuel");
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
    text.setPosition(50, 50);
    
    // Essayer de charger une police
    if (font.loadFromFile("font/lemon_milk.otf")) {
        text.setFont(font);
        std::cout << "Police personnalisée chargée" << std::endl;
    } else {
        std::cout << "Police par défaut utilisée" << std::endl;
    }
    
    std::cout << "Lancement de l'affichage..." << std::endl;
    
    int frameCount = 0;
    while (window.isOpen() && frameCount < 300) {  // 5 secondes à 60 FPS
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
        }
        
        // Mouvement simple du gros bloc
        if (frameCount % 2 == 0) {
            largeBlock.move(-1, 0);
        }
        
        // Affichage
        window.clear(sf::Color(30, 30, 60));  // Bleu foncé
        
        window.draw(ground);
        window.draw(wall);
        window.draw(smallBlock);
        window.draw(largeBlock);
        window.draw(text);
        
        window.display();
        
        frameCount++;
        
        if (frameCount % 60 == 0) {
            std::cout << "Seconde " << (frameCount/60) << " - Position gros bloc: " << largeBlock.getPosition().x << std::endl;
        }
    }
    
    std::cout << "Test terminé après " << frameCount << " frames" << std::endl;
    return 0;
}
