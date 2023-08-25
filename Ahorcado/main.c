#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "dibujos.h"
#include <time.h>

void Version ()
{
printf("\n\t\t\t\tVersion Animales\n");
}

void dibujos (int Vidas) {
    if (Vidas == 6)
        {
        SinAhorcado();
        }
        else if (Vidas == 5)
        {
        Cabeza();
        }
        else if (Vidas == 4)
        {
        Tronco();
        }
        else if (Vidas == 3)
        {
        BrazoIzquierdo();
        }
        else if (Vidas == 2)
        {
        BrazoDerecho();
        }
        else if (Vidas == 1)
        {
        PiernaIzquierda();
        }
        else if (Vidas == 0)
        {
        PiernaDerecha();
        }
}

 int main() {
    char Palabra[60]     ;
    char Rep[100]        ;
    char Guiones[100]    ;
	char LetrasIngresadas[100] = ""    ;
    char LetraUsuario    ;
    int  Longitud        ;
    int  i               ;
    int  j = 0           ;
    int  Inicial         ;
    int  Acertado = 0    ;
    int  Correcto = 0    ;
    int  Vidas = 6       ;
    int  Repetido = 0    ;
    int  Bandera = 0     ;
    int  Seguir = 0      ;
    int limpiar = 1    	 ;
/*random*/              srand(time(NULL));
 /*random*/            int PalabraOculta =0+rand()%20;


/*Inicio*/
    while (1) {
            while (Bandera==0) {
            	if (limpiar == 1){
                    Longitud = 0; Inicial = 0; j=0 ; i=0;
                    Rep[0] = ' '; Rep[1] = '\0'; Vidas = 6; Acertado = 0; Correcto = 0;
					LetraUsuario = 0; limpiar =  0;
                }
                if (PalabraOculta == 1)
                {
                    strcpy(Palabra, "PERRO");

                } else if (PalabraOculta == 2) {
                    strcpy(Palabra, "GATO");

                } else if (PalabraOculta == 3) {
                    strcpy(Palabra, "VACA");

                } else if (PalabraOculta == 4) {
                    strcpy(Palabra, "COCODRILO");

                } else if (PalabraOculta == 5) {
                    strcpy(Palabra, "JIRAFA");

                } else if (PalabraOculta == 6) {
                    strcpy(Palabra, "CERDO");

                } else if (PalabraOculta == 7) {
                    strcpy(Palabra, "OBEJA");

                } else if (PalabraOculta == 8) {
                    strcpy(Palabra, "MONO");

                } else if (PalabraOculta == 9) {
                    strcpy(Palabra, "BALLENA");

                } else if (PalabraOculta == 10) {
                    strcpy(Palabra, "OSO");

                } else if (PalabraOculta == 11) {
                    strcpy(Palabra, "MAPACHE");

                } else if (PalabraOculta == 12) {
                    strcpy(Palabra, "CONEJO");

                } else if (PalabraOculta == 13) {
                    strcpy(Palabra, "PATO");

                } else if (PalabraOculta == 14) {
                    strcpy(Palabra, "RANA");

                } else if (PalabraOculta == 15) {
                    strcpy(Palabra, "TIGRE");

                } else if (PalabraOculta == 16) {
                    strcpy(Palabra, "FOCA");

                } else if (PalabraOculta == 17) {
                    strcpy(Palabra, "ELEFANTE");

                } else if (PalabraOculta == 18) {
                    strcpy(Palabra, "CIERVO");
                } else if (PalabraOculta == 19) {
                    strcpy(Palabra, "LOBO");

                } else if (PalabraOculta == 20) {
                    strcpy(Palabra, "TORO");
            }
                LimpiaPantalla();
                TituloJuego()   ;
                Version()       ;
                printf("Letras: %d", Acertado);
                printf("      | \t");
                printf("Vidas: %d", Vidas);

                dibujos(Vidas);

                if (Inicial == 0)
                    {
                    for (i = 0; i < strlen(Palabra); i++)
                        {
                        if (Palabra[i] == '-')
                            {
                            Guiones[i] = '-';
                            Longitud++;
                            }
                         else
                            {
                            Guiones[i] = '-';
                            Longitud++;
                            }
                        }
                }
                Inicial = 1;
                Guiones[Longitud] = '\0';

                printf("\n");
                for (i = 0; i < strlen(Guiones); i++) {
                    printf(" %c ", Guiones[i]);
                }

                printf("\n\nIntroduzca una letra:");
                scanf("\n%1c", & LetraUsuario);
                LetraUsuario = toupper(LetraUsuario);//transforma las letras minusculas a mayusculas
 		if (LetraUsuario == -96  || LetraUsuario == -75){LetraUsuario='A';}
	else if (LetraUsuario == -126 || LetraUsuario == -112){LetraUsuario='E';}
	else if (LetraUsuario == -95  || LetraUsuario == -42){LetraUsuario='I';}
	else if (LetraUsuario == -94  || LetraUsuario == -32){LetraUsuario='O';}
	else if (LetraUsuario == -93  || LetraUsuario == -23){LetraUsuario='U';}
			while(isdigit(LetraUsuario)){
				                printf("\n\nNo puedes introducir numeros...\n\nIntroduzca una letra:");
                scanf("\n%1c", & LetraUsuario);
                LetraUsuario = toupper(LetraUsuario);//transforma las letras minusculas a mayusculas
 		if (LetraUsuario == -96  || LetraUsuario == -75){LetraUsuario='A';}
	else if (LetraUsuario == -126 || LetraUsuario == -112){LetraUsuario='E';}
	else if (LetraUsuario == -95  || LetraUsuario == -42){LetraUsuario='I';}
	else if (LetraUsuario == -94  || LetraUsuario == -32){LetraUsuario='O';}
	else if (LetraUsuario == -93  || LetraUsuario == -23){LetraUsuario='U';}
			}


				for (i = 0; i < strlen(Rep); i++) {
                    if (Rep[i] == LetraUsuario) {
                        Repetido = 1;
                    } else {
                        Repetido = 0;
                    }
              }
 		for (i = 0; i < strlen(Palabra); i++) { //VERIFICA SI SE REPITIÓ ALGUNA LETRA YA INGRESADA
                if (Guiones[i] == LetraUsuario) {
                    Repetido = 1;
                    Acertado++;
                    break;
                } else {Repetido = 0;}
            }
            for (i = 0; i < 100; i++) { //VERIFICA SI SE REPITIÓ ALGUNA LETRA YA INGRESADA
                if (LetrasIngresadas[i] == LetraUsuario) {
                    Repetido = 1;
                    break;
                } else {Repetido = 0;}
            }
                if (Repetido == 0)
                {
                    for (i = 0; i < strlen(Palabra); i++)
                        {
                            if (Palabra[i] == LetraUsuario)
                            {
                            Guiones[i] = LetraUsuario;
                            Acertado++;
                            Correcto = 1;
                            }
                        }
                }
                if (Repetido == 0) {
                    if (Correcto == 0) {
                        --Vidas;
						LetrasIngresadas[j]=LetraUsuario; j++;
                    }
                }
                Correcto = 0;

                printf("\n");

    if (Vidas == 0)
    {
                    LimpiaPantalla();
                    printf("\n\n");
                    MensajePerdiste();
                    printf("\n\n");
                    printf("La palabra secreta era:  %s\n\n",Palabra);
                    printf("\n\n");
                    system("pause");
                    LimpiaPantalla();

                    printf("Desea seguir jugando? SI=1 \\ NO=0\n");
                    scanf("%d", &Seguir);
                    if (Seguir == 1)
                        {
                        PalabraOculta = 0+rand()%20;
                        Longitud = 0;
                        Inicial = 0;

                        Rep[0] = ' ';
                        Rep[1] = '\0';
                        Vidas = 6;
                        Acertado = 0;
                        Correcto = 0;
                        LetraUsuario = 0;
                        }




                   else
                     {
                    printf("\n\n");
                    printf("\n\n");
                    printf("La palabra secreta era:  %s\n\n",Palabra);
                    Bandera = 1;
                     }
}



                if (strcmp(Palabra, Guiones) == 0)
                 {
                    LimpiaPantalla();
                    printf("\n\n");
                    MensajeGanaste();
                    printf("\n\n");
                    printf("La palabra secreta era:  %s \n\n",Palabra);
                    system("pause");
                    LimpiaPantalla();
                    printf("Desea seguir jugando? SI=1 \\ NO=0\n");
                    scanf("%d", &Seguir);
                    if (Seguir == 1)
                    {
                        PalabraOculta = 0+rand()%20;
                        limpiar=1;
                    }

                     else
                     {
                    printf("\n\n");


                    printf("\nGracias por jugar, hasta la proxima.\n\n");
                    system("pause");
                    Bandera = 1;
                        return 0;
                     }
                }

    } //WHILE
    printf("\n\n");
    system("PAUSE");
    return 0;
}

 }
