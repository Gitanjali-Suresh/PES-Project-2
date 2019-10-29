/*************** Header files ****************/
#include "led.h"
#include <stdint.h>
#include <stdio.h>
#include "fsl_debug_console.h"
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
/*************** Function prototype declarations ****************/
void Delay(uint32_t dly);
void Blink(void);
void led_Initialize(void);
/*************** Global variable declarations ****************/
uint32_t t_cycle[20] = {3000,1000,2000,600,1000,400,1000,200,500,100,500,100,500,100,1000,200,1000,400,2000,600};	/***** Timing Loop *****/
volatile static uint32_t color;		/***** variable for 3 on and off cycles *****/
uint32_t cycle;			/***** Variable indexing the timing loop *****/
uint32_t ct;		/***** variable for 10 complete cycles *****/
/************** Function for initializing the board and the LEDs ************/
void led_Initialize(void)
{
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
	BOARD_InitDebugConsole();
	LED_RED_INIT(1);
	LED_GREEN_INIT(1);
	LED_BLUE_INIT(1);
}
/************** Function for blinking the LEDs ************/
void Blink(void)
{
	cycle = 0;
	ct = 9;
	while(ct!=0)
	{
		if(ct == 9 && cycle == 0)		/***** Checking for the start of program *****/
		{
			#ifdef FB_RUN
				PRINTF("FB Run Version\n\r");
			#endif
			#ifdef FB_DEBUG
				PRINTF("FB Debug Version\n\r");
			#endif
			PRINTF("Program Start... \n\r");
			cycle = 0;
			PRINTF("===========================================================\n\r");
			PRINTF("Cycle %u.\n\r",(10-ct));		/***** Printing the number of the cycle ****/
			PRINTF("===========================================================\n\r");
		}
		/***** Looping 3 on and off cycles for every color *****/
		/***** Color Pattern - RED GREEN BLUE *****/
		for(color = 3;color > 0; cycle++,color--)
		{
			if(cycle == 20)		/***** Reinitializing the index of timing loop at end *****/
			{
				cycle = 0;
				ct--;
				PRINTF("===========================================================\n\r");
        		PRINTF("Cycle %u.\n\r",(10-ct));
        		PRINTF("===========================================================\n\r");
			}
			/***** Blinking the LED *****/
			/***** Printing the status along with time on the terminal *****/
			#ifdef FB_RUN
				LED_RED_ON();
				PRINTF("RED LED ON for %u ms.\n\r",t_cycle[cycle]);
				Delay(t_cycle[cycle]);
				LED_RED_OFF();
				PRINTF("RED LED OFF for %u ms.\n\r",t_cycle[++cycle]);
				Delay(t_cycle[cycle]);
				PRINTF("-----------------------------------------------\n\r");
			#endif
			/***** Printing the status along with value passed to the wait loop on the terminal *****/
			#ifdef FB_DEBUG
				LED_RED_ON();
				PRINTF("RED LED ON %u\n\r",t_cycle[cycle]);
				Delay(t_cycle[cycle]);
				LED_RED_OFF();
				PRINTF("RED LED OFF %u\n\r",t_cycle[++cycle]);
				Delay(t_cycle[cycle]);
				PRINTF("-----------------------------------------------\n\r");
			#endif
		}
		for(color = 3;color > 0; cycle++,color--)
		{
			if(cycle == 20)
			{
				cycle = 0;
				ct--;
				PRINTF("===========================================================\n\r");
        		PRINTF("Cycle %u.\n\r",(10-ct));
        		PRINTF("===========================================================\n\r");
			}
			#ifdef FB_RUN
				LED_GREEN_ON();
				PRINTF("GREEN LED ON for %u ms.\n\r",t_cycle[cycle]);
				Delay(t_cycle[cycle]);
				LED_GREEN_OFF();
				PRINTF("GREEN LED OFF for %u ms.\n\r",t_cycle[++cycle]);
				Delay(t_cycle[cycle]);
				PRINTF("-----------------------------------------------\n\r");
			#endif
			#ifdef FB_DEBUG
				LED_GREEN_ON();
				PRINTF("GREEN LED ON %u\n\r",t_cycle[cycle]);
				Delay(t_cycle[cycle]);
				LED_GREEN_OFF();
				PRINTF("GREEN LED OFF %u \n\r",t_cycle[++cycle]);
				Delay(t_cycle[cycle]);
				PRINTF("-----------------------------------------------\n\r");
			#endif
		}
		for(color = 3;color > 0; cycle++,color--)
		{
			if(cycle == 20)
			{
				cycle = 0;
				ct--;
				PRINTF("===========================================================\n\r");
        		PRINTF("Cycle %u.\n\r",(10-ct));
        		PRINTF("===========================================================\n\r");
			}
			#ifdef FB_RUN
				LED_BLUE_ON();
				PRINTF("BLUE LED ON for %u ms.\n\r",t_cycle[cycle]);
				Delay(t_cycle[cycle]);
				LED_BLUE_OFF();
				PRINTF("BLUE LED OFF for %u ms.\n\r",t_cycle[++cycle]);
				Delay(t_cycle[cycle]);
				PRINTF("-----------------------------------------------\n\r");
			#endif
			#ifdef FB_DEBUG
				LED_BLUE_ON();
				PRINTF("BLUE LED ON %u \n\r",t_cycle[cycle]);
				Delay(t_cycle[cycle]);
				LED_BLUE_OFF();
				PRINTF("BLUE LED OFF %u \n\r",t_cycle[++cycle]);
				Delay(t_cycle[cycle]);
				PRINTF("-----------------------------------------------\n\r");
			#endif
		}
		/***** For finishing the timing cycles in the last count *****/
		if(ct == 0)
		{
			while(cycle != 20)
			{
				#ifdef FB_RUN
					LED_RED_ON();
					PRINTF("RED LED ON for %u ms.\n\r",t_cycle[cycle]);
					Delay(t_cycle[cycle]);
					LED_RED_OFF();
					PRINTF("RED LED OFF for %u ms.\n\r",t_cycle[++cycle]);
					Delay(t_cycle[cycle]);
					PRINTF("-----------------------------------------------\n\r");
					cycle++;
				#endif
				#ifdef FB_DEBUG
					LED_RED_ON();
					PRINTF("RED LED ON %u\n\r",t_cycle[cycle]);
					Delay(t_cycle[cycle]);
					LED_RED_OFF();
					PRINTF("RED LED OFF %u\n\r",t_cycle[++cycle]);
					Delay(t_cycle[cycle]);
					PRINTF("-----------------------------------------------\n\r");
				#endif
			}
		}
		/***** For terminating the FB version *****/
		if(ct == 0 && cycle == 20)
		{
			PRINTF("===========================================================\n\r");
			PRINTF("Program End! \n\r");
			PRINTF("===========================================================\n\r");

		}
	}

}
/*************** Delay function for generating 1ms delay approximately ****************/
void Delay(uint32_t dly)
{
	uint32_t i = dly*7000;		/****** As clock is 8MHz *****/
	while(i!=0)
	{
		i--;		/***** Wasting MCU cycles to get the desired delay ******/
	}
}
