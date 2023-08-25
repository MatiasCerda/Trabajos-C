/*
AUTORES:
    Camilo Reyes
    Vicente Zapata

ASIGNATURA:
    TEORÍA DE LA COMPUTACIÓN

PROFESOR:
    Irene Zuccar

AÑO: 2018
*/

/*MODIFICADO POR IRENE ZUCCAR CON FINES DIDACTICOS PARA EL CURSO DE TEORÍA DE LA COMPUTACIÓN.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char pila[1000];    //"pila" almacena la pila del autómata apilador. En la posición 0 siempre deberá estár el "simbolo de pila vacía" Z0 (Se llena hacia la derecha)
char CadenaEntrada[1000]; //"CadenaEntrada" posee la cadena de entrada al autómata, leída desde el archivo de texto.

/*
LecturaEntrada(NomArchivo):
Función que abre y lee el contenido del archivo de nombre "NomArchivo". En este archivo debe estar almacenada la cadena
de entrada que analizará el autómata. La cadena es almacenada en la variable global "CadenaEntrada".
*/
void LecturaEntrada(char NomArchivo[20])
{
	FILE *archivo;

    archivo = fopen(NomArchivo , "r");
    if(archivo==NULL)
    {
        printf("El archivo no existe.\nEste programa se cerrar%c.", 160);
        exit(-1);
    }
	fgets(CadenaEntrada, 1000 , archivo);

	if (CadenaEntrada[strlen(CadenaEntrada)-1] == '\n') /*permite sacar un "salto de línea" si es que el archivo posee uno al final de la línea.*/
        CadenaEntrada[strlen(CadenaEntrada)-1] = '\0';
}

void AnalizaAutomata()
{
    int largoCadenaEntrada; //"largoCadenaEntrada" es el largo de la cadena de entrada.
    int estadoActual;		//"estadoActual" señalará el estado en el que está el procesamiento de la cadena de entrada.
    int i, j;

	i = 0;    //"i" indica la posición de la "CadenaEntrada" que se está leyendo.
	j = 0;    //"j" indica la posición del "tope" de la pila.

    estadoActual = 0;       //El estado inicial del autómata, es el estado 0.
    pila[0] = 'Z';          //se inicializa la pila con el símbolo de la pila vacía: "Z" (equivalente al "Z0" de los apuntes.

    largoCadenaEntrada = strlen(CadenaEntrada);

	while(i<largoCadenaEntrada){        //Asegura leer todos los símbolos de la cadena de entrada.
		switch(estadoActual){
			case 0:
				if(CadenaEntrada[i] == 'I' && pila[j] == 'Z')
				{
					pila[j+1] = 'I';
					j++;
					i++;
				}
				if(CadenaEntrada[i] == 'I' && pila[j] == 'I')
				{
					pila[j+1] = 'I';
					j++;
					i++;
				}
				if(CadenaEntrada[i] == 'E' && pila[j]=='I')
				{
					pila[j+1] = 'E';
					estadoActual = 1;
					j++;
					i++;
					break;
				}
				if(CadenaEntrada[i] == '*' && pila[j]== 'I')
				{
					pila[j+1] = '*';
					estadoActual = 6;
					j++;
					i++;
					break;
				}
				break;
			case 1:
				if(CadenaEntrada[i] == 'E' && pila[j] == 'E')
				{
					pila[j] = 'W';
					estadoActual = 2;
					i++;
					break;
				}
				if(CadenaEntrada[i]== '*' && pila[j]== 'E')
				{
					pila[j+1]= '*';
					j++;
					estadoActual = 10;
					i++;
					break;
				}
			case 2:
				if(CadenaEntrada[i]=='E' && pila[j] == 'W')
				{
					pila[j]= '\0';
					j--;
					estadoActual = 3;
					i++;
					break;
				}
				if(CadenaEntrada[i] == '*' && pila[j] == 'W')
				{
					pila[j+1]= '*';
					j++;
					estadoActual = 14;
					i++;
					break;
				}
				break;
			case 3:
				if(pila[j] == 'I')
				{
					pila[j]='\0';
					j--;
					estadoActual = 4;
					break;
				}
			case 4:
				if(pila[j]=='Z')
				{
					estadoActual = 5;
					break;
				}
				if(CadenaEntrada[i]=='E' && pila[j]=='I')
				{
					pila[j+1]= 'E';
					estadoActual = 1;
					i++;
					j++;
					break;
				}
				if(CadenaEntrada[i]=='*' && pila[j]=='I')
				{
					pila[j+1]= '*';
					j++;
					i++;
					estadoActual = 6;
					break;
				}
			case 5:
				if(CadenaEntrada[i]=='*' && pila[j] == 'Z')
				{
					estadoActual = 5;
					i++;
					break;
				}
				if(CadenaEntrada[i]=='E' && pila[j] == 'Z')
				{
					pila[j+1] = 'E';
					j++;
					i++;
					estadoActual = 18;
					break;
				}
				if(pila[j] == 'Z')
				{
					estadoActual = 5;
					i++;
					break;
				}
			case 6:
				if(CadenaEntrada[i]=='E' && pila[j] == '*')
				{
					pila[j]='E';
					i++;
					estadoActual =1;
					break;
				}
				if(CadenaEntrada[i]=='*' && pila[j] == '*')
				{
					pila[j] = 'P';
					i++;
					estadoActual = 7;
					break;
				}
			case 7:
				if(CadenaEntrada[i]== '*' && pila[j] == 'P')
				{
					pila[j] = 'M';
					i++;
					estadoActual = 8;
					break;
				}
				if(CadenaEntrada[i]== 'E' && pila[j] =='P')
				{
					pila[j] = 'E';
					i++;
					estadoActual = 1;
					break;
				}
			case 8:
				if(CadenaEntrada[i] == '*' && pila[j] == 'M')
				{
					pila[j] = '\0';
					j--;
					i++;
					estadoActual = 9;
					break;
				}
				if(CadenaEntrada[i] == 'E' && pila[j] == 'M')
				{
					pila[j] = 'E';
					i++;
					estadoActual = 1;
					break;
				}
			case 9:
				if(CadenaEntrada[i] == 'E' && pila[j] == 'I')
				{
					pila[j] = '\0';
					j--;
					i++;
					estadoActual = 9;
					break;
				}
				if(CadenaEntrada[i] == 'E' && pila[j]=='Z')
				{
					i++;
					estadoActual = 9;
					break;
				}
				if(CadenaEntrada[i] == '*' && pila [j] == 'I')
				{
					pila [j] = '\0';
					j--;
					i++;
					estadoActual = 9;
					break;
				}
				if(CadenaEntrada[i]=='*' && pila[j] == 'Z')
				{
					i++;
					estadoActual = 9;
					break;
				}

			case 10:
				if(CadenaEntrada[i] == '*' && pila[j] == '*')
				{
					pila[j] = 'P';
					i++;
					estadoActual = 11;
					break;
				}
				if(CadenaEntrada[i] == 'E' && pila[j] == '*')
				{
					pila[j]= '\0';
					j--;
					i++;
					estadoActual = 20;
					break;
				}
			case 11:
				if(CadenaEntrada[i] == '*' && pila[j] == 'P')
				{
					pila[j] = 'M';
					i++;
					estadoActual = 12;
					break;
				}
				if(CadenaEntrada[i] == 'E' && pila[j] == 'P')
				{
					pila[j] = '\0';
					j--;
					i++;
					estadoActual = 20;
					break;
				}
			case 12:
				if(CadenaEntrada[i] == '*' && pila[j] == 'M')
				{
					pila[j] = '\0';
					j--;
					i++;
					estadoActual = 13;
					break;
				}
				if(CadenaEntrada[i] == 'E' && pila[j] == 'M')
				{
					pila[j] = '\0';
					j--;
					i++;
					estadoActual = 20;
					break;
				}
			case 13:
				if(pila[j] == 'E')
				{
					pila[j] = '\0';
					j--;
					estadoActual = 19;
					break;
				}
			case 14:
				if(CadenaEntrada[i] == '*' && pila[j] == '*')
				{
					pila[j] = 'P';
					i++;
					estadoActual = 15;
					break;
				}
				if(CadenaEntrada[i] == 'E' && pila[j] == '*')
				{
					pila[j] = '\0';
					j--;
					i++;
					estadoActual = 21;
					break;
				}
			case 15:
				if(CadenaEntrada[i] == '*' && pila[j] == 'P')
				{
					pila[j] = 'M';
					i++;
					estadoActual = 16;
					break;
				}
				if(CadenaEntrada[i] == 'E' && pila[j] == 'P')
				{
					pila[j] = '\0';
					j--;
					i++;
					estadoActual = 21;
					break;
				}
			case 16:
				if(CadenaEntrada[i] == '*' && pila[j] == 'M')
				{
					pila[j] = '\0';
					i++;
					j--;
					estadoActual = 17;
					break;
				}
				if(CadenaEntrada[i] == 'E' && pila[j] == 'M')
				{
					pila[j] = '\0';
					j--;
					i++;
					estadoActual = 21;
					break;
				}
			case 17:
				if(pila[j] == 'W')
				{
					pila[j] = 'E';
					estadoActual = 1;
					break;
				}
			case 18:
				if(CadenaEntrada[i] == 'E' && pila[j] == 'E')
				{
					pila[j+1] = 'E';
					j++;
					i++;
					estadoActual = 18;
					break;
				}
				if(CadenaEntrada[i] == '*' && pila[j] == 'E')
				{
					pila[j+1] = '*';
					j++;
					i++;
					estadoActual = 22;
					break;
				}
				if(CadenaEntrada[i] == '*' && pila[j] == 'Z')
				{
					estadoActual = 5;
					break;
				}
				if(pila[j] == 'Z')
				{
					estadoActual = 5;
					break;
				}
			case 19:
				if(CadenaEntrada[i] == 'E' && pila[j]=='I')
				{
					pila[j+1] = 'E';
					estadoActual = 1;
					j++;
					i++;
					break;
				}
				if(CadenaEntrada[i] == '*' && pila[j]== 'I')
				{
					pila[j+1] = '*';
					estadoActual = 6;
					j++;
					i++;
					break;
				}
			case 20:
				if(pila[j] == 'E')
				{
					pila[j] ='W';
					estadoActual = 2;
					break;
				}
			case 21:
				if(pila[j] == 'W')
				{
					pila[j] ='\0';
					j--;
					estadoActual = 3;
					break;
				}
			case 22:
				if(CadenaEntrada[i] == '*' && pila[j] == '*')
				{
					pila[j] = 'P';
					i++;
					estadoActual = 23;
					break;
				}
				if(CadenaEntrada[i] == 'E' && pila[j] =='*')
				{
					pila[j] = 'E';
					i++;
					estadoActual = 18;
					break;
				}
			case 23:
				if(CadenaEntrada[i] == '*' && pila[j] == 'P')
				{
					pila[j] = 'M';
					i++;
					estadoActual = 24;
					break;
				}
				if(CadenaEntrada[i] == 'E' && pila[j] =='P')
				{
					pila[j] = 'E';
					i++;
					estadoActual = 18;
					break;
				}
			case 24:
				if(CadenaEntrada[i] == '*' && pila[j] == 'M')
				{
					pila[j] = '\0';
					j--;
					estadoActual = 25;
					break;
				}
				if(CadenaEntrada[i] == 'E' && pila[j] =='M')
				{
					pila[j] = 'E';
					i++;
					estadoActual = 18;
					break;
				}
			case 25:
				if(pila[j] == 'E'){
					pila[j] = '\0';
					estadoActual = 26;
					j--;
					break;
				}
			case 26:
				i++;
				if(pila[j] == 'Z'){
					estadoActual = 5;
					break;
				}
				if(pila[j] == 'E'){
					estadoActual = 18;
					break;
				}
		}
	}
	if(estadoActual == 5)
	{
		printf("\nPikachu subio el edificio y no sobro energia");
	}
	if(estadoActual == 9)
	{
		printf("\nPikachu muere");
	}
	if(estadoActual == 18 || estadoActual == 22 || estadoActual == 23 || estadoActual == 24 || estadoActual == 25){
		printf("\nPikachu subio el edificio y sobro energia");
	}
}
int main()
 {
	char NomArchivo[20];

	printf("Ingrese el nombre del archivo: ");
	scanf("%s", &NomArchivo);

	LecturaEntrada(NomArchivo);	// se lee la cadena en el CadenaEntrada CadenaEntrada
	AnalizaAutomata();
	printf("\n\n");
	return 0;
}
