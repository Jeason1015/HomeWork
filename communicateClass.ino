#include "communicateClass.h"

Communication::Communication(){}
Communication::~Communication(){}

void  Communication::readUartAndParseFigure(int data[maxDataLength], float figure[figureNum], int &modeFlag, int &datalength)
{
	Communication::readDataFromUART(data, datalength);
	modeFlag = data[0]; 
	if (modeFlag == 1)
	parseMode1(data, figure); 
	if (modeFlag == 2)
	parseMode2(data, figure);
	if (modeFlag == 9)
	parseMode1(data, figure);
	//Serial.print("#");
	/*for (int i = 0; i<6; i++)
	{
		Serial.print(figure[i]);
		Serial.print(",");
	}*/
	//Serial.println("%");
}

void Communication::readDataFromUART(int data[maxDataLength], int &datalength)
{
	while (true)
	{
		bool havefinishread = false;
		int dataindex = 0;
		int maxindex = maxDataLength - 1;
		while (Serial.available() == 0) {};
		char start = Serial.read();
		if (start != '#'){
			continue;
		}
		while (true){
			while (Serial.available() == 0) {};
			char temp = Serial.read();
			if (temp == '%'){
				havefinishread = true;
				datalength = dataindex;
				break;
			}
			else { 
				data[dataindex] = temp - '0';
				dataindex += 1;
			}
			if (dataindex > maxindex) 
				break;
		}
		if (havefinishread)
			break;
	}
}

float Communication::getFigureFromData(int data[maxDataLength], int startindex)
{
	int signindex = startindex;
	int sign = data[signindex];
	int integerindex = signindex + 1;
	int fractionalindex = integerindex + 3;
	float integer = data[integerindex] * 100.0 + data[integerindex + 1] * 10.0 + data[integerindex + 2];
	float fractional = data[fractionalindex] / 10.0 + data[fractionalindex + 1] / 100.0 + data[fractionalindex + 2] / 1000.0;
	float number = integer + fractional;
	if (sign == 1)
		return number;
	else
		return -number;
}

void Communication::swap(float &a, float &b)
{
  float tmp=0;
  tmp=b;
  b=a;
  a=tmp;
}

void  Communication::parseMode1(int data[maxDataLength], float motorAngle[motorNum])
{
	for (int i = 0; i < 6; i++){
		int startindex = i * 7 + 1;
		figure[i] = getFigureFromData(data, startindex);
	}
 //swap(figure[0],figure[1]);
 //swap(figure[1],figure[2]);
 //swap(figure[3],figure[4]);
 //swap(figure[4],figure[5]);
}

void  Communication::parseMode2(int data[maxDataLength], float motionEulerTx[figureNum])
{
    for (int i = 0; i < 6; i++){
    int startindex = i * 7 + 2;
    figure[i] = getFigureFromData(data, startindex);
    }
  
    swap(figure[0],figure[1]);
    swap(figure[1],figure[2]);
    swap(figure[3],figure[4]);
    swap(figure[4],figure[5]);
  
	
}


