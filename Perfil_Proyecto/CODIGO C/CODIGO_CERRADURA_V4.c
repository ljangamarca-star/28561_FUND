#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

#define MAX 100

//=========================================
// CAMBIAR ESTA RUTA
//=========================================
#define RUTA_ARCHIVO "C:\\Users\\Francisco\\Documents\\usuarios.txt"

//=========================================
// ESTRUCTURA
//=========================================
struct Usuario
{
    char nombre[50];
    char cedula[15];
    char pin[5];
};

struct Usuario usuarios[MAX];
int total = 0;

//=========================================
// LEER PIN
//=========================================
void leerPin(char pin[])
{
    char c;
    int i;

    i = 0;

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
            printf("*");
            i++;
        }
    }

    pin[i] = '\0';
}

//=========================================
// VALIDAR CEDULA ECUATORIANA
//=========================================
int validarCedula(char cedula[])
{
    int i;
    int suma;
    int num;
    int provincia;
    int tercerDigito;
    int resultado;
    int verificador;

    suma = 0;

    if(strlen(cedula) != 10)
        return 0;

    for(i = 0; i < 10; i++)
    {
        if(!isdigit(cedula[i]))
            return 0;
    }

    provincia = (cedula[0]-'0') * 10 + (cedula[1]-'0');

    // Provincias válidas del Ecuador
    if((provincia < 1 || provincia > 24) && provincia != 30)
        return 0;

    tercerDigito = cedula[2]-'0';

    if(tercerDigito >= 6)
        return 0;

    for(i = 0; i < 9; i++)
    {
        num = cedula[i]-'0';

        if(i % 2 == 0)
        {
            num = num * 2;

            if(num > 9)
                num = num - 9;
        }

        suma += num;
    }

    resultado = 10 - (suma % 10);

    if(resultado == 10)
        resultado = 0;

    verificador = cedula[9]-'0';

    if(resultado == verificador)
        return 1;

    return 0;
}

//=========================================
// VERIFICAR SI LA CEDULA YA EXISTE
//=========================================
int existeCedula(char cedula[])
{
    int i;

    for(i = 0; i < total; i++)
    {
        if(strcmp(usuarios[i].cedula, cedula) == 0)
        {
            return 1;
        }
    }

    return 0;
}

//=========================================
// CARGAR USUARIOS
//=========================================
void cargarUsuarios()
{
    FILE *archivo;

    archivo = fopen(RUTA_ARCHIVO, "r");

    if(archivo == NULL)
        return;

    total = 0;

    while(fscanf(archivo,
                 "%49[^\n]\n%14[^\n]\n%4[^\n]\n",
                 usuarios[total].nombre,
                 usuarios[total].cedula,
                 usuarios[total].pin) == 3)
    {
        total++;

        if(total >= MAX)
            break;
    }

    fclose(archivo);
}

//=========================================
// GUARDAR USUARIOS
//=========================================
void guardarUsuarios()
{
    FILE *archivo;
    int i;

    archivo = fopen(RUTA_ARCHIVO, "w");

    if(archivo == NULL)
    {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    for(i = 0; i < total; i++)
    {
        fprintf(archivo, "%s\n", usuarios[i].nombre);
        fprintf(archivo, "%s\n", usuarios[i].cedula);
        fprintf(archivo, "%s\n", usuarios[i].pin);
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
    scanf(" %[^\n]", usuarios[total].nombre);

    do
    {
        printf("Cedula: ");
        scanf("%s", usuarios[total].cedula);

        if(!validarCedula(usuarios[total].cedula))
        {
            printf("\nCedula invalida.\n");
            printf("Ingrese una cedula ecuatoriana valida.\n\n");
        }
        else if(existeCedula(usuarios[total].cedula))
        {
            printf("\nLa cedula ya se encuentra registrada.\n\n");
        }

    }while(!validarCedula(usuarios[total].cedula) ||
           existeCedula(usuarios[total].cedula));

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
    int encontrado;

    encontrado = 0;

    printf("\n========== LOGIN ==========\n");

    printf("Cedula: ");
    scanf("%s", cedula);

    printf("PIN: ");
    leerPin(pin);

    for(i = 0; i < total; i++)
    {
        if(strcmp(cedula, usuarios[i].cedula) == 0 &&
           strcmp(pin, usuarios[i].pin) == 0)
        {
            encontrado = 1;
            break;
        }
    }

    if(encontrado)
    {
        printf("\n\n***********************************");
        printf("\n ACCESO PERMITIDO");
        printf("\n Bienvenido %s", usuarios[i].nombre);
        printf("\n***********************************\n");
    }
    else
    {
        printf("\nCedula o PIN incorrectos.\n");
    }

    system("pause");
}

//=========================================
// MOSTRAR USUARIOS
//=========================================
void mostrarUsuarios()
{
    int i;

    if(total == 0)
    {
        printf("\nNo existen usuarios registrados.\n");
    }
    else
    {
        printf("\n========== USUARIOS ==========\n");

        for(i = 0; i < total; i++)
        {
            printf("\nUsuario %d\n", i + 1);
            printf("Nombre : %s\n", usuarios[i].nombre);
            printf("Cedula : %s\n", usuarios[i].cedula);
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
    char nuevaCedula[15];
    int i;
    int j;
    int encontrado;
    int repetida;

    encontrado = 0;

    printf("\nIngrese la cedula del usuario: ");
    scanf("%s", cedulaBuscar);

    for(i = 0; i < total; i++)
    {
        if(strcmp(cedulaBuscar, usuarios[i].cedula) == 0)
        {
            encontrado = 1;
            break;
        }
    }

    if(!encontrado)
    {
        printf("\nUsuario no encontrado.\n");
        system("pause");
        return;
    }

    printf("\n========== EDITAR USUARIO ==========\n");

    printf("Nuevo nombre: ");
    scanf(" %[^\n]", usuarios[i].nombre);

    do
    {
        repetida = 0;

        printf("Nueva cedula: ");
        scanf("%s", nuevaCedula);

        if(!validarCedula(nuevaCedula))
        {
            printf("\nCedula invalida.\n");
            continue;
        }

        for(j = 0; j < total; j++)
        {
            if(j != i && strcmp(nuevaCedula, usuarios[j].cedula) == 0)
            {
                repetida = 1;
                break;
            }
        }

        if(repetida)
        {
            printf("\nLa cedula ya pertenece a otro usuario.\n");
        }

    }while(!validarCedula(nuevaCedula) || repetida);

    strcpy(usuarios[i].cedula, nuevaCedula);

    printf("Nuevo PIN (4 digitos): ");
    leerPin(usuarios[i].pin);

    guardarUsuarios();

    printf("\n\nDatos actualizados correctamente.\n");

    system("pause");
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
        printf("        CERRADURA ELECTRONICA\n");
        printf("=========================================\n");
        printf("1. Registrar usuario\n");
        printf("2. Iniciar sesion\n");
        printf("3. Mostrar usuarios\n");
        printf("4. Editar usuario\n");
        printf("5. Salir\n");
        printf("=========================================\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

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

    }while(opcion != 5);
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
//=========================================
// VALIDAR CEDULA ECUATORIANA
//=========================================
    int i;
    int suma = 0;
    int provincia;
    int tercerDigito;
    int coeficiente;
    int valor;
    int digitoVerificador;
    int calculado;

