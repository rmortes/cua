#include "Talkthrough.h"
#include "math.h"

extern int modo;
extern int f;
extern int A;

float  pi=3.1416;
float tremolo;
int n=0;

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
	tremolo = A*sin(2*pi*f*n/44100);
	n=n+1;
	
	if (modo == 0) {   
	iChannel0LeftOut = iChannel0LeftIn;
	iChannel0RightOut = iChannel0RightIn;
	iChannel1LeftOut = iChannel1LeftIn;
	iChannel1RightOut = iChannel1RightIn;
	}

	if(modo==1){		
	iChannel0LeftOut = tremolo*iChannel0LeftIn;
	iChannel0RightOut =tremolo*iChannel0RightIn;
	iChannel1LeftOut = tremolo*iChannel1LeftIn;
	iChannel1RightOut =tremolo*iChannel1LeftIn;
	}
		
}
