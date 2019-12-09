/*
 * bt_prueba.c
 *
 *  Created on: 4 dic. 2019
 *      Author: nachotc
 */

#include "sapi.h"        // <= Biblioteca sAPI

#define UART_BLUETOOTH UART_232

int main( void )
{
   // ---------- CONFIGURACIONES ------------------------------

   // Inicializar y configurar la plataforma
   boardConfig();

   // Inicializar UART_232 para conectar al modulo bluetooth a 9600bps
   uartConfig( UART_BLUETOOTH, 9600 );
   uartWriteString(UART_BLUETOOTH, "AT+namePEPE\r\n");
   printf("UART_BLUETOOTH para modulo Bluetooth configurada.\n" );

   uint8_t data = 0;

   if( hm10bleTest( UART_BLUETOOTH ) ){
        printf("Modulo conectado correctamente.\n" );
   }
   else{
        printf("No funciona.\n" );
   }

   while(TRUE){
	   if( uartReadByte( UART_BLUETOOTH, &data ) ) {
	            if( data == 'h' ) {
	               gpioWrite( LEDB, ON );
	            }
	            if( data == 'l' ) {
	               gpioWrite( LEDB, OFF );
	            }
	            printf( data );
	            fflush(stdout);
	         }
   }

}
