#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <vector>
#include <chrono>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

struct Block {
    sf::Sprite sprite;
    sf::RectangleShape shape;  // Forme colorée pour meilleure visibilité
    float mass;
    float velocity;
    float x;
    float width;
    sf::Color color;
    bool useTexture;
    
    Block(float m = 1.0f, float w = 80.0f, sf::Color c = sf::Color::White, bool texture = true) 
        : mass(m), velocity(0.0f), x(0.0f), width(w), color(c), useTexture(texture) {
        
        // Configuration de la forme rectangulaire
        shape.setSize(sf::Vector2f(w, w * 0.8f));
        shape.setFillColor(c);
        shape.setOutlineThickness(2.0f);
        shape.setOutlineColor(sf::Color::White);
    }
    
    void updatePosition() {
        x += velocity;
        sprite.setPosition(x, sprite.getPosition().y);
        shape.setPosition(x, shape.getPosition().y);
    }
    
    void setPosition(float posX, float posY) {
        x = posX;
        sprite.setPosition(x, posY);
        shape.setPosition(x, posY);
    }
    
    bool collidesWith(const Block& other) const {
        return (x + width > other.x && x < other.x + other.width);
    }
    
    bool collidesWithWall(float wallX) const {
        return x <= wallX;
    }
    
    void draw(sf::RenderWindow& window) {
        if (useTexture && sprite.getTexture() != nullptr) {
            window.draw(sprite);
        } else {
            // Toujours dessiner la forme géométrique si pas de texture
            window.draw(shape);
        }
    }
};

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

// Collision élastique parfaite entre deux objets
void elasticCollision(Block& block1, Block& block2) {
    float v1 = block1.velocity;
    float v2 = block2.velocity;
    float m1 = block1.mass;
    float m2 = block2.mass;
    
    // Nouvelles vitesses après collision élastique
    block1.velocity = ((m1 - m2) * v1 + 2 * m2 * v2) / (m1 + m2);
    block2.velocity = ((m2 - m1) * v2 + 2 * m1 * v1) / (m1 + m2);
}

std::string formatFloat(float value, int precision = 6) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(precision) << value;
    return ss.str();
}

// Fonction pour calculer la vitesse optimale selon la masse
float calculateOptimalSpeed(float massRatio) {
    // Vitesse inversement proportionnelle à la racine de la masse pour éviter les overlaps
    if (massRatio <= 100.0f) {
        return 1.8f;
    } else if (massRatio <= 1000.0f) {
        return 1.2f;
    } else if (massRatio <= 10000.0f) {
        return 0.8f;
    } else if (massRatio <= 100000.0f) {
        return 0.5f;
    } else if (massRatio <= 1000000.0f) {
        return 0.3f;
    } else {
        return 0.1f; // Très lent pour masses énormes
    }
}

// Fonction pour jouer le son de collision
void playCollisionSound(sf::Music& sound) {
    if (sound.getStatus() == sf::Music::Playing) {
        sound.stop();
    }
    sound.play();
}
struct CollisionEffect {
    sf::CircleShape circle;
    float lifetime;
    float maxLifetime;
    sf::Vector2f position;
    
    CollisionEffect(sf::Vector2f pos) : lifetime(0.5f), maxLifetime(0.5f), position(pos) {
        circle.setRadius(10.0f);
        circle.setPosition(pos.x - 10, pos.y - 10);
        circle.setFillColor(sf::Color(255, 255, 0, 200));
        circle.setOutlineThickness(2.0f);
        circle.setOutlineColor(sf::Color::Red);
    }
    
    void update(float deltaTime) {
        lifetime -= deltaTime;
        float alpha = (lifetime / maxLifetime) * 255;
        if (alpha < 0) alpha = 0;
        
        circle.setFillColor(sf::Color(255, 255, 0, (sf::Uint8)alpha));
        circle.setOutlineColor(sf::Color(255, 0, 0, (sf::Uint8)alpha));
        
        // Expansion de l'effet
        float scale = 1.0f + (1.0f - lifetime / maxLifetime) * 2.0f;
        circle.setScale(scale, scale);
    }
    
    bool isExpired() const {
        return lifetime <= 0.0f;
    }
    
    void draw(sf::RenderWindow& window) {
        if (!isExpired()) {
            window.draw(circle);
        }
    }
};

int main()
{
    std::cout << "Initialisation de la fenêtre..." << std::endl;
    
    // Créer la fenêtre avec des paramètres pour forcer la visibilité
    sf::RenderWindow WINDOW(sf::VideoMode(1200, 800), "Pi par Collisions - Demo Interactive", 
                           sf::Style::Titlebar | sf::Style::Close);
    
    // Forcer la position de la fenêtre
    WINDOW.setPosition(sf::Vector2i(100, 100));
    
    // Paramètres pour optimiser l'affichage
    WINDOW.setFramerateLimit(60);
    WINDOW.setVerticalSyncEnabled(false);
    
    // Rendre la fenêtre active et visible
    WINDOW.requestFocus();
    
    std::cout << "Fenêtre créée avec succès à la position (100, 100)" << std::endl;
    std::cout << "Taille de la fenêtre: 1200x800" << std::endl;
    
    sf::Texture blockImg;
    bool textureLoaded = false;
    if (blockImg.loadFromFile("assets/image/block.png")) {
        textureLoaded = true;
    }
    
    sf::Font FONT;
    bool fontLoaded = false;
    if (FONT.loadFromFile("assets/font/lemon_milk.otf")) {
        fontLoaded = true;
        std::cout << "Police personnalisée chargée" << std::endl;
    } else {
        std::cout << "Police personnalisée non trouvée, utilisation de la police par défaut" << std::endl;
        // Essayer de charger une police système
        if (!FONT.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
            std::cout << "Aucune police disponible - texte peut ne pas s'afficher" << std::endl;
        }
    }
    sf::Music clack;
    if(!clack.openFromFile("assets/sound/Collisions.wav")) {
        std::cout << "Attention: fichier son non trouvé" << std::endl;
    } else {
        std::cout << "Son chargé avec succès" << std::endl;
    }
    clack.setVolume(20);
    
    // Configuration des expériences avec vitesses optimisées
    struct Experiment {
        float massRatio;
        std::string name;
        float expectedPi;
        float initialSpeed;
        int expectedDigits;
    };
    
    std::vector<Experiment> experiments = {
        {1.0f, "Masses égales (1:1)", M_PI, 2.0f, 0},
        {100.0f, "Rapport 1:100", M_PI * 10.0f, 1.8f, 1}, // π × 10
        {10000.0f, "Rapport 1:10000", M_PI * 100.0f, 1.2f, 2}, // π × 100
        {1000000.0f, "Rapport 1:1000000", M_PI * 1000.0f, 0.9f, 3} // π × 1000
    };
    
    // Recalculer les vitesses optimales et π théorique pour chaque expérience
    for (auto& exp : experiments) {
        exp.initialSpeed = calculateOptimalSpeed(exp.massRatio);
        float logMass = std::log10(exp.massRatio);
        exp.expectedPi = M_PI * std::pow(10, logMass / 2.0f);
    }
    
    int currentExperiment = 1;
    int collisionCount = 0;
    bool simulationRunning = false;
    bool simulationComplete = false;
    
    // Chronométrage
    auto startTime = std::chrono::steady_clock::now();
    auto lastTime = startTime;
    
    // Effets visuels
    std::vector<CollisionEffect> effects;
    
    // Initialisation des blocs avec couleurs - permettre texture si disponible
    Block smallBlock(1.0f, 60.0f, sf::Color(100, 150, 255), textureLoaded);  // Bleu
    Block largeBlock(experiments[currentExperiment].massRatio, 120.0f, sf::Color(255, 100, 100), textureLoaded); // Rouge
    
    // Position initiale
    float wallX = 80.0f;
    smallBlock.setPosition(250.0f, 400.0f);
    largeBlock.setPosition(700.0f, 350.0f);
    largeBlock.velocity = -experiments[currentExperiment].initialSpeed;
    
    std::cout << "Positions initiales:" << std::endl;
    std::cout << "  Petit bloc: (" << smallBlock.x << ", 400)" << std::endl;
    std::cout << "  Gros bloc: (" << largeBlock.x << ", 350)" << std::endl;
    std::cout << "  Mur: " << wallX << std::endl;
    
    // Configuration des sprites si texture disponible (mais on utilise les formes maintenant)
    if (textureLoaded) {
        smallBlock.sprite.setTexture(blockImg);
        largeBlock.sprite.setTexture(blockImg);
        smallBlock.sprite.setScale(0.6f, 0.6f);
        largeBlock.sprite.setScale(1.2f, 1.2f);
        smallBlock.sprite.setColor(sf::Color(150, 200, 255));
        largeBlock.sprite.setColor(sf::Color(255, 150, 150));
        std::cout << "Texture chargée avec succès" << std::endl;
    } else {
        std::cout << "Utilisation des formes rectangulaires colorées" << std::endl;
    }
    
    // Ligne du mur avec effet 3D
    sf::RectangleShape wall(sf::Vector2f(8, 350));
    wall.setPosition(wallX, 350);
    wall.setFillColor(sf::Color(200, 50, 50));
    
    sf::RectangleShape wallShadow(sf::Vector2f(5, 350));
    wallShadow.setPosition(wallX + 8, 353);
    wallShadow.setFillColor(sf::Color(100, 25, 25));
    
    // Ligne de sol
    sf::RectangleShape ground(sf::Vector2f(1200, 10));
    ground.setPosition(0, 700);
    ground.setFillColor(sf::Color(60, 60, 60));
    
    // Textes d'interface avec positions améliorées
    sf::Text titleText, collisionText, massText, piText, instructionText, statusText, timeText;
    
    titleText.setFont(FONT);
    titleText.setCharacterSize(32);
    titleText.setFillColor(sf::Color::White);
    titleText.setString("Demonstration: Pi par Collisions Elastiques");
    titleText.setPosition(50, 30);
    
    collisionText.setFont(FONT);
    collisionText.setCharacterSize(36);
    collisionText.setFillColor(sf::Color::Yellow);
    collisionText.setPosition(50, 80);
    
    massText.setFont(FONT);
    massText.setCharacterSize(22);
    massText.setFillColor(sf::Color::Cyan);
    massText.setPosition(50, 140);
    
    // piText.setFont(FONT);
    // piText.setCharacterSize(24);
    // piText.setFillColor(sf::Color::Green);
    // piText.setPosition(50, 200);
    
    timeText.setFont(FONT);
    timeText.setCharacterSize(20);
    timeText.setFillColor(sf::Color::Magenta);
    timeText.setPosition(50, 280);
    
    instructionText.setFont(FONT);
    instructionText.setCharacterSize(16);
    instructionText.setFillColor(sf::Color(200, 200, 200));
    instructionText.setString(">>> Controles: 1-4=Experiences | ESPACE=Start/Reset | R=Reset | UP/DOWN=Masse x10/÷10 | ESC=Quitter <<<");
    instructionText.setPosition(50, 750);
    
    statusText.setFont(FONT);
    statusText.setCharacterSize(20);
    statusText.setFillColor(sf::Color::White);
    statusText.setPosition(600, 80);
    
    auto resetSimulation = [&]() {
        collisionCount = 0;
        simulationRunning = false;
        simulationComplete = false;
        effects.clear();
        
        smallBlock.velocity = 0.0f;
        largeBlock.velocity = -experiments[currentExperiment].initialSpeed;
        largeBlock.mass = experiments[currentExperiment].massRatio;
        
        smallBlock.setPosition(250.0f, 400.0f);
        largeBlock.setPosition(700.0f, 350.0f);
        
        startTime = std::chrono::steady_clock::now();
    };
    
    std::cout << "Début de la boucle principale..." << std::endl;
    std::cout << "Si la fenêtre n'apparaît pas, vérifiez votre gestionnaire de fenêtres ou essayez Alt+Tab" << std::endl;
    
    // Variables pour détecter si la fenêtre est active
    bool windowVisible = true;
    int frameCount = 0;
    
    while(WINDOW.isOpen())
    {
        frameCount++;
        
        // Afficher un message tous les 60 frames (1 seconde) pour confirmer que ça tourne
        if (frameCount % 60 == 0) {
            std::cout << "Fenêtre active - Frame " << frameCount << " - Utilisez Alt+Tab si la fenêtre n'est pas visible" << std::endl;
        }
        
        auto currentTime = std::chrono::steady_clock::now();
        float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
        lastTime = currentTime;
        
        sf::Event event;
        while(WINDOW.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                WINDOW.close();
                
            if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Escape) {
                    std::cout << "Touche Échap pressée - Fermeture du programme" << std::endl;
                    WINDOW.close();
                }
                else if(event.key.code >= sf::Keyboard::Num1 && event.key.code <= sf::Keyboard::Num4) {
                    currentExperiment = event.key.code - sf::Keyboard::Num1;
                    std::cout << "Expérience " << (currentExperiment + 1) << " sélectionnée" << std::endl;
                    resetSimulation();
                }
                else if(event.key.code == sf::Keyboard::Space) {
                    std::cout << "Espace pressé - Démarrage/Reset de la simulation" << std::endl;
                    if(!simulationRunning && !simulationComplete) {
                        simulationRunning = true;
                        startTime = std::chrono::steady_clock::now();
                    } else {
                        resetSimulation();
                    }
                }
                else if(event.key.code == sf::Keyboard::R) {
                    std::cout << "R pressé - Reset de la simulation" << std::endl;
                    resetSimulation();
                }
                else if(event.key.code == sf::Keyboard::Up) {
                    // Augmenter la masse du gros bloc par 10
                    experiments[currentExperiment].massRatio *= 10.0f;
                    if (experiments[currentExperiment].massRatio > 100000000.0f) {
                        experiments[currentExperiment].massRatio = 100000000.0f; // Limite max
                    }
                    // Recalculer la vitesse optimale
                    experiments[currentExperiment].initialSpeed = calculateOptimalSpeed(experiments[currentExperiment].massRatio);
                    // Calcul plus précis de π théorique basé sur la formule mathématique
                    float logMass = std::log10(experiments[currentExperiment].massRatio);
                    experiments[currentExperiment].expectedPi = M_PI * std::pow(10, logMass / 2.0f);
                    resetSimulation();
                    std::cout << "Masse augmentée: " << experiments[currentExperiment].massRatio 
                              << " | Vitesse ajustée: " << experiments[currentExperiment].initialSpeed << std::endl;
                }
                else if(event.key.code == sf::Keyboard::Down) {
                    // Diminuer la masse du gros bloc par 10
                    experiments[currentExperiment].massRatio /= 10.0f;
                    if (experiments[currentExperiment].massRatio < 1.0f) {
                        experiments[currentExperiment].massRatio = 1.0f; // Limite min
                    }
                    // Recalculer la vitesse optimale
                    experiments[currentExperiment].initialSpeed = calculateOptimalSpeed(experiments[currentExperiment].massRatio);
                    // Calcul plus précis de π théorique basé sur la formule mathématique
                    float logMass = std::log10(experiments[currentExperiment].massRatio);
                    experiments[currentExperiment].expectedPi = M_PI * std::pow(10, logMass / 2.0f);
                    resetSimulation();
                    std::cout << "Masse diminuée: " << experiments[currentExperiment].massRatio 
                              << " | Vitesse ajustée: " << experiments[currentExperiment].initialSpeed << std::endl;
                }
            }
        }
        
        // Simulation physique
        if(simulationRunning && !simulationComplete) {
            // Mise à jour des positions
            smallBlock.updatePosition();
            largeBlock.updatePosition();
            
            // Vérification collision entre blocs
            if(smallBlock.collidesWith(largeBlock)) {
                // Position de l'effet
                sf::Vector2f effectPos(
                    (smallBlock.x + largeBlock.x) / 2.0f + 30,
                    (smallBlock.shape.getPosition().y + largeBlock.shape.getPosition().y) / 2.0f + 30
                );
                effects.push_back(CollisionEffect(effectPos));
                
                elasticCollision(smallBlock, largeBlock);
                collisionCount++;
                
                // Son à chaque collision
                playCollisionSound(clack);
                
                // Séparer les blocs pour éviter les collisions multiples
                // Ajustement plus agressif pour les masses importantes
                float separationDistance = 5.0f;
                if (largeBlock.mass > 10000.0f) {
                    separationDistance = 10.0f;
                } else if (largeBlock.mass > 1000000.0f) {
                    separationDistance = 15.0f;
                }
                
                if(smallBlock.x + smallBlock.width > largeBlock.x) {
                    smallBlock.x = largeBlock.x - smallBlock.width - separationDistance;
                }
                if(largeBlock.x + largeBlock.width > smallBlock.x && largeBlock.x < smallBlock.x) {
                    largeBlock.x = smallBlock.x + smallBlock.width + separationDistance;
                }
            }
            
            // Vérification collision avec le mur
            if(smallBlock.collidesWithWall(wallX)) {
                sf::Vector2f effectPos(wallX + 20, smallBlock.shape.getPosition().y + 30);
                effects.push_back(CollisionEffect(effectPos));
                
                smallBlock.velocity = -smallBlock.velocity;
                smallBlock.x = wallX + 2;
                collisionCount++;
                
                // Son à chaque collision avec le mur
                playCollisionSound(clack);
            }
            
            // Arrêt de la simulation si les blocs s'éloignent
            if(largeBlock.x > 1100 && largeBlock.velocity > 0) {
                simulationComplete = true;
                simulationRunning = false;
            }
        }
        
        // Mise à jour des effets visuels
        for(auto it = effects.begin(); it != effects.end();) {
            it->update(deltaTime);
            if(it->isExpired()) {
                it = effects.erase(it);
            } else {
                ++it;
            }
        }
        
        // Mise à jour de l'affichage
        collisionText.setString(">>> Collisions: " + std::to_string(collisionCount));
        
        massText.setString("*** " + experiments[currentExperiment].name + 
                          "\n    Petit bloc: 1 kg | Gros bloc: " + 
                          formatFloat(experiments[currentExperiment].massRatio, 0) + " kg" +
                          "\n    Rapport actuel: 1:" + formatFloat(experiments[currentExperiment].massRatio, 0) +
                          "\n    Vitesse initiale: " + formatFloat(experiments[currentExperiment].initialSpeed, 2));
        
        float piApproximation = 0;
        std::string piString = "pi theorique: " + formatFloat(experiments[currentExperiment].expectedPi, 3);
        
        if(currentExperiment > 0 && collisionCount > 0) {
            piApproximation = collisionCount / std::pow(10, currentExperiment);
            piString += "\n>> Pi calcule: " + formatFloat(piApproximation, 6);
            
            float error = std::abs(M_PI - piApproximation);
            piString += "\n>> Erreur: " + formatFloat(error, 6);
            
            int correctDigits = -std::log10(error / M_PI);
            if(correctDigits > 0) {
                piString += " (" + std::to_string(correctDigits) + " chiffres corrects)";
            }
        }
        piText.setString(piString);
        
        // Temps écoulé
        auto elapsed = std::chrono::duration<float>(currentTime - startTime).count();
        timeText.setString("=== Temps: " + formatFloat(elapsed, 1) + "s ===");
        
        if(!simulationRunning && !simulationComplete) {
            statusText.setString(">>> Appuyez sur ESPACE pour commencer <<<");
            statusText.setFillColor(sf::Color::Green);
        } else if(simulationRunning) {
            statusText.setString("*** Simulation en cours... ***");
            statusText.setFillColor(sf::Color::Yellow);
        } else {
            statusText.setString("!!! Simulation terminee !!!\n    ESPACE pour recommencer");
            statusText.setFillColor(sf::Color::Cyan);
        }
        
        // Affichage
        WINDOW.clear(sf::Color(20, 20, 40)); // Bleu foncé
        
        // Test: rectangle blanc pour vérifier l'affichage
        sf::RectangleShape testRect(sf::Vector2f(100, 50));
        testRect.setPosition(10, 10);
        testRect.setFillColor(sf::Color::White);
        WINDOW.draw(testRect);
        
        // Décor
        WINDOW.draw(ground);
        WINDOW.draw(wallShadow);
        WINDOW.draw(wall);
        
        // Blocs
        smallBlock.draw(WINDOW);
        largeBlock.draw(WINDOW);
        
        // Effets
        for(auto& effect : effects) {
            effect.draw(WINDOW);
        }
        
        // Interface
        WINDOW.draw(titleText);
        WINDOW.draw(collisionText);
        WINDOW.draw(massText);
        WINDOW.draw(piText);
        WINDOW.draw(timeText);
        WINDOW.draw(instructionText);
        WINDOW.draw(statusText);
        
        WINDOW.display();
    }
    
    return 0;
}