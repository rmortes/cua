/* Cabecera */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void EspacioEstados1(float a,float b,float e,float f,float K,float x0,float T,float tf);

void Grafico(int F,int C,float *x,int N);

/* Función principal */
int main (void)
{
	float PARa,PARb,PARe,PARf,escalon,CI,intervalo,tiempo;
   /* Obtención de datos */
   printf("Introduzca a: ");   scanf("%f",&PARa);
   printf("Introduzca b: ");   scanf("%f",&PARb);
   printf("Introduzca e: ");   scanf("%f",&PARe);
   printf("Introduzca f: ");   scanf("%f",&PARf);
   printf("Introduzca tamano escalon (K): ");   scanf("%f",&escalon);
   printf("Introduzca condicion inicial (x0): ");   scanf("%f",&CI);
   printf("Introduzca intervalo de muestreo (T): ");   scanf("%f",&intervalo);
   printf("Introduzca tiempo de la simulacion (tf): ");   scanf("%f",&tiempo);
   printf("\nHa introducido:\na = %f\nb = %f\ne = %f\nf = %f\nEscalon = %f\nCondInicial = %f\nIntervalo = %f\nTiempo = %f\n",PARa,PARb,PARe,PARf,escalon,CI,intervalo,tiempo);
   
   /* Llamada a la función */
   EspacioEstados1(PARa,PARb,PARe,PARf,escalon,CI,intervalo,tiempo);
   
   return 0;
}

void EspacioEstados1(float a,float b,float e,float f,float K,float x0,float T,float tf)
{
 /*
	ESTRATEGIA: *
	*************
	x[n+1]=(1+aT)x[n] + bTg[n]
	luego,
	x[n]=(1+aT)x[n-1] + bTg[n-1] (1)
	
	y[n] = ex[n] + fg[n] =
		 = e*{ (1+aT)x[n-1] + bTg[n-1] } + fg[n] =
		 = e*(1+aT)x[n-1] + ebTg[n-1] + fg[n] (2)
		 
	Como g(n) es un escalón, consideramos que para las n<0, g[n]=0 y para n>0 g[n]=K. (3)
	
	en n=0, por la definición de (3):
	(1) x[0] = x0
	(2) y[0] = ex0 + fg[0] =
			 = ex0 + fK
	
	en n>0
	(1) x[n] = (1+aT)x[n-1] + bTg[n-1] =
			 = (1+aT)x[n-1] + bTK
	(2) y[n] = e*(1+aT)x[n-1] + ebTg[n-1] + fg[n]
	pero, como por (3), g[n-1] = g[n] = K, tenemos
		y[n] = e*(1+aT)x[n-1] + ebTK + fK =
			 = e*(1+aT)x[n-1] + (ebT+f)K (5)
			 
	VARIABLES:
		nf 		== número de periodos escaneados
		n 		== índice que recorre los vectores
		BTK 	== bTK
		EBTFK 	== (ebT+f)*k
		EAT 	== e*(1+AT)
		Y[nf] 	== Vector de salida de tamaño nf (asignación dinámica de memoria "por las bravas")
		X[nf]	== Vector X de tamaño nf (asignación dinámica de memoria "por las bravas")
 */
	int nf,n;
	float EBTFK,EAT,BTK;
	printf("\nESPACIO ESTADOS 1\n");
	nf=(int)ceil(tf/T);
	float Y[nf],X[nf];
	printf("\n%f tiempo\n%f periodo\n%i muestras\n",tf,T,nf);
	BTK=b*T*K;
	EAT=e*(1+a*T); //Será constante, lo calculo una vez sólo.
	EBTFK=(e*b*T+f)*K; //Será constante, lo calculo una vez sólo.
	printf("\nBTK=%f\tEAT=%f\tEBTFK=%f\n",BTK,EAT,EBTFK);
	/* En n=0 */
	X[0]=x0;
	Y[0]=X[0]+f*K;
		for(n=1;n<nf;n++)
	{
		X[n]=EAT*X[n-1]+BTK;
		Y[n]=X[n-1]*EAT+EBTFK;
	}
			Grafico(50,100,Y,nf);

	return;
}

void Grafico(int F,int C,float *x,int N)
{
	int f, c, n, fc, cc;
	float xmin= 1000000.0;
	float xmax=-1000000.0;
	char graf[500][500]={0};
	
	for (n=1;n<N;n++)
	{
		if (x[n]<xmin) xmin = x[n];
		if (x[n]>xmax) xmax = x[n];
	}
	
	for (n=1;n<N;n++)
	{
		fc = ceil(F*((x[n]-xmin)/(xmax-xmin)));
		cc = ceil(C*((float)(n)/N));
		graf[fc][cc]=1;
	}

	printf("\n\n\n\n\nXmax = %5.2f",xmax);  
	for (f=1;f<=(F+2);f++)
	{
		printf("\n");  
		for (c=1;c<=C;c++)
		{
			if(f==1) printf("-");
			else if(f==(F+2)) printf("-");
			else
			{
				if(c==1) printf("|");	
				else if(c==C) printf("|");
				else 
				{
					if (graf[F+2-f][c]) printf("*");
					else printf(" ");
				}
			}
		}
	}	
	printf("\nXmin = %5.2f",xmin);  
}