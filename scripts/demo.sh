#!/bin/bash

# Démonstration rapide des capacités du programme
echo "🎯 DEMO: Pi Collide - Approximation de π par collisions"
echo "=================================================="
echo ""
echo "📚 THÉORIE:"
echo "Deux blocs avec masses en rapport 100^n donnent π × 10^n collisions"
echo ""
echo "🧮 EXEMPLES THÉORIQUES:"
echo "┌─────────────────┬──────────────────┬────────────────┐"
echo "│ Rapport masses  │ Collisions       │ Approximation  │"
echo "├─────────────────┼──────────────────┼────────────────┤"
echo "│ 1:1             │ 1                │ 1.000          │"
echo "│ 1:100           │ 31               │ 3.1            │"
echo "│ 1:10,000        │ 314              │ 3.14           │"
echo "│ 1:1,000,000     │ 3,141            │ 3.141          │"
echo "└─────────────────┴──────────────────┴────────────────┘"
echo ""
echo "⚡ VITESSES OPTIMISÉES:"
echo "Chaque expérience utilise une vitesse initiale calculée pour:"
echo "• Minimiser le temps de simulation"
echo "• Maximiser la précision du résultat"
echo "• Éviter les erreurs numériques"
echo ""
echo "✨ FONCTIONNALITÉS:"
echo "• Animation 2D fluide avec effets visuels"
echo "• Chronométrage précis des expériences"
echo "• Calcul automatique de l'erreur et de la précision"
echo "• Interface graphique intuitive avec émojis"
echo "• Effets sonores pour chaque collision"
echo ""
echo "🎮 CONTRÔLES:"
echo "• Touches 1-4: Changer les expériences"
echo "• ESPACE: Démarrer/Recommencer"
echo "• R: Reset rapide"
echo "• ESC: Quitter"
echo ""

# Vérifier la compilation
if [ ! -f "pi_collide" ]; then
    echo "🔧 Compilation nécessaire..."
    make
    if [ $? -ne 0 ]; then
        echo "❌ Erreur de compilation!"
        exit 1
    fi
    echo "✅ Compilation réussie!"
fi

echo "🚀 Pour lancer le programme:"
echo "   ./pi_collide"
echo ""
echo "📖 Pour plus d'informations:"
echo "   cat README.md"
echo ""
echo "🆘 En cas de problème d'affichage graphique:"
echo "   • Vérifiez \$DISPLAY: echo \$DISPLAY"
echo "   • Utilisez X11 forwarding: ssh -X"
echo "   • Sous Windows: installez VcXsrv ou Xming"
