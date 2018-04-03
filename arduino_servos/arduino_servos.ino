#include <Servo.h>

Servo servo_pitch;  // create servo object to control a servo 
Servo servo_heading;

float pos_pitch = 0, pos_heading = 0; /*!< Pitch and heading values to be written to the servos */
                                     
float diff_pitch = 0, curr_pitch = 0, ancient_pitch = 0; /*!< These are used to get approximations of head movements, avoiding trembling */ 

float diff_heading = 0, curr_heading = 0, ancient_heading = 0; /*!< These are used to get approximations of head movements, avoiding trembling */ 

int i = 0, j = 0; /*!< Used to get ancient pitch and heading, and not the previous ones */

float calib_const_pitch = 1.00;    // calibration constant value which depends on the servo being used
float calib_const_heading = 4.00;  // calibration constant value which depends on the servo being used

int aux = 0;  // auxiliary variable used to control data transport
float num[3]; // roll, pitch and heading values received via serial

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
  
  servo_pitch.attach(9);
  servo_heading.attach(10);
  
  servo_pitch.write(0);
  servo_heading.write(0);
  
}

// the loop routine runs over and over again forever:
void loop() 
{
  //for(int i=0; i<4; i++)
  //{
      
    aux = Serial.read();
    
    if(aux == 73)
    {
    
      for(int i=0; i<3; i++)
      {
        num[i] = Serial.parseFloat();
       } 
      
      //for(int j=0; j<7; j++)
      //{
        //Serial.print(num[j]);
        //Serial.print("  ");
      //}
     
      Serial.print("roll: ");
      Serial.print(num[0]); 
      Serial.print("  pitch: ");
      Serial.print(num[1]);
      Serial.print("  heading: ");
      Serial.print(num[2]);
      Serial.print("  pos_pitch: ");
      Serial.print(pos_pitch);
      Serial.print("  pos_heading: ");
      Serial.println(pos_heading);
      
      pos_pitch = (num[1] + 125)* calib_const_pitch;
      pos_heading = (num[2] + 18) * calib_const_heading;
     
      curr_pitch = num[1];
      curr_heading = num[2];
     
      /*
      Serial.print("accel_x: ");
      Serial.print(num[0]); 
      Serial.print("  accel_y: ");
      Serial.print(num[1]);
      Serial.print("  accel_z: ");
      Serial.print(num[2]);
      Serial.print("  gyro_z: ");
      Serial.print(num[3]);
      Serial.print("  push_button: ");
      Serial.print(num[4]);
      Serial.print("  joy_x: ");
      Serial.print(num[5]);
      Serial.print("  joy_z: ");
      Serial.println(num[6]);
      */
      //Serial.print("\n");
  
      //servo_pitch.write(pos_pitch);

      /*! Diference between current and ancient (10 takes before) 
      pitch and heading, used to avoid trembling */
      diff_pitch = curr_pitch - ancient_pitch;
      diff_heading = curr_heading - ancient_heading;
         
      if(diff_heading > 4 || diff_heading < -4)
      {
          servo_heading.write(pos_heading);
      }
      
      /*!< This 'else' condition is set because when heading is being
      changed, pitch has very high noise, so, it is better to avoid
      heading and pitch commands */
      else if(diff_pitch > 4 || diff_pitch < -4 && diff_heading > -3 && diff_heading < 3)
      {
          servo_pitch.write(pos_pitch);
      }
      
      
               
      /*
      if(num[2] > 15)
      {
        for(int i = 15; i < pos_heading; i++)
        {
          servo_heading.write(i);
        }
      }
      
      else if(num[2] < -15)
      {
        for(int i=-15; i > pos_heading; i--)
        {
          servo_heading.write(i);
        }
      }     
      */
 
      if(i == 10)
      {
        ancient_pitch = num[1];
        i = 0;
      }
      
      if(j == 10)
      {
        ancient_heading = num[2];
        j = 0;
      }
      
      aux = 0;
      
      i++;
      j++;
    }
}
