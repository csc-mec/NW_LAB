#include <stdio.h>

#define INFI 9999
#define MAX 10

int cost[MAX][MAX],dist[MAX][MAX], next_hop[MAX][MAX];
int nodes;

void init(){
    for(int i=0 ; i<nodes ; i++){
        for(int j=0 ; j<nodes ; j++){
            dist[i][j] = cost[i][j];
            next_hop[i][j] = j;
        }
    }
}


void update(){
    int updated;
    do{
        updated = 0;
        for(int i=0 ; i<nodes ; i++){
            for(int j=0 ; j<nodes ; j++){
                for(int k=0 ; k<nodes ; k++){
                    if(dist[i][j] > dist[i][k] + dist[k][j]){
                        dist[i][j] = dist[i][k] + dist[k][j];
                        next_hop[i][j] = next_hop[i][k];
                        updated = 1;
                    }
                }
            }
        }
    }while(updated);
}

void display(){
    for(int i=0 ; i<nodes ; i++){
        printf("Routing Table of Router %d\n",i);
        printf("DEST\tCOST\tNEXT\n");
        for(int j=0 ; j<nodes ; j++){
            printf("%d\t%d\t%d\n",j,dist[i][j],next_hop[i][j]);
        }
    }
}

int main(){
    printf("Enter number of routers : ");
    scanf("%d",&nodes);


    printf("Enter cost matrix [9999 for no link] :\n");

    for(int i=0 ; i<nodes ; i++){
        for(int j=0 ; j<nodes ; j++){
            scanf("%d",&cost[i][j]);
            if(i == j){
                cost[i][j] = 0;
            }
        }
    }

    init();
    update();
    display();

    return 0;
}
