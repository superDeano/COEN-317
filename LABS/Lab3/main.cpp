/*
 * Lab3 By Deano
 */

#include "stdbool.h"
#include "xparameters.h"
#include "xil_types.h"
#include "xgpio.h"
#include "xil_io.h"
#include "xil_exception.h"
#include "xtmrctr.h"
#include <iostream>

using namespace std;

//Function declarations
int runFirstPart();
int alternativeFirstPart();
int runSecondPart();
int runThirdPart();

int main(){
	runFirstPart();


    return 0;

}

/*
*
* Function related to the first part of the experiment
*
*/
int runFirstPart() {

	static XGpio GPIOInstance_Ptr;
	  XTmrCtr TimerInstancePtr;

	  int xStatus;

	  cout << "####  Counter Application Starts ####" << endl;


	  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	  //Step-1: AXI GPIO Initialization
	  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	  xStatus = XGpio_Initialize(&GPIOInstance_Ptr, XPAR_AXI_GPIO_FOR_OUTPUT_DEVICE_ID);
	  if(xStatus != XST_SUCCESS){
		    cout << "GPIO A Initialization FAILED" << endl;
		    return 1;
	  }

	  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	  //Step-2: AXI GPIO Set the Direction
	  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	  //XGpio_SetDataDirection(XGpio *InstancePtr, unsigned Channel, u32 DirectionMask);
	  //we use only channel 1, and 0 is the the parameter for output

	  XGpio_SetDataDirection(&GPIOInstance_Ptr, 1, 0);

	  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	  //Step-3: AXI Timer Initialization and Setting
	  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		/*Performs initialization of the TimerInstancePtr as type XTmrCtr*/
	  xStatus = XTmrCtr_Initialize(&TimerInstancePtr, XPAR_AXI_TIMER_0_DEVICE_ID);
	  if(xStatus != XST_SUCCESS){
	    cout <<  "TIMER INIT FAILED" << endl;
	    return 0;
	  }


	   //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	   //Step-4: Setting the timer Reset Value
	   //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	   // XTmrCtr_SetResetValue(XTmrCtr * InstancePtr, u8 TmrCtrNumber,
	   // u32 ResetValue);

		/*Loads a reset value into the timer*/
	  XTmrCtr_SetResetValue(&TimerInstancePtr, 0, 0);


	   //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	   //Step-5: Setting the Timer Option
	   //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*Sets the different modes of the timer and as an up-counter*/
	    XTmrCtr_SetOptions(&TimerInstancePtr, XPAR_AXI_TIMER_0_DEVICE_ID, XTC_CAPTURE_MODE_OPTION);


    // perform a write to the GPIO output port

    int LEDs;

   cout << "Enter the number to be sent to the LEDs" << endl;
   cin >> LEDs;

   // Determine how long it takes to perform a DiscreteWrite to the GPIO

	/*Start the counter*/
    XTmrCtr_Start(&TimerInstancePtr, 0);

  XGpio_DiscreteWrite(&GPIOInstance_Ptr, 1, (u8) LEDs);

  /*stops the timer*/
 XTmrCtr_Stop(&TimerInstancePtr, 0);

  // read the value of the counter register and store it in count
  unsigned int count;
  count = XTmrCtr_GetValue(&TimerInstancePtr, 0);                                        
  cout << " It required Count = " <<  count << " clock cycles to perform the DiscreteWrite" << endl;
	    return 3;
}

/*
*
* Function related to the second part of the experiment
*
*/
int runSecondPart(){

	//Initialize the timer to be in capture mode with overwriting of each capture value and enable capture mode ( HINT : write the hex value 0x19 to the timer control/status register);

	static XGpio GPIOInstance_Ptr;
    XTmrCtr TimerInstancePtr;

    int xStatus;	
	    
   cout << "####  Counter Application Starts ####" << endl;


  	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//Step-1: AXI GPIO Initialization		   
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  xStatus = XGpio_Initialize(&GPIOInstance_Ptr,XPAR_AXI_GPIO_FOR_OUTPUT_DEVICE_ID);

	//load 0 as the initial reset value into the load register of the counter;
	XTmrCtr_SetResetValue(&TimerInstancePtr,0,0)

//load the reset value into the counter (remember to clear the load bit to 0 afterwards so as to enable to counter );
XTmrCtr_SetOptions(&TimerInstancePtr,XPAR_AXI_TIMER_0_DEVICE_ID,XTC_CAPTURE_MODE_OPTION);

//start the timer by setting enable = 1 ;
XTmrCtr_Start(&TimerInstancePtr,1);

cout<< "Press on the switch to capture a value." << endl;
//while( the value of the load register is still equal to 0 )
while (*(Timer_Ptr + 1) == 0)

int capture_value = *(Timer_Ptr + 1) ; // read the captured value of the counter from the load register
//prompt the user to press SW% when they wish to capture a second counter value into the load register;
cout << "You decide when to capture the second value." << endl;
while( capture_value == *(Timer_Ptr + 1))
//{
// keep on waiting until SW5 is pressed
//}

int new_capture_value = *(Timer_Ptr + 1);
int difference_in_values = new_capture_value - capture_value;

//display the difference between new_capture_value and capture_value.
cout << "The difference in time is " << difference_in_values << "." << endl;
return 0;

}


/*
*
* Function related to the third part of the experiment
*
*/
int runThirdPart(){
// configure the timer for PWM mode;
static XGpio GPIOInstance_Ptr;
XTmrCtr TimerInstancePtr;

int xStatus = XGpio_Initialize(&GPIOInstance_Ptr,XPAR_AXI_TIMER_0_DEVICE_ID,XTVC_PWM_MODE_OPTION);

// while(true) {
// Ask user to input the desired period of the PWM signal and the desired duty cycle (either in seconds or as a percentage of the period ) ;
// load the appropriate values into the TLR0 and TLR1 registers as per the formulas given on page 4 of the datasheet
// start both timers; }


	return 3;
}



/*
*
* Function related to an alternative first part of the experiment
*
*/
int alternativeFirstPart(){

static XGpio GPIOInstance_Ptr;
u32* Timer_Ptr = (u32*)XPAR_TMRCTR_0_BASEADDR;
 // base address = control/status reg
 // base address + 4 bytes = load register value (reset value)
 // base address + 8 bytes  = counter register
    int xStatus;
    cout << "####  Ted counter Application Starts ####" << endl;
    
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
//Step-1: AXI GPIO Initialization 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
xStatus = XGpio_Initialize(&GPIOInstance_Ptr,XPAR_AXI_GPIO_FOR_OUTPUT_DEVICE_ID); 
if(xStatus != XST_SUCCESS){
     cout << "GPIO A Initialization FAILED" << endl;
     return 1;
 }
 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
//Step-2: AXI GPIO Set the Direction 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
XGpio_SetDataDirection(XGpio *InstancePtr, unsigned Channel, u32 DirectionMask);
//we use only channel 1, and 0 is the the parameter for output
XGpio_SetDataDirection(&GPIOInstance_Ptr, 1, 0);
// set mode to capture mode and specify up-count 
// 0x001 = capture
// 0x000 = generate mode
*(Timer_Ptr) = 0x001;

// load 0 as the reset value into the load register of the counter
*(Timer_Ptr + 1) = 0;

// now load this value into the counter register by setting load = 1 in control register
*(Timer_Ptr) = 0x021;

// put the load bit off to allow the counter to be enabled when the enable bit = 1
// since when load = 1 , the counter is prevented from running.
// start the timer by setting enable = 1 ; *(Timer_Ptr) = 0x081;
// perform a write to the GPIO output port
XGpio_DiscreteWrite(&GPIOInstance_Ptr, 1, 0xA3); 

// stop the timer by setting enable = 0; 
*(Timer_Ptr) = 0x001;

unsigned int count;
// read the value of the counter register
count = *(Timer_Ptr + 2) ;
cout << “Count = “ << count << endl;

cout << “Timer reloaded with 0” << endl; 
*(Timer_Ptr) = 0x021;
*(Timer_Ptr) = 0x001;
count = *(Timer_Ptr + 2);
cout << “Counter after reload = “<< count << endl;
// determine the overhead in starting and stopping the counter
*(Timer_Ptr) = 0x081; // start the timer 
*(Timer_Ptr) = 0x001; // stop the timer
count = *(Timer_Ptr + 2);

cout << "Time to access memory two times to start and stop timer Counter = " << count <<  endl;

return 0;
}
