/* 
  Esse é um simples exemplo da biblioteca aREST para Arduino (Uno/Mega/Due/Teensy)
  usando a biblioteca Ethernet, Sensor de Humidade de Temperatura DHT11, um potenciometro, um LED e ServoMotor 
  
 
  Escrito em 2014 por Marco Schwartz sob um licença GPL.
*/

// Libraries
#include <SPI.h>
#include <Ethernet.h>
#include <aREST.h>
#include <avr/wdt.h>
#include <DHT.h>
#include <Servo.h>



// Enter a MAC address for your controller below.
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,2,10);          //Define o endereco IP
IPAddress gateway(192,168,2,1);     //Define o gateway
IPAddress subnet(255, 255, 255, 0); //Define a máscara de rede


// Ethernet server
EthernetServer server(80);

// Criando instancia aREST
aREST rest = aREST();

//init - Necessário para uso do senso DHT11
#define DHTPIN A1 // pino que estamos conectado
#define DHTTYPE DHT11 // DHT 11

DHT dht(DHTPIN, DHTTYPE);

Servo servo1; 


// Variaveis usadas
int t;
int h;
int angle;
int luz;
int alt;



void setup(void)
{  
  // Start Serial
  Serial.begin(115200);
  pinMode(6, OUTPUT);  
  servo1.attach(5); 

  //Denindo variaveis que poderão ser acessadas pela API
  rest.variable("temperature",&t);
  rest.variable("humidity",&h);
  rest.variable("angle",&angle);
  rest.variable("luz",&luz);

  // Function to be exposed
  rest.function("led",ledControl);
  rest.function("servo",servoControl);
  
  // Definindo nome e ID do dispositivo
  rest.set_id("001");
  rest.set_name("Monitor_1");

  // Start the Ethernet connection and the server
  Ethernet.begin(mac, ip, gateway, subnet);
    
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());

  // Start watchdog
  wdt_enable(WDTO_4S);
}

void loop() {  
  
  // Leitura de dados do sensor DHT11
  h = dht.readHumidity();
  t = dht.readTemperature();

  //Leitura de angulo do Potenciomentro
  angle = analogRead(2); 
  
  // Mapeia o valor de 0 a 180 graus
  angle=map(angle, 0, 1023, 0, 180);
  
  EthernetClient client = server.available();
  rest.handle(client);
  wdt_reset();
  
}

//Funções que poderão ser acessadas pela API
int ledControl(String command) {  
  // Get state from command
  int state = command.toInt();  
  digitalWrite(6, state);  
  return 1;
}


int servoControl(String value) {  
  // Get state from value
  int angle = value.toInt();
  servo1.write(angle);
  return 1;
  
}


