#include <iostream>
#include <SFML/Graphics.hpp>

int main() {
    std::cout << "Test simple de fenêtre SFML..." << std::endl;
    
    // Créer une petite fenêtre de test
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test SFML - Fenetre Visible", 
                           sf::Style::Titlebar | sf::Style::Close);
    
    // Forcer la position au centre de l'écran
    window.setPosition(sf::Vector2i(200, 150));
    window.setFramerateLimit(30);
    
    std::cout << "Fenêtre créée à la position (200, 150)" << std::endl;
    std::cout << "Si vous ne voyez pas la fenêtre, utilisez Alt+Tab" << std::endl;
    
    // Créer un grand rectangle coloré pour rendre la fenêtre très visible
    sf::RectangleShape background(sf::Vector2f(800, 600));
    background.setFillColor(sf::Color::Red);
    
    sf::Text message;
    sf::Font defaultFont; // Utiliser la police par défaut
    
    message.setString("FENETRE VISIBLE!\nAppuyez sur ESC pour fermer");
    message.setCharacterSize(48);
    message.setFillColor(sf::Color::White);
    message.setPosition(50, 200);
    
    int frameCount = 0;
    
    while (window.isOpen()) {
        frameCount++;
        
        if (frameCount % 30 == 0) {
            std::cout << "Frame " << frameCount << " - Fenêtre active" << std::endl;
        }
        
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                std::cout << "Fermeture de la fenêtre de test" << std::endl;
                window.close();
            }
        }
        
        window.clear();
        window.draw(background);
        window.draw(message);
        window.display();
    }
    
    return 0;
}
