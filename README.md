# Pi Collide - Démonstration Interactive

🔢 **Démonstration de π par collisions élastiques** - Une simulation interactive qui montre comment les collisions entre deux blocs peuvent approximer la valeur de π.

## 📁 Structure du Projet

```
pi_collide/
├── src/                    # Code source principal
│   └── main.cpp           # Programme principal
├── assets/                # Ressources du jeu
│   ├── font/              # Polices
│   ├── image/             # Textures et images
│   └── sound/             # Effets sonores
├── tests/                 # Tests et programmes de diagnostic
├── scripts/               # Scripts utilitaires
├── build/                 # Fichiers compilés (généré)
├── Makefile              # Système de build
└── README.md             # Ce fichier
```

## 🚀 Installation et Utilisation

### Prérequis
- **Compilateur C++17** (g++, clang++)
- **SFML 2.5+** (graphiques, audio, système)
- **Linux/WSL** recommandé

### Installation rapide
```bash
# Installer les dépendances
make install-deps

# Compiler le programme
make

# Lancer la simulation
make run
```

### Compilation manuelle
```bash
g++ -std=c++17 -Wall -Wextra -O2 -o build/pi_collide src/main.cpp -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
```

### Fonctionnalités

✨ **Animation 2D fluide** avec effets visuels
🎯 **Compteur de collisions** en temps réel
📊 **4 expériences** avec différents rapports de masse
🧮 **Calcul automatique** de l'approximation de π
📏 **Mesure de précision** (nombre de chiffres corrects)
⏱️ **Chronométrage** des expériences
🎵 **Effets sonores** pour chaque collision
🎨 **Interface graphique** intuitive

## Installation

### Prérequis
- SFML (Simple and Fast Multimedia Library)
- Un compilateur C++ supportant C++17
- Un environnement graphique (X11, Wayland, ou Windows)

### Installation automatique des dépendances (Ubuntu/Debian)
```bash
make install-deps
```

### Installation manuelle SFML
```bash
# Ubuntu/Debian
sudo apt update && sudo apt install libsfml-dev

# Fedora/RHEL
sudo dnf install SFML-devel

# Arch Linux
sudo pacman -S sfml

# macOS (avec Homebrew)
brew install sfml
```

### Compilation
```bash
make
```

### Exécution
```bash
# Avec le script d'aide
./run.sh

# Directement
./pi_collide

# Ou via make
make run
```

## Utilisation

### Contrôles
| Touche | Action |
|--------|--------|
| **1** | Masses égales (1:1) |
| **2** | Rapport 1:100 |
| **3** | Rapport 1:10,000 |
| **4** | Rapport 1:1,000,000 |
| **ESPACE** | Démarrer/Recommencer la simulation |
| **R** | Reset rapide |
| **ESC** | Quitter |

### Interface
L'écran affiche :
- 🎯 **Nombre total de collisions**
- 📊 **Masses des blocs** (petit bloc bleu, gros bloc rouge)
- 🧮 **Valeurs de π** (théorique vs calculée)
- 📏 **Erreur et précision** (chiffres corrects)
- ⏱️ **Temps écoulé**
- ✨ **Effets visuels** lors des collisions

### Expériences recommandées

1. **Débutant** : Commencer par l'expérience 2 (1:100) pour voir ~31 collisions
2. **Intermédiaire** : Tester l'expérience 3 (1:10,000) pour ~314 collisions
3. **Avancé** : Expérience 4 (1:1,000,000) pour ~3141 collisions (plus long)

## Explication physique

La démonstration repose sur :

### 1. Collisions élastiques parfaites
- **Conservation de l'énergie** : E₁ + E₂ = E₁' + E₂'
- **Conservation du momentum** : m₁v₁ + m₂v₂ = m₁v₁' + m₂v₂'
- **Formules de collision** :
  ```
  v₁' = ((m₁-m₂)v₁ + 2m₂v₂) / (m₁+m₂)
  v₂' = ((m₂-m₁)v₂ + 2m₁v₁) / (m₁+m₂)
  ```

### 2. Rapport de masses spécifique
Pour obtenir π × 10ⁿ collisions, utiliser un rapport de masse de 100ⁿ :
- n=1 : 100¹ = 100 → π × 10¹ ≈ 31 collisions
- n=2 : 100² = 10,000 → π × 10² ≈ 314 collisions  
- n=3 : 100³ = 1,000,000 → π × 10³ ≈ 3141 collisions

### 3. Géométrie de l'espace des phases
Le phénomène est lié aux propriétés géométriques du système dynamique dans l'espace des phases, où les trajectoires forment des courbes dont la longueur est liée à π.

## Structure du projet

```
pi_collide/
├── main.cpp           # Code source principal
├── config.h           # Configuration et paramètres
├── Makefile          # Fichier de compilation
├── run.sh            # Script de lancement avec aide
├── README.md         # Ce fichier
├── font/
│   └── lemon_milk.otf # Police d'affichage
├── image/
│   └── block.png     # Texture des blocs
└── sound/
    └── Collisions.wav # Son des collisions
```

## Performances et optimisations

### Vitesses optimisées
Chaque expérience utilise une vitesse initiale optimisée pour :
- Minimiser le temps de calcul
- Maximiser la précision du résultat
- Éviter les erreurs numériques

### Effets visuels
- Effets de collision temporaires
- Blocs colorés (bleu/rouge) pour meilleure visibilité
- Interface avec émojis et couleurs
- Chronométrage précis

## Dépannage

### Problèmes d'affichage
```bash
# Vérifier l'environnement graphique
echo $DISPLAY

# Tester avec X11 forwarding (SSH)
ssh -X utilisateur@serveur

# Windows : installer VcXsrv ou Xming
```

### Problèmes de son
Le programme fonctionne sans son si le fichier audio n'est pas trouvé.

### Compilation
```bash
# Vérifier SFML
pkg-config --libs sfml-all

# Debug
make clean && make
```

## Améliorations futures

- 🎮 Mode interactif pour ajuster manuellement les masses
- 📈 Graphique temps réel de la convergence vers π
- 💾 Sauvegarde des résultats d'expériences  
- 🔊 Options audio avancées
- 🌐 Version web avec WebAssembly
- 📱 Port mobile (Android/iOS)

## Références scientifiques

- **3Blue1Brown** : [Colliding Blocks](https://www.youtube.com/watch?v=HEfHFsfGXjs)
- **Article original** : "Playing Pool with π" par Gregory Galperin
- **Physique** : Mécanique classique, systèmes dynamiques
- **Mathématiques** : Géométrie, analyse numérique

## Licence

Ce projet est sous licence MIT. Voir le fichier LICENSE pour plus de détails.

---

*Créé avec ❤️ pour démontrer la beauté des mathématiques dans la physique !*
