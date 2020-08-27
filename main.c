/*
 * RTOS_Queue_nasr18.c
 *
 * Created: 15/07/2020 02:26:07 م
 * Author : FGstore
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "semaphore.h"
xSemaphoreHandle xsbutton;



void vTaskButton(void *ptr);
void vTaskLED(void *ptr);
xQueueHandle XQueuebutton;


int main(void)
{
    
    while (1) 
    {
		xsbutton =xSemaphoreCreateBinary());
		
		
		xTaskCreate(vTaskButton,"Button",200,NULL,1,NULL);
		xTaskCreate(vTaskLED,"LED",200,NULL,2,NULL);
		vTaskStartScheduler();
    }
}
void vTaskButton(void *ptr){
	DDRB&=~(1<<4);
	DDRC|=(1<<2);

	while(1){
		if((PINB>>4 &1 )==1){
			_delay_ms(10);
		if(xSemaphoreGive(xsbutton)	==pdTRUE){
			PORTC ^=(1<<2);
			vTaskDelay(100/portTICK_PERIOD_MS);
		}
		else{
		}
		}
	}
}
void vTaskLED(void *ptr){
	DDRD|=(1<<3);
	
	while(1){
		if(xSemaphoreTake(xsbutton)==pdTRUE){
			PORTD^=(1<<3);
			
		}
		else{
		}
		
			
	}
	
}

