
// ***********************************************************************
// **************************    EEPROM    *******************************
// ***********************************************************************

void variable_default()
{
  PIN_joystick_speed = 15;
  PIN_joystick_steer = 16;
  inverse_speed = 0;
  inverse_steer = 0;
  inverse_send_speed_steer = 0;
  correction_scale = 0;
  speed_min = 0;
  speed_middle = 512;
  speed_max = 1023;
  steer_min = 0;
  steer_middle = 512;
  steer_max = 1023;
}

void save_eeprom()
{
  byte byte_position = 1;

  EEPROM.put(byte_position, PIN_joystick_speed);
  byte_position+=sizeof(PIN_joystick_speed);

  EEPROM.put(byte_position, PIN_joystick_steer);
  byte_position+=sizeof(PIN_joystick_steer);

  EEPROM.put(byte_position, inverse_speed);
  byte_position+=sizeof(inverse_speed);

  EEPROM.put(byte_position, inverse_steer);
  byte_position+=sizeof(inverse_steer);

  EEPROM.put(byte_position, correction_scale);
  byte_position+=sizeof(correction_scale);

  EEPROM.put(byte_position, inverse_send_speed_steer);
  byte_position+=sizeof(inverse_send_speed_steer);

  EEPROM.put(byte_position, speed_min);
  byte_position+=sizeof(speed_min);

  EEPROM.put(byte_position, speed_middle);
  byte_position+=sizeof(speed_middle);

  EEPROM.put(byte_position, speed_max);
  byte_position+=sizeof(speed_max);

  EEPROM.put(byte_position, steer_min);
  byte_position+=sizeof(steer_min);

  EEPROM.put(byte_position, steer_middle);
  byte_position+=sizeof(steer_middle);

  EEPROM.put(byte_position, steer_max);
  byte_position+=sizeof(steer_max);
}

void read_eeprom()
{
  byte byte_position = 1;

  EEPROM.get(byte_position, PIN_joystick_speed);
  byte_position+=sizeof(PIN_joystick_speed);

  EEPROM.get(byte_position, PIN_joystick_steer);
  byte_position+=sizeof(PIN_joystick_steer);
  
  EEPROM.get(byte_position, inverse_speed);
  byte_position+=sizeof(inverse_speed);
  
  EEPROM.get(byte_position, inverse_steer);
  byte_position+=sizeof(inverse_steer);
  
  EEPROM.get(byte_position, correction_scale);
  byte_position+=sizeof(correction_scale);
  
  EEPROM.get(byte_position, inverse_send_speed_steer);
  byte_position+=sizeof(inverse_send_speed_steer);
  
  EEPROM.get(byte_position, speed_min);
  byte_position+=sizeof(speed_min);
  
  EEPROM.get(byte_position, speed_middle);
  byte_position+=sizeof(speed_middle);
  
  EEPROM.get(byte_position, speed_max);
  byte_position+=sizeof(speed_max);
  
  EEPROM.get(byte_position, steer_min);
  byte_position+=sizeof(steer_min);
  
  EEPROM.get(byte_position, steer_middle);
  byte_position+=sizeof(steer_middle);
  
  EEPROM.get(byte_position, steer_max);
  byte_position+=sizeof(steer_max);
  
}

void init_eeprom()
{
  if (EEPROM.read(0) != value_to_init_eeprom)
  {
    Serial.println(F("\n\t --- variable_default --- \n"));
    variable_default();
    save_eeprom();
    EEPROM.write(0, value_to_init_eeprom);
  }
  else
  {
    Serial.println(F("\n\t --- read_eeprom --- \n"));
    read_eeprom();
  }
}