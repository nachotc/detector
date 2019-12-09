/*
 * prueba.c
 *
 *  Created on: 2 dic. 2019
 *      Author: nachotc
 */
#include "sapi.h"
#include "sapi_gpio.h"

int main (void){
	boardConfig();
	lcdInit( 16, 2, 5, 8 );
	lcdCursorSet( LCD_CURSOR_ON ); // Apaga el cursor
	lcdClear();                     // Borrar la pantalla
	gpioInit( GPIO6, GPIO_INPUT);
	uint8_t valor = 0;
	while (1){
		valor = gpioRead (GPIO6);
		gpioWrite( LEDB, valor);
		gpioWrite( LED2, !valor);
		lcdGoToXY( 0, 0); // Poner cursor en 0, 0
		if(!valor){
			lcdClear();
			lcdSendStringRaw("Detectando");
		}else{
			lcdClear();
			lcdSendStringRaw("Sin Gas");
		}
		delay(1000);
	}
	return 0;
}



