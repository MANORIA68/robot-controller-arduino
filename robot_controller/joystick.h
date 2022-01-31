// ***********************************************************************
// ***************************    SCALING    *****************************
// ***********************************************************************

int scaling(int analogread, int analogread_value_min, int analogread_value_middle, int analogread_value_max)
{
  int valeur_retournee;
  int zero = 0;
  int moyen = 512;
  int maximum = 1023;
  int deadzone = 30;

  if (analogread > analogread_value_middle - deadzone && analogread < analogread_value_middle + deadzone)
    valeur_retournee = moyen;

  else if (analogread > analogread_value_middle + deadzone)
  {
    valeur_retournee = map(analogread, analogread_value_middle + deadzone, analogread_value_max, moyen, maximum);
    if (valeur_retournee > maximum)
      return maximum;
  }
  else if (analogread < analogread_value_middle - deadzone)
  {
    valeur_retournee = map(analogread, analogread_value_middle - deadzone, analogread_value_min, moyen, zero);
    if (valeur_retournee < zero)
      return zero;
  }
  return valeur_retournee;
}

// ***********************************************************************
// ***********************    READ JOYSTICK    ***************************
// ***********************************************************************

void read_joystick()
{
  joystate.buttons = (~PIND >> 2) & 0x7F;
  if (PINB & 0x01)
    joystate.buttons &= ~button_mask_joystick;

  speed_read = analogRead(PIN_joystick_speed);
  steer_read = analogRead(PIN_joystick_steer);

  if (correction_scale)
  {
    joystate.speed_send = scaling(speed_read, speed_min, speed_middle, speed_max);
    joystate.steer_send = scaling(steer_read, steer_min, steer_middle, steer_max);
  }
  else
  {
    joystate.speed_send = speed_read;
    joystate.steer_send = steer_read;
  }

  if (inverse_speed)
    joystate.speed_send = 1023 - joystate.speed_send;
  if (inverse_steer)
    joystate.steer_send = 1023 - joystate.steer_send;

  if (serial_print)
  {
    Serial.print(F("\t\t speed_read = "));
    Serial.print(speed_read);
    Serial.print(F("\t steer_read = "));
    Serial.println(steer_read);
    Serial.print(F("\t\t speed_send = "));
    Serial.print(joystate.speed_send);
    Serial.print(F("\t steer_send = "));
    Serial.println(joystate.steer_send);
  }

  if (inverse_send_speed_steer)
  {
    int speed = joystate.speed_send;
    joystate.speed_send = joystate.steer_send;
    joystate.steer_send = speed;
  }
}

// ***********************************************************************
// ***********************    CALIBRATION AUTO    ************************
// ***********************************************************************

void calibration_joystick(byte PIN_joystick, int &value_read)
{
  unsigned long currentMillis = millis();
  unsigned long previousMillis = millis();

  const long interval = 3000;
  long value_read_moyenne = 0;
  int nb_value = 0;

  while (currentMillis - previousMillis < interval)
  {
    value_read = analogRead(PIN_joystick);
    value_read_moyenne += value_read;
    nb_value++;
    currentMillis = millis();
  }

  value_read = value_read_moyenne / nb_value;
}

void calibration_joystick(byte PIN_joystick, int &value_read_min, int &value_read_max)
{
  unsigned long currentMillis = millis();
  unsigned long previousMillis = millis();

  const long interval = 8000;
  int value_read = 0;
  value_read_min = 999999;
  value_read_max = 0;

  while (currentMillis - previousMillis < interval)
  {
    value_read = analogRead(PIN_joystick);

    if (value_read < value_read_min)
      value_read_min = value_read;

    if (value_read > value_read_max)
      value_read_max = value_read;

    currentMillis = millis();
  }
}

int calibration_auto()
{
  Serial.println(F("\n **** keep the speed joystick in the central position ****"));
  calibration_joystick(PIN_joystick_speed, speed_middle);

  Serial.println(F("\n **** keep the steer joystick in the central position ****"));
  calibration_joystick(PIN_joystick_steer, steer_middle);

  Serial.println(F("\n **** move the speed joystick up and down ****"));
  calibration_joystick(PIN_joystick_speed, speed_min, speed_max);

  Serial.println(F("\n **** move the steer joystick from right to left ****"));
  calibration_joystick(PIN_joystick_steer, steer_min, steer_max);

  correction_scale = HIGH;
  save_eeprom();
}
