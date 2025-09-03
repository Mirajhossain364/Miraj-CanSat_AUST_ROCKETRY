#include <SPI.h>
#include <LoRa.h>

void setup ()
{
  Serial.begin (9600);
  while (!Serial);
  Serial.println ("LoRa Receive Data ");

  if (!LoRa.begin (433E6))
  {
    Serial.println ("LoRa connection failed ");
    while (1);
    
  }
  
}

void loop ()
{
  int packetSize = LoRa.parsePacket ();

  if (packetSize)
  {
    Serial.println ("");
    Serial.println ("___________________________________");
    Serial.println ("Received packet :");

    while (LoRa. available ())
    {
      char incoming = (char)LoRa.read();
      if (incoming == 'c')
      {
        Serial.print("Error");
        
      }
      else
      {
        Serial.print (incoming);
      }
    }
  }
}
