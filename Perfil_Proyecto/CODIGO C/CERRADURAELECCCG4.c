/* GRUPO 4, IZA DANIEL, COMINA FRANCISCO, JHOSUE ANGAMARCA,, CERRADURA ELECTRONICA*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#include <sys/stat.h>
#include <ctype.h>

#define CARPETA "UsuariosPCB"
#define ARCHIVO "UsuariosPCB\\usuarios.txt"

//=========================================
// CREAR CARPETA
//=========================================
void crearCarpeta()
{
    _mkdir(CARPETA);
}

//=========================================
// GUARDAR DATOS
//=========================================
void guardarDatos(char nombre[], char cedula[], int pin)
{
    FILE *archivo;

    archivo = fopen(ARCHIVO, "w");

    if(archivo == NULL)
    {
        printf("No se pudo crear el archivo.\n");
        return;
    }

    fprintf(archivo, "Nombre: %s\n", nombre);
    fprintf(archivo, "Cedula: %s\n", cedula);
    fprintf(archivo, "PIN: %d\n", pin);

    fclose(archivo);
}
//=========================================
// VALIDAR CEDULA ECUATORIANA
//=========================================
int validarCedula(char cedula[])
{
    int i, suma = 0, num;
    int provincia;
    int tercerDigito;
    int resultado;
    int verificador;

    if(strlen(cedula) != 10)
        return 0;

    for(i = 0; i < 10; i++)
    {
        if(!isdigit(cedula[i]))
            return 0;
    }

    provincia = (cedula[0]-'0') * 10 + (cedula[1]-'0');

    // Provincias válidas: 01-24 y región 30
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
            num *= 2;
            if(num > 9)
                num -= 9;
        }

        suma += num;
    }

    resultado = 10 - (suma % 10);

    if(resultado == 10)
        resultado = 0;

    verificador = cedula[9]-'0';

    return (resultado == verificador);
}

int main()
{
crearCarpeta();
    // VARIABLES REGISTRADAS
    char nombreApellidoGuardado[50] = "";
    char cedula[15];"";
    int pinGuardado = 0;

    // VARIABLES INGRESADAS
    char cedulaGuardada[15] = "";
    int pin;

    int opcion;

    // ===== PANTALLA DE BIENVENIDA =====
    system("cls"); // En Linux/Mac usar "clear"

    printf("====================================\n");
    printf("      BIENVENIDO AL SISTEMA PCB\n");
    printf("====================================\n");
    printf(" Sistema de Control de Acceso\n");
    printf(" Registro mediante PIN o Cedula\n");
    printf("====================================\n");
    printf(" Presione ENTER para continuar...");
    getchar();

    do {

        system("cls"); // En Linux/Mac usar "clear"

        printf("====================================\n");
        printf("        SISTEMA DE ACCESO PCB\n");
        printf("====================================\n");
        printf("1. Ingresar Usuario\n");
printf("2. Iniciar sesion |");
printf("3. Mostrar usuario registrado\n");
printf("4. Editar usuario\n");
printf("5. Salir\n");
        printf("====================================\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {

            // ===== OPCION 1 =====
            case 1: {

                system("cls");

                int pinVerificacion;

                printf("======= REGISTRO USUARIO =======\n");

                // SI YA EXISTE UN USUARIO
                if(pinGuardado != 0) {

                    printf("Ya existe un usuario registrado.\n");
                    printf("Ingrese el PIN actual para registrar otro usuario: ");
                    scanf("%d", &pinVerificacion);

                    // SOLO UNA OPORTUNIDAD
                    if(pinVerificacion != pinGuardado) {

                        printf("\nACCESO DENEGADO\n");
                        break;
                    }
                }

                // NUEVO REGISTRO
                printf("\nIngrese nombre y apellido: ");
                scanf(" %[^\n]", nombreApellidoGuardado);

                printf("Ingrese nuevo PIN: ");
                scanf("%d", &pinGuardado);

                do
{
    printf("Ingrese cedula: ");
    scanf("%s", cedulaGuardada);

    if(!validarCedula(cedulaGuardada))
    {
        printf("\nCedula ecuatoriana invalida.\n");
        printf("Intente nuevamente.\n\n");
    }

}while(!validarCedula(cedulaGuardada));

                guardarDatos(nombreApellidoGuardado,
             cedulaGuardada,
             pinGuardado);
void mostrarProvincia(char cedula[])
{
    int provincia = (cedula[0]-'0') * 10 + (cedula[1]-'0');

    switch(provincia)
    {
        case 1: printf("Provincia: Azuay\n"); break;
        case 2: printf("Provincia: Bolivar\n"); break;
        case 3: printf("Provincia: Canar\n"); break;
        case 4: printf("Provincia: Carchi\n"); break;
        case 5: printf("Provincia: Cotopaxi\n"); break;
        case 6: printf("Provincia: Chimborazo\n"); break;
        case 7: printf("Provincia: El Oro\n"); break;
        case 8: printf("Provincia: Esmeraldas\n"); break;
        case 9: printf("Provincia: Guayas\n"); break;
        case 10: printf("Provincia: Imbabura\n"); break;
        case 11: printf("Provincia: Loja\n"); break;
        case 12: printf("Provincia: Los Rios\n"); break;
        case 13: printf("Provincia: Manabi\n"); break;
        case 14: printf("Provincia: Morona Santiago\n"); break;
        case 15: printf("Provincia: Napo\n"); break;
        case 16: printf("Provincia: Pastaza\n"); break;
        case 17: printf("Provincia: Pichincha\n"); break;
        case 18: printf("Provincia: Tungurahua\n"); break;
        case 19: printf("Provincia: Zamora Chinchipe\n"); break;
        case 20: printf("Provincia: Galapagos\n"); break;
        case 21: printf("Provincia: Sucumbios\n"); break;
        case 22: printf("Provincia: Orellana\n"); break;
        case 23: printf("Provincia: Santo Domingo de los Tsachilas\n"); break;
        case 24: printf("Provincia: Santa Elena\n"); break;
        case 30: printf("Region especial (Registro Civil)\n"); break;
        default: printf("Provincia desconocida\n");
    }
}
printf("\nUsuario registrado correctamente.\n");

                break;
            }

            // ===== OPCION 2 =====
            case 2:

                system("cls");

                printf("======= INICIAR CESIÓN =======\n");

                printf("Ingrese el PIN registrado: ");
                scanf("%d", &pin);

                // SOLO UNA OPORTUNIDAD
                if(pin == pinGuardado) {

                    printf("\nACCESO PERMITIDO\n");

                } else {

                    printf("\nACCESO DENEGADO\n");
                }

                break;

            // ===== OPCION 3 Usuarios Registrados =====
            case 3:

    system("cls");

    printf("======= USUARIO REGISTRADO =======\n");

    if(pinGuardado == 0)
    {
        printf("\nNo existe ningun usuario registrado.\n");
    }
    else
    {
        printf("Nombre : %s\n", nombreApellidoGuardado);
        printf("Cedula : %s\n", cedulaGuardada);
        printf("PIN    : ****\n");
    }

    break;
            // ===== OPCION 4 Editar usuario ====
    case 4:

    system("cls");

    printf("======= EDITAR USUARIO =======\n");

    if(pinGuardado == 0)
    {
        printf("\nNo existe ningun usuario registrado.\n");
        break;
    }

    printf("Ingrese el nuevo nombre y apellido: ");
    scanf(" %[^\n]", nombreApellidoGuardado);

    printf("Ingrese el nuevo PIN: ");
    scanf("%d", &pinGuardado);

    do
    {
        printf("Ingrese la nueva cedula: ");
        scanf("%s", cedulaGuardada);

        if(!validarCedula(cedulaGuardada))
        {
            printf("\nCedula invalida.\n");
        }

    }while(!validarCedula(cedulaGuardada));

    guardarDatos(nombreApellidoGuardado,
                 cedulaGuardada,
                 pinGuardado);

    printf("\nUsuario actualizado correctamente.\n");

    break;
            // ===== OPCION 5 Salir ====
            case 5:

                printf("\nSaliendo del sistema...\n");

                break;

            default:

                printf("\nOpcion invalida\n");
        }

        // PAUSA
        if(opcion != 5) {

            printf("\nPresione ENTER para continuar...");
            getchar();
            getchar();
        }

    } while(opcion != 5);

    return 0;
}
