#pragma once
#include "GRT/GRT.h"
using namespace GRT;
using namespace std;

class __declspec(dllexport) ShotClassifier
{
public:
	ShotClassifier();
	~ShotClassifier();
	double GrtVersion();
	int LoadTrainingData(char* filePath);
	int LoadModelFromFile(const char* filePath);
	void AddToTimeSeriesBuffer(double x, double y, double z);
	void GetBufferAsString(char *str, int len);
	int Predict();
private:
	DTW dtw;
	//Load some training data to train the classifier - the DTW uses LabelledTimeSeriesClassificationData
	LabelledTimeSeriesClassificationData trainingData;
	CircularBuffer<VectorDouble> timeSeriesBuffer;
};
