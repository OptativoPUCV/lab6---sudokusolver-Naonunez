#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
  //Filas
  for(int i=0; i<9; i++){
    int arreglo[10] = {0};
    
    for(int j=0; j<9 ; j++){
      int casilla = n->sudo[i][j];
      
      if (casilla != 0){
        if(arreglo[casilla] == 0){
          arreglo[casilla]=1;
          
        }
        else{
          return 0;
        }
      }
    }
  }
  //Columnas
  for (int i=0;i<9;i++){
    int arreglo[10] = {0};
    
    for(int j=0;j<9;j++){
      int casillaC= n->sudo[j][i];
      
      if(casillaC != 0){
        if (arreglo[casillaC] == 0){
          arreglo[casillaC] = 1;
        }
        else{
          return 0;
        }
      }
    }
  }

  //Submatrices
  for(int i=0; i<3;i++){
    int arreglo[10] = {0};
    for (int j=0; j<9 ; j++){
      int h=3*(i/3) + (j/3);
      int k=3*(i%3) + (j%3);

      int Matriz = n->sudo[k][h];
      if(Matriz != 0){
        if(arreglo[Matriz] == 0){
          arreglo[Matriz]= 1;
        }
        else{
          return 0;
        
        }
      }
    }
  }

  return 1;
}


List* get_adj_nodes(Node* n){
  List* list=createList();
  int fila, columna;

  for(fila=0; fila<9;fila++){
    int num = 1;
    
    for(columna=0; columna<9; columna++){
      if(n->sudo[fila][columna] == 0){
        
        for(num = 1;num < 10; num++){
          n->sudo[fila][columna] = num;
          
          if(is_valid(n)){
            Node * Adyacente = copy(n);
            pushBack(list,Adyacente);
          }
        }
        n->sudo[fila][columna] = 0;
        return list;
      }
    }
  }
  return list;
}


int is_final(Node* n){
  int i, j;

  for(i=0;i<9;i++){
    for(j=0;j<9;j++){
      if(n->sudo[j][i]==0){
        return 0;
      }
    }
  }
  return 1;
}

Node* DFS(Node* initial, int* cont){
  Stack* S=createStack();
  if(S==NULL){
    return NULL;
  }
  *cont=1;
  push(S,initial);

  while(S != 0){
    Node* nodo=top(S);
    pop(S);

    *cont=*cont-1;
    (*cont)--;
    if(is_final(nodo)==1){
      return nodo;
    
    }

    List * Adyacente = get_adj_nodes(nodo);

    Node* aux =first(Adyacente);

    while( aux != NULL){
      push(S,aux);
      aux=next(Adyacente);
      
      cont*++;
      *cont = *cont +1;
      
    }
  }
  if(*cont == 0) {
  return NULL;
  }
  free(initial);
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/