/*MILLARAY THIARE ATENEA ZAMBRANO SANTANA RUT 21.196.585-1*/
/*DIEGO ANTONIO VARGAS GOMEZ RUT 21.012.009-2*/

#include <stdio.h>
#include <stdlib.h>

typedef struct nodito
{
    char caracter;
    int frecuencia;
    int contador;
    struct nodito *siguiente;
}NODO;

NODO *crear(char caracter);
void insertar_lista(NODO **inicio, char caracter);
void mostrar_lista(NODO *inicio);
void ordenar_creciente(NODO **inicio);
void ordenar_decreciente(NODO **inicio);
int menu();
void buscar(NODO *inicio, char letra);

int main()
{

    // variable para almacenar informacion.
    NODO *lista = NULL;
    // aqui se leera el archivo.txt caracter por caracter y se insertara en una lista.
    // despues vamos a ocupar mostrar lista para mostrar los caracteres y su frecuencia en la lista.

    int opcion;
    FILE *archivo;
    char caracter;
    // bandera para indicar cuando la lista ya este creada.
    int bandera = 0;
    do
    {
        opcion = menu();
        switch (opcion)
        {
        case 1:// abrimos el archivo 
        {
            // fopen: para abrir el archivo.
            archivo = fopen("trabalenguas_cuentos.txt", "r");
            if (archivo == NULL)
            {
                printf("Error en la apertura del archivo\n");
            }
            else
            {
                system("cls");
                printf("El contenido del archivo es: \n\n");
                // feof: comprueba el indicador al final del archivo txt.
                while (!feof(archivo))
                {
                    // fgetc: obtiene un caracter.
                    caracter = fgetc(archivo);
                    printf("%c", caracter);
                    // fclose: para cerrar el archivo  se debe hacer siemrpe despues de ocuparlo.
                }
                fclose(archivo);
            }
        }
            printf("\n");
            system("pause");
            break;
        case 2:// generamos la lista 
        {
            //abrimos el archivo para generar la lista una sola vez
            if(bandera == 0){
            archivo = fopen("trabalenguas_cuentos.txt", "r");
               //recorremos y hacemos llamado a la funcion
                while (!feof(archivo))
                {
                    caracter = fgetc(archivo);
                    insertar_lista(&lista, caracter);
                }
                fclose(archivo);
            //MOSTRADO 
            system("cls");
            printf("Lista generada: \n");
            mostrar_lista(lista);
            bandera = 1;
            }else{
                system("cls");
                printf("La Lista ya a sido generada!! \n\n");
            }
            system("pause");
        break;
        }case 3://ordenamos por frecuencia ascendente 
        {
            system("cls");
            if(bandera == 1){
            printf("Lista ordenada por frecuencia creciente\n");
            ordenar_creciente(&lista);
            //MOSTRADO
            mostrar_lista(lista);
            printf("\n");
            }else{
                printf("\nLa lista aun no ha sido generada\n\n");
            }
            system("pause");
        }
        break;
        case 4://ordenamos por frecuencia descendente
        {
            system("cls");
            if(bandera == 1){
            printf("Lista ordenada por frecuencia decreciente\n");
            ordenar_decreciente(&lista);
            mostrar_lista(lista);
            printf("\n");
            }else{
                printf("\n La lista aun no ha sido generada\n \n");
            }
            system("pause");
        }
        break;
        case 5://medimos frecuencia de una letra 
        {
            char letra;
            system("cls");
            printf("Ingrese letra para medir su frecuencia \n");
            fflush(stdin);
            scanf("%c", &letra);
            buscar(lista, letra);
            printf("\n");
            system("pause");
        }
        break;
        }
    } while (opcion != 6);
    system("pause");
    return 0;
}

NODO *crear(char caracter)
{
    NODO *nuevo = (NODO *)malloc(sizeof(NODO));
    nuevo->caracter = caracter;
    nuevo->frecuencia = 1;
    nuevo->siguiente = NULL;
    return nuevo;
}

// NODO** representa la direccion de memoria del puntero a la cabeza(inicio) de la lista
void insertar_lista(NODO **inicio, char caracter)
{

    //*cabeza cambia el puntero a la cabeza de a lista y en el main quedan redy
    // se accede al valor al que apunta *cabeza
    if (*inicio == NULL)
    {
        *inicio = crear(caracter);
    }
    else
    {
        NODO *actual = *inicio;

        while (actual != NULL)
        {
            if (actual->caracter == caracter)
            {
                actual->frecuencia++;
                return;
            }
            actual = actual->siguiente;
        }
        actual = *inicio;
        // si se recorre la lista y no esta el caracter es porque es nuevo
        // se agrega un nuevo nodo al final de la lista
        while (actual->siguiente != NULL)
        {
            actual = actual->siguiente;
        }
        actual->siguiente = crear(caracter);
    }
}
// aqui entonces la funcion insertar, inserta el caracter en la lista enlazada
// aparte cuenta, puede aumentar el contador si el caracter esta y si o, crea un nuevo nodon alfinal

void mostrar_lista(NODO *inicio)
{
    NODO *actual = inicio;

    printf("Caracter\tFrecuencia\n");
    while (actual->siguiente != NULL)
    {
        printf("--%c-------------------%d\n", actual->caracter, actual->frecuencia);
        actual = actual->siguiente;
    }
}

void ordenar_creciente(NODO **inicio)
{
    if (*inicio == NULL)
    {
        return;
    }

    NODO *actual = *inicio;
    while (actual != NULL)
    {
        NODO *min = actual;
        NODO *temporal = actual->siguiente;

        while (temporal != NULL)
        {
            if (temporal->frecuencia < min->frecuencia)
            {
                min = temporal;
            }
            temporal = temporal->siguiente;
        }

        int frecuenciaTemp = actual->frecuencia;
        char caracterTemp = actual->caracter;
        actual->frecuencia = min->frecuencia;
        actual->caracter = min->caracter;
        min->frecuencia = frecuenciaTemp;
        min->caracter = caracterTemp;
        actual = actual->siguiente;
    }
}

void ordenar_decreciente(NODO **inicio)
{
    if (*inicio == NULL)
    {
        return;
    }
    NODO *actual = *inicio;
    while (actual != NULL)
    {
        NODO *max = actual;
        NODO *temporal = actual->siguiente;

        while (temporal != NULL)
        {
            if (temporal->frecuencia > max->frecuencia)
            {
                max = temporal;
            }
            temporal = temporal->siguiente;
        }

        int frecuenciaTemp = actual->frecuencia;
        char caracterTemp = actual->caracter;

        actual->frecuencia = max->frecuencia;
        actual->caracter = max->caracter;
        max->frecuencia = frecuenciaTemp;
        max->caracter = caracterTemp;
        actual = actual->siguiente;
    }
}

int menu()
{
    //ocupamos un menu.txt
    FILE *menu;
    char caracter;
    int x;
    do
    {
        system("cls");
        menu = fopen("menu.txt","r");
        if(menu == NULL){
            printf(" \nerror de apertura del archivo.txt\n");
        }else{
            //EOF end of file evalua el final del archivo
            while((caracter = fgetc(menu)) != EOF){
                printf("%c",caracter);
            }
        }
        fclose(menu);
        printf("\n \n");
        printf(">>> ");
        scanf("%d", &x);
        if (x < 1 || x > 6)
        {
            system("cls");
            printf("ERROR FUERA DE RANGO \n");
            system("pause");
        }
    } while (x < 1 || x > 6);
    return x;
}

void buscar(NODO *inicio, char letra)
{
    NODO *actual = inicio;
    int frecuencia = 0;

    while (actual != NULL)
    {
        if (actual->caracter == letra)
        {
            frecuencia = actual->frecuencia;
        }
        actual = actual->siguiente;
    }
    printf("\n La letra que ingresaste: (%c) se repite (%d) veces en archivo.txt \n", letra, frecuencia);
}
