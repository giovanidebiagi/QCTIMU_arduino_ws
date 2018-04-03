#include <ADXL345_ardu.h>
#include <L3G4200D_ardu.h>
#include <Wire.h>

#define USBCON

ADXL345 accel;                          //ADXL345 object
L3G4200D gyro;                          //L3G4200D object

// Variaveis do joystick
float sw_pin = 2;
int x_pin = 2;
int y_pin = 3;

float acceleration[3];
float gyro_z;

void setup(void)
{
    Serial.begin(115200);

    pinMode(sw_pin, INPUT_PULLUP);

    Wire.begin();

    // Inicializando o giroscópio para 200, 500 ou 2000 graus/seg
    gyro.gyroscopeInit(2000);    

    // Inicializando acelerometro
    accel.accelerometerInit();

    delay(1500);
}

void loop(void)
{
    acceleration[0] = accel.getAcceleration(X_axis);
    acceleration[1] = accel.getAcceleration(Y_axis);
    acceleration[2] = accel.getAcceleration(Z_axis);

    gyro_z = gyro.getGyroData(Z_axis);

    if (Serial.read() == 'I')
    {
        Serial.print("I|");
	Serial.print(acceleration[0]);
	Serial.print("|");
	Serial.print(acceleration[1]);
	Serial.print("|");
	Serial.print(acceleration[2]);
	Serial.print("|");
	Serial.print(gyro_z);
	Serial.print("|");
	Serial.print(analogRead(x_pin));
	Serial.print("|");
	Serial.print(analogRead(y_pin));
	Serial.print("|");
	Serial.print(digitalRead(sw_pin));
	Serial.println("|*");
    }
        
    delay(1); 
}




