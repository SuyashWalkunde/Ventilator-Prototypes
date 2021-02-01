void continuous_mandatory_ventilation()
{
  if(set_cmv_timer)
  {
    cmv_trigger_timer(2.0);
    cmv_window_elapsed = false;
  }
  while(!cmv_window_elapsed)
  {
    delay(10);
    set_cmv_timer = false;
    float pressure = 0;
    if(pressure > inhale_threshold)
    {
      Serial.println("Inside if Positive");
      patient_inhaled = true;
      goto give_extra_breath;
    }
  }
  give_extra_breath : 
      if(patient_inhaled == true)
      {
      bilevel_positive_airway_pressure();
      inhale_threshold = 1.5;
      patient_inhaled = false;
      }  
  Serial.println("Window Elapsed");
  set_cmv_timer = true;
}
void cmv_trigger_timer(float time_in_seconds)
{
  noInterrupts();
  TCCR4A = 0;
  TCCR4B = 0;
  double value = (double)(65535 - (15625 * time_in_seconds));
  TCNT4 = value;                        // preload timer
  TCCR4B |= (1 << CS40) | (1 << CS42);  // 1024 prescaler
  TIMSK4 |= (1 << TOIE4);               // enable timer overflow interrupt ISR
  interrupts();
  Serial.println("Timer Set");
}
