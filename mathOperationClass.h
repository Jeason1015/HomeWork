#pragma once
#include "math.h"
#include "config.h"


class MatrixOperation
{
public:

	// W=4
	void matrixMul(float A[W][W], float B[W][W], float result[W][W]);   
	void matrixMul(float A[W][W], float B[W], float result[W]);
	void matrixMul(float A[3][3], float B[3], float result[3]);
	void matrixMul(float A[3], float B[3], float &angle);

	void TestMultiplication();
	void EulerTx2Matrix(float rotateX, float rotateY, float rotateZ, float moveX, float moveY, float moveZ, float result[W][W]);
	void TxEuler2Matrix(float rotateX, float rotateY, float rotateZ, float moveX, float moveY, float moveZ, float result[W][W]);


};

class Trigonometric 
{
public:
	float degree2Radian(float angle);
	float sind(float angle);
	float cosd(float angle);
	float asind(float value);
	float acosd(float value);
};

class Utility 
{
public:
	Trigonometric TriUti;
	MatrixOperation MatrixOpUti;
	void calPointInRefCoorFromCurCoorAccordingPanelMotion(float panelMotion[figureNum][W], float bulb_UpPanelCoor[motorNum][W], float bulb_RefCoor[motorNum][W]);
	
	//euler and Rotation Matrix
	void euler2RotationMatrix(float rotateX, float rotateY, float rotateZ, float result[3][3]);
	void rotationMatrix2euler(float RotationMatrix[3][3], float &rotateX, float &rotateY, float &rotateZ);
	
	//R、T and Transformation Matrix
	void RT2TransformationMatrix(float RotationMatrix[3][3], float translationVector[3], float result[W][W]);
	void transformationMatrix2RT(float transformationMatrix[W][W], float RotationMatrix[3][3], float translationVector[3]);
	void motionMatrix2EulerTx(float motionMatrx[W][W], float motionFigure[figureNum]);
	//void txEuler2Matrix(float rotateX, float rotateY, float rotateZ, float moveX, float moveY, float moveZ, float result[W][W]);
		
	//Inverse
	void rotationMatrixInverse(float RotationMatrix[3][3], float result[3][3]);
	void transformationMatrixInverse(float transformationMatrix[W][W], float result[W][W]);
	
	void givenPanelEulerTx2CalMatrixBulbNext2BulbCur(float rotateX, float rotateY, float rotateZ, float moveX, float moveY, float moveZ, float result[W][W]);
	void EulerTx2MatrixBulbNext2BulbCur(float rotateX, float rotateY, float rotateZ, float moveX, float moveY, float moveZ, float result[W][W]);


};
