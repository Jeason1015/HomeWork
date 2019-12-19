#pragma once
#include "config.h"
#include "SixFreedomPlatformClass.h"
int sPin_in[6] = { 7, 6, 5, 4, 3, 2 };
int dPin_in[6] = { A8, A9, A10, A11, A12, A13 };
float Height_upPanel2BasePanel_in = 68.45;
float zeroHeight_in = 30;
float longArm_in = 85;
float shortArm_in = 25.318;
//float stepAngleOri_in = 1.8;
//int subdividing_in = 32;

float stepAngleOri_in = 18;
int subdividing_in = 125;
float iniMotorAngle = 79.44;

float bulb_UpPanelCoor_in[motorNum][4] = { { -2.5, 0, 77, 1 }, { -15.5, 0, 77, 1 }, { -65.432, 0, -40.665, 1 }, { -58.932, 0, -51.923, 1 }, { 67.9320, 0, -36.335, 1 }, { 74.432, 0, -25.077, 1 } };
float motor_baseCoor_in[motorNum][4] = { { 16, 0, 77, 1 }, { -34, 0, 77, 1 }, { -74.6820, 0, -24.644, 1 }, { -49.682, 0, -67.944, 1 }, { 58.682, 0, -52.356, 1 }, { 83.682, 0, -9.056, 1 } };

float MotorAngle_Cur_in[motorNum] = { iniMotorAngle, -iniMotorAngle, iniMotorAngle, -iniMotorAngle, iniMotorAngle, -iniMotorAngle };
float curPosition_in[figureNum] = { 0, 0, 0, 0, 0, 0 };
float maxTravelRange_in[motorNum] = { 10, 10, 10, 30, 30, 30 };


