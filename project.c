#include <ncurses.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#define MAX_players 150
#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50
#define MAX_EMAIL_LEN 250
int basefood = 3;
typedef struct{
    int positionx;
    int positiony;
    bool collected;

}gold;
typedef struct{
    int positionx;
    int positiony;
    bool collected;

}blackgold;


typedef struct{
    int positionx;
    int positiony;
    bool collected;

}food;
typedef struct{
    int positionx;
    int positiony;

}pillar;
typedef struct {
    int positionx;
    int positiony;
    int width, height;
   int doorpositionx[4];
    int doorpositiony[4];
    int stairpositionx;
    int stairpositiony;
pillar pillars[12];
int pillarcount;
   food foods[7];
    gold golds[20];
    blackgold blackgolds[20];
    int foodcount;
    int goldcount;
    int blackgoldcount;
} Room;
 float goldsobtaind;

void music();
int settings();
int startnewgame();
int pregamemenu();
int connectrooms(Room*rooms[], int numrooms, int whichway, int firstroom, int secondroom);
int drawroom (Room *room,int whichway, int roomnumber);
void show_temporary_message(int y, int x,const char *message);
        bool hungermessage= false;



int afterhunger=0;
int beforehunger=0;
char selected_music[100]="music2.mp3";

typedef struct{
    int positionx;
    int positiony;
    int whichroom;
    int health;
    int maxhealth;
    int gold;
    int hunger;
} adventurer;
float health=12;
float maxhealth=12;
float hunger=0;
adventurer player1;
int ismusicon=1;
int playerx;
int playery;
int firstplace;
bool coridor1[4][16]={false};
bool coridor2[4][14]={false};
bool wasinroom[4][8]={false};
bool roomdrawn[4][8]= {false};
bool coridordrawn1[4][8]={false};
bool corridordrawn2[4][7]={false};
int doornumber[8]={1,3,2,2,3,2,2,1};
int doornumber2[8]={1,2,1,3,3,1,2,1};
int floornumber = 0;
int foodscollected=0;
float goldcount=0;
int showmap(Room*rooms[], int whichway, int numrooms){
    clear();
    for (int i =0; i < numrooms; i++)
    {
        drawroom(rooms[i],whichway,i);


    }

    int ch;
    if (whichway==1){
        
                                connectrooms(rooms, numrooms,whichway, 0, 1);
                        connectrooms(rooms, numrooms,whichway, 1,2 );
                        connectrooms(rooms, numrooms,whichway, 2,4 );
                        connectrooms(rooms, numrooms,whichway, 2,5 );
                     connectrooms(rooms, numrooms,whichway, 3,4 );
                        connectrooms(rooms, numrooms,whichway, 4,5 );
                        connectrooms(rooms, numrooms,whichway, 3,6 );
                        connectrooms(rooms, numrooms,whichway, 6,7 );


    }
    else if( whichway==0){
                        connectrooms(rooms, numrooms,whichway, 0, 3);
                        connectrooms(rooms, numrooms,whichway, 1, 4);
                        connectrooms(rooms, numrooms,whichway, 1, 2);
                        connectrooms(rooms, numrooms,whichway, 3, 4);
                        connectrooms(rooms, numrooms,whichway, 4, 5);
                        connectrooms(rooms, numrooms,whichway, 3, 6);
                        connectrooms(rooms, numrooms,whichway, 6, 7);

    }
    mvprintw(playery, playerx, "@");
    do {
        ch = getch();
    }
    while (ch != 'm' && ch !='M');
    clear ();
    refresh();
     if (whichway==1){
            if(coridor1[floornumber][0]){
             connectrooms(rooms, numrooms,whichway, 0, 1);

            }
            
         if (coridor1[floornumber][1] ){
                connectrooms(rooms, numrooms,whichway, 1, 0);

            }
         if(coridor1[floornumber][2]){
            connectrooms(rooms, numrooms,whichway, 1,2 );

            }
            if(coridor1[floornumber][3]){
              connectrooms(rooms, numrooms,whichway, 2,1 );

            }
             if(coridor1[floornumber][4]){
                        connectrooms(rooms, numrooms,whichway, 2,4 );

            }
            if (coridor1[floornumber][5]){
                 connectrooms(rooms, numrooms,whichway, 4,2 );

            }
            if (coridor1[floornumber][6]){
                connectrooms(rooms, numrooms,whichway, 2,5 );

            }
            if (coridor1[floornumber][7]){
                        connectrooms(rooms, numrooms,whichway, 5,2 );

            }
            if (coridor1[floornumber][8]){
                        connectrooms(rooms, numrooms,whichway, 3,4 );

            }
            if (coridor1[floornumber][9]){
                        connectrooms(rooms, numrooms,whichway, 4,3 );

            }
            if (coridor1[floornumber][10]){
                        connectrooms(rooms, numrooms,whichway, 4,5 );

            }
            if (coridor1[floornumber][11]){
                        connectrooms(rooms, numrooms,whichway, 5,4 );

            }
            if (coridor1[floornumber][12]){
                        connectrooms(rooms, numrooms,whichway, 3,6 );

            }
            if (coridor1[floornumber][13]){
                        connectrooms(rooms, numrooms,whichway, 6,3 );

            }
            if (coridor1[floornumber][14]){
                        connectrooms(rooms, numrooms,whichway, 6,7 );

            }
            if (coridor1[floornumber][15]){
                        connectrooms(rooms, numrooms,whichway, 7,6 );

            }
            for (int i = 0; i < numrooms;i++){
                if(wasinroom[floornumber][i]){
                    drawroom(rooms[i],whichway,i);
                }
            }
            mvprintw(playery,playerx,"@");


            
            
        }
        else if (whichway==0){
            if (coridor2[floornumber][0]){
                connectrooms(rooms,numrooms,whichway,0,3);
            }
            if (coridor2[floornumber][1]){
                connectrooms(rooms,numrooms,whichway,3,0);
            }
            if (coridor2[floornumber][2]){
                connectrooms(rooms,numrooms,whichway,1,4);
            }
            if (coridor2[floornumber][3]){
                connectrooms(rooms,numrooms,whichway,4,1);
            }
            if (coridor2[floornumber][4]){
                connectrooms(rooms,numrooms,whichway,1,2);
            }
            if (coridor2[floornumber][5]){
                connectrooms(rooms,numrooms,whichway,2,1);
            }
            if (coridor2[floornumber][6]){
                connectrooms(rooms,numrooms,whichway,3,4);
            }
            if (coridor2[floornumber][7]){
                connectrooms(rooms,numrooms,whichway,4,3);
            }
            if (coridor2[floornumber][8]){
                connectrooms(rooms,numrooms,whichway,4,5);
            }
            if (coridor2[floornumber][9]){
                connectrooms(rooms,numrooms,whichway,5,4);
            }
            if (coridor2[floornumber][10]){
                connectrooms(rooms,numrooms,whichway,3,6);
            }
            if (coridor2[floornumber][11]){
                connectrooms(rooms,numrooms,whichway,6,3);
            }
            if (coridor2[floornumber][12]){
                connectrooms(rooms,numrooms,whichway,6,7);
            }
            if (coridor2[floornumber][13]){
                connectrooms(rooms,numrooms,whichway,7,6);
            }
            for (int i = 0; i < numrooms;i++){
                if(wasinroom[floornumber][i]){
                    drawroom(rooms[i],whichway,i);
                }
            }
            mvprintw(playery,playerx,"@");

                
        }

}
void foodmenu(Room*rooms[],int whichway,int numrooms){
    clear();
    mvprintw(0,1,"Press the letter to consume");
    mvprintw(2,1,"a ) %d portions of food", foodscollected);
    // خوردن غذا رو اضافه کن
    int ch;
    do{
    ch =getch();

    }
    while (ch!='q' && ch !='a');
    if (ch=='Q'||ch=='q')
    {   clear();
    refresh();
        if (whichway==1){
            if(coridor1[floornumber][0]){
             connectrooms(rooms, numrooms,whichway, 0, 1);

            }
            
         if (coridor1[floornumber][1] ){
                connectrooms(rooms, numrooms,whichway, 1, 0);

            }
         if(coridor1[floornumber][2]){
            connectrooms(rooms, numrooms,whichway, 1,2 );

            }
            if(coridor1[floornumber][3]){
              connectrooms(rooms, numrooms,whichway, 2,1 );

            }
             if(coridor1[floornumber][4]){
                        connectrooms(rooms, numrooms,whichway, 2,4 );

            }
            if (coridor1[floornumber][5]){
                 connectrooms(rooms, numrooms,whichway, 4,2 );

            }
            if (coridor1[floornumber][6]){
                connectrooms(rooms, numrooms,whichway, 2,5 );

            }
            if (coridor1[floornumber][7]){
                        connectrooms(rooms, numrooms,whichway, 5,2 );

            }
            if (coridor1[floornumber][8]){
                        connectrooms(rooms, numrooms,whichway, 3,4 );

            }
            if (coridor1[floornumber][9]){
                        connectrooms(rooms, numrooms,whichway, 4,3 );

            }
            if (coridor1[floornumber][10]){
                        connectrooms(rooms, numrooms,whichway, 4,5 );

            }
            if (coridor1[floornumber][11]){
                        connectrooms(rooms, numrooms,whichway, 5,4 );

            }
            if (coridor1[floornumber][12]){
                        connectrooms(rooms, numrooms,whichway, 3,6 );

            }
            if (coridor1[floornumber][13]){
                        connectrooms(rooms, numrooms,whichway, 6,3 );

            }
            if (coridor1[floornumber][14]){
                        connectrooms(rooms, numrooms,whichway, 6,7 );

            }
            if (coridor1[floornumber][15]){
                        connectrooms(rooms, numrooms,whichway, 7,6 );

            }
            for (int i = 0; i < numrooms;i++){
                if(wasinroom[floornumber][i]){
                    drawroom(rooms[i],whichway,i);
                }
            }
            mvprintw(playery,playerx,"@");


            
            
        }
        else if (whichway==0){
            if (coridor2[floornumber][0]){
                connectrooms(rooms,numrooms,whichway,0,3);
            }
            if (coridor2[floornumber][1]){
                connectrooms(rooms,numrooms,whichway,3,0);
            }
            if (coridor2[floornumber][2]){
                connectrooms(rooms,numrooms,whichway,1,4);
            }
            if (coridor2[floornumber][3]){
                connectrooms(rooms,numrooms,whichway,4,1);
            }
            if (coridor2[floornumber][4]){
                connectrooms(rooms,numrooms,whichway,1,2);
            }
            if (coridor2[floornumber][5]){
                connectrooms(rooms,numrooms,whichway,2,1);
            }
            if (coridor2[floornumber][6]){
                connectrooms(rooms,numrooms,whichway,3,4);
            }
            if (coridor2[floornumber][7]){
                connectrooms(rooms,numrooms,whichway,4,3);
            }
            if (coridor2[floornumber][8]){
                connectrooms(rooms,numrooms,whichway,4,5);
            }
            if (coridor2[floornumber][9]){
                connectrooms(rooms,numrooms,whichway,5,4);
            }
            if (coridor2[floornumber][10]){
                connectrooms(rooms,numrooms,whichway,3,6);
            }
            if (coridor2[floornumber][11]){
                connectrooms(rooms,numrooms,whichway,6,3);
            }
            if (coridor2[floornumber][12]){
                connectrooms(rooms,numrooms,whichway,6,7);
            }
            if (coridor2[floornumber][13]){
                connectrooms(rooms,numrooms,whichway,7,6);
            }
            for (int i = 0; i < numrooms;i++){
                if(wasinroom[floornumber][i]){
                    drawroom(rooms[i],whichway,i);
                }
            }
            mvprintw(playery,playerx,"@");

                
        }
    }
    else if (ch == 'a'){

        if(foodscollected > 0){
            show_temporary_message(20,40,"You have consumed 1 portion of food");
            foodscollected--;
            if (health<maxhealth){
                health++;
            }
            if (hunger>100){
                hunger-=100;
            }
            else if(hunger<=100){
                hunger=0;            }

            foodmenu(rooms, whichway,numrooms);

        }
        else if (foodscollected<=0){
          show_temporary_message(20,40,"You don't have any food to consume");
            foodmenu(rooms, whichway,numrooms);


        }
    }
    
}
void show_temporary_message(int y, int x,const char *message) {
    
    char backup[256];
    mvinnstr(y, x, backup, sizeof(backup) - 1);
    mvprintw(y, x, message);
    refresh();
    int ch;
    do {
        ch = getch();
    }
    while(ch != ' ');
    
    if (ch==' '){
mvprintw(y, x, backup);
    refresh();
    }
    
}

void playerplacement (adventurer player1,Room * rooms[], int firstplace) {
    adventurer number1;

    player1.positionx = rooms[firstplace]->positionx + rooms[firstplace]->width/2;
    playerx = rooms[firstplace]->positionx + rooms[firstplace]->width/2;
    player1.positiony = rooms[firstplace]->positiony+ rooms[firstplace]->height/2;
    playery = rooms[firstplace]->positiony+ rooms[firstplace]->height/2;
    mvprintw(player1.positiony, player1.positionx, "@");
}
int checkoverlap(Room * newroom, Room *rooms[], int numrooms){
    for (int i = 0 ; i < numrooms; i++ ){
        if (newroom->positionx < rooms[i]->positionx + rooms[i]->width &&
        newroom->positionx + newroom->width > rooms[i]->positionx &&
        newroom->positiony < rooms[i]->positiony + rooms[i]->height &&
        newroom->positiony + newroom->height > rooms[i]->positiony)
        {
            return 1;
        }
    }
    return 0;
}
Room * creatroom(int section, Room * rooms[], int numrooms,int whichway, int roomnumber){
    Room * newroom = malloc (sizeof(Room));

    switch (section)
    {
        case 0: newroom->positionx = 5; newroom->positiony = 5; break;
        case 1: newroom->positionx = 45; newroom->positiony = 5; break;
        case 2: newroom->positionx = 85; newroom->positiony = 5; break;
        case 3: newroom->positionx = 5; newroom->positiony = 23; break;
        case 4: newroom->positionx = 45; newroom->positiony = 23; break;
        case 5: newroom->positionx = 85; newroom->positiony = 23; break;
        case 6: newroom->positionx = 5; newroom->positiony = 37;break;
        case 7: newroom->positionx = 45; newroom->positiony = 37; break;

    }
    newroom ->height = rand () % 8 + 5;
    newroom->width = rand () %17 + 6;
    int overlap =1; 
    while ( overlap)
    {
        int randomx= rand () % (29 - newroom->width +1);
        if(randomx < 0)
            {
                randomx =0;
            }
            newroom -> positionx += randomx;
        int randomy= rand () % (12 - newroom->height +1);
         if(randomy < 0)
            {
                randomy =0;
            }
                        newroom -> positiony += randomy;

        overlap = checkoverlap (newroom , rooms , numrooms);

    }
    if (whichway==0){
        if(roomnumber==0){
             newroom ->doorpositionx[0] = newroom->positionx+ newroom ->width/2;
        newroom->doorpositiony[0]= newroom->positiony + newroom->height - 1;
        //down
        }
        else if (roomnumber==1){
            newroom ->doorpositionx[0] = newroom ->positionx+newroom ->width/2;
       newroom ->doorpositiony[0]= newroom ->positiony + newroom->height - 1;
        //down
        newroom ->doorpositionx[1] = newroom ->positionx + newroom ->width -1;
        newroom ->doorpositiony[1]= newroom ->positiony + newroom->height/2;
        //right

        }
        else if(roomnumber==2){
        newroom ->doorpositionx[0] = newroom ->positionx;
        newroom ->doorpositiony[0]= newroom ->positiony + newroom ->height/2;
        // left
        }
        else if ( roomnumber == 3){
            newroom->doorpositionx[0] = newroom ->positionx+newroom ->width/2;
       newroom ->doorpositiony[0]= newroom->positiony;
        //up
         newroom ->doorpositionx[1] = newroom ->positionx + newroom ->width -1;
        newroom ->doorpositiony[1]= newroom ->positiony + newroom->height/2;
        //right
        newroom ->doorpositionx[2] = newroom ->positionx+ newroom ->width/2;
        newroom ->doorpositiony[2]= newroom ->positiony + newroom->height - 1;
        //down
        }
        else if (roomnumber == 4){
            newroom ->doorpositionx[0] = newroom ->positionx;
        newroom ->doorpositiony[0]= newroom ->positiony + newroom ->height/2;
        // left
        newroom->doorpositionx[1] = newroom ->positionx+newroom ->width/2;
       newroom ->doorpositiony[1]= newroom->positiony;
        //up
        newroom ->doorpositionx[2] = newroom->positionx + newroom ->width -1;
     newroom ->doorpositiony[2]= newroom ->positiony + newroom ->height/2;
        //right

        }
        else if (roomnumber == 5){
            newroom ->doorpositionx[0] = newroom ->positionx;
        newroom ->doorpositiony[0]= newroom ->positiony + newroom ->height/2;
        // left
        }
        else if (roomnumber==6){
            newroom->doorpositionx[0] = newroom ->positionx+newroom ->width/2;
       newroom ->doorpositiony[0]= newroom->positiony;
        //up
         newroom ->doorpositionx[1] = newroom ->positionx + newroom ->width -1;
        newroom ->doorpositiony[1]= newroom ->positiony + newroom->height/2;
        //right
        }
        else if (roomnumber== 7){
            newroom ->doorpositionx[0] = newroom ->positionx;
        newroom ->doorpositiony[0]= newroom ->positiony + newroom ->height/2;
        // left
        }
    }
    else if (whichway==1){
    if (roomnumber == 0){
        newroom->doorpositionx[0] = newroom->positionx + newroom->width - 1;
        newroom->doorpositiony[0]= newroom ->positiony + newroom ->height/2;
    }
   else if (roomnumber == 1){
        newroom ->doorpositionx[0] = newroom ->positionx;
        newroom ->doorpositiony[0]= newroom ->positiony + newroom ->height/2;
        // left
        newroom ->doorpositionx[1] = newroom ->positionx + newroom ->width -1;
        newroom ->doorpositiony[1]= newroom ->positiony + newroom->height/2;
        //right
        newroom ->doorpositionx[2] = newroom ->positionx+ newroom ->width/2;
        newroom ->doorpositiony[2]= newroom ->positiony + newroom->height - 1;
        //down
        
    }
   else if (roomnumber ==2 ){
        newroom->doorpositionx[0] = newroom ->positionx;
        newroom ->doorpositiony[0]= newroom ->positiony +newroom ->height/2;
        //left
        newroom ->doorpositionx[1] = newroom ->positionx+ newroom ->width/2;
       newroom ->doorpositiony[1]= newroom ->positiony + newroom ->height - 1;
        //down

    }
   else if (roomnumber ==3){
         newroom ->doorpositionx[0] = newroom ->positionx + newroom ->width -1;
       newroom ->doorpositiony[0]= newroom ->positiony + newroom ->height/2;
        //right
         newroom ->doorpositionx[1] = newroom ->positionx+newroom ->width/2;
       newroom ->doorpositiony[1]= newroom ->positiony + newroom->height - 1;
        //down
    }
   else if(roomnumber ==4 ){
        newroom ->doorpositionx[0] = newroom ->positionx;
       newroom ->doorpositiony[0]= newroom ->positiony + newroom->height/2;
        //left
        newroom->doorpositionx[1] = newroom ->positionx+newroom ->width/2;
       newroom ->doorpositiony[1]= newroom->positiony;
        //up
         newroom ->doorpositionx[2] = newroom->positionx + newroom ->width -1;
     newroom ->doorpositiony[2]= newroom ->positiony + newroom ->height/2;
        //right
    }
    else if(roomnumber==5){
        newroom ->doorpositionx[0] = newroom ->positionx;
       newroom->doorpositiony[0]= newroom ->positiony + newroom ->height/2;
        //left
       newroom->doorpositionx[1] = newroom ->positionx+newroom->width/2;
       newroom ->doorpositiony[1]= newroom ->positiony;
        //up

    }
    else if(roomnumber == 6){
         newroom ->doorpositionx[0] = newroom ->positionx + newroom ->width -1;
        newroom ->doorpositiony[0]= newroom ->positiony + newroom ->height/2;
        //right
       newroom ->doorpositionx[1] = newroom ->positionx+newroom ->width/2;
      newroom->doorpositiony[1]= newroom ->positiony;
        //up
    }
    else if (roomnumber == 7){
       newroom ->doorpositionx[0] = newroom->positionx;
        newroom->doorpositiony[0]= newroom ->positiony + newroom ->height/2;
        //left
    }
    }


    return newroom;
    
} 

int drawroom (Room *room,int whichway, int roomnumber){
    int x , y; 
    for (x = room ->positionx ; x < room -> positionx + room ->width;x++)
    {
        mvprintw(room->positiony, x, "-");
        mvprintw(room->positiony + room->height - 1, x, "-");
    }
    for (y = room ->positiony+1 ; y < room -> positiony + room -> height -1; y++ )
    {
        mvprintw(y, room->positionx, "|");
        mvprintw(y, room->positionx + room->width - 1, "|");
        for (x = room -> positionx +1 ; x < room -> positionx + room -> width -1 ; x++){
                        mvprintw(y, x, ".");

        }

    // رسم در ها
    

    }
    if(whichway==1){ 
    for (int i =0 ; i < doornumber[roomnumber]; i++)
    {   
        mvprintw(room->doorpositiony[i], room->doorpositionx[i], "+");
    }
    }
    else if (whichway== 0){
        for (int i =0 ; i < doornumber2[roomnumber]; i++)
    {   
        mvprintw(room->doorpositiony[i], room->doorpositionx[i], "+");
    }
    }
    
   
}
int connectrooms(Room*rooms[], int numrooms, int whichway, int firstroom, int secondroom){
    if (whichway ==0){
            //up tp down
        if (firstroom==0 && secondroom==3){
            int x1=rooms[0]->doorpositionx[0];
         int y1 = rooms[0]->doorpositiony[0]+1;
         int x2 = rooms[3]->doorpositionx[0];
        int y2= rooms[3]->doorpositiony[0];
          while(y1 != y2-1){
            mvprintw(y1,x1,"#");
            y1++;
        }
        if (x1 != x2){
        if (x1 <x2){
        while(x1!= x2+1){
            mvprintw(y1,x1,"#");
            x1++;
        }}
        else if (x1 > x2)
        {
            while(x1!= x2-1){
            mvprintw(y1,x1,"#");
            x1--;
        }
        }  
        }
        else if (x1==x2) {
            mvprintw(y1,x1, "#");
        }
        mvprintw(y2,x2,"#");
        }
        //down to up
         if (firstroom==3 && secondroom==0){
            int x1=rooms[3]->doorpositionx[0];
         int y1 = rooms[3]->doorpositiony[0]-1;
         int x2 = rooms[0]->doorpositionx[0];
        int y2= rooms[0]->doorpositiony[0];
          while(y1 != y2+1){
            mvprintw(y1,x1,"#");
            y1--;
        }
        if (x1 != x2){
        if (x1 <x2){
        while(x1!= x2+1){
            mvprintw(y1,x1,"#");
            x1++;
        }}
        else if (x1 > x2)
        {
            while(x1!= x2-1){
            mvprintw(y1,x1,"#");
            x1--;
        }
        }  
        }
        else if (x1==x2) {
            mvprintw(y1,x1, "#");
        }
        mvprintw(y2,x2,"#");
        }
        //up tp down
        if (firstroom==1 && secondroom==4){
            int x1=rooms[1]->doorpositionx[0];
         int y1 = rooms[1]->doorpositiony[0]+1;
         int x2 = rooms[4]->doorpositionx[1];
        int y2= rooms[4]->doorpositiony[1];
          while(y1 != y2-1){
            mvprintw(y1,x1,"#");
            y1++;
        }
        if (x1 != x2){
        if (x1 <x2){
        while(x1!= x2+1){
            mvprintw(y1,x1,"#");
            x1++;
        }}
        else if (x1 > x2)
        {
            while(x1!= x2-1){
            mvprintw(y1,x1,"#");
            x1--;
        }
        }  
        }
        else if (x1==x2) {
            mvprintw(y1,x1, "#");
        }
        mvprintw(y2,x2,"#");
        }
        //down to up
         if (firstroom==4 && secondroom==1){
            int x1=rooms[4]->doorpositionx[1];
         int y1 = rooms[4]->doorpositiony[1]-1;
         int x2 = rooms[1]->doorpositionx[0];
        int y2= rooms[1]->doorpositiony[0];
          while(y1 != y2+1){
            mvprintw(y1,x1,"#");
            y1--;
        }
        if (x1 != x2){
        if (x1 <x2){
        while(x1!= x2+1){
            mvprintw(y1,x1,"#");
            x1++;
        }}
        else if (x1 > x2)
        {
            while(x1!= x2-1){
            mvprintw(y1,x1,"#");
            x1--;
        }
        }  
        }
        else if (x1==x2) {
            mvprintw(y1,x1, "#");
        }
        mvprintw(y2,x2,"#");
        }
         // left to right
            if (firstroom==1 && secondroom ==2) {
        int x1=rooms[1]->doorpositionx[1]+1;
        int y1 = rooms[1]->doorpositiony[1];
        int x2 = rooms[2]->doorpositionx[0];
        int y2= rooms[2]->doorpositiony[0];
        while(x1 != x2-1){
            mvprintw(y1,x1,"#");
            x1++;
        }
        if (y1 != y2){
        if (y1 <y2){
        while(y1!= y2+1){
            mvprintw(y1,x1,"#");
            y1++;
        }}
        else if (y1 > y2)
        {
            while(y1!= y2-1){
            mvprintw(y1,x1,"#");
            y1--;
        }
        }  
        }
        else if (y1==y2) {
            mvprintw(y1,x1, "#");
        }
        
            
        
         mvprintw(y2,x2, "#");
        }
        //right to left
        if (firstroom==2 && secondroom ==1) {
        int x1=rooms[2]->doorpositionx[0]-1;
        int y1 = rooms[2]->doorpositiony[0];
        int x2 = rooms[1]->doorpositionx[1];
        int y2= rooms[1]->doorpositiony[1];
        while(x1 != x2+1){
            mvprintw(y1,x1,"#");
            x1--;
        }
        if (y1 != y2){
        if (y1 <y2){
        while(y1!= y2+1){
            mvprintw(y1,x1,"#");
            y1++;
        }}
        else if (y1 > y2)
        {
            while(y1!= y2-1){
            mvprintw(y1,x1,"#");
            y1--;
        }
        }  
        }
        else if (y1==y2) {
            mvprintw(y1,x1, "#");
        }
            
        
         mvprintw(y2,x2, "#");
        }
        //left to right
        if (firstroom==3 && secondroom ==4) {
        int x1=rooms[3]->doorpositionx[1]+1;
        int y1 = rooms[3]->doorpositiony[1];
        int x2 = rooms[4]->doorpositionx[0];
        int y2= rooms[4]->doorpositiony[0];
        while(x1 != x2-1){
            mvprintw(y1,x1,"#");
            x1++;
        }
        if (y1 != y2){
        if (y1 <y2){
        while(y1!= y2+1){
            mvprintw(y1,x1,"#");
            y1++;
        }}
        else if (y1 > y2)
        {
            while(y1!= y2-1){
            mvprintw(y1,x1,"#");
            y1--;
        }
        }  
        }
         else if (y1==y2){
                        mvprintw(y1,x1,"#");

        }
            
        
         mvprintw(y2,x2, "#");
        }
        //right to left
        if (firstroom==4 && secondroom ==3) {
        int x1=rooms[4]->doorpositionx[0]-1;
        int y1 = rooms[4]->doorpositiony[0];
        int x2 = rooms[3]->doorpositionx[1];
        int y2= rooms[3]->doorpositiony[1];
        while(x1 != x2+1){
            mvprintw(y1,x1,"#");
            x1--;
        }
        if (y1 != y2){
        if (y1 <y2){
        while(y1!= y2+1){
            mvprintw(y1,x1,"#");
            y1++;
        }}
        else if (y1 > y2)
        {
            while(y1!= y2-1){
            mvprintw(y1,x1,"#");
            y1--;
        }
        }  
        }
        else if (y1==y2) {
            mvprintw(y1,x1, "#");
        }
            
        
         mvprintw(y2,x2, "#");
        }
        //left to right
        if (firstroom==4 && secondroom ==5) {
        int x1=rooms[4]->doorpositionx[2]+1;
        int y1 = rooms[4]->doorpositiony[2];
        int x2 = rooms[5]->doorpositionx[0];
        int y2= rooms[5]->doorpositiony[0];
        while(x1 != x2-1){
            mvprintw(y1,x1,"#");
            x1++;
        }
        if (y1 != y2){
        if (y1 <y2){
        while(y1!= y2+1){
            mvprintw(y1,x1,"#");
            y1++;
        }}
        else if (y1 > y2)
        {
            while(y1!= y2-1){
            mvprintw(y1,x1,"#");
            y1--;
        }
        }  
        }
         else if (y1==y2){
                        mvprintw(y1,x1,"#");

        }
            
        
         mvprintw(y2,x2, "#");
        }
        //right to left
        if (firstroom==5 && secondroom ==4) {
        int x1=rooms[5]->doorpositionx[0]-1;
        int y1 = rooms[5]->doorpositiony[0];
        int x2 = rooms[4]->doorpositionx[2];
        int y2= rooms[4]->doorpositiony[2];
        while(x1 != x2+1){
            mvprintw(y1,x1,"#");
            x1--;
        }
        if (y1 != y2){
        if (y1 <y2){
        while(y1!= y2+1){
            mvprintw(y1,x1,"#");
            y1++;
        }}
        else if (y1 > y2)
        {
            while(y1!= y2-1){
            mvprintw(y1,x1,"#");
            y1--;
        }
        }  
        }
        else if (y1==y2) {
            mvprintw(y1,x1, "#");
        }
            
        
         mvprintw(y2,x2, "#");
        }
    if(numrooms==7 || numrooms==8){ 
        //up tp down
        if (firstroom==3 && secondroom==6){
            int x1=rooms[3]->doorpositionx[2];
         int y1 = rooms[3]->doorpositiony[2]+1;
         int x2 = rooms[6]->doorpositionx[0];
        int y2= rooms[6]->doorpositiony[0];
          while(y1 != y2-1){
            mvprintw(y1,x1,"#");
            y1++;
        }
        if (x1 != x2){
        if (x1 <x2){
        while(x1!= x2+1){
            mvprintw(y1,x1,"#");
            x1++;
        }}
        else if (x1 > x2)
        {
            while(x1!= x2-1){
            mvprintw(y1,x1,"#");
            x1--;
        }
        }  
        }
        else if (x1==x2) {
            mvprintw(y1,x1, "#");
        }
        mvprintw(y2,x2,"#");
        }
        //down to up
         if (firstroom==6 && secondroom==3){
            int x1=rooms[6]->doorpositionx[0];
         int y1 = rooms[6]->doorpositiony[0]-1;
         int x2 = rooms[3]->doorpositionx[2];
        int y2= rooms[3]->doorpositiony[2];
          while(y1 != y2+1){
            mvprintw(y1,x1,"#");
            y1--;
        }
        if (x1 != x2){
        if (x1 <x2){
        while(x1!= x2+1){
            mvprintw(y1,x1,"#");
            x1++;
        }}
        else if (x1 > x2)
        {
            while(x1!= x2-1){
            mvprintw(y1,x1,"#");
            x1--;
        }
        }  
        }
        else if (x1==x2) {
            mvprintw(y1,x1, "#");
        }
        mvprintw(y2,x2,"#");
        }
if (numrooms==8){
            //left to right
        if (firstroom==6 && secondroom ==7) {
        int x1=rooms[6]->doorpositionx[1]+1;
        int y1 = rooms[6]->doorpositiony[1];
        int x2 = rooms[7]->doorpositionx[0];
        int y2= rooms[7]->doorpositiony[0];
        while(x1 != x2-1){
            mvprintw(y1,x1,"#");
            x1++;
        }
        if (y1 != y2){
        if (y1 <y2){
        while(y1!= y2+1){
            mvprintw(y1,x1,"#");
            y1++;
        }}
        else if (y1 > y2)
        {
            while(y1!= y2-1){
            mvprintw(y1,x1,"#");
            y1--;
        }
        }  
        }
         else if (y1==y2){
                        mvprintw(y1,x1,"#");

        }
        
            
        
         mvprintw(y2,x2, "#");
        }
        //right to left
        if (firstroom==7 && secondroom ==6) {
        int x1=rooms[7]->doorpositionx[0]-1;
        int y1 = rooms[7]->doorpositiony[0];
        int x2 = rooms[6]->doorpositionx[1];
        int y2= rooms[6]->doorpositiony[1];
        while(x1 != x2+1){
            mvprintw(y1,x1,"#");
            x1--;
        }
        if (y1 != y2){
        if (y1 <y2){
        while(y1!= y2+1){
            mvprintw(y1,x1,"#");
            y1++;
        }}
        else if (y1 > y2)
        {
            while(y1!= y2-1){
            mvprintw(y1,x1,"#");
            y1--;
        }
        }  
        }
        else if (y1==y2) {
            mvprintw(y1,x1, "#");
        }
            
        
         mvprintw(y2,x2, "#");
        }


        }

        }







        







        

        
    }
    else if (whichway==1){
            // left to right
            if (firstroom==0 && secondroom ==1) {
        int x1=rooms[0]->doorpositionx[0]+1;
        int y1 = rooms[0]->doorpositiony[0];
        int x2 = rooms[1]->doorpositionx[0];
        int y2= rooms[1]->doorpositiony[0];
        while(x1 != x2-1){
            mvprintw(y1,x1,"#");
            x1++;
        }
        if (y1 != y2){
        if (y1 <y2){
        while(y1!= y2+1){
            mvprintw(y1,x1,"#");
            y1++;
        }}
        else if (y1 > y2)
        {
            while(y1!= y2-1){
            mvprintw(y1,x1,"#");
            y1--;
        }
        }  
        }
        else if (y1==y2) {
            mvprintw(y1,x1, "#");
        }
        
            
        
         mvprintw(y2,x2, "#");
        }
        
        //right to left
        if (firstroom==1 && secondroom ==0) {
        int x1=rooms[1]->doorpositionx[0]-1;
        int y1 = rooms[1]->doorpositiony[0];
        int x2 = rooms[0]->doorpositionx[0];
        int y2= rooms[0]->doorpositiony[0];
        while(x1 != x2+1){
            mvprintw(y1,x1,"#");
            x1--;
        }
        if (y1 != y2){
        if (y1 <y2){
        while(y1!= y2+1){
            mvprintw(y1,x1,"#");
            y1++;
        }}
        else if (y1 > y2)
        {
            while(y1!= y2-1){
            mvprintw(y1,x1,"#");
            y1--;
        }
        }  
        }
        else if (y1==y2) {
            mvprintw(y1,x1, "#");
        }
            
        
         mvprintw(y2,x2, "#");
        }
        //left to right
        if (firstroom==1 && secondroom ==2) {
        int x1=rooms[1]->doorpositionx[1]+1;
        int y1 = rooms[1]->doorpositiony[1];
        int x2 = rooms[2]->doorpositionx[0];
        int y2= rooms[2]->doorpositiony[0];
        while(x1 != x2-1){
            mvprintw(y1,x1,"#");
            x1++;
        }
        if (y1 != y2){
        if (y1 <y2){
        while(y1!= y2+1){
            mvprintw(y1,x1,"#");
            y1++;
        }}
        else if (y1 > y2)
        {
            while(y1!= y2-1){
            mvprintw(y1,x1,"#");
            y1--;
        }
        }  
        }
         else if (y1==y2){
                        mvprintw(y1,x1,"#");

        }
            
        
         mvprintw(y2,x2, "#");
        }
        //right to left
        if (firstroom==2 && secondroom ==1) {
        int x1=rooms[2]->doorpositionx[0]-1;
        int y1 = rooms[2]->doorpositiony[0];
        int x2 = rooms[1]->doorpositionx[1];
        int y2= rooms[1]->doorpositiony[1];
        while(x1 != x2+1){
            mvprintw(y1,x1,"#");
            x1--;
        }
        if (y1 != y2){
        if (y1 <y2){
        while(y1!= y2+1){
            mvprintw(y1,x1,"#");
            y1++;
        }}
        else if (y1 > y2)
        {
            while(y1!= y2-1){
            mvprintw(y1,x1,"#");
            y1--;
        }
        }  
        }
        else if (y1==y2) {
            mvprintw(y1,x1, "#");
        }
            
        
         mvprintw(y2,x2, "#");
        }
        //up tp down
        if (firstroom==2 && secondroom==4){
            int x1=rooms[1]->doorpositionx[2];
         int y1 = rooms[1]->doorpositiony[2]+1;
         int x2 = rooms[4]->doorpositionx[1];
        int y2= rooms[4]->doorpositiony[1];
          while(y1 != y2-1){
            mvprintw(y1,x1,"#");
            y1++;
        }
        if (x1 != x2){
        if (x1 <x2){
        while(x1!= x2+1){
            mvprintw(y1,x1,"#");
            x1++;
        }}
        else if (x1 > x2)
        {
            while(x1!= x2-1){
            mvprintw(y1,x1,"#");
            x1--;
        }
        }  
        }
        else if (x1==x2) {
            mvprintw(y1,x1, "#");
        }
        mvprintw(y2,x2,"#");
        }  
        //down to up
         if (firstroom==4 && secondroom==2){
            int x1=rooms[4]->doorpositionx[1];
         int y1 = rooms[4]->doorpositiony[1]-1;
         int x2 = rooms[1]->doorpositionx[2];
        int y2= rooms[1]->doorpositiony[2];
          while(y1 != y2+1){
            mvprintw(y1,x1,"#");
            y1--;
        }
        if (x1 != x2){
        if (x1 <x2){
        while(x1!= x2+1){
            mvprintw(y1,x1,"#");
            x1++;
        }}
        else if (x1 > x2)
        {
            while(x1!= x2-1){
            mvprintw(y1,x1,"#");
            x1--;
        }
        }  
        }
        else if (x1==x2) {
            mvprintw(y1,x1, "#");
        }
        mvprintw(y2,x2,"#");
        }  
        //up tp down
        if (firstroom==2 && secondroom==5){
            int x1=rooms[2]->doorpositionx[1];
         int y1 = rooms[2]->doorpositiony[1]+1;
         int x2 = rooms[5]->doorpositionx[1];
        int y2= rooms[5]->doorpositiony[1];
          while(y1 != y2-1){
            mvprintw(y1,x1,"#");
            y1++;
        }
        if (x1 != x2){
        if (x1 <x2){
        while(x1!= x2+1){
            mvprintw(y1,x1,"#");
            x1++;
        }}
        else if (x1 > x2)
        {
            while(x1!= x2-1){
            mvprintw(y1,x1,"#");
            x1--;
        }
        }  
        }
        else if (x1==x2) {
            mvprintw(y1,x1, "#");
        }
        mvprintw(y2,x2,"#");
        }
        //down to up
         if (firstroom==5 && secondroom==2){
            int x1=rooms[5]->doorpositionx[1];
         int y1 = rooms[5]->doorpositiony[1]-1;
         int x2 = rooms[2]->doorpositionx[1];
        int y2= rooms[2]->doorpositiony[1];
          while(y1 != y2+1){
            mvprintw(y1,x1,"#");
            y1--;
        }
        if (x1 != x2){
        if (x1 <x2){
        while(x1!= x2+1){
            mvprintw(y1,x1,"#");
            x1++;
        }}
        else if (x1 > x2)
        {
            while(x1!= x2-1){
            mvprintw(y1,x1,"#");
            x1--;
        }
        }  
        }
        else if (x1==x2) {
            mvprintw(y1,x1, "#");
        }
        mvprintw(y2,x2,"#");
        }
        //left to right
        if (firstroom==3 && secondroom ==4) {
        int x1=rooms[3]->doorpositionx[0]+1;
        int y1 = rooms[3]->doorpositiony[0];
        int x2 = rooms[4]->doorpositionx[0];
        int y2= rooms[4]->doorpositiony[0];
        while(x1 != x2-1){
            mvprintw(y1,x1,"#");
            x1++;
        }
        if (y1 != y2){
        if (y1 <y2){
        while(y1!= y2+1){
            mvprintw(y1,x1,"#");
            y1++;
        }}
        else if (y1 > y2)
        {
            while(y1!= y2-1){
            mvprintw(y1,x1,"#");
            y1--;
        }
        }  
        }
         else if (y1==y2){
                        mvprintw(y1,x1,"#");

        }
        
            
        
         mvprintw(y2,x2, "#");
        }
        //right to left
        if (firstroom==4 && secondroom ==3) {
        int x1=rooms[4]->doorpositionx[0]-1;
        int y1 = rooms[4]->doorpositiony[0];
        int x2 = rooms[3]->doorpositionx[0];
        int y2= rooms[3]->doorpositiony[0];
        while(x1 != x2+1){
            mvprintw(y1,x1,"#");
            x1--;
        }
        if (y1 != y2){
        if (y1 <y2){
        while(y1!= y2+1){
            mvprintw(y1,x1,"#");
            y1++;
        }}
        else if (y1 > y2)
        {
            while(y1!= y2-1){
            mvprintw(y1,x1,"#");
            y1--;
        }
        }  
        }
        else if (y1==y2) {
            mvprintw(y1,x1, "#");
        }
            
        
         mvprintw(y2,x2, "#");
        }
        //left to right
        if (firstroom==4 && secondroom ==5) {
        int x1=rooms[4]->doorpositionx[2]+1;
        int y1 = rooms[4]->doorpositiony[2];
        int x2 = rooms[5]->doorpositionx[0];
        int y2= rooms[5]->doorpositiony[0];
        while(x1 != x2-1){
            mvprintw(y1,x1,"#");
            x1++;
        }
        if (y1 != y2){
        if (y1 <y2){
        while(y1!= y2+1){
            mvprintw(y1,x1,"#");
            y1++;
        }}
        else if (y1 > y2)
        {
            while(y1!= y2-1){
            mvprintw(y1,x1,"#");
            y1--;
        }
        }  
        
        
        }
        else if (y1==y2){
        mvprintw(y1,x1,"#");

        }
        mvprintw(y2,x2,"#");

        }
        //right to left
        if (firstroom==5 && secondroom ==4) {
        int x1=rooms[5]->doorpositionx[0]-1;
        int y1 = rooms[5]->doorpositiony[0];
        int x2 = rooms[4]->doorpositionx[2];
        int y2= rooms[4]->doorpositiony[2];
        while(x1 != x2+1){
            mvprintw(y1,x1,"#");
            x1--;
        }
        if (y1 != y2){
        if (y1 <y2){
        while(y1!= y2+1){
            mvprintw(y1,x1,"#");
            y1++;
        }}
        else if (y1 > y2)
        {
            while(y1!= y2-1){
            mvprintw(y1,x1,"#");
            y1--;
        }
        }  
        }
        else if (y1==y2) {
            mvprintw(y1,x1, "#");
        }
            
        
         mvprintw(y2,x2, "#");
        }
        
            
        
        

if (numrooms==7 || numrooms==8){

            //up tp down
        if (firstroom==3 && secondroom==6){
            int x1=rooms[3]->doorpositionx[1];
         int y1 = rooms[3]->doorpositiony[1]+1;
         int x2 = rooms[6]->doorpositionx[1];
        int y2= rooms[6]->doorpositiony[1];
          while(y1 != y2-1){
            mvprintw(y1,x1,"#");
            y1++;
        }
        if (x1 != x2){
        if (x1 <x2){
        while(x1!= x2+1){
            mvprintw(y1,x1,"#");
            x1++;
        }}
        else if (x1 > x2)
        {
            while(x1!= x2-1){
            mvprintw(y1,x1,"#");
            x1--;
        }
        }  
        }
        else if (x1==x2) {
            mvprintw(y1,x1, "#");
        }
        mvprintw(y2,x2,"#");
        }
        
        //down to up
         if (firstroom==6 && secondroom==3){
            int x1=rooms[6]->doorpositionx[1];
         int y1 = rooms[6]->doorpositiony[1]-1;
         int x2 = rooms[3]->doorpositionx[1];
        int y2= rooms[3]->doorpositiony[1];
          while(y1 != y2+1){
            mvprintw(y1,x1,"#");
            y1--;
        }
        if (x1 != x2){
        if (x1 <x2){
        while(x1!= x2+1){
            mvprintw(y1,x1,"#");
            x1++;
        }}
        else if (x1 > x2)
        {
            while(x1!= x2-1){
            mvprintw(y1,x1,"#");
            x1--;
        }
        }  
        }
        else if (x1==x2) {
            mvprintw(y1,x1, "#");
        }
        mvprintw(y2,x2,"#");
        
        }
        if (numrooms==8){
            //left to right
        if (firstroom==6 && secondroom ==7) {
        int x1=rooms[6]->doorpositionx[0]+1;
        int y1 = rooms[6]->doorpositiony[0];
        int x2 = rooms[7]->doorpositionx[0];
        int y2= rooms[7]->doorpositiony[0];
        while(x1 != x2-1){
            mvprintw(y1,x1,"#");
            x1++;
        }
        if (y1 != y2){
        if (y1 <y2){
        while(y1!= y2+1){
            mvprintw(y1,x1,"#");
            y1++;
        }}
        else if (y1 > y2)
        {
            while(y1!= y2-1){
            mvprintw(y1,x1,"#");
            y1--;
        }
        }  
        
        }
        else if (y1 == y1){
                        mvprintw(y1,x1, "#");

        }
        mvprintw(y2,x2,"#");

        }
        //right to left
        if (firstroom==7 && secondroom ==6) {
        int x1=rooms[7]->doorpositionx[0]-1;
        int y1 = rooms[7]->doorpositiony[0];
        int x2 = rooms[6]->doorpositionx[0];
        int y2= rooms[6]->doorpositiony[0];
        while(x1 != x2+1){
            mvprintw(y1,x1,"#");
            x1--;
        }
        if (y1 != y2){
        if (y1 <y2){
        while(y1!= y2+1){
            mvprintw(y1,x1,"#");
            y1++;
        }}
        else if (y1 > y2)
        {
            while(y1!= y2-1){
            mvprintw(y1,x1,"#");
            y1--;
        }
        }  
        }
        else if (y1==y2) {
            mvprintw(y1,x1, "#");
        }
            
        
         mvprintw(y2,x2, "#");
        }

        }
        }




    }
}

    

void show_attributes(Room* rooms[]) {
    
    mvprintw(50, 15, "Health: %.1f/%.1f", health,maxhealth);  // نمایش سلامت
    mvprintw(51, 15, "Hunger: %.1f", hunger);  // نمایش گرسنگی
    mvprintw(50 , 50 , "Gold: %.1f", goldcount);
}


    

        
          //برای بقیه رو هم بزن دمت گرم
    

void handleinput(adventurer player1, Room *rooms[], int firstplacen, int numrooms, int whichway,int stairroom){
    int ch;
    int ch2;

    while(health>=0){
       
        ch = getch();

        int newx= playerx;
        int newy = playery;
        if (ch == 'l' || ch == 'L') {
            newx++;
            if (hunger<250){
                hunger++;
                hungermessage=false;
                beforehunger++;
                if(beforehunger>=20){
                    beforehunger=0;
                    if(health <12){
                        health++;

                    }
                    else{
                        health=12;
                    }

                }
            }
            else if (hunger>=250){
   hunger=250;     
   beforehunger=0;
   if(!hungermessage ){    
                   show_temporary_message(0,0,"Warning! You have riched the hunger limit");
                                                      hungermessage=true;

                   }

    if (afterhunger< 40){
                    afterhunger++;
                }
                else if (afterhunger==40){
                    afterhunger=0;
                    health--;

                }
                
            }
        }
        else if (ch == 'h' || ch == 'H') {newx--;
        
        if (hunger<250){
                hunger++;                hungermessage=false;
                beforehunger++;
                if(beforehunger>=20){
                    beforehunger=0;
                    if(health <12){
                        health++;

                    }
                    else{
                        health=12;
                    }

                }

            }
            else if (hunger>=250){
                hunger=250;
                   beforehunger=0;

if(!hungermessage){    
                   show_temporary_message(0,0,"Warning! You have riched the hunger limit");
                   hungermessage=true;}
                if (afterhunger< 40){
                    afterhunger++;
                }
                else if (afterhunger==40){
                    afterhunger=0;
                    health--;

                }
                
            }
        }
        else if (ch == 'k' || ch == 'K') {newy++;if (hunger<250){
                hunger++;                hungermessage=false;
                beforehunger++;
                if(beforehunger>=20){
                    beforehunger=0;
                    if(health <12){
                        health++;

                    }
                    else{
                        health=12;
                    }

                }

            }
            else if (hunger>=250){
                hunger=250;
                   beforehunger=0;


if(!hungermessage){    
                   show_temporary_message(0,0,"Warning! You have riched the hunger limit");
                   hungermessage=true;}                if (afterhunger< 40){
                    afterhunger++;
                }
                else if (afterhunger==40){
                    afterhunger=0;
                    health--;

                }
                
            }}
        else if (ch == 'j' || ch == 'J') {newy--;if (hunger<250){
                hunger++;
                                hungermessage=false;
                                beforehunger++;
                if(beforehunger>=20){
                    beforehunger=0;
                    if(health <12){
                        health++;

                    }
                    else{
                        health=12;
                    }

                }

            }
            else if (hunger>=250){
                hunger=250;
                   beforehunger=0;

if(!hungermessage){    
                   show_temporary_message(0,0,"Warning! You have riched the hunger limit");
                   hungermessage=true;}
                if (afterhunger< 40){
                    afterhunger++;
                }
                else if (afterhunger==40){
                    afterhunger=0;
                    health--;

                }
                
            }}
        else if (ch =='y'|| ch == 'Y') {newx--; newy--;if (hunger<250){
                hunger+=2;                hungermessage=false;
                beforehunger++;
                if(beforehunger>=20){
                    beforehunger=0;
                    if(health <12){
                        health++;

                    }
                    else{
                        health=12;
                    }

                }

            }
            else if (hunger>=250){
                hunger=250;
                   beforehunger=0;

if(!hungermessage){    
                   show_temporary_message(0,0,"Warning! You have riched the hunger limit");
                   hungermessage=true;}
                if (afterhunger< 40){
                    afterhunger++;
                }
                else if (afterhunger==40){
                    afterhunger=0;
                    health--;

                }
                
            }}
        else if(ch == 'u' || ch == 'U') {newy--; newx++;if (hunger<250){
                hunger+=2;                hungermessage=false;
                beforehunger++;
                if(beforehunger>=20){
                    beforehunger=0;
                    if(health <12){
                        health++;

                    }
                    else{
                        health=12;
                    }

                }

            }
            else if (hunger>=250){
                hunger=250;
                   beforehunger=0;

                  if(!hungermessage){    
                   show_temporary_message(0,0,"Warning! You have riched the hunger limit");
                   hungermessage=true;}
                if (afterhunger< 40){
                    afterhunger++;
                }
                else if (afterhunger==40){
                    afterhunger=0;
                    health--;

                }
                
            }}
        else if (ch == 'b'||ch == 'B') {newy++; newx--;if (hunger<250){
                hunger+=2;                hungermessage=false;
                beforehunger++;
                if(beforehunger>=20){
                    beforehunger=0;
                    if(health <12){
                        health++;

                    }
                    else{
                        health=12;
                    }

                }

            }
            else if (hunger>=250){
                hunger=250;
                   beforehunger=0;

if(!hungermessage){    
                   show_temporary_message(0,0,"Warning! You have riched the hunger limit");
                   hungermessage=true;}
                if (afterhunger< 40){
                    afterhunger++;
                }
                else if (afterhunger==40){
                    afterhunger=0;
                    health--;

                }
                
            }}
        else if (ch == 'n'||ch == 'N'){newy ++; newx++;if (hunger<250){
                hunger+=2;                hungermessage=false;
                beforehunger++;
                if(beforehunger>=20){
                    beforehunger=0;
                    if(health <12){
                        health++;

                    }
                    else{
                        health=12;
                    }

                }

            }
            else if (hunger>=250){
                hunger=250;
                   beforehunger=0;

if(!hungermessage){    
                   show_temporary_message(0,0,"Warning! You have riched the hunger limit");
                   hungermessage=true;}
                if (afterhunger< 40){
                    afterhunger++;
                }
                else if (afterhunger==40){
                    afterhunger=0;
                    health--;

                }
                
            }}
        else if (ch == 'f'|| ch == 'F'){
            ch2 = getch();
            if (ch2 == 'h' || ch2 == 'H'){
                char nextone = mvinch(newy, newx-1) & A_CHARTEXT;

                do{newx--;
                    nextone = mvinch(newy, newx-2) & A_CHARTEXT;}
                 while( nextone == '.' ||  nextone == '#'||  nextone == '+');
                 newx--;
                 if (hunger<250){
                hunger+=4;                hungermessage=false;
                beforehunger++;
                if(beforehunger>=20){
                    beforehunger=0;
                    if(health <12){
                        health++;

                    }
                    else{
                        health=12;
                    }

                }

            }
            else if (hunger>=250){
                hunger=250;
                   beforehunger=0;

if(!hungermessage){    
                   show_temporary_message(0,0,"Warning! You have riched the hunger limit");
                   hungermessage=true;}
                if (afterhunger< 40){
                    afterhunger++;
                }
                else if (afterhunger==40){
                    afterhunger=0;
                    health--;

                }
                
            }
                 
            }
            else if (ch2 == 'l' || ch2 == 'L'){
                char nextone = mvinch(newy, newx+1) & A_CHARTEXT;

                do{newx++;
                    nextone = mvinch(newy, newx+2) & A_CHARTEXT;}
                 while( nextone == '.' ||  nextone == '#'||  nextone == '+');
                 newx++;
                 if (hunger<250){
                hunger+=4;                hungermessage=false;
                beforehunger++;
                if(beforehunger>=20){
                    beforehunger=0;
                    if(health <12){
                        health++;

                    }
                    else{
                        health=12;
                    }

                }

            }
            else if (hunger>=250){
                hunger=250;
                   beforehunger=0;

if(!hungermessage){    
                   show_temporary_message(0,0,"Warning! You have riched the hunger limit");
                   hungermessage=true;}
                if (afterhunger< 40){
                    afterhunger++;
                }
                else if (afterhunger==40){
                    afterhunger=0;
                    health--;

                }
                
            }
            }
            else if (ch2 == 'k' || ch2 == 'K'){
                char nextone = mvinch(newy+1, newx) & A_CHARTEXT;

                do{newy++;
                    nextone = mvinch(newy+2, newx) & A_CHARTEXT;}
                 while( nextone == '.' ||  nextone == '#'||  nextone == '+');
                 newy++;
                 if (hunger<250){
                hunger+=4;                hungermessage=false;
                beforehunger++;
                if(beforehunger>=20){
                    beforehunger=0;
                    if(health <12){
                        health++;

                    }
                    else{
                        health=12;
                    }

                }

            }
            else if (hunger>=250){
                hunger=250;
                   beforehunger=0;

if(!hungermessage){    
                   show_temporary_message(0,0,"Warning! You have riched the hunger limit");
                   hungermessage=true;}
                if (afterhunger< 40){
                    afterhunger++;
                }
                else if (afterhunger==40){
                    afterhunger=0;
                    health--;

                }
                
            }
            }
            else if (ch2 == 'j' || ch2 == 'J'){
                char nextone = mvinch(newy-1, newx) & A_CHARTEXT;

                do{newy--;
                    nextone = mvinch(newy-2, newx) & A_CHARTEXT;}
                 while( nextone == '.' ||  nextone == '#'||  nextone == '+');
                 newy--;
                 if (hunger<250){
                hunger+=4;                hungermessage=false;
                beforehunger++;
                if(beforehunger>=20){
                    beforehunger=0;
                    if(health <12){
                        health++;

                    }
                    else{
                        health=12;
                    }

                }

                
            }
            else if (hunger>=250){
                hunger=250;
                   beforehunger=0;

                if(!hungermessage){    
                   show_temporary_message(0,0,"Warning! You have riched the hunger limit");
                   hungermessage=true;
                   }
                if (afterhunger< 40){
                    afterhunger++;
                }
                else if (afterhunger==40){
                    afterhunger=0;
                    health--;

                }
                
            }
            }


        }
        else if (ch=='e'||ch=='E'){
            foodmenu(rooms,whichway,numrooms);
        }
        else if (ch=='m' || ch =='M'){
            showmap(rooms, whichway, numrooms);
        }
        


        
        
        
        
        
        char nextChar = mvinch(newy, newx) & A_CHARTEXT;
        if (nextChar == '.'){
            mvprintw(playery, playerx, ".");
            playerx = newx;
            playery=newy;
            mvprintw(playery,playerx,"@");

        }
        
       else if (nextChar == '+'){
            bool inroom = false;
           
            for(int i = 0; i < numrooms;i++){
                if (playerx > rooms[i]->positionx &&  playerx < rooms[i]->positionx + rooms[i]->width && playery > rooms[i]->positiony && playery < rooms[i]->positiony + rooms[i]->height ){
                    inroom = true;
                    break;
                }
            }

            if(inroom){
                mvprintw(playery,playerx, ".");
            }
            else{
                mvprintw(playery,playerx, "#");
            }
            playerx = newx;
            playery=newy;
            mvprintw(playery,playerx,"@");
            if (whichway ==1){
                if(playerx == rooms[0]->doorpositionx[0]&& playery == rooms[0]->doorpositiony[0]) {
                    if (!coridordrawn1[floornumber][0]){
                        connectrooms(rooms, numrooms,whichway, 0, 1);
                        coridordrawn1[floornumber][0]=true;
                        coridor1[floornumber][0]=true;
                    }
                }
               else if(playerx == rooms[1]->doorpositionx[0]&& playery == rooms[1]->doorpositiony[0]) {
                    if (!coridordrawn1[floornumber][0]){
                        connectrooms(rooms, numrooms,whichway, 1, 0);
                        coridordrawn1[floornumber][0]=true;
                        coridor1[floornumber][1]=true;
                    }
                }
                else if(playerx == rooms[1]->doorpositionx[1]&& playery == rooms[1]->doorpositiony[1]) {
                    if (!coridordrawn1[floornumber][1]){
                        connectrooms(rooms, numrooms,whichway, 1,2 );
                        coridordrawn1[floornumber][1]=true;
                        coridor1[floornumber][2]=true;
                    }
                }
                 else if(playerx == rooms[2]->doorpositionx[0]&& playery == rooms[2]->doorpositiony[0]) {
                    if (!coridordrawn1[floornumber][1]){
                        connectrooms(rooms, numrooms,whichway, 2,1 );
                        coridordrawn1[floornumber][1]=true;
                        coridor1[floornumber][3]=true;

                    }
                }
                else if(playerx == rooms[1]->doorpositionx[2]&& playery == rooms[1]->doorpositiony[2]) {
                    if (!coridordrawn1[floornumber][2]){
                        connectrooms(rooms, numrooms,whichway, 2,4 );
                        coridordrawn1[floornumber][2]=true;
                        coridor1[floornumber][4]=true;
                    }
                }
                else if(playerx == rooms[4]->doorpositionx[1]&& playery == rooms[4]->doorpositiony[1]) {
                    if (!coridordrawn1[floornumber][2]){
                        connectrooms(rooms, numrooms,whichway, 4,2 );
                        coridordrawn1[floornumber][2]=true;
                        coridor1[floornumber][5]=true;

                    }
                }
                else if(playerx == rooms[2]->doorpositionx[1]&& playery == rooms[2]->doorpositiony[1]) {
                    if (!coridordrawn1[floornumber][3]){
                        connectrooms(rooms, numrooms,whichway, 2,5 );
                        coridordrawn1[floornumber][3]=true;
                        coridor1[floornumber][6]=true;
                    }
                }
                else if(playerx == rooms[5]->doorpositionx[1]&& playery == rooms[5]->doorpositiony[1]) {
                    if (!coridordrawn1[floornumber][3]){
                        connectrooms(rooms, numrooms,whichway, 5,2 );
                        coridordrawn1[floornumber][3]=true;
                        coridor1[floornumber][7]=true;
                    }
                }
                else if(playerx == rooms[3]->doorpositionx[0]&& playery == rooms[3]->doorpositiony[0]) {
                    if (!coridordrawn1[floornumber][4]){
                        connectrooms(rooms, numrooms,whichway, 3,4 );
                        coridordrawn1[floornumber][4]=true;
                        coridor1[floornumber][8]=true;
                    }
                }
                else if(playerx == rooms[4]->doorpositionx[0]&& playery == rooms[4]->doorpositiony[0]) {
                    if (!coridordrawn1[floornumber][4]){
                        connectrooms(rooms, numrooms,whichway, 4,3 );
                        coridordrawn1[floornumber][4]=true;
                        coridor1[floornumber][9]=true;
                    }
                }
                else if(playerx == rooms[4]->doorpositionx[2]&& playery == rooms[4]->doorpositiony[2]) {
                    if (!coridordrawn1[floornumber][5]){
                        connectrooms(rooms, numrooms,whichway, 4,5 );
                        coridordrawn1[floornumber][5]=true;
                        coridor1[floornumber][10]=true;
                    }
                }
                else if(playerx == rooms[5]->doorpositionx[0]&& playery == rooms[5]->doorpositiony[0]) {
                    if (!coridordrawn1[floornumber][5]){
                        connectrooms(rooms, numrooms,whichway, 5,4 );
                        coridordrawn1[floornumber][5]=true;
                        coridor1[floornumber][11]=true;
                    }
                }
                else if(playerx == rooms[3]->doorpositionx[1]&& playery == rooms[3]->doorpositiony[1]) {
                    if (!coridordrawn1[floornumber][6]){
                        connectrooms(rooms, numrooms,whichway, 3,6 );
                        coridordrawn1[floornumber][6]=true;
                        coridor1[floornumber][12]=true;
                    }
                }
                else if(playerx == rooms[6]->doorpositionx[1]&& playery == rooms[6]->doorpositiony[1]) {
                    if (!coridordrawn1[floornumber][6]){
                        connectrooms(rooms, numrooms,whichway, 6,3 );
                        coridordrawn1[floornumber][6]=true;
                        coridor1[floornumber][13]=true;
                    }
                }
                else if(playerx == rooms[6]->doorpositionx[0]&& playery == rooms[6]->doorpositiony[0]) {
                    if (!coridordrawn1[floornumber][7]){
                        connectrooms(rooms, numrooms,whichway, 6,7 );
                        coridordrawn1[floornumber][7]=true;
                        coridor1[floornumber][14]=true;
                    }
                }
                else if(playerx == rooms[7]->doorpositionx[0]&& playery == rooms[7]->doorpositiony[0]) {
                    if (!coridordrawn1[floornumber][7]){
                        connectrooms(rooms, numrooms,whichway, 7,6 );
                        coridordrawn1[floornumber][7]=true;
                        coridor1[floornumber][15]=true;
                    }
                }



                
                
                
            
            }
            else if (whichway == 0){
                 if(playerx == rooms[0]->doorpositionx[0]&& playery == rooms[0]->doorpositiony[0]) {
                    if (!corridordrawn2[floornumber][0]){
                        connectrooms(rooms, numrooms,whichway, 0, 3);
                        corridordrawn2[floornumber][0]=true;
                        coridor2[floornumber][0]=true;
                    }
                }
                else if(playerx == rooms[3]->doorpositionx[0]&& playery == rooms[3]->doorpositiony[0]) {
                    if (!corridordrawn2[floornumber][0]){
                        connectrooms(rooms, numrooms,whichway, 3, 0);
                        corridordrawn2[floornumber][0]=true;
                        coridor2[floornumber][1]=true;
                    }
                }
                else if(playerx == rooms[1]->doorpositionx[0]&& playery == rooms[1]->doorpositiony[0]) {
                    if (!corridordrawn2[floornumber][1]){
                        connectrooms(rooms, numrooms,whichway, 1, 4);
                        corridordrawn2[floornumber][1]=true;
                        coridor2[floornumber][2]=true;
                    }

                }
                else if(playerx == rooms[4]->doorpositionx[1]&& playery == rooms[4]->doorpositiony[1]) {
                    if (!corridordrawn2[floornumber][1]){
                        connectrooms(rooms, numrooms,whichway, 4, 1);
                        corridordrawn2[floornumber][1]=true;
                        coridor2[floornumber][3]=true;
                    }

                }
                else if(playerx == rooms[1]->doorpositionx[1]&& playery == rooms[1]->doorpositiony[1]) {
                    if (!corridordrawn2[floornumber][2]){
                        connectrooms(rooms, numrooms,whichway, 1, 2);
                        corridordrawn2[floornumber][2]=true;
                        coridor2[floornumber][4]=true;
                    }

                }
                else if(playerx == rooms[2]->doorpositionx[0]&& playery == rooms[2]->doorpositiony[0]) {
                    if (!corridordrawn2[floornumber][2]){
                        connectrooms(rooms, numrooms,whichway, 2, 1);
                        corridordrawn2[floornumber][2]=true;
                        coridor2[floornumber][5]=true;
                    }


                }
                else if(playerx == rooms[3]->doorpositionx[1]&& playery == rooms[3]->doorpositiony[1]) {
                    if (!corridordrawn2[floornumber][3]){
                        connectrooms(rooms, numrooms,whichway, 3, 4);
                        corridordrawn2[floornumber][3]=true;
                        coridor2[floornumber][6]=true;
                    }


                }
                else if(playerx == rooms[4]->doorpositionx[0]&& playery == rooms[4]->doorpositiony[0]) {
                    if (!corridordrawn2[floornumber][3]){
                        connectrooms(rooms, numrooms,whichway, 4, 3);
                        corridordrawn2[floornumber][3]=true;
                        coridor2[floornumber][7]=true;
                    }


                }
                 else if(playerx == rooms[4]->doorpositionx[2]&& playery == rooms[4]->doorpositiony[2]) {
                    if (!corridordrawn2[floornumber][4]){
                        connectrooms(rooms, numrooms,whichway, 4, 5);
                        corridordrawn2[floornumber][4]=true;
                        coridor2[floornumber][8]=true;
                    }


                }
                 else if(playerx == rooms[5]->doorpositionx[0]&& playery == rooms[5]->doorpositiony[0]) {
                    if (!corridordrawn2[floornumber][4]){
                        connectrooms(rooms, numrooms,whichway, 5, 4);
                        corridordrawn2[floornumber][4]=true;
                        coridor2[floornumber][9]=true;
                    }


                }
                else if(playerx == rooms[3]->doorpositionx[2]&& playery == rooms[3]->doorpositiony[2]) {
                    if (!corridordrawn2[floornumber][5]){
                        connectrooms(rooms, numrooms,whichway, 3, 6);
                        corridordrawn2[floornumber][5]=true;
                        coridor2[floornumber][10]=true;
                    }



                }
                else if(playerx == rooms[6]->doorpositionx[0]&& playery == rooms[6]->doorpositiony[0]) {
                    if (!corridordrawn2[floornumber][5]){
                        connectrooms(rooms, numrooms,whichway, 6, 3);
                        corridordrawn2[floornumber][5]=true;
                        coridor2[floornumber][11]=true;
                    }



                }
                else if(playerx == rooms[6]->doorpositionx[1]&& playery == rooms[6]->doorpositiony[1]) {
                    if (!corridordrawn2[floornumber][6]){
                        connectrooms(rooms, numrooms,whichway, 6, 7);
                        corridordrawn2[floornumber][6]=true;
                        coridor2[floornumber][12]=true;
                    }



                }
                else if(playerx == rooms[7]->doorpositionx[0]&& playery == rooms[7]->doorpositiony[0]) {
                    if (!corridordrawn2[floornumber][6]){
                        connectrooms(rooms, numrooms,whichway, 7, 6);
                        corridordrawn2[floornumber][6]=true;
                        coridor2[floornumber][13]=true;
                    }



                }



                
                
                

                


                
                
                
            }
            

        }

       else if (nextChar == '#'){
        bool inroom = false;
         for(int i = 0; i < numrooms;i++){
                if (playerx > rooms[i]->positionx &&  playerx < rooms[i]->positionx + rooms[i]->width && playery > rooms[i]->positiony && playery < rooms[i]->positiony + rooms[i]->height ){
                    inroom = true;
                    break;
                }
            }if (!inroom)
            mvprintw(playery, playerx, "#");
            else {
                            mvprintw(playery, playerx, ".");

            }
            playerx = newx;
            playery=newy;
            mvprintw(playery,playerx,"@");

        }
        else if (nextChar=='F'){
        mvprintw(playery, playerx, ".");
         playerx = newx;
            playery=newy;
            mvprintw(playery,playerx,"@");
            foodscollected++;
            show_temporary_message(1,1,"You have collected 1 normal food");
            for (int i =0 ; i< numrooms;i++){
                for (int j=0 ; j<rooms[i]->foodcount;j++){
                    if(playerx == rooms[i]->foods[j].positionx && playery == rooms[i]->foods[j].positiony){
                        rooms[i]->foodcount--;
                        rooms[i]->foods[j].collected=true;
                    }
                }
            }

        }
        else if(nextChar=='G'){
             mvprintw(playery, playerx, ".");
         playerx = newx;   
            playery=newy;
            mvprintw(playery,playerx,"@");
            int ch4;
    
             goldsobtaind=rand()%50 + 10;
            goldcount+= goldsobtaind;
            
            
           show_temporary_message(1,1 , "You have obtaind Gold");

            for (int i =0 ; i< numrooms;i++){
                for (int j=0 ; j<rooms[i]->goldcount;j++){
                    if(playerx == rooms[i]->golds[j].positionx && playery == rooms[i]->golds[j].positiony){
                        rooms[i]->goldcount;
                        rooms[i]->golds[j].collected=true;
                    }
                }
            }

        }
         else if(nextChar=='B'){
             mvprintw(playery, playerx, ".");
         playerx = newx;   
            playery=newy;
            mvprintw(playery,playerx,"@");
    
             goldsobtaind=rand()%80 + 30;
            goldcount+= goldsobtaind;
            
            
           show_temporary_message(1,1 , "You have obtaind BlackGold");

            for (int i =0 ; i< numrooms;i++){
                for (int j=0 ; j<rooms[i]->blackgoldcount;j++){
                    if(playerx == rooms[i]->blackgolds[j].positionx && playery == rooms[i]->blackgolds[j].positiony){
                        rooms[i]->blackgoldcount;
                        rooms[i]->blackgolds[j].collected=true;
                    }
                }
            }

        }
    else if (nextChar=='T'){
        clear();
        mvprintw(30, 75, "Congrajulations! You have won");
                mvprintw(32, 75, "Your total score was %.1f", goldcount);
                
                mvprintw(33, 75, "press space to return to menu");
                int ch10;
                do {
                    ch10 = getch();


                }
                while(ch != ' ');
                menu();

    }
       if (whichway==1){ 
        for (int i =0 ;i < numrooms; i++)
        {
            for (int j =0 ; j< doornumber[i]; j++){
                char doorchar = mvinch (rooms[i]->doorpositiony[j], rooms[i]->doorpositionx[j]) & A_CHARTEXT;
                if (doorchar != '@' && wasinroom[floornumber][i]){
                    mvprintw(rooms[i]->doorpositiony[j], rooms[i]->doorpositionx[j], "+");
                }
                
            }
        }
       }
       else if(whichway==0){
        for (int i =0 ;i < numrooms; i++)
        {
            for (int j =0 ; j< doornumber2[i]; j++){
                char doorchar = mvinch (rooms[i]->doorpositiony[j], rooms[i]->doorpositionx[j]) & A_CHARTEXT;
                if (doorchar != '@' && wasinroom[floornumber][i]){
                    mvprintw(rooms[i]->doorpositiony[j], rooms[i]->doorpositionx[j], "+");
                }
                
            }
        }
       }
        
        
        for (int i =0;i < numrooms;i++){
            for (int j = 0; j < rooms[i]->foodcount;j++){
                char foodchar= mvinch(rooms[i]->foods[j].positiony,rooms[i]->foods[j].positionx ) & A_CHARTEXT;
                if (foodchar !='@' && wasinroom[floornumber][i]&& !rooms[i]->foods[j].collected){
                    mvprintw(rooms[i]->foods[j].positiony,rooms[i]->foods[j].positionx, "F");
                }
            }
        }
         for (int i =0;i < numrooms;i++){
            for (int j = 0; j < rooms[i]->goldcount;j++){
                char goldchar= mvinch(rooms[i]->golds[j].positiony,rooms[i]->golds[j].positionx ) & A_CHARTEXT;
                if (goldchar !='@' && wasinroom[floornumber][i]&& !rooms[i]->golds[j].collected){
                    mvprintw(rooms[i]->golds[j].positiony,rooms[i]->golds[j].positionx, "G");
                }
            }
        }
        for (int i =0;i < numrooms;i++){
            for (int j = 0; j < rooms[i]->blackgoldcount;j++){
                char blackgoldchar= mvinch(rooms[i]->blackgolds[j].positiony,rooms[i]->blackgolds[j].positionx ) & A_CHARTEXT;
                if (blackgoldchar !='@' && wasinroom[floornumber][i]&& !rooms[i]->blackgolds[j].collected){
                    mvprintw(rooms[i]->blackgolds[j].positiony,rooms[i]->blackgolds[j].positionx, "B");
                }
            }
        }

        /* for (int i =0;i < numrooms;i++){
            for (int j = 0; j < rooms[i]->pillarcount;j++){
                if ( wasinroom[floornumber][i]){
                    mvprintw(rooms[i]->pillars[j].positiony,rooms[i]->pillars[j].positionx, "O");
                }
            }
        }*/
        
                char stairchar = mvinch (rooms[stairroom]->stairpositiony, rooms[stairroom]->stairpositionx) & A_CHARTEXT;
                if (stairchar != '@' && wasinroom[floornumber][stairroom] && floornumber<3){
                    mvprintw(rooms[stairroom]->stairpositiony, rooms[stairroom]->stairpositionx, "<");
                }
                
            

         for(int i = 0; i < numrooms;i++){
                if (playerx >= rooms[i]->positionx &&  playerx < rooms[i]->positionx + rooms[i]->width && playery >= rooms[i]->positiony && playery <= rooms[i]->positiony + rooms[i]->height ){
                    wasinroom[floornumber][i] = true;
                }
                if (wasinroom[floornumber][i] && !roomdrawn[floornumber][i]){
                    drawroom(rooms[i],whichway, i);
                    roomdrawn[floornumber][i]= true;
                }
            }
             if ( newx==rooms[stairroom]->stairpositionx && newy == rooms[stairroom]->stairpositiony){
            clear();
            floornumber++;
            startnewgame();
        }
        show_attributes(rooms);
        if (health ==0){
            clear();
            mvprintw(28, 70, "Game Over press Space to return to menu");
            int ch5;
            do {
                ch5= getch();
            }
            while (ch5 != ' ');
            menu();
            
            
        }
        int ganjroom;
        if(floornumber==3){
        do {
            ganjroom= rand()%numrooms;
        }
        while (ganjroom==firstplace);
        }
        if ( wasinroom[3][ganjroom]){
            int ganjpositionx = rooms[ganjroom]->positionx+(rooms[ganjroom]->width)/2;
                        int ganjpositiony = rooms[ganjroom]->positiony+(rooms[ganjroom]->height)/2;
            mvprintw(ganjpositiony, ganjpositionx, "T");
        }
        
        break;
        
    }
}
typedef struct {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
    char email[MAX_EMAIL_LEN];
} player;

player players[MAX_players];
int player_count = 0;
bool validate_email(const char *email){
    const char *at = strchr (email, '@');
    const char *dot = strchr (email, '.');
    return at && dot && at < dot;
}

int check_user_credentials(const char *username, const char *password) {
    FILE *file = fopen("players.txt", "r");
    if (file == NULL) {
        return -1;
    }

    char line[150];
    int username_found = 0;

    while (fgets(line, sizeof(line), file)) {
        
        char *file_username = strtok(line, ",");
        char *file_password = strtok(NULL, ",");
        char *file_email = strtok(NULL, ",");

        if (file_username && strcmp(username, file_username) == 0) {
            username_found = 1; 

            if (file_password && strcmp(password, file_password) == 0) {
                fclose(file);
                return 1; 
            }
        }
    }

    fclose(file);
    return username_found ? 0 : -1;
}
bool validate_password(const char *password){
    if (strlen(password)< 7)
        return false;
        bool digit = false , upper = false , lower = false;
        for (int i =0 ; i < strlen (password); i++)
        {
            if (isdigit(password[i])) digit = true;
            if (isupper(password[i])) upper = true;
            if (islower(password[i])) lower = true;
        }
        return upper && lower && digit;
}

bool username_exists(const char *username){
    FILE *file = fopen("players.txt", "r");
    if (file == NULL) {
        return 0; 
    }

    char line[150];
    while (fgets(line, sizeof(line), file)) {
        
        char *saved_username = strtok(line, ",");
        if (saved_username != NULL && strcmp(saved_username, username) == 0) {
            fclose(file);
            return 1; 
        }
    }

    fclose(file);
    return 0; 
}
void saveplayer (){
    FILE *file = fopen ("players.txt", "r");
    if (file) {
        fwrite (&player_count , sizeof(int), 1, file);
        fwrite(players , sizeof (player), player_count, file);
        fclose (file);
    }
}

void createnewuser ()

{
    clear();
    refresh();
    player new_user;
    clear();
    mvprintw(12, 80, "Enter username: ");
    echo();
    getstr(new_user.username);
    noecho();

    if (username_exists(new_user.username)) {
        mvprintw(14, 80, "Username already taken! Press anything to return to menu");
        getch();
        menu();
        return;  
    }

   
    int valid_password = 0;
         mvprintw(16, 80, "Enter password : ");
        echo();
        getstr(new_user.password);
        noecho();
         

        if (validate_password(new_user.password)) {
            valid_password = 1; 
        } else {
            mvprintw(18, 80, "Invalid password! press anything to return to menu");
            getch();
            menu();
            clrtoeol();
        }
    

    int valid_email = 0;
    
        mvprintw(20, 80, "Enter email: ");
        echo();
        getstr(new_user.email);
        noecho();

        if (validate_email(new_user.email)) {
            valid_email = 1; 
        } else {
            mvprintw(22, 80, "Invalid email format! press anything to return to menu");
            getch();
            menu();
            clrtoeol(); 
        }
    

    FILE *file = fopen("players.txt", "a");
    if (file == NULL) {
        mvprintw(10, 80, "Error opening file for saving user.");
        getch();
        return;
    }
    fprintf(file, "%s,%s,%s\n", new_user.username, new_user.password, new_user.email);
    fclose(file);

    mvprintw(24, 80, "User created successfully! Press any key to return to menu.");
    getch();

    clear();  
    refresh();  
}


void loginplayer(){
    clear();
    char username [MAX_USERNAME_LEN]={0};
    char password [MAX_PASSWORD_LEN]= {0};
    int status;
     mvprintw(12, 80, "Enter username ( press 'n' to login as a guest): ");
    echo();
    getstr(username);
    noecho();

    if (strcmp(username, "n") == 0) {
        clear();
        mvprintw(14, 80, "Logged in as Guest. ");
        mvprintw(16, 80, "Press Enter to continue to the main menu.");
        while (getch() != '\n');  
        menu();  
    }

   
    mvprintw(14, 80, "Enter password : ");
    echo();
    getstr(password);
    noecho();
    status = check_user_credentials(username, password);

    if (status == 1) {
        mvprintw(16, 80, "Login successful! Press any key to continue.");
    } else if (status == 0) {
        mvprintw(16, 80, "Incorrect password! Please try again.");
    } else if (status == -1) {
        mvprintw(16, 80, "Username not found! Please register first.");
    }
    


}

void leaderboard (){
    // جدول امتیازات
}
void menu ()
{
    const char *choices[] = {"Create New Player","Login","Leader Board","Pregame Menu","Exit",};
    int num_choices = sizeof(choices) / sizeof(choices[0]);
    int choice = 0; 
    int ch;
    initscr();
    clear();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    while (1){
        clear();
        mvprintw (2, 50, "Main Menu");
        for (int i =0; i < num_choices; i++)
        {
            if (i==choice)
            attron(A_REVERSE);
            mvprintw (4+i, 50, "%s", choices[i]);
            if (i== choice)
            attroff(A_REVERSE);
        }
         ch = getch();
        if (ch == KEY_UP)
            choice = (choice == 0) ? num_choices - 1 : choice - 1;
        else if (ch == KEY_DOWN)
            choice = (choice == num_choices - 1) ? 0 : choice + 1;
        else if (ch == 10)
            break;
    }

        switch (choice){
            case 0:
            createnewuser();
            break;
            case 1:
            loginplayer();
            break;
            case 2:
            leaderboard();
            break;
            case 3:
            pregamemenu();
            break;
            case 4:
            clear();
            mvprintw(5, 50,"Exiting the program. Goodbye!" );
            getch();
            endwin();
            return;
            
        }
        menu();

    

}
int loadsavedgame(){
    clear();
    mvprintw(50,50,"press anything to return");
    getch();
    clear();
    menu();
    // بازی قبلی
}
void music(){
           const char *choices[] = {"Omen","BloodHound","DarkBeast",NULL,"Exit",};
           int num_choices = sizeof(choices) / sizeof(choices[0]);
    int choice = 0; 
    int ch;
    initscr();
    clear();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
     while (1){
        clear();

        mvprintw (2, 50, "Music Setting");
        if (ismusicon){
            choices[3]= "Turn off music";

        }
        else {
            choices[3]="Turn on music";
        }
        for (int i =0; i < num_choices; i++)
        {
            if (i==choice)
            attron(A_REVERSE);
            mvprintw (4+i, 50, "%s", choices[i]);
            if (i== choice)
            attroff(A_REVERSE);
        }
         ch = getch();
        if (ch == KEY_UP)
            choice = (choice == 0) ? num_choices - 1 : choice - 1;
        else if (ch == KEY_DOWN)
            choice = (choice == num_choices - 1) ? 0 : choice + 1;
        else if (ch == 10)
            break;
    }

        switch (choice){
            case 0:
             strcpy(selected_music, "music1.mp3");
                ismusicon = 1; 
            break;
            case 1:
                strcpy(selected_music, "music2.mp3");  
                ismusicon = 1;              break;
            case 2:
strcpy(selected_music, "music3.mp3");  
                ismusicon = 1;            break;
            case 3:
                ismusicon = !ismusicon; 
            break;
            case 4:
           menu();
            break;
            
        }
        menu();


}
int changedifficulty(){const char *choices[] = {"Easy","Medium","Hard","Exit",};
        int num_choices = sizeof(choices) / sizeof(choices[0]);
    int choice = 0; 
    int ch;
    initscr();
    clear();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
     while (1){
        clear();
        mvprintw (2, 50, "Difficulty level");
        for (int i =0; i < num_choices; i++)
        {
            if (i==choice)
            attron(A_REVERSE);
            mvprintw (4+i, 50, "%s", choices[i]);
            if (i== choice)
            attroff(A_REVERSE);
        }
         ch = getch();
        if (ch == KEY_UP)
            choice = (choice == 0) ? num_choices - 1 : choice - 1;
        else if (ch == KEY_DOWN)
            choice = (choice == num_choices - 1) ? 0 : choice + 1;
        else if (ch == 10)
            break;
    }

        switch (choice){
            case 0:
            basefood= 5;
            break;
            case 1:
            basefood= 3;
            break;
            case 2:
            basefood= 1;
            break;
            case 3:
            menu();
            break;
            
            
        }
        menu();



}
int settings(){
       const char *choices[] = {"Change music","Change color","Change Difficulty","Exit",};
        int num_choices = sizeof(choices) / sizeof(choices[0]);
    int choice = 0; 
    int ch;
    initscr();
    clear();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    
     while (1){
        clear();
        mvprintw (2, 50, "Setting");
        for (int i =0; i < num_choices; i++)
        {
            if (i==choice)
            attron(A_REVERSE);
            mvprintw (4+i, 50, "%s", choices[i]);
            if (i== choice)
            attroff(A_REVERSE);
        }
         ch = getch();
        if (ch == KEY_UP)
            choice = (choice == 0) ? num_choices - 1 : choice - 1;
        else if (ch == KEY_DOWN)
            choice = (choice == num_choices - 1) ? 0 : choice + 1;
        else if (ch == 10)
            break;
    }

        switch (choice){
            case 0:
            music();
            break;
            case 1:
            menu();
            break;
            case 2:
            changedifficulty();
            break;
            case 3:
            menu();
            break;
            
            
        }
        menu();

}
int pregamemenu(){

     const char *choices[] = {"Continue","New game","Settings","Main menu",};
    int num_choices = sizeof(choices) / sizeof(choices[0]);
    int choice = 0; 
    int ch;
    initscr();
    clear();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    while (1){
        clear();
        for (int i =0; i < num_choices; i++)
        {
            if (i==choice)
            attron(A_REVERSE);
            mvprintw (4+i, 50, "%s", choices[i]);
            if (i== choice)
            attroff(A_REVERSE);
        }
         ch = getch();
        if (ch == KEY_UP)
            choice = (choice == 0) ? num_choices - 1 : choice - 1;
        else if (ch == KEY_DOWN)
            choice = (choice == num_choices - 1) ? 0 : choice + 1;
        else if (ch == 10)
            break;
    }

        switch (choice){
            case 0:
            loadsavedgame();
            break;
            case 1:
            startnewgame();
            break;
            case 2:
            settings();
            break;
            case 3:
            clear();
            mvprintw(5, 50,"Exiting the program. Goodbye!" );
            getch();
            endwin();
            return;
            
        }
        menu();

    

}

int startnewgame(){
     clear();
    
    srand(time(NULL));
    initscr();
    noecho();
    curs_set(FALSE);
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        fprintf(stderr, "Mix_OpenAudio failed: %s\n", Mix_GetError());
        return;
    }

  
    Mix_Music *music = NULL;
    if (ismusicon ) {
        music = Mix_LoadMUS(selected_music);
        if (!music) {
            fprintf(stderr, "Mix_LoadMUS failed: %s\n", Mix_GetError());
            return;
        }

        Mix_PlayMusic(music, -1);
    }

   
    if (floornumber>0){
                    show_temporary_message(0,0,"You have entered a new floor");

    }
    int whichway = rand()%2;
    //روش های مختلف برای ساخت مپ

    int numrooms= rand () % 3 + 6;
    Room * rooms[numrooms];
    firstplace = rand()%numrooms;
    for (int i = 0;i < numrooms; i++ )
    {
        rooms[i]= creatroom(i, rooms, i, whichway,i);
    }
    drawroom(rooms[firstplace],whichway, firstplace);
    roomdrawn[floornumber][firstplace]=true;
        bool placeokforstair=true;
         int stairroom = firstplace;
        while(stairroom==firstplace){
            stairroom= rand()%numrooms;
        }
        bool stairgenerated = false;
        while (!stairgenerated && floornumber < 3){

            int tempx = rooms[stairroom]->positionx+rand()%(rooms[stairroom]->width-3)+1;
            int tempy =rooms[stairroom]->positiony+rand()%(rooms[stairroom]->height-2)+1;

             for (int i =0 ; i < doornumber[stairroom];i++){
            if(rooms[stairroom]->doorpositionx[i] == tempx && rooms[stairroom]->doorpositiony[i] == tempy){
                placeokforstair=false;
            }}
            if(placeokforstair){

          rooms[stairroom]->stairpositionx= tempx;
        rooms[stairroom]->stairpositiony= tempy;
        stairgenerated =true;
            }


        
        }

        int foodnumbers= rand()%3+basefood;
        
        int foodsgenerated=0;
        for (int i =0 ;i<numrooms;i++){
            rooms[i]->foodcount=0;
        }
        
        while (foodsgenerated < foodnumbers)
        {   int foodroom=rand()%numrooms;
            int posx= rooms[foodroom]->positionx+rand()%(rooms[foodroom]->width-2)+1;
            int posy=rooms[foodroom]->positiony+rand()%(rooms[foodroom]->height-2)+1;
            bool placeisokforfood = true;
            for (int i =0 ; i < doornumber[foodroom];i++){
            if(rooms[foodroom]->doorpositionx[i] == posx && rooms[foodroom]->doorpositiony[i] == posy){
                placeisokforfood=false;
            }}
            if(rooms[foodroom]->stairpositionx == posx && rooms[foodroom]->stairpositiony == posy){
             placeisokforfood=false;

            }
           if (playerx==posx && playery==posy){
               placeisokforfood=false;          
           }
            
           if (placeisokforfood){
            rooms[foodroom]->foods[rooms[foodroom]->foodcount].positionx= posx;
             rooms[foodroom]->foods[rooms[foodroom]->foodcount].positiony=posy;
             rooms[foodroom]->foods[rooms[foodroom]->foodcount].collected = false;
             rooms[foodroom]->foodcount++;
            
            

            foodsgenerated++;
           }
           
            
        }
        
        
             /*   int pillarnumber=rand()%4+1;

        int pillargenerated=0;
        for(int i =0 ; i < numrooms;i++){
            rooms[i]->pillarcount=0;
        }
        bool placeisokforpillar=true;
        int posx1=0,posy1=0;
        while (pillargenerated < pillarnumber)
        {   int pillarroom=rand()%numrooms;
             posx1= rooms[pillarnumber]->positionx+rand()%(rooms[pillarroom]->width - 5)+2;
             posy1=rooms[pillarroom]->positiony+rand()%(rooms[pillarroom]->height - 5)+3;
             placeisokforpillar = true;
            for (int i =0 ; i < doornumber[pillarroom];i++){
            if(rooms[pillarroom]->doorpositionx[i] == posx1 && rooms[pillarroom]->doorpositiony[i] == posy1){
                placeisokforpillar=false;
            }}
            for (int i =0;i < numrooms;i++){
            for (int j = 0; j < rooms[i]->foodcount;j++){
                if (posx1==rooms[i]->foods[j].positionx &&posy1==rooms[i]->foods[j].positiony){
                    placeisokforpillar=false;
                }
            }
        }

            if(rooms[pillarroom]->stairpositionx == posx1 && rooms[pillarroom]->stairpositiony == posy1){
             placeisokforpillar=false;

            }
           if (playerx==posx1 && playery==posy1){
               placeisokforpillar=false;    
           }
           if (placeisokforpillar){
            rooms[pillarroom]->pillars[rooms[pillarroom]->pillarcount].positionx=posx1;
             rooms[pillarroom]->pillars[rooms[pillarroom]->pillarcount].positiony=posy1;
             rooms[pillarroom]->pillarcount++;

            

            pillargenerated++;
           } 
        }*/

int goldnumbers = rand() % 6 + 1;
 int blackgoldnumbers = rand() % 3 + 1;  
 int goldsgenerated = 0;
 int blackgoldsgenerated = 0;
 for (int i =0; i< numrooms;i++){
    rooms[i]->blackgoldcount=0;
    rooms[i]->goldcount=0;
 }

 while (goldsgenerated < goldnumbers) {
    int goldroom = rand() % numrooms; 
    int posx = rooms[goldroom]->positionx + rand() % (rooms[goldroom]->width - 2) + 1;
    int posy = rooms[goldroom]->positiony + rand() % (rooms[goldroom]->height - 2) + 1;

    bool placeisokforgold = true;
    for (int i = 0; i < doornumber[goldroom]; i++) {
        if (rooms[goldroom]->doorpositionx[i] == posx && rooms[goldroom]->doorpositiony[i] == posy) {
            placeisokforgold = false;
        }
    }
    if (rooms[goldroom]->stairpositionx == posx && rooms[goldroom]->stairpositiony == posy) {
        placeisokforgold = false;
    }
    for (int i = 0; i < rooms[goldroom]->foodcount; i++) {
        if (rooms[goldroom]->foods[i].positionx == posx && rooms[goldroom]->foods[i].positiony == posy) {
            placeisokforgold = false;
        }
    }

    if (placeisokforgold) {
        rooms[goldroom]->golds[rooms[goldroom]->goldcount].positionx = posx;
        rooms[goldroom]->golds[rooms[goldroom]->goldcount].positiony = posy;
        rooms[goldroom]->goldcount++;
        goldsgenerated++;
    }
 } 


 while (blackgoldsgenerated < blackgoldnumbers) {
    int blackgoldroom = rand() % numrooms;
    int posx = rooms[blackgoldroom]->positionx + rand() % (rooms[blackgoldroom]->width - 2) + 1;
    int posy = rooms[blackgoldroom]->positiony + rand() % (rooms[blackgoldroom]->height - 2) + 1;

    bool placeisokforblackgold = true;
    for (int i = 0; i < doornumber[blackgoldroom]; i++) {
        if (rooms[blackgoldroom]->doorpositionx[i] == posx && rooms[blackgoldroom]->doorpositiony[i] == posy) {
            placeisokforblackgold = false;
        }
    }
    if (rooms[blackgoldroom]->stairpositionx == posx && rooms[blackgoldroom]->stairpositiony == posy) {
        placeisokforblackgold = false;
    }
    for (int i = 0; i < rooms[blackgoldroom]->foodcount; i++) {
        if (rooms[blackgoldroom]->foods[i].positionx == posx && rooms[blackgoldroom]->foods[i].positiony == posy) {
            placeisokforblackgold = false;
        }
    }

    if (placeisokforblackgold) {
        rooms[blackgoldroom]->blackgolds[rooms[blackgoldroom]->blackgoldcount].positionx = posx;
        rooms[blackgoldroom]->blackgolds[rooms[blackgoldroom]->blackgoldcount].positiony = posy;
        rooms[blackgoldroom]->blackgoldcount++;
        blackgoldsgenerated++;
    }
 }
        
        

    

    //connectrooms(rooms, numrooms, whichway);
    playerplacement(player1,rooms, firstplace);
    refresh();
    while (1){
        show_attributes(rooms);
    handleinput(player1,rooms,firstplace, numrooms,whichway,stairroom);
    }
    refresh();
    getch();
    endwin();
}

int main ()

{   
    menu();


} 