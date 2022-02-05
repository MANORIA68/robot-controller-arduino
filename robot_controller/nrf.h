RF24 nRF(nRF_CE, nRF_CSn);

void nrf_send_data()
{
  nRF.stopListening();

  if (!nRF.write(&joystate, sizeof(struct joystick_state)))
  {
    if (SERIAL_DEBUG)
      Serial.println(F("Not Ack'd from bot"));
  }
  else
  {
    if (SERIAL_DEBUG)
      Serial.println(F("Ack from bot"));
  }
}

void nrf_receive_data()
{
  nRF.startListening();

  if (nRF.available())
  {
    while (nRF.available())
    {
      nRF.read(&robot_feedback, sizeof(struct feedback_data));
      if (SERIAL_DEBUG)
        Serial.println(F("nRF available"));
    }
  }
  else if (SERIAL_DEBUG)
    Serial.println(F("nRF no available"));
}

void init_nrf(const byte tx_address[6], const byte rx_address[6])
{
  Serial.println(F(" init nrf"));

  printf_begin();
  if (!nRF.begin())
    Serial.println(F("radio hardware is not responding!!"));

  nRF.openWritingPipe(tx_address);
  nRF.openReadingPipe(1, rx_address);
  nRF.printDetails();
}