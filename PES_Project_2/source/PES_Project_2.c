/******************************************************************************
*                                                                             *
*                       PRINCIPLES OF EMBEDDED SOFTWARE                       *
*                                  PROJECT 2                                  *
*   Project By:GITANJALI SURESH (GISU9983) & RUCHA BORWANKAR (RUBO1268)       *
*                   Cross Platform IDE: MCUXpresso IDE v11                    *
*                   Compiler: MinGW/GNU gcc v8.2.0 (PC version)               *
*                       Cross-Compiler: ARM GCC (FB version)                  *
*                                                                             *
*******************************************************************************/
/*************** Header files ****************/
#include <stdio.h>				/***** For printf() *****/
#include <stdint.h>				/***** For standard int datatypes *****/
#include <time.h>				/***** For delay and timestamps *****/
/*************** Header files and functions specific for FB_RUN ****************/
#ifdef FB_RUN
	#include "led.h"
	void Blink(void);
	void led_Initialize(void);
#endif
/*************** Header files and functions specific for FB_DEBUG ****************/
#ifdef FB_DEBUG
	#include "led.h"
	void Blink(void);
	void led_Initialize(void);
#endif
/*************** Global variable declarations ****************/
uint32_t t_cyc[20] = {3000,1000,2000,600,1000,400,1000,200,500,100,500,100,500,100,1000,200,1000,400,2000,600};	/***** Timing Loop *****/
volatile static uint32_t clr;		/***** variable for 3 on and off cycles *****/
uint32_t count;			/***** variable for 10 complete cycles *****/
/*************** Function prototype declarations ****************/
void delay(uint32_t dly);
void timestamp(void);
/*************** Main Function ****************/
int main(void)
{
	/*************** FB Run version ****************/
	#ifdef FB_RUN
		led_Initialize();	/***** Initialization of LEDs on board *****/
		Blink();			/***** Blinking of LEDs *****/
	#endif
	/*************** FB Debug version ****************/
	#ifdef FB_DEBUG
		led_Initialize();		/***** Initialization of LEDs on board *****/
		Blink();				/***** Blinking of LEDs *****/
	#endif
	/*************** PC Run version ****************/
	#ifdef PC_RUN
    	count = 9;
    	uint32_t cyc = 0;		/***** Variable indexing the timing loop *****/
		while(count!=0)
		{
			if(count == 9 && cyc == 0)		/***** Checking for the start of program *****/
			{
				printf("\nPC Run Version");
				printf("\nProgram Start... \n");
				cyc = 0;
    			printf("\n-----------------------------------------------------------\n");
    			printf("\nCycle %u.\n\r",(10-count));		/***** Printing the number of the cycle ****/
    			printf("\n-----------------------------------------------------------\n");
			}
			/***** Looping 3 on and off cycles for every color *****/
			/***** Color Pattern - RED GREEN BLUE *****/
			for(clr = 3;clr > 0; cyc++,clr--)
			{
					if(cyc == 20)		/***** Reinitializing the index of timing loop at end *****/
					{
						cyc = 0;
						count--;
    	        		printf("\n-----------------------------------------------------------\n");
    	        		printf("\nCycle %u.\n\r",(10-count));
    	        		printf("\n-----------------------------------------------------------\n");
					}
					/***** Printing the LED status along with their wait time *****/
					printf("\nRED LED ON for %u ms.",t_cyc[cyc]);
					delay(t_cyc[cyc]);
    				printf("\nRED LED OFF for %u ms.",t_cyc[++cyc]);
    				delay(t_cyc[cyc]);
    				printf("\n");
			}
			for(clr = 3;clr > 0; cyc++,clr--)
			{
				if(cyc == 20)
				{
				    cyc = 0;
				    count--;
	        		printf("\n-----------------------------------------------------------\n");
	        		printf("\nCycle %u.\n\r",(10-count));
	        		printf("\n-----------------------------------------------------------\n");
				}
				printf("\nGREEN LED ON for %u ms.",t_cyc[cyc]);
				delay(t_cyc[cyc]);
				printf("\nGREEN LED OFF for %u ms.",t_cyc[++cyc]);
				delay(t_cyc[cyc]);
				printf("\n");
			}
			for(clr = 3;clr > 0; cyc++,clr--)
			{
				if(cyc == 20)
				{
				    cyc = 0;
				    count--;
	        		printf("\n-----------------------------------------------------------\n");
	        		printf("\nCycle %u.\n\r",(10-count));
	        		printf("\n-----------------------------------------------------------\n");
				}
				printf("\nBLUE LED ON for %u ms.",t_cyc[cyc]);
				delay(t_cyc[cyc]);
				printf("\nBLUE LED OFF for %u ms.",t_cyc[++cyc]);
				delay(t_cyc[cyc]);
				printf("\n");
			}
			/***** For finishing the timing cycles in the last count *****/
		    if(count == 0)
		    {
		    	while(cyc!=20)
		    	{
					printf("\nRED LED ON for %u ms.",t_cyc[cyc]);
					delay(t_cyc[cyc]);
    				printf("\nRED LED OFF for %u ms.",t_cyc[++cyc]);
    				delay(t_cyc[cyc]);
    				printf("\n");
					cyc++;
		    	}
		    }
		    /***** For terminating the PC Run version *****/
			if(count == 0 && cyc == 20)
			{
				printf("\nPC Run Version");
				printf("\nProgram End! ");

			}
		}
		#endif
		/*************** PC Debug version ****************/
		#ifdef PC_DEBUG
    		count = 9;
    		uint32_t cyc = 0;		/***** Variable indexing the timing loop *****/
    		while(count!=0)
    		{
    			if(count == 9 && cyc == 0)		/***** Checking for the start of program *****/
    			{
    				printf("\nPC Run Version");
    				printf("\nProgram Start... \n");
    				cyc = 0;
        			printf("\n-----------------------------------------------------------\n");
        			printf("\nCycle %u.\n\r",(10-count));	/***** Printing the number of the cycle ****/
        			printf("\n-----------------------------------------------------------\n");
    			}
    			/***** Looping 3 on and off cycles for every color *****/
    			/***** Color Pattern - RED GREEN BLUE *****/
    			for(clr = 3;clr > 0; cyc++,clr--)
    			{
    					if(cyc == 20)			/***** Reinitializing the index of timing loop at end *****/
    					{
    						cyc = 0;
    						count--;
        	        		printf("\n-----------------------------------------------------------\n");
        	        		printf("\nCycle %u.\n\r",(10-count));
        	        		printf("\n-----------------------------------------------------------\n");
    					}
    					/***** Printing the LED status along with the timestamp and time since previous event *****/
    					printf("\nRED LED ON");
    					timestamp();
    					printf(" %u ms",t_cyc[cyc-1]);
    					delay(t_cyc[cyc]);
    					if(cyc == 19)		/***** for looping around the time loop once it reaches the end *****/
    					{
        					printf("\nRED LED OFF");
        					timestamp();
        					printf(" %u ms",t_cyc[19]);
        					delay(t_cyc[0]);
        					printf("\n");
        				    cyc = 0;
        				    count--;
    						if(count != 0)
    						{
        	        			printf("\n-----------------------------------------------------------\n");
        	        			printf("\nCycle %u.\n\r",(10-count));
        	        			printf("\n-----------------------------------------------------------\n");
    						}
    					}
    					else
    					{
        					printf("\nRED LED OFF");
        					++cyc;
        					timestamp();
        					printf(" %u ms",t_cyc[cyc-1]);
        					delay(t_cyc[cyc]);
        					printf("\n");
    					}
    			}
    			for(clr = 3;clr > 0; cyc++,clr--)
    			{
    				if(cyc == 20)
    				{
    				    cyc = 0;
    				    count--;
    	        		printf("\n-----------------------------------------------------------\n");
    	        		printf("\nCycle %u.\n\r",(10-count));
    	        		printf("\n-----------------------------------------------------------\n");
    				}
    				printf("\nGREEN LED ON");
					timestamp();
					printf(" %u ms",t_cyc[cyc-1]);
    				delay(t_cyc[cyc]);
					if(cyc == 19)
					{
    					printf("\nGREEN LED OFF");
    					timestamp();
    					printf(" %u ms",t_cyc[19]);
    					delay(t_cyc[0]);
    					printf("\n");
					}
					else
					{
    					printf("\nGREEN LED OFF");
    					++cyc;
    					timestamp();
    					printf(" %u ms",t_cyc[cyc-1]);
    					delay(t_cyc[cyc]);
    					printf("\n");
					}
				}
    			for(clr = 3;clr > 0; cyc++,clr--)
    			{
    				if(cyc == 20)
    				{
    				    cyc = 0;
    				    count--;
    	        		printf("\n-----------------------------------------------------------\n");
    	        		printf("\nCycle %u.\n\r",(10-count));
    	        		printf("\n-----------------------------------------------------------\n");
    				}
    				printf("\nBLUE LED ON");
					timestamp();
					printf(" %u ms",t_cyc[cyc-1]);
    				delay(t_cyc[cyc]);
					if(cyc == 19)
					{
    					printf("\nBLUE LED OFF");
    					timestamp();
    					printf(" %u ms",t_cyc[19]);
    					delay(t_cyc[0]);
    					printf("\n");
					}
					else
					{
    					printf("\nBLUE LED OFF");
    					++cyc;
    					timestamp();
    					printf(" %u ms",t_cyc[cyc-1]);
    					delay(t_cyc[cyc]);
    					printf("\n");
					}
    			}
    			/***** For finishing the timing cycles in the last count *****/
    		    if(count == 0)
    		    {
    		    	while(cyc!=20)
    		    	{
    					printf("\nRED LED ON");
    					timestamp();
    					printf(" %u ms",t_cyc[cyc-1]);
    					delay(t_cyc[cyc]);
    					if(cyc == 19)
    					{
        					printf("\nRED LED OFF");
        					timestamp();
        					printf(" %u ms",t_cyc[19]);
        					delay(t_cyc[0]);
        					printf("\n");
        				    cyc = 0;
        				    count--;
    						if(count != 0)
    						{
        	        			printf("\n-----------------------------------------------------------\n");
        	        			printf("\nCycle %u.\n\r",(10-count));
        	        			printf("\n-----------------------------------------------------------\n");
    						}
    					}
    					else
    					{
        					printf("\nRED LED OFF");
        					++cyc;
        					timestamp();
        					printf(" %u ms",t_cyc[cyc-1]);
        					delay(t_cyc[cyc]);
        					printf("\n");
    					}
    					cyc++;
    		    	}
    		    }
    		    /***** For terminating the PC Debug version *****/
    			if(count == 0 && cyc == 20)
    			{
    				printf("\nPC Run Version");
    				printf("\nProgram End! ");

    			}
    		}
		#endif
    return 0 ;
}
/*************** Delay function using clock() for 1ms delay [1] ****************/
void delay(uint32_t dly)
{
	clock_t start_time = clock();
	while (clock() < start_time + dly)
	{
		;	/***** Wasting CPU cycles to get the desired delay ******/
	}
}
/*************** Function for generating time stamps [2] ****************/
void timestamp(void)
{
	time_t ts = time(NULL);
	struct tm *pts = localtime(&ts);
	printf(" %02d:%02d:%02d", pts->tm_hour, pts->tm_min, pts->tm_sec);
}

/************************************************** References ********************************************************
[1] https://www.geeksforgeeks.org/time-delay-c/
[2] http://zetcode.com/articles/cdatetime/
************************************************************************************************************************/
