CPAP_params continuous_positive_airway_pressure()
{
  CPAP_params parameters;
  int pressure_knob = get_pressure_knob(pot_pin);
  int oxygen_knob = get_oxygen_knob(oxygen_knob_pin);
  float oxygen_value = 0;
  float expiratory_flow = get_SDP11108_flow_rate(A4);
  oxygen_value = get_oxygen_value();
  oxygen_motor.write(oxygen_knob);
  Serial.print("Pressure: ");
  Serial.print(pressure_knob);
  Serial.print("  ");
  Serial.print("oxygen_knob: ");
  Serial.print(oxygen_knob);
  Serial.print("  ");
  motor.write(pressure_knob);
  parameters.pressure = get_AS21_Pressure(A7);
  parameters.flow = get_flowrate_from_sfm();
  Serial.print("parameters.flow: ");
  Serial.print(parameters.flow);
  Serial.print("  ");
  Serial.print("parameters.pressure: ");
  Serial.print(parameters.pressure);
  Serial.print("  ");
  Serial.print("expiratory_flow: ");
  Serial.print(expiratory_flow);
  Serial.println();
  return parameters;

}
