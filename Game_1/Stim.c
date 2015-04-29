/*PATCH 1.1 NOTES

Fixes:
Mage reroll works correctly

New Content:
your mom

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <Windows.h>
#include "Stim.h"


int wooden_sword[] = { 0, 0 }, fire_rune[] = { 0, 0 }, wood_club[] = { 0, 0 }, chipped_dagger[] = { 1, 0 };
int potions = 3;
int light_armor[] = { 0 }, heavy_armor[] = { 0 }, dual = 0, isrune = 0, ismace = 0, issword = 0, isdagger = 0;
int ismain_hand = 1, isoff_hand = 0, isarmor = 0, is_magic_main = 0, is_magic_off = 0, is_physical_main = 1, is_physical_off = 0;
int mage_roll = 0, HP, MAX_HP, ATK, DEF, MATK, MDEF, ACC, LCK, iswarrior = 0, isrogue = 0, ismage = 0, iscleric = 0;
double DMG, eDMG, WMOD1, WMOD2, WMULT1, WMULT2;
//calculate damage split

int isskeleton = 0, istroll = 0, isgoblin = 0, isorc = 0;
int eHP, temp_eHP, eATK, eDEF, eMATK, eMDEF, eACC, eLCK, eWMOD, enemy_level = 1, enemy = 1, drop_rarity;
void enemy_combat(Enemy en, Player user);
int drop_roll();
void damage_range(Enemy en, Player user);
void pickup_weapon(int*weapon);
void pickup_potion();
void pickup_misc(int * misc);
//to make different potion types, just make an array and each space will represent a type
Enemy lv1_pick_monster(int levelNum,int r);
void your_attack(Enemy en, Player user);
void enemy_attack(Enemy en, Player user);
void encounter(Enemy en, Player user, char** screen);
void combat(void);
void stance(void);
void mage_reroll(Player user);
//work on meditate
void clear_buffer(void);
void skeleton(void);
void enemy_attacks(Enemy en, Player user);
void goblin(void);
void orc(void);
void troll(void);
void addItem(Player user, PotionPtr POTION, int QUANTITY, WeaponPtr);
void removeItem(Player user, int quantity, ItemPtr it);
int countPotions(Player user);
//int saveGame(Player user);


int main2(int argc, char* argv[])
{
	srand(time(NULL));
	//character_select();
	for (;;)
		menu();
	return 0;
}


int character_select(Player user)
{
	int pick, up = 4, low = 1, i;
	printf("Choose a name for your character: ");
	scanf("%s", user->NAME);
	printf("%s, Choose your character: \n\n", user->NAME);
	printf("(1) Warrior\n(2) Cleric\n(3) Mage\n(4) Rogue\n\n");
	i = scanf("%d", &pick);
	pick = dumb_user(pick, up, low, i);
	user->CLASS = pick;
	user->CURRENCY = 200;
	

	switch (pick)
	{
	case 1:
		printf("You are a Warrior! Your armor gives you strength.\n\n");
		user->HP = 11;
		user->MAXHP = 11;
		user->ATK = 11;
		user->DEF = 13;
		user->MATK = 6;
		user->MDEF = 12;
		user->ACC = 70;
		user->LCK = 8;
		break;
	case 2:
		printf("You are a Cleric! Potions are good to the last drop.\n\n");
		user->HP = 15;
		user->MAXHP = 15;
		user->ATK = 14;
		user->DEF = 9;
		user->MATK = 10;
		user->MDEF = 12;
		user->ACC = 60;
		user->LCK = 10;
		break;
	case 3:
		printf("You are a Mage! Runes are your friends!\n\n");
		user->HP = 10;
		user->MAXHP = 10;
		user->ATK = 7;
		user->DEF = 10;
		user->MATK = 15;
		user->MDEF = 14;
		user->ACC = 80;
		user->LCK = 10;
		break;
	case 4:
		printf("You are a Rogue! Sorry, you can't sneak.\n\n");
		user->HP = 8;
		user->MAXHP = 8;
		user->ATK = 10;
		user->DEF = 10;
		user->MATK = 9;
		user->MDEF = 9;
		user->ACC = 90;
		user->LCK = 20;
		break;
	}
}



Enemy lv1_pick_monster(int levelNum,int r)
{
	Enemy temp = malloc(sizeof(EnemySize));
	temp->NAME = malloc(sizeof(char) * 10);
	temp->Position[0][0] = rand() % 20;
	temp->Position[0][1] = rand() % 80;
	temp->Position[1][0] = temp->Position[0][0];
	temp->Position[1][1] = temp->Position[0][1];
	enemy_level = levelNum;
	temp->LEVEL = enemy_level;
	if (r == 0){
		temp->index = 0;
		temp->MAXHP = 15 + (enemy_level);
		temp->ATK = 6 + (enemy_level);
		temp->DEF = 1 + (enemy_level);
		temp->MATK = 8 + (enemy_level);
		temp->MDEF + (enemy_level);
		temp->ACC = 90;
		temp->LCK = 5 + (enemy_level);
		temp->HP = 15 + (enemy_level);
		temp->WMOD = 1.15;
		temp->NAME = "Goblin";
		temp->drop_rareity = .5;
	}
	else if (r == 1){
		temp->index = 1;
		temp->MAXHP = 17 + (enemy_level);
		temp->ATK = 10 + (enemy_level);
		temp->DEF = 5 + (enemy_level);
		temp->MATK = 10 + (enemy_level);
		temp->MDEF = 5 + (enemy_level);
		temp->ACC = 80;
		temp->LCK = 17 + (enemy_level);
		temp->WMOD = 1.25;
		temp->HP = temp->MAXHP;
		temp->NAME = "Skeleton";
		temp->drop_rareity = 1;
	}

	else if (r == 2){
		temp->index = 2;
		temp->MAXHP = 20 + (enemy_level);
		temp->ATK = 12 + (enemy_level);
		temp->DEF = 6 + (enemy_level);
		temp->MATK = 8 + (enemy_level);
		temp->MDEF = 4 + (enemy_level);
		temp->ACC = 75;
		temp->LCK = 10 + (enemy_level);
		temp->HP = 20 + (enemy_level);
		temp->WMOD = 1.25;
		temp->NAME = "Orc";
		temp->drop_rareity = 1.5;
	}
	else if (r == 3){
		temp->index = 3;
		temp->MAXHP = 25 + (enemy_level);
		temp->ATK = 14 + (enemy_level);
		temp->DEF = 2 + (enemy_level);
		temp->MATK = 10 + (enemy_level);
		temp->MDEF = 6 + (enemy_level);
		temp->ACC = 65;
		temp->LCK = 10 + (enemy_level);
		temp->HP = 25 + (enemy_level);
		temp->WMOD = 1.3;
		temp->NAME = "Troll";
		temp->drop_rareity = 3;
	}
}

void enemy_attack(Enemy en, Player user)
{
	if (en->HP <= 0)
	{
		printf("\n\nYou have slain the monster, but the horde continues in its path of destruction\n\n");
		lv1drops(user);
	}
	else
	{
		switch (enemy)
		{
		case 1:
			enemy_attacks(en, user);
			break;
		}
	}

}
void encounter(Enemy en, Player user, char** screen)
{
	char temp[64];
	char c;
	int i;
	int coins;

	//surpise attack
	for (;;)
	{
		
		hpBars(user, en);
		//fscanf(stdin,"%*[^\n]%*c");
		fgets(temp,64,stdin);
		//clear_buffer();
		updateScreen();
		your_attack(en, user);
		hpBars(user, en);
		enemy_attack(en, user);
		
		if (en->HP <= 0){
			user->BATTLES++;
			updateScreen();
			coins = en->MAXHP*user->LCK*(rand() % 3);
			if (coins > 0){
				printf("Enemy killed, you found %d coins", coins);
				user->CURRENCY += coins;
			}
			else
				printf("Enemy killed", coins);
		
			printf("\n\nPress enter to continue...");
			getch();
			break;
		}
			
		if (user->HP <= 0)
		{
			gameOver(user);
			break;
		}
	}

}

void your_attack(Enemy en, Player user)
{
	int attack, i, up = 3, low = 1;
	printf("\n(1) Basic Attack\n\n");
	damage_range(en,user);
	printf("(2) Inventory\n");
	i = scanf("%d", &attack);
	attack = dumb_user(attack, up, low, i);
	switch (attack)
	{
		// attacks are determined by weapons multiplier: sword with str*.2
		// DMG=(weapon*attack)-defense ifDMG<1, DMG = 1
	case 1:
		combat(en, user);
		break;
	case 2:
		inventoryGraphics(user);
		break;
		//case 3: 
		//break;
	}
	updateScreen();
}

void combat(Enemy en, Player user)
{
	updateScreen();
	//system("cls");
	int roll, loss, DMG;
	double min, max;
	int accuracy;
	min = user->weaponLeft->attackModMin;
	max = user->weaponLeft->attackModMax;
	if (user->weaponLeft->isPhysical==1)
		DMG = (user->ATK + user->weaponLeft->weaponMod)*user->weaponLeft->weaponMult;
	else
		DMG = (user->MATK + user->weaponLeft->weaponMod)*user->weaponLeft->weaponMult;
	min = floor(min*DMG);
	max = ceil(max*DMG);
	//should I incorporate luck?
	//damage range is taking into account DMG as the average damage
	roll = max - min + 1;
	roll = rand() % roll;
	roll += min;
	int r = rand() % 100, luck = floor(110 - (user->LCK*1.2));
	r += 1;
	accuracy = (user->ACC + user->weaponLeft->AccMod)/2;
	if (r > accuracy)
		printf("You miss!\n");
	else
	{
		r = rand() % 100;
		r += 1;
		if (r >= luck)
		{
			printf("\nYou score a critical hit!\n");
			roll*=2;
		}
		//could implement critical modifier on weapons
		if (user->weaponLeft->isPhysical == 1)
			loss = roll - en->DEF;
		else
			loss = roll - en->MDEF;
		if (loss < 1)
			loss = 1;
		en->HP = en->HP - loss;

		printf("You delivered %d damage\n", loss);
		if (r >= luck)
			DMG /= 2;

		if (user->CLASS == 4)
		{
			r = rand() % 100;
			r += LCK*.2 + 1;
			if (r >= 95)
			{
				printf("\nYou have the agility to do something else!\n\n");
				your_attack(en, user);
			}

		}
	}
	Sleep(500);
	printf("Press Enter To Continue...\n");
	getch();
	updateScreen();
}
void clear_buffer(void)
{
	char c;
	
	scanf("%c", &c);
	while (c != '\n')
	{
		scanf("%c", &c);
	}
}
void enemy_combat(Enemy en, Player user)
{
	//figure out enemy ranges
	int max, luck, min, r = rand() % 100;
	r += 1;
	if (en->NAME = "Skeleton")
		max = ceil(en->ATK*1.2), min = floor(en->ATK*.8);
	if (en->NAME == "Goblin")
		max = ceil(en->ATK*1.1), floor(min = en->ATK*.9);
	if (en->NAME == "Orc")
		max = ceil(en->ATK*1.2), min = floor(en->ATK*.9);
	if (en->NAME == "Troll")
		max = ceil(en->ATK*1.3), min = floor(en->ATK * 1);
	int roll = max - min + 1;
	roll = rand() % roll;
	roll += min;
	r = rand() % 100, luck = floor(110 - user->LCK*1.2);
	if (r > en->ACC)
	{
		printf("The enemy missed!\n");
	}
	else
	{
		int loss = ceil(1.0*roll / (.2*user->DEF));
		if (loss < 1)
			loss = 1;
		user->HP = user->HP - loss;
		printf("Enemy delivered %d damage\n", loss);
	}
	Sleep(500);
	printf("Press Enter To Continue...\n");
	getch();
	updateScreen();
}

void enemy_attacks(Enemy en, Player user)
{
	int r = rand() % 100, half_hp = en->HP / 2, crit = 110 - en->LCK*1.2;
	r += 1;
	if (en->HP < half_hp)
	{
		if (en->index == 1)
			printf("\nIt's bones are shaking\n\n");
		else if (en->index == 0)
			printf("\nThe goblin squeals for mercy\n\n");
		else if (en->index == 2)
			printf("\nThe orc coughs up blood\n\n");
		else if (en->index == 3)
			printf("\nThe troll spits out a tooth\n\n");
		else if (en->index == 4)
			printf("\nYou will die just like your weak excuse for a brother!\n\n");
		Sleep(1000);
	}
	en->ATK = en->ATK*en->WMOD;
	if (r >= crit)
	{
		if (en->index == 1)
			printf("\nThe skeleton cackles with glee!\n\n");
		else if (en->index == 0)
			printf("\nThe goblin is giddy\n\n");
		else if (en->index == 2)
			printf("\nThe orc deals a heavy blow!\n\n");
		else if (en->index == 3)
			printf("\nThe troll smashes you\n\n");
		else if (en->index == 4)
			printf("\nI have you now!\n\n");
		en->ATK *= 2;
		Sleep(1000);
	}

	enemy_combat(en, user);
	if (r >= en->LCK)
		en->ATK /= 2;
}
void menu(void)
{
	int select, up = 6, low = 1, i;
	printf("What would you like to do?\n");
	printf("(2)Check your inventory\n(3)Check your stats\n(4)Meditate\n(5)Save\n(6)Quit\n");
	i = scanf("%d", &select);
	select = dumb_user(select, up, low, i);
	switch (select)
	{
	case 1:
		system("cls");
		//encounter(en, user);
		break;
	case 2:
		system("cls");
		//inventory();
		break;
	case 3:
		system("cls");
		stats();
		break;
	case 4:
		system("cls");
		stance();
		break;
	case 5:
		system("cls");
		save();
		break;
	case 6:
		system("cls");
		quit();
		break;
	}
}
void stats()
{
	printf("HP: %d/%d\nATK: %d\nDEF: %d\nMATK: %d\nMDEF: %d\nACC: %d\nLCK: %d\n\n", HP, MAX_HP, ATK, DEF, MATK, MDEF, ACC, LCK);
	printf("Main hand: ");
	main_hand();
	printf("\nOff hand: ");
	off_hand();
	printf("\nArmor: ");
	armor();
	printf("\n\n");
}
void save()
{
	exit(1);
}
void quit()
{
	exit(1);
}
int dumb_user(int select, int upper, int lower, int i)
{
	for (;;)
	{
		if (i != 1)
		{
			printf("\nChoose Wisely\n");
			clear_buffer();
			i = scanf("%d", &select);
		}
		else if (select < lower || select>upper)
		{
			printf("\nChoose Wisely\n");
			clear_buffer();
			i = scanf("%d", &select);
		}
		else
			break;
	}
	return select;
}
void main_hand()
{
	if (wooden_sword[0] == 1)
		printf("Wooden Sword (+0 ATK, 1.5 MOD)");
	if (fire_rune[0] == 1)
		printf("Fire Rune (+2 MATK, 1.2 MOD)");
	if (wood_club[0] == 1)
		printf("Wood Club (+3 ATK, 1 MOD)");
	if (chipped_dagger[0] == 1)
		printf("Chipped Dagger (-1 ATK, 1.1 MOD)");
}
void off_hand()
{
	if (wooden_sword[1] == 1)
		printf("Wooden Sword (+0 ATK, 1.5 MOD)");
	if (fire_rune[1] == 1)
		printf("Fire Rune (+2 MATK, 1.2 MOD)");
	if (wood_club[1] == 1)
		printf("Wood Club (+3 ATK, 1 MOD)");
	if (chipped_dagger[1] == 1)
		printf("Chipped Dagger (-1 ATK, 1.1 MOD)");
}
void armor()
{
	if (light_armor[0] == 1)
		printf("Light Armor (+1 DEF, +2 MDEF,+1 HP,+5 ACC)");
	if (heavy_armor[0] == 1)
		printf("Heavy Armor (+2 DEF, +1 MDEF,+3HP)");
}
int drop_roll()
{
	int r = rand() % 30;
	int bonus = floor(r - 1 + .2*LCK + drop_rarity);
	return bonus;
}

void pickup_weapon(int* weapon)
{
	int i, answer1, answer2, answer3;
	printf("Your main hand: ");
	main_hand();
	printf("\nYour off Hand: ");
	off_hand();
	printf("\nWould you like to pick it up?\n(1) Yes\n(2) No\n");
	i = scanf(" %d", &answer1);
	answer1 = dumb_user(answer1, 2, 1, i);
	if (answer1 == 1)
	{
		if (ismain_hand == 1 && isoff_hand == 1)
		{
			printf("\nWould you like to equip it to your main hand(1) or off hand(2)?\n");
			clear_buffer();
			i = scanf("%d", &answer2);
			answer2 = dumb_user(answer2, 2, 1, i);
			if (answer2 == 1)
			{
				drop_main_weapon();
				weapon[0] = 1;
				ismain_hand = 1;
			}

			else
			{
				drop_off_weapon();
				weapon[1] = 1;
			}

		}
		//use else if () for other drop types				
	}
}
void pickup_potion()
{
	int i, answer1, answer2, answer3;
	printf("\nWould you like to pick it up?\n(1) Yes\n(2) No\n");
	i = scanf(" %d", &answer1);
	answer1 = dumb_user(answer1, 2, 1, i);
	if (answer1 == 1)
	{
		printf("The potion is yours! Huzzah!\n");
		potions++;
	}
}
void pickup_misc(int* misc)
{
	int i, answer1;
	printf("Your armor: ");
	armor();
	printf("\nWould you like to pick it up?\n(1) Yes\n(2) No\n");
	i = scanf(" %d", &answer1);
	answer1 = dumb_user(answer1, 2, 1, i);
	if (answer1 == 1)
	{
		drop_armor();
		misc[0] = 1;
		isarmor = 1;
	}
}
char dumb_user_yn(char answer, int i)
{
	for (;;)
	{
		if (i != 1)
		{
			printf("Choose Wisely\n");
			clear_buffer();
			i = scanf("%c", &answer);
		}
		else if (answer == 'y' || answer == 'Y' || answer == 'n' || answer == 'N')
			break;
		else
		{
			printf("Choose Wisely\n");
			clear_buffer();
			i = scanf("%c", &answer);
		}
	}
	return answer;
}
double calc_dmg()
{

	if (is_physical_main == 1 && is_magic_off == 1)
		DMG = (ATK + WMOD1)*WMULT1 + (MATK + WMOD2)*WMULT2;
	if (is_magic_main == 1 && is_physical_off == 1)
		DMG = (MATK + WMOD1)*WMULT1 + (ATK + WMOD2)*WMULT2;
	if (is_magic_main == 1 && is_magic_off == 1)
		DMG = (MATK + WMOD1)*WMULT1 + (MATK + WMOD2)*WMULT2;
	if (is_physical_main == 1 && is_physical_off == 1)
		DMG = (ATK + WMOD1)*WMULT1 + (ATK + WMOD2)*WMULT2;
	if (is_physical_main == 1 && is_physical_off == 0 && is_magic_main == 0 && is_magic_off == 0)
		DMG = (ATK + WMOD1)*WMULT1;
	if (is_physical_main == 0 && is_physical_off == 1 && is_magic_main == 0 && is_magic_off == 0)
		DMG = (ATK / 2 + WMOD2)*WMULT2;
	if (is_physical_main == 0 && is_physical_off == 0 && is_magic_main == 1 && is_magic_off == 0)
		DMG = (MATK + WMOD1)*WMULT1;
	if (is_physical_main == 0 && is_physical_off == 0 && is_magic_main == 0 && is_magic_off == 1)
		DMG = (MATK / 2 + WMOD2)*WMULT2;
	return DMG;
}
void your_armor()
{
	if (light_armor[0] == 1)
	{
		DEF += 1;
		MDEF += 2;
		MAX_HP += 1;
		ACC += 5;
	}

	if (heavy_armor[0] == 1)
	{
		DEF += 2;
		MDEF += 1;
		MAX_HP += 3;
	}
}
void your_main_weapon()
{
	if (wooden_sword[0] == 1)
	{
		WMOD1 = 0, WMULT1 = 1.5;
		is_magic_main = 0;
		is_physical_main = 1;
		issword = 1;
	}
	if (fire_rune[0] == 1)
	{
		WMOD1 = 2, WMULT1 = 1.2;
		is_magic_main = 1;
		is_physical_main = 0;
		isrune = 1;
	}
	if (wood_club[0] == 1)
	{
		WMOD1 = 3, WMULT1 = 1;
		is_magic_main = 0;
		is_physical_main = 1;
		ismace = 1;
	}
	if (chipped_dagger[0] == 1)
	{
		WMOD1 = -1, WMULT1 = 1.1;
		is_magic_main = 0;
		is_physical_main = 1;
		isdagger = 1;
	}
}
void your_off_weapon()
{
	if (wooden_sword[1] == 1)
	{
		WMOD2 = 0, WMULT2 = 1.5;
		is_magic_off = 0;
		is_physical_off = 1;
		issword = 1;
	}
	if (fire_rune[1] == 1)
	{
		WMOD2 = 2, WMULT2 = 1.2;
		is_magic_off = 1;
		is_physical_off = 0;
		isrune = 1;
	}
	if (wood_club[1] == 1)
	{
		WMOD2 = 3, WMULT2 = 1;
		is_magic_off = 0;
		is_physical_off = 1;
		ismace = 1;
	}
	if (chipped_dagger[1] == 1)
	{
		WMOD2 = -1, WMULT2 = 1.1;
		is_magic_off = 0;
		is_physical_off = 1;
		isdagger = 1;
	}
}
void drop_main_weapon()
{
	if (wooden_sword[0] == 1)
		wooden_sword[0] = 0;
	if (fire_rune[0] == 1)
		fire_rune[0] = 0;
	if (wood_club[0] == 1)
		wood_club[0] = 0;
	if (chipped_dagger[0] == 1)
		chipped_dagger[0] = 0;
}
void drop_off_weapon()
{
	if (wooden_sword[1] == 1)
		wooden_sword[1] = 0;
	if (fire_rune[1] == 1)
		fire_rune[1] = 0;
	if (wood_club[1] == 1)
		wood_club[1] = 0;
	if (chipped_dagger[1] == 1)
		chipped_dagger[1] = 0;
}
void drop_armor()
{
	if (light_armor[0] == 1)
		light_armor[0] = 0;
	if (heavy_armor[0] == 1)
		heavy_armor[0] = 0;
}
void isdual()
{
	if (is_physical_main == 1 && is_magic_off == 1)
		dual = 1;
	if (is_magic_main == 1 && is_physical_off == 1)
		dual = 1;
	if (is_magic_main == 1 && is_magic_off == 1)
		dual = 1;
	if (is_physical_main == 1 && is_physical_off == 1)
		dual = 1;
	if (is_physical_main == 1 && is_physical_off == 0 && is_magic_main == 0 && is_magic_off == 0)
		dual = 0;
	if (is_physical_main == 0 && is_physical_off == 1 && is_magic_main == 0 && is_magic_off == 0)
		dual = 0;
	if (is_physical_main == 0 && is_physical_off == 0 && is_magic_main == 1 && is_magic_off == 0)
		dual = 0;
	if (is_physical_main == 0 && is_physical_off == 0 && is_magic_main == 0 && is_magic_off == 1)
		dual = 0;
	if (dual == 1)
	{
		DMG *= .9;
		ACC *= .8;
	}
	//this might be a huge nerf to accuracy
}

void use_potion()
{
	system("cls");
	if (potions > 0)
	{
		int temp = MAX_HP;
		int heal;
		if (iscleric == 1)
			heal = MAX_HP*.75;
		else
			heal = MAX_HP*.5;
		HP += heal;
		if (HP > temp)
			HP = temp;
		printf("You healed for %d HP!\n", heal);
		potions--;
	}
}
void mage_reroll(Player user)
{
	int i, answer;
	if (user->CLASS == 3)
	{
		clear_buffer();
		printf("\nWould you like to pick it up?\n(1) Yes\n(2) No\n");
		i = scanf(" %d", &answer);
		answer = dumb_user(answer, 2, 1, i);
		mage_roll = 0;
		if (answer == 1)
			lv1drops(user);
	}
}
void stance(void)
{
	int i, answer;
	printf("You take time to ready yourself\n"
		"(1) One Hand a weapon\n(2) Dual Wield your weapons\n(3) Two-hand a weapon\n");
	i = scanf(" %d", &answer);
	answer = dumb_user(answer, 3, 1, i);
	switch (answer)
	{
	case 1:
		
		break;
	case 2:
		isdual();
		if (dual == 0)
			printf("You do not have 2 weapons equipped!\n");
		else
			printf("Two weapons are better than one!\n");
		break;
	case 3:
		break;
	}



	return;
}

void addItem(Player user, PotionPtr POTION, int QUANTITY, WeaponPtr WEAPON){
	ItemPtr temp;
	ItemPtr it = malloc(sizeof(Item));
	int i;

	it->POTION = POTION;
	it->QUANTITY = QUANTITY;
	it->WEAPON = WEAPON;
	it->next = NULL; 
	it->prev = NULL;

	if (user->INVENTORY->size == 0){
		user->INVENTORY->head = it;
		user->INVENTORY->size++;
	}	

	else{
		temp = user->INVENTORY->head;
		for (i = 0; i < user->INVENTORY->size;i++){
			if (it->POTION != NULL && temp->POTION != NULL){
				if (it->POTION->NAME == temp->POTION->NAME){
					temp->QUANTITY+= it->QUANTITY;
					return;
				}
			}
			if (it->WEAPON != NULL && temp->WEAPON != NULL){
				if (it->WEAPON->NAME == temp->WEAPON->NAME){
					temp->QUANTITY+= it->QUANTITY;
					return;
				}
			}
			temp = temp->next;
		}
		temp = user->INVENTORY->head;
		for (i = 1; i < user->INVENTORY->size; i++)
			temp = temp->next;
		it->prev = temp;
		temp->next = it;

		user->INVENTORY->size++;
	}
}

void removeItem(Player user, int quantity, ItemPtr it){


		it->QUANTITY -= quantity;

		if (it->QUANTITY <= 0){
			if (it == user->INVENTORY->head)
				user->INVENTORY->head = it->next;
			else if (it->next == NULL)
				it->prev = NULL;
			else{
				it->prev->next = it->next;
				it->next->prev = it->prev;
			}
			user->INVENTORY->size--;

			free(it);

		}
	
	
}

int countPotions(Player user){
	ItemPtr temp = user->INVENTORY->head;
	int i = 0;
	int j;
	for (j = 0; j < user->INVENTORY->size;j++)
	{
		if (temp->POTION != NULL)
			i+= temp->QUANTITY;

		if (temp->next != NULL)
			temp = temp->next;
	}

	return i;
}
void damage_range(Enemy en,Player user)
{ 
	int accuracy;
	double min, max;
	min = user->weaponLeft->attackModMin;
	max = user->weaponLeft->attackModMax;
	if (user->weaponLeft->isPhysical == 1)
	{
		DMG = (user->ATK + user->weaponLeft->weaponMod)*user->weaponLeft->weaponMult;
		min = floor(min*DMG);
		max = ceil(max*DMG);
		min -= en->DEF;
		max -= en->DEF;
	}
	else if (user->weaponLeft->isPhysical == 0)
	{
		DMG = (user->MATK + user->weaponLeft->weaponMod)*user->weaponLeft->weaponMult;
		min = floor(min*DMG);
		max = ceil(max*DMG);
		min -= en->MDEF;
		max -= en->MDEF;
	}
	printf("Damage: %.0f - %.0f\n", min, max);
	accuracy = (user->ACC + user->weaponLeft->AccMod) / 2;
	printf("Accuracy: %d%%\n", accuracy);
}

void addItemShop(SalesMan user, PotionPtr POTION, int QUANTITY, WeaponPtr WEAPON){
	ItemPtr temp;
	ItemPtr it = malloc(sizeof(Item));
	int i;

	it->POTION = POTION;
	it->QUANTITY = QUANTITY;
	it->WEAPON = WEAPON;
	it->next = NULL;
	it->prev = NULL;

	if (user->INVENTORY->size == 0){
		user->INVENTORY->head = it;
		user->INVENTORY->size++;
	}

	else{
		temp = user->INVENTORY->head;
		for (i = 0; i < user->INVENTORY->size; i++){
			if (it->POTION != NULL && temp->POTION != NULL){
				if (it->POTION->index == temp->POTION->index){
					temp->QUANTITY += it->QUANTITY;
					return;
				}
			}
			if (it->WEAPON != NULL && temp->WEAPON != NULL){
				if (it->WEAPON->index == temp->WEAPON->index){
					temp->QUANTITY += it->QUANTITY;
					return;
				}
			}
			temp = temp->next;
		}
		temp = user->INVENTORY->head;
		for (i = 1; i < user->INVENTORY->size; i++)
			temp = temp->next;
		it->prev = temp;
		temp->next = it;

		user->INVENTORY->size++;
	}
}

void removeItemShop(SalesMan user, int quantity, ItemPtr it){

	it->QUANTITY -= quantity;

	if (it->QUANTITY <= 0){
		if (it == user->INVENTORY->head)
			user->INVENTORY->head = it->next;
		else if (it->next == NULL)
			it->prev = NULL;
		else{
			it->prev->next = it->next;
			it->next->prev = it->prev;
		}
		user->INVENTORY->size--;

		free(it);

	}
}