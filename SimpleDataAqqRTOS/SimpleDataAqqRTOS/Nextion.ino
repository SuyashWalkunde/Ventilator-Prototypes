void CPAP_startPushCallback(void *ptr)
{

  StartCPAP = true;
  StartBiPAP = false;
  PrintNex = 269;
  c_inhale.getValue(&inhale_value);
  c_exhale.getValue(&exhale_value);
  c_pressure.getValue(&pressure_value);
  c_bpm.getValue(&bpm_value);
  Serial.print("StartCPAP: ");
  Serial.print(StartCPAP);
  Serial.print("  ");
  Serial.print("StartBiPAP: ");
  Serial.print(StartBiPAP);
  Serial.print("  ");
  Serial.print("inhale: ");
  Serial.print(inhale_value);
  Serial.print("  ");
  Serial.print("exhale: ");
  Serial.print(exhale_value);
  Serial.print("  ");
  Serial.print("pressure: ");
  Serial.print(pressure_value);
  Serial.print("  ");
  Serial.print("BPM: ");
  Serial.print(bpm_value);
  Serial.println();
}
void BiPAP_startPushCallback(void *ptr)
{
  //  display_mode_counter = 2;
  StartBiPAP = true;
  StartCPAP = false;
  PrintNex = 269;
  b_inhale.getValue(&inhale_value);
  b_exhale.getValue(&exhale_value);
  b_pressure.getValue(&pressure_value);
  b_bpm.getValue(&bpm_value);
  peep_speed.getValue(&peep_speed_value);
  tidal_volume.getValue(&tidal_volume_value);
  Serial.print("StartCPAP: ");
  Serial.print(StartCPAP);
  Serial.print("  ");
  Serial.print("StartBiPAP: ");
  Serial.print(StartBiPAP);
  Serial.print("  ");;
  Serial.print("inhale: ");
  Serial.print(inhale_value);
  Serial.print("  ");
  Serial.print("exhale: ");
  Serial.print(exhale_value);
  Serial.print("  ");
  Serial.print("pressure: ");
  Serial.print(pressure_value);
  Serial.print("  ");
  Serial.print("BPM: ");
  Serial.print(bpm_value);
  Serial.print("  ");
  Serial.print("Tidal_volume: ");
  Serial.print(tidal_volume_value);
  Serial.print("  ");
  Serial.print("PEEP: ");
  Serial.print(peep_speed_value);
  Serial.println();
}

void CMV_startPushCallback(void *ptr)
{
  //  display_mode_counter = 3;
  StartCMV = true;
  StartCPAP = false;
  StartBiPAP = false;
  PrintNex = 269;
  cmv_inhale.getValue(&inhale_value);
  cmv_exhale.getValue(&exhale_value);
  cmv_pressure.getValue(&pressure_value);
  cmv_bpm.getValue(&bpm_value);
  cmv_peep_speed.getValue(&peep_speed_value);
  cmv_flow_feedback.getValue(&flow_value);
  cmv_fio2_feedback.getValue(&fio2_value);
  cmv_tidal_volume_feedback.getValue(&tidal_volume_value);

  Serial.print("inhale: ");
  Serial.print(inhale_value);
  Serial.print("  ");
  Serial.print("exhale: ");
  Serial.print(exhale_value);
  Serial.print("  ");
  Serial.print("pressure: ");
  Serial.print(pressure_value);
  Serial.print("  ");
  Serial.print("BPM: ");
  Serial.print(bpm_value);
  Serial.print("  ");
  Serial.print("Tidal_volume: ");
  Serial.print(tidal_volume_value);
  Serial.print("  ");
  Serial.print("PEEP: ");
  Serial.print(peep_speed_value);
  Serial.println();
}

void SIMV_PC_startPushCallback(void *ptr)
{
  //  display_mode_counter = 3;
  StartSIMV_PC = true;
  StartCMV = false;
  StartCPAP = false;
  StartBiPAP = false;
  PrintNex = 269;
  simv_pc_inhale.getValue(&inhale_value);
  simv_pc_exhale.getValue(&exhale_value);
  simv_pc_pressure_feedback.getValue(&pressure_value);
  simv_pc_bpm.getValue(&bpm_value);
  simv_pc_peep_speed.getValue(&peep_speed_value);
  simv_pc_flow_feedback.getValue(&flow_value);
  simv_pc_fio2_feedback.getValue(&fio2_value);
  simv_pc_tidal_volume_feedback.getValue(&tidal_volume_value);
  Serial.print("inhale: ");
  Serial.print(inhale_value);
  Serial.print("  ");
  Serial.print("exhale: ");
  Serial.print(exhale_value);
  Serial.print("  ");
  Serial.print("pressure: ");
  Serial.print(pressure_value);
  Serial.print("  ");
  Serial.print("BPM: ");
  Serial.print(bpm_value);
  Serial.print("  ");
  Serial.print("Tidal_volume: ");
  Serial.print(tidal_volume_value);
  Serial.print("  ");
  Serial.print("PEEP: ");
  Serial.print(peep_speed_value);
  Serial.println();
}




//void SIMV_VC_startPushCallback(void *ptr)
//{
//  //  display_mode_counter = 3;
//  StartSIMV_PC = false;
//  StartCMV = false;
//  StartCPAP = false;
//  StartBiPAP = false;
//  PrintNex = 269;
//  simv_vc_inhale.getValue(&inhale_value);
//  simv_vc_exhale.getValue(&exhale_value);
//  simv_vc_pressure_feedback.getValue(&pressure_value);
//  simv_vc_bpm.getValue(&bpm_value);
//  simv_vc_peep_speed.getValue(&peep_speed_value );
//  simv_vc_flow_feedback.getValue(&flow_value);
//  simv_vc_fio2_feedback.getValue(&fio2_value);
//  simv_vc_tidal_volume_feedback.getValue(&tidal_volume_value);
//  Serial.print("inhale: ");
//  Serial.print(inhale_value);
//  Serial.print("  ");
//  Serial.print("exhale: ");
//  Serial.print(exhale_value);
//  Serial.print("  ");
//  Serial.print("pressure: ");
//  Serial.print(pressure_value);
//  Serial.print("  ");
//  Serial.print("BPM: ");
//  Serial.print(bpm_value);
//  Serial.print("  ");
//  Serial.print("Tidal_volume: ");
//  Serial.print(tidal_volume_value);
//  Serial.print("  ");
//  Serial.print("PEEP: ");
//  Serial.print(peep_speed_value);
//  Serial.println();
//}
