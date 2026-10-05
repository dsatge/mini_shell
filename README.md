# Minishell

![Capture d'écran Minishell](assets/minishell_screenshot.png)

This project has been created as part of the 42 curriculum by dsatge and enschnei

## Description 

Création d'un interpréteur de commandes inspiré de Bash. Ce projet nécessite la création d'un parseur de texte complexe, la gestion de l'historique, de l'environnement système, des signaux Unix, ainsi que l'exécution en parallèle de processus connectés par des pipes.

![C](https://img.shields.io/badge/Language-C-blue.svg)

Ce projet approfondit :
- L'architecture et le cycle de vie des processus UNIX (`fork`, `execve`, `waitpid`).
- La communication inter-processus par pipes (`pipe`, `dup2`).
- L'analyse lexicale (Lexer/Tokenizer) et syntaxique (Parser).
- La gestion des signaux POSIX (`SIGINT`, `SIGQUIT`).
- La gestion rigoureuse de la mémoire sans fuite (`valgrind`).

---

## Les commandes implémentées

### 1. Commandes internes (Builtins)
- `echo` (avec l'option `-n`)
- `cd` (avec chemins relatifs et absolus)
- `pwd`
- `export` (mise à jour et affichage de l'environnement)
- `unset` (suppression de variables)
- `env` (affichage de l'environnement)
- `exit` (avec gestion des codes de retour numériques)

### 2. Exécution et Redirections
- Recherche et exécution de binaires via la variable d'environnement `PATH` (ainsi que les chemins absolus/relatifs).
- Redirections d'entrée et de sortie : `<`, `>`, `>>`.
- Gestion des **Heredocs** (`<<`) avec délimiteur.
- Pipelines multiples (`|`) connectant la sortie d'une commande à l'entrée de la suivante.

### 3. Parsing & Expansion
- Gestion des guillemets simples (`'`) et doubles (`"`).
- Expansion des variables d'environnement (`$VAR`) et du code de retour précédent (`$?`).
- Historique des commandes avec la bibliothèque `readline`.

### 4. Signaux
- `Ctrl-C` : Interrompt la commande en cours ou affiche un nouveau prompt.
- `Ctrl-D` : Envoie un EOF et quitte le shell.
- `Ctrl-\` : Ignoré dans le prompt interactif, géré proprement lors de l'exécution des processus enfants.

---
## Compilation

Générez l'exécutable à l'aide du `Makefile` :
```bash
make
```

vous pouvez ensuite executer le fichier `minishell` et l'utiliser comme avec un shell classique. Vous pouvez également vous aider de la partie : `Les commandes implémentées` pour plus de facilitées.

## Architecture du projet

Le flux de traitement d'une commande suit une chaîne standard de compilation :

```text
[ Input Utilisateur (readline) ]
               │
               ▼
      [ Lexer / Tokenizer ]      --> Découpage en tokens (mots, pipes, redirections, quotes)
               │
               ▼
            [ Parser ]           --> Validation syntaxique & organisation en commandes
               │
               ▼
           [ Expander ]          --> Remplacement des variables ($VAR, $?) et gestion des quotes
               │
               ▼
           [ Executor ]          --> Redirections, forks, pipes, builtins et execve