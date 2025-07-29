#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    std::cout << "=== Test basique SFML ===" << std::endl;
    
    // Test de création de fenêtre
    std::cout << "Création de la fenêtre..." << std::endl;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test SFML");
    std::cout << "Fenêtre créée avec succès" << std::endl;
    
    // Test de création d'un rectangle
    sf::RectangleShape rect(sf::Vector2f(200, 100));
    rect.setPosition(300, 250);
    rect.setFillColor(sf::Color::Red);
    std::cout << "Rectangle créé" << std::endl;
    
    // Test de police par défaut
    sf::Font font;
    sf::Text text;
    text.setString("Test SFML");
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
    text.setPosition(10, 10);
    
    // Si on peut charger une police système
    if (font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        text.setFont(font);
        std::cout << "Police système chargée" << std::endl;
    } else {
        std::cout << "Aucune police disponible" << std::endl;
    }
    
    std::cout << "Début de la boucle d'affichage..." << std::endl;
    
    // Boucle d'affichage très simple
    int frameCount = 0;
    while (window.isOpen() && frameCount < 60) {  // Max 60 frames pour test
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        
        window.clear(sf::Color::Blue);
        window.draw(rect);
        window.draw(text);
        window.display();
        
        frameCount++;
        
        if (frameCount % 10 == 0) {
            std::cout << "Frame " << frameCount << " affichée" << std::endl;
        }
    }
    
    std::cout << "Test terminé. Total frames: " << frameCount << std::endl;
    return 0;
}
