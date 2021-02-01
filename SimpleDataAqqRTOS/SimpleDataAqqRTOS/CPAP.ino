void CPAP(void *pvParameters)  // This is a task.
{

  (void) pvParameters;
  for (;;)
  {

    vTaskDelay(2);
    if (StartCPAP == true)
    {
      int motor_angle = map(pressure_value, 5, 40, 20, 180);
      motor.write(motor_angle);
      Serial.println("Motor is running");
      Serial.print("inhale_pressure: ");
      Serial.print(inhale_pressure);
    }
  }
}

void CPAPGraph(void *pvParameters)  // This is a task.
{

  (void) pvParameters;
  for (;;)
  {
    vTaskDelay(2);
    if (StartCPAP == true)
    {

      float cpap_flow_Rate = inspiratory_flow_sensor_data;
      float inhale_pressure = inspiratory_sensor_data;


      c_flow.setValue((float)cpap_flow_Rate);
      c_pressure_feedback.setValue((float)inhale_pressure);

      //CPAP Pressure and Flow Mapping
      inhale_pressure = map(inhale_pressure, 0, 10, 0, 255);
      cpap_flow_Rate = map(cpap_flow_Rate, 0, 120, 0, 255);

      //CPAP Pressure and flow display graph
      cpap_flow_wave.addValue(0, CH_OFFSET + cpap_flow_Rate);
      cpap_pressure_wave.addValue(0, CH_OFFSET + inhale_pressure);
    }
  }
}
