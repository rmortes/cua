#include <stdio.h>
#include <string.h>

int main (){
//Declaramos variables

char nombre1[50], apellido1[50], apellido2[50];
char nombre2[50], apellido3[50], apellido4[50];

//Introduccion de datos de los usuarios y puesta en mayusculas para poder comparar mejor
printf("Introduzca nombre y apellidos de la primera persona: ");

scanf("%s",nombre1);
scanf("%s",apellido1);
scanf("%s",apellido2);

printf("Introduzca nombre y apellidos de la primera persona: ");

scanf("%s",nombre2);
scanf("%s",apellido3);
scanf("%s",apellido4);

strupr(nombre1); strupr(apellido1); strupr(apellido2);
strupr(nombre2); strupr(apellido3); strupr(apellido4);

// Comprobacion de los datos para saber sus diferentes resultados

if (strcmp(nombre1,nombre2)==0 && strcmp(apellido1,apellido3)==0 && strcmp(apellido2,apellido4)==0)
{
printf(" Resultado: %s_%s_%s y %s_%s_%s son LA MISMA PERSONA\n",nombre1,apellido1,apellido2,nombre2, apellido3,apellido4) ;
} else {

if (strcmp(apellido1,apellido3)==0 && strcmp(apellido2,apellido4)==0)
{
printf( "Resultado: %s_%s_%s y %s_%s_%s son HERMANOS\n",nombre1,apellido1,apellido2,nombre2, apellido3,apellido4) ;
}else {
if (strcmp(apellido1,apellido2)==0 ||strcmp(apellido1,apellido4)==0 || strcmp(apellido2,apellido3)==0 || strcmp(apellido2,apellido4)==0 )
{
printf( "Resultado: %s_%s_%s y %s_%s_%s son PRIMOS\n",nombre1,apellido1,apellido2,nombre2, apellido3,apellido4) ;
} else {

if(strcmp(nombre1,nombre2)==0)
{
printf( "Resultado: %s_%s_%s y %s_%s_%s son TOCAYOS\n",nombre1,apellido1,apellido2,nombre2, apellido3,apellido4) ;
} else {
printf("Resultado: %s_%s_%s y %s_%s_%s no tienen coincidencias\n" ,nombre1,apellido1,apellido2,nombre2, apellido3,apellido4) ;
}
}

}
}

return (0);
}
