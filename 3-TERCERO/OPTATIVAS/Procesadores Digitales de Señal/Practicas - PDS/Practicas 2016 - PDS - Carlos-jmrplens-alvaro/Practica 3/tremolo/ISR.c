#include "Talkthrough.h"

int modo=0;  
int f=1;
int A=1;    
//--------------------------------------------------------------------------//
// Function:	Sport0_RX_ISR												//
//																			//
// Description: This ISR is executed after a complete frame of input data 	//
//				has been received. The new samples are stored in 			//
//				iChannel0LeftIn, iChannel0RightIn, iChannel1LeftIn and 		//
//				iChannel1RightIn respectively.  Then the function 			//
//				Process_Data() is called in which user code can be executed.//
//				After that the processed values are copied from the 		//
//				variables iChannel0LeftOut, iChannel0RightOut, 				//
//				iChannel1LeftOut and iChannel1RightOut into the dma 		//
//				transmit buffer.											//
//--------------------------------------------------------------------------//
EX_INTERRUPT_HANDLER(Sport0_RX_ISR)
{
	// confirm interrupt handling
	*pDMA1_IRQ_STATUS = 0x0001;

	// copy input data from dma input buffer into variables
	iChannel0LeftIn = iRxBuffer1[INTERNAL_ADC_L0];
	iChannel0RightIn = iRxBuffer1[INTERNAL_ADC_R0];
	iChannel1LeftIn = iRxBuffer1[INTERNAL_ADC_L1];
	iChannel1RightIn = iRxBuffer1[INTERNAL_ADC_R1];

	// call function that contains user code
	Process_Data();				

	// copy processed data from variables into dma output buffer
	iTxBuffer1[INTERNAL_DAC_L0] = iChannel0LeftOut;
	iTxBuffer1[INTERNAL_DAC_R0] = iChannel0RightOut;
	iTxBuffer1[INTERNAL_DAC_L1] = iChannel1LeftOut;
	iTxBuffer1[INTERNAL_DAC_R1] = iChannel1RightOut;
}

//--------------------------------------------------------------------------//
// Function:	FlagA_ISR													//
//																			//
// Parameters:	None														//
//																			//
// Return:		None														//
//																			//
// Description:	This ISR is called every time the button connected to PF8	//
//				is pressed.													//
//				The state of flag sLight_Move_Direction is changed, so the	//
//				shift-direction for the LED pattern in Timer0_ISR changes.	//
//--------------------------------------------------------------------------//


EX_INTERRUPT_HANDLER(FlagA_ISR)
{
	if (*pFIO_FLAG_D == 0x0100) {  //sw4
	A=A+1;
	modo=1;
	if (A>=10){
		A=10;	
	}
	}
	if(*pFIO_FLAG_D == 0x0400){    // sw6 
		
	
		modo=1;
		f=f+1;

	}
	if(*pFIO_FLAG_D == 0x0800 ){	 //sw7
		modo=0;
		A=1;
		f=1;
		
	}
	if(*pFIO_FLAG_D == 0x0200  ){	 //   sw5 
	modo=1;
        f=f-1;
	if (f<=1){
		f=1;	
	}
	}
	// confirm interrupt handling
	*pFIO_FLAG_C = 0x0F00;


}

