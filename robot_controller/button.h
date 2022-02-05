
#define button_mask_up 0x01
#define button_mask_right 0x02
#define button_mask_down 0x04
#define button_mask_left 0x08
#define button_mask_start 0x10
#define button_mask_select 0x20
#define button_mask_joystick 0x40

unsigned long last_button_time = 0;

void read_button()
{
    joystate.buttons = (~PIND >> 2) & 0x7F;
    if (PINB & 0x01)
        joystate.buttons &= ~button_mask_joystick;

    if (joystate.buttons & button_mask_up)
        Serial.println(F("UP "));
    if (joystate.buttons & button_mask_right)
        Serial.println(F("RIGHT "));
    if (joystate.buttons & button_mask_down)
        Serial.println(F("DOWN "));
    if (joystate.buttons & button_mask_left)
    {
        Serial.println(F("LEFT "));

        if (millis() - last_button_time > 400)
        {
            mode_print_lcd++;
            // overflow(mode_print_lcd, 0, sizeof(enum item_mode_lcd) - 1);
            overflow(mode_print_lcd, 0, 2);
            last_button_time = millis();
        }
    }
    if (joystate.buttons & button_mask_start)
        Serial.println(F("START "));
    if (joystate.buttons & button_mask_select)
        Serial.println(F("SELECT "));
    if (joystate.buttons & button_mask_joystick)
        Serial.println(F("JOYSTICK "));
}