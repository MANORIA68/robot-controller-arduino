RF24 nRF(nRF_CE, nRF_CSn);

void nrf_send_data()
{
  nRF.stopListening();

  if (!nRF.write(&Feedback, sizeof(SerialFeedback)))
  {
    // Serial.println(F("Not Ack'd from controller"));
  }
  else
  {
    // Serial.println(F("Ack controller"));
  }
}

bool nrf_receive_data()
{
  nRF.startListening();

  if (nRF.available())
  {
    while (nRF.available())
    {
      nRF.read(&joystate, sizeof(struct joystick_state));
      // Serial.println(F("nRF available"));
      return HIGH;
    }
  }
  else
  {
    // Serial.println(F("nrf no available"));
    return LOW;
  }
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