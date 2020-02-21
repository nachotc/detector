/*
 * bt_prueba.c
 *
 *  Created on: 4 dic. 2019
 *      Author: nachotc
 */

#include "sapi.h"        // <= Biblioteca sAPI

#define UART_BLUETOOTH UART_232
#define UART_PC        UART_USB

int main( void )
{
   // ---------- CONFIGURACIONES ------------------------------

   // Inicializar y configurar la plataforma
   boardConfig();

   // Inicializar UART_232 para conectar al modulo bluetooth a 9600bps
   uartConfig( UART_BLUETOOTH, 9600 );
   uartWriteString(UART_BLUETOOTH, "AT+namePEPE\r\n");
   uartWriteString( UART_PC, "UART_BLUETOOTH para modulo Bluetooth configurada.\r\n" );
  
   uartConfig( UART_PC, 9600 );
   uartWriteString( UART_PC, "UART_PC configurada.\r\n" );


   uint8_t data = 0;

   /*if( hm10bleTest( UART_BLUETOOTH ) ){
        printf("Modulo conectado correctamente.\n" );
   }
   else{
        printf("No funciona.\n" );
   }*/

   while(TRUE){
	   if( uartReadByte( UART_PC, &data ) ) {
         	uartWriteByte( UART_BLUETOOTH, data );
   	   }
	   if( uartReadByte( UART_BLUETOOTH, &data ) ) {
	            if( data == 'h' ) {
	               gpioWrite( LEDB, ON );
	            }
	            if( data == 'l' ) {
	               gpioWrite( LEDB, OFF );
	            }
	            uartWriteByte( UART_PC, data );
	   }
	   // Si presiono TEC1 imprime la lista de comandos AT
	   if( !gpioRead( TEC1 ) ) {
		 hm10blePrintATCommands( UART_BLUETOOTH );
		 delay(500);
	   }
   }

}


/*bool_t hm10bleTest( int32_t uart )
{
   uartWriteString( uart, "AT\r\n" );
   return waitForReceiveStringOrTimeoutBlocking( uart,
                                                 "OK\r\n", strlen("OK\r\n"),
                                                 1000 );
}
*/
void hm10blePrintATCommands( int32_t uart )
{
   uartWriteString( uart, "AT+HELP?\r\n" );
}
