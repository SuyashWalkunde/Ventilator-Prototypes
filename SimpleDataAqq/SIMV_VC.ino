void synchronized_intermittent_mandatory_ventilation_vc()
{
  uint32_t inspiration_flow = get_flowrate_from_sfm();
  Serial.print("inspiration_flow: ");
  Serial.print(inspiration_flow);
  Serial.println();
  
}
