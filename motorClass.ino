#include "motorClass.h"

void Motor::allMotorsMotion(float motorAngle[motorNum], int sPin[motorNum], int dPin[motorNum], float stepAngle, int mode)
{
	for (int i = 0; i < 6; i++){ 
		motorStepNum[i] = motorAngle[i] / stepAngle;
   /* Serial.print("");
    Serial.print(i+1);
    Serial.print("");
    Serial.println(motorStepNum[i]);*/
	}
	int maxStep = 0;
	for (int i = 0 ; i < 6; i++) {
		if (maxStep < abs(motorStepNum[i]))
			maxStep = abs(motorStepNum[i]);
	}
  if (mode==1)
  {
    MotionModel1(maxStep,sPin,dPin);
  }
  else if(mode==2)
  {
    MotionModel2(sPin,dPin);
  }
  else
  {
    MotionModel3(maxStep,sPin,dPin);
  }
}

void Motor::MotionModel1(int maxStep,int sPin[motorNum], int dPin[motorNum])
{
  int halfPulsePeriodConfig_mode1=halfPulsePeriodConfig*3;
  //Serial.println("mode1");
	for (int i = 0; i < 6; i++) {
		if (motorStepNum[i] < 0)
		{
		  digitalWrite(dPin[i], LOW);
     //Serial.println("LOW");
     //Serial.println(dPin[i]);
		}
		else
		{
		  digitalWrite(dPin[i], HIGH);
      //Serial.println("HIGH");
     //Serial.println(dPin[i]);
		}
	}
 //Serial.print("maxstep = ");
 //Serial.println(maxStep);
	for (int i = 0; i < maxStep; i++) {
		for (int j = 0; j < 6; j++) {
			if (abs(motorStepNum[j]) != 0)
			{
				int k = maxStep / abs(motorStepNum[j]);
				if (motorStepNum[j] != 0 && i % k == 0 && i < abs(motorStepNum[j])*k) {
					digitalWrite(sPin[j], HIGH);
					delayMicroseconds(halfPulsePeriodConfig_mode1);
					digitalWrite(sPin[j], LOW);
					delayMicroseconds(halfPulsePeriodConfig_mode1);
				}
			}
		}
	}
}

void Motor::MotionModel2(int sPin[motorNum], int dPin[motorNum])
{
  for (int j = 0; j < 6; j++)
  {
    if (motorStepNum[j] < 0)
      digitalWrite(dPin[j], LOW);
    else
      digitalWrite(dPin[j], HIGH);
	  for (int i = 0; i < abs(motorStepNum[j]); i++)
	  {
			digitalWrite(sPin[j], HIGH);
			delayMicroseconds(halfPulsePeriodConfig*5);
			digitalWrite(sPin[j], LOW);
			delayMicroseconds(halfPulsePeriodConfig*5);
		}
	}
}


void Motor::MotionModel3(int maxStep,int sPin[motorNum], int dPin[motorNum])
{
  //Serial.println("mode1");
  for (int i = 0; i < 6; i++) {
    if (motorStepNum[i] < 0)
    {
      digitalWrite(dPin[i], LOW);
     //Serial.println("LOW");
     //Serial.println(dPin[i]);
    }
    else
    {
      digitalWrite(dPin[i], HIGH);
      //Serial.println("HIGH");
     //Serial.println(dPin[i]);
    }
  }
 //Serial.print("maxstep = ");
 //Serial.println(maxStep);
  for (int i = 0; i < maxStep; i++) {
    for (int j = 0; j < 6; j++) {
      if (abs(motorStepNum[j]) != 0)
      {
        int k = maxStep / abs(motorStepNum[j]);
        if (motorStepNum[j] != 0 && i % k == 0 && i < abs(motorStepNum[j])*k) {
          digitalWrite(sPin[j], HIGH);
          delayMicroseconds(halfPulsePeriodConfig);
          digitalWrite(sPin[j], LOW);
          delayMicroseconds(halfPulsePeriodConfig);
        }
      }
    }
  }
}
