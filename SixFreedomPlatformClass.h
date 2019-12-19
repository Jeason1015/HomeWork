#ifndef _SIXFREEDOM_H_
#define _SIXFREEDOM_H_
#include "config.h"
#include "motorClass.h"
#include "mathOperationClass.h"

enum Status { FAILE = 0, SUCCESS = 1, GETPARAM };
class SixFreedomPlatform
{
  public:
    SixFreedomPlatform(int sPin_in[6], int dPin_in[6], float longArm_in, float shortArm_in, float stepAngleOri_in, int subdividing_in,
                       float bulb_UpPanelCoor_in[motorNum][4], float motor_baseCoor_in[motorNum][4], float MotorAngle_Cur_in[motorNum],
                       float curPosition_in[figureNum], float maxTravelRange_in[motorNum], float Height_upPanel2BasePanel_in, float zeroHeight_in);
    //	  ~SixFreedomPlatform(void);
    int sPin[6];
    int dPin[6];
    float zeroHeight;
    float Height_upPanel2BasePanel;
    float longArm;
    float shortArm;
    float stepAngleOri; 
    int subdividing; 
    float stepAngle = stepAngleOri / subdividing;
    float bulb_UpPanelCoor[motorNum][4];      
    float motor_baseCoor[motorNum][4];
    float MotorMovingAngle[motorNum];
    float NextJoint_MotorCoor[motorNum][3];
    float CurJoint_MotorCoor[motorNum][3];
    float MotorAngle_Cur[motorNum];
    
    //float curRx, curRy, curRz, curX, curY, curZ;
    float curPosition[figureNum];
    float T_NextCoor2CurCoor[4][4];
    float T_CurCoor2BaseCoor[4][4];
    float T_BaseCoor2MotorCoor[motorNum][4][4];
    float maxTravelRange[motorNum];
    //Status receiveFigureAndExe(int motionFigure[6], int modeFlag)
    //SFP---sixFreedomPlatform
    Motor MotSFP;
    MatrixOperation MatirxOpSFP;
    Utility UtilitySFP;
    Trigonometric TriSFP;
    Status returenInstruction = FAILE;
    Status exeMotionByMode1(float motorFigure[motorNum]);//give the motion angle of 6 motor
    Status exeMotionByMode2(float eulerTxFigure[figureNum]);//give the five point algorithm result to move (rotaiton x, rotaiton y, rotaiton z, translation x, translation y, translation z)
    Status exeMotionByMode3();
    Status exeMotionByMode4();
    Status exeMotionByMode9(float eulerTxFigure[figureNum]);//give the panel motion to move
    bool judgeWhetherExeceedWorkSpace(float eulerTxFigure[motorNum]);
    void updatePlatformStatus(float panelMotionEulerTx[figureNum]);

  private:
    
    void fivePointOutput2PanelMotion(float fivePointEulerTx[figureNum], float panelMotionEulerTx[figureNum]);
    
    void calNextBulbBaseCoorFromPanelMotion(float eulerTxFigure[figureNum], float NextBulb_BaseCoor[motorNum][4]);
    
    void calNextBulbMotorCoorFromNextBulbBaseCoor(float NextBulb_BaseCoor[motorNum][4], float NextBulb_MotorCoor[motorNum][4]);
    
    void calNextJointMotorCoorFromNextBulbMotorCoor(float NextBulb_MotorCoor[motorNum][4], float NextJoint_MotorCoor[motorNum][3]);
    
    void calMotorMovingAngleFromNextJointMotorCoor(float NextJoint_BaseCoor[motorNum][3], float motorAngle[motorNum]);
    
    
    void getMotorAngleFromPanelMotion(float eulerTxFigure[figureNum], float motorAngle[motorNum]);
    
    void iniTransformationMatrixCurCoor2BaseCoor();
    
    void iniTransformationMatrixBaseCoor2MotorCoor();
    
    void iniCurJointMotorCoor();
};
#endif
