#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <Windows.h>
#include "Stim.h"
#include <conio.h>
#include <dos.h>
#include <mmsystem.h>  /* multimedia functions (such as MIDI) for Windows */
#include <sys/types.h>
#include <errno.h>



void titleScreen();
void setWindow();
void battleSequence(Enemy en, Player user);

void updateScreen();

void addAnimation(AnimationPtr animate, int x, int y);

void updatePlayerPosition(Player user);

void updateEnemyPosition(Enemy en, Player user);

void warriornextlevel(Player user);

void titleMusic();

char** loadArt(char* filename);

SalesMan addSalesman();

void moveSalesman(SalesMan storeman);

void menuGraphics(Player user);

AnimationPtr initAnimation(frames, x, y);
void initPlayer();
WeaponPtr initWeapon(char* name, double weaponModMin, double weaponModMax, double attackMod, double AccMod, int isPhysical, char* DESCRIPTION, char* fileName);

PotionPtr initPotion(char* NAME, int MAXHPRAISE, int HPRAISE, int ATKRAISE, int DEFRAISE, int MATKRAISE, int MDEFRAISE, int ACCRAISE, int LCKRAISE, char* DESCRIPTION, char* fileName);

ItemPtr initItem(PotionPtr POTION, int QUANTITY, WeaponPtr WEAPON);

void itemBox(Player user, ItemPtr it, int* exit);

void inventoryGraphics(Player user);

void useItem(Player user, ItemPtr it);

char screen[20][80] = { { 176 } };
int playerPosition[2][2] = { 0 };
int screenCounter;
char ground;
char*** characters;
char** playerSprite;
Enemy* enemies;
WeaponPtr* weapons;
PotionPtr* potions;
SalesMan storeman;

HANDLE wHnd;    // Handle to write to the console.
HANDLE rHnd;    // Handle to read from the console.
AnimationPtr boxes;

int main(int argc, char* argv[]){
	int i, j, k;
	Player mainChar = malloc(sizeof(PlayerSize));
	ItemPtr tempItem;
	char key_code;
	boxes = initAnimation(80, 20, 80);
	characters = malloc(5 * sizeof(char*));
	characters[0] = loadArt("Unknown.txt");
	characters[1] = loadArt("Skeleton.txt");
	characters[2] = loadArt("Goblin.txt");
	characters[3] = loadArt("Orc.txt");
	characters[4] = loadArt("Troll.txt");
	
	playerSprite = loadArt("Player.txt");
	storeman = NULL;
	mainChar->BATTLES = 1;
	

	//mainChar->INVENTORY->size = 0;

	


	weapons = malloc(sizeof(WeaponPtr*) * 7);
	weapons[0] = initWeapon("Empty", 0.0, 0.0, 1.0, 100, 1,"Nothing to see here",NULL);
	weapons[0]->picture = loadArt("Unknown.txt");
	weapons[1] = initWeapon("Wooden Sword", 0.0, 0.7, 1.3, 90, 1,"The strongest of all wooden swords",NULL);
	weapons[1]->picture = loadArt("Wooden_sword.txt");
	weapons[2] = initWeapon("Fire Rune", 2.0, 0.8, 1.2, 70, 0,"HOT",NULL);
	weapons[2]->picture = loadArt("Fire_rune.txt");
	weapons[3] = initWeapon("Wood Club", 3.0, 0.6, 1.4, 80, 1,"Big stick",NULL);
	weapons[3]->picture = loadArt("Wood_club.txt");
	weapons[4] = initWeapon("Chipped Dagger", -1.0, 0.9, 1.1, 70, 1,"Sucks to suck",NULL);
	weapons[4]->picture = loadArt("Chipped_dagger.txt");
	//weapons[5] = initWeapon("Light Rune", -1.0, 0.9, 1.1, 70, 1, "ZZZZZP", NULL);
	//weapons[5]->picture = loadArt("Light_rune.txt");
	weapons[6] = initWeapon("Frost Rune", -1.0, 0.9, 1.1, 70, 1, "Chilly...", NULL);
	//weapons[6]->picture = loadArt("Frost_rune.txt");

	potions = malloc(sizeof(PotionPtr*) * 1);
	potions[0] = initPotion("Potion",0,5,0,0,0,0,0,0,"A Simple Healing Potion","Potion.txt");
	potions[0]->picture = loadArt("Potion.txt");
	//PotionPtr initPotion(char* name, int MAXHPRAISE, int HPRAISE, int ATKRAISE, int DEFRAISE, int MATKRAISE, int MDEFRAISE, int ACCRAISE, int LCKRAISE);



	mainChar->weaponLeft = weapons[4];
	mainChar->weaponRight = weapons[0];

	//tempItem->POTION = potions[0];
	//tempItem->QUANTITY = 2;
	

	srand(time(NULL));

	enemies = malloc(sizeof(Enemy) * 3);
	for (i = 0; i < 3; i++)
		enemies[i] = NULL;


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
	system("cls");
	getch();
	titleScreen();
	system("cls");

	character_select(mainChar);
	mainChar->INVENTORY = malloc(sizeof(Inventory));
	mainChar->INVENTORY->head = malloc(sizeof(Item));
	mainChar->INVENTORY->head = NULL;
	mainChar->INVENTORY->size = 0;
	system("cls");
	printf("\n\n\n\n\t\t\t%s, Your journey begins here...\n", mainChar->NAME);
	Sleep(1000);
	system("cls");
	srand(time(NULL));
	ground = 176;



	tempItem = malloc(sizeof(Item));
	tempItem->POTION = potions[0];
	tempItem->QUANTITY = 3;
	tempItem->next = NULL;

	addItem(mainChar, potions[0],3,NULL);
	addItem(mainChar, potions[0], 3,NULL);
	addItem(mainChar, NULL, 1, weapons[2]);
	addItem(mainChar, NULL, 1, weapons[3]);
	addItem(mainChar, NULL, 1, weapons[4]);
	addItem(mainChar, NULL, 1, weapons[6]);
	


	for (i = 0; i < 20; i++)
		screen[i][79] = NULL;

	for (i = 0; i < 20; i++){
		for (j = 0; j < 79; j++)
			screen[i][j] = ground;
	}

	updateEnemyPosition(enemies, mainChar);

	warriornextlevel(mainChar);
	updatePlayerPosition(mainChar);
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

void titleScreen(){
	int i, j;
	char animation[51] = { ' ' };

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
	printf("\t\tPress Any Key To Continue...\n");
	getch();
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

	if (user->Position[1][0] > 20)
		user->Position[1][0] = 19;
	if (user->Position[1][1] > 78)
		user->Position[1][1] = 78;

	if (rand() % 20 == 0){
		for (i = 0; i < 3; i++){
			if (enemies[i] == NULL){
				enemies[i] = lv1_pick_monster();
				break;
			}

		}
	}
	if (rand() % 100 == 0 && storeman == NULL)
		storeman = addSalesman();


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




			screen[en[i]->Position[0][0]][en[i]->Position[0][1]] = ground;
			screen[en[i]->Position[1][0]][en[i]->Position[1][1]] = 233;

			if (user->Position[1][0] == en[i]->Position[1][0] && user->Position[1][1] == en[i]->Position[1][1]){
				for (j = 0; j < 20; j++){
					for (k = 0; k < 80; k++)
						tempScreen[j][k] = screen[j][k];
				}
				ground = ' ';
				addAnimation(boxes, 0, 0);
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
	user->MAXHP = 11;
	user->ATK = 11;
	user->DEF = 13;
	user->MATK = 6;
	user->MDEF = 12;
	user->ACC = 70;
	user->LCK = 8;

	user->Position[0][0] = 15;
	user->Position[0][1] = 15;
	user->Position[1][0] = 15;
	user->Position[1][1] = 15;
	//issword = 0, isrune = 0, ismace = 0, isdagger = 0, isarmor = 0;
	//your_main_weapon();
	//your_off_weapon();
	//your_armor();
	//DMG = calc_dmg();
	//isdual();
	//iswarrior = 1;
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
	Sleep(200);

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
	int i, j, k, l;
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

WeaponPtr initWeapon(char* name, double weaponMod, double attackModMin, double attackModMax, double AccMod, int isPhysical, char* DESCRIPTION,char* fileName){
	WeaponPtr temp;
	temp = malloc(sizeof(Weapon));

	temp->NAME = name;
	temp->weaponMod = weaponMod;
	temp->attackModMin = attackModMin;
	temp->attackModMax = attackModMax;
	temp->AccMod = AccMod;
	temp->isPhysical = isPhysical;
	temp->DESCRIPTION = DESCRIPTION;
	return temp;
}

void moveSalesman(SalesMan storeman, Player user){
	if (storeman != NULL && user != NULL){
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

		if (storeman->Position[1][0] > 20)
			storeman->Position[1][0] = 19;
		if (storeman->Position[1][1] > 78)
			storeman->Position[1][1] = 78;




		screen[storeman->Position[0][0]][storeman->Position[0][1]] = ground;
		screen[storeman->Position[1][0]][storeman->Position[1][1]] = '$';

		if (user->Position[1][0] == storeman->Position[1][0] && user->Position[1][1] == storeman->Position[1][1]){
			printf("Welcome to my humble shop...\n\n");
			getch();
		}


		storeman->Position[0][0] = storeman->Position[1][0];
		storeman->Position[0][1] = storeman->Position[1][1];
	}
}

SalesMan addSalesman(){
	SalesMan temp = malloc(sizeof(SalesManSize));
	temp->Position[1][0] = rand() % 20;
	temp->Position[1][1] = rand() % 80;

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
			if (key_code == 's' && cursor[2] < 2){
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
					printf("You are very handsome\n");
					break;
				case 2:
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
			if (key_code == 'd' && (cursor[0] <  4 + 2 * ceil(user->INVENTORY->size / 2) && cursor[1] < 22 - (20 * (user->INVENTORY->size % 2)))){
				screen[cursor[0]][cursor[1]] = ' ';
				cursor[1] += 20;
				cursor[2] ++;
			}
			if (key_code == 's' && !(cursor[0] == 3 + 2 * ceil(user->INVENTORY->size / 2) && cursor[1] >= 22 - (20 * (user->INVENTORY->size % 2)))){
				if (!(cursor[0] == 5 + 2 * ceil(user->INVENTORY->size / 2)))
				{
					screen[cursor[0]][cursor[1]] = ' ';
					cursor[0] += 2;
					cursor[2] += 2;
				}
				
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
				itemBox(user, tempItem,&exit);
				for (i = 0; i < 20; i++){
					for (j = 0; j < 80; j++)
						screen[i][j] = tempScreen[i][j];
				}

			}
			screen[cursor[0]][cursor[1]] = 219;


			updateScreen();

		}
	}while (key_code != 27 && exit == 0);
	for (i = 0; i < 20; i++){
		for (j = 0; j < 80; j++)
			screen[i][j] = tempScreen2[i][j];
	}

	free(temp);
	return;
}

void itemBox(Player user,ItemPtr it,int* exit){
		char* tempchar = malloc(sizeof(char)*40);
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
			i = 0;
			if (it->POTION->ACCRAISE != 0){
				sprintf(tempchar, "Accuracy: +%d   ", it->POTION->ACCRAISE);
				for (j = 0; j < strlen(tempchar); j++){
					screen[5][j + i + 41] = tempchar[i];
					i++;
				}
					
			}
			if (it->POTION->ATKRAISE != 0){
				sprintf(tempchar, "Attack: +%d   ", it->POTION->ATKRAISE);
				for (i = 0; i < strlen(tempchar); i++){
					screen[5][j + i + 41] = tempchar[i];
					i++;
				}
			}
			if (it->POTION->DEFRAISE != 0){
				sprintf(tempchar, "Defense: +%d   ", it->POTION->DEFRAISE);
				for (i = 0; i < strlen(tempchar); i++){
					screen[5][j + i + 41] = tempchar[i];
					i++;
				}
			}
			if (it->POTION->HPRAISE != 0){
				sprintf(tempchar, "HP: +%d   ", it->POTION->HPRAISE);
				for (i = 0; i < strlen(tempchar); i++){
					screen[5][j + i + 41] = tempchar[i];
					i++;
				}
			}
			if (it->POTION->LCKRAISE != 0){
				sprintf(tempchar, "Luck: +%d   ", it->POTION->LCKRAISE);
				for (i = 0; i < strlen(tempchar); i++){
					screen[5][j + i + 41] = tempchar[i];
					i++;
				}
			}
			if (it->POTION->MATKRAISE != 0){
				sprintf(tempchar, "Magic Attack: +%d   ", it->POTION->MATKRAISE);
				for (i = 0; i < strlen(tempchar); i++){
					screen[5][j + i + 41] = tempchar[i];
					i++;
				}
			}
			if (it->POTION->MDEFRAISE != 0){
				sprintf(tempchar, "Magic Defense: +%d   ", it->POTION->MDEFRAISE);
				for (i = 0; i < strlen(tempchar); i++){
					screen[5][j + i + 41] = tempchar[i];
					i++;
				}
			}
			if (it->POTION->MAXHPRAISE != 0){
				sprintf(tempchar, "Max HP: +%d   ", it->POTION->MAXHPRAISE);
				for (i = 0; i < strlen(tempchar); i++){
					screen[5][j + i + 41] = tempchar[i];
					i++;
				}
			}



			sprintf(tempchar, "%.20s", it->POTION->NAME);
			for (i = 0; i < strlen(tempchar); i++)
			{
				screen[2][i + 41] = tempchar[i];
			}
			sprintf(tempchar, "%s", it->POTION->DESCRIPTION);
			for (i = 0; i < strlen(tempchar); i++)
			{
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

		}

		sprintf(tempchar, "Use");
		for (i = 0; i < strlen(tempchar); i++)
		{
			screen[13][i + 42] = tempchar[i];
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
				screen[cursor[0]][cursor[1]] = ' ';
				cursor[1] += 10;
				cursor[2] ++;
			}
			if (key_code == 's' && cursor[0] < 15 ){
				screen[cursor[0]][cursor[1]] = ' ';
				cursor[0] += 2;
				cursor[2] += 2;
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
							if (tempInt <= 0 || tempInt > it->QUANTITY)
								printf("\nInvalid choice, please select a number between 0 and %d\n", it->QUANTITY);
						} while (tempInt <= 0 || tempInt > it->QUANTITY);

						if (it->QUANTITY != tempInt)
							it->QUANTITY -= tempInt;
						else
							removeItem(user, 1, it);
					}
					else
						removeItem(user, 1, it);
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


PotionPtr initPotion(char* NAME, int MAXHPRAISE, int HPRAISE, int ATKRAISE, int DEFRAISE, int MATKRAISE, int MDEFRAISE, int ACCRAISE, int LCKRAISE, char* DESCRIPTION,char* fileName){
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
		
	}

	if (it->QUANTITY > 1)
		it->QUANTITY--;
	else
		removeItem(User,1,it);
}