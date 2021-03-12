# 1340-Group-Project

### Game—Airplane Attacks.

### How to Play and Rules

- Control the trajectory of your plane with AD keys to dodge attacks from enemy airplanes and avoid crashes on them
- shoot the enemy planes with the space key
- Direct crash on the enemy planes ends the game, whereas one attack would deduct half of your plane's health points

### Features

- **Generation of random game sets or events**

    The positions of enemy planes and health pills for increasing health points vary from each game. 

- **Data Structures for storing the game status**

    A 2D array list is randomly generated throughout the entire game. Occurrences of certain numbers at array[x][y] would represent new planes at Screen[x][y]. The same logic applies to health points.

- **Dynamic memory management**

- **Program codes in multiple files**
    - setup.h
    - health pills.h
    - attack.h
    - airplane agents.h
    - main.c
    - color.h
    - sound.h

- **File input/output**
    - load the game by compiling the c program and running the executable
    - AD and space keys serve will be read by the program, which makes according effects on the screen
    - when the game ends, your score and best score so far will be displayed
