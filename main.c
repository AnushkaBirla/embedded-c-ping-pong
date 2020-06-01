#include <lpc17xx.h>
#include <stdio.h>
#include <stdlib.h>
#include "uart.h"
#include "GLCD.h"
#include <cmsis_os2.h> 
#include <stdbool.h>


//unsigned short paddleWhite_bitmap[] = { White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White,
//																				White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White,
//																		 	  White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White,
//																			  White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White,
//																			  White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White};

//unsigned short paddleBlack_bitmap[] = { Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black,
//																				Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black,
//																				Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black,
//																				Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black,
//																				Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black};

//unsigned short ball_bitmap[] = { Black, Black, Black, Black, Black, Black, White, White, White, White, White, Black, Black, Black, Black, Black, Black, 
//																 Black, Black, Black, Black, Black, White, White, White, White, White, White, White, Black, Black, Black, Black, Black,   
//																 Black, Black, Black, Black, White, White, White, White, White, White, White, White, White, Black, Black, Black, Black,  
//																 Black, Black, White, White, White, White, White, White, White, White, White, White, White, White, Black, Black, Black,  
//																 Black, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, Black,  						
//															   White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, 
//																 White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, 
//																 White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White,   
//																 White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, 
//																 White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White,  
//																 Black, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, Black, 
//																 Black, Black, White, White, White, White, White, White, White, White, White, White, White, White, White, Black, Black, 
//																 Black, Black, Black, White, White, White, White, White, White, White, White, White, White, White, Black, Black, Black, 
//																 Black, Black, Black, Black, White, White, White, White, White, White, White, White, White, Black, Black, Black, Black,
//																 Black, Black, Black, Black, Black, White, White, White, White, White, White, White, Black, Black, Black, Black, Black,
//																 Black, Black, Black, Black, Black, Black, White, White, White, White, White, Black, Black, Black, Black, Black, Black}; 

//unsigned short ball_bitmap_clear[] = { Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, 
//																 Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black,   
//																 Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black,  
//																 Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black,  
//																 Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black,  						
//															   Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, 
//																 Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, 
//																 Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black,   
//																 Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, 
//																 Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black,  
//																 Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, 
//																 Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, 
//																 Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, 
//																 Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black,
//																 Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black,
//																 Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black}; 

unsigned short paddle_bitmap[] = { Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,
																	 Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,
																	 Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,
																	 Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,
																	 Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black};

	
unsigned short paddleWhite_bitmap[] = { White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White,
																				White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White,
																				White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White,
																				White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White,
																				White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White};

unsigned short paddleBlack_bitmap[] = { Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black,
																				Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black,
																				Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black,
																				Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black,
																				Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black};

	unsigned short paddleBlackBig_bitmap[] = { Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, 
																				Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, 
																				Black,Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black,
																				Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black,
																				Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black,
																				Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black,
																				Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black,
																				Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black,
																				Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black,
																				Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black,
																				Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black,
	                                    	Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black,
																				Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black,
																				Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black,
																				Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black,
																				Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black,
																				Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black,
																				Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black,
																				Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black,
																				Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black};

	
unsigned short ball_bitmap[] = { Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,
															 	 Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,
																 Black,Black,Black,Black,White,White,White,White,White,White,White,Black,Black,Black,Black,
													 			 Black,Black,Black,White,White,White,White,White,White,White,White,White,Black,Black,Black,
														 		 Black,Black,White,White,White,White,White,White,White,White,White,White,White,Black,Black,
																 Black,Black,White,White,White,White,White,White,White,White,White,White,White,Black,Black,
																 Black,Black,White,White,White,White,White,White,White,White,White,White,White,Black,Black,
																 Black,Black,White,White,White,White,White,White,White,White,White,White,White,Black,Black,
																 Black,Black,White,White,White,White,White,White,White,White,White,White,White,Black,Black,
																 Black,Black,White,White,White,White,White,White,White,White,White,White,White,Black,Black,
																 Black,Black,White,White,White,White,White,White,White,White,White,White,White,Black,Black,
																 Black,Black,Black,White,White,White,White,White,White,White,White,White,Black,Black,Black,
																 Black,Black,Black,Black,White,White,White,White,White,White,White,Black,Black,Black,Black,
																 Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,
																 Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black};

unsigned short bitmap_clear[] = { Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,
																			 Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,
																			 Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,
																			 Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,
																			 Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,
																			 Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,
																			 Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,
																			 Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,
																			 Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,
																			 Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,
																			 Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,
																			 Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,
																			 Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,
																			 Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,
																			 Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black};

const int ballDiameter = 15;			
const int paddleWidth = 50;		
const int paddlePadding = 10;																			 
const int screenWidth = 320;
const int screenHeight = 220;	//excluding bottom section with player score details
int x_coord_p1, y_coord_p1;
int x_coord_p2, y_coord_p2;
int x_coord_ball, y_coord_ball;
int player1Score, player2Score;	
bool ballClear;

//player 1 joystick position
void joystick(void *arg){
	int increment = 5;
	
	while(1){		
		if (!((LPC_GPIO1->FIOPIN) & 0x1000000)){
			//move paddle right by increment value if it is within the screen bounds
			if(x_coord_p1 < screenWidth - (paddleWidth+2*paddlePadding)){
				x_coord_p1 += increment;
			}
		}
		else if (!((LPC_GPIO1->FIOPIN) & 0x4000000)){
			//move paddle left by increment value if it is within the screen bounds
			if(x_coord_p1 > 0){
				x_coord_p1 -= increment;
			}
		}		
		//delay so that the screen can be updated
		osDelay(50);
		osThreadYield();
	}
}

int map(int val, int in_min, int in_max, int out_min, int out_max){
	return (val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

//player 2 potentiometer position
void potentiometer(void *arg){	
	while(1){
		LPC_PINCON->PINSEL1 &= ~(0x03<<18);
		LPC_PINCON->PINSEL1 |= (0x01<<18);
		
		LPC_SC->PCONP |= (0x01<<12);		
		LPC_ADC->ADCR = (1 << 2) | (4 << 8) | (1 << 21);		
		LPC_ADC->ADCR |= (0x01<<24);
		
		while(!(LPC_ADC->ADGDR & 0x80000000)){
			//map reading from (0 to 4095) to screen range (0, 270)
			x_coord_p2 = map((((LPC_ADC->ADGDR)&(0xFFF0))>>4), 0, 4095, 0, screenWidth - (paddleWidth+2*paddlePadding));	
			osDelay(350);			
		}
		osThreadYield();
	}
}

// led
void led(void *arg){
	//initalize LEDs
	LPC_GPIO2->FIODIR |= 0x0000007C;
	LPC_GPIO1->FIODIR |= 0xB0000000;

	LPC_GPIO1->FIOSET |= 0x00;
	LPC_GPIO2->FIOSET |= 0x00;

	while(1){
		//checks if a point has been scored
		if(ballClear == true) {
			//flicker light for one second for each point scored
			for(int i = 0; i < 10; i++){
				LPC_GPIO2->FIOSET |= 0x04; // turn on
				osDelay(50);
				LPC_GPIO2->FIOCLR |= 0x04;
				osDelay(50);
			}
			
			//clear LED back to off
			LPC_GPIO2->FIOCLR |= 0x04;
		}

		osThreadYield();
	}
}

//update ball position
void ballPos(void *args){
	//set ball direction vestor and speed muiltiplier
	int direction[] = {-1, 1};
	int speed = 1;
	
	//pause before starting the game to allow the players to ready themselves
	osDelay(3000);
	
	while(1) {
		//check if ball is within screen bounds and has not collided with either paddle
		while(x_coord_ball < (screenWidth - ballDiameter) && x_coord_ball > 0 && y_coord_ball > (y_coord_p1 + 5) && y_coord_ball+ballDiameter < y_coord_p2) //ball is on screen and has not collided with anything - find appropriate x and y coords for the walls and paddles
		{		
			//update ball position
			x_coord_ball += direction[0]*speed; // i.e [153, 250] => [153, 250] + [(-1)*2, (1)*2] = [151, 252] ,moves left and down
			y_coord_ball += direction[1]*speed;
			
			osDelay(30);
		}
			
		//ball hit bottom of playing screen
		if(y_coord_ball == (y_coord_p1+5)){
			//ball collided with P1 paddle
			//atleast half of the ball must overlap the paddle for a positive hit
			if(x_coord_ball >= ((x_coord_p1+paddlePadding)-(ballDiameter/2)) && x_coord_ball <= (x_coord_p1 + paddleWidth + paddlePadding -(ballDiameter/2)))
			{
				//invert y direction and shift ball down by one to remove paddle overlap
				direction[1] = direction[1] * -1;
				y_coord_ball += 1;
			}
			else //ball falls off screen, no collision
			{			
				//clear ball, update P1 score, reset ball position to center
				ballClear = true;
				player2Score++;
				//delay to allow for the screen to clear ball image before it is reset to the center
				osDelay(100);				
				x_coord_ball = screenWidth/2 - ballDiameter/2;
				y_coord_ball = screenHeight/2;										
			}
		}

		//ball hit top of playing screen
		if((y_coord_ball+ballDiameter) == y_coord_p2){
			//ball collided with P2 paddle
			//atleast half of the ball must overlap the paddle for a positive hit
			if(x_coord_ball >= (x_coord_p2-(ballDiameter/2)) && x_coord_ball <= (x_coord_p2 + paddleWidth -(ballDiameter/2)))
			{
				//invert y direction and shift ball up by one to remove paddle overlap
				direction[1] = direction[1] * -1;
				y_coord_ball -= 1;
			}
			else //ball falls off screen, no collision
			{
				//clear ball, update P1 score, reset ball position to center
				ballClear = true;
				player1Score++;
				//delay to allow for the screen to clear ball image before it is reset to the center
				osDelay(100);
				x_coord_ball = screenWidth/2 - ballDiameter/2;
				y_coord_ball = screenHeight/2;										
			}
		}
		
		//ball hit right wall
		if(x_coord_ball == (screenWidth - ballDiameter)){
			//invert x direction and shift ball to the left by one to remove wall overlap
			direction[0] = direction[0] * -1;
			x_coord_ball -= 1;
		}
		
		if(x_coord_ball == 0){
			//invert x direction and shift ball to the right by one to remove wall overlap
			direction[0] = direction[0] * -1;
				x_coord_ball += 1;
		}
	
		osDelay(200);
		osThreadYield();
	}
}
	
//update screen
void screenController(void *args){
	//initalize screen to black and game objects to white
	GLCD_Init();
	GLCD_Clear(Black);
	GLCD_SetBackColor(Black);
	GLCD_SetTextColor(White);
	
	char score[25];
	int paddleHeight = 5;
	
	GLCD_Bitmap(x_coord_p1, y_coord_p1 , paddleWidth+(paddlePadding*2), paddleHeight, (unsigned char*)paddle_bitmap);
	GLCD_Bitmap(x_coord_p2, y_coord_p2 , paddleWidth, paddleHeight, (unsigned char*)paddleWhite_bitmap);
	
	while(1){
		//Plyer 1 and Player 2 scores at bottom fo screen
		sprintf(score, "Player 1: %i              Player 2: %i", player1Score, player2Score);
		GLCD_DisplayString( 29, 0 ,0, (unsigned char*)score);	
		
		//end game once a player to reachs 5 points
		if (player1Score == 5 || player2Score == 5){
			//include delay between last point scored and game over screen for player benefit
			osDelay(2000);
			//clear screen, display game over text and which player won
			GLCD_Clear (Black);			
			GLCD_DisplayString( 3, 5 ,1, (unsigned char*)"GAME OVER");	
			
			if(player1Score == 5){
				GLCD_DisplayString( 5, 3 ,1, (unsigned char*)"Player 1 Wins!");
			}
			if(player2Score == 5){
				GLCD_DisplayString( 5, 2 ,1, (unsigned char*)"Player 2 Wins!");
			}
				
			//exit thread, game is over LCD should not update until the game is reset
			osThreadExit();
		}
			
		//player movements
		GLCD_Bitmap(x_coord_p1, y_coord_p1 , paddleWidth+(paddlePadding*2), paddleHeight, (unsigned char*)paddle_bitmap);
			
		GLCD_Bitmap(x_coord_p2, y_coord_p2 , paddleWidth, paddleHeight, (unsigned char*)paddleWhite_bitmap);
		//adjust for inconsisten potentimoeter readings, clear P2 line to Black
		GLCD_Bitmap(x_coord_p2+paddleWidth+1, y_coord_p2 , screenWidth-(x_coord_p2+paddleWidth+1), paddleHeight, (unsigned char*)paddleBlack_bitmap);
		GLCD_Bitmap(0, y_coord_p2 , x_coord_p2-1, paddleHeight, (unsigned char*)paddleBlack_bitmap);

		// clearing p1 row to black to prevent redrawing the paddle when the koystickis moved while the ball is off the screen
		GLCD_Bitmap(x_coord_p1+paddleWidth+1, y_coord_p1 , screenWidth-(x_coord_p1+paddleWidth+1), paddleHeight, (unsigned char*)paddleBlack_bitmap);
		GLCD_Bitmap(0, y_coord_p1 , x_coord_p1-1, paddleHeight, (unsigned char*)paddleBlack_bitmap);
		
		//clear ball position with blank bitmap when point is scored
		if(ballClear == true){
			osDelay(50);
			GLCD_Bitmap(x_coord_ball, y_coord_ball , ballDiameter, ballDiameter, (unsigned char*)bitmap_clear);		
			ballClear = false;
			//delay before re-drawing ball to give players time to react between points
			osDelay(2000);		
		}

		//draw pong ball
		GLCD_Bitmap(x_coord_ball, y_coord_ball , ballDiameter, ballDiameter, (unsigned char*)ball_bitmap); 
	
		osThreadYield();
	}
}
	
int main (void) {
	//intialize global variables
	x_coord_p1 = screenWidth/2;
	y_coord_p1 = 10;
	x_coord_p2 = screenWidth/2;
	y_coord_p2 = screenHeight;
	x_coord_ball = screenWidth/2;
	y_coord_ball = screenHeight/2;
	player1Score = 0;
  player2Score = 0;	
	ballClear = false;
	
	//initalize and begin threading
	osKernelInitialize();
	osThreadNew(potentiometer, NULL, NULL);
	osThreadNew(joystick, NULL, NULL);
	osThreadNew(led, NULL, NULL);
	osThreadNew(screenController, NULL, NULL);
	osThreadNew(ballPos, NULL, NULL);
	osKernelStart();
	for( ; ; ) {}
}

