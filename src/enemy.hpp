struct Enemy{
    int y;
    int x;
    char shape;
    int speed;
}; 

void printEnemy(WINDOW* win);
void eraseEnemy(WINDOW* win);

void updateEnemyPos();
void generateEnemy();








