#!/bin/bash

echo "=== Lancement de Pi Collide avec forçage d'affichage ==="

# Définir l'affichage si nécessaire (pour WSL)
if [[ -n "$WSL_DISTRO_NAME" ]]; then
    echo "Détection WSL - Configuration de l'affichage..."
    export DISPLAY=:0
fi

# Vérifier si X11 fonctionne
if command -v xwininfo >/dev/null 2>&1; then
    echo "Test de l'affichage X11..."
    xwininfo -root -tree >/dev/null 2>&1
    if [ $? -eq 0 ]; then
        echo "✅ X11 fonctionne"
    else
        echo "❌ Problème avec X11"
    fi
fi

echo "Lancement du programme..."
echo "Instructions:"
echo "  - Utilisez Alt+Tab si la fenêtre n'apparaît pas"
echo "  - Appuyez sur ESPACE pour démarrer"
echo "  - Touches 1-4 pour changer d'expérience"
echo "  - Flèches Haut/Bas pour ajuster la masse"
echo "  - ESC pour quitter"
echo ""

./pi_collide

echo "Programme fermé."
