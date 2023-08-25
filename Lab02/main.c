#include<stdio.h>
#include<stdlib.h>


int **DaMemoriaGrafo(int n)
{
    int **aux, i;

    aux = (int **)malloc(n*sizeof(int *));
    if (!aux)
    {
        printf("\n\nNP HAY MEMORIA SUFICIENTE PARA CONTINUAR.\nESTE PROGRAMA SE CERRARA.");
        exit(1);
    }
    for(i=0;i<n;i++)
    {
        aux[i] = (int *)malloc(n*sizeof(int));
        if (!aux[i])
        {
            printf("\n\nNO HAY MEMORIA SUFICIENTE PARA CONTINUAR.\nESTE PROGRAMA SE CERRARA.");
            exit(1);
        }
    }
    return aux;
}


void AlgDePrim(char nomArchivo[20])

{

    int a,b,u,v,n,i,j,ne=1;                         //Variables para morverse entre nodos sin alterar las variables////
    int visitado[40]={0},min,mincost=0,cost[40][40];// del nodo seleccionado ademas de los costos y los visitados  ////
                                                    //minimo, costo minimo, matriz de costos
    FILE *pArchivo;
    int **Grafo; /*EN ESTE EJEMPLO, DEFINÍ EN FORMA LOCAL A LA MATRIZ DEL GRAFO Y A SU DIMENSIÓN ("n"): SI QUIERES LAS DEFINES GLOBALMENTE!!!*/


	system("cls");

	pArchivo = fopen(nomArchivo, "r");
    if (pArchivo == NULL)
    {
        printf("\n\nERROR: Archivo no encontrado.");
        exit(1);
    }
    fscanf(pArchivo, "%d", &n); /*LEE EL NÚMERO DE NODOS DEL GRAFO, DESDE EL ARCHIVO.*/
    Grafo = DaMemoriaGrafo(n); /*GENERA UNA MATRIZ CUADRADA DE nxn ENTEROS.*/
    printf("\n ACM  Prim:\n");

	for(i=0;i<n;i++)
        for(j=0;j<n;j++)
        {
        fscanf(pArchivo, "%d", &Grafo[i][j]);
		cost[i][j] = Grafo[i][j];
		if(cost[i][j]==0)
			cost[i][j]=999; //Costo muy grande, suponiendo el infinito //
	}
    fclose(pArchivo);//Se cierra el archivo
	visitado[1]=1; //se marca el nodo como visitado

	printf("\n");
    int iteraciones =0;
	while(ne < n)

	{
		for(i=0,min=999;i<n;i++) //parte de 1 para no tener nodo 0
		for(j=0;j<n;j++)         //parte de 1 para no tener nodo 0
		if(cost[i][j]< min)
		if(visitado[i]!=0)
		{
			min=cost[i][j];
			a=u=i;  // asignaciones para no modificar i
			b=v=j;  // asignaciones para no modificar j
		}

		if(visitado[u]==0 || visitado[v]==0)
		{
			printf("\n Arco %d:(%d,%d) costo:%d",ne++,a,b,min);
			mincost+=min;
			visitado[b]=1;
		}

		cost[a][b]=cost[b][a]=999;
        iteraciones++;
	}
    printf("\n\n Costo minimo = %d",mincost);
	printf("\n\n Cantidad de iteraciones = %d\n\n\n\n", iteraciones);


}

#include <stdio.h>

struct Nodo  //Estructura del Nodo del Laboratorio 2
{
    int Nodo_1;
    int Nodo_2;
    int Coste;
    struct Nodo *sig;
};
typedef struct Nodo tNodo;
typedef tNodo *Lista;

Lista CrearNodo(int Nodo_1, int Nodo_2, int Coste)//Creacion de Nodo con sus tres Valores
{
    Lista aux;
    aux=(Lista)malloc(sizeof(tNodo));
    if(aux!= NULL )
    {
        aux->Nodo_1=Nodo_1;
        aux->Nodo_2=Nodo_2;
        aux->Coste=Coste;
        aux->sig=NULL;
    }
    return aux;
}

Lista CrearLista(Lista Q, int Nodo_1, int Nodo_2, int Coste)//Insertar al final de la Lista el Nodo creado
{
    Lista aux,aux2;
    aux=CrearNodo(Nodo_1,Nodo_2,Coste);
    if(Q=NULL)
    {Q=aux;}
    else
    {
        aux2=Q;
        while(aux2->sig!=NULL)
        {aux2=aux2->sig;}
        aux2->sig=aux;
        aux=NULL;
    }
    aux2=NULL;
    return Q;
}


Lista CrearQ(int** Matriz, int Numero_Nodos, Lista Q)//Pasar los valores de la Matriz a la Lista
{
    Lista aux;
    if(Q==NULL)
    {
        for(int i=1; i<Numero_Nodos;i++)
        {
            for(int j=1; j< Numero_Nodos; j++)
            {
               Q=CrearLista(Q,i,j,Matriz[i][j]);
            }
        }
    }
    return Q;
}
int Negativo_1(int *VS, int Numero_Nodos)//Condicion para el Kruzkal "Si todo VS es igual a -1 se detendra el codigo"
{
    int Num_1;
    for(int i=0;i<Numero_Nodos;i++)
    {
        if(VS[i]!=-1)
        {
            Num_1++;
        }
     }
     return Num_1;
}

Lista SacarPrincipio(Lista Q)//Elimina el primer elemento de Q
{
    Lista aux;
    if(Q!=NULL)
    {
        aux=Q;
        Q=Q->sig;
        aux->sig=NULL;
        free(aux);
    }
    return Q;
}

Lista PrimerNodo(Lista Q)//Retorna el Primer Nodo de Q
{
    Lista aux;
    if(Q!=NULL)
    {
        aux=Q;
        aux->sig=NULL;
    }
    return aux;
}


void ImprimirT(Lista T)//Imprime el T realizado con su Coste total
{
    Lista aux;
    aux=T;
    int Coste_Total=0;

    while(aux->sig!=null)
    {
        printf("Arista:(%d , %d) Coste: %d\n", aux->Nodo_1, aux->Nodo_2, aux->Coste);
        Coste_Total=Coste_Total+aux->Coste;
    }
    printf("%d",Coste_Total);
}

void Kruzkal(int** Matriz, int Numero_Nodos)
{
    Lista T=null;//Dejamos T vacio para agregarle valores
    int *VS; //Un arreglo con todos los Nodos (excepto el 0 que esta en -1) !=-1
    Lista Q=null;//Tambien dejamos Q vacio
    Lista Arista;
    int Numero_Iteraciones=0;

    Q=CrearQ(Matriz, Numero_Nodos, Q);//Primero llenamos Q con todas las Aristas presentes en la Matriz
    VS[0]=-1;
    for(int i=1;i<=Numero_Nodos;i++)//Luego llenamos VS con todos los Nodos presentes
    {VS[i]=i;}

    while(Negativo_1(VS,Numero_Nodos)>1 && Q!=null)//Preguntara si Q No esta Vacio & si todos los VS NO son -1
    {
        Arista = PrimerNodo(Q);//Retorna la Primera Arista

        if((VS[Arista->Nodo_1]!=-1)&&(VS[Arista->Nodo_2]!=-1))//Luego preguntara si ninguna de ellos es -1
        {
            VS[Arista->Nodo_1]=-1;//Luego los va a conectar
            VS[Arista->Nodo_2]=-1;
            T=CrearLista(T,Arista->Nodo_1, Arista->Nodo_2, Arista->Coste);//Y luego agregara la Arista a T
        }
        Numero_Iteraciones++;
        Q=SacarPrincipio(Q);//Finalmente removera la primera Arista de la Lista Q

    }
    printf("Numero Iteraciones %d", Numero_Iteraciones);
    printf("\nRecorrido de Kurzkal\n");
    ImprimirT(T);


}





int main()
{
    char nombreArchivo[30];

    printf("Ingrese nombre de archivo:   (Recuerde la extension .txt) \n");
    scanf("%s", &nombreArchivo);

    //Aca deberia ir la funcion de Kruskal


    AlgDePrim(nombreArchivo);

    printf("\n\n");
    return 0;

}
//Recordatorio:
//void prim (matriz y n° nodo);
//1 escoger el arco coste menor ordenando las aristas
//2 revisar cuales son los arcos que estan conectados a ese arco
//3
