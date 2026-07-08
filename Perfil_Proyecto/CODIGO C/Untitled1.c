#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define MAX 100

struct Usuario{
    char nombre[50];
    char cedula[15];
    char pin[5];
};

struct Usuario usuarios[MAX];
int total = 0;

//============================
// INGRESAR PIN CON *
//============================
void leerPin(char pin[])
{
    char c;
    int i = 0;

    while(1)
    {
        c = getch();

        if(c == 13)
        {
            if(i == 4)
                break;
        }
        else if(c == 8 && i > 0)
        {
            i--;
            printf("\b \b");
        }
        else if(c >= '0' && c <= '9' && i < 4)
        {
            pin[i] = c;
            i++;
            printf("*");
        }
    }

    pin[i] = '\0';
}

//============================
// CARGAR USUARIOS
//============================
void cargarUsuarios()
{
    FILE *archivo;

    archivo = fopen("usuarios.txt","r");

    if(archivo == NULL)
        return;

    total = 0;

    while(fscanf(archivo,"%49[^\n]\n%14[^\n]\n%4[^\n]\n",
                 usuarios[total].nombre,
                 usuarios[total].cedula,
                 usuarios[total].pin) == 3)
    {
        total++;
    }

    fclose(archivo);
}

//============================
// GUARDAR USUARIOS
//============================
void guardarUsuarios()
{
    FILE *archivo;

    archivo = fopen("usuarios.txt","w");

    int i;

    for(i=0;i<total;i++)
    {
        fprintf(archivo,"%s\n",usuarios[i].nombre);
        fprintf(archivo,"%s\n",usuarios[i].cedula);
        fprintf(archivo,"%s\n",usuarios[i].pin);
    }

    fclose(archivo);
}

//============================
// REGISTRAR USUARIO
//============================
void registrarUsuario()
{
    if(total == MAX)
    {
        printf("\nNo hay espacio.\n");
        return;
    }

    printf("\nNombre completo: ");
    fflush(stdin);
    gets(usuarios[total].nombre);

    printf("Cedula: ");
    scanf("%s",usuarios[total].cedula);

    printf("PIN (4 digitos): ");

    leerPin(usuarios[total].pin);

    guardarUsuarios();

    total++;

    printf("\n\nUsuario registrado correctamente.\n");

    system("pause");
}

//////////////////////////////////////////////////
// INICIAR SESION
//////////////////////////////////////////////////

void login()
{
    char cedula[15];
    char pin[5];
    int i, encontrado = 0;

    printf("\nIngrese la cedula: ");
    scanf("%s", cedula);

    printf("Ingrese el PIN: ");
    leerPin(pin);

    for(i=0; i<total; i++)
    {
        if(strcmp(cedula, usuarios[i].cedula)==0 &&
           strcmp(pin, usuarios[i].pin)==0)
        {
            encontrado = 1;
            break;
        }
    }

    if(encontrado)
    {
        printf("\n\n***************");
        printf("\n ACCESO PERMITIDO");
        printf("\n Bienvenido %s", usuarios[i].nombre);
        printf("\n***************\n");
    }
    else
    {
        printf("\n\nCedula o PIN incorrectos.\n");
    }

    system("pause");
}

//////////////////////////////////////////////////
// MOSTRAR USUARIOS
//////////////////////////////////////////////////

void mostrarUsuarios()
{
    int i;

    if(total==0)
    {
        printf("\nNo hay usuarios registrados.\n");
    }
    else
    {
        printf("\n=========== USUARIOS ===========\n");

        for(i=0;i<total;i++)
        {
            printf("\nUsuario #%d\n", i+1);
            printf("Nombre : %s\n", usuarios[i].nombre);
            printf("Cedula : %s\n", usuarios[i].cedula);
            printf("PIN    : ****\n");
        }
    }

    system("pause");
}

//////////////////////////////////////////////////
// EDITAR USUARIO
//////////////////////////////////////////////////

void editarUsuario()
{
    char cedula[15];
    int i, encontrado=0;

    printf("\nIngrese la cedula del usuario: ");
    scanf("%s", cedula);

    for(i=0;i<total;i++)
    {
        if(strcmp(cedula, usuarios[i].cedula)==0)
        {
            encontrado=1;
            break;
        }
    }

    if(!encontrado)
    {
        printf("\nUsuario no encontrado.\n");
        system("pause");
        return;
    }

    printf("\nNuevo nombre: ");
    fflush(stdin);
    gets(usuarios[i].nombre);

    printf("Nueva cedula: ");
    scanf("%s", usuarios[i].cedula);

    printf("Nuevo PIN: ");
    leerPin(usuarios[i].pin);

    guardarUsuarios();

    printf("\n\nDatos actualizados correctamente.\n");

    system("pause");
}

//////////////////////////////////////////////////
// MENU
//////////////////////////////////////////////////

void menu()
{
    int opcion;

    do
    {
        system("cls");

        printf("=================================\n");
        printf("   CERRADURA ELECTRONICA\n");
        printf("=================================\n");
        printf("1. Registrar usuario\n");
        printf("2. Iniciar sesion\n");
        printf("3. Ver usuarios\n");
        printf("4. Editar usuario\n");
        printf("5. Salir\n");
        printf("=================================\n");
        printf("Seleccione una opcion: ");
        scanf("%d",&opcion);

        switch(opcion)
        {
            case 1:
                registrarUsuario();
                break;

            case 2:
                login();
                break;

            case 3:
                mostrarUsuarios();
                break;

            case 4:
                editarUsuario();
                break;

            case 5:
                printf("\nHasta luego.\n");
                break;

            default:
                printf("\nOpcion invalida.\n");
                system("pause");
        }

    }while(opcion!=5);
}

//////////////////////////////////////////////////
// MAIN
//////////////////////////////////////////////////

int main()
{
    cargarUsuarios();

    menu();

    return 0;
}
