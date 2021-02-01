void inspiratory_pressure(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  for (;;) // A Task shall never return or exit.
  {
    float AS21_adc = analogRead(A7);
    inspiratory_sensor_data = ((AS21_adc - inspiratory_sensor) / 41.66);
  }
}

void expiratory_pressure(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  for (;;)
  {
    float AS21_adc = analogRead(A8);
    expiratory_sensor_data = ((AS21_adc - expiratory_sensor) / 41.66);
  }
}

void expiratory_flow_rate(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  for (;;)
  {
    float sensor_ADC = (analogRead(A4));
    float voltage_mV = ((5000 / 1023) * sensor_ADC);
    float voltage = (voltage_mV / 1000);
    float differential_pressure = sq((voltage - 0.25 ) / (3.75)) * 500;
    double flow_rate_mL_sec = discharg_coefficient * sqrt(2 * (abs(differential_pressure)) / fluid_density) * area_constant;
    expiratory_flow_sensor_data = (flow_rate_mL_sec * 1000000);
  }
}

void inspiratory_flow_rate(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  for (;;)
  {
    inspiratory_flow_sensor_data = senseFlow.getvalue(); // slm
    inspiratory_flow_sensor_data = (inspiratory_flow_sensor_data / scale); 
    //
  }
}

// int motor_angle = map(pressure, 0, 30, 14, 180);
