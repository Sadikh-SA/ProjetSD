
# Jeu de la Vie
Ce projet est un devoir de Master 1 Informatique à l'UFR Sciences Techniques de l'université de Bourgogne. Il traite sur le Jeu de la Vie, qui est un automate cellulaire, et est écrit en C.

# Installation
Pour installer le Jeu de la Vie sur votre ordinateur, veuillez suivre les instructions ci-dessous.

## Fichiers
Il faut tout d'abord télécharger la dernière version de ce projet, vous pouvez soit télécharger un fichier zip sur le github ou procéder par un clone.
~~~{.sh}
git clone <lien>
~~~
La structure du projet se présente comme cela :

- bin/ => Dossier contenant l'exécutable
- grilles/ => Dossier contenant les fichiers grilles
- include/ => Dossier contenant les fichiers d'entête
- lib/ => Dossier contenant la librairie
- obj/ => Dossier contenant les fichiers binaires qui vont être supprimé après
- src/ => Dossier contenant les fichiers sources
- Makefile => Fichier config Make

## Compilation
### Prérequis

- Le compilateur C (gcc)
- Le programme Make

### Générer l'exécutable

Pour compiler le programme et générer l'exécutable il suffit d'exécuter la commande:
~~~{.sh}
make # Affichage textuel dans la console
~~~
L’exécutable est générée dans le dossier bin/.

### Nettoyer le projet

Pour nettoyer le dossier racine, et supprimer tout fichier généré par une compilation, il suffit d'exécuter la commande:
~~~{.sh}
make clean
~~~

# Utilisation
## Version texte
### Démarrage
Après avoir compilé le programme, l'exécutable à été générée dans le dossier bin/. 
Le programme a pour arguments, le nom du fichier de la grille, il suffit donc d'exécuter la commande:
~~~{.sh}
./bin/main grilles/nom_fichier_grille.txt
~~~

### Commandes
Lorsque l'application est démarrée il est possible d’exécuter des commandes.

- c => Activer/désactiver le comptage cyclique
- v => Activer/désactiver le vieillissement
- o => Vérifie si la colonie est oscillante et affiche le temps si c'est le cas
- n => Changer de grille
- q => Quitter le programme

### Evolution

Pour faire évoluer les cellules, il suffit d'appuyer sur la touche entrée.