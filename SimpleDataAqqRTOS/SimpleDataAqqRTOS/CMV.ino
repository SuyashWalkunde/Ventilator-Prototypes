void continuous_mandatory_ventilation(float inhale, float exhale, float breaths_per_minute, float pressure)
{

  for ( uint32_t tStart = millis();  (millis() - tStart) < 2000;  )

  {
    float cmv_inhale_pressure = expiratory_sensor_data;
    int motor_angle = map(pressure, 0, 30, 14, 180);
    if (cmv_inhale_pressure < -0.3)
    {
      patient_inhaled = true;
      int breath_complete = give_extra_breath(inhale, exhale, breaths_per_minute, pressure);
      Serial.println(inhale_pressure);
      vTaskDelay(2);
      break;
    }
    else
    {
      Serial.println(inhale_pressure);
      vTaskDelay(2);
    }
  }
  Serial.println("CMV_Window Elapsed");
  bilevel_positive_airway_pressure(inhale, exhale, breaths_per_minute, pressure);
}

int give_extra_breath(float inhale, float exhale, float breaths_per_minute, float pressure)
{
  // calculate inhale time
  int i = 0;
  float total_time = inhale + exhale;
  float inhale_time = (60 / breaths_per_minute) * ( (float)inhale / total_time);
  float exhale_time = (60 / breaths_per_minute) * ( (float)exhale / total_time);
  inhale_time *= 1000;
  exhale_time *= 1000;
  for ( uint32_t tStart = millis();  (millis() - tStart) < inhale_time;  )
  {
    int motor_angle = map(pressure, 0, 30, 14, 180);
    motor.write(motor_angle);
    Serial.println("Inside Inhale Loop");
    nexLoop(nex_listen_list);
    float cmv_flow_Rate = inspiratory_flow_sensor_data;
    float cmv_inhale_pressure =  inspiratory_sensor_data;
    float inhale_volume = cmv_flow_Rate * (inhale_time / 1000);
    vTaskDelay(10);

  }
  // run exhale loop for exhale time using millis()
  for ( uint32_t tStart = millis();  (millis() - tStart) < exhale_time;  ) {
    int motor_angle = map(pressure, 0, 30, 14, 180);
    motor.write(peep_speed_value);
    Serial.println("Inside Exhale Loop");
    vTaskDelay(10);
  }
  patient_inhaled = false;
  i++;
  return i;
}


void CMV( void *pvParameters )
{

  (void) pvParameters;
  for (;;)
  {
    Serial.print("StartCMV: ");
    Serial.print(StartCMV);
    Serial.println(" ");
    vTaskDelay(2);
    if (StartCMV == true)
    {
      continuous_mandatory_ventilation((float)inhale_value,
                                       (float)exhale_value,
                                       (float)bpm_value,
                                       (float)pressure_value);
    }
  }
}
