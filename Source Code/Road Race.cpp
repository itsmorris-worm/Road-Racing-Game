/////////////////////////////////////////////////////ROAD RACING GAME///////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////CHANDAN SHARMA/////////////////////
#include<stdio.h>
#include<conio.h>
#include<dos.h> 
#include <windows.h>
#include <time.h>

#define SCREEN_WIDTH 100
#define SCREEN_HEIGHT 36
#define WIN_WIDTH 70 

using namespace std; 
 
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int enemyY[3];
int enemyX[3];
int enemyFlag[3];
char car[4][4] = { ' ','±','±',' ', 
					'±','±','±','±', 
					' ','±','±',' ',
					'±','±','±','±' }; 
					
int carPos = WIN_WIDTH/2;
int score = 0; 

void gotoxy(int x, int y){
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}
void setcursor(bool visible, DWORD size) {
	if(size == 0)
		size = 46;	
	
	CONSOLE_CURSOR_INFO lpCursor;	
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor);
}
void drawBorder(){  
	for(int i=0; i<SCREEN_HEIGHT; i++){
		for(int j=0; j<17; j++){
			gotoxy(0+j+69,i+7); printf("=");
			gotoxy(WIN_WIDTH-j+69,i+7); printf("=");
		}
	} 
	for(int i=0; i<SCREEN_HEIGHT; i++){
		gotoxy(SCREEN_WIDTH+62,i+7); printf("±");
	} 
}
void genEnemy(int ind){
	enemyX[ind] = 17 + rand()%(33);  
}
void drawEnemy(int ind){
	if( enemyFlag[ind] == true ){
		gotoxy(enemyX[ind]+69, enemyY[ind]+7);   printf("CHAN");  
		gotoxy(enemyX[ind]+69, enemyY[ind]+1+7); printf(" DA "); 
		gotoxy(enemyX[ind]+69, enemyY[ind]+2+7); printf(" NN "); 
		gotoxy(enemyX[ind]+69, enemyY[ind]+3+7); printf("+AA+"); 
	} 
}
void eraseEnemy(int ind){
	if( enemyFlag[ind] == true ){
		gotoxy(enemyX[ind]+69, enemyY[ind]+7); printf("    ");  
		gotoxy(enemyX[ind]+69, enemyY[ind]+1+7); printf("    ");
		gotoxy(enemyX[ind]+69, enemyY[ind]+3+7); printf("    "); 
		gotoxy(enemyX[ind]+69, enemyY[ind]+3+7); printf("    ");
	} 
}
void resetEnemy(int ind){
	eraseEnemy(ind);
	enemyY[ind] = 1;
	genEnemy(ind);
}

void drawCar(){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			gotoxy(j+carPos+69, i+22+7); printf("%c",car[i][j]);
		}
	}
}
void eraseCar(){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			gotoxy(j+carPos+69, i+22+7); printf(" ");
		}
	}
}
 
int collision(){
	if( enemyY[0]+4 >= 23 ){
		if( enemyX[0] + 4 - carPos >= 0 && enemyX[0] + 4 - carPos < 9  ){
			return 1;
		}
	}
	return 0;
} 
void gameover(){
	system("cls");
	printf("\n");
	gotoxy(79.5,20);
	printf("\t\t  -------------------------------");
	gotoxy(79.5,21);
	printf("\t\t   --------- Game Over ---------");
	gotoxy(79.5,22);
	printf("\t\t  -------------------------------");
	gotoxy(76,24);
	printf("\t\t*Press any key to go back to menu.*");
	gotoxy(106,25);
	getch();
}
void updateScore(){
	gotoxy(WIN_WIDTH + 7+69, 5+7);printf("Score: %d\n",score);
}

void instructions(){
	
	system("cls");
	gotoxy(100,15);
	printf("Instructions");
	gotoxy(100,16);
	printf("----------------");
	gotoxy(90,17);
	printf("Avoid Cars by moving left or right. ");
	gotoxy(97,18);
	printf("Press 'a' to move left");
	gotoxy(96,19);
	printf("Press 'd' to move right");
	gotoxy(97,20);
	printf("Press 'escape' to exit");
	gotoxy(92,21);
	printf("Press any key to go back to menu");
	gotoxy(108,22);
	getch();
}

void play(){
	carPos = -1 + WIN_WIDTH/2;
	score = 0;
	enemyFlag[0] = 1;
	enemyFlag[1] = 0;
	enemyY[0] = enemyY[1] = 1;
	  
	system("cls"); 
	drawBorder(); 
	updateScore();
	genEnemy(0);
	genEnemy(1);
	
	gotoxy(WIN_WIDTH + 7+69, 2+8);printf("Car Game");
	gotoxy(WIN_WIDTH + 6+69, 4+7);printf("----------");
	gotoxy(WIN_WIDTH + 6+69, 6+7);printf("----------");
	gotoxy(WIN_WIDTH + 7+69, 12+7);printf("Control ");
	gotoxy(WIN_WIDTH + 7+69, 13+7);printf("-------- ");
	gotoxy(WIN_WIDTH + 2+71, 14+7);printf(" A Key - Left");
	gotoxy(WIN_WIDTH + 2+71, 15+7);printf(" D Key - Right"); 
	
	gotoxy(18+75, 5+7);printf("Press any key to start");
	getch();
	gotoxy(18+75, 5+7);printf("                      ");
	
	while(1){
		if(kbhit()){
			char ch = getch();
			if( ch=='a' || ch=='A' ){
				if( carPos > 18 )
					carPos -= 4;
			}
			if( ch=='d' || ch=='D' ){
				if( carPos < 50 )
					carPos += 4;
			} 
			if(ch==27){
				break;
			}
		} 
		
		drawCar(); 
		drawEnemy(0); 
		drawEnemy(1); 
		if( collision() == 1  ){
			gameover();
			return;
		} 
		Sleep(50);
		eraseCar();
		eraseEnemy(0);
		eraseEnemy(1);   
		
		if( enemyY[0] == 10 )
			if( enemyFlag[1] == 0 )
				enemyFlag[1] = 1;
		
		if( enemyFlag[0] == 1 )
			enemyY[0] += 1;
		
		if( enemyFlag[1] == 1 )
			enemyY[1] += 1;
		 
		if( enemyY[0] > SCREEN_HEIGHT-4 ){
			resetEnemy(0);
			score++;
			updateScore();
		}
		if( enemyY[1] > SCREEN_HEIGHT-4 ){
			resetEnemy(1);
			score++;
			updateScore();
		}
	}
}

int main()
{
	setcursor(0,0); 
	srand( (unsigned)time(NULL)); 
	 
	do{
		system("cls");
		gotoxy(96,15);
		printf("** WELCOME TO THE RACE **");
		getch();
		gotoxy(95,16);
		printf(" -------------------------- "); 
		gotoxy(95,17);
		printf(" |        Road Race        | "); 
		gotoxy(95,18);
		printf(" --------------------------");
		gotoxy(102,20);
		printf("1. Start Game");
		gotoxy(102,21);
		printf("2. Instructions");	 
		gotoxy(102,22);
		printf("3. Quit");
		gotoxy(102,24);
		printf("Select option: ");
		char op = getche();
		
		if( op=='1') play();
		else if( op=='2') instructions();
		else if( op=='3'){
			printf("\n\n");
			char s[200];
			gotoxy(110,27);
			printf("PLEASE, GIVE YOUR FEEDBACK.");
			gotoxy(137,29);
			scanf("%s",s);
			gotoxy(120,31);
			printf("saving...");
			Sleep(3000);
			gotoxy(120,31);
			printf("YOUR FEEDBACK HAS BEEN SAVED.");
			Sleep(1000);
			gotoxy(120,32);
			printf("THANK YOU! FOR YOUR VALUABLE FEEDBACK.");
			Sleep(1000);
			system("cls");
			exit(0);
		}
	}while(1);
	
	return 0;
}
