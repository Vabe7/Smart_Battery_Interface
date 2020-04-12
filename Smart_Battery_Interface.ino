#include <Wire.h>


#define specifiction_info 0 //packed specification number and scaling information
#define serial_number 0

byte register_to_call = 0;
int16_t current = 0; //charge/discharge rate in mA increments - positive for charge, negative for discharge, 0 to 32,767 mA for charge or 0 to -32,768 mA for discharge
uint16_t remaining_capacity = 0;  //remaining charge in mAh or 10mWh
uint16_t temperature = 0; //cell temperature in tenth degree Kelvin increments, 0 to +6553.5°K
uint16_t overall_voltage = 0; //battery terminal voltage in milli-volts, 0 to 65,535 mV
uint16_t cell_voltage[6] = {0, 0, 0, 0, 0, 0}; //battery cell voltage in milli-volts, 0 to 65,535 mV
uint16_t full_charge_capacity = 0; //estimated full charge capacity in mAh or 10mWh
uint16_t cycle_count = 0; //number of times the battery has been charged, 0 to 65535, 65535 indicates that the battery has been charged exactly that many times or more



void requestEvent(void){
  switch (register_to_call) {
    case 0x0A: //current request
      Wire.write(lowByte(current));
      Wire.write(highByte(current));
      break;
    case 0x0F: //remaining capacity request
      Wire.write(lowByte(remaining_capacity));
      Wire.write(highByte(remaining_capacity));
      break;
    case 0x08: //temperature request
      Wire.write(lowByte(temperature));
      Wire.write(highByte(temperature));
      break;
    case 0x09: //overall voltage request
      Wire.write(lowByte(overall_voltage));
      Wire.write(highByte(overall_voltage));
      break;
    case 0x3f: //cell 1 voltage request
      Wire.write(lowByte(cell_voltage[0]));
      Wire.write(highByte(cell_voltage[0]));
      break;
    case 0x3e: //cell 2 voltage request
      Wire.write(lowByte(cell_voltage[1]));
      Wire.write(highByte(cell_voltage[1]));
      break;
    case 0x3d: //cell 3 voltage request
      Wire.write(lowByte(cell_voltage[2]));
      Wire.write(highByte(cell_voltage[2]));
      break;
    case 0x3c: //cell 4 voltage request
      Wire.write(lowByte(cell_voltage[3]));
      Wire.write(highByte(cell_voltage[3]));
      break;
    case 0x3b: //cell 5 voltage request
      Wire.write(lowByte(cell_voltage[4]));
      Wire.write(highByte(cell_voltage[4]));
      break;
    case 0x3a: //cell 6 voltage request
      Wire.write(lowByte(cell_voltage[5]));
      Wire.write(highByte(cell_voltage[5]));
      break;
    case 0x1a: //specification_Info
      Wire.write(lowByte(specifiction_info));
      Wire.write(highByte(specifiction_info));
      break;
    case 0x10: //full charge capacity
      Wire.write(lowByte(full_charge_capacity));
      Wire.write(highByte(full_charge_capacity));
      break;
    case 0x1c: //serial number
      Wire.write(lowByte(serial_number));
      Wire.write(highByte(serial_number));
      break;
    case 0x17: //cycle count
      Wire.write(lowByte(cycle_count));
      Wire.write(highByte(cycle_count));
      break;

  }

}

void recieveEvent(int Anzahl){
  while (Wire.available()){
    register_to_call = Wire.read();
  }

}

void setup() {
  Wire.begin(0x0B);
  Wire.onReceive(recieveEvent);
  Wire.onRequest(requestEvent);
    
}

void loop() {
  //update values
  
}

