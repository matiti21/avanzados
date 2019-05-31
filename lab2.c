#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>

typedef struct local{
  char** matriz;
  int largo;
  int ancho;
  int lineaActual;
  int** possOcupadas;
  struct local* siguiente;


}local;


void imprimirMartriz(char **matriz,int largo, int ancho){
  for (int i = 0; i < largo; ++i)
  { printf("\n");
    for (int j = 0; j < ancho; ++j)
    {
      printf("%c",matriz[i][j]);
    }
  }
}

void imprimirPoss(int **matriz,int largo, int ancho){
  for (int i = 0; i < largo; ++i)
  { printf("\n");
    for (int j = 0; j < 2; ++j)
    {
      printf("%d",matriz[i][j]);
    }
  }
}
  


local* crearNodo(int largo,int ancho){
  local* nodo= (local*)(malloc(sizeof(local)));
  nodo->siguiente= NULL;
  nodo->matriz=(char**)malloc(ancho* sizeof(char* ));
  int max;
  if(largo>ancho){
    max=largo;
  }
  else{
    max=ancho;
  }
  nodo->possOcupadas=(int**)malloc(max*(sizeof(int*)));
  int i=0;
  while(i<max){
    nodo->possOcupadas[i]=(int*)malloc(2*(sizeof(int)));
    for (int j = 0; j < 2; ++j)
    {
      nodo->possOcupadas[i][j]=-1;
    }
    i+=1;
  }
  i=0;

  while (i<largo){
    nodo->matriz[i]=(char*)malloc(ancho* sizeof(char));

    for (int j = 0; j < ancho; ++j)
    {
      nodo->matriz[i][j]='_';
    }
    i+=1;
  }
  nodo->largo=largo;
  nodo->ancho=ancho;
  //imprimirMartriz(nodo->matriz,nodo->largo,nodo->ancho);
  //imprimirPoss(nodo->possOcupadas,nodo->largo,2);
  nodo->lineaActual=0;
  return nodo;
}


local* agregar(local* principal, local* agregado){

  agregado->siguiente=principal;
  return agregado;
}

local* sacarPrimero(local* lista){
  local*aux= lista;
  lista=lista->siguiente;
  return aux;


} 
local* leerArchivo(char nombre[]){
  local* nodo;
  FILE* archivo=NULL;
  archivo=fopen(nombre,"r");
  int largo;

  int ancho;
  
  int cantidad;
  int x;
  int y;

  fscanf(archivo,"%d %d",&largo,&ancho);
  fscanf(archivo,"%d ", &cantidad);
  
  nodo=crearNodo(largo,ancho);
  int i=0;
  while (i< cantidad){
    fscanf(archivo,"%d %d",&x,&y);
    nodo->possOcupadas[i][0]=x;
    nodo->possOcupadas[i][1]=y;
    nodo->matriz[x][y]='X';
    i+=1;
  }
  fclose(archivo);
  return nodo;


}
bool siguienteLineaOcupada (local* aComprobar){
  int ancho=aComprobar->ancho;
  int fila=aComprobar->lineaActual;
  int i=0;
  for (i = 0; i < ancho; ++i)
  {
    if(aComprobar->matriz[fila][i]=='X'){
      return true;
    }
  }
  
  return false;
}


local* copiarNodo(local* generador,local* nuevo){
  int largo=generador->largo;
  int ancho=generador->ancho;
  nuevo->lineaActual=generador->lineaActual+1;
  nuevo->largo=largo;
  nuevo->ancho=ancho;
  int i,j;
  for ( i = 0; i < largo; ++i)
  {
    for (j = 0; j < ancho; ++j)
    {
      nuevo->matriz[i][j]=generador->matriz[i][j];
    }
  }
  return nuevo;
}

bool revisarColumna(local* generador, int fila, int  i){
  int largo=generador->largo;
  int j;
  for ( j = 0; j < largo ; ++j)
  {
    if(generador->matriz[j][i]=='X'){
      return false;
    }

  }
  return true;
}
bool revisarDiagonal(local* generador, int fila, int columna){
   int j=columna;
   int i=fila;
   int k=fila;//fila
   int l=columna;//columna
   int n;
    int m;
    n=fila;
    m=columna;
    int v;
    int b;
    v=fila;
    b= columna;
    int contador=0;
   while(contador<generador->largo || contador<generador->ancho) {
    //printf("K=%i,l=%i,i=%i,j=%i,v=%i,b=%i,n=%i,m=%i",k,l,i,j,v,b,n,m);
    if(k>0 && l>0){
      k=k-1;
      l=l-1;
      //printf("generador->matriz[%i][%i]=%c\n",k, l,generador->matriz[k][l]);

      if(generador->matriz[k][l]=='X'){
        return false;
      }
    
    }

    if(i<generador->ancho-1 && j<generador->largo-1){
      j=j+1;
      i=i+1;
      //printf("generador->matriz[%i][%i]=%c\n",i, j,generador->matriz[i][j]);
      if(generador->matriz[i][j]=='X'){
        return false;
      }
        
    }
    if(n<generador->largo-1 && m>0){
      n=n+1;
      m=m-1;
       //printf("generador->matriz[%i][%i]=%c\n",n, m,generador->matriz[n][m]);
      if(generador->matriz[n][m]=='X'){
        return false;
      }
       
    }
    if(v>0 && b<generador->ancho){
      v=v-1;
      b= b+1;
      //printf("generador->matriz[%i][%i]=%c\n",v, b,generador->matriz[v][b]);
      if(generador->matriz[v][b]=='X'){
        return false;
        
      }
        
    }
    
       
    contador+=1;
    int c;
    //scanf("%d",&c);

  }
  return true;
}

local* generarEstadosEnFila(local*abiertos, local* generador){
  int ancho=generador->ancho;
  int fila=generador->lineaActual;
  int i;
  int contador=0;
  int c;
  for (i = 0; i < ancho; ++i)

  {//scanf("%d",&c);
    if(revisarColumna(generador, fila, i) && revisarDiagonal(generador,fila,i)){
      contador=0;
      //scanf("%d",&c);
      local *nuevo = crearNodo(generador->largo, generador->ancho);
      //imprimirMartriz(nuevo->matriz,nuevo->largo,nuevo->ancho);
      nuevo=copiarNodo(generador, nuevo);
      //printf("\nNuuvo actual=%i\n",nuevo->lineaActual);
      //printf("IMPRIMIR\n");
      //scanf("%d",&c);
      //printf(nuevo->largo,nuevo->ancho)

      //printf("\n\n");
      //printf("i=%d\n",i);
      nuevo->matriz[fila][i]='X';
      printf("NUEVO\n");  
      imprimirMartriz(nuevo->matriz,nuevo->largo,nuevo->ancho);
      
      
      
      abiertos=agregar(abiertos, nuevo);
      //imprimirMartriz(abiertos->matriz,abiertos->largo,abiertos->ancho);
      //if(abiertos->siguiente!=NULL){
       // printf("SIGUIENTE");
        //imprimirMartriz(abiertos->siguiente->matriz,abiertos->largo,abiertos->ancho);
      //}
      //imprimirMartriz(abiertos->siguiente->matriz,abiertos->largo,abiertos->ancho);
      
      //printf("SeCaE");
      //scanf("%d",&c);

    }
    printf("contador=%i\n",contador);
    contador+=1;
    printf("i=%d\n",i);
  }
  if(contador>=generador->ancho-1){
    generador->lineaActual+=1;
    abiertos=agregar(abiertos, generador);
  }
  return abiertos;
}

local* generarEstados(local* abiertos, local* cerrados, local* mejor){
    abiertos=leerArchivo("entrada.in");
    cerrados= abiertos;
    while(abiertos!=NULL){
      
      local* aux= sacarPrimero(abiertos);
      
      printf("lineaActual=%i",aux->lineaActual);
      int c;
      //scanf("%d",&c);  
       if(aux->lineaActual>aux->largo-1){
        
        return aux;
      }
      


      else if(siguienteLineaOcupada(aux)){
        aux->lineaActual+=1;
        aux->siguiente=abiertos;
        

      }
      else{
        abiertos=generarEstadosEnFila(abiertos, aux);
        printf("\n\n");
        imprimirMartriz(abiertos->matriz,abiertos->largo,abiertos->ancho);
        printf("\n\n");
        //imprimirMartriz(abiertos->siguiente->matriz,abiertos->largo,abiertos->ancho);
        //printf("\n\n");
      }
    }
}


void main(){
  int c;
  local*cerrados;
  local*mejor;  
  local *nodo=generarEstados(nodo,cerrados, mejor);
  //while (nodo!=NULL){
    //imprimirMartriz(nodo->matriz,nodo->largo,nodo->ancho);
    //printf("\n");
    //nodo=nodo->siguiente;
    //scanf("%d",&c);
  //}
    //printf("%d",nodo->possOCada vez que se clone el repositorio se necesita hacer:
  

  //imprimirMartriz(nodo->matriz,nodo->largo,nodo->ancho);
  //imprimirPoss(nodo->possOcupadas,nodo->largo,2);
  return;
}

