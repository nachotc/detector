/*
 * ejemploFreeRTOS.c
 *
 *  Created on: 4 dic. 2019
 *      Author: nachotc
 */

/* Incluir librerías FreeRTOS. */
#include "FreeRTOS.h"
#include "task.h"

/* Demo includes. */
#include "supporting_functions.h"

/* Used as a loop counter to create a very crude delay. */
#define mainDELAY_LOOP_COUNT		( 0xffffff )

/* Prototipo de la función de la tarea. */
void vTaskFunction( void *pvParameters );

/* Se definen los nombres de las tareas que serán
 * enviadas por parametro a las funciones de las mismas. */
const char *pcTextForTask1 = "Task 1 is running\r\n";
const char *pcTextForTask2 = "Task 2 is running\r\n";

/*-----------------------------------------------------------*/

int main( void )
{
   /* Creacion de tarea. */
   xTaskCreate(	vTaskFunction,            /* Puntero a la funcion que implementa la tarea. */
                  "Task 1",                 /* Nombre de la tarea. */
                  configMINIMAL_STACK_SIZE, /* Tamaño de la pila de la tarea. */
                  (void*)pcTextForTask1,    /* Parametro que será usado por la tarea. */
                  tskIDLE_PRIORITY+1,       /* Prioridad de la tarea. */
                  NULL );                   /* Manejador nulo. */

   /* Creacion de la segunda tarea, igual a la primera. */
   xTaskCreate( vTaskFunction, "Task 2", configMINIMAL_STACK_SIZE, (void*)pcTextForTask2, tskIDLE_PRIORITY+1, NULL );

   /* Start del scheduler para comenzar a ejecutar las tareas. */
   vTaskStartScheduler();

   for( ;; );
   return 0;
}
/*-----------------------------------------------------------*/

void vTaskFunction( void *pvParameters )
{
   char *pcTaskName;
   volatile uint32_t ul;

   /* Casteo del parametro recibido, contiene el nombre de la tarea. */
   pcTaskName = ( char * ) pvParameters;

   for( ;; ) {
      /* Imprime el nombre de la tarea. */
      vPrintString( pcTaskName );

      /* Delay. */
      for( ul = 0; ul < mainDELAY_LOOP_COUNT; ul++ ) {
      }
   }
}




