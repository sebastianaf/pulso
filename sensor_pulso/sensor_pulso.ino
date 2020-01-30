// Medidor de pulso cardiaco 
// Modificado por: www.elprofegarcia.com
// Visualiza en LCD 16x2 el valor de BPM, grafica el ritmo cardiaco por el Serial Plotter y pulso por el pin 13
// Conexion Sensor Pulsos -> Arduino UNO:   S -> A0 , Vcc -> 5V , (-) -> GND
// Conexion i2C -> Arduino UNO:  SCL-> A5   SDA->A4  VCC->5V  GND->GND

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);   // inicializa la interfaz I2C del LCD 16x2
int pulsePin = 0;                   // Sensor de Pulso conectado al puerto A0
// Estas variables son volatiles porque son usadas durante la rutina de interrupcion en la segunda Pestaña
volatile int BPM;                   // Pulsaciones por minuto
volatile int Signal;                // Entrada de datos del sensor de pulsos
volatile int IBI = 600;             // tiempo entre pulsaciones
volatile boolean Pulse = false;     // Verdadero cuando la onda de pulsos es alta, falso cuando es Baja
volatile boolean QS = false;        // Verdadero cuando el Arduino Busca un pulso del Corazon

void setup(){ 
 pinMode(13, OUTPUT); 
 lcd.init();                         // Se inicializa el LCD 16x2
 lcd.backlight();                           
 lcd.clear();                                
 Serial.begin(9600);                // Puerto serial configurado a 9600 Baudios
 interruptSetup();                  // Configura la interrucion para leer el sensor de pulsos cada 2mS  
}

void loop(){
 int pulso = analogRead(A0);           //Lee el valor del pulsometro conectado al puerto Analogo A0
 if (pulso >= 530) {                   // Enciende led 13 cuando el pulso pasa de un valor (debe ajustarse)
    digitalWrite(13, HIGH);
 }  
 else{
    digitalWrite(13, LOW);
 }  
   lcd.setCursor(1,0);                   //Muestra en el LCD el valor de BPM 
   lcd.print("BPM= ");
   lcd.print(BPM);
   lcd.print("   "); 
   //Serial.print("BPM = ");  Serial.println(BPM); //Habilitar estas linea para ver BPM en el monitor serial pero deshabilitar la siguiente
   Serial.println(pulso);                          // envia el valor del pulso por el puerto serie  (desabilitarla si habilita la anterior linea)
  if (QS == true){                       // Bandera del Quantified Self es verdadera cuando el Arduino busca un pulso del corazon
    QS = false;                          // Reset a la bandera del Quantified Self 
  }
}











