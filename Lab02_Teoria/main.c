#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int largoCinta;

typedef struct cinta{
    char caracter;
    int linea;
}tCinta;
typedef tCinta *pCinta;

pCinta Cinta;

typedef struct nodo{
    char caracter;
    int linea;
    struct nodo *sig;
}tNodo;
typedef tNodo *pNodo;

pNodo Pila = NULL;
pNodo c_pila = NULL;

void push(char caracter, int linea){
    pNodo nodo;
    nodo = (pNodo)malloc(sizeof(tNodo));
    if (nodo != NULL){
        nodo->caracter = caracter;
        nodo->linea = linea;
        nodo->sig = Pila;
        Pila = nodo;
    }
}

char pop(pNodo *nodito){
    char caracter;
    pNodo nodo;
    nodo = Pila;
    caracter = nodo->caracter;
    //*pila = *pila->siguiente;
    free(nodo);
    return caracter;
}

void ArmaPila(){
    c_pila = Pila;
    push('Z',0);
    for (int i=0;i<largoCinta;i++){
        if (Cinta[i].caracter == '{' || Cinta[i].caracter == '}'){
            push(Cinta[i].caracter,Cinta[i].linea);
        }
        if (Cinta[i].caracter == '(' || Cinta[i].caracter == ')'){
            push(Cinta[i].caracter,Cinta[i].linea);
        }
        if (Cinta[i].caracter == '[' || Cinta[i].caracter == ']'){
            push(Cinta[i].caracter,Cinta[i].linea);
        }
    }
}

void Leer(){
    char *archivo = malloc(sizeof(char));
    FILE *pArch = NULL;
    int flag = 1;
    int linea = 1;
    char caracter;
    while(flag == 1){
        printf("Ingrese el nombre del archivo de entrada: ");
        scanf("%s",archivo);
        pArch = fopen(archivo,"r");
        if (!pArch)
            printf("El archivo %s no existe o se encuentra da%cado...\n\n", archivo, 164);
        else
            flag = 0;
    }
    int largoArch = 1;
    while((caracter = fgetc(pArch)) != EOF)
            largoArch++;
    rewind(pArch);
    Cinta = malloc(sizeof(tCinta)*1024*largoArch);
    int i = 0;
    while((caracter = fgetc(pArch)) != EOF){
        if (caracter == '\0' || caracter == '\n')
            linea++;
        else if(caracter != 9){
            Cinta[i].caracter=caracter;
            Cinta[i].linea=linea;
            i++;
        }
    }
    largoCinta = i;
    ArmaPila();
}

int seguir(){
    char opcion;
    printf("\nDesea probar otro archivo S/N?  ");
    fflush(stdin);
    scanf("%c" , &opcion);
    if (opcion == 's' || opcion == 'S')
        return 1;
    else
        return 0;
}

int main(){
    int flag = 1;
    while(flag){
        system("cls");
        Leer();
        //////////////////////////
        printf("\nCinta:\n|");
        for(int i=0;i<largoCinta;i++){
            printf("%c|",Cinta[i].caracter);
        }
        printf("\nLinea:\n|");
        for(int i=0;i<largoCinta;i++){
            printf("%i|",Cinta[i].linea);
        }

        printf("\n------------------\n");
        while(Pila != NULL){
            printf("%c\n-\n",Pila->caracter);
            Pila = Pila->sig;
        }
        /////////////////////////
        flag = seguir();
        free(Pila);
        free(Cinta);
        Pila = c_pila;
    }
    return 0;
}

