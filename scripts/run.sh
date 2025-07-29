#!/bin/bash

# Script de lancement pour Pi Collide

echo "==================================="
echo "     Pi Collide - Démonstration"
echo "==================================="
echo ""
echo "Ce programme démontre comment les collisions entre"
echo "deux blocs peuvent approximer la valeur de π !"
echo ""
echo "Phénomène mathématique :"
echo "- Rapport de masses 1:100    → ~31 collisions  (π × 10)"
echo "- Rapport de masses 1:10000  → ~314 collisions (π × 100)"
echo "- Rapport de masses 1:1M     → ~3141 collisions(π × 1000)"
echo ""
echo "Contrôles :"
echo "- Touches 1-4 : Changer les rapports de masse"
echo "- ESPACE      : Démarrer/Recommencer la simulation"
echo "- ESC         : Quitter"
echo ""
echo "Lancement du programme..."

# Vérifier si on est dans un environnement graphique
if [ -z "$DISPLAY" ]; then
    echo "ATTENTION: Aucun environnement graphique détecté (pas de \$DISPLAY)"
    echo "Pour exécuter ce programme, vous avez besoin d'un serveur X."
    echo ""
    echo "Solutions possibles :"
    echo "1. Utiliser un environnement de bureau Linux"
    echo "2. Utiliser X11 forwarding avec SSH : ssh -X"
    echo "3. Utiliser un serveur X sous Windows (VcXsrv, Xming...)"
    echo ""
    read -p "Voulez-vous continuer quand même ? (y/n) " -n 1 -r
    echo
    if [[ ! $RE1 =~ ^[Yy]$ ]]; then
        exit 1
    fi
fi

# Compiler si nécessaire
if [ ! -f "pi_collide" ] || [ "main.cpp" -nt "pi_collide" ]; then
    echo "Compilation nécessaire..."
    make
    if [ $? -ne 0 ]; then
        echo "Erreur de compilation !"
        exit 1
    fi
fi

# Lancer le programme
./pi_collide
