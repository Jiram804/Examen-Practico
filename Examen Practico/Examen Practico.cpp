#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct nodo{
    struct nodo* izq;
    struct nodo* padre;
    int caracter;
    int caracterN;
    char nombre[50];
    char apellido[50];
    char nacionalidad[50];
    char medalla[10];
    struct nodo* der;
}Nodo;
typedef struct arbol{
    int totalizq;
    Nodo* raiz;
    int totalder;
}Arbol;
Arbol* crearArbol(){
    Arbol aux = (Arbol)malloc(sizeof(Arbol));
    aux->totalder = 0;
    aux->totalizq = 0;
    aux->raiz = NULL;
    return aux;
}
Nodo* crearNodo(char* Nombre1, char Apellido1[50], char Nacionalidad1[50], int caracter1, char medalla1[10], int caracter2){
    Nodo aux = (Nodo)malloc(sizeof(Nodo));
    char* auxiliar;
    aux->izq = NULL;
    aux->der = NULL;
    aux->padre = NULL;
    aux->caracterN = caracter2;
    aux->caracter = caracter1;
    strcpy(aux->medalla, medalla1);
    strcpy(aux->nombre, Nombre1);
    strcpy(aux->apellido, Apellido1);
    strcpy(aux->nacionalidad, Nacionalidad1);
    return aux;
}
int arbolvacio(Arbol* a){
    if(a->raiz == NULL){
        return 1;
    }
    else{
        return 0;
    }
}
void insertarnodo(Arbol* a, Nodo* n){
    Nodo* aux, * ant;
    if(arbolvacio(a) == 1){
        a->raiz = n;
    }
    else{
        aux = a->raiz;
        while(aux != NULL){
            ant = aux;
            if(n->caracter < aux->caracter){
                aux = aux->der;
            }
            else{
                aux = aux->izq;
            }
        }
        n->padre = ant;
        if(n->caracter < ant->caracter){
            ant->der = n;
        }
        else{
            ant->izq = n;
        }
    }
}
void imprimirNodo(Nodo* n){
    if(n != NULL){
        imprimirNodo(n->der);
        printf("%s %s Nacio en %s tiene una medalla de %s\n", n->nombre, n->apellido, n->nacionalidad, n->medalla);
        imprimirNodo(n->izq);
    }
}
void imprimir(Arbol* a){
    if (arbolvacio(a)){
        printf("Arbol vacio\n");
    }
    else{
        imprimirNodo(a->raiz);
    }
}
Nodo* buscarNodo(Arbol* a, int caracter){
    Nodo* aux = NULL;
    if(!arbolvacio(a)){
        aux = a->raiz;
        while(aux != NULL && caracter != aux->caracter){
            if(caracter > aux->caracter){
                aux = aux->izq;
            }
            else{
                aux = aux->der;
            }
        }
    }
    return aux;
}
void preorden(Nodo* n, char* Nacion){
    if(n != NULL){

        if(n->nacionalidad == Nacion){
            printf("%s %s de nacionalidad %s tiene medalla de %s\n", n->nombre, n->apellido, n->nacionalidad, n->medalla);
        }
        preorden(n->izq, Nacion);
        preorden(n->der, Nacion);
    }
}
void imprimirPreorden(Arbol* a, char* Nacion){
    if(!arbolvacio(a)){
        preorden(a->raiz, Nacion);
    }
}
int main(){
    FILE* atletas;
    Arbol* oro = crearArbol();
    Arbol* plata = crearArbol();
    Arbol* bronce = crearArbol();
    Nodo* aux;
    char nombre[50];
    char apellido[50];
    char nombreaux[50];
    int caracterBusqueda;
    int salidamenu = 14;
    char* NACIOn;
    int caracteraux2;
    char nacionaux[50];
    char medalla[50];
    char nacion[50];
    int salida = 0, seleccion = 0;
    int oroaux, plataaux, bonceaux;
    int caracter, caracter2;
    int caracterMedalla;
    atletas = fopen("Atletas.txt", "r");
    if(atletas == NULL){
        printf("error al abrir el archivo\n");
        return 1;
    }
    salida = 0; 
    while(salida < 50){
        fscanf(atletas, "%s", &nombre);
        fscanf(atletas, "%s", &apellido);
        fscanf(atletas, "%s", &nacion);
        fscanf(atletas, "%s", &medalla);
        caracter = nombre[0];
        caracter2 = nacion[0];
        caracterMedalla = medalla[0];
        if(caracterMedalla == 79){
            insertarnodo(oro, crearNodo(nombre, apellido, nacion, caracter, medalla, caracter2));
        }
        else if(caracterMedalla == 80) {
            insertarnodo(plata, crearNodo(nombre, apellido, nacion, caracter, medalla, caracter2));
        }
        else if(caracterMedalla == 66) {
            insertarnodo(bronce, crearNodo(nombre, apellido, nacion, caracter, medalla, caracter2));
        }
        else{
            printf("error\n");
        }
        salida++;
    }
    fclose(atletas);
    while(salidamenu != 0) {
        printf("1.mostrar todos los ganadores de oro\n");
        printf("2.mostrar todos los ganadores de plata\n");
        printf("3.mostrar todos los ganadores de bronce\n");
        printf("4.buscar por nacionalidad\n");
        printf("5.buscar por deportista\n");
        printf("6.salida\n");
        scanf("%d", &seleccion);
        switch(seleccion) {
        case 1:{
            printf("\n");
            imprimir(oro);
            printf("\n");
        }
              break;
        case 2:{
            printf("\n");
            imprimir(plata);
            printf("\n");
        }
              break;
        case 3:{
            printf("\n");
            imprimir(bronce);
            printf("\n");
        }
              break;
        case 4:
            printf("ingrse la nacion\n");
            scanf("%s", &NACIOn);
            imprimirPreorden(oro, NACIOn);
            imprimirPreorden(plata, NACIOn);
            imprimirPreorden(bronce, NACIOn);
            break;
        case 5:{
            printf("ingree el nombre del atleta\n");
            scanf("%s", &nombreaux);
            caracterBusqueda = nombreaux[0];
            aux = buscarNodo(oro, caracterBusqueda);
            if(aux != NULL){
                printf("%s %s es %s y obtuvo medalla de %s\n", aux->nombre, aux->apellido, aux->nacionalidad, aux->medalla);
            }
            else{
                printf("El atleta que busca no coincide con la base de datos\n");
            }
            aux = buscarNodo(plata, caracterBusqueda);
            if(aux != NULL){
                printf("%s %s es %s y obtuvo medalla de %s\n", aux->nombre, aux->apellido, aux->nacionalidad, aux->medalla);
            }
            else{
                printf("El atleta que busca no coincide con la base de datos\n");
            }
            aux = buscarNodo(bronce, caracterBusqueda);
            if(aux != NULL){
                printf("%s %s es %s y obtuvo medalla de %s\n", aux->nombre, aux->apellido, aux->nacionalidad, aux->medalla);
            }
            else{
                printf("El atleta que busca no coincide con la base de datos\n");
            }
        }
              break;
        case 6:{
            salidamenu = 0;
        }
              break;
        }
    }
    return 0;
}