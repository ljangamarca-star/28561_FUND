#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    // VARIABLES REGISTRADAS
    char nombreApellidoGuardado[50] = "";
    char cedulaGuardada[15] = "";
    int pinGuardado = 0;

    // VARIABLES INGRESADAS
    char cedula[15];
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
        printf("2. Ingresar PIN\n");
        printf("3. Ingresar Cedula\n");
        printf("4. Salir\n");
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

                printf("Ingrese cedula: ");
                scanf("%s", cedulaGuardada);

                printf("\nUsuario registrado correctamente.\n");

                break;
            }

            // ===== OPCION 2 =====
            case 2:

                system("cls");

                printf("======= INGRESAR PIN =======\n");

                printf("Ingrese el PIN registrado: ");
                scanf("%d", &pin);

                // SOLO UNA OPORTUNIDAD
                if(pin == pinGuardado) {

                    printf("\nACCESO PERMITIDO\n");

                } else {

                    printf("\nACCESO DENEGADO\n");
                }

                break;

            // ===== OPCION 3 =====
            case 3:

                system("cls");

                printf("======= INGRESAR POR CEDULA =======\n");

                printf("Ingrese la cedula registrada: ");
                scanf("%s", cedula);

                // SOLO UNA OPORTUNIDAD
                if(strcmp(cedula, cedulaGuardada) == 0) {

                    printf("\nACCESO PERMITIDO\n");

                } else {

                    printf("\nACCESO DENEGADO\n");
                }

                break;

            // ===== OPCION 4 =====
            case 4:

                printf("\nSaliendo del sistema...\n");

                break;

            default:

                printf("\nOpcion invalida\n");
        }

        // PAUSA
        if(opcion != 4) {

            printf("\nPresione ENTER para continuar...");
            getchar();
            getchar();
        }

    } while(opcion != 4);

    return 0;
}
