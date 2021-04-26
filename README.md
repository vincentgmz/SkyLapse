# SkyLapse
An Air Combat Game

### Group Members Info
    Name        UID
    Guo Minzhe  3035812335
    Deng Jiaqi  3035832490

### How to Play and Rules

#### Keys

- <kbd>w</kbd><kbd>a</kbd><kbd>s</kbd><kbd>d</kbd> for moving your spaceship
- <kbd>space</kbd> for shooting bullet
- <kbd>r</kbd> for shooting laser (but only has three chances)

#### Rules

- Protect your base (on the left of your screen). It gets destroyed, then you lose.
- Avoid getting shot
- Eliminate the enemies with your bullets
- When you reach enough scores, you would see the boss. Defeating him would bring you victory.

### How to run the game

1. Clone the repo `git clone https://github.com/vincentgmz/SkyLapse`
2. Enter the folder `cd SkyLapse`
3. Change the `libInstall.sh` into executable mode `chmod 700 libInstall.sh`
4. Execute the `libInstall.sh` by `./libInstall.sh`
5. Wait for several minutes
6. Compile the code by `make`
7. Run the game through `./bin/main`
8. Enjoy the game :)

### Non-standard C/C++ libraries

#### Ncurses

    Ncurses is a linux GUI library. It is used for presenting the game panels. The player and enemies are shown through Ncurses features. Due to the trait of Ncurses, there's no need for duplicated printing for each update for the game status.

### Required Features

- **Generation of random game sets or events**

    Enemies are generated randomly and the chance of enemy shooting bullets is randomized. 

- **Data Structures for storing the game status**

    Struct is used in the game. For example, the Enemy struct contains the position and status of the enemy.
    A position struct is also used for storing the x and y coordinates of the enemy and player.
    Bullet is also an individual struct, which contains its status.
    Arrays are used for storing all the enemies and bullet entities.

- **Dynamic memory management**

    Enemies and bullets are generated through dynamic memory pointer, which make the allocation more convenient.
    
- **Program codes in multiple files**
    
    In our project, different files contains different part of our game. For instance, the `boss.cpp` and `boss.h` files contains the status and functions related to the boss of the game. `enemy.cpp` and `enemy.h` contains the variables of the enemies. Separating the game into different files makes the codes more easy to read.

- **File input/output**

    File input : The start, game-over and end pages of the game are loaded through file input. By reading each lines from the input file, the screen prints the pre-set page in the txt files.

    File output : Once you eliminate the boss and reach the end of the game, you would see a file called `summary.txt` in your folder, which contains your score and the time you took to get the victory.
