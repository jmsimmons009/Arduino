int dacPins[]={2,4,7,8};
int sin16[] = {7, 8, 10, 11, 12, 13, 14, 14, 15, 14, 14, 13, 12, 11, 10, 8, 7, 6, 4, 3, 2, 1, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6,}; 

int lowToneDurations[] = {120, 105, 42, 89, 78, 74, 62}; //Octave 1
//                         A     B   C  D   E    F    G
int highToneDurations[] = {54, 45, 12, 36, 29, 26, 22}; //Octave 2
//                          a  b    c  d    e   f   g

//Scale
//char* song = "A B C D E F G a b c d e f g";

//Star Wars
char* song = "G G G CCC ggg fed cc ggg fed cc ggg fef ddd GG G CCC ggg fed cc ggg fed cc ggg";  
             //"fef ddd GG G AAA A fedc cde dd A BB GG G" 
             //"AAA A fedc ggd ddd GG G AAA A fedc";
void setup()
{
  for (int i = 0; i < 4; i++)
  {
      pinMode(dacPins[i], OUTPUT); //Set Digital Pins to Output
  }
  Serial.begin(9600);
}

void loop()
{
  int i = 0;
  char ch = song[0];
  while (ch!= 0) //Check the array "song" for the notes
  {
    if (ch == ' ') // pause
    {
      delay(75); 
    }
    else if (ch >= 'A' and ch <= 'G') //Octave 1
    {
      playNote(lowToneDurations[ch - 'A']); 
    }
    else if (ch >= 'a' and ch <= 'g') //Octave 2
    {
      playNote(highToneDurations[ch - 'a']);
    }
    i++;
    ch = song[i];
  }
  delay(10000);
}

void setOutput(byte value)
{
  digitalWrite(dacPins[3], ((value & 8) > 0));
  digitalWrite(dacPins[2], ((value & 4) > 0));
  digitalWrite(dacPins[1], ((value & 2) > 0));
  digitalWrite(dacPins[0], ((value & 1) > 0));
}

void playNote(int pitchDelay)
{
    long numCycles = 5000 / pitchDelay + (pitchDelay / 4);
    for (int c = 0; c < numCycles; c++)
    {
      for (int i = 0; i < 32; i++)
      {
        setOutput(sin16[i]);
        delayMicroseconds(pitchDelay);
      }
    }
}
