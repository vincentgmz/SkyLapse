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
int base_health = 10;
int ENEMY_GEN_RATE = 25;
int boss_health = 50;
AREA MAIN_AREA = {0,15,0,79};
AREA INFO_AREA = {16,24,0,80};
Bullet BulletList[MAX_NUM_BULLET];
bool isBoss = false;

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
    printBoss(WIN);
}
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
    
    for (size_t i = 0; i < MAX_NUM_ENEMY; i++)
    {
        if (ENEMY_LIST[i].exist == true)
        {
            player.score += 10;
            ENEMY_LIST[i].exist = false;
        }
        
    }
    

}

void printPlayer(WINDOW* WIN){

    mvwaddch(WIN, player.pos.y, player.pos.x, ')');
    mvwaddch(WIN, player.pos.y, player.pos.x - 1, '-');
    mvwaddch(WIN, player.pos.y + 1, player.pos.x - 1, '/');
    mvwaddch(WIN, player.pos.y - 1, player.pos.x - 1, '\\');

}

void erasePlayer(WINDOW* WIN){

    mvwaddch(WIN, player.pos.y, player.pos.x, ' ');
    mvwaddch(WIN, player.pos.y, player.pos.x - 1, ' ');
    mvwaddch(WIN, player.pos.y + 1, player.pos.x - 1, ' ');
    mvwaddch(WIN, player.pos.y - 1, player.pos.x - 1, ' ');

}


void updateScore(WINDOW* win, int num){
    mvwprintw(win,1,1,"Score: %d",num);
}

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

void displayIntroScr(){
    mv_print_file("src/introScr.txt",0,0);
    while (getch()!='p');
    clear();

}


void displayDefScr(){
    nodelay(stdscr, false);
    clear();
    mv_print_file("src/defScr.txt",0,0);
}

void displayVicScr(){

    nodelay(stdscr, false);
    clear();
    mv_print_file("src/vicScr.txt",0,0);
}

void CollisionCheck(int lasty){

    for (int i = 0; i < MAX_NUM_BULLET; i++)
    {

        if (BulletList[i].exist == false)
        {
            continue;
        }
        for (int j = 0; j < MAX_NUM_ENEMY; j++)
        {
            if (ENEMY_LIST[j].exist == false){
                continue;
            }

            if (ENEMY_LIST[j].pos.y == BulletList[i].pos.y && BulletList[i].player == true)
            {
                if (abs(ENEMY_LIST[j].pos.x - BulletList[i].pos.x) / BulletList[i].speed < 1)
                {
                    BulletList[i].exist = false;
                    ENEMY_LIST[j].exist = false;
                    player.score+=10;
                }
                
            }

            if (abs(ENEMY_LIST[j].pos.x - player.pos.x) == 0 && ENEMY_LIST[j].pos.y == player.pos.y)
            {
                player.hp = 0;
                if (player.hp == 0)
                {
                    player.symbol = ' ';
                }
            }
        }
        
        
        if (isBoss == true)
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

    for (int i = 0; i < MAX_NUM_BULLET; i++)
    {
        
        if (BulletList[i].exist == true)
        {
            mvwaddch(WIN, BulletList[i].pos.y, BulletList[i].pos.x, BulletList[i].symbol);   
        }

    }

}

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
*/
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
    initscr();
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
    while(restart == true){
        int height =16;
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
        player.hp = 10;
        player.score = 500;
        char c;
        restart = false;

        int numOfUltimate = 3;
        
        mvwaddch(MAIN,player.pos.y,player.pos.x,player.symbol);
        

        time_t start = time(NULL);
        time_t finished;
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
            
            switch (input_key)
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
                if (lasty <= BOSS_Y_COORDINATE_BOTTOM && lasty >= BOSS_Y_COORDINATE_TOP){
                  boss_health -=10;
                  }
                break;
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
            if (difftime(later,now2) >= 3)
            {
              recover(MAIN,lasty);
              
            }

            eraseEnemy(MAIN);
            eraseBullet(MAIN);

            updateEnemy();
            updateBullet();
            CollisionCheck(lasty);
            updateScore(INFO,player.score);
            mvwprintw(INFO,3,2,"%d",player.hp);
            mvwprintw(INFO,4,2,"%d",base_health);
            if (tick % ENEMY_GEN_RATE == 0)
            {
                generateEnemy();
            }
            enemyBullet();
            printEnemy(MAIN);
            printBullet(MAIN);

            printPlayer(MAIN);
            //printWind(INFO);
            
            wrefresh(MAIN);
            wrefresh(INFO);

            tick++;

            if(player.hp <= 0 || base_health == 0){
                break;
            }
            if (exit) break;

            if(player.score >= 500){

                printBoss(MAIN);
                isBoss = true;
                ENEMY_GEN_RATE = 20;

                mvwprintw(INFO, 5, 2, "%d", boss_health);

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

        ofstream fout;
        fout.open("summary.txt");
        fout<<"Score: "<<player.score<<'\n';
        fout<<"Time Used: "<<difftime(finished,start)<<'\n';
        fout.close();
        if (victory != true)
        {
            displayDefScr();
            char b = getch();
            if (b =='r'){
                restart = true;
            }
        }
        
        else{

            displayVicScr();
            getch();

        }
      
        
        
    }
    endwin();
    return 0;
        
    }
    
    
   

