#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#include <dos.h>
#include <mmsystem.h> 
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

HANDLE wHnd;   
HANDLE rHnd;    
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

	shopKeeperFaces = malloc(sizeof(char**) * 3);
	mainChar->INVENTORY = malloc(sizeof(Inventory));
	mainChar->INVENTORY->head = malloc(sizeof(Item));
	mainChar->INVENTORY->head = NULL;
	mainChar->INVENTORY->size = 0;

	mainChar->weaponLeft = malloc(sizeof(Weapon));
	mainChar->weaponRight = malloc(sizeof(Weapon));

	characters = malloc(sizeof(char**)*7);
	weapons = malloc(sizeof(WeaponPtr*) * 11);
	potions = malloc(sizeof(PotionPtr*) * 3);

	ripHead = malloc(sizeof(char*) * 27);

	

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
				spiral->frames[i][20 - j][i] = 219;
			else if (j % 4 == 3)
				spiral->frames[i][i][j] = 219;
			else if (j % 4 == 2)
				spiral->frames[i][j][i] = 219;
			else if (j % 4 == 1)
				spiral->frames[i][i][20 - j] = 219;


		}
		j--;
	}


	
	characters[0] = loadArt(fopen("Unknown.txt","r"));
	characters[1] = loadArt(fopen("Skeleton.txt", "r"));
	characters[2] = loadArt(fopen("Goblin.txt", "r"));
	characters[3] = loadArt(fopen("Orc.txt", "r"));
	characters[4] = loadArt(fopen("Troll.txt", "r"));
	characters[5] = loadArt(fopen("A_Cog.txt", "r"));
	characters[6] = loadArt(fopen("Cog_Head2.txt", "r"));

	playerSprite = loadArt(fopen("Player.txt", "r"));

	bossSprite = loadArt(fopen("A_Cog_Sprite.txt", "r"));

	title = loadArt(fopen("TitleArt.txt", "r"));

	ripHead[0] = loadArt(fopen("Frame1.txt", "r"));
	ripHead[1] = loadArt(fopen("Frame2.txt", "r"));
	ripHead[2] = loadArt(fopen("Frame3.txt", "r"));
	ripHead[3] = loadArt(fopen("Frame4.txt", "r"));
	ripHead[4] = loadArt(fopen("Frame5.txt", "r"));
	ripHead[5] = loadArt(fopen("Frame6.txt", "r"));
	ripHead[6] = loadArt(fopen("Frame7.txt", "r"));
	ripHead[7] = loadArt(fopen("Frame8.txt", "r"));
	ripHead[8] = loadArt(fopen("Frame9.txt", "r"));
	ripHead[9] = loadArt(fopen("Frame10.txt", "r"));
	ripHead[10] = loadArt(fopen("Frame11.txt", "r"));
	ripHead[11] = loadArt(fopen("Frame12.txt", "r"));
	ripHead[12] = loadArt(fopen("Frame13.txt", "r"));
	ripHead[13] = loadArt(fopen("Frame14.txt", "r"));
	ripHead[14] = loadArt(fopen("Frame15.txt", "r"));
	ripHead[15] = loadArt(fopen("Frame16.txt", "r"));
	ripHead[16] = loadArt(fopen("Frame17.txt", "r"));
	ripHead[17] = loadArt(fopen("Frame18.txt", "r"));
	ripHead[18] = loadArt(fopen("Frame19.txt", "r"));
	ripHead[19] = loadArt(fopen("Frame20.txt", "r"));
	ripHead[20] = loadArt(fopen("Frame21.txt", "r"));
	ripHead[21] = loadArt(fopen("Frame22.txt", "r"));
	ripHead[22] = loadArt(fopen("Frame23.txt", "r"));
	ripHead[23] = loadArt(fopen("Frame24.txt", "r"));
	ripHead[24] = loadArt(fopen("Frame25.txt", "r"));
	ripHead[25] = loadArt(fopen("Frame26.txt", "r"));
	ripHead[26] = loadArt(fopen("Frame27.txt", "r"));


	shopKeeperFaces[0] = loadArt(fopen("Shop_n.txt", "r"));
	shopKeeperFaces[1] = loadArt(fopen("Shop_h.txt", "r"));
	shopKeeperFaces[2] = loadArt(fopen("Shop_s.txt", "r"));

	storeman = NULL;

	weapons[0] = initWeapon("Empty", 0.0, 0.0, 0.0, 1.0, 100, 1, "Nothing to see here", NULL, 0);
	weapons[0]->picture = loadArt(fopen("Unknown.txt", "r"));
	weapons[1] = initWeapon("Wooden Sword", 1.0, 1.5, 0.85, 1.15, 90, 1, "The strongest of all wooden swords", NULL, 200);
	weapons[1]->picture = loadArt(fopen("Wsword.txt", "r"));
	weapons[2] = initWeapon("Fire Rune", 2.0, 1.4, 0.9, 1.1, 70, 0, "Kindle your flame", NULL, 300);
	weapons[2]->picture = loadArt(fopen("Firune.txt", "r"));
	weapons[3] = initWeapon("Wood Club", 3.0, 1.0, 0.8, 1.2, 80, 1, "Politics is the skilled use of blunt objects", NULL, 500);
	weapons[3]->picture = loadArt(fopen("Wclub.txt", "r"));
	weapons[4] = initWeapon("Chipped Dagger", -1.0, 1.1, 0.95, 1.05, 75, 1, "Excellent for spreading butter", NULL, 100);
	weapons[4]->picture = loadArt(fopen("Cdagger.txt", "r"));
	weapons[5] = initWeapon("Lightning Rune", 2.0, 1.4, 0.9, 1.1, 70, 0, "ZZZZZP", NULL, 300);
	weapons[5]->picture = loadArt(fopen("Lrune.txt", "r"));
	weapons[6] = initWeapon("Frost Rune", 2.0, 1.4, 0.9, 1.1, 70, 0, "Death is a dish best served cold", NULL, 300);
	weapons[6]->picture = loadArt(fopen("Frrune.txt", "r"));
	weapons[7] = initWeapon("Great Sword", 5.0, 1.3, .6, 1.2, 60, 1, "Size Matters.", NULL, 1000);
	weapons[7]->picture = loadArt(fopen("Gsword.txt", "r"));
	weapons[8] = initWeapon("Steel Sword", 2.0, 1.75, .85, 1.15, 90, 1, "Slay your foes!", NULL, 750);
	weapons[8]->picture = loadArt(fopen("Ssword.txt", "r"));
	weapons[9] = initWeapon("Steel Dagger", 0, 1.55, .9, 1.1, 80, 1, "Great for stabbing!", NULL, 600);
	weapons[9]->picture = loadArt(fopen("Sdagger.txt", "r"));

	potions[0] = initPotion("Healing Potion", 0, 5, 0, 0, 0, 0, 0, 0, "A Simple Healing Potion", "Potion.txt", 50);
	potions[0]->picture = loadArt(fopen("Potion.txt", "r"));
	potions[1] = initPotion("Defense Potion", 0, 0, 0, 2, 0, 0, 0, 0, "Increases your defense", "Potion.txt", 200);
	potions[1]->picture = loadArt(fopen("Potion.txt", "r"));
	potions[2] = initPotion("Attack Potion", 0, 0, 3, 0, 0, 0, 0, 0, "Increases your attack", "Potion.txt", 200);
	potions[2]->picture = loadArt(fopen("Potion.txt", "r"));
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

		
		addItem(mainChar, potions[0], 3, NULL);
		initPlayerPosition(mainChar);
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
	int i, j, k;
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
				enemies[i] = lv1_pick_monster(user->BATTLES, (rand() % 4));
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
	int i, j, k;
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

			for (j = 0; en[j] != NULL && j < 3; j++){
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
				user->ATK += 2;
				user->ACC += 1;
				user->HP += 2;
				user->MAXHP += 2;
				user->DEF += 1;
				user->MATK += 1;
				user->MDEF += 1;
				user->LCK += 1;
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

void initPlayerPosition(Player user)
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

	for (i = 0; i < 20; i++){
		for (j = 0; j < 80; j++)
			screen[i][j] = ' ';
	}

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
		for (i = 0; characters[enemyIndex][i] != NULL && i < 14; i++){
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


	for (i = 0; playerSprite[i] != NULL && i < 15; i++){
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

char** loadArt(FILE* fp){
	int i, j, k, l, m;
	char** temp;
	char tempChar[80];

	if (fp == NULL)
		printf("Not");

	i = 0;
	while (fscanf(fp, "%s") != EOF)
		i++;

	rewind(fp);

	temp = malloc(sizeof(char*) * 20);


	j = 0;

	while (j <= i && j<20){

		temp[j] = malloc(80 * sizeof(char));
		for (m = 0; m < 80; m++)
			temp[j][m] = '\0';
		
		fscanf(fp, "%78[^\n]", temp[j]);
		fscanf(fp, "%c");

		//fgets(temp[j], 78, fp);
		j++;
	}
	if (j < 20){
		temp[j] = NULL;
		j++;
	}

	return temp;
}

WeaponPtr initWeapon(char* name, double weaponMod, double weaponMult, double attackModMin, double attackModMax, double AccMod, int isPhysical, char* DESCRIPTION, char* fileName, int price){
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
			while (enemies[i] != NULL && i < 3){
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
				itemBox(user, tempItem, &exit, &removedItem);
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

void itemBox(Player user, ItemPtr it, int* exit, int* removedItem){
	char* tempchar = malloc(sizeof(char) * 64);
	int cursor[3];
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
		if (it->POTION->ACCRAISE != 0){
			sprintf(tempchar, "Accuracy: +%d   ", it->POTION->ACCRAISE);
			for (j = 0; j < strlen(tempchar); j++){
				screen[3 + i][j + 41] = tempchar[j];
				i++;
			}

		}
		if (it->POTION->ATKRAISE != 0){
			sprintf(tempchar, "Attack: +%d   ", it->POTION->ATKRAISE);
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
		if (it->WEAPON->weaponMod != 0){
			sprintf(tempchar, "Attack MOD: %g", it->WEAPON->weaponMod);
			for (j = 0; j < strlen(tempchar); j++){
				screen[3 + i][j + 41] = tempchar[j];

			}
			i++;
		}
		if (it->WEAPON->weaponMult != 0){
			sprintf(tempchar, "Attack Mult: %g", it->WEAPON->weaponMult);
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
		if (key_code == 'd' && (cursor[1] < 42)){
			if (!(cursor[0]>13))
			{
				screen[cursor[0]][cursor[1]] = ' ';
				cursor[1] += 10;
				cursor[2] ++;
			}
		}
		if (key_code == 's' && cursor[0] < 15){
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
				useItem(user, it);
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

PotionPtr initPotion(char* NAME, int MAXHPRAISE, int HPRAISE, int ATKRAISE, int DEFRAISE, int MATKRAISE, int MDEFRAISE, int ACCRAISE, int LCKRAISE, char* DESCRIPTION, char* fileName, int price){
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
		User->MAXHP += it->POTION->MAXHPRAISE;
		if (User->HP == User->MAXHP && it->POTION->HPRAISE > 0){
			printf("You are already at max health\n");
			printf("Press enter to continue...\n");
			clear_buffer();
			return;
		}
		User->HP += it->POTION->HPRAISE;
		while (User->HP > User->MAXHP)
			User->HP--;
		User->LCK += it->POTION->LCKRAISE;
		User->MATK += it->POTION->MATKRAISE;
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


		
	}
	if (it->QUANTITY > 1)
		it->QUANTITY--;
	else
		removeItem(User, 1, it);
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

	sprintf(temp, "%s", user->NAME);
	for (j = 0; j < strlen(temp); j++)
		screen[2][j + 20] = temp[j];
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
		sprintf(temp, "Rogue", user->CLASS);
		break;
	}
	for (j = 0; j < strlen(temp); j++)
		screen[3][j + 20] = temp[j];
	updateScreen();
	Sleep(100);

	sprintf(temp, "Attack: %d", user->ATK);
	for (j = 0; j < strlen(temp); j++)
		screen[4][j + 30] = temp[j];
	updateScreen();
	Sleep(100);

	sprintf(temp, "Defense: %d", user->DEF);
	for (j = 0; j < strlen(temp); j++)
		screen[5][j + 30] = temp[j];
	updateScreen();
	Sleep(100);

	sprintf(temp, "Accuracy: %d", user->ACC);
	for (j = 0; j < strlen(temp); j++)
		screen[6][j + 30] = temp[j];
	updateScreen();
	Sleep(100);

	sprintf(temp, "Max HP: %d", user->MAXHP);
	for (j = 0; j < strlen(temp); j++)
		screen[7][j + 30] = temp[j];
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
	int i, j;
	printf("Saving...\n\n");


	fp = fopen("Save.s", "w");

	fprintf(fp, "%s\n", user->NAME);

	fprintf(fp, "%d\n", user->CLASS);
	fprintf(fp, "%d\n", user->ATK);
	fprintf(fp, "%d\n", user->DEF);
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
	int loadInt, tempSize, loadInt2;
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
		fscanf(fp, "%s%*c", loadChar);
		if (strcmp(loadChar, "Potion", 1) == 0){
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


	if (en->HP < 0)
		en->HP = 0;
	sprintf(temp, "Enemy Hp %d/%d", en->HP, en->MAXHP);
	for (i = 0; i < strlen(temp); i++)
		screen[0][i + 10] = temp[i];
	j = 0;

	for (i = 0; i <= (((double)en->HP * 100) / ((double)en->MAXHP * 10)) * 4; i++){

		if (i % 2 == 1)
			screen[2][j + 10] = 177;
		else{
			screen[2][j + 10] = 219;
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
	if (user->HP < 0)
		user->HP = 0;
	sprintf(temp, "Player Hp %d/%d", user->HP, user->MAXHP);
	for (i = 0; i < strlen(temp); i++)
		screen[16][i + 20] = temp[i];
	j = 0;

	for (i = 0; i <= (((double)user->HP * 100) / ((double)user->MAXHP * 10)) * 4; i++){

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
		itm = (rand() % (weaponSize - 2)) + 1;
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
	shopkeeper->shopkeeperFace = 0;

	shopkeeper->INVENTORY = malloc(sizeof(Inventory));
	shopkeeper->INVENTORY->size = 0;

	for (i = 0; i < potionsSize && i<3; i++)
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

		for (i = 0; shopKeeperFaces[shopkeeper->shopkeeperFace][i] != NULL && i < 20; i++){
			for (j = 0; shopKeeperFaces[shopkeeper->shopkeeperFace][i][j] != NULL && j < 80; j++)
				screen[i][j + 5] = shopKeeperFaces[shopkeeper->shopkeeperFace][i][j];
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
		sprintf(temp, "Exit");
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
					shopkeeper->shopkeeperFace = 1;
					break;
				case 1:
					Sell(user, shopkeeper);
					shopkeeper->shopkeeperFace = 2;
					break;
				case 2:
					shopkeeper->shopkeeperFace = 0;
					shopTalk(user, shopkeeper);
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
				sellBox(user, shopkeeper, tempItem);
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

void buyBox(Player user, SalesMan shopkeeper, ItemPtr it){
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
				if (toBuy > 0){
					if (shopkeeper->shopkeeperFace == 2)
						shopkeeper->shopkeeperFace = 0;
					else
						shopkeeper->shopkeeperFace == 1;
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
							addItem(user, NULL, toBuy, weapons[it->WEAPON->index]);
							removeItemShop(shopkeeper, toBuy, it);
						}
						else{
							printf("Not enough currency\n");
							printf("Press enter to continue...");
							getch();
						}
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

		sprintf(tempchar, "Sell Price: %d", (int)ceil(it->POTION->price / 2.0));
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
		sprintf(tempchar, "Sell Price: %d", (int)ceil(it->WEAPON->price*(2.0 / 3.0)));
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
					if (shopkeeper->shopkeeperFace == 1)
						shopkeeper->shopkeeperFace = 0;
					else
						shopkeeper->shopkeeperFace == 2;
					do{
						printf("How many would you like to sell?: ");
						while (scanf("%d", &toSell) == 0)
							clear_buffer();
					} while (toSell > it->QUANTITY && toSell < 0);
				}
				else if (it->QUANTITY == 1)
					toSell = 1;
				if (toSell > 0){
					if (it->POTION != NULL){

						user->CURRENCY += (int)ceil(it->POTION->price / 2.0 * toSell);
						addItemShop(shopkeeper, potions[it->POTION->index], toSell, NULL);
						removeItem(user, toSell, it);
					}
					else if (it->WEAPON != NULL){
						user->CURRENCY += (int)ceil(it->WEAPON->price*(2.0 / 3.0)*toSell);
						addItemShop(shopkeeper, NULL, toSell, weapons[it->WEAPON->index]);
						removeItem(user, toSell, it);
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
	int i, j, k;
	int enemy_level = 20;
	int key_code = 0;
	Enemy boss = malloc(sizeof(EnemySize));
	boss->NAME = "A Cognate Pig Sloth";

	boss->index = 4;
	boss->MAXHP = 100 + (.2*enemy_level);
	boss->ATK = 15 + (.2*enemy_level);
	boss->DEF = 15 + (.2*enemy_level);
	boss->MATK = 10 + (.2*enemy_level);
	boss->MDEF = 6 + (.2*enemy_level);
	boss->ACC = 85;
	boss->LCK = 20 + (.2*enemy_level);
	boss->HP = 100 + (.2*enemy_level);
	boss->WMOD = 1.3;
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

	for (k = 0; k < 7; k++){
		for (i = 0; i < 20; i++){
			for (j = 0; j < 80; j++){

				if (k % 2 == 0){
					if (screen[i][j] == ' ')
						screen[i][j] = '*';
				}

				if (k % 2 == 1){
					if (screen[i][j] == '*')
						screen[i][j] = ' ';
				}

			}


		}


		updateScreen();
		Sleep(100);
	}
	addAnimation(boxes, 0, 0);


	for (i = 0; i < 20; i++){
		for (j = 0; j < 80; j++)
			screen[i][j] = ' ';
	}





	while (offsetX < maxOffset){
		for (i = 0; characters[enemyIndex][i] != NULL && i < 14; i++){
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

	for (k = 0; k < 19; k++){
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
		else if (k == 12){
			sprintf(temp, "Goodbye... Brot");
			for (i = 0; i < strlen(temp); i++){
				screen[13][i + 12] = temp[i];
				updateScreen();
				if (i == 7 || i == 8 || i == 9)
					Sleep(300);
				else if (i != strlen(temp)-1)
					Sleep(150);
					
				
			}
			
		}
		else if (k == 13){
			sprintf(temp, "Goodbye... Brot");
			for (i = 0; i < strlen(temp); i++)
				screen[13][i + 12] = temp[i];
			updateScreen();
			Sleep(600);
			screen[13][15 + 13] = '.';
			updateScreen();
			Sleep(200);
			screen[13][15 + 14] = '.';
			updateScreen();
			Sleep(1000);
		}
		else
			Sleep(200);

	}


	while (!kbhit())
	{
		k = rand() % 4 + 19;
		for (i = 0; i < 20; i++){
			for (j = 0; j < 80; j++)
				screen[i][j] = ' ';
		}
		for (i = 0; ripHead[k][i] != NULL && i < 20; i++){
			for (j = 0; ripHead[k][i][j] != NULL && j < 78; j++){
				screen[i][j] = ripHead[k][i][j];
			}
		}
		Sleep(200);
		updateScreen();
		printf("Press any key to continue...");
	}
	
	
	for (k = 20; k < 27;k++){
		for (i = 0; i < 20; i++){
			for (j = 0; j < 80; j++)
				screen[i][j] = ' ';
		}
		for (i = 0; ripHead[k][i] != NULL && i < 20; i++){
			for (j = 0; ripHead[k][i][j] != NULL && j < 78; j++){
				screen[i][j] = ripHead[k][i][j];
			}
		}
		Sleep(200);
		updateScreen();
	}
	
	maxOffset = 33;
	offsetX = 0;
	enemyIndex = 6;

	while (offsetX <= maxOffset){
		for (i = 0; i < 20; i++){
			for (j = 0; j < 80; j++)
				screen[i][j] = ' ';
		}
		for (i = 0; characters[enemyIndex][i] != NULL && i < 14; i++){
			for (j = 0; characters[enemyIndex][i][j] != NULL && i < 78; j++){
				if (characters[enemyIndex][i][j] != NULL && characters[enemyIndex][i][j] != NULL != '\n' && characters[enemyIndex][i][j] != ' ')
					screen[i][j + offsetX] = characters[enemyIndex][i][j];

			}


		}
		Sleep(20);
		updateScreen();
		offsetX++;
	}

	for (i = 0; playerSprite[i] != NULL && i < 10; i++){
		for (j = 0; playerSprite[i][j] != NULL && j < 78; j++){
			if (playerSprite[i][j] != NULL && playerSprite[i][j] != NULL != '\n' && playerSprite[i][j] != ' ')
				screen[i + 10][j] = playerSprite[i][j];

		}


	}



	


	
	for (i = 0; characters[enemyIndex][i] != NULL && i < 20; i++){
		for (j = 0; characters[enemyIndex][i][j] != NULL && i < 78; j++){
			if (characters[enemyIndex][i][j] != NULL && characters[enemyIndex][i][j] != NULL != '\n' && characters[enemyIndex][i][j] != ' ')
				screen[i][j + maxOffset] = characters[enemyIndex][i][j];

		}

	}
	updateScreen();
	Sleep(1000);
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
	Sleep(1000);
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

	for (i = 0; i < 10; i++)
		screen[0][i] = ' ';
	for (i = 0; i < 10; i++)
		screen[2][i] = ' ';

	updateScreen();

	encounter(en, user, screen);

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

	sprintf(temp, "This is what you deserve for killing my brother!");
	for (i = 0; i < strlen(temp); i++){
		screen[13][i + 15] = temp[i];
		updateScreen();
		Sleep(20);
	}
	Sleep(1500);
	sprintf(temp, "..How...did...you...");
	for (i = 0; i < 7; i++){
		screen[4][i + 3] = temp[i];
		updateScreen();
		Sleep(30);
	}

	Sleep(500);

	
	for (; i < 13; i++){
		screen[4][i + 3] = temp[i];
		updateScreen();
		Sleep(80);
	}
	Sleep(800);
	for (; i < strlen(temp); i++){
		screen[4][i + 3] = temp[i];
		updateScreen();
		Sleep(150);
	}
	Sleep(1000);

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

	for (j = 32; j < 80; j++){
		screen[5][j] = 219;
		updateScreen();
		Sleep(1);
	}
	Sleep(500);
	for (i = 0; i < 2; i++){
		for (j = 30; j < 80; j++){
			screen[5][j] = ' ';
			
		}
		updateScreen();
		Sleep(500);
		for (j = 30; j < 80; j++){
			screen[5][j] = 219;
		}
		updateScreen();
		Sleep(500);
	}

	for (j = 30; j < 80; j++)
		screen[5][j] = ' ';
	updateScreen();
	Sleep(1000);
	for (k = 0; k < 10; k++){
		for (i = 5+k; characters[enemyIndex][i] != NULL && i < 15; i++){
			for (j = 0; characters[enemyIndex][i][j] != NULL && j < 80; j++){
				if (characters[enemyIndex][i][j] != NULL && characters[enemyIndex][i][j] != NULL != '\n' && characters[enemyIndex][i][j] != ' ')
					screen[i+k][j + maxOffset] = characters[enemyIndex][i][j];
				
				screen[k+5][j + maxOffset] = ' ';
				
			}
			
			Sleep(20);

		}
		updateScreen();
	}
	
		for (i = 5 ; i < 20; i++){
			for (j = 30;  j < 80; j++){
				screen[i][j] = ' ';
			}
			Sleep(20);
			updateScreen();
		}
		

		Sleep(2000);
	printf("Press enter to continue...");
	clear_buffer();
	

	user->isInBattle = 0;

	endGame(user);
}

void shopTalk(Player user, SalesMan shoppkeeper){
	int i, j, k;
	char temp[80];
	int key_code = 0;
	int cursor[3];

	for (i = 0; i < 20; i++){
		for (j = 0; j < 80; j++)
			screen[i][j] = ' ';
	}

	sprintf(temp, "What would you like to ask me?");
	for (i = 0; i < strlen(temp); i++)
	{
		screen[2][i + 15] = temp[i];
	}
	sprintf(temp, "What weapon should I get?", user->NAME);
	for (i = 0; i < strlen(temp); i++)
	{
		screen[4][i + 15] = temp[i];
	}
	sprintf(temp, "I need information", user->NAME);
	for (i = 0; i < strlen(temp); i++)
	{
		screen[6][i + 15] = temp[i];
	}
	

	cursor[0] = 4;
	cursor[1] = 14;
	cursor[2] = 0;
	while (key_code != 13){
		key_code = 0;


		screen[cursor[0]][cursor[1]] = 219;

		updateScreen();


		key_code = getch();

		if (key_code == 'w' && cursor[2] > 0){
			screen[cursor[0]][cursor[1]] = ' ';
			cursor[0] -= 2;
			cursor[2] --;
		}
		if (key_code == 's' && cursor[2] < 1){
			screen[cursor[0]][cursor[1]] = ' ';
			cursor[0] += 2;
			cursor[2] ++;
		}
		if (key_code == 13){
			switch (cursor[2]){
			case 0:
				printf("Alright, now I'm going to ask you some personal question, please answer honestly\n");
				printf("Press enter to continue...");
				getch();
				readQuestion(initSpeech());
				break;
			case 1:
				readQuestion(initSpeech2());
				break;
			}
			screen[cursor[0]][cursor[1]] = 219;
		}

		updateScreen();
	}
}

SpeechNodePtr addRoot(SpeechBinTreePtr tree, char* question, char* leftAnswer, char* rightAnswer){
	SpeechDataPtr the_data = malloc(sizeof(SpeechData));

	the_data->question = question;
	the_data->leftAnswer = leftAnswer;
	the_data->rightAnswer = rightAnswer;

	tree->root = makeNode(the_data);
	return tree->root;
}

SpeechNodePtr addChild(SpeechNodePtr parent, int leftOrRightChild,char* question, char* leftAnswer, char* rightAnswer){
	SpeechNodePtr temp;
	SpeechDataPtr the_data = malloc(sizeof(SpeechData));

	the_data->question = question;
	the_data->leftAnswer = leftAnswer;
	the_data->rightAnswer = rightAnswer;

	temp = makeNode(the_data);

	if (leftOrRightChild == 1){
		parent->right = temp;
	}
	else if (leftOrRightChild == -1){
		parent->left = temp;
	}

	return temp;
}

SpeechNodePtr makeNode(SpeechDataPtr the_data){
	SpeechNodePtr np = malloc(sizeof(SpeechNode));
	/*np->data = malloc(sizeof(SpeechData));
	np->data->question = the_data->question;
	np->data->leftAnswer = the_data->leftAnswer;
	np->data->rightAnswer = the_data->rightAnswer;*/
	np->data = the_data;
	np->left = NULL;
	np->right = NULL;

	return np;
}

void readQuestion(SpeechBinTreePtr speech){
	int i, j, k;
	int key_code = 0;
	int cursor[3];
	SpeechNodePtr temp = speech->root;

	

	for (k = 0; k < 4;k++){
		key_code = 0;
		for (i = 0; i < 20; i++){
			for (j = 0; j < 80; j++)
				screen[i][j] = ' ';
		}

		updateScreen();

		for (i = 0; i < 80 && temp->data->question[i] != NULL; i++)
		{
			screen[2][i] = temp->data->question[i];
			updateScreen();
			Sleep(20);
		}
		
		for (i = 0; i < 80 && temp->data->leftAnswer[i] != NULL; i++)
		{
			screen[4][i + 15] = temp->data->leftAnswer[i];
		}

		for (i = 0; i < 80 && temp->data->rightAnswer[i] != NULL; i++)
		{
			screen[6][i + 15] = temp->data->rightAnswer[i];
		}


		cursor[0] = 4;
		cursor[1] = 14;
		cursor[2] = 0;
		while (key_code != 13){
			key_code = 0;


			screen[cursor[0]][cursor[1]] = 219;

			updateScreen();


			key_code = getch();

			if (key_code == 'w' && cursor[2] > 0){
				screen[cursor[0]][cursor[1]] = ' ';
				cursor[0] -= 2;
				cursor[2] --;
			}
			if (key_code == 's' && cursor[2] < 1){
				screen[cursor[0]][cursor[1]] = ' ';
				cursor[0] += 2;
				cursor[2] ++;
			}
			if (key_code == 13){
				switch (cursor[2]){
				case 0:
					temp = temp->left;
					break;
				case 1:
					temp = temp->right;
					break;
				}
				screen[cursor[0]][cursor[1]] = 219;
			}

			updateScreen();


		}
	}


}

SpeechBinTreePtr initSpeech(){
	SpeechBinTreePtr temp = malloc(sizeof(SpeechBinTree));
	SpeechNodePtr tempSpeech;


	tempSpeech = addRoot(temp, "You find a 100 dollar bill on the ground, what do you do?", "Pick it up, it belongs to me", "Leave it there, its not mine");
	tempSpeech = addChild(tempSpeech, 1, "You see a kid getting bullied at school, what do you do?", "Confront the bullies", "Walk away quickly");
	tempSpeech = addChild(tempSpeech, 1, "You are invited to a party, how do you respond?", "No thanks, I'm not into parties", "YES!");
	addChild(tempSpeech, 1, "I would recommend a Lightning Rune to compliment your quirky personality", "Thanks!", "Agdsagsag");
	addChild(tempSpeech, -1, "I would recommend a Steel Dagger to compliment your timid personality", "Okay, I guess", "I don't think that is correct, in my opinion");

	tempSpeech = temp->root;
	tempSpeech = addChild(tempSpeech, -1, "You come across a homeless man on the street, he needs money. What do you do?", "Give him the 100 dollar bill you found", "Nothing, he looks alright to me");
	tempSpeech = addChild(tempSpeech, -1, "You didn't study for this test what do you do?", "Take a little peek at my neighbors paper", "I would rather have a poor grade than no dignity");
	addChild(tempSpeech, 1, "I would recommend a Great Sword to compliment your chivalrous personality", "Thank you sir", "I am grateful for your services");
	addChild(tempSpeech, -1, "I would recommend a Chipped Dagger to compliment your selfish personality", "Wow...", "Can I have it for free?");

	tempSpeech = temp->root->right;

	tempSpeech = addChild(tempSpeech, -1, "Someone mistakes you for Guy Fieri, what do you do?", "Welcome to flavor town", "Who?");
	addChild(tempSpeech, 1, "I would recommend a Wooden Club to compliment your uncultured personality", "Thanks", "What?");
	addChild(tempSpeech, -1, "I would recommend a Fire Rune to compliment your spicy personality", "Some people are just born to cook and talk", "I am a filthy liar");

	tempSpeech = temp->root->left;
	tempSpeech = addChild(tempSpeech, 1, "Do you like memes?", "Absolutely!", "Memes?");
	addChild(tempSpeech, 1, "You are lucky", "What?", "I guess I am");
	addChild(tempSpeech, -1, "I would recommend Quiting The Game to compliment your horrible personality", "Wot", "But my memes...");

	return temp;
}

SpeechBinTreePtr initSpeech2(){
	SpeechBinTreePtr temp = malloc(sizeof(SpeechBinTree));
	SpeechNodePtr tempSpeech;


	tempSpeech = addRoot(temp, "What do you want to hear?", "Give me some rumors please", "Can I have some tips?");
	tempSpeech = addChild(tempSpeech, 1, "Sure thing, what kind of tip do you want?", "Weapons", "Gameplay");
	tempSpeech = addChild(tempSpeech, 1, "Did you know enemies level up after each battle?", "No I didn't", "Yes thats common knowledge");
	addChild(tempSpeech, 1, "Oh, well I guess you know how to play this game already", "Yea...", "Don't be so rude");
	addChild(tempSpeech, -1, "Great! I'm so great, aren't I?", "I guess...", "Please don't speak to me again");

	tempSpeech = temp->root;
	tempSpeech = addChild(tempSpeech, -1, "Alright, do you want to hear about your brother?", "Please tell me!", "No, thats boring");
	tempSpeech = addChild(tempSpeech, -1, "Well, I heard that a OCT took your brother and is holding him captive", "How do I get him!?", "Oh wow, thanks");
	addChild(tempSpeech, 1, "No problem, come visit anytime", "Thank you!", "You are very helpful");
	addChild(tempSpeech, -1, "I've heard that you have to prove your worth in combat, and the monster will reveal itself", "Wow", "Thank you!");

	tempSpeech = temp->root->right;

	tempSpeech = addChild(tempSpeech, -1, "You need a good balanced weapon that compliments your stats", "Well thats obvious...", "Thanks!");
	addChild(tempSpeech, 1, "Well I didn't ask for your opinion", "Oh", "Fine");
	addChild(tempSpeech, -1, "No problem, have a nice day", "You too!", "You're the best");

	tempSpeech = temp->root->left;
	tempSpeech = addChild(tempSpeech, 1, "Well, did you know that you level up with each battle you complete?", "Yup", "No");
	addChild(tempSpeech, 1, "You're welcome for the tip", "Thank you", "Have a nice day");
	addChild(tempSpeech, -1, "Well then I guess you can just leave", "Oh...", "I didn't like you anyways");

	return temp;
}

void endGame(Player user){
	int i, j, k;
	char temp[64];

	for (i = 0; i < 20; i++){
		for (j = 0; j < 80; j++){
			if (i % 2 == 0)
				screen[i][j] = '*';
			else
				screen[i][j] = ' ';
		}
		Sleep(50);
		updateScreen();
	}
	for (j = 0; j < 80; j++){
		for (i = 0; i < 20; i++)
				screen[i][j] = ' ';
		Sleep(1);
		updateScreen();
	}

	sprintf(temp, "Congratulations winner!");
	for (i = 0; i < strlen(temp); i++){
		screen[5][i + 30] = temp[i];
		updateScreen();
		Sleep(20);
	}

	Sleep(500);
	while (!kbhit()){
		sprintf(temp, "Congratulations winner!");
		for (i = 0; i < strlen(temp); i++)
			screen[5][i + 30] = temp[i];
		updateScreen();
		Sleep(1000);
		for (i = 0; i < strlen(temp); i++)
			screen[5][i + 30] = ' ';
		updateScreen();
		Sleep(1000);
	}

	exit(1);
}

void gameOver(Player user){
	int i, j;
	char temp[64];
	int cursor[3];
	int key_code = 0;

	free(user->INVENTORY);
	for (i = 0; i < 3; i++)
		enemies[i] = NULL;

	user->INVENTORY = malloc(sizeof(Inventory));
	user->INVENTORY->head = malloc(sizeof(Item));
	user->INVENTORY->head = NULL;
	user->INVENTORY->size = 0;

	for (i = 0; i < 19; i++){
		for (j = 0; j < 80; j++){
			if (screen[i][j] != ' ')
				screen[i + 1][j] = screen[i][j];
				screen[i][j] = ' ';
		}
		Sleep(50);
		updateScreen();
	}
	for (j = 0; j < 80; j++)
		screen[20][j] = ' ';
	Sleep(200);

	sprintf(temp, "Game over, you won %d battles",user->BATTLES);
	for (i = 0; i < strlen(temp); i++){
		screen[5][i + 20] = temp[i];
		updateScreen();
		Sleep(20);
	}

	sprintf(temp, "Load");
	for (j = 0; j < strlen(temp); j++){
		screen[10][j + 31] = temp[j];
	}
	sprintf(temp, "Quit");
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
				loadGame(user);
				main(NULL,NULL);
				break;
			case 1:
				exit(1);
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

