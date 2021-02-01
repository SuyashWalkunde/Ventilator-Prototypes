//
#include <Servo.h>
#include <SFM4200CORE.h>
#include <Adafruit_ADS1015.h>
#include <Wire.h>
#include <Pushbutton.h>

//Insatnces of Sensors And Motor.
SFM4200CORE senseFlow(0x40);
Adafruit_ADS1115 ads(0x48);
Servo oxygen_motor;
Servo motor;

// Variables for Pressure and Flow Rate Calculation.
double differential_pressure;
float sensor_ambient_air = 44.0;
float first_static_pressure, second_static_pressure;
float flow_rate, air_pressure;
int potValue;
float differential_voltage = 0.0;
int offset = 0; // Offset
float scale = 256.0; // Scale factor for Air & N2 is 140.0, O2 is 142.8
int oxygen_motor_pin = 11;

//PID_Variables
float kp =0.5;


//Pin Configurations.
#define servo_pin 6
#define first_mpxv A1
#define second_mpxv A0
#define AS21_pin A4
#define mpxv_pin A7
#define pot_pin A0
#define oxygen_knob_pin A1

//Flow Calculation Constant.
#define discharg_coefficient 0.95
#define fluid_density 1.25
#define area_constant 0.000066

//Main Array Constant.
#define MAX 5

//mode change Definations and Variables.
#define PEEP 3
#define BPM 2
#define IE 19
#define MODE 18


volatile int peep_counter = 0;
volatile int bpm_counter = 0;
volatile int ie_counter = 0;
volatile int mode_counter = 2;

//BiPAP Variable.
int inhale = 1;
int exhale = 4;
int ie_ratio_array[MAX] = {1, 1, 1, 2, 4};
int PEEP_speed[4] = {30, 45, 65, 95};
int breaths_per_minute = 12;
bool end_loop = false;
bool inhale_complete = false;
bool exhale_complete = true;
bool trigger_window_elasped = false;
float total_time = inhale + exhale;
int oxygen_knob = 0;
volatile bool set_inhale_timer = true;
volatile bool set_exhale_timer = true;
//SIMV Variables
float inspiration_trigger_window = 2.0;

// ADC auto Caliberate
float AS21_offset_inspiratory = 0.0;
float AS21_offset_expipiratory = 0.0;

// CMV Variables
bool cmv_window_elapsed = false;
bool set_cmv_timer = true;
bool patient_inhaled = false;
int8_t inhale_threshold = -1.5;

//Structure for CPAP Parameters
struct CPAP_params
{
  float flow;
  float pressure;
} Suyash;
