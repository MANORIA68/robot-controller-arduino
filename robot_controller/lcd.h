// ***********************************************************************
// ***************************    LCD    *********************************
// ***********************************************************************

uint8_t battery_0[8]  = {0x0E, 0x1B, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1F};
uint8_t battery_20[8]  = {0x0E, 0x1B, 0x11, 0x11, 0x11, 0x11, 0x1F, 0x1F};
uint8_t battery_40[8]  = {0x0E, 0x1B, 0x11, 0x11, 0x11, 0x1F, 0x1F, 0x1F};
uint8_t battery_60[8]  = {0x0E, 0x1B, 0x11, 0x11, 0x1F, 0x1F, 0x1F, 0x1F};
uint8_t battery_80[8]  = {0x0E, 0x1B, 0x11, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F};
uint8_t battery_100[8]  = {0x0E, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F};

enum item_battery_lcd
{
  BATTERY_0,
  BATTERY_20,
  BATTERY_40,
  BATTERY_60,
  BATTERY_80,
  BATTERY_100,
}; 

bool init_lcd()
{
  if (i2c_test_connection(ADDRESS_I2C_LCD))
  {
    if (connection_lcd == LOW)
    {
      lcd.init();
      connection_lcd = HIGH;
      Serial.print(F("Lcd_i2c_initialiser !"));
    }
    return HIGH;
  }
  else
  {
    Serial.print(F("connection_lcd = LOW"));
    connection_lcd = LOW;
    return LOW;
  }
}

void setup_Lcd()
{
  Serial.print(F("\n\t --- setup_Lcd --- \n"));
  if (!i2c_test_connection(ADDRESS_I2C_LCD))
  {
    connection_lcd = LOW;
    return;
  }
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Controller");
  lcd.setCursor(0, 1);
  lcd.print("init.");
  lcd.createChar(BATTERY_0, battery_0);
  lcd.createChar(BATTERY_20, battery_20);
  lcd.createChar(BATTERY_40, battery_40);
  lcd.createChar(BATTERY_60, battery_60);
  lcd.createChar(BATTERY_80, battery_80);
  lcd.createChar(BATTERY_100, battery_100);
}

String str_lcd(int var, byte size)
{
  String str = String(var);

  if (str.length() < size)
  {
    for (byte i = 0; i < size - str.length(); i++)
    {
      str += " ";
    }
  }
  return str;
}

void print_lcd_joy()
{

  if (last_mode_print_lcd != mode_print_lcd)
  {
    lcd.clear();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Joystick");
    lcd.setCursor(14, 0);
    lcd.write(BATTERY_0); 
    lcd.setCursor(15, 0);
    lcd.write(BATTERY_20); 
    lcd.setCursor(16, 0);
    lcd.write(BATTERY_40); 
    lcd.setCursor(17, 0);
    lcd.write(BATTERY_60); 
    lcd.setCursor(18, 0);
    lcd.write(BATTERY_80); 
    lcd.setCursor(19, 0);
    lcd.write(BATTERY_100); 
    lcd.setCursor(7, 1);
    lcd.print("read:");
    lcd.setCursor(14, 1);
    lcd.print("send:");
    lcd.setCursor(0, 2);
    lcd.print("Speed:");
    lcd.setCursor(0, 3);
    lcd.print("Steer:");

    last_mode_print_lcd = mode_print_lcd;
  }

  lcd.setCursor(7, 2);
  lcd.print(str_lcd(speed_read, 6));
  lcd.setCursor(7, 3);
  lcd.print(str_lcd(steer_read, 6));

  lcd.setCursor(14, 2);
  lcd.print(str_lcd(joystate.speed_send, 6));
  lcd.setCursor(14, 3);
  lcd.print(str_lcd(joystate.steer_send, 6));
}

void print_lcd_feedback()
{

  if (last_mode_print_lcd != mode_print_lcd)
  {
    lcd.clear();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Robot feedback");
    lcd.setCursor(0, 1);
    lcd.print("Speed R:");
    lcd.setCursor(14, 1);
    lcd.print("L:");
    lcd.setCursor(0, 2);
    lcd.print("BatV:");
    lcd.setCursor(10, 2);
    lcd.print("BoardT:");

    last_mode_print_lcd = mode_print_lcd;
  }

  lcd.setCursor(9, 1);
  lcd.print(str_lcd(robot_feedback.speedR_meas, 6));
  lcd.setCursor(16, 1);
  lcd.print(str_lcd(robot_feedback.speedL_meas, 6));
}

void print_lcd_pinout()
{

  if (last_mode_print_lcd != mode_print_lcd)
  {
    lcd.clear();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Pinout");

    lcd.setCursor(0, 1);
    lcd.print("Speed:");
    lcd.setCursor(7, 1);
    lcd.print(PIN_joystick_speed);

    lcd.setCursor(11, 1);
    lcd.print("Steer:");
    lcd.setCursor(18, 1);
    lcd.print(PIN_joystick_steer);

    lcd.setCursor(0, 2);
    lcd.print("Buzzer:");
    lcd.setCursor(8, 2);
    lcd.print(PIN_buzzer);

    lcd.setCursor(11, 2);
    lcd.print("Lcd: 0x");
    lcd.setCursor(18, 2);
    lcd.print(ADDRESS_I2C_LCD);

    last_mode_print_lcd = mode_print_lcd;
  }
}

void print_lcd_cal_no_move()
{
    lcd.clear();
    lcd.backlight();
    lcd.setCursor(5, 0);
    lcd.print("*********");
    lcd.setCursor(1, 1);
    lcd.print("No move joystick");
    lcd.setCursor(5, 2);
    lcd.print("*********");
    last_mode_print_lcd = -1;
}

void print_lcd_cal_move_speed()
{
    lcd.clear();
    lcd.backlight();
    lcd.setCursor(5, 0);
    lcd.print("*** ! ***");
    lcd.setCursor(0, 1);
    lcd.print("Move speed joystick");
    lcd.setCursor(5, 2);
    lcd.print("*** ! ***");
    last_mode_print_lcd = -1;
}

void print_lcd_cal_move_steer()
{
    lcd.clear();
    lcd.backlight();
    lcd.setCursor(5, 0);
    lcd.print(" <<--->> ");
    lcd.setCursor(0, 1);
    lcd.print("Move steer joystick");
    lcd.setCursor(5, 2);
    lcd.print(" <<--->> ");
    last_mode_print_lcd = -1;
}

void print_lcd()
{
  if (millis() - last_print_lcd_time > 150)
  {
    switch (mode_print_lcd)
    {
    case JOYSTICK:
      print_lcd_joy();
      break;

    case FEEDBACK:
      print_lcd_feedback();
      break;

    case PINOUT:
      print_lcd_pinout();
      break;

    default:
      break;
    }
    last_print_lcd_time=millis();
  }
}