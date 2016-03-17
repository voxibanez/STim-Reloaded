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
	int index;
}EnemySize, *Enemy;

typedef struct weapon{
	char* NAME;
	double weaponMod;
	double weaponMult;
	double attackModMin;
	double attackModMax;
	double AccMod;
	int isPhysical;
	char* DESCRIPTION;
	char** picture;
	int index;
	int price;
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
	int index;
	int price;
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

typedef struct speechdata{
	char* question;
	char* leftAnswer;
	char* rightAnswer;
}SpeechData, *SpeechDataPtr;

typedef struct speechnode{
	SpeechDataPtr data;
	struct speechnode * left;
	struct speechnode * right;
} SpeechNode, *SpeechNodePtr;

typedef struct speechTree{
	SpeechNodePtr root;
}SpeechBinTree, *SpeechBinTreePtr;

typedef struct salesman{
	int Position[2][2];
	InventoryPtr INVENTORY;

	SpeechBinTreePtr conversations;
	int shopkeeperFace;
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



int character_select(Player user);
void meditate();
void isdual();
void use_potion();
void damage_range();
double calc_dmg();
void who_are_you();
int choice_user(int select, int upper, int lower, int i);
char user_yn(char answer, int i);
void bossBattleInitiate(Player user);
void bossBattleRoom(Player user);