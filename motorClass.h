#ifndef _MOTORCLASS_H_
#define _MOTORCLASS_H_
#include "config.h"
class Motor
{
public:
	//Motor(void);
	//~Motor(void);
	float motorMoveAngle[motorNum];
	int halfPulsePeriod = halfPulsePeriodConfig;  
	int motorStepNum[6];     
	void allMotorsMotion(float motorAngle[motorNum], int sPin[motorNum], int dPin[motorNum], float stepAngle, int mode);   //閿熸枻鎷烽敓鍙鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓锟�
	void MotionModel2(int sPin[motorNum], int dPin[motorNum]);
	void MotionModel1(int maxStep,int sPin[motorNum], int dPin[motorNum]);
	void MotionModel3(int maxStep,int sPin[motorNum], int dPin[motorNum]);
};
#endif
