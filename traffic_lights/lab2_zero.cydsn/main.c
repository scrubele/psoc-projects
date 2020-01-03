/*========================================
 *
 *Traffic lights emulator.
 *
 *========================================
 */
#include "project.h"
#include <stdio.h>

int algo = 0;
uint16 t_count = 0;
const int RED = 1,
	YELLOW = 1,
	GREEN = 1;
const int ALGO_1 = 0,
	ALGO_2 = 1;

/*traffic_lights intervals according to the algorithms.*/
int traffic_lights_intervals[2][8] = {
		{ 6, 8, 13, 14, 15, 16, 17, 19 }, /*ALGO_1*/
	    { 2, 3, 4, 5, 6, 8, 17, 19 } /*ALGO_2*/
};
void setLeds(int red, int yellow, int green)
{
	Pin_Red_Write(red);
	Pin_Blue_Write(yellow);
	Pin_Green_Write(green);
}

void clearAll()
{
	Pin_Test_Write(0);
	setLeds(0, 0, 0);
	t_count = 0;
}

CY_ISR(Pin_SW2_Handler)
{
	algo ^= 1;
	clearAll();
	Pin_SW2_ClearInterrupt();
}

void runAlgorithm1()
{
	if (t_count < traffic_lights_intervals[ALGO_1][0])
	{
		setLeds(RED, 0, 0);
	}
	else if (t_count < traffic_lights_intervals[ALGO_1][1])
	{
		setLeds(RED, YELLOW, 0);
	}
	else if (t_count < traffic_lights_intervals[ALGO_1][2])
	{
		setLeds(0, 0, GREEN);
	}
	else if (t_count < traffic_lights_intervals[ALGO_1][3])
	{
		setLeds(0, 0, 0);
	}
	else if (t_count < traffic_lights_intervals[ALGO_1][4])
	{
		setLeds(0, 0, GREEN);
	}
	else if (t_count < traffic_lights_intervals[ALGO_1][5])
	{
		setLeds(0, 0, 0);
	}
	else if (t_count < traffic_lights_intervals[ALGO_1][6])
	{
		setLeds(0, 0, GREEN);
	}
	else if (t_count < traffic_lights_intervals[ALGO_1][7])
	{
		setLeds(0, YELLOW, 0);
	}
	else
	{
		clearAll();
	}
}
void runAlgorithm2()
{
	if (t_count < traffic_lights_intervals[ALGO_2][0])
	{
		setLeds(0, 0, GREEN);
	}
	else if (t_count < traffic_lights_intervals[ALGO_2][1])
	{
		setLeds(0, 0, 0);
	}
	else if (t_count < traffic_lights_intervals[ALGO_2][2])
	{
		setLeds(0, 0, GREEN);
	}
	else if (t_count < traffic_lights_intervals[ALGO_2][3])
	{
		setLeds(0, 0, 0);
	}
	else if (t_count < traffic_lights_intervals[ALGO_2][4])
	{
		setLeds(0, 0, GREEN);
	}
	else if (t_count < traffic_lights_intervals[ALGO_2][5])
	{
		setLeds(0, YELLOW, 0);
	}
	else if (t_count < traffic_lights_intervals[ALGO_2][6])
	{
		setLeds(RED, 0, 0);
	}
	else if (t_count < traffic_lights_intervals[ALGO_2][7])
	{
		setLeds(0, YELLOW, 0);
	}
	else
	{
		clearAll();
	}
}

void testTimer()
{
	if (t_count % 10 == 0)
	{
		Pin_Test_Write(1);
	}
}

CY_ISR(Timer_Int_Handler)
{
	t_count++;
	if (algo)
	{
		runAlgorithm1();
	}
	else
	{
		runAlgorithm2();
	}
}
int main(void)
{
	CyGlobalIntEnable;
	Timer_Start();
	Timer_Int_StartEx(Timer_Int_Handler);
	Pin_SW2_Int_StartEx(Pin_SW2_Handler);
	for (;;) {}
}