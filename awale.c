#include <stdio.h>
#include <stdlib.h>
#include "awale.h"

int minMaxValue(Position position_current, int computer_play ,int depth, int depthMax){
    int tab_values[8] = {0,0,0,0,0,0,0,0};
    int i, res;
    Position position_next = position_current;
    if (depth == depthMax){
        return evaluation(tab_values, computer_play);
    }

    for (i=0; i<8; i++){
        if (position_next.cells_computer[i]){
            playMove(position_next, i, computer_play);
            tab_values[i] += minMaxValue(position_next, !computer_play, depth, depthMax); 
            depth++;
        }
    }

    if (computer_play)  res = position_next.seeds_computer;
    else    res = position_next.seeds_player;

    return res;
}

void affiche(){
    for (int i=0; i<7; i++){
        printf(" %d",i);
    }
    printf("\n==================\n");
    for (int i=15; i>7; i--){
        printf(" %d",i);
    }
}

Position initialisation(Position pos){
    for (int i=0; i<7; i++){
        pos.cells_computer[i] = 4;
    }
    for (int i=0; i<7; i++){
        pos.cells_player[i] = 4;
    }
    pos.computer_play = 1;
    pos.seeds_computer = 0;
    pos.seeds_player = 0;

    return pos;
}

//==========================================================================
int evaluation(int* tab, int computer_play){
    int best_index;
    if (computer_play){
        best_index = searchMax(tab);
    }else   best_index = searchMin(tab);

    return best_index;
}

//==========================================================================
int searchMax(int* tab){
    int max=tab[0];
    int index = 0;
    for (int i=1; i<8;i++){
        if (max<tab[i]){
            max = tab[i];
            index = i;
        } 
    }
    return index;
}

//==========================================================================
int searchMin(int* tab){
    int min = tab[0];
    int index = 0;
    for (int i = 1; i < 8; i++){
        if (min > tab[i]){
            min = tab[i];
            index = i;
        }
    }
    return index;
}

//==========================================================================
void playMove(Position position, int index, int computer_play){
    int seeds = 0, j, i;

    if(computer_play){
        seeds = position.cells_computer[index];
        position.cells_computer[index] = 0;
        j = index;
        i = 1;
        while (seeds){
            if (j<8){
                if(j == index){
                    j++;
                    continue;
                }
                position.cells_computer[j]++;
            }
            else{
                position.cells_player[j-i]++;
                if (position.cells_player[j-i] > 1 && position.cells_player[j-i] < 4){
                    position.seeds_computer += position.cells_player[j-i];
                    position.cells_player[j-i] = 0;
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
        seeds = position.cells_player[index];
        position.cells_player[index] = 0;
        j = index;
        i = 1;
        while (seeds){
            if (j>-1){    
                if (j == index){
                    j--;
                    continue;
                }
                position.cells_player[j]++;
            }
            else{
                position.cells_computer[j+i]++;
                if (position.cells_computer[j+i] > 1 && position.cells_computer[j+i] < 4){
                    position.seeds_player += position.cells_computer[j+i];
                    position.cells_computer[j+i] = 0;
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
    
}