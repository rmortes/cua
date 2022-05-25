#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
void poladivf(void){
    float VDD,R1,R2,RD,RS, VP,IDSS;
    float IDS[2],IDSB,VGS,VDS,VDG,a,b,c,VTH,RTH;
    printf("Introduzca VDD (Voltios): ");
    scanf("%f",&VDD);
    printf("\n Introduzca R1 (Ohmios): ");
    scanf("%f",&R1);
    printf("\n Introduzca R2 (Ohmios): ");
    scanf("%f",&R2);
    printf("\n Introduzca RS (Ohmios): ");
    scanf("%f",&RS);
    printf("\n Introduzca RD (Ohmios): ");
    scanf("%f",&RD);
    printf("\n Introduzca VP (Voltios): ");
    scanf("%f",&VP);
    printf("\n Introduzca IDSS (Amperios) : ");
    scanf("%f",&IDSS);
    VTH=(VDD*R2)/(R1+R2);
    RTH=(R1*R2)/(R1+R2);
    a=(pow((RS/VP),2))*IDSS;
    c=(1-pow((VTH/RS),2))*IDSS;
    b=(-2*(1-(VTH/RS))*(RS/VP)*IDSS)-1;
    IDS[0]=(-b+sqrt(pow(b,2)-4*a*c))/(2*a);
    IDS[1]=(-b-sqrt(pow(b,2)-4*a*c))/(2*a);
    VDS=VDD-(IDS[0]*(RD+RS));
    IDSB=IDS[0];
    if(VDS<0){
        VDS=VDD-(IDS[1]*(RD+RS));
        IDSB=IDS[1];
    }
    VGS=VTH-IDSB*RS;
    VDG=VDS-VGS;
    if(VGS<-VP){
        printf("\n El transistor esta en CORTE\n");
    }
    if(VDG<VP && VGS>-VP){
        printf("\n El transistor se encuentra en la ZONA OHMICA\n");
    }
    if(VGS>-VP && VDG>VP){
        printf("\n Transistor en SATURACION Q(IDS,VDS) Q(%f,%f)\n",IDSB,VDS);
        printf("-----------------------------------------------\n - IDS1= %f A \n - IDS2= %f A \n - VGS= %f V \n - VDS= %f V \n - VDG= %f V \n",IDS[0],IDS[1],VGS,VDS,VDG);
    }
    return;

}

void polautomaticaf(void){
    float VDD,RG,RD,RS, VP,IDSS;
    float IDS[2],IDSB,VGS,VDS,VDG,a,b,c;
    printf("Introduzca VDD (Voltios): ");
    scanf("%f",&VDD);
    printf("\n Introduzca RG (Ohmios): ");
    scanf("%f",&RG);
    printf("\n Introduzca RS (Ohmios): ");
    scanf("%f",&RS);
    printf("\n Introduzca RD (Ohmios): ");
    scanf("%f",&RD);
    printf("\n Introduzca VP (Voltios): ");
    scanf("%f",&VP);
    printf("\n Introduzca IDSS (Amperios) : ");
    scanf("%f",&IDSS);
    a=(pow((RS/VP),2))*IDSS;
    c=IDSS;
    b=(-2*(RS/VP)*IDSS)-1;
    IDS[0]=(-b+(sqrt(pow(b,2)-4*a*c)))/(2*a);
    IDS[1]=(-b-(sqrt(pow(b,2)-4*a*c)))/(2*a);
    VDS=VDD-(IDS[0]*(RD+RS));
    IDSB=IDS[0];
    if(VDS<0){
        VDS=VDD-(IDS[1]*(RD+RS));
        IDSB=IDS[1];
    }
    VGS=-IDSB*RS;
    VDG=VDS-VGS;
    if(VGS<-VP){
        printf("\n El transistor esta en CORTE\n");
    }
    if(VDG<VP && VGS>-VP){
        printf("\n El transistor se encuentra en la ZONA OHMICA\n");
    }
    if(VGS>-VP && VDG>VP){
        printf("\n Transistor en SATURACION Q(IDS,VDS) Q(%f,%f)\n",IDSB,VDS);

    }
    printf("-----------------------------------------------\n - IDS1= %f A \n - IDS2= %f A \n - VGS= %f V \n - VDS= %f V \n - VDG= %f V \n",IDS[0],IDS[1],VGS,VDS,VDG);
    return;
}

void polfijaf(void){
    float VDD, E,RG,RD,RS, VP,IDSS;
    float IDS[2],IDSB,VGS,VDS,VDG,a,b,c;
    printf("Introduzca VDD (Voltios): ");
    scanf("%f",&VDD);
    printf("Introduzca E (Voltios): ");
    scanf("%f",&E);
    printf("\n Introduzca RG (Ohmios): ");
    scanf("%f",&RG);
    printf("\n Introduzca RS (Ohmios): ");
    scanf("%f",&RS);
    printf("\n Introduzca RD (Ohmios): ");
    scanf("%f",&RD);
    printf("\n Introduzca VP (Voltios): ");
    scanf("%f",&VP);
    printf("\n Introduzca IDSS (Amperios) : ");
    scanf("%f",&IDSS);
    a=(pow((RS/VP),2))*IDSS;
    c=(1-pow((E/RS),2))*IDSS;
    b=(-2*(1-(E/RS))*(RS/VP)*IDSS)-1;
    IDS[0]=(-b+sqrt(pow(b,2)-4*a*c))/(2*a);
    IDS[1]=(-b-sqrt(pow(b,2)-4*a*c))/(2*a);
    VDS=VDD-(IDS[0]*(RD+RS));
    IDSB=IDS[0];
    if(VDS<0){
        VDS=VDD-(IDS[1]*(RD+RS));
        IDSB=IDS[1];
    }
    VGS=E-IDSB*RS;
    VDG=VDS-VGS;
    if(VGS<-VP){
        printf("\n El transistor esta en CORTE\n");
    }
    if(VDG<VP && VGS>-VP){
        printf("\n El transistor se encuentra en la ZONA OHMICA\n");
    }
    if(VGS>-VP && VDG>VP){
        printf("\n Transistor en SATURACION Q(IDS,VDS) Q(%f,%f)\n",IDSB,VDS);
        printf("-----------------------------------------------\n - IDS1= %f A \n - IDS2= %f A \n - VGS= %f V \n - VDS= %f V \n - VDG= %f V \n",IDS[0],IDS[1],VGS,VDS,VDG);
    }
    return;

}
void peqseauto(float hfe, float RC, float RE){
    float hie,RL,GV,RCL;
    printf("\n Introduzca el valor de hie (Ohmios):");
    scanf("%f",&hie);
    printf("\n Introduzca el valor de RL (Ohmios):");
    scanf("%f",&RL);
    RCL=(RC*RL)/(RC+RL);
    GV=(-hfe*RCL)/(hie+RE*(hfe+1));
    printf("\n La ganancia de tension es: %f",GV);
    return;
}

void peqsepolcb(float hfe, float RC, float RE, float RB){
    float hie,RL,GV,RCL;
    printf("\n Introduzca el valor de hie (Ohmios):");
    scanf("%f",&hie);
    printf("\n Introduzca el valor de RL (Ohmios):");
    scanf("%f",&RL);
    RCL=(RC*RL)/(RC+RL);
    GV=(((hie+RE*(1+hfe))/RB)-hfe)/(((1/RB)+(1/RCL))*(hie+RE*(1+hfe)));
    printf("\n La ganancia de tension es: %f",GV);
    return;
}

void peqsefij(float hfe, float RC, float RE){
    float hie,RL,GV;
    printf("\n Introduzca el valor de hie (Ohmios):");
    scanf("%f",&hie);
    printf("\n Introduzca el valor de RL (Ohmios):");
    scanf("%f",&RL);
    GV=(-hfe*((RC*RL)/(RC+RL)))/(hie+RE*(1+hfe));
    printf("\n La ganancia de tension es: %f",GV);
    return;
}

void polautomatica(void){
    float VCC,R1,R2,RC,RE,BETA;
    float VBEON=0.7, VCESAT=0.2;
    float IB,IC,IE,VCE,VTH,RTH;
    printf("Introduzca Vcc (Voltios): ");
    scanf("%f",&VCC);
    printf("\n Introduzca R1 (Ohmios): ");
    scanf("%f",&R1);
    printf("\n Introduzca R2 (Ohmios): ");
    scanf("%f",&R2);
    printf("\n Introduzca RC (Ohmios): ");
    scanf("%f",&RC);
    printf("\n Introduzca RE (Ohmios): ");
    scanf("%f",&RE);
    printf("\n Introduzca la amplificacion : ");
    scanf("%f",&BETA);
    VTH=(VCC*R2)/(R1+R2);
    RTH=(R1*R2)/(R1+R2);
    IB=(VTH-VBEON)/(RTH+RE*(1+BETA));
    IC=IB*BETA;
    IE=IB+IC;
    VCE=VCC-IC*RC-IE*RE;
    if(IB<0){
        printf("\n IB=IC=IE=0 , VBE<VBEON , Transistor esta en CORTE");
    }
    if(IB>0 && VCE<0){
        printf("\n Transistor  en SATURACION , VCE=VCESAT=0.2");
        IC=(VCC-VCESAT-RE*IE)/RC;
        printf("\n IC<IB*BETA  IC= %f A",IC);
    }
    if(IB>0 && VCE>0){
        printf("\n Transistor en CONDUCCION Q(IC,VCE) Q(%f,%f) ",IC,VCE);
        printf("\n Valor de IB,IC,IE y VCE \n ----------------------- \n - IB= %f A \n - IC= %f A \n - IE= %f A \n - VCE= %f V",IB,IC,IE,VCE);
    }
    printf("\n \n Pulse para obtener la ganancia de tension del equivalente en pequeña senal");
    getche();


    peqseauto(BETA, RC, RE);
    return;
}

void polcb(void){
    float VCC,RB,RC,RE,BETA;
    float VBEON=0.7, VCESAT=0.2;
    float IB,IC,IE,VCE;
    printf("Introduzca Vcc (Voltios): ");
    scanf("%f",&VCC);
    printf("\n Introduzca RB (Ohmios): ");
    scanf("%f",&RB);
    printf("\n Introduzca RC (Ohmios): ");
    scanf("%f",&RC);
    printf("\n Introduzca RE (Ohmios): ");
    scanf("%f",&RE);
    printf("\n Introduzca la amplificacion : ");
    scanf("%f",&BETA);
    IB=(VCC-VBEON)/(RC*(1+BETA)+RB+RE*(1+BETA));
    IC=IB*BETA;
    IE=IB+IC;
    VCE=VCC-RC*(IB+IC)-RE*IE;
    if(IB<0){
        printf("\n IB=IC=IE=0 , VBE<VBEON , Transistor esta en CORTE");
    }
    if(IB>0 && VCE<0){
        printf("\n Transistor  en SATURACION , VCE=VCESAT=0.2");
        IC=(VCC-VCESAT-RE*IE)/RC;
        printf("\n IC<IB*BETA  IC= %f A",IC);
    }
    if(IB>0 && VCE>0){
        printf("\n Transistor en CONDUCCION Q(IC,VCE) Q(%f,%f) ",IC,VCE);
        printf("\n Valor de IB,IC,IE y VCE \n ----------------------- \n - IB= %f A \n - IC= %f A \n - IE= %f A \n - VCE= %f V",IB,IC,IE,VCE);
    }
    printf("\n \n Pulse para obtener la ganancia de tension del equivalente en pequeña senal");
    getche();

    peqsepolcb(BETA, RC, RE,RB);

    return;

}

void polfija(void){
   float VCC,RB,RC,RE,BETA;
   float VBEON=0.7, VCESAT=0.2;
   float IB,IC,IE,VCE;
   printf("Introduzca Vcc (Voltios): ");
   scanf("%f",&VCC);
   printf("\n Introduzca RB (Ohmios): ");
   scanf("%f",&RB);
   printf("\n Introduzca RC (Ohmios): ");
   scanf("%f",&RC);
   printf("\n Introduzca RE (Ohmios): ");
   scanf("%f",&RE);
   printf("\n Introduzca la amplificacion : ");
   scanf("%f",&BETA);
   IB=(VCC-VBEON)/(RB+RE*(1+BETA));
   IC=BETA*IB;
   IE=IB+IC;
   VCE=VCC-IC*RC-RE*IE;
   if(IB<0){
       printf("\n IB=IC=IE=0 , VBE<VBEON , Transistor en CORTE");
   }
   if(IB>0 && VCE<0){
       printf("\n  Transistor  en SATURACION , VCE=VCESAT=0.2");
       IC=(VCC-VCESAT-RE*IE)/RC;
       printf("\n IC<IB*BETA  IC= %f A",IC);
   }
   if(IB>0 && VCE>0){
       printf("\n Transistor en CONDUCCION Q(IC,VCE) Q(%f,%f) ",IC,VCE);
       printf("\n Valor de IB,IC,IE y VCE \n ----------------------- \n - IB= %f A \n - IC= %f A \n - IE= %f A \n - VCE= %f V",IB,IC,IE,VCE);
   }
   printf("\n \n Pulse para obtener la ganancia de tension del equivalente en pequeña senal");
   getche();
   peqsefij(BETA, RC, RE);
   return;
}

int main(void){
int a,a2,b,c=0;
while(c==0){
    a=0,b=0,a2=0;
    while(b<=0 || b>3){
        printf("\n Selecciona el tipo de transistor(1-3): \n 1.FET \n 2.BJT \n 3.SALIR \n");
        scanf("%d",&b);
    }
    switch(b){
    case 1:
        while(a2<=0 || a2>4){
        printf("Selecciona el tipo de polarizacion(1-3): \n 1.Polarizacion fija \n 2.Polarizacion automatica \n 3.Polarizacion por divisor de tension \n 4.Atras\n");
        scanf("%d",&a2);
        }
        switch(a2){
        case 1:
            polfijaf();
            break;
        case 2:
            polautomaticaf();
            break;
        case 3:
            poladivf();
            break;
        case 4:
            break;
        }
        break;

    case 2:
        while(a==0 || a>4){
        printf("Selecciona el tipo de polarizacion(1-3): \n 1.Polarizacion fija \n 2.Polarizacion colector-base \n 3.Polarizacion automatica \n 4.Atras \n");
        scanf("%d",&a);
        }
        switch(a){
        case 1:
            polfija();
            break;
        case 2:
            polcb();
            break;
        case 3:
            polautomatica();
            break;
        case 4:
            break;
        }
        break;
    case 3:
        c=1;
        break;


    }



}
return(0);
}
