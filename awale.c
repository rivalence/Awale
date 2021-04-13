#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "awale.h"

int minMaxValue(Position *position_current, int computer_play ,int depth, int depthMax){
    int tab_values[8] = {0,0,0,0,0,0,0,0};
    int i, res, graines_restantes, affame;
    Position position_next;
    affame = etatAffame(position_current);
    if (affame == 0 || affame == 1){
        return evaluation(position_current, computer_play);
    }

    if (finalPosition(position_current, computer_play)){
        return evaluation(position_current, computer_play);
    }

    if (depth == depthMax){
        //printf("%d for cpu; profondeur: %d; computer_p %d\n", position_current->seeds_computer, depth, computer_play);
        //printf("%d for player; profondeur: %d; computer_p %d\n", position_current->seeds_player, depth, computer_play);
        return evaluation(position_current, computer_play);
    }

    for (i=0; i<8; i++){
        if (position_current->cells_computer[i]){
            graines_restantes = playMove(position_current, &position_next, i, computer_play);
            tab_values[i] = minMaxValue(&position_next, !computer_play, depth+1, depthMax); 
        }
        else{
            if (computer_play)  tab_values[i] -= 100;
            else    tab_values[i] += 100; 
        }
    }
    if (computer_play)  res = searchMax(tab_values, depth);
    else    res = searchMin(tab_values, depth);

    //printf("%d for cpu; profondeur: %d; computer_p: %d res %d\n", position_next.seeds_computer, depth, computer_play, res);
    //printf("%d for player; profondeur: %d; computer_p: %d res %d\n", position_next.seeds_player, depth,computer_play, res);
    return res;
}

//==========================================================================
void affiche(Position* pos){
    for (int i=0; i<8; i++){
        printf(" %d",pos->cells_computer[i]);
    }
    printf("\n==================\n");
    for (int i=0; i<8; i++){
        printf(" %d",pos->cells_player[i]);
    }

    printf("\n\n");
}

//==========================================================================
void copieValeur(Position* pos_next, Position* pos_curent){
    for (int i=0; i<8; i++){
        pos_next->cells_computer[i] = pos_curent->cells_computer[i];
    }
    for (int i=0; i<8; i++){
        pos_next->cells_player[i] = pos_curent->cells_player[i];
    }
    pos_next->computer_play = pos_curent->computer_play;
    pos_next->seeds_computer = pos_curent->seeds_computer;
    pos_next->seeds_player = pos_curent->seeds_player;
}

//==========================================================================
void initialisation(Position* pos){ //Etat initial de la grille
    for (int i=0; i<8; i++){
        pos->cells_computer[i] = 4;
    }
    for (int i=0; i<8; i++){
        pos->cells_player[i] = 4;
    }
    pos->computer_play = 1;
    pos->seeds_computer = 0;
    pos->seeds_player = 0;
}

//==========================================================================
void deliberation(Position* pos){
    if (pos->seeds_computer > pos->seeds_player){
        printf("Fin du jeu ! Le CPU remporte la partie");
    }
    else if(pos->seeds_player > pos->seeds_computer){
        printf("Fin du jeu ! %s remporte la partie", pos->name);
    }
    else{
        printf("Le jeu se termine sur un match nul !");
    }
}

//==========================================================================
int verificationCase(int index_choisi){
    if (index_choisi < 1 || index_choisi > 8){
         do
        {
            printf("Entrez une position entre 1 et 8: ");
            scanf("%d",&index_choisi); 
        } while (index_choisi < 1 || index_choisi > 8);
    }

    return index_choisi;
}

//==========================================================================
int finalPosition(Position* pos_current, int computer_play){
    int total_seeds;
    total_seeds = getTotalSeeds(pos_current);
    if (total_seeds <= 8){   
        return 1;   //On retourne vrai si la partie doit se terminer
    }
    else{
        return 0;
    }    
}

//==========================================================================
int etatAffame(Position* pos_current){  //Vérifie si chaque a toujours des graines. Sinon il perd
    int seeds = 0;
    for (int i=0; i<8; i++){
        seeds += pos_current->cells_computer[i];
    }
    if (seeds == 0){
        for (int i=0; i<8; i++){
            pos_current->seeds_player += pos_current->cells_player[i];
        }
        return 0;   //False si cpu n'a plus de graines et perd
    }

    seeds = 0;
    for (int i=0; i<8; i++){
        seeds += pos_current->cells_player[i];
    }
    if(seeds == 0){
        for (int i=0; i<8; i++){
            pos_current->seeds_computer += pos_current->cells_computer[i];
        }
        return 1;   //True si joueur n'a plus de graines et perd
    }

    return 10;
}

//==========================================================================
int evaluation(Position* pos, int computer_play){
    double valmax_double=0.0, seeds_cpu=0.0, seeds_player=0.0;
    int valmax_int;
    if (computer_play){
        return pos->seeds_player;
    }
    else {
        if (pos->seeds_player != 0){
            if (pos->seeds_computer == 0){
                return -1000;
            }
            seeds_cpu = pos->seeds_computer * 1.0;
            seeds_player = pos->seeds_player * 1.0;
            valmax_double = seeds_cpu / seeds_player;
            valmax_int = (int)(valmax_double * 100);
        }
        else{
            valmax_int = pos->seeds_computer * 6500;
        }
        return valmax_int;
    }
}

//==========================================================================
int getTotalSeeds(Position* pos){
    int seeds_number=0;

    for (int i=0; i<8; i++){
        seeds_number += pos->cells_player[i];
    }
    for (int i=0; i<8; i++){
        seeds_number += pos->cells_computer[i];
    }

    return seeds_number;
}

//==========================================================================
int searchMax(int* tab, int depth){
    int max=tab[0];
    int index = 0;
    for (int i=1; i<8;i++){
        if (max<tab[i]){
            max = tab[i];
            index = i;
        } 
    }
    if (depth == 1){
        return index;
    }
    return max * -1;
}

//==========================================================================
int searchMin(int* tab, int depth){
    int min = tab[0];
    int index = 0;
    for (int i = 1; i < 8; i++){
        if (min > tab[i]){
            min = tab[i];
            index = i;
        }
    }
    if (depth == 1){
        return index;
    }
    return min * -1;
}

//==========================================================================
int playMove(Position *position_current, Position* position_next, int index, int computer_play){
    int seeds = 0, j, i, nbre_graines;
    
    copieValeur(position_next, position_current);
    if(computer_play){
        seeds = position_next->cells_computer[index];
        position_next->cells_computer[index] = 0;
        j = index;
        i = 1;
        while (seeds){
            if (j<8){
                if(j == index){
                    j++;
                    continue;
                }
                else{
                    position_next->cells_computer[j]++;
                }
            }
            else{
                position_next->cells_player[j-i]++;
                if (position_next->cells_player[j-i] > 1 && position_next->cells_player[j-i] < 4){
                    position_next->seeds_computer += position_next->cells_player[j-i];
                    position_next->cells_player[j-i] = 0;
                }
                i += 2;
            }    

            seeds--;
            j++;
            if (j>15){
                j=0;
                i=1;
                }
        }     
    }
    else{
        seeds = position_next->cells_player[index];
        position_next->cells_player[index] = 0;
        j = index;
        i = 1;
        while (seeds){
            if (j>-1){    
                if (j == index){
                    j--;
                    continue;
                }
                position_next->cells_player[j]++;
            }
            else{
                position_next->cells_computer[j+i]++;
                if (position_next->cells_computer[j+i] > 1 && position_next->cells_computer[j+i] < 4){
                    position_next->seeds_player += position_next->cells_computer[j+i];
                    position_next->cells_computer[j+i] = 0;
                }
                i += 2;
            }    

            j--;
            seeds--;
            if (j<-8)  {
                j = 7;
                i = 1;
            }
        } 
    }

    nbre_graines = getTotalSeeds(position_next);

    return nbre_graines;    
}