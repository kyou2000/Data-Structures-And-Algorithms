#include <stdio.h>
#include <stdlib.h>
#define MAX 5


// 深度优先搜索路径

void init_mix(int **mix){

    for(int i=0;i<MAX;i++){
        mix[i] = (int*)malloc(sizeof(int)*MAX);
        for(int j=0;j<MAX;j++){
            mix[i][j] = 0;
        }
    }
}

void print_road(int *path, int len){
    for(int i=0;i<len;i++){
        printf("%d  ",path[i]);
    }
}

void free_mix(int **mix){

    for(int i=0;i<5;i++){
        free(mix[i]);
    }
    free(mix);

}

void print_mix(int **mix){
    for(int i = 0; i< MAX; i++){
                for(int j = 0; j<MAX; j++){
                    printf("%d    ",mix[i][j]);
                }
                printf("\n");
            }
}

int is_empty(int top){

    if(top == -1){
        return 1;
    }else{
        return 0;
    }
}

// 检查环路
int detect(int *path,int data,int len){
    for(int i=0;i<len;i++){
        if(path[i] == data){
            return 1;
        }
    }
    return 0;
    
}

int main(){
    int nums = 0;
    // 有向无环图的路径查找
    // 图采用邻接矩阵存储
    int **graph = (int**)malloc(sizeof(int*)*MAX);
    init_mix(graph);

    graph[0][1] = 1;
    graph[0][2] = 1;
    graph[1][2] = 1;
    graph[1][3] = 1;
    graph[2][4] = 1;
    graph[3][4] = 1; 

    int end = MAX-1;

    int **visited_stack = (int**)malloc(sizeof(int*)*MAX);
    init_mix(visited_stack);

    int *path_stack = (int*)malloc(sizeof(int)*MAX);
    
    int top = -1;
    
    int p = 0; // 当前节点

    // 开始结点进栈
    top ++;
    path_stack[top] = p;

    int safety = 0;

    while(is_empty(top) == 0 && safety == 0){

        // 判断当前节点是否为终点
        if(path_stack[top] == end){

            print_road(path_stack,top+1);
            printf("\n");
            nums++;
            
            path_stack[top] = -1;

            for(int i = 0; i<MAX; i++){
                    visited_stack[top][i] = 0;
                }
            top--;

        }else{
            // 选出下一个节点
            // 0表示已未被访问，1表示已被访问
            p = path_stack[top];
            int s = -1;
            for(int i=0; i<MAX; i++){ 
                if(graph[p][i] == 1 && visited_stack[top][i] == 0){
                    s = i;
    
                    visited_stack[top][i] = 1;

                    break;
                }
            }
            
            if (s == -1) {
                path_stack[top] = -1;

                for(int i = 0; i<5; i++){
                    visited_stack[top][i] = 0;
                }
                top--;
                  
            }else{

                if(detect(path_stack,s,top+1) == 0){
                    top++;
                    path_stack[top] = s;
                }
                else{
                    safety = 1;
                }
                
            }
            s = -1;
           
        }
         
    }
    if (safety == 1){
        printf("error:存在环路\n");
    }else{
        printf("nums = %d\n",nums);
    }
    

    free_mix(visited_stack);
    free(path_stack);
    free_mix(graph);
    return 0;
}