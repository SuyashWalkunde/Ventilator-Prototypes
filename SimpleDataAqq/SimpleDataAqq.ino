#include "definations.h"
uint32_t get_flowrate_from_sfm()
{
  float flow_rate = senseFlow.getvalue(); // slm
  return (16.67 * (flow_rate - offset) / scale);
}

float get_AS21_Pressure(int analog_pin)
{
  float AS21_adc = analogRead(A7);
  float air_pressure = ((AS21_adc - AS21_offset_inspiratory) /41.66);
//  return (AS21_adc*4.89);
  return air_pressure * 10;
}

float get_SDP11108_flow_rate(int analog_pin)
{
  float sensor_ADC = (analogRead(analog_pin));
  float voltage_mV = ((5000/1023) * sensor_ADC);
  float voltage = (voltage_mV / 1000);
  float differential_pressure =sq((voltage - 0.25 )/ (3.75)) * 500;
  double flow_rate_mL_sec = discharg_coefficient * sqrt(2 * (abs(differential_pressure)) / fluid_density) * area_constant;

  return (flow_rate_mL_sec * 1000000);
}

//float get_flow_rate(double delta_pressure)
//{
//  double flow_rate_mL_sec = discharg_coefficient * sqrt(2 * (abs(delta_pressure) * 1000) / fluid_density) * area_constant;
//  return flow_rate_mL_sec * 1000000;
//}

float get_oxygen_value()
{
  return ads.readADC_Differential_0_1();
}

int get_pressure_knob(int analog_pin)
{
  int pressure_value = analogRead(analog_pin);
  int scaled_pressure = map(pressure_value, 0, 1023, 0, 180);
  return scaled_pressure;
}

int get_oxygen_knob(int analog_pin)
{
  int oxygen_value = analogRead(analog_pin);
//  Serial.print(oxygen_value);
//  Serial.println();
  int scaled_oxygen = map(oxygen_value, 0, 1023, 0, 180);
  return scaled_oxygen;
}

void setup() {
  
  //Parameters For ADS1115 And Flow Rate

  ads.setGain(GAIN_TWO);
  ads.begin();
  senseFlow.init();
  analogReference(EXTERNAL);
  Serial.begin(9600);
  // Pins For Interrupt used for Modes and Other Quantity Change.
  pinMode(PEEP, INPUT_PULLUP);
  pinMode(BPM, INPUT_PULLUP);
  pinMode(IE, INPUT_PULLUP);
  pinMode(MODE, INPUT_PULLUP);

  // Motor Setup and Min-Max Caliberation.
  motor.attach(servo_pin, 1000, 2000);
  Serial.println("Initilizing ESC...");
  motor.write(18);
  delay(3000);
  motor.write(0);
  delay(3000);

  //
  AS21_offset_inspiratory = analogRead(A7);

  // Oxygen Control Motor
  oxygen_motor.attach(oxygen_motor_pin);
  oxygen_motor.write(0);
  //Interrupt Defination for Mode Switch
  attachInterrupt(digitalPinToInterrupt(PEEP), peep_handler, FALLING);
  attachInterrupt(digitalPinToInterrupt(BPM), bpm_handler, FALLING);
  attachInterrupt(digitalPinToInterrupt(IE), ie_handler, FALLING);
  attachInterrupt(digitalPinToInterrupt(MODE), mode_handler, FALLING);
}

void loop() {

  mode_counter = 2;
  if (mode_counter == 0)
  {
    Serial.println("No Mode");
  }
  else if (mode_counter == 1)
  {
    CPAP_params parameters = continuous_positive_airway_pressure();
  }
  else if (mode_counter == 2)
  {
    bilevel_positive_airway_pressure();
  }
  else if (mode_counter == 3)
  {
    motor.write(0);
    synchronized_intermittent_mandatory_ventilation_vc();
  }
  else if (mode_counter == 4)
  {
    motor.write(0);
    synchronized_intermittent_mandatory_ventilation_pc();
  }
  else if (mode_counter == 5)
  {
    motor.write(0);
    continuous_mandatory_ventilation();
  }
  else{
    mode_counter = 0;
  }
}
