#include <stdio.h> 
#include <tchar.h> 
#include <iostream> 
#include <windows.h> 
#include <algorithm> 
#define _USE_MATH_DEFINES 
#include <math.h> 
using namespace std; 


// 高斯分布随机数系列,默认期望值为0,方差为1
double GaussRand(double dExpect = 0, double dVariance = 1);
double GaussRand(double dExpect, double dVariance)
{
	static double V1, V2, S;
	static int phase = 0;
	double X;

	if ( phase == 0 )
	{
		do
		{
			double U1 = (double)rand() / RAND_MAX;
			double U2 = (double)rand() / RAND_MAX;

			V1 = 2 * U1 - 1;
			V2 = 2 * U2 - 1;
			S = V1 * V1 + V2 * V2;
		} while(S >= 1 || S == 0);

		X = V1 * sqrt(-2 * log(S) / S);
	}
	else
	{
		X = V2 * sqrt(-2 * log(S) / S);
	}

	phase = 1 - phase;

	return (X*dVariance + dExpect);
}

int _tmain(int argc, _TCHAR* argv[]) 
{ 
	const int DATA_CNT = 100000; 
	double dArrData[DATA_CNT] = {0}; 

	double dSum = 0; 

	// 对全部数赋随机数,默认期望值为0,方差为1
	
	srand(GetTickCount()); 
	for (int nIdx = 0; nIdx < DATA_CNT; nIdx++) 
	{ 
		// 防止计算方差时数值过大 
		
		dArrData[nIdx] = GaussRand(); 
		dSum += dArrData[nIdx]; 
	} 
	// 求平均数 

	double dAverageData = dSum / DATA_CNT; 
	// 计算全部的数的方差(各个数据分别与其和的平均数之差的平方的和的平均数) 
	
	double dVariance = 0.0; 
	for (int nIdx = 0; nIdx < DATA_CNT; nIdx++) 
	{ 
		double dDeviate = dArrData[nIdx] - dAverageData; 
		dVariance += pow(dDeviate, 2); 
	} 
	dVariance /= DATA_CNT; 
	// 计算标准差(方差的算术平方根,反映一组数据的离散程序) 
	
	double dStandardDeviation = sqrt(dVariance); 
	// 计算0.5个正负标准差之间包括的数字个数 
	
	int nDataCnt = 0; 
	for (int nIdx = 0; nIdx < DATA_CNT; nIdx++) 
	{ 
		double dDeviate = dArrData[nIdx] - dAverageData; 
		if (abs(dDeviate) <= 0.5*dStandardDeviation) 
		{ 
			nDataCnt++; 
		} 
	} 
	cout<<nDataCnt<<endl; 

	// 计算1个正负标准差之间包括的数字个数 
	nDataCnt = 0;
	for (int nIdx = 0; nIdx < DATA_CNT; nIdx++) 
	{ 
		double dDeviate = dArrData[nIdx] - dAverageData; 
		if (abs(dDeviate) <= dStandardDeviation) 
		{ 
			nDataCnt++; 
		} 
	} 
	cout<<nDataCnt<<endl; 

	// 计算2个正负标准差之间包括的数字个数 
	nDataCnt = 0;
	for (int nIdx = 0; nIdx < DATA_CNT; nIdx++) 
	{ 
		double dDeviate = dArrData[nIdx] - dAverageData; 
		if (abs(dDeviate) <= 2*dStandardDeviation) 
		{ 
			nDataCnt++; 
		} 
	} 
	cout<<nDataCnt<<endl; 

	// 计算3个正负标准差之间包括的数字个数 
	nDataCnt = 0;
	for (int nIdx = 0; nIdx < DATA_CNT; nIdx++) 
	{ 
		double dDeviate = dArrData[nIdx] - dAverageData; 
		if (abs(dDeviate) <= 3*dStandardDeviation) 
		{ 
			nDataCnt++; 
		} 
	} 
	cout<<nDataCnt<<endl; 
	getchar()；
	return 0; 
} 
