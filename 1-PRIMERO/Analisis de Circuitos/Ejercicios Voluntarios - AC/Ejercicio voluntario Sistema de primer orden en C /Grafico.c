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
