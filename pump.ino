//Pin declaration
const int low=24, med=26, full=30, pit=21, pump=32/*pump on/off */; 
bool var=0, lState, mState, aState, fState; //var: variable to check pump is on or off 0:on, 1:off
volatile bool pState/*pit State: 1-Not empty, 0-empty*/;

void setup()
{
  pinMode(low, INPUT_PULLUP);
  pinMode(med, INPUT_PULLUP);
  pinMode(full, INPUT_PULLUP);
  pinMode(pump, OUTPUT);
  pinMode(pit, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop()
{
  checkPit();    //Checks pit state
  readS();       //Checks tank water level
  if((pState==0)&&(fState==1))  //if pit not empty and tank empty turn pump on
  {
    digitalWrite(pump, HIGH);
    var=0;
  }
  else
    {
      var=1;
      digitalWrite(pump, LOW);
    }
  while(pState==0)
  {
    readS();  //read sensor data
    if(fState==0)
    {
      var=1;
      digitalWrite(pump, LOW);
      Serial.println("-4-0- Water Level: FULL, Pump: OFF"); 
    }
    else if(mState==0)
    {
      if(var==0)
        Serial.println("-2-1- Water Level: Medium, Pump: ON");
      else
        Serial.println("-2-0- Water Level: Medium, Pump: OFF");
    }
    else if(lState==0)
    {
      if(var==0)
        Serial.println("-1-1- Water Level: Low, Pump: ON");
      else
        Serial.println("-1-0- Water Level: Low, Pump: OFF");
    }
    else
    {
      if(var==0)
        Serial.println("-0-1- Water Level: EMPTY, Pump: ON");
      else
        Serial.println("-0-0- Water Level: EMPTY, Pump: OFF");
    }
    checkPit();
    delay(500);
  
    if((pState==0)&&(fState==1))
    {
      var=0;
      digitalWrite(pump, HIGH);
    }
    else
    {
      var=1;
      digitalWrite(pump, LOW);
    }
  }
} 

void readS()
{
  lState=digitalRead(low);
  mState=digitalRead(med);
  fState=digitalRead(full);
}

void checkPit()
{
  pState=digitalRead(pit);
}
