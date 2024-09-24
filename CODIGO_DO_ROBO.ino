/*
   Autor: Renan dos Santos Oliveira
   Descrição: Esse código foi desenvolvido para o projeto de um agente robótico
   de um sistema multi-agente, com o princípio de estabelecer a comunicação
   
   

*/
//============ BIBLIOTECAS ===========================
#include <TB6612_ESP32.h>
#include <MPU6050_tockn.h>
#include <Wire.h>
#include <BluetoothSerial.h>

//========== DEFINIÇÕES DA PONTE H ====================
#define AIN1 13 // Pino D13 do ESP32 no pino AIN1 da Ponte H TB6612FNG
#define BIN1 12 // Pino D12 do ESP32 no pino BIN1 da Ponte H TB6612FNG
#define AIN2 14 // Pino D14 do ESP32 no pino AIN2 da Ponte H TB6612FNG
#define BIN2 27 // Pino D27 do ESP32 no pino BIN2 da Ponte H TB6612FNG
#define PWMA 26 // Pino D26 do ESP32 no pino PWMA da Ponte H TB6612FNG
#define PWMB 25 // Pino D25 do ESP32 no pino PWMB da Ponte H TB6612FNG
#define STBY 33 // Pino D33 do ESP32 no pino STBY da Ponte H TB6612FNG
// ========= Conexão dos Motores ========
/*
 * Terminais do motor da ESQUERDA conectado no pino A01 e A02 da Ponte H TB6612FNG
 * Terminais do motor da DIREITA conectado no pino B01 e B02 da Ponte H TB6612FNG
 */
//=======================================
const int offsetA = 1;
const int offsetB = 1;
//================ Parâmetros do Giroscópio ======================
// GIROSCÓPIO MPU-6050
// SCL = GPIO D22
// SDA = GPIO D21
MPU6050 mpu6050(Wire);//Criando o objeto
BluetoothSerial SerialBT;
char comando;
//======================= Parâmetros dos Motores =================
Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY, 2000 , 8, 1 );
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY, 2000 , 8, 2 );

void setup()
{
  //============ Inicializando o Bluetooth =======================
  Serial.begin(115200);
  SerialBT.begin("ESP32_Robot"); // Nome do dispositivo Bluetooth
  Serial.println("O dispositivo está pronto para parear");
  //============== Inicializando o Giroscópio ====================
  Wire.begin();
  mpu6050.begin();//Inicializando o objeto
  mpu6050.calcGyroOffsets(true);
  // Calibrar o sensor(sensor deve que ficar parado para calibração)
}


void loop()
{
  comando = (char)SerialBT.read();

  if (Serial.available())
  {
    SerialBT.write(Serial.read());
  }

  if (SerialBT.available())
  {
    mpu6050.update();
    if (comando == 'f')//Andar para frente
    {
      forward(motor1, motor2, 100);
      delay(1000);
      brake(motor1, motor2);
      delay(2000);
      SerialBT.print("Orientação Eixo X : ");
      SerialBT.println(mpu6050.getAngleX());
      SerialBT.print("Orientação Eixo Y : ");
      SerialBT.println(mpu6050.getAngleY());
      SerialBT.print("Orientação Eixo Z : ");
      SerialBT.println(mpu6050.getAngleZ());
    }
    if (comando == 't')//Andar para trás
    {
      back(motor1, motor2, -100);
      delay(1000);
      brake(motor1, motor2);
      delay(2000);
      SerialBT.print("Orientação Eixo X : ");
      SerialBT.println(mpu6050.getAngleX());
      SerialBT.print("Orientação Eixo Y : ");
      SerialBT.println(mpu6050.getAngleY());
      SerialBT.print("Orientação Eixo Z : ");
      SerialBT.println(mpu6050.getAngleZ());
    }
    if (comando == 'p')//Parar
    {
      brake(motor1, motor2);
      delay(1000);
      brake(motor1, motor2);
      delay(2000);
      SerialBT.print("Orientação Eixo X : ");
      SerialBT.println(mpu6050.getAngleX());
      SerialBT.print("Orientação Eixo Y : ");
      SerialBT.println(mpu6050.getAngleY());
      SerialBT.print("Orientação Eixo Z : ");
      SerialBT.println(mpu6050.getAngleZ());
    }
    if (comando == 'e')//Andar para esquerda
    {
      left(motor1, motor2, 100);
      delay(1000);
      brake(motor1, motor2);
      delay(2000);
      SerialBT.print("Orientação Eixo X : ");
      SerialBT.println(mpu6050.getAngleX());
      SerialBT.print("Orientação Eixo Y : ");
      SerialBT.println(mpu6050.getAngleY());
      SerialBT.print("Orientação Eixo Z : ");
      SerialBT.println(mpu6050.getAngleZ());
    }
    if (comando == 'd')//Andar para direita
    {
      right(motor1, motor2, 100);
      delay(1000);
      brake(motor1, motor2);
      delay(2000);
      SerialBT.print("Orientação Eixo X : ");
      SerialBT.println(mpu6050.getAngleX());
      SerialBT.print("Orientação Eixo Y : ");
      SerialBT.println(mpu6050.getAngleY());
      SerialBT.print("Orientação Eixo Z : ");
      SerialBT.println(mpu6050.getAngleZ());
    }
  }
}
