/*
 * sensore.c
 *
 *  Created on: 3/10/2019
 *      Author: barcala
 */

#include "sapi.h"
#include "sapi_gpio.h"


int main(void){

   /* Inicializar la placa */
   boardConfig();
   gpioInit( GPIO1, GPIO_INPUT );

   volatile uint8_t valor = 0;


   /* ------------- REPETIR POR SIEMPRE ------------- */
   while(1) {

       valor = gpioRead( GPIO1 );

       gpioWrite( LEDB, !valor );

       gpioWrite( LED2, valor);

       delay(500);

   }

   return 0 ;
}


