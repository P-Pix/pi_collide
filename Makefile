# Makefile pour Pi Collide - Projet organisé
# Démonstration de π par collisions élastiques avec SFML

# Variables
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Répertoires
SRC_DIR = src
BUILD_DIR = build
TESTS_DIR = tests
ASSETS_DIR = assets
SCRIPTS_DIR = scripts

# Fichiers
MAIN_SRC = $(SRC_DIR)/main.cpp
MAIN_TARGET = $(BUILD_DIR)/pi_collide

# Cible principale
all: $(MAIN_TARGET)

# Compilation du programme principal
$(MAIN_TARGET): $(MAIN_SRC) | $(BUILD_DIR)
	@echo "🔨 Compilation du programme principal..."
	$(CXX) $(CXXFLAGS) -o $@ $< $(LIBS)
	@echo "✅ Programme compilé avec succès : $@"

# Créer le répertoire build s'il n'existe pas
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Exécution du programme
run: $(MAIN_TARGET)
	@echo "🚀 Lancement de Pi Collide..."
	@echo "📁 Répertoire de travail : $(PWD)"
	cd $(PWD) && $(MAIN_TARGET)

# Tests de compilation
test-compile: | $(BUILD_DIR)
	@echo "🧪 Test de compilation des fichiers de test..."
	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/test_window $(TESTS_DIR)/test_window.cpp $(LIBS)
	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/test_sfml $(TESTS_DIR)/test_sfml.cpp $(LIBS)
	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/simple_test $(TESTS_DIR)/simple_test.cpp $(LIBS)
	@echo "✅ Tous les tests compilés"

# Exécution des tests
test-window: test-compile
	@echo "🪟 Test de la fenêtre..."
	cd $(PWD) && $(BUILD_DIR)/test_window

test-sfml: test-compile
	@echo "🎮 Test SFML..."
	cd $(PWD) && $(BUILD_DIR)/test_sfml

# Scripts utilitaires
demo: $(MAIN_TARGET)
	@echo "🎯 Lancement de la démo..."
	cd $(PWD) && $(SCRIPTS_DIR)/demo.sh

run-windowed: $(MAIN_TARGET)
	@echo "🪟 Lancement avec détection de fenêtre..."
	cd $(PWD) && $(SCRIPTS_DIR)/run_windowed.sh

# Nettoyage
clean:
	@echo "🧹 Nettoyage des fichiers compilés..."
	rm -rf $(BUILD_DIR)/*
	@echo "✅ Nettoyage terminé"

# Installation des dépendances (Ubuntu/Debian)
install-deps:
	@echo "📦 Installation des dépendances SFML..."
	sudo apt update
	sudo apt install -y libsfml-dev
	@echo "✅ Dépendances installées"

# Validation du projet
validate:
	@echo "🔍 Validation de la structure du projet..."
	@echo "📂 Structure :"
	@ls -la
	@echo ""
	@echo "📁 Sources :"
	@ls -la $(SRC_DIR)/
	@echo ""
	@echo "🎨 Assets :"
	@ls -la $(ASSETS_DIR)/
	@echo ""
	@echo "🧪 Tests :"
	@ls -la $(TESTS_DIR)/
	@echo ""
	@echo "📜 Scripts :"
	@ls -la $(SCRIPTS_DIR)/

# Aide
help:
	@echo "🔧 Pi Collide - Commandes disponibles :"
	@echo ""
	@echo "  make           - Compiler le programme principal"
	@echo "  make run       - Compiler et exécuter le programme"
	@echo "  make demo      - Lancer la démo avec instructions"
	@echo "  make run-windowed - Lancer avec détection de fenêtre"
	@echo "  make test-compile - Compiler tous les tests"
	@echo "  make test-window  - Tester l'affichage de fenêtre"
	@echo "  make test-sfml    - Tester SFML"
	@echo "  make clean     - Nettoyer les fichiers compilés"
	@echo "  make install-deps - Installer les dépendances SFML"
	@echo "  make validate  - Vérifier la structure du projet"
	@echo "  make help      - Afficher cette aide"
	@echo ""
	@echo "🎮 Contrôles du jeu :"
	@echo "  ESPACE     - Démarrer/Redémarrer la simulation"
	@echo "  1-4        - Changer d'expérience"
	@echo "  ↑/↓        - Ajuster la masse (×10/÷10)"
	@echo "  R          - Reset"
	@echo "  ESC        - Quitter"

.PHONY: all run demo run-windowed test-compile test-window test-sfml clean install-deps validate help
