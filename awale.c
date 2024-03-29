#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "awale.h"

int depthMaxParcourue=0;
int* p_depth = &depthMaxParcourue;

int minMaxValue(Position *position_current, int computer_play ,int depth, int depthMax){
    int tab_values[8] = {0,0,0,0,0,0,0,0};
    int i, res, elagage;
    int* p_elagage = &elagage;
    
    Position position_next;
    if (finalPosition(position_current, computer_play)){
        *p_depth = depth;
        return evaluation(position_current, computer_play);
    }

    if (depth == depthMax){
        *p_depth = depthMax;
        return evaluation(position_current, computer_play);
    }

    for (i=0; i<8; i++){
        if (validMove(position_current, computer_play, i)){
            playMove(position_current, &position_next, i, computer_play);
            tab_values[i] = minMaxValue(&position_next, !computer_play, depth+1, depthMax);
            if (elagage){
                if (tab_values[i] > 0 && elagage < 0){
                    if (elagage > (tab_values[i] * (-1))){
                        *p_elagage = searchMax(tab_values, depth);
                        return elagage;
                    }
                }
                if (tab_values[i] < 0 && elagage > 0){
                    if (elagage < (tab_values[i] * (-1))){
                        *p_elagage = searchMin(tab_values, depth);
                        return elagage;
                    }
                }
            }
        }
        else{
            if (computer_play)  tab_values[i] -= 100000;
            else    tab_values[i] += 100000; 
        }
    }

    if (computer_play)  res = searchMax(tab_values, depth);
    else    res = searchMin(tab_values, depth);

    *p_elagage = res;
    if (depth == 1){
        printf("\nProfondeur max atteinte : %d\n", depthMaxParcourue);
    }

    return res;
}

//==========================================================================
int validMove(Position* pos, int computer_play, int index){ //On vérifie si la case contient des graines 
    if (computer_play){
        return pos->cells_computer[index];  //True si la case est non vide, sinon faux
    }
    else{
        return pos->cells_player[index];
    }
}

//==========================================================================
void affiche(Position* pos){
    int j=16;
    for (int i=0; i<8; i++){
        printf("%d[%d] ",i+1,pos->cells_computer[i]);
    }

    printf("\n===============================================\n");
    for (int i=0; i<8; i++){
        printf("%d[%d] ",j-i,pos->cells_player[i]);
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
    if (pos->computer_play){
        pos->debut = 1;
    }
    else{
        pos->debut = 10;
    }
}

//==========================================================================
void deliberation(Position* pos){
    if (pos->seeds_computer > pos->seeds_player){
        printf("Fin du jeu ! Le CPU remporte la partie\n");
    }
    else if(pos->seeds_player > pos->seeds_computer){
        printf("Fin du jeu ! %s remporte la partie\n", pos->name);
    }
    else{
        printf("Le jeu se termine sur un match nul !\n");
    }
}

//==========================================================================
int verificationCase(int index_choisi){
    if (index_choisi < 9 || index_choisi > 16){
         do
        {
            printf("Entrez une position entre 9 et 16: ");
            scanf("%d",&index_choisi); 
        } while (index_choisi < 9 || index_choisi > 16);
    }

    return index_choisi;
}

//==========================================================================
int changeIndex(int index_choisi){
    if (index_choisi == 16){
        return 1;
    }
    if (index_choisi == 15){
        return 2;
    }
    if (index_choisi == 14){
        return 3;
    }
    if (index_choisi == 13){
        return 4;
    }
    if (index_choisi == 12){
        return 5;
    }
    if (index_choisi == 11){
        return 6;
    }
    if (index_choisi == 10){
        return 7;
    }
    if (index_choisi == 9){
        return 8;
    }

    return 15;
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
int etatAffame(Position* pos_current){  //Vérifie si chaque joueur a toujours des graines. Sinon il perd
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
    int valmax_int;
    if (computer_play){
        valmax_int = calculFavorableIA(pos, -1);
        return valmax_int;
    }
    else {
        valmax_int = calculFavorableIA(pos, 1);
        return valmax_int;
    }
}

//==========================================================================
int calculFavorableIA(Position* pos, int signe){
    double valmax_double=0.0, seeds_cpu=0.0, seeds_player=0.0;
    int valmax_int;
    if (pos->seeds_player != 0){
        if (pos->seeds_computer == 0){
            return signe * 1000;
        }
        seeds_cpu = pos->seeds_computer * 1.0;
        seeds_player = pos->seeds_player * 1.0;
        valmax_double = seeds_cpu / seeds_player;
        valmax_int = (int)(valmax_double * (signe * 100));
        }
    else{
        valmax_int = pos->seeds_computer * (signe * 6500);
        }

    return valmax_int;
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
int getLastIndexPlayer(int j){
    int index_player = -1;
    if (j==-1){
        index_player=0;
    }
    if (j==-2){
        index_player=1;
    }
    if (j==-3){
        index_player=2;
    }
    if (j==-4){
        index_player=3;
    }
    if (j==-5){
        index_player=4;
    }
    if (j==-6){
        index_player=5;
    }
    if (j==-7){
        index_player=6;
    }
    if (j==-8){
        index_player=7;
    }

    return index_player;
}

//==========================================================================
int playMove(Position *position_current, Position* position_next, int index, int computer_play){
    int seeds = 0, j, i, nbre_graines, index_player = -1;
    
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
                i += 2;
            }    
            seeds--;
            j++;
            if (j>15){
                j=0;
                i=1;
                }
        }

        j--;
        while(j>7){
            if (position_next->cells_player[15-j] > 1 && position_next->cells_player[15-j] < 4){
                position_next->seeds_computer += position_next->cells_player[15-j];
                position_next->cells_player[15-j] = 0;
                j--;
            }
            else{
                break;
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
                i += 2;
            }    

            j--;
            seeds--;
            if (j<-8)  {
                j = 7;
                i = 1;
            }
        }

        j++;
        index_player = getLastIndexPlayer(j);
        while (index_player>-1)
        {
            if (position_next->cells_computer[index_player] > 1 && position_next->cells_computer[index_player] < 4){
                    position_next->seeds_player += position_next->cells_computer[index_player];
                    position_next->cells_computer[index_player] = 0;
                    index_player--;
                }
            else{
                break;
            }
        }
         
    }

    nbre_graines = getTotalSeeds(position_next);
    return nbre_graines;    
}

//==========================================================================
void vider_buffer(FILE* f)
{
    int c;
    while ((c=fgetc(f)) != '\n' && c != EOF);
}


//==========================================================================

void sleep(int nbr_seconds)
{
	clock_t goal;

	goal = (nbr_seconds * CLOCKS_PER_SEC) + clock();

	while(goal > clock())
	{
		;
	}
}