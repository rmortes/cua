/*----------------------------------------------------------------------
    · Funciones para el LCD:
	· LCD_Enable: Habilitación del LCD.
	· LCD_REG: Escritura en el LCD.
	· LCD_BUSY: Control si el LCD está ocupado.
		
    · Funciones de usuario.
        · LCD_INI (unsigned char , unsigned char ): Inicializa el LCD.
	· LCD_Control (unsigned char): Utilización del LCD.
	· LCD_Caracter (unsigned char): Representación de un carácter.
	· LCD_Cadena (char []): Representa una cadena.
	· LCD_ColumnaFila (unsigned char , unsigned char): Escribe en la posición indicada por el usuario.	
	· LCD_CGRAM (unsigned char, unsigned char []): Escribe en memoria un carácter diseñado por el usuario.
	---------------------------------------------------------------------------*/

#include "LCD4bits.h"
#include "stdio.h"

/* LCD_Enable: Inicia la lectura/escritura de datos.    
*/
void LCD_Enable (void)
{
  	LCD_OUT |= LCD_E;
	__delay_cycles(2);
	LCD_OUT &= ~LCD_E;
}

/* LCD_REG: Escritura en el LCD
	· dato: Dato de los pines del uC.		

*/
void LCD_REG (unsigned char dato)
{	
  	if (dato & 1)
	  LCD_OUT |= LCD_DB4;
	else
	  LCD_OUT &= ~LCD_DB4;
	
	if (dato & 2)
	  LCD_OUT |= LCD_DB5;
	else
	  LCD_OUT &= ~LCD_DB5;
	
	if (dato & 4)
	  LCD_OUT |= LCD_DB6;
	else
	  LCD_OUT &= ~LCD_DB6;
	
	if (dato & 8)
	  LCD_OUT |= LCD_DB7;
	else
	  LCD_OUT &= ~LCD_DB7;
	
	LCD_Enable();
}

#ifdef BusyFlag_ON

/* LCD_BUSY: Consulta si el LCD está ocupado.
*/
void LCD_BUSY (void)
{	
  	LCD_OUT &= ~LCD_RS;
  	LCD_OUT |= LCD_RW;
	
	LCD_DIR &= ~LCD_DB7;
	
	LCD_OUT |= LCD_E;
	
	while (LCD_DB7 & LCD_IN);
	LCD_OUT &= ~LCD_E;

	LCD_DIR |= LCD_DB7;
	
	LCD_OUT &= ~LCD_RW;
}
#endif


/*
LCD_INI: Inicializa por sw el LCD (Número de bits del bus de datos, el número de 
líneas y el tamaño del carácter). 
	· FuncSet: 	Configura LCD: 1 o 2 líneas y tamaño carácter.
	· EntryMode:	Características de los datos.
. 
*/
void LCD_INI (unsigned char FuncSet, unsigned char EntryMode)
{
#ifdef BusyFlag_ON  
  	LCD_DIR |= LCD_RS+LCD_RW+LCD_E+LCD_DB4+LCD_DB5+LCD_DB6+LCD_DB7;
	LCD_OUT &= ~(LCD_RS + LCD_RW + LCD_E);
#else
  	LCD_DIR |= LCD_RS+LCD_E+LCD_DB4+LCD_DB5+LCD_DB6+LCD_DB7;
	LCD_OUT &= ~(LCD_RS + LCD_E);  		
#endif		
	
	__delay_cycles(IniDelay_1);			// ~ 15 ms
	
	LCD_REG (0x03);
	__delay_cycles(IniDelay_2); 			// ~ 4.1 ms
	
	LCD_REG (0x03);
	__delay_cycles(IniDelay_3); 			// ~ 100 us
	
	LCD_REG (0x03);
	__delay_cycles(GeneralDelay);			// ~ 40 us
	
	LCD_REG (0x02);
	
	__delay_cycles(GeneralDelay);			// ~ 40 us
	
	LCD_REG (0x02);		// Function set  (Modo 4 bits...
 	__delay_cycles(2);	// ...El número de líneas del LCD y el tipo 
	LCD_REG (FuncSet);	// ...de fuente no puede cambiarse despues de este punto
	
	 __delay_cycles(GeneralDelay);			// ~ 40 us
	
	LCD_REG (0x00);		// Display...
	__delay_cycles(2);
	LCD_REG (FuncSet);	// ...OFF
	
	__delay_cycles(GeneralDelay);			// ~ 40 us
	
	LCD_REG (0x00);		// Display...
	__delay_cycles(2);
	LCD_REG (0x01);		// ...Clear
	
	__delay_cycles(DelayDisplayCursor);		// ~ 1.64 ms
	
	LCD_REG (0x00);		// Entry Mode...
	__delay_cycles(2);
	LCD_REG (EntryMode);	// ...Set
	
	__delay_cycles(GeneralDelay);			// ~ 40 us
}


/*
LCD_Control: Función para controlar el encendido del LCD y el cursor.
		· dato: Comando de control.		
*/

void LCD_Control (unsigned char dato)
{
#ifdef BusyFlag_ON
  	LCD_OUT &= ~(LCD_RS + LCD_RW + LCD_E);
 	LCD_REG (dato >> 4); 			// Parte alta
	__delay_cycles(2);
	LCD_REG (dato);
	
	LCD_BUSY ();
#else
	LCD_OUT &= ~(LCD_RS + LCD_E);
 	LCD_REG (dato >> 4); 			// Parte alta
	__delay_cycles(2);
	LCD_REG (dato);
	
	if (dato == ReturnHome || dato == ClearDisplay)
		__delay_cycles(DelayDisplayCursor);	// ~ 1.64 ms
	else
	  	__delay_cycles(GeneralDelay);		// ~ 40 us
#endif  
}

/*LCD_Caracter (unsigned char dato): Representa un carácter en el LCD.
	· dato: Carácter a representar.		
*/

void LCD_Caracter (unsigned char dato)
{
#ifdef BusyFlag_ON
  	LCD_OUT |= LCD_RS;
  	LCD_OUT &= ~(LCD_RW + LCD_E);
	
 	LCD_REG (dato >> 4); 			// Parte alta
	__delay_cycles(2);
	LCD_REG (dato);
	LCD_BUSY ();
#else
	LCD_OUT |= LCD_RS;
  	LCD_OUT &= ~LCD_E;
	
 	LCD_REG (dato >> 4); 			// Parte alta
	__delay_cycles(2);
	LCD_REG (dato);
	__delay_cycles(GeneralDelay);		// ~ 40 us
#endif  
}

/* LCD_Cadena: Representa una cadena definida por el usuario.
	· cadena: Cadena a representar.		
*/
void LCD_Cadena(char cadena[])
{
	char *p;
	
	p = cadena;
	
	while (*p != '\0') {
	LCD_Caracter(*p);
	p++;
	}
}

/* LCD_Entero: Presenta el valor numérico indicado
	· Valor: Valor numérico a representar.		
*/

void LCD_Entero(int valor)
{
	char cadena_numero[16];
        sprintf(cadena_numero, "%u", valor); // Convierte el entero a una cadena de caracteres
	LCD_Cadena (cadena_numero);
}
/*
LCD_Float: Presenta el valor numérico indicado con dos decimales.
	· Valor: Valor numérico a representar.		

*/
// se comenta para no trabajar con float
void LCD_Float(float valor)
{
        int x, y;
        x= (int) valor;
        y= (int)(x-valor)*1000;     //x1000 tres decimales
	char cadena_float[16];
        sprintf(cadena_float, "%d.%03d", x,y); // Convierte el float a una cadena de caracteres
	LCD_Cadena (cadena_float);
	
}

/*
LCD_ColumnaFila: Situa el cursor en la posición (x,y).
		· x: 	Columna en la que nos queremos situar (0-15).
		· y: 	Fila en la que nos queremos situar (0-1).		
*/
void LCD_FilaColumna (unsigned char x, unsigned char y)
{	
  	LCD_Control (0x80 + y + (x << 6));
}

/*
LCD_CGRAM: Representa un carácter diseñado por el usuario.
        · posicion: Dirección en la CGRAM.
        · patrón: Carácter creado por el usuario.

*/
void LCD_CGRAM (unsigned char posicion, unsigned char patron[])
{
#ifdef BusyFlag_ON
	 LCD_OUT &= ~(LCD_RS + LCD_RW + LCD_E);
	 
	 LCD_REG ((0x40 + posicion) >> 4);	// Direccion 0x40 + posicion
	 __delay_cycles(2);
	 LCD_REG (0x40 + posicion);
	 
	 LCD_BUSY ();
	 
	 LCD_OUT |= LCD_RS;
	 
	 for (unsigned char i = 0; i < 8; i++)
	 {
	   	LCD_REG (patron[i] >> 4);	
	 	__delay_cycles(2);
	 	LCD_REG (patron[i]);
	 
	 	LCD_BUSY ();

	 	LCD_OUT |= LCD_RS;
	 }
#else
	 LCD_OUT &= ~(LCD_RS + LCD_E);
	 
	 LCD_REG ((0x40 + posicion) >> 4);	
	 __delay_cycles(2);
	 LCD_REG (0x40 + posicion);
	 
	 __delay_cycles(GeneralDelay);		// ~ 40 us
	 
	 LCD_OUT |= LCD_RS;
	 
	 for (unsigned char i = 0; i < 8; i++)
	 {
	   	LCD_REG (patron[i] >> 4);	
	 	__delay_cycles(2);
	 	LCD_REG (patron[i]);
	 
	 	__delay_cycles(GeneralDelay);	// ~ 40 us

	 	LCD_OUT |= LCD_RS;
	 }
#endif  
	 
	 LCD_OUT &= ~LCD_RS;
}

