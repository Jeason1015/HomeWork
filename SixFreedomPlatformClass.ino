#include "SixFreedomPlatformClass.h"
using namespace std;

SixFreedomPlatform::SixFreedomPlatform(int sPin_in[6], int dPin_in[6], float longArm_in, float shortArm_in, float stepAngleOri_in, int subdividing_in,
	float bulb_UpPanelCoor_in[motorNum][4], float motor_baseCoor_in[motorNum][4], float MotorAngle_Cur_in[motorNum],
	float curPosition_in[figureNum], float maxTravelRange_in[motorNum], float Height_upPanel2BasePanel_in, float zeroHeight_in)
{
	Height_upPanel2BasePanel = Height_upPanel2BasePanel_in;
	longArm = longArm_in;
	shortArm = shortArm_in;
	stepAngleOri = stepAngleOri_in;
	subdividing = subdividing_in;
	stepAngle = stepAngleOri / subdividing;
	zeroHeight = zeroHeight_in;
	for (int i = 0; i < 6; i++)
	{
		sPin[i] = sPin_in[i];
		dPin[i] = dPin_in[i];
		curPosition[i] = curPosition_in[i];//the position of the center of upPanel 
		maxTravelRange[i] = maxTravelRange_in[i];//the border of rotation angle and translation length
		MotorAngle_Cur[i] = MotorAngle_Cur_in[i];// the ini angle of the angle between short ram and vertical axis of motor, 6 clock orientation is 0 degree, clockwise is positive,counter-clockwise is negative
		for (int j = 0; j < 4; j++)
		{
			bulb_UpPanelCoor[i][j] = bulb_UpPanelCoor_in[i][j];// the bulb coordinate in upPanle coor
			motor_baseCoor[i][j] = motor_baseCoor_in[i][j];// the motor coordinate in base coor
		}
	}
	
	iniTransformationMatrixCurCoor2BaseCoor();
	iniTransformationMatrixBaseCoor2MotorCoor();
	iniCurJointMotorCoor(); 
}

/*************************
 * motion model 1 2 3 4 9
 *************************/

//give the motion angle of 6 motor
Status SixFreedomPlatform::exeMotionByMode1(float motorFigure[motorNum])
{
  int mode=2;
	MotSFP.allMotorsMotion(motorFigure, sPin, dPin, stepAngle,mode);
	return SUCCESS;
}

//give the five point algorithm result to move (rotaiton x, rotaiton y, rotaiton z, translation x, translation y, translation z)
Status SixFreedomPlatform::exeMotionByMode2(float fivePointEulerTx[figureNum])
{
	int motorMode=3;
	float panelMotionEulerTx[figureNum];
	fivePointOutput2PanelMotion(fivePointEulerTx, panelMotionEulerTx);
	bool flag = judgeWhetherExeceedWorkSpace(panelMotionEulerTx);
	if (flag == 1)
	{
		getMotorAngleFromPanelMotion(panelMotionEulerTx, MotSFP.motorMoveAngle);
		MotSFP.allMotorsMotion(MotSFP.motorMoveAngle, sPin, dPin, stepAngle,motorMode);
		updatePlatformStatus(panelMotionEulerTx);
		return SUCCESS;
	}
	else
	{
		return FAILE;
	}
}

//violent to the bottom
Status SixFreedomPlatform::exeMotionByMode3()
{
  float eulerTxFigure[figureNum] = { 60, -60, 60, -60, 60, -60 };
 return exeMotionByMode1(eulerTxFigure);
}

//to the bottom according to current position
Status SixFreedomPlatform::exeMotionByMode4()
{
  float eulerTxFigure[figureNum] = { 0, 0, 0, 0, -zeroHeight, 0 };
  float returnFigure[figureNum]={-curPosition[0],-curPosition[1],-curPosition[2],-curPosition[3],-curPosition[4],-curPosition[5]};
  //exeMotionByMode3();
  exeMotionByMode9(returnFigure);
  return exeMotionByMode9(eulerTxFigure);

}

//give the panel motion to move
Status SixFreedomPlatform::exeMotionByMode9(float eulerTxFigure[figureNum])
{
  //float panelMotionEulerTx[figureNum];
  //fivePointOutput2PanelMotion(5pointEulerTx, panelMotionEulerTx);

  bool flag = judgeWhetherExeceedWorkSpace(eulerTxFigure);
  int motorMode=2;
  if (flag == true)
  {
    getMotorAngleFromPanelMotion(eulerTxFigure, MotSFP.motorMoveAngle);
    MotSFP.allMotorsMotion(MotSFP.motorMoveAngle, sPin, dPin, stepAngle, motorMode);
    updatePlatformStatus(eulerTxFigure);
    return SUCCESS;
  }
  else
  {
    return FAILE;
  }
}

/**********************************
 * R, t, coordinate transformation
 **********************************/

void SixFreedomPlatform::fivePointOutput2PanelMotion(float fivePointEulerTx[figureNum], float panelMotionEulerTx[figureNum])
{
	float rotationMatrix[3][3];
	float translationVector[3];
	float middleMatrix[W][W];
	float panelMotionMatrix[W][W];
	UtilitySFP.euler2RotationMatrix(fivePointEulerTx[0], fivePointEulerTx[1], fivePointEulerTx[2], rotationMatrix);
	for (int i = 0; i<3; i++)
	{
		translationVector[i] = -fivePointEulerTx[i + 3];
	}
	UtilitySFP.RT2TransformationMatrix(rotationMatrix, translationVector, middleMatrix);
	UtilitySFP.transformationMatrixInverse(middleMatrix, panelMotionMatrix);
	UtilitySFP.motionMatrix2EulerTx(panelMotionMatrix, panelMotionEulerTx);
}

void SixFreedomPlatform::getMotorAngleFromPanelMotion(float motionEulerTx[figureNum], float motorMovingAngle[motorNum])
{
	float NextBulb_BaseCoor[motorNum][4];
	float NextBulb_MotorCoor[motorNum][4];
	calNextBulbBaseCoorFromPanelMotion(motionEulerTx, NextBulb_BaseCoor);
	calNextBulbMotorCoorFromNextBulbBaseCoor(NextBulb_BaseCoor, NextBulb_MotorCoor);
	calNextJointMotorCoorFromNextBulbMotorCoor(NextBulb_MotorCoor, NextJoint_MotorCoor);
	calMotorMovingAngleFromNextJointMotorCoor(NextJoint_MotorCoor, motorMovingAngle);
}

void SixFreedomPlatform::calNextBulbBaseCoorFromPanelMotion(float motionEulerTx[figureNum], float NextBulb_BaseCoor[motorNum][4])
{
	//float transformationMatrix[W][W];
	float NextBulb_CurCoor[motorNum][4];
	UtilitySFP.givenPanelEulerTx2CalMatrixBulbNext2BulbCur(motionEulerTx[0], motionEulerTx[1], motionEulerTx[2], motionEulerTx[3], motionEulerTx[4], motionEulerTx[5], T_NextCoor2CurCoor);
	for (int i = 0; i<motorNum; i++)
	{
		MatirxOpSFP.matrixMul(T_NextCoor2CurCoor, bulb_UpPanelCoor[i], NextBulb_CurCoor[i]);//NextBulb閸︺劌缍嬮崜宥呮綏閺嶅洨閮存稉瀣畱閸ф劖鐖�
	}
	for (int j = 0; j<motorNum; j++)
	{
		MatirxOpSFP.matrixMul(T_CurCoor2BaseCoor, NextBulb_CurCoor[j], NextBulb_BaseCoor[j]);//NextBulb閸︺劌鐔�閸ф劖鐖ｇ化璁崇瑓閻ㄥ嫬娼楅弽锟�
	}
}

void SixFreedomPlatform::calNextBulbMotorCoorFromNextBulbBaseCoor(float NextBulb_BaseCoor[motorNum][4], float NextBulb_MotorCoor[motorNum][4])
{
	for (int i = 0; i<motorNum; i++)
	{
		MatirxOpSFP.matrixMul(T_BaseCoor2MotorCoor[i], NextBulb_BaseCoor[i], NextBulb_MotorCoor[i]);
	}
}

void SixFreedomPlatform::calNextJointMotorCoorFromNextBulbMotorCoor(float NextBulb_MotorCoor[motorNum][4], float NextJoint_MotorCoor[motorNum][3])
{
	for (int i = 0; i < motorNum; i++)
	{
		float Bx = NextBulb_MotorCoor[i][0];
		float By = NextBulb_MotorCoor[i][1];
		float Bz = NextBulb_MotorCoor[i][2];
		float alpha = Bx * Bx + By * By + Bz * Bz;
		float beta = alpha + shortArm * shortArm;
		float gama = beta - longArm * longArm;
		float A = 4 * (Bx*Bx + By * By);
		float B = -4 * Bx * gama;
		float C = gama * gama - 4 * By*By*shortArm*shortArm;
		float tem = B * B - 4 * A*C;
		if (i % 2 == 0)
		{
			NextJoint_MotorCoor[i][0] = (-B + sqrt(tem)) / (2 * A);
		}
		else
		{
			NextJoint_MotorCoor[i][0] = (-B - sqrt(tem)) / (2 * A);
		}
		NextJoint_MotorCoor[i][1] = (gama - 2 * Bx*NextJoint_MotorCoor[i][0]) / (2 * By);
		NextJoint_MotorCoor[i][2] = 0;
	}
}

void SixFreedomPlatform::calMotorMovingAngleFromNextJointMotorCoor(float NextJoint_MotorCoor[motorNum][3], float MotorMovingAngle[motorNum])
{
	for (int i = 0; i<motorNum; i++)
	{
		float tmp;
		float tmp1;
		float tmp2;
		float theta;
		MatirxOpSFP.matrixMul(NextJoint_MotorCoor[i], CurJoint_MotorCoor[i], tmp);
		MatirxOpSFP.matrixMul(NextJoint_MotorCoor[i], NextJoint_MotorCoor[i], tmp1);
		MatirxOpSFP.matrixMul(CurJoint_MotorCoor[i], CurJoint_MotorCoor[i], tmp2);
		tmp /= (sqrt(tmp1)*sqrt(tmp2));
		theta = TriSFP.acosd(tmp);
		if (NextJoint_MotorCoor[i][1]<CurJoint_MotorCoor[i][1])
		{
			MotorMovingAngle[i] = -theta;
		}
		else
		{
			MotorMovingAngle[i] = theta;
		}
		
		if (i % 2 != 0)
		{
			MotorMovingAngle[i] = -MotorMovingAngle[i];
		}
	}
}

void SixFreedomPlatform::updatePlatformStatus(float panelMotionEulerTx[figureNum]) 
{
	float T_middle[W][W];
	MatirxOpSFP.matrixMul(T_CurCoor2BaseCoor, T_NextCoor2CurCoor, T_middle);
	for (int rowNum = 0; rowNum < W; rowNum++)
	{
		for (int colNum = 0; colNum < W; colNum++)
		{
			T_CurCoor2BaseCoor[rowNum][colNum] = T_middle[rowNum][colNum];
		}
	}
 
  //Joint positon
	for (int j = 0; j<motorNum; j++)
	{
		for (int cNum = 0; cNum<3; cNum++)
		{
			CurJoint_MotorCoor[j][cNum] = NextJoint_MotorCoor[j][cNum];
		}
	}
 
	//mortor angle
	for (int ma = 0; ma<motorNum; ma++)
	{
		MotorAngle_Cur[ma] = MotorAngle_Cur[ma] + MotorMovingAngle[ma];
	}
 
	//the positon of the center of upPanel
	for (int p = 0; p < figureNum; p++)
	{
		curPosition[p] = curPosition[p] + panelMotionEulerTx[p];
	}
}

bool SixFreedomPlatform::judgeWhetherExeceedWorkSpace(float eulerTxFigure[motorNum]) 
{
	for (int i = 0; i < motorNum; i++){
		if (abs(curPosition[i] + eulerTxFigure[i]) >= maxTravelRange[i]+0.01)
		{
    /*
      Serial.print("");
      Serial.print(i+1);
      Serial.print("");
      Serial.println(abs(curPosition[i]));
      Serial.println(abs(curPosition[i]));
      Serial.println(abs(curPosition[i] + eulerTxFigure[i]));
      Serial.println(maxTravelRange[i]);
      */
			return false; 
		}
	}
	return true;  
}


/********************************
 *3 function about initialization
 ********************************/

void SixFreedomPlatform::iniTransformationMatrixCurCoor2BaseCoor()
{
	UtilitySFP.givenPanelEulerTx2CalMatrixBulbNext2BulbCur(0, 0, 0, 0, -Height_upPanel2BasePanel, 0, T_CurCoor2BaseCoor);
}

//6 motor coordinates
void SixFreedomPlatform::iniTransformationMatrixBaseCoor2MotorCoor()
{
	UtilitySFP.EulerTx2MatrixBulbNext2BulbCur(0, 0, 0, motor_baseCoor[0][0], motor_baseCoor[0][1], motor_baseCoor[0][2], T_BaseCoor2MotorCoor[0]);
	UtilitySFP.EulerTx2MatrixBulbNext2BulbCur(0, 0, 0, motor_baseCoor[1][0], motor_baseCoor[1][1], motor_baseCoor[1][2], T_BaseCoor2MotorCoor[1]);
	UtilitySFP.EulerTx2MatrixBulbNext2BulbCur(0, -120, 0, motor_baseCoor[0][0], motor_baseCoor[0][1], motor_baseCoor[0][2], T_BaseCoor2MotorCoor[2]);
	UtilitySFP.EulerTx2MatrixBulbNext2BulbCur(0, -120, 0, motor_baseCoor[1][0], motor_baseCoor[1][1], motor_baseCoor[1][2], T_BaseCoor2MotorCoor[3]);
	UtilitySFP.EulerTx2MatrixBulbNext2BulbCur(0, 120, 0, motor_baseCoor[0][0], motor_baseCoor[0][1], motor_baseCoor[0][2], T_BaseCoor2MotorCoor[4]);
	UtilitySFP.EulerTx2MatrixBulbNext2BulbCur(0, 120, 0, motor_baseCoor[1][0], motor_baseCoor[1][1], motor_baseCoor[1][2], T_BaseCoor2MotorCoor[5]);
}

void SixFreedomPlatform::iniCurJointMotorCoor()
{
	float motionEulerTx[figureNum] = { 0, 0, 0, 0, 0, 0 };
	float NextBulb_BaseCoor[motorNum][4];
	float NextBulb_MotorCoor[motorNum][4];
	calNextBulbBaseCoorFromPanelMotion(motionEulerTx, NextBulb_BaseCoor);
	calNextBulbMotorCoorFromNextBulbBaseCoor(NextBulb_BaseCoor, NextBulb_MotorCoor);
	calNextJointMotorCoorFromNextBulbMotorCoor(NextBulb_MotorCoor, CurJoint_MotorCoor); 
}
