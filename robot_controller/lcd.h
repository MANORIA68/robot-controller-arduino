// ***********************************************************************
// ***************************    LCD    *********************************
// ***********************************************************************

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

    default:
      break;
    }
    last_print_lcd_time=millis();
  }
}