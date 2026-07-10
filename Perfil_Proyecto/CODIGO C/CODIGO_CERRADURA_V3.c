#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

#define MAX 100

//==============================
// CAMBIAR ESTA RUTA
//==============================
#define RUTA_ARCHIVO "C:\\Users\\Francisco\\Documents\\usuarios.txt"

//==============================
// ESTRUCTURA
//==============================
struct Usuario
{
    char nombre[50];
    char cedula[15];
    char pin[5];
};

struct Usuario usuarios[MAX];
int total=0;

//==============================
// LEER PIN
//==============================
void leerPin(char pin[])
{
    char c;
    int i=0;

    while(1)
    {
        c=getch();

        if(c==13)
        {
            if(i==4)
                break;
        }
        else if(c==8 && i>0)
        {
            i--;
            printf("\b \b");
        }
        else if(c>='0' && c<='9' && i<4)
        {
            pin[i]=c;
            printf("*");
            i++;
        }
    }

    pin[i]='\0';
}

//==============================
// VALIDAR CEDULA
//==============================
int validarCedula(char cedula[])
{
    int i,suma=0,num,verificador,resultado;

    if(strlen(cedula)!=10)
        return 0;

    for(i=0;i<10;i++)
    {
        if(!isdigit(cedula[i]))
            return 0;
    }

    int provincia=(cedula[0]-'0')*10+(cedula[1]-'0');

    // Solo Pichincha
    if(provincia!=17)
        return 0;

    if((cedula[2]-'0')>=6)
        return 0;

    for(i=0;i<9;i++)
    {
        num=cedula[i]-'0';

        if(i%2==0)
        {
            num*=2;

            if(num>9)
                num-=9;
        }

        suma+=num;
    }

    resultado=10-(suma%10);

    if(resultado==10)
        resultado=0;

    verificador=cedula[9]-'0';

    if(resultado==verificador)
        return 1;

    return 0;
}

//==============================
// CARGAR USUARIOS
//==============================
void cargarUsuarios()
{
    FILE *archivo;

    archivo=fopen(RUTA_ARCHIVO,"r");

    if(archivo==NULL)
        return;

    total=0;

    while(fscanf(archivo,"%49[^\n]\n%14[^\n]\n%4[^\n]\n",
        usuarios[total].nombre,
        usuarios[total].cedula,
        usuarios[total].pin)==3)
    {
        total++;
    }

    fclose(archivo);
}

//==============================
// GUARDAR USUARIOS
//==============================
void guardarUsuarios()
{
    FILE *archivo;

    archivo=fopen(RUTA_ARCHIVO,"w");

    if(archivo==NULL)
    {
        printf("No se pudo crear el archivo.");
        return;
    }

    int i;

    for(i=0;i<total;i++)
    {
        fprintf(archivo,"%s\n",usuarios[i].nombre);
        fprintf(archivo,"%s\n",usuarios[i].cedula);
        fprintf(archivo,"%s\n",usuarios[i].pin);
    }

    fclose(archivo);
}
//=========================================
// REGISTRAR USUARIO
//=========================================
void registrarUsuario()
{
    if(total >= MAX)
    {
        printf("\nNo hay espacio para mas usuarios.\n");
        system("pause");
        return;
    }

    printf("\n========== REGISTRO ==========\n");

    printf("Nombre: ");
    fflush(stdin);
    gets(usuarios[total].nombre);

    do
    {
        printf("Cedula: ");
        scanf("%s", usuarios[total].cedula);

        if(!validarCedula(usuarios[total].cedula))
        {
            printf("\nCedula invalida.");
            printf("\nDebe ser una cedula valida de Pichincha (17).\n\n");
        }

    }while(!validarCedula(usuarios[total].cedula));

    printf("PIN (4 digitos): ");
    leerPin(usuarios[total].pin);

    total++;

    guardarUsuarios();

    printf("\n\nUsuario registrado correctamente.\n");

    system("pause");
}

//=========================================
// INICIAR SESION
//=========================================
void login()
{
    char cedula[15];
    char pin[5];

    int i;
    int encontrado=0;

    printf("\n========== LOGIN ==========\n");

    printf("Cedula: ");
    scanf("%s", cedula);

    printf("PIN: ");
    leerPin(pin);

    for(i=0;i<total;i++)
    {
        if(strcmp(cedula,usuarios[i].cedula)==0 &&
           strcmp(pin,usuarios[i].pin)==0)
        {
            encontrado=1;
            break;
        }
    }

    if(encontrado)
    {
        printf("\n\n***************************");
        printf("\nACCESO PERMITIDO");
        printf("\nBienvenido %s",usuarios[i].nombre);
        printf("\n***************************\n");
    }
    else
    {
        printf("\n\nCedula o PIN incorrectos.\n");
    }

    system("pause");
}

//=========================================
// MOSTRAR USUARIOS
//=========================================
void mostrarUsuarios()
{
    int i;

    if(total==0)
    {
        printf("\nNo existen usuarios registrados.\n");
    }
    else
    {
        printf("\n========= USUARIOS =========\n");

        for(i=0;i<total;i++)
        {
            printf("\nUsuario %d\n",i+1);
            printf("Nombre : %s\n",usuarios[i].nombre);
            printf("Cedula : %s\n",usuarios[i].cedula);
            printf("PIN    : ****\n");
        }
    }

    system("pause");
}

//=========================================
// EDITAR USUARIO
//=========================================
void editarUsuario()
{
    char cedulaBuscar[15];
    int i;
    int encontrado=0;

    printf("\nIngrese la cedula del usuario: ");
    scanf("%s",cedulaBuscar);

    for(i=0;i<total;i++)
    {
        if(strcmp(cedulaBuscar,usuarios[i].cedula)==0)
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
    printf("\n===== EDITAR USUARIO =====\n");

    printf("Nuevo nombre: ");
    fflush(stdin);
    gets(usuarios[i].nombre);

    do
    {
        printf("Nueva cedula: ");
        scanf("%s",usuarios[i].cedula);

        if(!validarCedula(usuarios[i].cedula))
        {
            printf("\nCedula invalida.\n");
        }
    }while(!validarCedula(usuarios[i].cedula));
    printf("Nuevo PIN: ");
    leerPin(usuarios[i].pin);
    guardarUsuarios();
    printf("\n\nDatos actualizados correctamente.\n");
    system("pause");
}
//=========================================
// VERIFICAR SI LA CEDULA YA EXISTE
//=========================================
int existeCedula(char cedula[])
{
    int i;

    for(i=0;i<total;i++)
    {
        if(strcmp(usuarios[i].cedula, cedula)==0)
        {
            return 1;
        }
    }

    return 0;
}

//=========================================
// MENU
//=========================================
void menu()
{
    int opcion;

    do
    {
        system("cls");

        printf("\n=========================================\n");
        printf("      CERRADURA ELECTRONICA\n");
        printf("=========================================\n");
        printf("1. Registrar usuario\n");
        printf("2. Iniciar sesion\n");
        printf("3. Mostrar usuarios\n");
        printf("4. Editar usuario\n");
        printf("5. Salir\n");
        printf("=========================================\n");
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
                printf("\nGracias por utilizar el sistema.\n");
                break;

            default:
                printf("\nOpcion incorrecta.\n");
                system("pause");
        }

    }while(opcion!=5);
}

//=========================================
// MAIN
//=========================================
int main()
{
    cargarUsuarios();

    menu();

    return 0;
}
