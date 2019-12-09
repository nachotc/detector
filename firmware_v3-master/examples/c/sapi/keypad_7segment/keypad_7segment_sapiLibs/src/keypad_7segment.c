/* Copyright 2016, Eric Pernia.
 * All rights reserved.
 *
 * This file is part sAPI library for microcontrollers.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/*
 * Date: 2016-07-28
 */

/*==================[inclusions]=============================================*/

#include "sapi.h"                // <= sAPI header
#include "stdio.h"



/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/


/* FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE RESET. */
void queTecla(uint16_t k, char * key){
	char arre[16] = {                         '1',    '2',    '3', 'a',
	                                           '4',    '5',    '6', 'b',
	                                           '7',    '8',    '9', 'c',
	                                           '*',    '0',    '#', 'd'
	                                      };


	*key = arre[k];
}

int main(void){

   /* ------------- INICIALIZACIONES ------------- */

   /* Inicializar la placa */
   boardConfig();
   lcdInit( 16, 2, 5, 8 );
   lcdCursorSet( LCD_CURSOR_ON ); // Apaga el cursor
   lcdClear();                     // Borrar la pantalla
   /* Configuracion de pines para el display 7 segmentos */
   /*
   --------------------------+------------+-----------+----------------
    Segmento encendido       | Valor BIN  | Valor HEX | GPIO resultado
   --------------------------+------------+-----------+----------------
    Enciende el segmento 'a' | 0b00000001 |   0x20    | GPIO5
    Enciende el segmento 'b' | 0b00000010 |   0x80    | GPIO7
    Enciende el segmento 'c' | 0b00000100 |   0x40    | GPIO6
    Enciende el segmento 'd' | 0b00001000 |   0x02    | GPIO1
    Enciende el segmento 'e' | 0b00010000 |   0x04    | GPIO2
    Enciende el segmento 'f' | 0b00100000 |   0x10    | GPIO4
    Enciende el segmento 'g' | 0b01000000 |   0x08    | GPIO3
    Enciende el segmento 'h' | 0b10000000 |   0x80    | GPIO8
   --------------------------+------------+-----------+----------------
                a
              -----
          f /     / b
           /  g  /
           -----
       e /     / c
        /  d  /
        -----    O h = dp (decimal point).

   */
   uint8_t display7Segment[8] = {
      GPIO5, // Segment 'a'
      GPIO7, // Segment 'b'
      GPIO6, // Segment 'c'
      GPIO1, // Segment 'd'
      GPIO2, // Segment 'e'
      GPIO4, // Segment 'f'
      GPIO3, // Segment 'g'
      GPIO8  // Segment 'h' or 'dp'
   };

   display7SegmentPinConfig( display7Segment );


   /* Configuracion de pines para el Teclado Matricial*/

   // Teclado
   keypad_t keypad;

   // Filas --> Salidas
   uint8_t keypadRowPins1[4] = {
		   GPIO7, 	 // Row 0
		   GPIO5,    // Row 1
		   GPIO3,    // Row 2
		   GPIO1     // Row 3
   };

   // Columnas --> Entradas con pull-up (MODO = GPIO_INPUT_PULLUP)
   uint8_t keypadColPins1[4] = {
		   CAN_RD,    // Column 0
		   CAN_TD,    // Column 1
		   T_COL1,    // Column 2
		   T_FIL0     // Column 3
   };

   keypadConfig( &keypad, keypadRowPins1, 4, keypadColPins1, 4 );


   // Vector de conversion entre indice de tecla presionada y el índice del
   // display 7 segmentos
   uint16_t keypadToDesplayKeys[16] = {
                                           1,    2,    3, 0x10,
                                           4,    5,    6, 0x11,
                                           7,    8,    9, 0x12,
                                           0,    0,    0, 0x13
                                      };

   // Variable para guardar la tecla leida
   uint16_t tecla = 0;



   /* ------------- REPETIR POR SIEMPRE ------------- */
   char tecla2;
   volatile int cont = 0;
   printf("HOLA0\n");
   while(1) {
      if( keypadRead( &keypad, &tecla ) ){
        // display7SegmentWrite( display7Segment,
         // tecla2 = keypadToDesplayKeys[ (uint8_t)tecla ];
    	  queTecla(tecla, &tecla2);
    	  printf("%c",tecla2);
    	  fflush(stdout); //necesario para forzar la salida del buffer a stdout o \n
    	  lcdGoToXY( cont, 0); // Poner cursor en 0, 0
    	  lcdSendStringRaw(&tecla2);
    	  //lcdData(cont);
    	  cont++;
    	  delay(1000);


      } else{
         //display7SegmentWrite( display7Segment, DISPLAY_7_SEGMENT_OFF );
    	//printf("nada0\n");
      }
   }

   /* NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa no es llamado
      por ningun S.O. */
   return 0 ;
}

/*==================[end of file]============================================*/
