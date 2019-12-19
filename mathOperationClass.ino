//#include "StdAfx.h"
//#include "stdafx.h"
#include "mathOperationClass.h"
#include "config.h"
//#include<iomanip>
//#include<iostream>


using namespace std;

#pragma region 
void MatrixOperation::matrixMul(float A[W][W], float B[W][W], float result[W][W])
{
	int i, j, k;
	for (i = 0; i<W; i++)
	{
		for (j = 0; j<W; j++)
		{
			result[i][j] = 0;
			for (k = 0; k<W; k++)
				result[i][j] += A[i][k] * B[k][j];
		}
	}
}
void MatrixOperation::matrixMul(float A[W][W], float B[W], float result[W])
{
	int i, j;
	for (i = 0; i<W; i++)
	{
		result[i] = 0;
		for (j = 0; j<W; j++)
		{
			result[i] += A[i][j] * B[j];
		}
	}
}
void MatrixOperation::matrixMul(float A[3][3], float B[3], float result[3])
{
	int i, j;
	for (i = 0; i<3; i++)
	{
		result[i] = 0;
		for (j = 0; j<3; j++)
		{
			result[i] += A[i][j] * B[j];
		}
	}

	//testByMC
	// for (int i = 0; i< 3; i++)
	// {
	// 	printf("%.2f ",result[i]);
	// }
	// printf("\n");
}
void MatrixOperation::matrixMul(float A[3], float B[3], float &angle)
{
	angle = A[0] * B[0] + A[1] * B[1] + A[2] * B[2];
}
void MatrixOperation::TestMultiplication()
{
	float a[4][4] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
	float b[4][4] = { 3, 5, 6, 3, 2, 1, 1, 4, 6, 4, 8, 34, 43, 6, 4, 2 };
	float result[4][4];
	this->matrixMul(a, b, result);

	//testByMC
	//for (int i = 0;i<4;i++)
	//for(int j = 0;j<4;j++)
	//printf("%.2f ", result[i][j];
}
#pragma endregion

#pragma region 
float Trigonometric::degree2Radian(float angle)
{
	float result;
	float pi = acos(-1.0);
	float coefficient = pi / 180.0;
	result = coefficient*angle;
	return result;
}
float Trigonometric::sind(float angle)
{
	float pi = acos(-1.0);
	float coefficient = pi / 180.0;
	return sin(coefficient * angle);
}
float Trigonometric::cosd(float angle)
{
	float pi = acos(-1.0);
	float coefficient = pi / 180.0;
	return cos(coefficient * angle);
}
float Trigonometric::asind(float value)
{
	float pi = acos(-1.0);
	return asin(value) * 180.0 / pi;
}
float Trigonometric::acosd(float value)
{
	float pi = acos(-1.0);
	return acos(value) * 180.0 / pi;
}
#pragma endregion
//#pragma region 閿熸枻鎷烽敓瑙掔尨鎷烽敓鏂ゆ嫹
//float Trigonometric::sind(float angle)
//{
//  float pi = acos(-1.0);
//  float coefficient = pi / 180.0;
//  return sin(coefficient * angle);
//}
//
//float Trigonometric::cosd(float angle)
//{
//  float pi = acos(-1.0);
//  float coefficient = pi / 180.0;
//  return cos(coefficient * angle);
//}
//
//float Trigonometric::asind(float value)
//{
//  float pi = acos(-1.0);
//  return asin(value) * 180.0 / pi;
//}
//
//float Trigonometric::acosd(float value)
//{
//  float pi = acos(-1.0);
//  return acos(value) * 180.0 / pi;
//}
//#pragma endregion

#pragma region 
void Utility::euler2RotationMatrix(float rotateX, float rotateY, float rotateZ, float result[3][3])
{
	float omega = TriUti.degree2Radian(rotateX);
	float phy = TriUti.degree2Radian(rotateY);
	float kappa = TriUti.degree2Radian(rotateZ);

	result[0][0] = cos(phy)*cos(kappa);
	result[0][1] = cos(omega)*sin(kappa) + sin(omega)*sin(phy)*cos(kappa);
	result[0][2] = sin(omega)*sin(kappa) - cos(omega)*sin(phy)*cos(kappa);

	result[1][0] = -cos(phy)*sin(kappa);
	result[1][1] = cos(omega)*cos(kappa) - sin(omega)*sin(phy)*sin(kappa);
	result[1][2] = sin(omega)*cos(kappa) + cos(omega)*sin(phy)*sin(kappa);

	result[2][0] = sin(phy);
	result[2][1] = -sin(omega)*cos(phy);
	result[2][2] = cos(omega)*cos(phy);
}

void Utility::rotationMatrix2euler(float RotationMatrix[3][3], float &rotateX, float &rotateY, float &rotateZ)
{
	rotateY = TriUti.asind(RotationMatrix[2][0]);
	rotateX = TriUti.asind(-RotationMatrix[2][1] / TriUti.cosd(rotateY));
	rotateZ = TriUti.acosd(RotationMatrix[0][0] / TriUti.cosd(rotateY));
}

void Utility::RT2TransformationMatrix(float RotationMatrix[3][3], float translationVector[3], float result[W][W])
{
	result[0][0] = RotationMatrix[0][0];
	result[0][1] = RotationMatrix[0][1];
	result[0][2] = RotationMatrix[0][2];

	result[1][0] = RotationMatrix[1][0];
	result[1][1] = RotationMatrix[1][1];
	result[1][2] = RotationMatrix[1][2];

	result[2][0] = RotationMatrix[2][0];
	result[2][1] = RotationMatrix[2][1];
	result[2][2] = RotationMatrix[2][2];

	result[0][3] = translationVector[0];//moveX
	result[1][3] = translationVector[1];//moveY
	result[2][3] = translationVector[2];//moveZ

	result[3][0] = 0;
	result[3][1] = 0;
	result[3][2] = 0;
	result[3][3] = 1;
}

void Utility::transformationMatrix2RT(float transformationMatrix[W][W], float RotationMatrix[3][3], float translationVector[3])
{
	RotationMatrix[0][0] = transformationMatrix[0][0];
	RotationMatrix[0][1] = transformationMatrix[0][1];
	RotationMatrix[0][2] = transformationMatrix[0][2];

	RotationMatrix[1][0] = transformationMatrix[1][0];
	RotationMatrix[1][1] = transformationMatrix[1][1];
	RotationMatrix[1][2] = transformationMatrix[1][2];

	RotationMatrix[2][0] = transformationMatrix[2][0];
	RotationMatrix[2][1] = transformationMatrix[2][1];
	RotationMatrix[2][2] = transformationMatrix[2][2];

	translationVector[0] = transformationMatrix[0][3];
	translationVector[1] = transformationMatrix[1][3];
	translationVector[2] = transformationMatrix[2][3];
}

void Utility::motionMatrix2EulerTx(float motionMatrx[W][W], float motionFigure[figureNum])
{
	float RotationMatrix[3][3];
	float translationVector[3];
	transformationMatrix2RT(motionMatrx, RotationMatrix, translationVector);
	rotationMatrix2euler(RotationMatrix, motionFigure[0], motionFigure[1], motionFigure[2]);
	motionFigure[3] = translationVector[0];
	motionFigure[4] = translationVector[1];
	motionFigure[5] = translationVector[2];
}

//void Utility::txEuler2Matrix(float rotateX, float rotateY, float rotateZ, float moveX, float moveY, float moveZ, float result[W][W])
//{}

void Utility::rotationMatrixInverse(float RotationMatrix[3][3], float result[3][3])
{
	result[0][0] = RotationMatrix[0][0];
	result[0][1] = RotationMatrix[1][0];
	result[0][2] = RotationMatrix[2][0];

	result[1][0] = RotationMatrix[0][1];
	result[1][1] = RotationMatrix[1][1];
	result[1][2] = RotationMatrix[2][1];

	result[2][0] = RotationMatrix[0][2];
	result[2][1] = RotationMatrix[1][2];
	result[2][2] = RotationMatrix[2][2];
}

void Utility::transformationMatrixInverse(float transformationMatrix[W][W], float result[W][W])
{
	float rotationMatrix[3][3];
	float translationVector[3];//t
	float rotationMatrixInv[3][3];
	float translationForInv[3];
	float minusTranslationVector[3];
	transformationMatrix2RT(transformationMatrix, rotationMatrix, translationVector);
	for (int i = 0; i < 3; i++)
	{
		minusTranslationVector[i] = -translationVector[i];//-t
	}
	rotationMatrixInverse(rotationMatrix, rotationMatrixInv);
	MatrixOpUti.matrixMul(rotationMatrixInv, minusTranslationVector, translationForInv);
	RT2TransformationMatrix(rotationMatrixInv, translationForInv, result);
}

void Utility::panelEulerTx2MatrixBulbNext2BulbCur(float rotateX, float rotateY, float rotateZ, float moveX, float moveY, float moveZ, float result[W][W])
{
	float rotationMatrix[3][3];
	float translationVector[3];//-t
	float middleTranMatrix[W][W];

	translationVector[0] = -moveX;
	translationVector[1] = -moveY;
	translationVector[2] = -moveZ;

	euler2RotationMatrix(rotateX, rotateY, rotateZ, rotationMatrix);//R
	RT2TransformationMatrix(rotationMatrix, translationVector, middleTranMatrix);//[R,-t] Pnext=result*Pcur
	transformationMatrixInverse(middleTranMatrix, result);// [R, -t]
}

void Utility::EulerTx2MatrixBulbNext2BulbCur(float rotateX, float rotateY, float rotateZ, float moveX, float moveY, float moveZ, float result[W][W])
{
	float rotationMatrix[3][3];
	float translationVector[3];//-t

	translationVector[0] = -moveX;
	translationVector[1] = -moveY;
	translationVector[2] = -moveZ;

	euler2RotationMatrix(rotateX, rotateY, rotateZ, rotationMatrix);//R
	RT2TransformationMatrix(rotationMatrix, translationVector, result);//[R,-t] Pnext=result*Pcur
}
#pragma endregion
