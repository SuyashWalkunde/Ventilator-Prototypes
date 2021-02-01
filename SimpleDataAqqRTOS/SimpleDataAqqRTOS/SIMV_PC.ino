void synchronized_intermittent_mandatory_ventilation_pc(float inhale, float exhale, float breaths_per_minute, float pressure)
{

  int motor_angle = map(pressure, 0, 30, 14, 180);
  float total_time = inhale + exhale;
  float inhale_time = (60 / breaths_per_minute) * ( (float)inhale / total_time);
  float exhale_time = (60 / breaths_per_minute) * ( (float)exhale / total_time);
  inhale_time *= 1000;
  exhale_time *= 1000;

  for ( uint32_t tStart = millis();  (millis() - tStart) < inspiration_trigger_window;  )

  {

    inhale_pressure = inspiratory_sensor_data;
    //Function to convert analog value into cmh2o.
  }

  double pressure_to_apply = pressure_value - inhale_pressure;


  Serial.println();
  float flow = expiratory_flow_sensor_data;
  // function to convert cmh2o into motor_angle
  //  int pressure_angle = 20;
  for ( uint32_t tStart = millis();  (millis() - tStart) < (inhale_time - inspiration_trigger_window);  ) {
    motor.write(motor_angle);
    Serial.print("inhale_time: ");
    Serial.print(inhale_time);
    Serial.print("  exhale_time: ");
    Serial.print(exhale_time);
    Serial.print("Inside Inhale Loop");
    Serial.println();
    vTaskDelay(10);
  }
  for ( uint32_t tStart = millis();  (millis() - tStart) < exhale_time;  ) {
    motor.write(motor_angle);
    Serial.print("inhale_time: ");
    Serial.print(inhale_time);
    Serial.print("  exhale_time: ");
    Serial.print(exhale_time);
    Serial.print("Inside Exhale Loop");
    Serial.print("   SIMV_PC");
    Serial.println();
    vTaskDelay(10);
  }
}
void SIMV_PC( void *pvParameters )
{

  (void) pvParameters;
  for (;;)
  {
    vTaskDelay(2);
    if (StartSIMV_PC == true)
    {
      synchronized_intermittent_mandatory_ventilation_pc((float)inhale_value,
          (float)exhale_value,
          (float)bpm_value,
          (float)pressure_value);
    }
  }
}
