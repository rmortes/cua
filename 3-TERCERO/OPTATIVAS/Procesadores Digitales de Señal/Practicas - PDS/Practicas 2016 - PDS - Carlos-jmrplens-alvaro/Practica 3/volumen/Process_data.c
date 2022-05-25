#include "Talkthrough.h"

extern int modo;
extern int volumen;


//--------------------------------------------------------------------------//
// Function:	Process_Data()												//
//																			//
// Description: This function is called from inside the SPORT0 ISR every 	//
//				time a complete audio frame has been received. The new 		//
//				input samples can be found in the variables iChannel0LeftIn,//
//				iChannel0RightIn, iChannel1LeftIn and iChannel1RightIn 		//
//				respectively. The processed	data should be stored in 		//
//				iChannel0LeftOut, iChannel0RightOut, iChannel1LeftOut,		//
//				iChannel1RightOut, iChannel2LeftOut and	iChannel2RightOut	//
//				respectively.												//
//--------------------------------------------------------------------------//
void Process_Data(void)
{
	if (modo == 0){
	iChannel0LeftOut = iChannel0LeftIn;
	iChannel0RightOut = iChannel0RightIn;
	iChannel1LeftOut = iChannel1LeftIn;
	iChannel1RightOut = iChannel1RightIn;
	}
	if(modo==2){
	iChannel0LeftOut = 0;
	iChannel0RightOut = iChannel0RightIn;
	iChannel1LeftOut = 0;
	iChannel1RightOut = iChannel1RightIn;
	}
	if(modo==3){
	iChannel0LeftOut = iChannel0LeftIn;
	iChannel0RightOut = 0;
	iChannel1LeftOut = iChannel1LeftIn;
	iChannel1RightOut = 0;
	}
	if(modo==4){		
	iChannel0LeftOut =  volumen*iChannel0LeftIn;
	iChannel0RightOut = volumen*iChannel0RightIn;
	iChannel1LeftOut =  volumen*iChannel1LeftIn;
	iChannel1RightOut = volumen*iChannel1LeftIn;
	}	
}
