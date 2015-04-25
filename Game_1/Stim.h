typedef struct enemy{
	int Position[2][2];

	char* NAME;
	int MAXHP;
	int HP;
	int LEVEL;
	int ATK;
	int DEF;
	int MATK;
	int MDEF;
	int ACC;
	int LCK;
	int WMOD;
	int drop_rareity;
}EnemySize, *Enemy;

typedef struct weapon{
	char* NAME;
	double weaponMod;
	double attackModMin;
	double attackModMax;
	double AccMod;
	int isPhysical;
	char* DESCRIPTION;
	char** picture;
}Weapon, *WeaponPtr;

typedef struct potion{
	char* NAME;
	int MAXHPRAISE;
	int HPRAISE;
	int ATKRAISE;
	int DEFRAISE;
	int MATKRAISE;
	int MDEFRAISE;
	int ACCRAISE;
	int LCKRAISE;
	char* DESCRIPTION;
	char** picture;
}Potion, *PotionPtr;

typedef struct item{
	WeaponPtr WEAPON;
	PotionPtr POTION;
	int QUANTITY;
	struct item *next;
	struct item *prev;
}Item, *ItemPtr;

typedef struct inventory{
	int MAXSIZE;
	int size;
	ItemPtr head;
}Inventory, *InventoryPtr;

typedef struct salesman{
	int Position[2][2];
}SalesManSize, *SalesMan;



typedef struct player{
	int Position[2][2];

	char NAME[64];
	int MAXHP;
	int HP;
	int LEVEL;
	int ATK;
	int DEF;
	int MATK;
	int MDEF;
	int ACC;
	int LCK;
	int CURRENCY;
	int CLASS;
	int BATTLES;

	WeaponPtr weaponLeft;
	WeaponPtr weaponRight;

	InventoryPtr INVENTORY;

	int isInBattle;

}PlayerSize, *Player;

typedef struct animation{
	int frameCount;
	int sizeX;
	int sizeY;
	int speed;
	char*** frames;


}Animation, *AnimationPtr;


void warrior(void);
void mage(void);
void cleric(void);
void rogue(void);
int character_select(Player user);
void menu(void);
void stats();
void save();
void quit();
void meditate();
void drop_main_weapon();
void drop_off_weapon();
void drop_armor();
void isdual();
void use_potion();
void damage_range();
void main_hand();
void off_hand();
void armor();
void mage_reroll();
double calc_dmg();
void your_main_weapon();
void your_off_weapon();
void your_armor();
void who_are_you();
int dumb_user(int select, int upper, int lower, int i);
char dumb_user_yn(char answer, int i);

