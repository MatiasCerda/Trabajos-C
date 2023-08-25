#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
int largo;

int **CreaMatriz(){ //Asigna memoria para una matriz
    int filas = 11;
    int columnas = 4;
    int **matriz = malloc(sizeof(int));
    matriz = (int **)malloc(filas*(sizeof(int *)));
    for(int i=0;i<filas;i++){
        matriz[i] = (int *)malloc(filas*(sizeof(int)));
    }
    for(int i=0;i<columnas;i++){
        for(int j=0;j<columnas;j++){
            matriz[i][j] = 0;
        }
    }
    return matriz;
}
int **Llena_matriz(){
    int **matriz = malloc(sizeof(int));
    matriz = CreaMatriz();
    ////////////////
    matriz[0][0]=6;
    matriz[0][1]=0;
    matriz[0][2]=1;
    matriz[0][3]=4;
    ////////////////
    matriz[1][0]=6;
    matriz[1][1]=0;
    matriz[1][2]=2;
    matriz[1][3]=4;
    ////////////////
    matriz[2][0]=9;
    matriz[2][1]=3;
    matriz[2][2]=2;
    matriz[2][3]=2;
    ////////////////
    matriz[3][0]=9;
    matriz[3][1]=3;
    matriz[3][2]=2;
    matriz[3][3]=5;
    ////////////////
    matriz[4][0]=6;
    matriz[4][1]=0;
    matriz[4][2]=1;
    matriz[4][3]=5;
    ////////////////
    matriz[5][0]=9;
    matriz[5][1]=3;
    matriz[5][2]=5;
    matriz[5][3]=5;
    ////////////////
    matriz[6][0]=7;
    matriz[6][1]=0;
    matriz[6][2]=1;
    matriz[6][3]=4;
    ////////////////
    matriz[7][0]=8;
    matriz[7][1]=0;
    matriz[7][2]=1;
    matriz[7][3]=4;
    ////////////////
    matriz[8][0]=8;
    matriz[8][1]=8;
    matriz[8][2]=8;
    matriz[8][3]=8;
    ////////////////
    matriz[9][0]=10;
    matriz[9][1]=3;
    matriz[9][2]=2;
    matriz[9][3]=5;
    ////////////////
    matriz[10][0]=8;
    matriz[10][1]=3;
    matriz[10][2]=2;
    matriz[10][3]=5;
    ////////////////
return matriz;
}
char *LeeArchivo(){ // El el archivo .txt almacenado en la carpeta
    char *archivo = malloc(sizeof(char));
    char *string = malloc(sizeof(char));
    FILE *pArch = NULL;
    int flag = 1;
    char caracter;
    largo = 0;
    while(flag){
        printf("Ingrese el nombre del archivo de entrada: ");
        scanf("%s",archivo);
        pArch = fopen(archivo,"r");
        if (!pArch){
            printf("El archivo %s no existe o se encuentra dañado...\n\n", archivo);
            flag = 1;
        }else{
            flag = 0;
        }
    }
    int i=0;
    while((caracter = fgetc(pArch)) != EOF){
		string[i]=caracter;
		largo++;
		i++;
    }
   // printf("largo: %d\n\n", largo);
    fclose(pArch);
    free(pArch);
    return string;
}
void Imprime_matriz(int **matriz){
    for(int i=0; i < 11;i++){
        for(int j=0; j < 4; j++){
            if(j==0){
                if(matriz[i][j] < 10){
                    printf(" %d  ",matriz[i][j]);
                }else{
                    printf("%d  ",matriz[i][j]);
                }
            }else{
                printf("%d  ",matriz[i][j]);
            }
        }
        printf("\n");
    }
}

void Imprime_string(char *string){
    printf("[");
    for (int i=0; i < largo; i++){
        printf("%c", string[i]);
    }
    printf("]");
}

int camino(char letra){
    switch(letra){
        case 'a':
            return 0;
        case 'c':
            return 1;
        case 't':
            return 2;
        case 'g':
            return 3;
    }
}
void recorrer(char *string, int **matriz){
    int nodo = 0;
    for(int i=0;i<largo;i++){
        nodo = matriz[nodo][camino(string[i])];
        //printf("\n Camino: %c -> Nodo: %d (largo: %d , i: %d)\n", string[i], nodo, largo, i);
        //system("pause");
        if(nodo==8){
            printf("HUMANO");
            break;
        }
        else if((i == largo-1)&&(nodo==3)){
            printf("MUTANTE");
            break;
        }
        else if(i == largo-1 && nodo == 0){
            printf("HUMANO");
            break;
        }
    }
}
int Seguir(){
    int seguir;
    printf("\nDesea probar otro archivo? 1/0 : ");
    scanf("%d", &seguir);
    switch(seguir){
        case 1:
            return 1;
        case 0:
            return 0;
    }

}

int main(){
    int **matriz = malloc(sizeof(int));
    char *string = malloc(sizeof(char));
    int flag = 1;
    while(flag){
        system("cls");
        matriz=Llena_matriz();
        //Imprime_matriz(matriz);
        string=LeeArchivo();
        printf("Cadena: ");
        Imprime_string(string);

        printf("\nEl individuo es: ");
        recorrer(string,matriz);
        free(matriz);
        free(string);
        flag=Seguir();

    }
    return 0;


}

