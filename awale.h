#include <stdio.h>
#include <stdlib.h>

typedef struct {
int cells_player[8]; // each cell contains a certain number of seeds
int cells_computer[8];
int computer_play; // boolean true if the computer has to play and false otherwise
int seeds_player; // seeds taken by the player
int seeds_computer; // seeds taken by the computer
} Position;

int minMaxValue(Position, int , int, int); //Valeur max calculée
int finalPosition(Position, int, int);
int searchMax(int*);
int searchMin(int*);
void playMove(Position, int, int);
int evaluation(int*, int);
Position initialisation(Position);
void affiche();
