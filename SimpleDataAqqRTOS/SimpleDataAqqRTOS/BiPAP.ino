void bilevel_positive_airway_pressure(float inhale, float exhale, float breaths_per_minute, float pressure)
{
  float total_time = inhale + exhale;
  inhale_time = (60 / breaths_per_minute) * ( (float)inhale / total_time);
  exhale_time = (60 / breaths_per_minute) * ( (float)exhale / total_time);
  inhale_time *= 1000;
  exhale_time *= 1000;
  int motor_angle = map(pressure, 0, 30, 14, 180);

  for (uint32_t tStart = millis(); (millis() - tStart) < inhale_time; )
  {
    inhale_is_running = true;
    exhale_is_running = false;
    motor.write(motor_angle);
//    Serial.print("inhale_time: ");
//    Serial.print(inhale_time);
//    Serial.print(" ");
//    Serial.print(" exhale_time: ");
//    Serial.print(exhale_time);
//    Serial.print(" ");
    Serial.print("Inside Inhale Loop");
    Serial.print(" BiPAP");
    Serial.println();
    vTaskDelay(20);
  }

  for (uint32_t tStart = millis(); (millis() - tStart) < exhale_time; )
  {
    inhale_is_running = false;
    exhale_is_running = true;
    motor.write(peep_speed_value);
//    Serial.print("inhale_time: ");
//    Serial.print(inhale_time);
//    Serial.print(" ");
//    Serial.print(" exhale_time: ");
//    Serial.print(exhale_time);
//    Serial.print(" ");
    Serial.print("Inside Exhale Loop");
    Serial.print(" BiPAP");
    Serial.println();
    vTaskDelay(20);
  }
}

void BiPAP( void *pvParameters )
{

  (void) pvParameters;
  for (;;)
  {
    //    Serial.print("StartBiPAP: ");
    //    Serial.print(StartBiPAP);
    //    Serial.println(" ");
    vTaskDelay(2);
    if (StartBiPAP == true)
    {
      bilevel_positive_airway_pressure((float)inhale_value,
                                       (float)exhale_value,
                                       (float)bpm_value,
                                       (float)pressure_value);
    }
  }
}

void BiPAPGraph( void *pvParameters )
{

  (void) pvParameters;
  for (;;)
  {
    vTaskDelay(2);
    if (inhale_is_running)
    {
      float inhale_flow = inspiratory_flow_sensor_data;
      float Bipap_inhale_pressure = inspiratory_sensor_data;
      int   inhale_volume = inhale_flow * (inhale_time / 1000);
      b_flow.setValue((float)inhale_flow);
      b_pressure_feedback.setValue((float)Bipap_inhale_pressure);
      tidal_volume_feedback.setValue((float)inhale_volume);

      Bipap_inhale_pressure = map(Bipap_inhale_pressure, 0, 10, 0, 255);
      float Bipap_flow_Rate = map(inhale_flow, 0, 120, 0, 255);
      float volume = map(inhale_volume, 0, 2000, 0, 255);

      bipap_flow_wave.addValue(0, CH_OFFSET + Bipap_flow_Rate);
      bipap_pressure_wave.addValue(0, CH_OFFSET + Bipap_inhale_pressure);
      bipap_volume_wave.addValue(0, CH_OFFSET + volume);

      cmv_flow_wave.addValue(0, CH_OFFSET + Bipap_flow_Rate);
      cmv_pressure_wave.addValue(0, CH_OFFSET + Bipap_inhale_pressure);
      cmv_volume_wave.addValue(0, CH_OFFSET + volume);
    }

    if (exhale_is_running)
    {
      float exhale_flow = expiratory_flow_sensor_data;
      float Bipap_exhale_pressure = expiratory_sensor_data;
      int exhale_volume = exhale_flow * (exhale_flow / 1000);
      b_flow.setValue((float)exhale_flow);
      b_pressure_feedback.setValue((float)Bipap_exhale_pressure);
      tidal_volume_feedback.setValue((float)exhale_volume);

      Bipap_exhale_pressure = map(Bipap_exhale_pressure, 0, 10, 0, 255);
      float Bipap_flow_Rate = map(exhale_flow, 0, 120, 0, 255);
      float volume = map(exhale_volume, 0, 2000, 0, 255);

      bipap_flow_wave.addValue(0, CH_OFFSET + Bipap_flow_Rate);
      bipap_pressure_wave.addValue(0, CH_OFFSET + Bipap_exhale_pressure);
      bipap_volume_wave.addValue(0, CH_OFFSET + volume);

      cmv_flow_wave.addValue(0, CH_OFFSET + Bipap_flow_Rate);
      cmv_pressure_wave.addValue(0, CH_OFFSET + Bipap_exhale_pressure);
      cmv_volume_wave.addValue(0, CH_OFFSET + volume);
    }
  }
}
