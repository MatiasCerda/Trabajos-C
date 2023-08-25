#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
int largo;
//NODO = Estados que puede tomar q0,q1,q2,q3....... hasta el q10
void SaltoLinea(int lineas){
    int i;
    for(i = 0; i < lineas; i++){
        printf("\n");
    }
}
int **CreaMatriz(){ //Asigna memoria para una matriz
    int filas = 11;
    int columnas = 4;
    int **matriz = malloc(sizeof(int));
    matriz = (int **)malloc(filas*(sizeof(int *)));
    int i;
    int j;
    for( i=0;i<filas;i++){
        matriz[i] = (int *)malloc(filas*(sizeof(int)));
    }

    for( i=0;i<columnas;i++){
        for( j=0;j<columnas;j++){
            matriz[i][j] = 0;
        }
    }
    return matriz;
}
int **Llena_matriz(){//Rellena la matriz con datos del automatata creado a mano
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
char *LeeArchivo(){ // Lee el archivo .txt almacenado en la carpeta
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
void Imprime_matriz(int **matriz)//Imprime la matriz del automata, se hizo para un mejor seguimiento del codigo
{
    int i, j;
    for( i=0; i < 11;i++){
        for( j=0; j < 4; j++){
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
    int  i;
    for (i=0; i < largo; i++){
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
    int i;
    for( i=0;i<largo;i++){//Aca empiezan las condicionales y el recorrido de la matriz
        nodo = matriz[nodo][camino(string[i])];
      //  printf("\n Camino: %c -> Nodo: %d (largo: %d , i: %d)\n", string[i], nodo, largo, i);
        //system("pause");
         if((i == largo-1)&&(nodo==3)){//Para entrar a esta condicional la cadena de ADN no debe contener mas caracteres
            printf("MUTANTE");         // Y ademas debe quedar en el nodo 3 que es el unico estado final
            break;
         }
        else if(nodo==8){      //Para que entre a este if no es necesario que la cadena de ADN finalice ya que este es
            printf("HUMANO");  //un estado/nodo sumidero porque tiene 3 adenina(a) consecutivas lo cual automaticamente es humano
            break;

        }else if(i == largo-1){//Para todos los otros estados el adn es reconocido como Humano
            printf("HUMANO");
            break;
        }
    }
}
int Seguir(){
   char opcion;
    printf("\nDesea probar con otro documento? (y/n) : ");
    scanf("%s",&opcion);
    opcion = tolower(opcion);
    SaltoLinea(2);
    switch (opcion) {
        case 'y':
            return 1; // permite que el ciclo while de la funcion main continúe
        case '1':
            return 1;
        default:
            printf("El programa ha finalizado correctamente :)\n\n");
            exit(1); // rompe ciclo while cambiando la variable flag del main en 0
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

