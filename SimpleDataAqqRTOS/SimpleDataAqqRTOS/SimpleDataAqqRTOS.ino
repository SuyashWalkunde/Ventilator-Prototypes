#include <Arduino_FreeRTOS.h>
#include "defines.h"
#include "includes.h"
#include "globals.h"
#include "prototypes.h"

void setup() {

  Serial.begin(9600);
  while (!Serial)
  {
    ;
  }
  motor.attach(10, 1000, 2000);
  motor.write(20);
  delay(3000);
  motor.write(0);
  delay(3000);
  nexInit();
  senseFlow.init();
  CPAP_start.attachPush(CPAP_startPushCallback);
  BiPAP_start.attachPush(BiPAP_startPushCallback);
  SIMV_PC_start.attachPush(SIMV_PC_startPushCallback);
  CMV_start.attachPush(CMV_startPushCallback);
  inspiratory_sensor = analogRead(A7);
  expiratory_sensor = analogRead(A8);

  Serial.println("Init Complete");
  Serial.println(StartCPAP);
  Serial.println(StartBiPAP);
  Serial.println(StartCMV);
  Serial.println(StartSIMV_PC);
  delay(300);

  // Now set up two tasks to run independently.
  xTaskCreate(
    inspiratory_pressure
    ,  "inspiratory_pressure"   // A name just for humans
    ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  1  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL );

  xTaskCreate(
    expiratory_pressure
    ,  "expiratory_pressure"
    ,  128  // Stack size
    ,  NULL
    ,  1  // Priority
    ,  NULL );

  xTaskCreate(
    display_get_data
    ,  "display_get_data"
    ,  128  // Stack size
    ,  NULL
    ,  2  // Priority
    ,  NULL );

  xTaskCreate(
    CPAP
    ,  "CPAP"
    ,  128  // Stack size
    ,  NULL
    ,  1  // Priority
    ,  NULL );

  xTaskCreate(
    CPAPGraph
    ,  "CPAPGraph"
    ,  128  // Stack size
    ,  NULL
    ,  1  // Priority
    ,  NULL );

  xTaskCreate(
    BiPAP
    ,  "BiPAP"
    ,  128  // Stack size
    ,  NULL
    ,  1  // Priority
    ,  NULL );

  xTaskCreate(
    BiPAPGraph
    ,  "BiPAPGraph"
    ,  128  // Stack size
    ,  NULL
    ,  1  // Priority
    ,  NULL );

  xTaskCreate(
    inspiratory_flow_rate
    ,  "inspiratory_flow_rate"
    ,  128  // Stack size
    ,  NULL
    ,  1  // Priority
    ,  NULL );

  xTaskCreate(
    expiratory_flow_rate
    ,  "expiratory_flow_rate"
    ,  128  // Stack size
    ,  NULL
    ,  1  // Priority
    ,  NULL );


  xTaskCreate(
    CMV
    ,  "CMV"
    ,  128  // Stack size
    ,  NULL
    ,  1  // Priority
    ,  NULL );

  xTaskCreate(
    SIMV_PC
    ,  "SIMV_PC"
    ,  128  // Stack size
    ,  NULL
    ,  1  // Priority
    ,  NULL );
}

void loop()
{

}


void display_get_data(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  for (;;)
  {
    vTaskDelay(2);
    nexLoop(nex_listen_list);
    if (PrintNex == 268)
    {
      //          Serial.println("Monitoring Nextion Display");
    }

  }
}
