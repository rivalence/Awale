#include <stdio.h>
#include <stdlib.h>
#include "awale.h"

int main(int argc, char *argv[]){       
Position position;
int best_index, index_choisi;

initialisation(&position);
affiche(&position);
while(1){
        if (position.computer_play){
                printf("Au tour du cpu :\n");
                best_index = minMaxValue(&position, position.computer_play, 1, 10);
                printf("cpu a joué la case numéro %d\n\n", best_index);
                playMove(&position, &position, best_index, position.computer_play);
                affiche(&position);
                printf("\nNombre de graines du cpu : %d\n", position.seeds_computer);
                printf("Nombre de graines du joueur : %d\n\n", position.seeds_player);
                position.computer_play--;
        }
        else{
                printf("Au tour du joueur :");
                scanf("%d",&index_choisi);
                playMove(&position, &position, index_choisi, position.computer_play);
                affiche(&position);
                printf("\nNombre de graines du cpu : %d\n", position.seeds_computer);
                printf("Nombre de graines du joueur : %d\n\n", position.seeds_player);
                position.computer_play++;
        }      
}
}

