#include <stdio.h>
#include <stdlib.h>
#include "awale.h"

int main(int argc, char *argv[]){       
Position position;
int best_index, index_choisi, graines_restantes = 65, affame;

initialisation(&position);
affiche(&position);
printf("Nom du joueur:");
scanf("%s",position.name);
while(graines_restantes>8){
        if (position.computer_play){
                printf("Au tour du cpu :\n");
                best_index = minMaxValue(&position, position.computer_play, 1, DEPTHMAX);
                printf("cpu a joué la case numéro %d\n\n", best_index);
                graines_restantes = playMove(&position, &position, best_index, position.computer_play);
                affiche(&position);
                printf ("\nGraines restantes sur le plateau: %d", graines_restantes);
                printf("\nNombre de graines du cpu : %d\n", position.seeds_computer);
                printf("Nombre de graines du joueur : %d\n\n", position.seeds_player);
                affame = etatAffame(&position);
                if (affame == 0 || affame == 1){
                        graines_restantes = 0;
                        break;
                }
                position.computer_play--;
        }
        else{
                printf("Au tour de %s :", position.name);
                scanf("%d",&index_choisi);        
                index_choisi = verificationCase(index_choisi);           
                if (position.cells_player[index_choisi-1]==0){
                        do
                        {
                                printf("Jouez une case non vide :");
                                scanf("%d",&index_choisi);
                                index_choisi = verificationCase(index_choisi);
                        } while (position.cells_player[index_choisi-1]==0);   
                }
                graines_restantes = playMove(&position, &position, index_choisi-1, position.computer_play);
                affiche(&position);
                printf ("\nGraines restantes sur le plateau: %d", graines_restantes);
                printf("\nNombre de graines du cpu : %d\n", position.seeds_computer);
                printf("Nombre de graines du joueur : %d\n\n", position.seeds_player);
                affame = etatAffame(&position);
                if (affame == 0 || affame == 1){
                        graines_restantes = 0;
                        break;
                }
                position.computer_play++;
        }      
}
printf ("\nGraines restantes sur le plateau: %d", graines_restantes);
printf("\nNombre de graines du cpu : %d\n", position.seeds_computer);
printf("Nombre de graines du joueur : %d\n\n", position.seeds_player);
deliberation(&position);

}

