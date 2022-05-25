#include <stdio.h>

int main (void){

    //Empezamos mostrando un encabezado a modo decorativo
    printf("Fundamentos de Programacion 1 - Practica 1/Ejercicio 2. \n");
    printf("------------------------------------------------------- \n\n");


    //Pedimos al usuario la fecha en la que pidio el prestamo
    int dia, mes, ano, anomes, mesactual;

    printf("Introduzca la fecha de concesion del prestamo: ");
    scanf("%d/%d/%d",&dia, &mes, &ano);


    //filtramos los datos introducidos
    if (dia>30 || dia<1){
        printf("Error, el dia introducido no es correcto.");
    }else{
        if(mes<1 || mes>12){
            printf("Error, el mes introducido no es correcto.");
        }else{
            if(ano<1900 || ano>2100){
                printf("Error, el año introducido no es correcto.");

            }else{



                //Convertimos los años a meses, y los sumamos al mes introducido
                anomes = ano*12;
                mesactual = mes-1+anomes;



                //Pedimos al usuario el numero de cuotas de su prestamo
                int cuotas, mesfinal, anofuturo, mesfuturo;
                printf("Introduzca el numero de cuotas (meses)del prestamo: ");
                scanf("%d",&cuotas);


                //Filtramos los datos obtenidos
                if(cuotas<1 || cuotas>1200){
                    printf("Error, el numero de cuotas introducido no es correcto");

                }else{


                    //Calculamos segun las cuotas cual será el mes de finalizacion del prestamo
                    mesfinal=mesactual+cuotas;

                    //Pasamos de años a meses
                    anofuturo=mesfinal/12;
                    mesfuturo=mesfinal%12;


                    //Mostramos el resultado: Fecha de finalizacion del prestamo
                    //Con el Switch haremos que muestre el mes de forma alfabética
                    printf("El prestamo finaliza el: %d de ",dia);


                    switch(mesfuturo){

                    case 0:  printf("Enero");
                        break;
                    case 1:  printf("Febrero");
                        break;
                    case 2:  printf("Marzo");
                        break;
                    case 3:  printf("Abril");
                        break;
                    case 4:  printf("Mayo");
                        break;
                    case 5:  printf("Junio");
                        break;
                    case 6:  printf("Julio");
                        break;
                    case 7:  printf("Agosto");
                        break;
                    case 8:  printf("Septiembre");
                        break;
                    case 9:  printf("Octubre");
                        break;
                    case 10:  printf("Noviembre");
                        break;
                    case 11:  printf("Diciembre");
                        break;
                    }

                    //mostramos el año
                    printf(" de %d\n", anofuturo);


                }


            }



        }
    }


    //Finalizamos el programa
    return 0;
}
