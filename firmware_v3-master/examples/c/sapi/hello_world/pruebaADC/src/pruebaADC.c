/*
 * pruebaADC.c
 *
 *  Created on: 2 dic. 2019
 *      Author: nachotc
 */

#include "sapi.h"

int main(void){

   /* ------------- INICIALIZACIONES ------------- */

   /* Inicializar la placa */
   boardConfig();

   /* Inicializar UART_USB a 115200 baudios */
   uartConfig( UART_USB, 115200 );

   /* Inicializar AnalogIO */
   /* Posibles configuraciones:
    *    ADC_ENABLE,  ADC_DISABLE,
    *    ADC_ENABLE,  ADC_DISABLE,
    */
   adcConfig( ADC_ENABLE ); /* inicia el ADC */
   uint16_t muestra = 0;
   float voltaje;

   while(1){
	   muestra = adcRead(CH3); //Le muestra del ADC, canal 3
	   voltaje = muestra * (3.3 / 1023.0); //realiza conversión de la muestra a voltaje
	   printf("Muestra: %d - Voltaje: %f \n",muestra,voltaje);
	   delay(1500);
   }

   return 0;
}


