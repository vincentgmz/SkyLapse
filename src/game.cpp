# include <ncurses.h>
# include <iostream>
# include <string>
# include <unistd.h>
# include "game.h"
# include <ctime>
# include "enemy.h"
# include <cstdlib>
# include <list>
# include <fstream>
# include "boss.h"
//# include "infoScr.h"
using namespace std;

/*

    PLAYER LOOKS LIKE
    \
    -)
    /

*/

/* paramters from line 26- 28 and 33 can be adjusted according to game's difficulty level
*/
int base_health = 10; // base health -1 if an enemy airplane is not destroyed but pass to the left
int ENEMY_GEN_RATE = 27; // rate of generating enemies
int boss_health = 50; 
AREA MAIN_AREA = {0,15,0,79};
AREA INFO_AREA = {16,24,0,80};
Bullet BulletList[MAX_NUM_BULLET];
bool isBoss = false;
int numOfUltimate = 3; // number of laser beams player can shoot in the entire game. 

/*prints all kinds of important game data in form of ascii char
input: window, player's health, number of available laser beams, boss's health, and base's health
 */
void printInfo(WINDOW* win, int health, int numUltimate, int bossHealth, int base_health){
    
    //cleans up everything before printing out those values
    for (int i = 34; i < 59; i++)
    {
        mvwaddch(win,2,i,' ');
    }
    for (int i = 34; i < 59 ; i++)
    {
        mvwaddch(win,3,i,' ');
    }
    for (int i = 34; i < 59 ; i++)
    {
        mvwaddch(win,4,i,' ');
    }
    for (int i = 34; i < 59; i++)
    {
        mvwaddch(win,5,i,' ');
    }
    
    
    //print the current values 
    mvwprintw(win,2,30,"HP: ");
    for (int i = 34; i < 34+health; i++)
    {
        mvwaddch(win,2,i,'/');
    }
    mvwprintw(win,3,30,"Ult: ");
    for (int i = 35; i < 35 + numUltimate; i++)
    {
        mvwaddch(win,3,i,'#');
    }
    mvwprintw(win,4,30,"Boss: ");
    for (int i = 36; i < 36+ bossHealth / 10 + 1; i++)
    {
        mvwaddch(win,4,i,'/');
    }
    mvwprintw(win,5,30,"Base_HP: ");
    for (int i = 39; i < 39 + base_health; i++)
    {
        mvwaddch(win,5,i,'/');
    }
    

}

  /*after making ultimate attacks, some chars will be lost this ensures nothing lost
  input: window, the y coordinate where player shoots with laser */
void recover(WINDOW* WIN, int lasty){
  
    for (int i = 1; i < 78; i++)
    {
        if (lasty > MAIN_AREA.top+1 && lasty < MAIN_AREA.bot - 1)
        {
            mvwaddch(WIN,lasty -1,i,' ');
            mvwaddch(WIN,lasty,i,' ');
            mvwaddch(WIN,lasty + 1,i,' ');
            
        } else{
            mvwaddch(WIN,lasty,i,' ');
    }
    }
    //print boss again to ensure details of the boss is not lost.
    if(isBoss == true){
    printBoss(WIN);
    }
}

   
/* making ultimate attack in form of laser beam with length of 3 y units. clear all enemies
input: window ,the y coordinate where player shoots with laser
*/
void ultimate(WINDOW* WIN, int& lasty){
    eraseEnemy(WIN);
    lasty = player.pos.y;
    for (int i = 1; i < 78; i++)
    {
        if (player.pos.y > MAIN_AREA.top + 1 && player.pos.y < MAIN_AREA.bot - 1)
        {
            mvwaddch(WIN,player.pos.y -1,i,'-');
            mvwaddch(WIN,player.pos.y,i,'-');
            mvwaddch(WIN,player.pos.y + 1,i,'-');
            
        } else{
            mvwaddch(WIN,player.pos.y,i,'-');
    }
    }
    // for any enemy that exists currently, they will die immediately and you score 10* numofEnemy
    for (size_t i = 0; i < MAX_NUM_ENEMY; i++)
    {
        if (ENEMY_LIST[i].exist == true)
        {
            player.score += 10;
            ENEMY_LIST[i].exist = false;
        }
        
    }
    

}


//prints the player airplane
//input: window
void printPlayer(WINDOW* WIN){

    mvwaddch(WIN, player.pos.y, player.pos.x, ')');
    mvwaddch(WIN, player.pos.y, player.pos.x - 1, '-');
    mvwaddch(WIN, player.pos.y + 1, player.pos.x - 1, '/');
    mvwaddch(WIN, player.pos.y - 1, player.pos.x - 1, '\\');

}

//erases the player airplane
//input: window
void erasePlayer(WINDOW* WIN){

    mvwaddch(WIN, player.pos.y, player.pos.x, ' ');
    mvwaddch(WIN, player.pos.y, player.pos.x - 1, ' ');
    mvwaddch(WIN, player.pos.y + 1, player.pos.x - 1, ' ');
    mvwaddch(WIN, player.pos.y - 1, player.pos.x - 1, ' ');

}


// updates player's score
// input: window and current score
void updateScore(WINDOW* win, int num){
    mvwprintw(win,1,1,"Score: %d",num);
}

 //file input: to read our intro_page.txt and end_page designed in ascii chars. 
 // input: filename of the file to open, y and x coordinate of initial printing position 
void mv_print_file(string file_loc, int y, int x){
   
    ifstream fin;
    fin.open(file_loc);
    string str;
    while(getline(fin, str)){
       mvprintw(y,x,str.c_str()); 
       y++;
    }
    fin.close();
}

// displayes intro page
void displayIntroScr(){
    mv_print_file("src/introScr.txt",0,0);
    while (getch()!='p');
    clear();

}


//displays ending page
void displayDefScr(){
    nodelay(stdscr, false);
    clear();
    mv_print_file("src/defScr.txt",0,0);
}

//displays victory page

void displayVicScr(){
    nodelay(stdscr, false);
    clear();
    mv_print_file("src/vicScr.txt",0,0);
}

// checks for any collision and update its effect
void CollisionCheck(){
    for (int i = 0; i < MAX_NUM_BULLET; i++)
    {

        if (BulletList[i].exist == false)  //ignores dead bullet
        {
            continue;
        }
        for (int j = 0; j < MAX_NUM_ENEMY; j++)
        {
            if (ENEMY_LIST[j].exist == false){
                continue;
            }
            // player kills one enemy when the bullet and enemy share the same row.
            if (ENEMY_LIST[j].pos.y == BulletList[i].pos.y && BulletList[i].player == true)
            {
                if (abs(ENEMY_LIST[j].pos.x - BulletList[i].pos.x) / BulletList[i].speed < 1)
                {
                    BulletList[i].exist = false;
                    ENEMY_LIST[j].exist = false;
                    player.score+=10;
                }
                
            }
            // enemy and player at the same location
            if (abs(ENEMY_LIST[j].pos.x - player.pos.x) == 0 && ENEMY_LIST[j].pos.y == player.pos.y)
            {
                player.hp = 0;  //dies directly
                if (player.hp == 0)
                {
                    player.symbol = ' ';
                }
            }
        }
        
        
        if (isBoss == true) // player's bullet between the size of the boss attacks the boss. 
        {
            
            if (BulletList[i].player == true)
            {
                if (BulletList[i].pos.y <= BOSS_Y_COORDINATE_BOTTOM && BulletList[i].pos.x >= BOSS_Y_COORDINATE_TOP)
                {
                    
                    if (BulletList[i].pos.x >= BOSS_X_COORDINATE_LEFT)
                    {
                        boss_health -= 1;
                        BulletList[i].exist = false;
                    }
                
                }
                
                
            }

        }

        // when enemy's bullet coincides with the player, player's hp reduces by 1
        if (BulletList[i].pos.y == player.pos.y && BulletList[i].player == false)
        {
            if (abs(player.pos.x - BulletList[i].pos.x)/BulletList[i].speed < 1){
                if (player.hp == 0)
                {
                    player.symbol = ' ';
                }
                BulletList[i].exist = false;
                    
                player.hp--;
            }
        }
        




    }
    
}


void generateBullet(){

    // generate player's bullet

    for (int i = 0; i < MAX_NUM_BULLET; i++)
    {
        
        if (BulletList[i].exist == false)
        {
            BulletList[i].exist = true;
            BulletList[i].pos.x = player.pos.x + 1; 
            BulletList[i].pos.y = player.pos.y;        
            BulletList[i].symbol = '>';
            BulletList[i].speed = 2;  
            BulletList[i].player = true;
            break;
        }

    }
    
}

void printBullet(WINDOW* WIN){
    //print bullet

    for (int i = 0; i < MAX_NUM_BULLET; i++)
    {
        
        if (BulletList[i].exist == true)
        {
            mvwaddch(WIN, BulletList[i].pos.y, BulletList[i].pos.x, BulletList[i].symbol);   
        }

    }

}


// make it disappear if bullet out of boundary
void updateBullet(){


    for (int i = 0; i < MAX_NUM_BULLET; i++)
    {

        if (BulletList[i].exist == true && BulletList[i].player == true)
        {
            BulletList[i].pos.x += BulletList[i].speed;

            if (BulletList[i].pos.x >= MAIN_AREA.right)
            {
                BulletList[i].exist = false;
            }
        }else if (BulletList[i].exist == true && BulletList[i].player == false)
        {
            BulletList[i].pos.x -= BulletList[i].speed;

            if (BulletList[i].pos.x <= MAIN_AREA.left)
            {
                BulletList[i].exist = false;
            }
        }

    }
    
}


//erases bullet
//input: Window (main)
void eraseBullet(WINDOW* WIN){

    for (int i = 0; i < MAX_NUM_BULLET; i++)
    {
        
        if (BulletList[i].exist == true)
        {
            mvwaddch(WIN, BulletList[i].pos.y, BulletList[i].pos.x, ' ');   
        }

    }

}


/* this function creates windows for the main and sub one. 
input: height width, the coordindate of top left and top*/
WINDOW* createNewWin(int height, int width, int starty, int startx, bool isDataWin)
{
    WINDOW* localWin = newwin(height, width, starty, startx);
    box(localWin, 0, 0);
    wrefresh(localWin);

    if (isDataWin == true)
    {
        int score = 0;
        mvwprintw(localWin, 1, 1, "SCORE: %d",0);
        starty += 2;
        startx += 2;
    }

    wrefresh(localWin);
    return localWin;
}


// timer
//input: time passed in second , the INFO window
void showTime(int second, WINDOW* win){
   int minute = second / 60;
   second %= 60;
   if (minute/10 == 0)
   {
       if (second / 10== 0){
        mvwprintw(win, 1, 68,"TIME: 0%d:0%d",minute,second);
        }
        else{
            mvwprintw(win, 1, 68,"TIME: 0%d:%d",minute,second);
        }  
   }
   else{
        if (second / 10== 0){
        mvwprintw(win, 1, 68,"TIME: %d:0%d",minute,second);
        }
        else{
            mvwprintw(win, 1, 68,"TIME: %d:%d",minute,second);
        }
       
   }
   
   wrefresh(win);
 
}

int main(int argc, char const *argv[])
{
    initscr();      //initial setup
    refresh();
    cbreak();
    noecho();    
    curs_set(0);
    keypad(stdscr,true);

    displayIntroScr(); 

    nodelay(stdscr,true);
    int maxX, maxY;

    getmaxyx(stdscr,maxY,maxX); 

    bool restart = true;
    int best = 0;

    // if fails, player can choose to restart or not
    // if wins, jump to victory page
    while(restart == true){
        int height =16;     //parameter for the two windows
        int width = 80;
        int starty = 0;
        int startx = 0;

        //create the main game window
        WINDOW* MAIN = createNewWin(height, width, starty, startx, false);

        starty = height;
        height = 8;

        //create the data window
        WINDOW* INFO = createNewWin(height, width, starty, startx, true);
    

        nodelay(INFO,TRUE);
        nodelay(MAIN,TRUE);
    
        player.pos.x = 5;
        player.pos.y = 5;
        player.symbol = 'E';
        player.hp = 10;   // can be reduced to increase the difficulty level
        boss_health = 50;
        base_health = 10;
        numOfUltimate = 3;
        player.score = 0;
        char c;
        restart = false;

        
        mvwaddch(MAIN,player.pos.y,player.pos.x,player.symbol);
        

        time_t start = time(NULL); // starting time
        time_t finished; // ending time
        srand(time(0));
        bool exit = false;
        int tick = 0;
        bool victory = false;

        for (int i = 0; i < MAX_NUM_ENEMY; i++)
        {
            Enemy* temp = new Enemy;
            temp->exist = false;
            ENEMY_LIST[i] = *temp;

        }
        
        for (int i = 0; i < MAX_NUM_BULLET; i++)
        {
            Bullet* temp = new Bullet;
            temp->exist = false;
            BulletList[i] = *temp;
        }

        int lasty = 1;
        while (true)
        {   

            usleep(50000);   // Frame rate approximately 50 fps
            
            time_t now = time(NULL);
            time_t now2 = 1;
            int passed = difftime(now,start);

            showTime(passed,INFO);

            char input_key;
            input_key = wgetch(MAIN);   
            
            switch (input_key)  // wasd to control trajectory of player's airplane
            {
            case 'w':
                if (player.pos.y > MAIN_AREA.top + 2)
                {
                    erasePlayer(MAIN);
                    player.pos.y -= 1;
                }
                break;
            
            case 's':
                if (player.pos.y < MAIN_AREA.bot - 2)
                {
                    erasePlayer(MAIN);
                    player.pos.y += 1;
                }
                break;
            
            case 'a':
                if (player.pos.x > MAIN_AREA.left + 3)
                {
                    erasePlayer(MAIN);
                    player.pos.x -= 3;
                }
                break;

            case 'd':
                if (player.pos.x < MAIN_AREA.right - 3)
                {
                    erasePlayer(MAIN);
                    player.pos.x += 3;
                }
                break;
            
            case 'r':
                if (numOfUltimate > 0)
                {
                    now2 = time(NULL);
                    ultimate(MAIN,lasty);
                    numOfUltimate -= 1; 
                }
                // detect if beam hits the boss
                if (isBoss == true && numOfUltimate!=0)
                {
                    if (lasty - 1 <= BOSS_Y_COORDINATE_BOTTOM && lasty + 1 >= BOSS_Y_COORDINATE_TOP){
                        boss_health -=10;
                    }
                    break;
                }
                
               
            // Space key reflects ' '
            case ' ':
                generateBullet();
                break;
            
            case 'q':
                exit = true;
                break;

            default:
                break;
            }
            time_t later = time(NULL); 

            mvwprintw(MAIN,1,1,"%d",passed);
            if (difftime(later,now2) >= 3)  // recovers to the normal page after three seconds of laser beam emission/ultimate. 
            {
              recover(MAIN,lasty);
              
            }

            eraseEnemy(MAIN);
            eraseBullet(MAIN);

            updateEnemy();
            updateBullet();
            CollisionCheck();
            updateScore(INFO,player.score);
            printInfo(INFO, player.hp, numOfUltimate, boss_health,base_health);
            if (tick % ENEMY_GEN_RATE == 0) 
            {
                generateEnemy();
            }
            enemyBullet();
            printEnemy(MAIN);
            printBullet(MAIN);

            printPlayer(MAIN);

            
            wrefresh(MAIN);
            wrefresh(INFO);

            tick++;

            if(player.hp <= 0 || base_health == 0){
                break;
            }
            if (exit) break;

            if(player.score >= 300){ // increase it to make the game harder

                printBoss(MAIN);
                isBoss = true;
                ENEMY_GEN_RATE = 25;

            }

            if(boss_health <= 0){
                victory = true;
                
                break;
            }

        }
        finished = time(NULL);
        if (player.score > best)
        {
            best = player.score;
        }
        // file output: a summary of performace
        ofstream fout;
        fout.open("summary.txt");
        fout<<"Score: "<<player.score<<'\n';
        fout<<"Time Used: "<<difftime(finished,start)<<'\n';
        fout.close();
        if (victory != true)
        {
            displayDefScr();
            char b = getch();
            while (b != 'q' && b != 'r'){
                b = getch();
            }
            if (b =='r'){
                restart = true;
            }
        }
        
        else{

            displayVicScr();

            while(getch() != 'q');

        }
        cleanBoss(MAIN); // cleans the boss at the end
        isBoss =false; // set isBoss to false so that recover would not be called. 
      
        
        
    }
    endwin();
    return 0;
        
    }
    
    
   

