#include<iostream>
#include<conio.h>
#include<time.h>
#include<windows.h>
#include<fstream>

#define SCREEN_HEIGHT 30
#define SCREEN_WIDTH 100
#define GAME_BOX 80

using namespace std;
HANDLE console=GetStdHandle(STD_OUTPUT_HANDLE);

class creation{
    public:
    int score=0,speed=50,counter=10,prev_score=0;
    char ch,name[8]="none";
    void gotoxy(int x,int y){
        COORD pos;
        pos.Y=x;
        pos.X=y;
        SetConsoleCursorPosition(console,pos);
    }

    void start_box(){
        int i;
        for(i=3;i<50;i+=2){
            gotoxy(5,i);
            cout<<"*";
        }
        for(i=3;i<50;i+=2){
            gotoxy(25,i);
            cout<<"*";
        }
        for(i=5;i<25;i++){
            gotoxy(i,3);
            cout<<"*";
        }
        for(i=5;i<26;i++){
            gotoxy(i,51);
            cout<<"*";
        }
    }

    void instructions(){
	    system("cls");
	    cout<<"\n\t------------------";
	    cout<<"\n\t   Instructions";
	    cout<<"\n\t------------------";
	    cout<<"\n\n Avoid Cars by moving left or right. ";
	    cout<<"\n\n    Press 'a' to move left";
	    cout<<"\n    Press 'd' to move right";
	    cout<<"\n    Press 'escape' to exit";
	    cout<<"\n\nPress any key to go back to menu";
	    getch();
    }

    void border(){
        for(int i=1; i<=SCREEN_HEIGHT; i++){
		    for(int j=1; j<=20; j++){        //right(1-20) and left(61-80), mid(21-60)
			    gotoxy(i,j); cout<<'-';
			    gotoxy(i,GAME_BOX-j+1); cout<<'-';
		    }
        }
	for(int i=1; i<=SCREEN_HEIGHT; i++){
		gotoxy(i,SCREEN_WIDTH); cout<<"|";
	}
    }

    void cursor_visibility(bool _switch){
        CONSOLE_CURSOR_INFO cursor;
        cursor.bVisible=_switch; //0->invisible
        cursor.dwSize=1;        // minimized the size of cursor
        SetConsoleCursorInfo(console,&cursor);
    }

    void score_board(){
        ifstream sf("score_file.txt");
        sf>>name>>prev_score;
        sf.close();
        gotoxy(2,GAME_BOX+5); cout<<"------------";
        gotoxy(3,GAME_BOX+7); cout<<"Car Game";
        gotoxy(4,GAME_BOX+5); cout<<"------------";
        gotoxy(6,GAME_BOX+7); cout<<"Score: "<<score;
        gotoxy(12,GAME_BOX+3); cout<<"|Highest Score|";
        gotoxy(14,GAME_BOX+2); cout<<"-> "<<name<<"\t"<<prev_score;
        gotoxy(20,GAME_BOX+5); cout<<"------------";
        gotoxy(21,GAME_BOX+7); cout<<"Control";
        gotoxy(22,GAME_BOX+5); cout<<"------------";
        gotoxy(24,GAME_BOX+3); cout<<"A -> Move left";
        gotoxy(25,GAME_BOX+3); cout<<"B -> Move right";
    }
    
    void score_update(){
        gotoxy(6,GAME_BOX+7); cout<<"Score: "<<score;
    }
    void game_over(){
        system("cls");
	    cout<<endl;
	    cout<<"\t\t--------------------------"<<endl;
	    cout<<"\t\t-------- Game Over -------"<<endl;
	    cout<<"\t\t--------------------------"<<endl<<endl;
        cout<<"\n\t\tHighest score: "<<prev_score<<endl;
		cout<<"\t\tYour Score: "<<score<<endl;
        if(score>prev_score){
            cout<<"\n\n\tCongratulation you have achieved the highest score."<<endl;
            cout<<"\n\tDo you want to save your score?(Y/N)"<<endl;;
            do{
                ch=getch();
                if(ch=='y'||ch=='Y'){
                    save();
                    cout<<"\n\t\tYour named saved successfully."<<endl;
                    exit(0);
                }
                else if(ch=='n'||ch=='N'){
                    exit(0);
                }   
            }
            while(ch!='Y'||ch!='y');
        }
        else{
            cout<<"\n\n\t\tPress any key to exit.";
            getch();
            exit(0);
        }
	    
        
    }

    void save(){
        cout<<"\n\t\tEnter your name (8 character limit): ";
        cin>>name;
        ofstream sf("score_file.txt");
        sf<<name<<"\n"<<score;
        sf.close();
    }
};

class car:virtual public creation{
    public:
    char car[4][4] = { ' ','*','*',' ', 
					   '*','*','*','*', 
					   ' ','*','*',' ',
					   '*','*','*','*' }; 

    int car_pos=1+GAME_BOX/2; //start position of car
    void draw_car(){
        for(int i=0;i<4;i++){
		    for(int j=0;j<4;j++){
			    gotoxy(i+27,j+car_pos); cout<<car[i][j];
		    }
	    }
    }

    void erase_car(){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			gotoxy(i+27,j+car_pos); cout<<" ";
		}
	}
}
};

class enemy:virtual public creation{
    public:
    int enemyX_cord[3],enemyY_cord[3]={1};
    int enemy_flag[3];

    void enemy_pos(int enemy_num){
        enemyX_cord[enemy_num]=21+rand()%37;   // 61 is the right boundary
    }

    void draw_enemy(int enemy_num){
        if(enemy_flag[enemy_num]==1){
            gotoxy(enemyY_cord[enemy_num]+1,enemyX_cord[enemy_num] );  cout<<"****";  
		    gotoxy(enemyY_cord[enemy_num]+2,enemyX_cord[enemy_num] );  cout<<" ** "; 
		    gotoxy(enemyY_cord[enemy_num]+3,enemyX_cord[enemy_num] );  cout<<"****"; 
		    gotoxy(enemyY_cord[enemy_num]+4,enemyX_cord[enemy_num] );  cout<<" ** ";  
        }
    }

    void erase_enemy(int enemy_num){
        if(enemy_flag[enemy_num]==1){
            gotoxy(enemyY_cord[enemy_num]+1,enemyX_cord[enemy_num] );   cout<<"    ";  
		    gotoxy(enemyY_cord[enemy_num]+2,enemyX_cord[enemy_num] );   cout<<"    "; 
		    gotoxy(enemyY_cord[enemy_num]+3,enemyX_cord[enemy_num] );   cout<<"    "; 
		    gotoxy(enemyY_cord[enemy_num]+4,enemyX_cord[enemy_num] );   cout<<"    ";  
        }
    }

    void next_enemy(int enemy_num){
        erase_enemy(enemy_num);
        enemy_pos(enemy_num);
        enemyY_cord[enemy_num]=1;   //reseting y axis
    }

};

class play:public car,public enemy{
    public:
    int collision();
    void start(){
        system("cls");
        border();
        score_board();
        gotoxy(14,29); cout<<"Press any key to start";
        getch();
        gotoxy(14,29); cout<<"                      ";
        enemy_flag[0]=1;    // enemy car 1 activated
        enemy_flag[1]=0;     // enemy car 2 inactivated
        enemy_pos(0);
        enemy_pos(1);
        while(1){
            if(kbhit()){
                ch=getch();
                if(ch=='A'||ch=='a'){
                    if(car_pos>21){ //21,22,23,24
                    car_pos-=4;
                    }
                }
                if(ch=='D'||ch=='d'){
                    if(car_pos<57){ //57,56,55,54
                    car_pos+=4;
                    }
                }
            }
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
		    draw_car(); 
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),3);
            draw_enemy(0);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),2);
            draw_enemy(1);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);

            if(collision()==1){
                game_over();
                return;
            }

            Sleep(speed);
            erase_car();
            erase_enemy(0);
            erase_enemy(1);


            if(enemyY_cord[0]==13){
                enemy_flag[1]=1;     // enemy car 2 activated so they won't come simultaneously 
            }
            
            if(enemy_flag[0]==1){   //moving forward car 1
                enemyY_cord[0]+=1;
            }

            if(enemy_flag[1]==1){   //moving forward car 2
                enemyY_cord[1]+=1;
            }

            if(enemyY_cord[0]>SCREEN_HEIGHT-3){         //removing enemy when they touch down and reset the 
                next_enemy(0);                          //car to start point 
                score++;
                score_update();
            }

            if(enemyY_cord[1]>SCREEN_HEIGHT-3){          
                next_enemy(1);                          
                score++;
                score_update();
            }

            if(score==counter&&speed>10){
                speed-=5;
                counter+=10;
            }
        }
    }
};

int play::collision(){
    if(enemyY_cord[0]>22){
        if(enemyX_cord[0]+4-car_pos<9&&enemyX_cord[0]+4-car_pos>=0){
            return 1;
        }
    }
    if(enemyY_cord[1]>22){
        if(enemyX_cord[1]+4-car_pos<9&&enemyX_cord[1]+4-car_pos>=0){
            return 1;
        }
    }
    return 0;
}

int main(){
    play obj;
    srand(time(0));
    obj.cursor_visibility(false);
	do{
		system("cls");
        // first para ->row    second para ->col
        obj.start_box();
		obj.gotoxy(8,13);  cout<<" -------------------------- ";
		obj.gotoxy(9,13);  cout<<" |                        | "; 
		obj.gotoxy(10,13); cout<<" |        CAR GAME        | "; 
		obj.gotoxy(11,13); cout<<" |                        | "; 
		obj.gotoxy(12,13); cout<<" --------------------------";
		obj.gotoxy(15,12); cout<<"1 -> Start Game";
		obj.gotoxy(16,12); cout<<"2 -> Instructions";	 
		obj.gotoxy(17,12); cout<<"3 -> Quit";
		obj.gotoxy(20,12); cout<<"Select your option: ";
		char ch = getche();
        obj.gotoxy(25,13);
		switch(ch){
			case '1':
			obj.start();
			break;

			case '2':
			obj.instructions();
			break;

			case '3':
			exit(0);
		}
		
	}while(1);

}
