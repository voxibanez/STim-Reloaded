#include "Stim.h"

int titleScreen(Player user);
void setWindow();
void battleSequence(Enemy en, Player user);

void updateScreen();

void addAnimation(AnimationPtr animate, int x, int y);

void updatePlayerPosition(Player user);

void updateEnemyPosition(Enemy en, Player user);

void initPlayerPosition(Player user);

void titleMusic();

char** loadArt(char* filename);

SalesMan addSalesman(Player user);

void moveSalesman(SalesMan storeman);

void menuGraphics(Player user);

AnimationPtr initAnimation(int frames, int x, int y);

void initPlayer();

WeaponPtr initWeapon(char* name, double weaponMod, double weaponMult, double attackModMin, double attackModMax, double AccMod, int isPhysical, char* DESCRIPTION, char* fileName, int price);

PotionPtr initPotion(char* NAME, int MAXHPRAISE, int HPRAISE, int ATKRAISE, int DEFRAISE, int MATKRAISE, int MDEFRAISE, int ACCRAISE, int LCKRAISE, char* DESCRIPTION, char* fileName, int price);

ItemPtr initItem(PotionPtr POTION, int QUANTITY, WeaponPtr WEAPON);

void itemBox(Player user, ItemPtr it, int* exit, int* removedItem);

void inventoryGraphics(Player user);

void useItem(Player user, ItemPtr it);

void playerStats(Player user);

void findSaveFile(Player user);

void saveGame(Player user);

void loadGame(Player user);

void initGame(Player mainChar);

void hpBars(Player user, Enemy en);

void lv1drops(Player user);

void Shop(Player user, SalesMan shopkeeper);

void Buy(Player user, SalesMan shopkeeper);

void Sell(Player user, SalesMan shopkeeper);

void buyBox(Player user, SalesMan shopkeeper, ItemPtr it);

void sellBox(Player user, SalesMan shopkeeper, ItemPtr it);

void bossBattle(Player user, Enemy en);

void shopTalk(Player user, SalesMan shoppkeeper);

 SpeechNodePtr addChild(SpeechNodePtr parent, int leftOrRightChild, char* question, char* answerLeft, char* answerRight);

 SpeechNodePtr addRoot(SpeechBinTreePtr tree, char* question, char* answerLeft, char* answerRight);

SpeechNodePtr makeNode(SpeechDataPtr the_data);

void readQuestion(SpeechBinTreePtr speech);

SpeechBinTreePtr initSpeech();

void endGame(Player user);

SpeechBinTreePtr initSpeech2();