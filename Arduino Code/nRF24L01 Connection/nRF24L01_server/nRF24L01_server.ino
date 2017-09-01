//nrf24_server

#include <SPI.h>
#include <RH_NRF24.h>

// Singleton instance of the radio driver

RH_NRF24 nrf24;

void setup() {
  Serial.begin(9600);
  while (!Serial)
  ; //Wait for serial port to connect.
  if (!nrf24.init ())
    Serial.println("init failed");
  // Defaults after init are 2.402 Ghz (channel 2), 2Mbps, 0dBm
  if (!nrf24.setChannel (1))
    Serial.println("setChannel failed");
  if (!nrf24.setRF (RH_NRF24 :: DataRate2Mbps, RH_NRF24 :: TransmitPower0dBm)) 
    Serial.println("setRF failed");

}

void loop() {
  if (nrf24.available())
  {
    //Should be a message for us now
    uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    if (nrf24.recv(buf, &len))
    {
      // NRF24::printBuffer("request: ", buf,len);
      Serial.print("got request");
      Serial.println((char*)buf);
      
      // Send a reply

      uint8_t data[] = "And helo back to you" ;
      nrf24.send(data, sizeof("data"));
      nrf24.waitPacketSent ();
      Serial.println ("Sent a reply");
    }
    else
    {
      Serial.println ("recv failed");
    }
  }
}






  


  
