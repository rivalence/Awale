#include <stdio.h>
#include <stdlib.h>
#define DEPTHMAX 12

typedef struct {
int cells_player[8]; // each cell contains a certain number of seeds
int cells_computer[8];
int computer_play; // boolean true if the computer has to play and false otherwise
int seeds_player; // seeds taken by the player
int seeds_computer; // seeds taken by the computer
char name[20];
int debut;
} Position;

int minMaxValue(Position*, int , int, int); //Valeur max calculée
int finalPosition(Position*, int);
int searchMax(int*, int);
int searchMin(int*, int);
int playMove(Position*, Position*, int, int);
int evaluation(Position*, int);
void initialisation(Position*);
void affiche(Position*);
void copieValeur(Position*, Position*);
int getTotalSeeds(Position*);
int verificationCase(int);
void deliberation(Position*);
int etatAffame(Position*);
void vider_buffer(FILE*);
int changeIndex(int);
int getLastIndexPlayer(int);
int calculFavorableIA(Position*, int);
int validMove(Position*, int, int);