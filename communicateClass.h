#ifndef _COMMUNICATE_H_
#define _COMMUNICATE_H_
#include "config.h"

//data---10023000
//figure---2.3

class Communication
{
public:
	Communication(void);
	~Communication(void);
	int data[maxDataLength];   
	int datalength;
	int modeFlag;    
	float figure[figureNum];  
	void readDataFromUART(int data[maxDataLength], int &datalength);
	float getFigureFromData(int data[maxDataLength], int startIndex); 

	
    void swap(float &a, float &b);
	void parseMode1(int data[maxDataLength], float motorAngle[motorNum]);    
	void parseMode2(int data[maxDataLength], float motionEulerTx[figureNum]); 

	void readUartAndParseFigure(int data[maxDataLength], float figure[figureNum], int &modeFlag, int &datalength);
	void getDataFromFigure(float inputFigure[6], int figurenumber, int data[50], int &datalength);   

};
#endif
