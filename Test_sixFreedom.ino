#include "stdio.h"
#include "config.h"
#include "Test_sixFreedom.h"
#include "CommunicateClass.h"
SixFreedomPlatform SixFreedom(sPin_in, dPin_in, longArm_in, shortArm_in, stepAngleOri_in, subdividing_in,
  bulb_UpPanelCoor_in, motor_baseCoor_in, MotorAngle_Cur_in,
  curPosition_in, maxTravelRange_in, Height_upPanel2BasePanel_in, zeroHeight_in);
class Communication COMM;

void setup() {
  Serial.begin(9600);
  for (int i = 0; i<6; i++)
  {
    pinMode(SixFreedom.sPin[i], OUTPUT);  
    pinMode(SixFreedom.dPin[i], OUTPUT);   
  }
}

void loop()
{
  COMM.readUartAndParseFigure(COMM.data, COMM.figure, COMM.modeFlag, COMM.datalength);
   /*Serial.print("flag: ");
  Serial.println(COMM.modeFlag);
   Serial.print("figure 1: ");
  Serial.println(COMM.figure[0]);
  Serial.print("figure 2: ");
  Serial.println(COMM.figure[1]);
  Serial.print("figure 3: ");
  Serial.println(COMM.figure[2]);
  Serial.print("figure 4: ");
  Serial.println(COMM.figure[3]);
  Serial.print("figure 5: ");
  Serial.println(COMM.figure[4]);
  Serial.print("figure 6: ");
  Serial.println(COMM.figure[5]);*/
  if (COMM.modeFlag == 1)
  {
    SixFreedom.returenInstruction=SixFreedom.exeMotionByMode1(COMM.figure);
  }
  else if (COMM.modeFlag == 2)
  {
    //SixFreedom.exeMotionByMode2(COMM.figure);
    SixFreedom.returenInstruction=SixFreedom.exeMotionByMode9(COMM.figure);
  }
    else if (COMM.modeFlag == 5)
  {
    SixFreedom.returenInstruction=SixFreedom.exeMotionByMode4();
  }
  else if (COMM.modeFlag == 4)
  {
    for(int i=0;i<6;i++)
    {
      SixFreedom.curPosition[i] = curPosition_in[i];
    }
    
  }
  else if (COMM.modeFlag == 9)
  {
    SixFreedom.returenInstruction=SixFreedom.exeMotionByMode9(COMM.figure);
    /*
    for (int i=0;i<6;i++)
    {
      Serial.println("################################");
      Serial.print("i=");
      Serial.println(i);
      
      Serial.println(SixFreedom.curPosition[i]);
      Serial.println("################################");
    }
    */
  }

  //return Instruction
  if (SixFreedom.returenInstruction==SUCCESS)
  {
    Serial.println("#1%");
  }
  else if (SixFreedom.returenInstruction==FAILE)
  {
    Serial.println("#0%");
  }
  

}
