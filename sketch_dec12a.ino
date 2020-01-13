
const int trigger1 = 2; // pin senzor 1
const int echo1 = 3; // pin echo senzor 1
const int trigger2 = 4; // pin senzor 2
const int echo2 = 5;// pin  echo senzor 2

long durata;
int distanta;
int distanta_stanga;
int distanta_dreapta;

float temp;

int tempPin = A0; //pinul pentru senzor temperatura

int tempMin = 20; // intervale de temperatura

int tempMax = 70;

int fan = 7; //pinul pentru motor

int fanSpeed = 0;

void setup() {
Serial.begin(9600); 
  
pinMode(trigger1, OUTPUT); 
pinMode(echo1, INPUT); 
pinMode(fan, OUTPUT);

pinMode(tempPin, INPUT);
pinMode(trigger2, OUTPUT); 
pinMode(echo2, INPUT); 
}


void calculate_distance(int trigger, int echo)//Calculare distante
{
  
digitalWrite(trigger, LOW);
delayMicroseconds(2);
digitalWrite(trigger, HIGH);
delayMicroseconds(10);
digitalWrite(trigger, LOW);

durata = pulseIn(echo, HIGH);// Calculare durata puls pe pin echo
distanta= durata*0.034/2;//formula pentru calcularea distantei in centimetri

if (distanta>50)
    distanta = 50;
}

void loop() { //infinite loopy
calculate_distance(trigger1,echo1);
distanta_stanga =distanta; //distanta primul senzor


calculate_distance(trigger2,echo2);
distanta_dreapta =distanta; //distanta senzor 2

Serial.print("L=");
Serial.println(distanta_stanga);
Serial.print("R=");
Serial.println(distanta_dreapta);

if ((distanta_stanga >20 && distanta_dreapta>20) && (distanta_stanga <30 && distanta_dreapta<30)) //Detectare ambele maini pause
{Serial.println("Play/Pause"); delay (500);}

calculate_distance(trigger1,echo1);
distanta_stanga =distanta;

calculate_distance(trigger2,echo2);
distanta_dreapta =distanta;

 

// Moduri de control
//Control senzor 1
if (distanta_stanga>=13 && distanta_stanga<=17)
{
  delay(100); //Hand Hold Time
  calculate_distance(trigger1,echo1);
  distanta_stanga =distanta;
  if (distanta_stanga>=13 && distanta_stanga<=17)
  {
    Serial.println("Left Locked");
    while(distanta_stanga<=40)
    {
      calculate_distance(trigger1,echo1);
      distanta_stanga =distanta;
      if (distanta_stanga<10) // Detectare mana
      {Serial.println ("Vup"); delay (300);}
      if (distanta_stanga>20) //Mana in afara intervalului
      {Serial.println ("Vdown"); delay (300);}
    }
  }
}

//Control senzor 2
if (distanta_dreapta>=13 && distanta_dreapta<=17)
{
      delay(100); //Hand Hold Time
      calculate_distance(trigger2,echo2);
      distanta_dreapta =distanta;
      if (distanta_dreapta>=13 && distanta_dreapta<=17)
      {
        Serial.println("Right Locked");
        while(distanta_dreapta<=40)
        {
          calculate_distance(trigger2,echo2);
          distanta_dreapta =distanta;
          if (distanta_dreapta<10) //Detectare mana
             {Serial.println ("Rewind"); delay (300);}
          if (distanta_dreapta>20) //Mana in afara valorilor
          {
            Serial.println ("Forward"); delay (300);
          }
       }
     }
}


temp = analogRead(tempPin);

temp = (temp *5.0*100.0)/1024.0; //Temperatura in celsius

Serial.println(temp);

delay(1000); 

if(temp < tempMin) { 

fanSpeed = 0; 

digitalWrite(fan, LOW);

}

if((temp >= tempMin) && (temp <= tempMax)) 
{

fanSpeed = map(temp, tempMin, tempMax, 32, 255); 

analogWrite(fan, fanSpeed); 

}

delay(200);
}
