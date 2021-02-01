
void peep_handler()
{
  if (peep_counter < 4)
  {
    peep_counter++;
  }
  else
  {
    peep_counter = 0;
  }
  Serial.print("peep_counter: ");
  Serial.print(peep_counter);
  Serial.println();
}

void bpm_handler()
{
  if (bpm_counter < 4)
  {
    bpm_counter++;
  }
  else
  {
    bpm_counter = 0;
  }
  breaths_per_minute = 10 + (2 * bpm_counter);
  Serial.print("bpm_counter: ");
  Serial.print(bpm_counter);
  Serial.println();

}

void ie_handler()
{
  if (ie_counter < 4)
  {
    ie_counter++;
  }
  else
  {
    ie_counter = 0;
  }
  inhale = ie_ratio_array[ie_counter];
  exhale = ie_ratio_array[(MAX - 1) - ie_counter];
  total_time = inhale + exhale;
  Serial.print("ie_counter: ");
  Serial.print(ie_counter);
  Serial.println();
}

void mode_handler()
{
  if (mode_counter  < 5)
  {
    mode_counter++;
  }
  else
  {
    mode_counter = 0;
  }
  Serial.print("mode_counter: ");
  Serial.print(mode_counter);
  Serial.println();
}
ISR(TIMER1_OVF_vect)                    // interrupt service routine for Inhale timer overflow
{
  Serial.println("Inside Inhale ISR");
  set_exhale_timer = true;
  exhale_complete = false;
}

ISR(TIMER3_OVF_vect)                    // interrupt service routine for Exhale timer overflow
{
  Serial.println("Inside Exhale ISR");
  set_inhale_timer = true;
  inhale_complete = false;
}


ISR(TIMER4_OVF_vect)                    // interrupt service routine for Exhale timer overflow
{
  cmv_window_elapsed = true;
}
