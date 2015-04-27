#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#include <dos.h>
#include <mmsystem.h>  /* multimedia functions (such as MIDI) for Windows */
#include <sys/types.h>
#include <errno.h>
#include "Graphics.h"

char screen[20][80] = { { 176 } };
int playerPosition[2][2] = { 0 };
int screenCounter;
char ground;
char*** characters;
char*** shopKeeperFaces;
char** playerSprite;
char** bossSprite;
char*** ripHead;
Enemy* enemies;
int enemiesSize = 0;
WeaponPtr* weapons;
int weaponSize = 0;
PotionPtr* potions;
int potionsSize = 0;
SalesMan storeman;
char** title;
int storemanInt = 0;

HANDLE wHnd;    // Handle to write to the console.
HANDLE rHnd;    // Handle to read from the console.
AnimationPtr boxes;
AnimationPtr spiral;
AnimationPtr flash;

int main(int argc, char* argv[]){
	int i, j, k;
	Player mainChar = malloc(sizeof(PlayerSize));
	ItemPtr tempItem;
	char key_code;

	enemies = malloc(sizeof(Enemy) * 3);
	for (i = 0; i < 3; i++)
		enemies[i] = NULL;
		
	shopKeeperFaces = malloc(sizeof(char**)*3);
	mainChar->INVENTORY = malloc(sizeof(Inventory));
	mainChar->INVENTORY->head = malloc(sizeof(Item));
	mainChar->INVENTORY->head = NULL;
	mainChar->INVENTORY->size = 0;

	mainChar->weaponLeft = malloc(sizeof(Weapon));
	mainChar->weaponRight = malloc(sizeof(Weapon));

	characters = malloc(7 * sizeof(char*));
	weapons = malloc(sizeof(WeaponPtr*) * 7);
	potions = malloc(sizeof(PotionPtr*) * 1);
	
	ripHead = malloc(sizeof(char*) * 8);
	
	

	boxes = initAnimation(80, 20, 80);
	spiral = initAnimation(210, 20, 20);
	flash = initAnimation(6, 20, 40);
	spiral->speed = 20;
	flash->speed = 200;
	for (i = 0; i < 20; i++){
		for (j = 0; j < 80; j++)
			screen[i][j] = ' ';
	}

	i = 0;
	j = 20;
	k = 0;
	for (k = 0; k < 20; k++){
		for (i = 0; i < j; i++){
			if (j % 4 == 0)
				spiral->frames[i][20-j][i] = 219;
			else if (j % 4 == 3)
				spiral->frames[i][i][j] = 219;
			else if (j % 4 == 2)
				spiral->frames[i][j][i] = 219;
			else if (j % 4 == 1)
				spiral->frames[i][i][20-j] = 219;


		}
		j--;
	}

	

	characters[0] = loadArt("Unknown.txt");
	characters[1] = loadArt("Skeleton.txt");
	characters[2] = loadArt("Goblin.txt");
	characters[3] = loadArt("Orc.txt");
	characters[4] = loadArt("Troll.txt");
	characters[5] = loadArt("A_Cog.txt");
	characters[6] = loadArt("Cog_Head.txt");

	playerSprite = loadArt("Player.txt");

	bossSprite = loadArt("A_Cog_Sprite.txt");

	title = loadArt("TitleArt.txt");

	ripHead[0] = loadArt("Frame1.txt");

	ripHead[1] = loadArt("Frame2.txt");
	ripHead[2] = loadArt("Frame3.txt");
	ripHead[3] = loadArt("Frame4.txt");
	ripHead[4] = loadArt("Frame5.txt");
	ripHead[5] = loadArt("Frame6.txt");
	ripHead[6] = loadArt("Frame7.txt");
	ripHead[7] = loadArt("Frame8.txt");


	shopKeeperFaces[0] = loadArt("Shop_n.txt");
	storeman = NULL;

	weapons = malloc(sizeof(WeaponPtr*) * 8);

	weapons[0] = initWeapon("Empty", 0.0,0.0, 0.0, 1.0, 100, 1,"Nothing to see here",NULL,0);
	weapons[0]->picture = loadArt("Unknown.txt");
	weapons[1] = initWeapon("Wooden Sword", 1.0, 1.5, 0.85, 1.15, 90, 1, "The strongest of all wooden swords", NULL,200);
	weapons[1]->picture = loadArt("Wsword.txt");
	weapons[2] = initWeapon("Fire Rune", 2.0, 1.4, 0.9, 1.1, 70, 0,"Kindle your flame",NULL,300);
	weapons[2]->picture = loadArt("Firune.txt");
	weapons[3] = initWeapon("Wood Club", 3.0, 1.0, 0.8, 1.2, 80, 1,"Politics is the skilled use of blunt objects",NULL,600);
	weapons[3]->picture = loadArt("Wclub.txt");
	weapons[4] = initWeapon("Chipped Dagger", -1.0, 1.1, 0.95, 1.05, 75, 1,"Excellent for spreading butter",NULL,100);
	weapons[4]->picture = loadArt("Cdagger.txt");
	weapons[5] = initWeapon("Lightning Rune", 2.0, 1.4, 0.9, 1.1, 70, 0, "ZZZZZP", NULL,300);
	weapons[5]->picture = loadArt("Lrune.txt");
	weapons[6] = initWeapon("Frost Rune", 2.0, 1.4, 0.9, 1.1, 70, 0, "Death is a dish best served cold", NULL,300);
	weapons[6]->picture = loadArt("Frrune.txt");
	weapons[7] = initWeapon("OP Rune", 99.0, 99.4, 99.9, 99.1, 990, 0, "Death is a dish best served OP", NULL, 300);
	weapons[7]->picture = loadArt("Frrune.txt");

	potions[0] = initPotion("Potion", 0, 5, 0, 0, 0, 0, 0, 0, "A Simple Healing Potion", "Potion.txt",50);
	potions[0]->picture = loadArt("Potion.txt");

	srand(time(NULL));




	for (i = 0; i < 79; i++)
	{
		for (j = 0; j < i; j++){
			if (i >= 10)
			{
				boxes->frames[i][19][j] = 219;
				boxes->frames[i][0][j] = 219;
			}
			else{
				boxes->frames[i][10 + i][j] = 219;
				boxes->frames[i][10 - i][j] = 219;
			}
		}
		if (i < 10)
		{
			for (k = 10 - i; k <= 10 + i; k++)
				boxes->frames[i][k][j] = 219;
		}
		else{
			for (k = 0; k < 19; k++)
				boxes->frames[i][k][j] = 219;
			boxes->frames[i][k][j] = 219;
		}



	}
	for (i = 0; i < 19; i++){
		for (j = 0; j < 79; j++)
			boxes->frames[79][i][j] = ' ';
		boxes->speed = 1;
	}

	setWindow();
	initGame(mainChar);
	system("cls");
	getch();

	if (titleScreen(mainChar) == 0){
		system("cls");

		mainChar->BATTLES = 1;
		mainChar->weaponLeft = weapons[4];
		mainChar->weaponRight = weapons[0];

		character_select(mainChar);


		system("cls");
		printf("\n\n\n\n\t\tYour brother has been missing for a long time\n");
		Sleep(2000);
		printf("\t\t\t%s, Your quest is to find him\n", mainChar->NAME);
		Sleep(1500);
		printf("\n\n\t\t\t     (w,a,s,d to move)\n");
		//printf("\n\n\n\n\t\t\t%s, Your journey begins here...\n", mainChar->NAME);
		Sleep(1000);
		printf("\n\n\t\t\tPress enter to continue...");
		getch();
		system("cls");

		tempItem = malloc(sizeof(Item));
		tempItem->POTION = potions[0];
		tempItem->QUANTITY = 3;
		tempItem->next = NULL;

		addItem(mainChar, potions[0], 3, NULL);
		addItem(mainChar, potions[0], 3, NULL);
		addItem(mainChar, NULL, 1, weapons[2]);
		addItem(mainChar, NULL, 1, weapons[3]);
		addItem(mainChar, NULL, 1, weapons[4]);
		addItem(mainChar, NULL, 1, weapons[6]);
		addItem(mainChar, NULL, 1, weapons[7]);
		warriornextlevel(mainChar);
	}
	else
	{
		system("cls");
		printf("\n\n\n\n\t\t\tWelcome back %s...\n", mainChar->NAME);
		Sleep(1000);
		system("cls");
	}
	srand(time(NULL));
	ground = 176;

	for (i = 0; i < 20; i++)
		screen[i][79] = NULL;

	for (i = 0; i < 20; i++){
		for (j = 0; j < 79; j++)
			screen[i][j] = ground;
	}

	updateEnemyPosition(enemies, mainChar);

	
	updatePlayerPosition(mainChar);
	if (mainChar->BATTLES > 10)
		bossBattleInitiate(mainChar);
	moveSalesman(storeman, mainChar);
	updateScreen();

	while (1){
		
		//getch();
		//if (kbhit()){
		mainChar->isInBattle = 0;
		key_code = getch();

		if (key_code == 'w')
			mainChar->Position[1][0] --;
		if (key_code == 's')
			mainChar->Position[1][0] ++;

		if (key_code == 'a')
			mainChar->Position[1][1] --;
		if (key_code == 'd')
			mainChar->Position[1][1] ++;
		if (key_code == 'w' || key_code == 'a' || key_code == 's' || key_code == 'd'){
			updatePlayerPosition(mainChar);
			moveSalesman(storeman, mainChar);
			updateEnemyPosition(enemies, mainChar);
			if (mainChar->BATTLES > 10)
				bossBattleInitiate(mainChar);
			updateScreen();

		}
		if (key_code == 27)
			menuGraphics(mainChar);
		updatePlayerPosition(mainChar);
		updateScreen();



		key_code = NULL;



		//}
		//else
		//continue;
	}

}

int titleScreen(Player user){
	int i, j,k;
	char animation[51] = { ' ' };
	char cursor[3];
	char temp[64];
	int key_code = 0;

	animation[50] = NULL;
	
	for (i = 0; i < 20; i++){
		animation[25 - i] = '-';
		animation[25 + i] = '-';
		printf("\t\t\tSTim\n");
		for (j = 0; j < 50; j++)
			printf("%c", animation[j]);
		printf("\n\n\n");
		Sleep(20);
		if (i < 19)
			system("cls");
	}
	getch();
	system("cls");
	for (i = 0; i < 7; i++){
		for (j = 0; j < 30; j++)
			screen[i + 1][j + 20] = title[i][j];
	}
	updateScreen();
	
	sprintf(temp, "Start");
	for (j = 0; j < strlen(temp); j++){
		screen[10][j + 31] = temp[j];
	}
	sprintf(temp, "Load");
	for (j = 0; j < strlen(temp); j++){
		screen[10][j + 41] = temp[j];
	}
	cursor[0] = 10;
	cursor[1] = 30;
	cursor[2] = 0;

	screen[cursor[0]][cursor[1]] = 219;

	updateScreen();

	while (key_code != 13){
		key_code = getch();

		if (key_code == 'a' && cursor[1] >= 31){
			screen[cursor[0]][cursor[1]] = ' ';
			cursor[1] -= 10;
			cursor[2] --;
		}
		if (key_code == 'd' && (cursor[1] < 31)){
			if (!(cursor[0]>13))
			{
				screen[cursor[0]][cursor[1]] = ' ';
				cursor[1] += 10;
				cursor[2] ++;
			}
		}
		if (key_code == 13){
			switch (cursor[2]){
			case 0:
				return 0;
				break;
			case 1:
				loadGame(user);
				return 1;
				break;
			}
		}
		else
			screen[cursor[0]][cursor[1]] = 219;
		updateScreen();
	}
	//printf("\t\tPress Any Key To Continue...\n");
	//getch();
	system("cls");
}

void setWindow()
{
	// Set up the handles for reading/writing:
	wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	rHnd = GetStdHandle(STD_INPUT_HANDLE);
	// Change the window title:

	// Set up the required window size:
	SMALL_RECT windowSize = { 0, 0, 500, 400 };
	SetConsoleWindowInfo(wHnd, 1, &windowSize);
	// Change the console window size:
	// Create a COORD to hold the buffer size:
	COORD bufferSize = { 70, 70 };
	SetConsoleScreenBufferSize(wHnd, bufferSize);
	MoveWindow(GetConsoleWindow(), 100, 100, 700, 500, TRUE);
	// Exit
	SetConsoleTitle(L"STim");
	return 0;
}

void updateScreen(){
	system("cls");

	for (screenCounter = 0; screenCounter < 20; screenCounter++)
		printf("%.79s\n", screen[screenCounter]);

}

void updatePlayerPosition(Player user){
	int i;

	if (user->Position[1][0] < 0)
		user->Position[1][0] = 0;
	if (user->Position[1][1] < 0)
		user->Position[1][1] = 0;

	if (user->Position[1][0] > 19)
		user->Position[1][0] = 19;
	if (user->Position[1][1] > 78)
		user->Position[1][1] = 78;

	if (rand() % 20 == 0){
		for (i = 0; i < 3; i++){
			if (enemies[i] == NULL){
				enemies[i] = lv1_pick_monster(user->BATTLES,(rand() % 4));
				break;
			}

		}
	}
	if (rand() % 100 == 0 && storemanInt == 0)
		storeman = addSalesman(user);


	screen[user->Position[0][0]][user->Position[0][1]] = ground;
	screen[user->Position[1][0]][user->Position[1][1]] = 219;

	user->Position[0][0] = user->Position[1][0];
	user->Position[0][1] = user->Position[1][1];

	

	

}

void updateEnemyPosition(Enemy* en, Player user){
	int i,j,k;
	int tempScreen[20][80];
	for (i = 0; i<3; i++){
		if (en[i] != NULL){
			en[i]->LEVEL = user->BATTLES;
				if ((rand() % 2) == 1){
					if (user->Position[1][0] > en[i]->Position[1][0])
						en[i]->Position[1][0] ++;
					else if (user->Position[1][0] < en[i]->Position[1][0])
						en[i]->Position[1][0] --;
				}
				else{
					if (user->Position[1][1] > en[i]->Position[1][1])
						en[i]->Position[1][1] ++;
					else if (user->Position[1][1] < en[i]->Position[1][1])
						en[i]->Position[1][1] --;
				}


			if (en[i]->Position[1][0] < 0)
				en[i]->Position[1][0] = 0;
			if (en[i]->Position[1][1] < 0)
				en[i]->Position[1][1] = 0;

			if (en[i]->Position[1][0] > 20)
				en[i]->Position[1][0] = 19;
			if (en[i]->Position[1][1] > 78)
				en[i]->Position[1][1] = 78;

			for (j = 0; en[j] != NULL && j<3; j++){
				if (j != i){
					if (en[i]->Position[1][0] == en[j]->Position[1][0] && en[i]->Position[1][1] == en[j]->Position[1][1]){
						en[i]->Position[1][0] = en[i]->Position[0][0];
						en[i]->Position[1][1] = en[i]->Position[0][1];
					}
						
				}
			}
			if (storemanInt == 1){
				if (en[i]->Position[1][0] == storeman->Position[1][0] && en[i]->Position[1][1] == storeman->Position[1][1]){
					en[i]->Position[1][0] = en[i]->Position[0][0];
					en[i]->Position[1][1] = en[i]->Position[0][1];
				}
			}
		

			screen[en[i]->Position[0][0]][en[i]->Position[0][1]] = ground;
			screen[en[i]->Position[1][0]][en[i]->Position[1][1]] = 233;

			

			if (user->Position[1][0] == en[i]->Position[1][0] && user->Position[1][1] == en[i]->Position[1][1]){
				for (j = 0; j < 20; j++){
					for (k = 0; k < 80; k++)
						tempScreen[j][k] = screen[j][k];
				}
				ground = ' ';
				addAnimation(boxes, 0, 0);
				//addAnimation(spiral, 0, 20);
				battleSequence(en[i], user);
				for (j = 0; j < 20; j++){
					for (k = 0; k < 80; k++)
						screen[j][k] = tempScreen[j][k];
				}
				ground = 176;
				if (en[i]->HP <= 0){
					screen[en[i]->Position[1][0]][en[i]->Position[1][1]] = ground;
					en[i] = NULL;
				}
			}

			if (en[i] != NULL){
				en[i]->Position[0][0] = en[i]->Position[1][0];
				en[i]->Position[0][1] = en[i]->Position[1][1];
			}
		}
	}



}

void warriornextlevel(Player user)
{
	user->Position[0][0] = 15;
	user->Position[0][1] = 15;
	user->Position[1][0] = 15;
	user->Position[1][1] = 15;
}

void addAnimation(AnimationPtr animate, int x, int y){
	int i, j, k;
	for (i = 0; i < animate->frameCount; i++){
		for (j = 0; j < animate->sizeX; j++){
			for (k = 0; k < animate->sizeY; k++){
				if (i > 0 && animate->frames[i - 1][j][k] != NULL)
					screen[x + j][y + k] = ground;
				if (animate->frames[i][j][k] != NULL)
					screen[x + j][y + k] = animate->frames[i][j][k];

			}

		}
		Sleep(animate->speed);
		updateScreen();
		printf("\nSize: %dx%d", sizeof(animate->frames[i]), sizeof(animate->frames[i][j]));
	}




}

AnimationPtr initAnimation(int frames, int x, int y)
{
	int i, j, k;
	AnimationPtr temp;

	temp = malloc(sizeof(Animation));

	temp->frames = malloc(frames * sizeof(char **));
	for (i = 0; i < frames; ++i)
	{
		temp->frames[i] = malloc(x * sizeof(char *));
		for (j = 0; j < x; ++j)
		{
			temp->frames[i][j] = malloc(sizeof(char)*y);

			for (k = 0; k < y; k++)
				temp->frames[i][j][k] = NULL;
		}


	}
	temp->frameCount = frames;

	temp->sizeX = x;
	temp->sizeY = y;
	return temp;
}

void battleSequence(Enemy en, Player user){
	int i, j, k;
	int enemyIndex;
	char temp[64];
	int offsetX = 0;
	int offsetY = 0;
	int maxOffset = 1;

	user->isInBattle = 1;

	if (en->NAME == "Skeleton"){
		enemyIndex = 1;
		maxOffset = 48;
	}
	else if (en->NAME == "Goblin"){
		enemyIndex = 2;
		maxOffset = 45;
	}
	else if (en->NAME == "Orc"){
		enemyIndex = 3;
		maxOffset = 40;
	}
	else if (en->NAME == "Troll"){
		enemyIndex = 4;
		maxOffset = 40;
	}
	else{
		enemyIndex = 0;
		maxOffset = 40;
	}


	while (offsetX < maxOffset){
		for (i = 0; characters[enemyIndex][i] != NULL && i < 20; i++){
			for (j = 0; characters[enemyIndex][i][j] != NULL && i < 78; j++){
				if (characters[enemyIndex][i][j] != NULL && characters[enemyIndex][i][j] != NULL != '\n' && characters[enemyIndex][i][j] != ' ')
					screen[i][j + offsetX] = characters[enemyIndex][i][j];

			}

		}
		updateScreen();
		Sleep(20);
		if (offsetX > 0 && offsetX < maxOffset - 1){
			for (i = 0; characters[enemyIndex][i] != NULL && i < 20; i++){
				for (j = 0; characters[enemyIndex][i][j] != NULL && i < 78; j++){

					screen[i][j + offsetX - 1] = ground;

				}
			}

		}


		offsetX++;
	}
	sprintf(temp, "A level %d %s appeared...", en->LEVEL, en->NAME);
	for (i = 0; i < strlen(temp); i++){
		screen[1][i + 3] = temp[i];
		updateScreen();
		Sleep(20);
	}
	Sleep(500);
	updateScreen();
	

	for (i = 0; playerSprite[i] != NULL && i < 10; i++){
		for (j = 0; playerSprite[i][j] != NULL && i < 78; j++){
			if (playerSprite[i][j] != NULL && playerSprite[i][j] != NULL != '\n' && playerSprite[i][j] != ' ')
				screen[i + 10][j] = playerSprite[i][j];

		}

	}
	updateScreen();


	for (i = 0; i < strlen(temp); i++)
		screen[1][i + 3] = ground;
	updateScreen();

	encounter(en, user, screen);

	user->isInBattle = 0;
}

char** loadArt(char* filename){
	int i, j, k, l,m;
	char** temp;
	char tempChar[80];
	FILE* fp;



	fp = fopen(filename, "r");
	if (fp == NULL)
		printf("Not");

	i = 0;
	while (fscanf(fp, "%s") != EOF)
		i++;

	rewind(fp);

	temp = malloc(sizeof(char) * 20);


	j = 0;

	while (j < i){

		temp[j] = malloc(80 * sizeof(char *));
		temp[j][0] = NULL;
		fscanf(fp, "%78[^\n]", temp[j]);
		fscanf(fp, "%c");
		
		//fgets(temp[j], 78, fp);
		j++;
	}

	return temp;
}

WeaponPtr initWeapon(char* name, double weaponMod,double weaponMult, double attackModMin, double attackModMax, double AccMod, int isPhysical, char* DESCRIPTION,char* fileName,int price){
	WeaponPtr temp;
	temp = malloc(sizeof(Weapon));

	temp->NAME = name;
	temp->weaponMod = weaponMod;
	temp->weaponMult = weaponMult;
	temp->attackModMin = attackModMin;
	temp->attackModMax = attackModMax;
	temp->AccMod = AccMod;
	temp->isPhysical = isPhysical;
	temp->DESCRIPTION = DESCRIPTION;
	temp->price = price;
	temp->index = weaponSize;

	weaponSize++;
	return temp;
}

void moveSalesman(SalesMan storeman, Player user){
	int i = 0;
	if (storemanInt == 1 && storeman != NULL && user != NULL){

		if (user->Position[1][0] == storeman->Position[1][0] && user->Position[1][1] == storeman->Position[1][1]){
			Shop(user, storeman);
			storemanInt = 0;
		}
		else{
			int r = rand() % 4;
			if (r == 0)
				storeman->Position[1][1]++;
			if (r == 1)
				storeman->Position[1][1]--;
			if (r == 2)
				storeman->Position[1][0]++;
			if (r == 3)
				storeman->Position[1][0]--;




			if (storeman->Position[1][0] < 0)
				storeman->Position[1][0] = 0;
			if (storeman->Position[1][1] < 0)
				storeman->Position[1][1] = 0;

			if (storeman->Position[1][0] > 19)
				storeman->Position[1][0] = 19;
			if (storeman->Position[1][1] > 78)
				storeman->Position[1][1] = 78;

			if (user->Position[1][0] == storeman->Position[1][0] && user->Position[1][1] == storeman->Position[1][1]){
				storeman->Position[1][0] = storeman->Position[0][0];
				storeman->Position[1][1] = storeman->Position[0][1];
			}
			while (enemies[i] != NULL && i<3){
				if (enemies[i]->Position[1][0] == storeman->Position[1][0] && enemies[i]->Position[1][1] == storeman->Position[1][1]){
					storeman->Position[1][0] = storeman->Position[0][0];
					storeman->Position[1][1] = storeman->Position[0][1];
				}
				i++;
			}

		


			screen[storeman->Position[0][0]][storeman->Position[0][1]] = ground;
			screen[storeman->Position[1][0]][storeman->Position[1][1]] = '$';




			storeman->Position[0][0] = storeman->Position[1][0];
			storeman->Position[0][1] = storeman->Position[1][1];

			
		}
	}
}

SalesMan addSalesman(Player user){
	SalesMan temp = malloc(sizeof(SalesManSize));
	storemanInt = 1;
	do{
		temp->Position[1][0] = rand() % 20;
		temp->Position[1][1] = rand() % 80;
	} while (temp->Position[1][0] != user->Position[1][0] && temp->Position[1][1] != user->Position[1][1]);




	temp->Position[0][0] = temp->Position[1][0];
	temp->Position[0][1] = temp->Position[1][1];

	return temp;
}

void menuGraphics(Player user){
	char tempScreen[20][80];
	char tempScreen2[20][80];
	char temp[20];
	int cursor[3];
	int i, j, k;
	int key_code = 0;
	
	for (i = 0; i < 20; i++){
		for (j = 0; j < 80; j++)
			tempScreen[i][j] = screen[i][j];
	}
	

	for (i = 9; i > 0; i--){
		for (j = 2; j < 22; j++){
			screen[i][j] = ' ';
			screen[18 - i][j] = ' ';
		}
		if (i == 1)
		{
			for (j = 2; j < 22; j++)
				screen[1][j] = 219;
		}
		if (i > 1){
			screen[18 - i][2] = 219;
			screen[18 - i][21] = 219;
			screen[i][2] = 219;
			screen[i][21] = 219;
		}
		if (i == 1)
		{
			screen[17][2] = 219;
			screen[17][21] = 219;
			for (j = 2; j < 22; j++)
				screen[18][j] = 219;
		}
		Sleep(20);
		updateScreen();
	}

	sprintf(temp, "Items");
	for (i = 0; i < strlen(temp); i++)
	{
		screen[4][i + 5] = temp[i];
	}

	sprintf(temp, "%s", user->NAME);
	for (i = 0; i < strlen(temp); i++)
	{
		screen[6][i + 5] = temp[i];
	}

	sprintf(temp, "Save", user->NAME);
	for (i = 0; i < strlen(temp); i++)
	{
		screen[8][i + 5] = temp[i];
	}

	sprintf(temp, "Quit", user->NAME);
	for (i = 0; i < strlen(temp); i++)
	{
		screen[10][i + 5] = temp[i];
	}
	updateScreen();

	cursor[0] = 4;
	cursor[1] = 4;
	cursor[2] = 0;
	while (key_code != 27){
		key_code = 0;


	screen[cursor[0]][cursor[1]] = 219;

	updateScreen();

	
		key_code = getch();
	
			if (key_code == 'w' && cursor[2] > 0){
				screen[cursor[0]][cursor[1]] = ' ';
				cursor[0] -= 2;
				cursor[2] --;
			}
			if (key_code == 's' && cursor[2] < 3){
				screen[cursor[0]][cursor[1]] = ' ';
				cursor[0] += 2;
				cursor[2] ++;
			}
			if (key_code == 13){
				for (i = 0; i < 20; i++){
					for (j = 0; j < 80; j++)
						tempScreen2[i][j] = screen[i][j];
				}
				switch (cursor[2]){
				case 0:
					inventoryGraphics(user);
					break;
				case 1:
					playerStats(user);
					break;
				case 2:
					findSaveFile(user);
					break;
				case 3:
					exit(1);
					break;
				}
				screen[cursor[0]][cursor[1]] = 219;
				for (i = 0; i < 20; i++){
					for (j = 0; j < 80; j++)
						screen[i][j] = tempScreen2[i][j];
				}

			}
			
			updateScreen();
		
			
	}

	for (i = 0; i < 20; i++){
		for (j = 0; j < 80; j++)
			screen[i][j] = tempScreen[i][j];
		updateScreen();
		Sleep(10);
	}

}

void inventoryGraphics(Player user){
	int i, j, k, l, m;
	char tempScreen[20][80];
	char tempScreen2[20][80];
	char* temp = malloc(sizeof(char)*64);
	int key_code = 0;
	int exit = 0;
	int removedItem = 0;
	int cursor[3];
	ItemPtr tempItem;
	tempItem;

	for (i = 0; i < 20; i++){
		for (j = 0; j < 80; j++)
			tempScreen2[i][j] = screen[i][j];
	}

	cursor[0] = 5;
	cursor[1] = 1;
	cursor[2] = 0;

	

		do{
			removedItem = 0;
		tempItem = user->INVENTORY->head;
		key_code = 0;
		for (i = 0; i < 20; i++){
			for (j = 0; j < 80; j++)
				screen[i][j] = ' ';
		}
		sprintf(temp, "Left Hand: %.20s\0", user->weaponLeft->NAME);

		for (i = 0; i < 32 && temp[i] != '\0'; i++){
			screen[1][i + 10] = temp[i];
		}

		sprintf(temp, "Right Hand: %.20s\0", user->weaponRight->NAME);
		for (i = 0; i < 32 && temp[i] != '\0'; i++){
			screen[3][i + 10] = temp[i];
		}

		i = 2;
		k = 5;

		for (l = 0; l < user->INVENTORY->size; l++)
		{
			for (m = 0; m < 21; m++)
				temp[m] = ' ';
			if (tempItem->POTION != NULL){
				sprintf(temp, "%.20s x%d", tempItem->POTION->NAME, tempItem->QUANTITY);
			}
			if (tempItem->WEAPON != NULL){
				sprintf(temp, "%.20s x%d", tempItem->WEAPON->NAME, tempItem->QUANTITY);
			}


			for (j = 0; j < 20; j++){
				if (temp[j] != NULL)
					screen[k][i] = temp[j];
				i++;
			}

			if (i > 39){
				i = 2;
				k += 2;
			}
			tempItem = tempItem->next;

		}
		updateScreen();

		if (user->INVENTORY->size < 1){
			printf("Your inventory is empty...\n");
			printf("Press ESC to exit");
			key_code = getch();
		}
		else{

			screen[cursor[0]][cursor[1]] = 219;

			updateScreen();


			key_code = getch();

			if (key_code == 'w' && cursor[0] > 5){
				screen[cursor[0]][cursor[1]] = ' ';
				cursor[0] -= 2;
				cursor[2] -= 2;
			}
			if (key_code == 'a' && cursor[1] >= 20){
				screen[cursor[0]][cursor[1]] = ' ';
				cursor[1] -= 20;
				cursor[2] --;
			}
			if (key_code == 'd' && cursor[1]<20 && cursor[2]+2 <= user->INVENTORY->size){
				
						screen[cursor[0]][cursor[1]] = ' ';
						cursor[1] += 20;
						cursor[2] ++;
				
			}
			if (key_code == 's' && cursor[2] + 3 <= user->INVENTORY->size){
					screen[cursor[0]][cursor[1]] = ' ';
					cursor[0] += 2;
					cursor[2] += 2;
				
			
			}

			if (key_code == 13){
				for (i = 0; i < 20; i++){
					for (j = 0; j < 40; j++)
						tempScreen[i][j] = screen[i][j];
				}
				tempItem = user->INVENTORY->head;
				for (i = 0; i < cursor[2]; i++){
					tempItem = tempItem->next;
				}
				itemBox(user, tempItem,&exit,&removedItem);
				for (i = 0; i < 20; i++){
					for (j = 0; j < 80; j++)
						screen[i][j] = tempScreen[i][j];
				}

				if (cursor[2] + 1 > user->INVENTORY->size)
				{

					if (cursor[1] >= 20){
						screen[cursor[0]][cursor[1]] = ' ';
						cursor[1] -= 20;
						cursor[2] --;
					}
					else if (cursor[0] > 5){
						screen[cursor[0]][cursor[1]] = ' ';
						cursor[0] -= 2;
						cursor[2] -= 2;
					}
				}

			}

			
			
			}
			//screen[cursor[0]][cursor[1]] = 219;


			updateScreen();

		
	}while (key_code != 27 && exit == 0);
	for (i = 0; i < 20; i++){
		for (j = 0; j < 80; j++)
			screen[i][j] = tempScreen2[i][j];
	}

	free(temp);
	return;
}

void itemBox(Player user,ItemPtr it,int* exit,int* removedItem){
		char* tempchar = malloc(sizeof(char)*64);
		int cursor[3];
		int i, j, k,tempInt;
		int key_code = 0;
		for (i = 0; i < 20; i++){
			for (j = 40; j < 79; j++){
				screen[i][j] = ' ';
			}
		}

		for (i = 9; i > 0; i--){
			
			if (i == 1)
			{
				for (j = 40; j < 79; j++)
					screen[0][j] = 219;
				screen[1][40] = 219;
				screen[1][78] = 219;
			}
			if (i > 1){
				screen[18 - i][40] = 219;
				screen[18 - i][78] = 219;
				screen[i][40] = 219;
				screen[i][78] = 219;
			}
			if (i == 1)
			{
				screen[17][40] = 219;
				screen[17][78] = 219;
				for (j = 40; j < 79; j++)
					screen[18][j] = 219;
			}
			Sleep(20);
			updateScreen();
		}
		
		if (it->POTION != NULL)
		{
			i = 1;
			if (it->POTION->ACCRAISE != 0){
				sprintf(tempchar, "Accuracy: +%d   ", it->POTION->ACCRAISE);
				for (j = 0; j < strlen(tempchar); j++){
					screen[3+i][j + 41] = tempchar[j];
					i++;
				}
					
			}
			if (it->POTION->ATKRAISE != 0){
				sprintf(tempchar, "Attack: +%d   ", it->POTION->ATKRAISE);
				for (j = 0; j < strlen(tempchar); j++){
					screen[3+i][j + 41] = tempchar[j];
					
				}
				i++;
			}
			if (it->POTION->DEFRAISE != 0){
				sprintf(tempchar, "Defense: +%d   ", it->POTION->DEFRAISE);
				for (j = 0; j < strlen(tempchar); j++){
					screen[3+i][j + 41] = tempchar[j];
					
				}
				i++;
			}
			if (it->POTION->HPRAISE != 0){
				sprintf(tempchar, "HP: +%d   ", it->POTION->HPRAISE);
				for (j = 0; j < strlen(tempchar); j++){
					screen[3+i][j + 41] = tempchar[j];
					
				}
				i++;
			}
			if (it->POTION->LCKRAISE != 0){
				sprintf(tempchar, "Luck: +%d   ", it->POTION->LCKRAISE);
				for (j = 0; j < strlen(tempchar); j++){
					screen[5][j + i + 41] = tempchar[j];
					i++;
				}
			}
			if (it->POTION->MATKRAISE != 0){
				sprintf(tempchar, "Magic Attack: +%d   ", it->POTION->MATKRAISE);
				for (j = 0; j < strlen(tempchar); j++){
					screen[3+i][j + i + 41] = tempchar[j];
					
				}
				i++;
			}
			if (it->POTION->MDEFRAISE != 0){
				sprintf(tempchar, "Magic Defense: +%d   ", it->POTION->MDEFRAISE);
				for (j = 0; j < strlen(tempchar); j++){
					screen[3+i][j + 41] = tempchar[j];
					
				}
				i++;
			}
			if (it->POTION->MAXHPRAISE != 0){
				sprintf(tempchar, "Max HP: +%d   ", it->POTION->MAXHPRAISE);
				for (j = 0; j < strlen(tempchar); j++){
					screen[3+i][j + 42] = tempchar[j];
					
				}
				i++;

			}
			sprintf(tempchar, "%.20s", it->POTION->NAME);
			for (i = 0; i < strlen(tempchar); i++)
			{
				screen[2][i + 41] = tempchar[i];
			}
			sprintf(tempchar, "%s", it->POTION->DESCRIPTION);
			for (i = 0; i < strlen(tempchar); i++)
			{
				if (i>36)
					screen[12][i + 41 - 37] = tempchar[i];
				else
					screen[11][i + 41] = tempchar[i];
			}
			for (i = 0; i < 10; i++){
				for (j = 0; j < 13; j++){
					if(it->POTION->picture[i][j] == NULL)
						break;
					else if (it->POTION->picture[i][j] != '\n'){
						screen[i + 1][j + 57] = it->POTION->picture[i][j];
					}
				}
			}
			sprintf(tempchar, "Use");
			for (i = 0; i < strlen(tempchar); i++)
			{
				screen[13][i + 42] = tempchar[i];
			}
			
		}

		if (it->WEAPON != NULL)
		{
			sprintf(tempchar, "%.20s", it->WEAPON->NAME);
			for (i = 0; i < strlen(tempchar); i++)
			{
				screen[2][i + 41] = tempchar[i];
			}
			sprintf(tempchar, "%s", it->WEAPON->DESCRIPTION);
			for (i = 0; i < strlen(tempchar); i++)
			{
				if (i>36)
					screen[12][i + 41-37] = tempchar[i];
				else
					screen[11][i + 41] = tempchar[i];
			}
			for (i = 0; i < 10; i++){
				for (j = 0; j < 13; j++){
					if (it->WEAPON->picture[i][j] == NULL)
						break;
					else if (it->WEAPON->picture[i][j] != '\n'){
						screen[i + 1][j + 57] = it->WEAPON->picture[i][j];
					}
				}
			}

			i = 1;
			if (it->WEAPON->AccMod != 0){
				sprintf(tempchar, "Accuracy: %g", it->WEAPON->AccMod);
				for (j = 0; j < strlen(tempchar); j++){
					screen[3 + i][j + 41] = tempchar[j];
					
				}
				i++;
			}
			if (it->WEAPON->attackModMax != 0){
				sprintf(tempchar, "Attack MOD: %g", it->WEAPON->attackModMax);
				for (j = 0; j < strlen(tempchar); j++){
					screen[3 + i][j + 41] = tempchar[j];

				}
				i++;
			}
			
			sprintf(tempchar, "Equip");
			for (i = 0; i < strlen(tempchar); i++)
			{
				screen[13][i + 42] = tempchar[i];
			}
			

		}

		
		sprintf(tempchar, "Toss");
		for (i = 0; i < strlen(tempchar); i++)
		{
			screen[13][i + 52] = tempchar[i];
		}
		sprintf(tempchar, "Cancel");
		for (i = 0; i < strlen(tempchar); i++)
		{
			screen[15][i + 42] = tempchar[i];
		}
		
		for (i = 0; i < 18; i++){
			screen[i][78] = 219;
		}
		

		updateScreen();
		

		cursor[0] = 13;
		cursor[1] = 41;
		cursor[2] = 0;

		screen[cursor[0]][cursor[1]] = 219;

		updateScreen();

		while (key_code != 13 && key_code != 27){
			key_code = getch();

			if (key_code == 'w' && cursor[0] > 13){
				screen[cursor[0]][cursor[1]] = ' ';
				cursor[0] -= 2;
				cursor[2] -= 2;
			}
			if (key_code == 'a' && cursor[1] >= 42){
				screen[cursor[0]][cursor[1]] = ' ';
				cursor[1] -= 10;
				cursor[2] --;
			}
			if (key_code == 'd' && (cursor[1] < 42 )){
				if (!(cursor[0]>13))
				{
					screen[cursor[0]][cursor[1]] = ' ';
					cursor[1] += 10;
					cursor[2] ++;
				}
			}
			if (key_code == 's' && cursor[0] < 15 ){
				if (!(cursor[1]>41)){
					screen[cursor[0]][cursor[1]] = ' ';
					cursor[0] += 2;
					cursor[2] += 2;
				}
			}
			if (key_code == 13){
				switch (cursor[2]){
				case 0:
					if (user->isInBattle == 1)
						*exit = 1;
					useItem(user,it);
					break;
				case 1:
					if (it->QUANTITY > 1){
						do{
							printf("How many would you like to throw away?: ");
							scanf("%d", &tempInt);
							clear_buffer();
							if (tempInt <= 0 || tempInt > it->QUANTITY)
								printf("\nInvalid choice, please select a number between 0 and %d\n", it->QUANTITY);
						} while (tempInt <= 0 || tempInt > it->QUANTITY);

						if (it->QUANTITY != tempInt)
							it->QUANTITY -= tempInt;
						else{
							*removedItem = 1;
							removeItem(user, 1, it);
						}
							
					}
					else{
						*removedItem = 1;
						removeItem(user, 1, it);
					}
					break;
				case 2:
					key_code = 13;
					break;
				}

			}
			screen[cursor[0]][cursor[1]] = 219;
			updateScreen();

		}
		free(tempchar);
		return;
	}

PotionPtr initPotion(char* NAME, int MAXHPRAISE, int HPRAISE, int ATKRAISE, int DEFRAISE, int MATKRAISE, int MDEFRAISE, int ACCRAISE, int LCKRAISE, char* DESCRIPTION,char* fileName,int price){
	int i;
	PotionPtr temp = malloc(sizeof(Potion));


	temp->NAME = NAME;
	temp->MAXHPRAISE = MAXHPRAISE;
	temp->HPRAISE = HPRAISE;
	temp->ATKRAISE = ATKRAISE;
	temp->DEFRAISE = DEFRAISE;
	temp->MATKRAISE = MATKRAISE;
	temp->MDEFRAISE = MDEFRAISE;
	temp->ACCRAISE = ACCRAISE;
	temp->LCKRAISE = LCKRAISE;
	temp->DESCRIPTION = DESCRIPTION;
	temp->price = price;
	temp->index = potionsSize;

	potionsSize++;
	return temp;
}

ItemPtr initItem(PotionPtr POTION, int QUANTITY, WeaponPtr WEAPON){
	ItemPtr temp = malloc(sizeof(Item));


	temp->WEAPON = NULL;

	temp->next = NULL;
	temp->prev = NULL;

	return temp;
}

void useItem(Player User, ItemPtr it){
	char tempScreen[20][80];
	int i, j;
	char temp[64];
	int cursor[3];
	int key_code = 0;

	if (it->POTION != NULL){
				User->ACC += it->POTION->ACCRAISE;
				User->ATK += it->POTION->ATKRAISE;
				User->DEF += it->POTION->DEFRAISE;
				User->HP += it->POTION->HPRAISE;
				User->LCK += it->POTION->LCKRAISE;
				User->MATK += it->POTION->MATKRAISE;
				User->MAXHP += it->POTION->MAXHPRAISE;
				User->MDEF += it->POTION->MDEFRAISE;
			}
			if (it->WEAPON != NULL){
				for (i = 0; i < 20; i++){
					for (j = 0; j < 80; j++){
						tempScreen[i][j] = screen[i][j];
					}
				}
				for (i = 2; i < 18; i++){
					for (j = 41; j < 77; j++){
						screen[i][j] = ' ';
					}
				}

				sprintf(temp, "Which hand would you like to equip?");
				for (j = 0; j < strlen(temp); j++){
					screen[3][j + 42] = temp[j];
				}
				sprintf(temp, "Left");
				for (j = 0; j < strlen(temp); j++){
					screen[10][j + 51] = temp[j];
				}
				sprintf(temp, "Right");
				for (j = 0; j < strlen(temp); j++){
					screen[10][j + 61] = temp[j];
				}
				cursor[0] = 10;
				cursor[1] = 50;
				cursor[2] = 0;

				screen[cursor[0]][cursor[1]] = 219;

				updateScreen();

				while (key_code != 13 && key_code != 27){
					key_code = getch();

					if (key_code == 'a' && cursor[1] >= 51){
						screen[cursor[0]][cursor[1]] = ' ';
						cursor[1] -= 10;
						cursor[2] --;
					}
					if (key_code == 'd' && (cursor[1] < 51)){
						if (!(cursor[0]>13))
						{
							screen[cursor[0]][cursor[1]] = ' ';
							cursor[1] += 10;
							cursor[2] ++;
						}
					}
					if (key_code == 13){
						switch (cursor[2]){
						case 0:
							if (User->weaponLeft->NAME != "Empty"){
								addItem(User, NULL, 1, User->weaponLeft);
							}
								
							User->weaponLeft = it->WEAPON;
							break;
						case 1:
							if (User->weaponRight->NAME != "Empty")
								addItem(User, NULL, 1, User->weaponRight);
							User->weaponRight = it->WEAPON;
							break;
						}
						for (i = 0; i < 20; i++){
							for (j = 0; j < 80; j++){
								screen[i][j] = tempScreen[i][j];
							}
						}
					}
					else
						screen[cursor[0]][cursor[1]] = 219;
					updateScreen();
				}


				if (it->QUANTITY > 1)
					it->QUANTITY--;
				else
					removeItem(User, 1, it);
			}
		}

void playerStats(Player user){
	int i, j;
	char temp[64];
	char screenTemp[20][80];

	for (i = 0; i < 20; i++){
		for (j = 0; j < 80; j++)
			screenTemp[i][j] = screen[i][j];
	}
	for (i = 0; i < 20; i++){
		for (j = 0; j < 80; j++)
			screen[i][j] = ' ';
	}

	for (i = 0; i < 20; i++){
		for (j = 0; j < 20 && playerSprite[i][j] != '\0'; j++){
			if (playerSprite[i][j] != '\n')
				screen[i][j] = playerSprite[i][j];
		}
			
		updateScreen();
		Sleep(20);
			
	}
	Sleep(100);

	sprintf(temp,"%s", user->NAME);
	for (j = 0; j < strlen(temp); j++)
		screen[2][j+20] = temp[j];
	updateScreen();
	Sleep(100);

	
	switch (user->CLASS){
	case 1:
		sprintf(temp, "Warrior", user->CLASS);
		break;
	case 2:
		sprintf(temp, "Cleric", user->CLASS);
		break;
	case 3:
		sprintf(temp, "Mage", user->CLASS);
		break;
	case 4:
		sprintf(temp, "Rouge", user->CLASS);
		break;
	}
	for (j = 0; j < strlen(temp); j++)
		screen[3][j + 20] = temp[j];
	updateScreen();
	Sleep(100);

	sprintf(temp, "Attack: %d", user->ATK);
	for (j = 0; j < strlen(temp); j++)
		screen[4][j+30] = temp[j];
	updateScreen();
	Sleep(100);

	sprintf(temp, "Defense: %d", user->DEF);
	for (j = 0; j < strlen(temp); j++)
		screen[5][j+30] = temp[j];
	updateScreen();
	Sleep(100);

	sprintf(temp, "Accuracy: %d", user->ACC);
	for (j = 0; j < strlen(temp); j++)
		screen[6][j+30] = temp[j];
	updateScreen();
	Sleep(100);

	sprintf(temp, "Max HP: %d", user->MAXHP);
	for (j = 0; j < strlen(temp); j++)
		screen[7][j+30] = temp[j];
	updateScreen();
	Sleep(100);

	sprintf(temp, "Current HP: %d", user->HP);
	for (j = 0; j < strlen(temp); j++)
		screen[8][j + 30] = temp[j];
	updateScreen();
	Sleep(100);

	sprintf(temp, "Luck: %d", user->LCK);
	for (j = 0; j < strlen(temp); j++)
		screen[9][j + 30] = temp[j];
	updateScreen();
	Sleep(100);

	sprintf(temp, "Magic Attack: %d", user->MATK);
	for (j = 0; j < strlen(temp); j++)
		screen[10][j + 30] = temp[j];
	updateScreen();
	Sleep(100);

	sprintf(temp, "Magic Defense: %d", user->MDEF);
	for (j = 0; j < strlen(temp); j++)
		screen[11][j + 30] = temp[j];
	updateScreen();
	Sleep(100);

	sprintf(temp, "Currency: %d", user->CURRENCY);
	for (j = 0; j < strlen(temp); j++)
		screen[12][j + 30] = temp[j];
	updateScreen();
	Sleep(100);

	printf("Press any key to exit...");
	getch();

}

void findSaveFile(Player user){
	int i, j, k;
	char temp[64];
	int key_code = 0;
	char cursor[3];
	char tempScreen[20][80];

	if (fopen("Save.s", "r") != NULL)
	{
		for (i = 0; i < 20; i++){
			for (j = 0; j < 80; j++)
				screen[i][j] = ' ';
		}
		sprintf(temp, "There is already a save file, would you like to overwrite?");
		for (j = 0; j < strlen(temp); j++){
			screen[3][j + 11] = temp[j];
		}
		sprintf(temp, "Yes");
		for (j = 0; j < strlen(temp); j++){
			screen[10][j + 21] = temp[j];
		}
		sprintf(temp, "No");
		for (j = 0; j < strlen(temp); j++){
			screen[10][j + 31] = temp[j];
		}
		cursor[0] = 10;
		cursor[1] = 20;
		cursor[2] = 0;

		screen[cursor[0]][cursor[1]] = 219;

		updateScreen();

		while (key_code != 13 && key_code != 27){
			key_code = getch();

			if (key_code == 'a' && cursor[1] >= 21){
				screen[cursor[0]][cursor[1]] = ' ';
				cursor[1] -= 10;
				cursor[2] --;
			}
			if (key_code == 'd' && (cursor[1] < 21)){
				if (!(cursor[0]>13))
				{
					screen[cursor[0]][cursor[1]] = ' ';
					cursor[1] += 10;
					cursor[2] ++;
				}
			}
			if (key_code == 13){
				switch (cursor[2]){
				case 0:
					saveGame(user);
					break;
				case 1:
					break;
				}
				for (i = 0; i < 20; i++){
					for (j = 0; j < 80; j++){
						screen[i][j] = tempScreen[i][j];
					}
				}
			}
			else
				screen[cursor[0]][cursor[1]] = 219;
			updateScreen();
		}
	}
	else{
		saveGame(user);
	}

}

void saveGame(Player user){
	FILE* fp;
	ItemPtr temp = user->INVENTORY->head;
	int i,j;
	printf("Saving...\n\n");


	fp = fopen("Save.s", "w");

	fprintf(fp, "%s\n", user->NAME);
	
	fprintf(fp,"%d\n", user->CLASS);
	fprintf(fp,"%d\n", user->ATK);
	fprintf(fp,"%d\n", user->DEF);
	fprintf(fp, "%d\n", user->ACC);
	fprintf(fp, "%d\n", user->LCK);
	fprintf(fp, "%d\n", user->MATK);
	fprintf(fp, "%d\n", user->MDEF);
	fprintf(fp, "%d\n", user->HP);
	fprintf(fp, "%d\n", user->MAXHP);
	fprintf(fp, "%d\n", user->BATTLES);
	fprintf(fp, "%d\n", user->CURRENCY);
	fprintf(fp, "%d\n", user->Position[1][0]);
	fprintf(fp, "%d\n", user->Position[1][1]);
	fprintf(fp, "%s\n", user->weaponLeft->NAME);
	fprintf(fp, "%s\n", user->weaponRight->NAME);
	fprintf(fp, "%d\n", user->INVENTORY->size);


	for (i = 0; i < user->INVENTORY->size; i++){
		if (temp->POTION != NULL){
			fprintf(fp, "Potion\n");
			fprintf(fp, "%s\n%d\n", temp->POTION->NAME, temp->QUANTITY);
		}
		else if (temp->WEAPON != NULL){
			fprintf(fp, "Weapon\n");
			fprintf(fp, "%s\n%d\n", temp->WEAPON->NAME, temp->QUANTITY);
		}
		temp = temp->next;
	}
	j = 0;
	for (i = 0; i < 3; i++){
		if (enemies[i] != NULL)
			j++;
	}
	fprintf(fp, "%d\n", j);
	for (i = 0; i < 3; i++){
		if (enemies[i] != NULL){
			fprintf(fp, "%d\n", enemies[i]->index);
			fprintf(fp, "%d\n", enemies[i]->LEVEL);
			fprintf(fp, "%d\n", enemies[i]->Position[1][0]);
			fprintf(fp, "%d\n", enemies[i]->Position[1][1]);
		}
	}
	if (storeman == NULL)
		fprintf(fp, "0\n");
	else{
		fprintf(fp, "1\n");
		fprintf(fp, "%d\n", storeman->Position[1][0]);
		fprintf(fp, "%d\n", storeman->Position[1][1]);
	}

	fclose(fp);

	
	Sleep(1000);
	printf("Save complete");
}

void loadGame(Player user){
	FILE* fp;
	ItemPtr temp = user->INVENTORY->head;
	int loadInt,tempSize,loadInt2;
	char loadChar[64];
	int i, j;

	printf("Loading...\n");
	fp = fopen("Save.s", "r");

	fscanf(fp, "%s", user->NAME);

	fscanf(fp, "%d", &user->CLASS);
	fscanf(fp, "%d", &user->ATK);
	fscanf(fp, "%d", &user->DEF);
	fscanf(fp, "%d", &user->ACC);
	fscanf(fp, "%d", &user->LCK);
	fscanf(fp, "%d", &user->MATK);
	fscanf(fp, "%d", &user->MDEF);
	fscanf(fp, "%d", &user->HP);
	fscanf(fp, "%d", &user->MAXHP);
	fscanf(fp, "%d", &user->BATTLES);
	fscanf(fp, "%d", &user->CURRENCY);
	fscanf(fp, "%d", &user->Position[1][0]);
	fscanf(fp, "%d", &user->Position[1][1]);

	user->Position[0][0] = user->Position[1][0];
	user->Position[0][1] = user->Position[1][1];


	fgets(loadChar, 10, fp);
	fgets(loadChar, 64, fp);
	for (j = 0; j < weaponSize; j++){
		if (strncmp(weapons[j]->NAME, loadChar, strlen(weapons[j]->NAME)) == 0)
			user->weaponLeft = weapons[j];
	}
	fgets(loadChar, 64, fp);
	for (j = 0; j < weaponSize; j++){
		if (strncmp(weapons[j]->NAME, loadChar, strlen(weapons[j]->NAME)) == 0)
			user->weaponRight = weapons[j];
	}

	fscanf(fp, "%d", &tempSize);

	
	user->INVENTORY->size = 0;

	for (i = 0; i < tempSize; i++){
		//fgets(loadChar, 64, fp);
		fscanf(fp,"%s%*c",loadChar);
		if (strcmp(loadChar,"Potion",1) == 0){
			fgets(loadChar, 64, fp);
			fscanf(fp, "%d", &loadInt);

			for (j = 0; j < potionsSize; j++){
				if (strncmp(potions[j]->NAME, loadChar, strlen(potions[j]->NAME)) == 0)
					addItem(user, potions[j], loadInt, NULL);
			}
		}
			
		else if (strcmp(loadChar, "Weapon", 1) == 0){
			fgets(loadChar, 64, fp);
			fscanf(fp, "%d", &loadInt);

			for (j = 0; j < weaponSize; j++){
				if (strncmp(weapons[j]->NAME, loadChar, strlen(weapons[j]->NAME)) == 0)
					addItem(user, NULL, loadInt, weapons[j]);
			}
		}
	}

	
	fscanf(fp, "%d", &j);
	for (i = 0; i < j; i++){
		fscanf(fp, "%d", &loadInt);
		fscanf(fp, "%d", &loadInt2);
		enemies[i] = lv1_pick_monster(loadInt2, loadInt);
		fscanf(fp, "%d", &enemies[i]->Position[1][0]);
		fscanf(fp, "%d", &enemies[i]->Position[1][1]);
		}
	
	fscanf(fp, "%d", &loadInt);
	if (loadInt == 1){
		storemanInt = 1;
		storeman = malloc(sizeof(SalesManSize));
		fscanf(fp, "%d", &storeman->Position[1][0]);
		fscanf(fp, "%d", &storeman->Position[1][1]);
		storeman->Position[0][0] = storeman->Position[1][0];
		storeman->Position[0][1] = storeman->Position[1][1];
	}
	fclose(fp);

}

void initGame(Player mainChar){
	int i, j, k, l;
	
	
	
	
}

void hpBars(Player user, Enemy en){
	int i, j, k;
	char temp[64];

	for (i = 0; i <= 20; i++)
		screen[2][i + 10] = ' ';

	for (i = 0; i <= 20; i++)
		screen[0][i + 10] = ' ';

	sprintf(temp, "Enemy Hp %d/%d",en->HP,en->MAXHP);
	for (i = 0; i < strlen(temp); i++)
		screen[0][i + 10] = temp[i];
	j = 0;

	for (i = 0; i <= (((double)en->HP*100) / ((double)en->MAXHP*10))*4;i++){

		if (i % 2 == 1)
			screen[2][j+10] = 177;
		else{
			screen[2][j+10] = 219;
			j++;
		}
			
	}

	screen[2][31] = 186;
	screen[2][9] = 186;
	screen[1][9] = 201;
	screen[3][9] = 200;

	for (i = 0; i < 21; i++)
		screen[3][i + 10] = 205;
	screen[3][i + 10] = 188;
	for (i = 0; i < 21; i++)
		screen[1][i + 10] = 205;
	screen[1][i + 10] = 187;

	for (i = 0; i <= 20; i++)
		screen[16][i + 20] = ' ';

	for (i = 0; i <= 20; i++)
		screen[18][i + 20] = ' ';

	sprintf(temp, "Player Hp %d/%d", user->HP, user->MAXHP);
	for (i = 0; i < strlen(temp); i++)
		screen[16][i + 20] = temp[i];
	j = 0;

	for (i = 0; i <= (((double)user->HP * 100) / ((double)user->MAXHP * 10))*4; i++){

		if (i % 2 == 1)
			screen[18][j + 20] = 177;
		else{
			screen[18][j + 20] = 219;
			j++;
		}
	}
	screen[18][41] = 186;
	screen[18][19] = 186;

	screen[17][19] = 201;
	screen[19][19] = 200;
	for (i = 0; i < 21; i++)
		screen[17][i + 20] = 205;
	screen[17][i + 20] = 187;
	for (i = 0; i < 21; i++)
		screen[19][i + 20] = 205;
	screen[19][i + 20] = 188;
	updateScreen();
}

void lv1drops(Player user)
{
	int itm;
	int choice;
	int roll = drop_roll();
	if (roll < 5)
		printf("It dropped nothing!\n");
	if (roll >= 5 && roll < 9)
	{
		itm = (rand() % (weaponSize-2)) +1;
		do{
			updateScreen();
			printf("Enemy dropped a %s\n", weapons[itm]->NAME);
			printf("1)Pick up\n2)Leave there\n", weapons[itm]->NAME);
			scanf("%d", &choice);
			if (choice == 1){
				addItem(user, NULL, 1, weapons[itm]);
			}
			clear_buffer();
		} while (choice > 2 && choice < 1);
		
		
	}
}

void Shop(Player user, SalesMan shopkeeper){
	int i, j, k;
	char temp[64];
	int cursor[3];
	int key_code = 0;
	char tempScreen[20][80];
	int exit = 0;
	

	shopkeeper->INVENTORY = malloc(sizeof(Inventory));
	shopkeeper->INVENTORY->size = 0;

	for (i = 0; i < potionsSize; i++)
		addItemShop(shopkeeper, potions[i], 5, NULL);

	for (i = 1; i < weaponSize; i++)
		addItemShop(shopkeeper, NULL, 1, weapons[i]);


	



	cursor[0] = 10;
	cursor[1] = 20;
	cursor[2] = 0;	
	
	while (exit == 0){
		key_code = 0;

		for (i = 0; i < 20; i++){
			for (j = 0; j < 80; j++){
				tempScreen[i][j] = screen[i][j];
				screen[i][j] = ' ';
			}
		}

		for (i = 0; shopKeeperFaces[0][i] != NULL && i < 20; i++){
			for (j = 0; shopKeeperFaces[0][i][j] != NULL && j < 80; j++)
				screen[i][j + 5] = shopKeeperFaces[0][i][j];
		}
		

		sprintf(temp, "Hello, welcome to my shop");
		for (j = 0; j < strlen(temp); j++){
			screen[9][j + 17] = temp[j];
		}
		sprintf(temp, "Buy");
		for (j = 0; j < strlen(temp); j++){
			screen[10][j + 21] = temp[j];
		}
		sprintf(temp, "Sell");
		for (j = 0; j < strlen(temp); j++){
			screen[10][j + 31] = temp[j];
		}
		sprintf(temp, "Talk");
		for (j = 0; j < strlen(temp); j++){
			screen[12][j + 21] = temp[j];
		}
		sprintf(temp, "Cancel");
		for (j = 0; j < strlen(temp); j++){
			screen[12][j + 31] = temp[j];
		}

		screen[cursor[0]][cursor[1]] = 219;

		updateScreen();

		while (key_code != 13){

			key_code = getch();

			if (key_code == 'a' && cursor[1] >= 21){
				screen[cursor[0]][cursor[1]] = ' ';
				cursor[1] -= 10;
				cursor[2] --;
			}
			if (key_code == 'w' && cursor[0] > 10){
				screen[cursor[0]][cursor[1]] = ' ';
				cursor[0] -= 2;
				cursor[2] -= 2;
			}
			if (key_code == 's' && cursor[0] < 12){
				screen[cursor[0]][cursor[1]] = ' ';
				cursor[0] += 2;
				cursor[2] += 2;
			}
			if (key_code == 'd' && (cursor[1] < 21)){
				if (!(cursor[0]>13))
				{
					screen[cursor[0]][cursor[1]] = ' ';
					cursor[1] += 10;
					cursor[2] ++;
				}
			}
			if (key_code == 13){
				switch (cursor[2]){
				case 0:
					Buy(user, shopkeeper);
					break;
				case 1:
					Sell(user, shopkeeper);
					break;
				case 2:
					break;
				case 3:
					exit = 1;
					break;
				}
				
			
			}
			else
				screen[cursor[0]][cursor[1]] = 219;
			updateScreen();
		}
		for (i = 0; i < 20; i++){
			for (j = 0; j < 80; j++){
				screen[i][j] = tempScreen[i][j];
			}
		}
		updateScreen();
	}
}

void Buy(Player user, SalesMan shopkeeper){
	int i, j, k, l, m;
	char tempScreen[20][80];
	char tempScreen2[20][80];
	char temp[64];
	int key_code = 0;
	int exit = 0;
	int removedItem = 0;
	int cursor[3];
	ItemPtr tempItem;
	tempItem;

	for (i = 0; i < 20; i++){
		for (j = 0; j < 80; j++)
			tempScreen2[i][j] = screen[i][j];
	}

	cursor[0] = 5;
	cursor[1] = 1;
	cursor[2] = 0;



	do{
		removedItem = 0;
		tempItem = shopkeeper->INVENTORY->head;
		key_code = 0;
		for (i = 0; i < 20; i++){
			for (j = 0; j < 80; j++)
				screen[i][j] = ' ';
		}

		sprintf(temp, "Money: %d", user->CURRENCY);
		for (i = 0; i < strlen(temp); i++){
			screen[1][i + 15] = temp[i];
		}

		i = 2;
		k = 5;

		for (l = 0; l < shopkeeper->INVENTORY->size; l++)
		{
			for (m = 0; m < 21; m++)
				temp[m] = ' ';
			if (tempItem->POTION != NULL){
				sprintf(temp, "%.20s x%d", tempItem->POTION->NAME, tempItem->QUANTITY);
			}
			if (tempItem->WEAPON != NULL){
				sprintf(temp, "%.20s x%d", tempItem->WEAPON->NAME, tempItem->QUANTITY);
			}


			for (j = 0; j < 20; j++){
				if (temp[j] != NULL)
					screen[k][i] = temp[j];
				i++;
			}

			if (i > 39){
				i = 2;
				k += 2;
			}
			tempItem = tempItem->next;

		}
		updateScreen();

		if (shopkeeper->INVENTORY->size < 1){
			printf("Sorry, my inventory is empty...\n");
			printf("Press ESC to exit");
			key_code = getch();
		}
		else{

			screen[cursor[0]][cursor[1]] = 219;

			updateScreen();


			key_code = getch();

			if (key_code == 'w' && cursor[0] > 5){
				screen[cursor[0]][cursor[1]] = ' ';
				cursor[0] -= 2;
				cursor[2] -= 2;
			}
			if (key_code == 'a' && cursor[1] >= 20){
				screen[cursor[0]][cursor[1]] = ' ';
				cursor[1] -= 20;
				cursor[2] --;
			}
			if (key_code == 'd' && cursor[1] < 20 && cursor[2] + 2 <= shopkeeper->INVENTORY->size){

				screen[cursor[0]][cursor[1]] = ' ';
				cursor[1] += 20;
				cursor[2] ++;

			}
			if (key_code == 's' && cursor[2] + 3 <= shopkeeper->INVENTORY->size){
				screen[cursor[0]][cursor[1]] = ' ';
				cursor[0] += 2;
				cursor[2] += 2;


			}
			if (key_code == 13){
				for (i = 0; i < 20; i++){
					for (j = 0; j < 40; j++)
						tempScreen[i][j] = screen[i][j];
				}
				tempItem = shopkeeper->INVENTORY->head;
				for (i = 0; i < cursor[2]; i++){
					tempItem = tempItem->next;
				}
				buyBox(user, storeman, tempItem);
				for (i = 0; i < 20; i++){
					for (j = 0; j < 80; j++)
						screen[i][j] = tempScreen[i][j];
				}

				if (cursor[2] + 1 > user->INVENTORY->size)
				{

					if (cursor[1] >= 20){
						screen[cursor[0]][cursor[1]] = ' ';
						cursor[1] -= 20;
						cursor[2] --;
					}
					else if (cursor[0] > 5){
						screen[cursor[0]][cursor[1]] = ' ';
						cursor[0] -= 2;
						cursor[2] -= 2;
					}
				}

			}



		}
		//screen[cursor[0]][cursor[1]] = 219;


		updateScreen();


	} while (key_code != 27 && exit == 0);
	for (i = 0; i < 20; i++){
		for (j = 0; j < 80; j++)
			screen[i][j] = tempScreen2[i][j];
	}

	return;
}

void Sell(Player user, SalesMan shopkeeper){
	int i, j, k, l, m;
	char tempScreen[20][80];
	char tempScreen2[20][80];
	char* temp = malloc(sizeof(char) * 64);
	int key_code = 0;
	int exit = 0;
	int removedItem = 0;
	int cursor[3];
	ItemPtr tempItem;
	tempItem;

	for (i = 0; i < 20; i++){
		for (j = 0; j < 80; j++)
			tempScreen2[i][j] = screen[i][j];
	}

	cursor[0] = 5;
	cursor[1] = 1;
	cursor[2] = 0;



	do{
		removedItem = 0;
		tempItem = user->INVENTORY->head;
		key_code = 0;
		for (i = 0; i < 20; i++){
			for (j = 0; j < 80; j++)
				screen[i][j] = ' ';
		}

		sprintf(temp, "Money: %d", user->CURRENCY);
		for (i = 0; i < strlen(temp); i++){
			screen[1][i + 15] = temp[i];
		}

		i = 2;
		k = 5;

		for (l = 0; l < user->INVENTORY->size; l++)
		{
			for (m = 0; m < 21; m++)
				temp[m] = ' ';
			if (tempItem->POTION != NULL){
				sprintf(temp, "%.20s x%d", tempItem->POTION->NAME, tempItem->QUANTITY);
			}
			if (tempItem->WEAPON != NULL){
				sprintf(temp, "%.20s x%d", tempItem->WEAPON->NAME, tempItem->QUANTITY);
			}


			for (j = 0; j < 20; j++){
				if (temp[j] != NULL)
					screen[k][i] = temp[j];
				i++;
			}

			if (i > 39){
				i = 2;
				k += 2;
			}
			tempItem = tempItem->next;

		}
		updateScreen();

		if (user->INVENTORY->size < 1){
			printf("Your inventory is empty, quit wasting my time...\n");
			printf("Press ESC to exit");
			key_code = getch();
		}
		else{

			screen[cursor[0]][cursor[1]] = 219;

			updateScreen();


			key_code = getch();

			if (key_code == 'w' && cursor[0] > 5){
				screen[cursor[0]][cursor[1]] = ' ';
				cursor[0] -= 2;
				cursor[2] -= 2;
			}
			if (key_code == 'a' && cursor[1] >= 20){
				screen[cursor[0]][cursor[1]] = ' ';
				cursor[1] -= 20;
				cursor[2] --;
			}
			if (key_code == 'd' && cursor[1] < 20 && cursor[2] + 2 <= user->INVENTORY->size){

				screen[cursor[0]][cursor[1]] = ' ';
				cursor[1] += 20;
				cursor[2] ++;

			}
			if (key_code == 's' && cursor[2] + 3 <= user->INVENTORY->size){
				screen[cursor[0]][cursor[1]] = ' ';
				cursor[0] += 2;
				cursor[2] += 2;
			}

			if (key_code == 13){
				for (i = 0; i < 20; i++){
					for (j = 0; j < 40; j++)
						tempScreen[i][j] = screen[i][j];
				}
				tempItem = user->INVENTORY->head;
				for (i = 0; i < cursor[2]; i++){
					tempItem = tempItem->next;
				}
				sellBox(user,shopkeeper, tempItem);
				for (i = 0; i < 20; i++){
					for (j = 0; j < 80; j++)
						screen[i][j] = tempScreen[i][j];
				}

				if (cursor[2] + 1 > user->INVENTORY->size)
				{

					if (cursor[1] >= 20){
						screen[cursor[0]][cursor[1]] = ' ';
						cursor[1] -= 20;
						cursor[2] --;
					}
					else if (cursor[0] > 5){
						screen[cursor[0]][cursor[1]] = ' ';
						cursor[0] -= 2;
						cursor[2] -= 2;
					}
				}

			}



		}
		//screen[cursor[0]][cursor[1]] = 219;


		updateScreen();


	} while (key_code != 27 && exit == 0);
	for (i = 0; i < 20; i++){
		for (j = 0; j < 80; j++)
			screen[i][j] = tempScreen2[i][j];
	}

	free(temp);
	return;
}

void buyBox(Player user,SalesMan shopkeeper, ItemPtr it){
	char* tempchar = malloc(sizeof(char) * 64);
	int cursor[3];
	int toBuy;
	ItemPtr temp;
	int i, j, k, tempInt;
	int key_code = 0;
	for (i = 0; i < 20; i++){
		for (j = 40; j < 79; j++){
			screen[i][j] = ' ';
		}
	}

	for (i = 9; i > 0; i--){

		if (i == 1)
		{
			for (j = 40; j < 79; j++)
				screen[0][j] = 219;
			screen[1][40] = 219;
			screen[1][78] = 219;
		}
		if (i > 1){
			screen[18 - i][40] = 219;
			screen[18 - i][78] = 219;
			screen[i][40] = 219;
			screen[i][78] = 219;
		}
		if (i == 1)
		{
			screen[17][40] = 219;
			screen[17][78] = 219;
			for (j = 40; j < 79; j++)
				screen[18][j] = 219;
		}
		Sleep(20);
		updateScreen();
	}

	if (it->POTION != NULL)
	{
		i = 1;

		sprintf(tempchar, "Price: %d coins", it->POTION->price);
		for (j = 0; j < strlen(tempchar); j++){
			screen[3 + i][j + 41] = tempchar[j];
			
		}
		i+=2;
		if (it->POTION->ACCRAISE != 0){
			sprintf(tempchar, "Accuracy: +%d", it->POTION->ACCRAISE);
			for (j = 0; j < strlen(tempchar); j++){
				screen[3 + i][j + 41] = tempchar[j];
				
			}
			i++;
		}
		if (it->POTION->ATKRAISE != 0){
			sprintf(tempchar, "Attack: +%d", it->POTION->ATKRAISE);
			for (j = 0; j < strlen(tempchar); j++){
				screen[3 + i][j + 41] = tempchar[j];

			}
			i++;
		}
		if (it->POTION->DEFRAISE != 0){
			sprintf(tempchar, "Defense: +%d   ", it->POTION->DEFRAISE);
			for (j = 0; j < strlen(tempchar); j++){
				screen[3 + i][j + 41] = tempchar[j];

			}
			i++;
		}
		if (it->POTION->HPRAISE != 0){
			sprintf(tempchar, "HP: +%d   ", it->POTION->HPRAISE);
			for (j = 0; j < strlen(tempchar); j++){
				screen[3 + i][j + 41] = tempchar[j];

			}
			i++;
		}
		if (it->POTION->LCKRAISE != 0){
			sprintf(tempchar, "Luck: +%d   ", it->POTION->LCKRAISE);
			for (j = 0; j < strlen(tempchar); j++){
				screen[5][j + i + 41] = tempchar[j];
				i++;
			}
		}
		if (it->POTION->MATKRAISE != 0){
			sprintf(tempchar, "Magic Attack: +%d   ", it->POTION->MATKRAISE);
			for (j = 0; j < strlen(tempchar); j++){
				screen[3 + i][j + i + 41] = tempchar[j];

			}
			i++;
		}
		if (it->POTION->MDEFRAISE != 0){
			sprintf(tempchar, "Magic Defense: +%d   ", it->POTION->MDEFRAISE);
			for (j = 0; j < strlen(tempchar); j++){
				screen[3 + i][j + 41] = tempchar[j];

			}
			i++;
		}
		if (it->POTION->MAXHPRAISE != 0){
			sprintf(tempchar, "Max HP: +%d   ", it->POTION->MAXHPRAISE);
			for (j = 0; j < strlen(tempchar); j++){
				screen[3 + i][j + 42] = tempchar[j];

			}
			i++;

		}
		sprintf(tempchar, "%.20s", it->POTION->NAME);
		for (i = 0; i < strlen(tempchar); i++)
		{
			screen[2][i + 41] = tempchar[i];
		}
		sprintf(tempchar, "%s", it->POTION->DESCRIPTION);
		for (i = 0; i < strlen(tempchar); i++)
		{
			if (i>36)
				screen[12][i + 41 - 37] = tempchar[i];
			else
				screen[11][i + 41] = tempchar[i];
		}
		for (i = 0; i < 10; i++){
			for (j = 0; j < 13; j++){
				if (it->POTION->picture[i][j] == NULL)
					break;
				else if (it->POTION->picture[i][j] != '\n'){
					screen[i + 1][j + 57] = it->POTION->picture[i][j];
				}
			}
		}
		sprintf(tempchar, "Buy");
		for (i = 0; i < strlen(tempchar); i++)
		{
			screen[13][i + 42] = tempchar[i];
		}

	}

	if (it->WEAPON != NULL)
	{
		sprintf(tempchar, "Price: %d coins", it->WEAPON->price);
		for (j = 0; j < strlen(tempchar); j++){
			screen[1 + i][j + 41] = tempchar[j];
			
		}
		i+=2;
		sprintf(tempchar, "%.20s", it->WEAPON->NAME);
		for (i = 0; i < strlen(tempchar); i++)
		{
			screen[3][i + 41] = tempchar[i];
		}
		sprintf(tempchar, "%s", it->WEAPON->DESCRIPTION);
		for (i = 0; i < strlen(tempchar); i++)
		{
			if (i>36)
				screen[12][i + 41 - 37] = tempchar[i];
			else
				screen[11][i + 41] = tempchar[i];
		}
		for (i = 0; i < 10; i++){
			for (j = 0; j < 13; j++){
				if (it->WEAPON->picture[i][j] == NULL)
					break;
				else if (it->WEAPON->picture[i][j] != '\n'){
					screen[i + 1][j + 57] = it->WEAPON->picture[i][j];
				}
			}
		}

		i = 1;
		if (it->WEAPON->AccMod != 0){
			sprintf(tempchar, "Accuracy: %g", it->WEAPON->AccMod);
			for (j = 0; j < strlen(tempchar); j++){
				screen[3 + i][j + 41] = tempchar[j];

			}
			i++;
		}
		if (it->WEAPON->attackModMax != 0){
			sprintf(tempchar, "Attack MOD: %g", it->WEAPON->attackModMax);
			for (j = 0; j < strlen(tempchar); j++){
				screen[3 + i][j + 41] = tempchar[j];

			}
			i++;
		}

		sprintf(tempchar, "Buy");
		for (i = 0; i < strlen(tempchar); i++)
		{
			screen[13][i + 42] = tempchar[i];
		}
	}

	sprintf(tempchar, "Cancel");
	for (i = 0; i < strlen(tempchar); i++)
	{
		screen[13][i + 52] = tempchar[i];
	}

	for (i = 0; i < 18; i++){
		screen[i][78] = 219;
	}


	updateScreen();


	cursor[0] = 13;
	cursor[1] = 41;
	cursor[2] = 0;

	screen[cursor[0]][cursor[1]] = 219;

	updateScreen();

	while (key_code != 13 && key_code != 27){
		key_code = getch();

		if (key_code == 'a' && cursor[1] >= 42){
			screen[cursor[0]][cursor[1]] = ' ';
			cursor[1] -= 10;
			cursor[2] --;
		}
		if (key_code == 'd' && (cursor[1] < 42)){
			if (!(cursor[0]>13))
			{
				screen[cursor[0]][cursor[1]] = ' ';
				cursor[1] += 10;
				cursor[2] ++;
			}
		}
		
		if (key_code == 13){
			switch (cursor[2]){
			case 0:
				if (it->QUANTITY > 1){
					do{
						printf("How many would you like to buy?: ");
						while (scanf("%d", &toBuy) != 1)
							clear_buffer();
						
					} while (toBuy > it->QUANTITY && toBuy < 1);
				}
				else
					toBuy = 1;
				if (it->POTION != NULL){
					if (user->CURRENCY >= it->POTION->price * toBuy){
						user->CURRENCY -= it->POTION->price * toBuy;
						addItem(user, potions[it->POTION->index], toBuy, NULL);
						removeItemShop(shopkeeper, toBuy, it);
					}
					else{
						printf("Not enough currency");
						getch();
					}
				}
				else if (it->WEAPON != NULL){
					if (user->CURRENCY >= it->WEAPON->price * toBuy){
						user->CURRENCY -= it->WEAPON->price * toBuy;
						addItem(user,NULL , toBuy, weapons[it->WEAPON->index]);
						removeItemShop(shopkeeper, toBuy, it);
					}
					else{
						printf("Not enough currency\n");
						printf("Press enter to continue...");
						getch();
					}
				}
				

				break;
			case 1:
				key_code = 13;
				break;
			}

		}
		screen[cursor[0]][cursor[1]] = 219;
		updateScreen();

	}
	free(tempchar);
	return;
}

void sellBox(Player user, SalesMan shopkeeper, ItemPtr it){
	char* tempchar = malloc(sizeof(char) * 64);
	int cursor[3];
	int toSell;
	ItemPtr temp;
	int i, j, k, tempInt;
	int key_code = 0;
	for (i = 0; i < 20; i++){
		for (j = 40; j < 79; j++){
			screen[i][j] = ' ';
		}
	}

	for (i = 9; i > 0; i--){

		if (i == 1)
		{
			for (j = 40; j < 79; j++)
				screen[0][j] = 219;
			screen[1][40] = 219;
			screen[1][78] = 219;
		}
		if (i > 1){
			screen[18 - i][40] = 219;
			screen[18 - i][78] = 219;
			screen[i][40] = 219;
			screen[i][78] = 219;
		}
		if (i == 1)
		{
			screen[17][40] = 219;
			screen[17][78] = 219;
			for (j = 40; j < 79; j++)
				screen[18][j] = 219;
		}
		Sleep(20);
		updateScreen();
	}

	if (it->POTION != NULL)
	{
		i = 1;

		sprintf(tempchar, "Sell Price: %d coins", it->POTION->price/2);
		for (j = 0; j < strlen(tempchar); j++){
			screen[3 + i][j + 41] = tempchar[j];

		}
		i += 2;
		if (it->POTION->ACCRAISE != 0){
			sprintf(tempchar, "Accuracy: +%d", it->POTION->ACCRAISE);
			for (j = 0; j < strlen(tempchar); j++){
				screen[3 + i][j + 41] = tempchar[j];

			}
			i++;
		}
		if (it->POTION->ATKRAISE != 0){
			sprintf(tempchar, "Attack: +%d", it->POTION->ATKRAISE);
			for (j = 0; j < strlen(tempchar); j++){
				screen[3 + i][j + 41] = tempchar[j];

			}
			i++;
		}
		if (it->POTION->DEFRAISE != 0){
			sprintf(tempchar, "Defense: +%d   ", it->POTION->DEFRAISE);
			for (j = 0; j < strlen(tempchar); j++){
				screen[3 + i][j + 41] = tempchar[j];

			}
			i++;
		}
		if (it->POTION->HPRAISE != 0){
			sprintf(tempchar, "HP: +%d   ", it->POTION->HPRAISE);
			for (j = 0; j < strlen(tempchar); j++){
				screen[3 + i][j + 41] = tempchar[j];

			}
			i++;
		}
		if (it->POTION->LCKRAISE != 0){
			sprintf(tempchar, "Luck: +%d   ", it->POTION->LCKRAISE);
			for (j = 0; j < strlen(tempchar); j++){
				screen[5][j + i + 41] = tempchar[j];
				i++;
			}
		}
		if (it->POTION->MATKRAISE != 0){
			sprintf(tempchar, "Magic Attack: +%d   ", it->POTION->MATKRAISE);
			for (j = 0; j < strlen(tempchar); j++){
				screen[3 + i][j + i + 41] = tempchar[j];

			}
			i++;
		}
		if (it->POTION->MDEFRAISE != 0){
			sprintf(tempchar, "Magic Defense: +%d   ", it->POTION->MDEFRAISE);
			for (j = 0; j < strlen(tempchar); j++){
				screen[3 + i][j + 41] = tempchar[j];

			}
			i++;
		}
		if (it->POTION->MAXHPRAISE != 0){
			sprintf(tempchar, "Max HP: +%d   ", it->POTION->MAXHPRAISE);
			for (j = 0; j < strlen(tempchar); j++){
				screen[3 + i][j + 42] = tempchar[j];

			}
			i++;

		}
		sprintf(tempchar, "%.20s", it->POTION->NAME);
		for (i = 0; i < strlen(tempchar); i++)
		{
			screen[2][i + 41] = tempchar[i];
		}
		sprintf(tempchar, "%s", it->POTION->DESCRIPTION);
		for (i = 0; i < strlen(tempchar); i++)
		{
			if (i>36)
				screen[12][i + 41 - 37] = tempchar[i];
			else
				screen[11][i + 41] = tempchar[i];
		}
		for (i = 0; i < 10; i++){
			for (j = 0; j < 13; j++){
				if (it->POTION->picture[i][j] == NULL)
					break;
				else if (it->POTION->picture[i][j] != '\n'){
					screen[i + 1][j + 57] = it->POTION->picture[i][j];
				}
			}
		}
		sprintf(tempchar, "Sell");
		for (i = 0; i < strlen(tempchar); i++)
		{
			screen[13][i + 42] = tempchar[i];
		}

	}

	if (it->WEAPON != NULL)
	{
		sprintf(tempchar, "Sell Price: %d coins", it->WEAPON->price*(2/3));
		for (j = 0; j < strlen(tempchar); j++){
			screen[1 + i][j + 41] = tempchar[j];

		}
		i += 2;
		sprintf(tempchar, "%.20s", it->WEAPON->NAME);
		for (i = 0; i < strlen(tempchar); i++)
		{
			screen[3][i + 41] = tempchar[i];
		}
		sprintf(tempchar, "%s", it->WEAPON->DESCRIPTION);
		for (i = 0; i < strlen(tempchar); i++)
		{
			if (i>36)
				screen[12][i + 41 - 37] = tempchar[i];
			else
				screen[11][i + 41] = tempchar[i];
		}
		for (i = 0; i < 10; i++){
			for (j = 0; j < 13; j++){
				if (it->WEAPON->picture[i][j] == NULL)
					break;
				else if (it->WEAPON->picture[i][j] != '\n'){
					screen[i + 1][j + 57] = it->WEAPON->picture[i][j];
				}
			}
		}

		i = 1;
		if (it->WEAPON->AccMod != 0){
			sprintf(tempchar, "Accuracy: %g", it->WEAPON->AccMod);
			for (j = 0; j < strlen(tempchar); j++){
				screen[3 + i][j + 41] = tempchar[j];

			}
			i++;
		}
		if (it->WEAPON->attackModMax != 0){
			sprintf(tempchar, "Attack MOD: %g", it->WEAPON->attackModMax);
			for (j = 0; j < strlen(tempchar); j++){
				screen[3 + i][j + 41] = tempchar[j];

			}
			i++;
		}

		sprintf(tempchar, "Sell");
		for (i = 0; i < strlen(tempchar); i++)
		{
			screen[13][i + 42] = tempchar[i];
		}
	}

	sprintf(tempchar, "Cancel");
	for (i = 0; i < strlen(tempchar); i++)
	{
		screen[13][i + 52] = tempchar[i];
	}

	for (i = 0; i < 18; i++){
		screen[i][78] = 219;
	}


	updateScreen();


	cursor[0] = 13;
	cursor[1] = 41;
	cursor[2] = 0;

	screen[cursor[0]][cursor[1]] = 219;

	updateScreen();

	while (key_code != 13 && key_code != 27){
		key_code = getch();

		if (key_code == 'a' && cursor[1] >= 42){
			screen[cursor[0]][cursor[1]] = ' ';
			cursor[1] -= 10;
			cursor[2] --;
		}
		if (key_code == 'd' && (cursor[1] < 42)){
			if (!(cursor[0]>13))
			{
				screen[cursor[0]][cursor[1]] = ' ';
				cursor[1] += 10;
				cursor[2] ++;
			}
		}

		if (key_code == 13){
			switch (cursor[2]){
			case 0:
				if (it->QUANTITY > 1){
					do{
						printf("How many would you like to sell?: ");
						while (scanf("%d", &toSell) == 0)
							clear_buffer();
					} while (toSell > it->QUANTITY && toSell < 1);
				}
				else if (it->QUANTITY == 1)
					toSell = 1;
				if (it->POTION != NULL){
					
						user->CURRENCY += it->POTION->price/2*toSell;
						addItemShop(shopkeeper, potions[it->POTION->index], toSell, NULL);
						removeItem(user, toSell, it);
				}
				else if (it->WEAPON != NULL){
						user->CURRENCY += (it->WEAPON->price*(2.0 / 3.0)*toSell);
						addItemShop(shopkeeper, NULL, toSell, weapons[it->WEAPON->index]);
						removeItem(user, toSell, it);
				}

				break;
			case 1:
				key_code = 13;
				break;
			}

		}
		screen[cursor[0]][cursor[1]] = 219;
		updateScreen();

	}
	free(tempchar);
	return;
}

void bossBattleInitiate(Player player){
	int i;
	screen[1][39] = ' ';
	screen[0][39] = ' ';
	screen[1][40] = ' ';
	screen[0][40] = ' ';

	if ((player->Position[1][1] == 39 && player->Position[1][0] == 0) || (player->Position[1][1] == 40 && player->Position[1][0] == 0) || (player->Position[1][1] == 39 && player->Position[1][0] == 1) || (player->Position[1][1] == 40 && player->Position[1][0] == 1))
		bossBattleRoom(player);
}

void bossBattleRoom(Player user){
	int i, j,k;
	int enemy_level = 20;
	int key_code = 0;
	Enemy boss = malloc(sizeof(EnemySize));
	boss->NAME = "A Cognate Pig Sloth";

	boss->index = 3;
	boss->MAXHP = 30 + (.2*enemy_level);
	boss->ATK = 20 + (.2*enemy_level);
	boss->DEF = 10 + (.2*enemy_level);
	boss->MATK = 10 + (.2*enemy_level);
	boss->MDEF = 6 + (.2*enemy_level);
	boss->ACC = 85;
	boss->LCK = 20 + (.2*enemy_level);
	boss->HP = 30 + (.2*enemy_level);
	boss->WMOD = 1.5;
	boss->drop_rareity = 3;

	//addAnimation(spiral, 1, 1);

	user->Position[1][0] = 20;
	user->Position[1][1] = 40;

	

	ground = ' ';
	for (i = 0; i < 20; i++){
		for (j = 0; j < 80; j++)
			screen[i][j] = ' ';
		updateScreen();
		Sleep(20);
	}

	for (i = 0; i < 5; i++){
		for (j = 0; j < 5; j++)
			screen[i][j + 35] = bossSprite[i][j];
	}

	updatePlayerPosition(user);
	updateScreen();

	while (1){

		//getch();
		//if (kbhit()){
		user->isInBattle = 0;
		key_code = getch();

		if (key_code == 'w')
			user->Position[1][0] --;
		if (key_code == 's')
			user->Position[1][0] ++;

		if (key_code == 'a')
			user->Position[1][1] --;
		if (key_code == 'd')
			user->Position[1][1] ++;
		if (key_code == 'w' || key_code == 'a' || key_code == 's' || key_code == 'd'){
			updatePlayerPosition(user);
			//updateScreen();

		}
		if (key_code == 27)
			menuGraphics(user);
		updatePlayerPosition(user);

		for (i = 0; i < 5; i++){
			for (j = 35; j < 40; j++){
				if (user->Position[1][0] == i && user->Position[1][1] == j){
					bossBattle(user, boss);
				}
			}

		}
		updateScreen();

		key_code = NULL;



		//}
		//else
		//continue;
	}


}

void bossBattle(Player user, Enemy en){
	int i, j, k;
	int enemyIndex;
	char temp[64];
	int offsetX = 0;
	int offsetY = 0;
	int maxOffset = 1;

	user->isInBattle = 1;
	maxOffset = 51;
	enemyIndex = 5;

	for (i = 0; i < 20; i++){
		for (j = 0; j < 80; j++)
			screen[i][j] = ' ';
	}
	
	



	while (offsetX < maxOffset){
		for (i = 0; characters[enemyIndex][i] != NULL && i < 20; i++){
			for (j = 0; characters[enemyIndex][i][j] != NULL && i < 78; j++){
				if (characters[enemyIndex][i][j] != NULL && characters[enemyIndex][i][j] != NULL != '\n' && characters[enemyIndex][i][j] != ' ')
					screen[i][j + offsetX] = characters[enemyIndex][i][j];

			}

		}
		updateScreen();
		Sleep(20);
		if (offsetX > 0 && offsetX < maxOffset - 1){
			for (i = 0; characters[enemyIndex][i] != NULL && i < 20; i++){
				for (j = 0; characters[enemyIndex][i][j] != NULL && i < 78; j++){
					screen[i][j + offsetX - 1] = ground;

				}
			}

		}


		offsetX++;
	}
	for (i = 0; playerSprite[i] != NULL && i < 10; i++){
		for (j = 0; playerSprite[i][j] != NULL && j < 78; j++){
			if (playerSprite[i][j] != NULL && playerSprite[i][j] != NULL != '\n' && playerSprite[i][j] != ' ')
				screen[i + 10][j] = playerSprite[i][j];

		}

	}
	sprintf(temp, "%s: ", en->NAME);
	for (i = 0; i < strlen(temp); i++){
		screen[1][i + 3] = temp[i];
		updateScreen();
		Sleep(20);
	}
	Sleep(500);
	sprintf(temp, "The end is near...");
	for (i = 0; i < strlen(temp); i++){
		screen[2][i + 3] = temp[i];
		updateScreen();
		Sleep(20);
	}
	Sleep(1000);
	sprintf(temp, "You will end up just like");
	for (i = 0; i < strlen(temp); i++){
		screen[3][i + 3] = temp[i];
		updateScreen();
		Sleep(20);
	}
	sprintf(temp, "your brother!");
	for (i = 0; i < strlen(temp); i++){
		screen[4][i + 3] = temp[i];
		updateScreen();
		Sleep(20);
	}
	Sleep(1000);

	for (k = 0; k < 8; k++){
		for (i = 0; i < 20; i++){
			for (j = 0; j < 80; j++)
				screen[i][j] = ' ';
		}
		for (i = 0; ripHead[k][i] != NULL && i < 20; i++){
			for (j = 0; ripHead[k][i][j] != NULL && j < 78; j++){
				screen[i][j] = ripHead[k][i][j];
			}
		}
		updateScreen();
		if (k == 0)
			Sleep(1000);
		else
			Sleep(100);
		
	}
	Sleep(1000);
	printf("Press enter to continue...");
	clear_buffer();

	for (i = 0; i < 20; i++){
		for (j = 0; j < 80; j++)
			screen[i][j] = ' ';
	}

	for (i = 0; playerSprite[i] != NULL && i < 10; i++){
		for (j = 0; playerSprite[i][j] != NULL && j < 78; j++){
			if (playerSprite[i][j] != NULL && playerSprite[i][j] != NULL != '\n' && playerSprite[i][j] != ' ')
				screen[i + 10][j] = playerSprite[i][j];

		}

	}



	maxOffset = 33;


	
	for (i = 0; characters[enemyIndex][i] != NULL && i < 20; i++){
		for (j = 0; characters[enemyIndex][i][j] != NULL && i < 78; j++){
			screen[i][j + offsetX - 1] = ground;

		}
	}

	enemyIndex = 6;
	for (i = 0; characters[enemyIndex][i] != NULL && i < 20; i++){
		for (j = 0; characters[enemyIndex][i][j] != NULL && i < 78; j++){
			if (characters[enemyIndex][i][j] != NULL && characters[enemyIndex][i][j] != NULL != '\n' && characters[enemyIndex][i][j] != ' ')
				screen[i][j + maxOffset] = characters[enemyIndex][i][j];

		}

	}
	updateScreen();
	Sleep(2000);
	sprintf(temp, "YOU MONSTER!");
	for (i = 0; i < strlen(temp); i++){
		screen[13][i + 15] = temp[i];
		updateScreen();
		Sleep(20);
	}
	Sleep(1500);
	sprintf(temp, "HAHAHAHAHAHAHAHA!!!");
	for (i = 0; i < strlen(temp); i++){
		screen[6][i + 3] = temp[i];
		updateScreen();
		Sleep(20);
	}
	
	printf("Press enter to continue...");
	clear_buffer();


	for (i = 0; i < 20; i++){
		for (j = 0; j < 80; j++)
			screen[i][j] = ' ';
	}

	for (i = 0; characters[enemyIndex][i] != NULL && i < 20; i++){
		for (j = 0; characters[enemyIndex][i][j] != NULL && i < 78; j++){
			if (characters[enemyIndex][i][j] != NULL && characters[enemyIndex][i][j] != NULL != '\n' && characters[enemyIndex][i][j] != ' ')
				screen[i][j + maxOffset] = characters[enemyIndex][i][j];

		}

	}

	for (i = 0; playerSprite[i] != NULL && i < 10; i++){
		for (j = 0; playerSprite[i][j] != NULL && i < 78; j++){
			if (playerSprite[i][j] != NULL && playerSprite[i][j] != NULL != '\n' && playerSprite[i][j] != ' ')
				screen[i + 10][j] = playerSprite[i][j];

		}

	}

	updateScreen();

	sprintf(temp, "%s", en->NAME);
	for (i = 0; i < strlen(temp); i++){
		screen[0][i + 3] = temp[i];
		updateScreen();
		Sleep(20);
	}
	Sleep(500);

	sprintf(temp, "Level: ???");
	for (i = 0; i < strlen(temp); i++){
		screen[2][i + 3] = temp[i];
		updateScreen();
		Sleep(20);
	}
	Sleep(1000);
	updateScreen();

	for (i = 0; i < strlen(temp); i++)
		screen[1][i + 3] = ground;

	for (i = 0; i < 10;i++)
		screen[0][i] = ' ';
	for (i = 0; i < 10; i++)
		screen[2][i] = ' ';
	
	updateScreen();

	encounter(en, user, screen);

	user->isInBattle = 0;
}