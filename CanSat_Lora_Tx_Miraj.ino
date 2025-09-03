 #include <SPI.h>
 #include <LoRa.h>
 #include <DHT.h>
 #include <Wire.h>
 #include <SD.h>
 #include <MPU6050_light.h>

 

 #define DHTPIN A1
 #define DHTTYPE DHT11
 
 int hum;
 float temp;
 const int cs = 4;
 
 
MPU6050 mpu(Wire);
unsigned long timer = 0;

 DHT dht (DHTPIN , DHTTYPE);
 File datafile;

 
 void setup()
 {
  Serial.begin (9600);
  SD.begin(cs);
  
  Wire.begin(9600);
  byte status = mpu.begin();
  
  dht.begin();
  while (!Serial);

  Serial.println ("Lora send Data");

  if (!LoRa .begin (433E6))
  {
    Serial.println ("Connecting Lora failed");
    while (1);
    
  }
 }





void loop ()
{
  mpu.update();
  
  temp = dht.readTemperature ();
  hum = dht.readHumidity ();
float  x= mpu.getAngleX();
float  y= mpu.getAngleY();
float  z= mpu.getAngleZ();

String stringdata = "";

  stringdata += "Humidity = " + String (hum) + " %" + "   Temperature = " + String(temp) + "C" + "   Angle of X = "+ String(x) + "   Angle of Y = " + String (y) + "   Angle of Z = " + String (z) + "Battery Voltage = Sensor nai";                                    

 File datafile = SD.open ("miraj.txt" , FILE_WRITE);

 if (datafile )
{
  datafile.println (stringdata);
  datafile.close();
  //Serial.println (stringdata);
  
}

else 
{
  Serial.println ("Fuck off!!!");
}

  
  

 Serial.println ("Sending data: ");
  
  LoRa.beginPacket ();

  LoRa.print ("Humidity = ");
  LoRa.print (hum);
  LoRa.print ("%");
  
  LoRa.print ("      Tamparature = ");
  LoRa.print (temp);
  LoRa.print ("C");


  LoRa.print ("      Angle of X axis = ");
  LoRa.print (x);
  
  LoRa.print ("      Angle of Y axis = ");
  LoRa.print (y);

  LoRa.print ("      Angle of Z axis = ");
  LoRa.print (z);

  Serial.print ("Humidity = ");
  Serial.print (hum);
  Serial.print ("%");
  
  Serial.print ("        Tamparature = ");
  Serial.print (temp);
  Serial.print ("C");

  Serial.print ("        Angle of X axis = ");
  Serial.print (x);
  
  Serial.print ("        Angle of Y axis = ");
  Serial.print (y);

  Serial.print ("        Angle of Z axis = ");
  Serial.println (z);
  
  Serial.println ("");

 LoRa.endPacket();

  


 LoRa.endPacket ();


  delay (500);
}
 