/*-------------------------------------------------------
 PROYECTO: CERRADURA ELECTRONICA
 Guardado permanente de usuarios
 Compatible con Code::Blocks
--------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <direct.h>
#define CREAR_CARPETA(x) _mkdir(x)
#else
#include <sys/stat.h>
#include <sys/types.h>
#define CREAR_CARPETA(x) mkdir(x,0777)
#endif

#define ARCHIVO "Datos/usuarios.txt"


typedef struct
{
    char nombre[50];
    char cedula[15];
    int pin;

}Usuario;


/*--------------- PROTOTIPOS ----------------*/

void crearCarpeta();
void pausa();
void limpiar();

void registrarUsuario();
void visualizarUsuarios();
void editarUsuario();
void eliminarUsuario();
void ingresarPIN();

int menuPrincipal();
int menuUsuarios();



/*--------------- FUNCIONES GENERALES ----------------*/

void crearCarpeta()
{
    CREAR_CARPETA("Datos");

    FILE *archivo = fopen(ARCHIVO,"a");

    if(archivo != NULL)
    {
        fclose(archivo);
    }
}


void limpiar()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}


void pausa()
{
    printf("\nPresione ENTER para continuar...");
    getchar();
    getchar();
}



/*--------------- MENU PRINCIPAL ----------------*/


int menuPrincipal()
{
    int opcion;

    limpiar();

    printf("\n================================");
    printf("\n     CERRADURA ELECTRONICA");
    printf("\n================================");
    printf("\n1. Gestion de usuarios");
    printf("\n2. Ingresar PIN");
    printf("\n3. Salir");
    printf("\n================================");
    printf("\nSeleccione una opcion: ");

    scanf("%d",&opcion);

    return opcion;
}



/*--------------- MENU USUARIOS ----------------*/


int menuUsuarios()
{
    int opcion;

    limpiar();

    printf("\n================================");
    printf("\n       GESTION USUARIOS");
    printf("\n================================");
    printf("\n1. Registrar usuario");
    printf("\n2. Visualizar usuarios");
    printf("\n3. Editar usuario");
    printf("\n4. Eliminar usuario");
    printf("\n5. Regresar");
    printf("\n================================");
    printf("\nSeleccione una opcion: ");

    scanf("%d",&opcion);

    return opcion;
}
/*=========================================================
                REGISTRAR USUARIO
=========================================================*/

void registrarUsuario()
{
    FILE *archivo;
    Usuario u;

    limpiar();

    printf("\n========= REGISTRAR USUARIO =========\n");

    getchar();

    printf("Ingrese nombre: ");
    fgets(u.nombre, sizeof(u.nombre), stdin);
    u.nombre[strcspn(u.nombre, "\n")] = '\0';


    printf("Ingrese cedula: ");
    fgets(u.cedula, sizeof(u.cedula), stdin);
    u.cedula[strcspn(u.cedula, "\n")] = '\0';


    printf("Ingrese PIN: ");
    scanf("%d",&u.pin);


    archivo = fopen(ARCHIVO,"a");


    if(archivo == NULL)
    {
        printf("\nError al abrir el archivo.\n");
        pausa();
        return;
    }


    /*
       Guarda solamente los datos ingresados:
       Nombre ; Cedula ; PIN
    */

    fprintf(archivo,"%s;%s;%d\n",
            u.nombre,
            u.cedula,
            u.pin);


    fclose(archivo);


    printf("\nUsuario registrado correctamente.\n");

    pausa();
}



/*=========================================================
                VISUALIZAR USUARIOS
=========================================================*/

void visualizarUsuarios()
{
    FILE *archivo;
    char linea[150];

    limpiar();


    archivo = fopen(ARCHIVO,"r");


    if(archivo == NULL)
    {
        printf("\nNo existen usuarios registrados.\n");
        pausa();
        return;
    }


    printf("\n========== USUARIOS REGISTRADOS ==========\n");


    while(fgets(linea,sizeof(linea),archivo))
    {
        printf("\n%s",linea);
    }


    fclose(archivo);


    pausa();
}
/*=========================================================
                    EDITAR USUARIO
=========================================================*/

void editarUsuario()
{
    FILE *archivo, *temporal;
    Usuario u;
    char cedulaBuscar[15];
    int encontrado = 0;


    limpiar();

    printf("\n========= EDITAR USUARIO =========\n");


    getchar();

    printf("Ingrese la cedula del usuario: ");
    fgets(cedulaBuscar,sizeof(cedulaBuscar),stdin);
    cedulaBuscar[strcspn(cedulaBuscar,"\n")] = '\0';



    archivo = fopen(ARCHIVO,"r");

    temporal = fopen("Datos/temp.txt","w");



    if(archivo == NULL || temporal == NULL)
    {
        printf("\nError al abrir archivo.\n");
        pausa();
        return;
    }



    while(fscanf(archivo,"%[^;];%[^;];%d\n",
                 u.nombre,
                 u.cedula,
                 &u.pin) != EOF)
    {

        if(strcmp(u.cedula,cedulaBuscar)==0)
        {
            encontrado = 1;


            printf("\nNuevo nombre: ");
            fgets(u.nombre,sizeof(u.nombre),stdin);
            u.nombre[strcspn(u.nombre,"\n")] = '\0';


            printf("Nuevo PIN: ");
            scanf("%d",&u.pin);
            getchar();


        }


        fprintf(temporal,"%s;%s;%d\n",
                u.nombre,
                u.cedula,
                u.pin);

    }


    fclose(archivo);
    fclose(temporal);



    remove(ARCHIVO);
    rename("Datos/temp.txt",ARCHIVO);



    if(encontrado)
        printf("\nUsuario actualizado correctamente.\n");
    else
        printf("\nUsuario no encontrado.\n");


    pausa();
}



/*=========================================================
                    ELIMINAR USUARIO
=========================================================*/

void eliminarUsuario()
{
    FILE *archivo,*temporal;

    Usuario u;

    char cedulaBuscar[15];

    int encontrado=0;



    limpiar();

    printf("\n========= ELIMINAR USUARIO =========\n");


    getchar();


    printf("Ingrese la cedula del usuario: ");
    fgets(cedulaBuscar,sizeof(cedulaBuscar),stdin);

    cedulaBuscar[strcspn(cedulaBuscar,"\n")]='\0';



    archivo=fopen(ARCHIVO,"r");
    temporal=fopen("Datos/temp.txt","w");



    if(archivo==NULL || temporal==NULL)
    {
        printf("\nError con el archivo.\n");
        pausa();
        return;
    }



    while(fscanf(archivo,"%[^;];%[^;];%d\n",
                 u.nombre,
                 u.cedula,
                 &u.pin)!=EOF)
    {


        if(strcmp(u.cedula,cedulaBuscar)!=0)
        {
            fprintf(temporal,"%s;%s;%d\n",
                    u.nombre,
                    u.cedula,
                    u.pin);
        }
        else
        {
            encontrado=1;
        }

    }



    fclose(archivo);
    fclose(temporal);



    remove(ARCHIVO);
    rename("Datos/temp.txt",ARCHIVO);



    if(encontrado)
        printf("\nUsuario eliminado correctamente.\n");
    else
        printf("\nUsuario no encontrado.\n");


    pausa();

}



/*=========================================================
                    INGRESAR PIN
=========================================================*/

void ingresarPIN()
{
    FILE *archivo;

    Usuario u;

    int pinIngresado;

    int encontrado=0;



    limpiar();


    printf("\n========== ACCESO ==========\n");


    printf("Ingrese PIN: ");
    scanf("%d",&pinIngresado);



    archivo=fopen(ARCHIVO,"r");



    if(archivo==NULL)
    {
        printf("\nNo hay usuarios registrados.\n");
        pausa();
        return;
    }



    while(fscanf(archivo,"%[^;];%[^;];%d\n",
                 u.nombre,
                 u.cedula,
                 &u.pin)!=EOF)
    {


        if(u.pin==pinIngresado)
        {
            encontrado=1;

            printf("\nAcceso permitido.");
            printf("\nBienvenido: %s\n",u.nombre);

            break;
        }

    }



    fclose(archivo);



    if(!encontrado)
    {
        printf("\nPIN incorrecto.\n");
    }


    pausa();

}



/*=========================================================
                        MAIN
=========================================================*/

int main()
{

    int opcion;
    int submenu;


    crearCarpeta();



    do
    {

        opcion=menuPrincipal();



        switch(opcion)
        {


            case 1:


                do
                {

                    submenu=menuUsuarios();



                    switch(submenu)
                    {

                        case 1:
                            registrarUsuario();
                            break;


                        case 2:
                            visualizarUsuarios();
                            break;


                        case 3:
                            editarUsuario();
                            break;


                        case 4:
                            eliminarUsuario();
                            break;


                        case 5:
                            break;


                        default:

                            printf("\nOpcion incorrecta.\n");
                            pausa();

                    }


                }while(submenu!=5);


                break;




            case 2:

                ingresarPIN();

                break;




            case 3:

                printf("\nCerrando sistema...\n");

                break;




            default:

                printf("\nOpcion incorrecta.\n");
                pausa();

        }



    }while(opcion!=3);



    return 0;
}
