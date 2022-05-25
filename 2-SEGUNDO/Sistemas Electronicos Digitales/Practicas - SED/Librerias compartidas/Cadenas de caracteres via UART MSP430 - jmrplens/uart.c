int tx_flag;			// Flag para saber si se ha terminado la transmision
char tx_char;			// Caracter que se envia a traves de la UART
int rx_flag;			// Flag para saber si se ha terminado la recepcion
char rx_char;			// Caracter que se recibe a traves de la UART

void config_uart(void)
{
	P1SEL = BIT1 + BIT2;					//Setup the I/O
	P1SEL2 = BIT1 + BIT2;
    UCA0CTL1 |= UCSSEL_2; 				// Reloj SMCLK
							            // Para MCLK 8MHz, 9600Baud, UCBRx=52, UCBRSx=0, UCBRFx=1
	UCA0BR0 = 52;                  		//8MHz, OSC16, 9600
	UCA0BR1 = 0;                   	 	//((8MHz/9600)/16) = 52.08333
	UCA0MCTL = 0x10|UCOS16; 			//UCBRFx=1,UCBRSx=0, UCOS16=1
	UCA0CTL1 &= ~UCSWRST; 				// Maquina de estados USCI
	IE2 |= UCA0RXIE; 					// Activa interrupciones de recepcion

	rx_flag = 0;
	tx_flag = 0;
}

unsigned char uart_leec()				// Recibe un caracter de la UART
{
	while (rx_flag == 0);		 		// Espera a que la recepcion de la UA este disponible
	rx_flag = 0;						// Borra el flag
    return rx_char;                     // Devuelve el caracter leido
}


void uart_lees(char* cadena, int length)// Recibe un string de la UART
{
	int i = 0;

	while((i < length))					// Recorre la cadena en toda su longitud y lo envia a leer caracter
	{
		cadena[i] = uart_leec();
		if(cadena[i] == '\r')			// Si se recibe un retorno, se termina de transmitir la cadena
		{
			for( ; i < length ; i++)	// Borra el resto de la cadena, incluido el /r recibido
			{
				cadena[i] = '\0';
			}
			break;
		}
		i++;
	}
}

void uart_enviac(unsigned char c)
{
	tx_char = c;						// Envia un caracter a la UART
	IE2 |= UCA0TXIE; 					// Activa las interrupciones de transmision
	while(tx_flag == 1);				// Espera a que se envie el caracter
	tx_flag = 1;						// Reactivamos el flag para el proximo envio
}

void uart_envias(char *str)				// Envia un string a la UART
{
     while(*str) uart_enviac(*str++);	// Recorre la cadena y envia cada caracter a enviar caracter
}

/* Interrupcion de transmision */
#pragma vector = USCIAB0TX_VECTOR		
__interrupt void USCI0TX_ISR(void)
{
	UCA0TXBUF = tx_char;				// Copia un caracter al buffer del transmision
	tx_flag = 0;						// Borra el flag de transmision
	IE2 &= ~UCA0TXIE; 					// Desactiva la interrupcion para no sobrecargar con envios vacios
}

/* Interrupcion de recepcion */
#pragma vector = USCIAB0RX_VECTOR		
__interrupt void USCI0RX_ISR(void)
{
	rx_char = UCA0RXBUF;				// Copia un caracter al buffer del recepcion
	rx_flag = 1;						// Configuramos el flag de recepcion

}
