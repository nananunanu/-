#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define ROW 15
#define COLUM 15
#define BOOM_COUNT 40
enum array_state {footprint = 1, destination, boom};
enum sight_state {up, down, left, right};
void init_maps(int* p, int* first_address);
void print_maps_in_game(int maps[][COLUM], enum sight_state sight);
void print_maps_end(int maps[][COLUM]);

struct coordinate {
    int m;
    int n;
};
typedef struct coordinate coordinate;
coordinate player = {0, 0};


void init_maps(int* p,int* const first_address) {
    coordinate a = { 0, 0 };
    int BOOM = BOOM_COUNT;

    srand((unsigned)time(NULL));

    while (BOOM > 0) {
        int random = rand() % (ROW * COLUM) + 1;
        if ((random == 1 && *p != boom) && (a.m != 1 && a.n != 1)) {
            *p = boom;
            BOOM = BOOM - 1;
        }
        p++;
        a.m++;
        if (a.n == (COLUM - 1)) {
            p = first_address;
            a.m = 0;
            a.n = 0;
        }
        else if (a.m == (ROW - 1)) {
            a.m = 0;
            a.n++;
        }
    }
}

int main(void) {
    enum array_state type;
    enum sight_state sight;
    
    int maps[ROW][COLUM] = { 0 };
    maps[ROW - 1][COLUM - 1] = destination;
    char direction[2];
    init_maps((int*)maps, &maps[0][0]);
    print_maps_in_game(maps, sight);

    
    int k = 0;
    while (k <  100) {
        scanf("%c", &direction[0]);
        getchar();
        switch(direction[0]) {
            case 'w':
                player.m--;
                sight = up; //0
                if (player.m < 0) {
                    printf("can't move\n");
                    player.m = 0;
                }
                break;
            
            case 'a':
                player.n--;
                sight = left; //2
                if (player.n < 0) {
                    printf("can't move\n");
                    player.n = 0;
                }
                break;
            
            case 's':
                player.m++;
                sight = down; //1
                if (player.m > ROW - 1) {
                    printf("can't move\n");
                    player.m = ROW - 1;
                }
                break;
            
            case 'd':
                player.n++;
                sight = right; //3
                if (player.n > COLUM - 1) {
                    printf("can't move\n");
                    player.n = COLUM - 1;
                }
                break;

            default:
                break;
        }

        if (maps[player.m][player.n] == boom) {
            printf("BOOM!!!!\n");
            break;
        }
        else if (maps[player.m][player.n] == destination) {
            printf("OMg!!! CLEAR!!!!\n");
            break;
        }
        
        system("clear");
        print_maps_in_game(maps, sight);
        k++;
    }

    print_maps_end(maps);
    return 0;
}

void print_maps_in_game(int maps[][COLUM], enum sight_state sight) {
    
    printf("boom: %d size: %dx%d\n", BOOM_COUNT, ROW, COLUM);
    /*printf("   ");
    for (int i = 0; i < COLUM; i++) {
        printf("%d ", i);
    }
    printf("\n   ");
    for (int i = 0; i < COLUM; i++) {
        printf("--");
    }
    printf("\n");*/
    
    
    for (int i = 0; i < ROW; i++) {
        printf("%2d| ", i);
        for (int j = 0; j < COLUM; j++) {
            if (i == player.m && j == player.n) {
                printf("p ");
                maps[i][j] = footprint;
            }
            else if (maps[i][j] == footprint) {
                printf("' ");
            }
            else if (maps[i][j] == destination) {
                printf("@ ");
            }
            else if (maps[i][j] == boom && sight == up && i + 1 == player.m && j == player.n) {
                printf("! ");
            }
            else if (maps[i][j] == boom && sight == down && i - 1 == player.m && j == player.n) {
                printf("! ");
            }
            else if (maps[i][j] == boom && sight == left && i == player.m && j + 1 == player.n) {
                printf("! ");
            }
            else if (maps[i][j] == boom && sight == right && i == player.m && j - 1 == player.n) {
                printf("! ");
            }
            else {
                printf(". ");
            }
            
        }
        printf("\n");
    }
}

void print_maps_end(int maps[][COLUM]) {
    /*printf("   ");
    for (int i = 0; i < COLUM; i++) {
        printf("%d ", i);
    }
    printf("\n   ");
    for (int i = 0; i < COLUM; i++) {
        printf("--");
    }
    printf("\n");*/
    for (int i = 0; i < ROW; i++) {
        printf("%2d| ", i);
        for (int j = 0; j < COLUM; j++) {
            if (i == player.m && j == player.n) {
                printf("p ");
                maps[i][j] = footprint;
            }
            else if (maps[i][j] == footprint) {
                printf("' ");
            }
            else if (maps[i][j] == destination) {
                printf("@ ");
            }
            else if (maps[i][j] == boom) {
                printf("* ");
            }
            else {
                printf(". ");
            }
        }
        printf("\n");
    }
}