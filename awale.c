#include <stdio.h>
#include <stdlib.h>
#include "awale.h"

int minMaxValue(Position *position_current, int computer_play ,int depth, int depthMax){
    int tab_values[8] = {0,0,0,0,0,0,0,0};
    int i, res;
    Position position_next;

    if (depth == depthMax){
        return evaluation(position_current, computer_play, depth);
    }

    for (i=0; i<8; i++){
        if (position_current->cells_computer[i]){
            playMove(position_current, &position_next, i, computer_play);
            tab_values[i] = minMaxValue(&position_next, !computer_play, depth+1, depthMax); 
        }
        else{
            if (computer_play)  tab_values[i] -= 100;
            else    tab_values[i] += 100; 
        }
    }
    if (computer_play)  res = searchMax(tab_values, depth);
    else    res = searchMin(tab_values, depth);

    //printf("%d for cpu profondeur: %d res %d\n", position_next.seeds_computer, depth, res);
    //printf("%d for player profondeur: %d res %d\n", position_next.seeds_player, depth, res);
    return res;
}

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

void initialisation(Position* pos){
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
int evaluation(Position* pos, int computer_play, int depth){
    if (computer_play){
        return pos->seeds_computer - pos->seeds_player;
    }
    else {
        return pos->seeds_player - pos->seeds_computer;
    }
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
    return max;
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
    return min;
}

//==========================================================================
void playMove(Position *position_current, Position* position_next, int index, int computer_play){
    int seeds = 0, j, i;
    
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
                j = 1;
                i = 1;
            }
        } 
    }
    
}