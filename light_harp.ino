int pitchInputPin = 0;
int volInputPin = 1;
int volumeOutPin = 6;

int pitchDelay;
int volume;
int count;

int dacPins[]={2,4,7,8};
int sin16[] = {7, 8, 10, 11, 12, 13, 14, 14, 15, 14, 14, 13, 12, 11, 
            10, 8, 7, 6, 4, 3, 2, 1, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6,};

int counter = 0;

void setup()
{
  
  for (int i = 0; i < 4; i++)
  {
     pinMode(dacPins[i], OUTPUT);
  }
  pinMode(volumeOutPin, OUTPUT);
 
  Serial.begin(9600);
}

void loop()
{
  Serial.println("Begin");
  pitchDelay = analogRead(pitchInputPin);
  Serial.println(pitchDelay);
  pitchDelay = map(pitchDelay, 0, 1023, 10, 60);
  
  volume = analogRead(volInputPin);
  Serial.println(volume);
  volume = map(volume, 0, 1023, 10, 70);
  
  for  (int j=0; j<32; j++)
  {
    setOutput(sin16[j]);
    delay(pitchDelay);
  }
  if (count == 10)
  {
    digitalWrite(volumeOutPin, volume);
    count=0;
  }
  count++;
}

void setOutput(byte value)
{
   digitalWrite(dacPins[3], ((value & 8) > 0));
   digitalWrite(dacPins[2], ((value & 4) > 0));
   digitalWrite(dacPins[1], ((value & 2) > 0));
   digitalWrite(dacPins[0], ((value & 1) > 0));
}
