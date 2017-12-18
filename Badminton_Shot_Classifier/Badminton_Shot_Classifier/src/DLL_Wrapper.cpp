#include "ShotClassifier.h"
#define ShotClassifierAPI _declspec(dllexport)

extern "C" ShotClassifierAPI void* NewShotClassifier()
{
	return new ShotClassifier;
}

extern "C" ShotClassifierAPI double GrtVersion(void* obj)
{
	ShotClassifier *classifier = (ShotClassifier*)obj;
	return classifier->GrtVersion();
}

extern "C" ShotClassifierAPI int LoadTrainingData(void* obj, char* filePath)
{
	ShotClassifier *classifier = (ShotClassifier*)obj;
	return classifier->LoadTrainingData(filePath);
}

extern "C" ShotClassifierAPI int LoadModelFromFile(void* obj, const char* filePath)
{
	ShotClassifier *classifier = (ShotClassifier*)obj;
	return classifier->LoadModelFromFile(filePath);
}

extern "C" ShotClassifierAPI void AddToTimeSeriesBuffer(void* obj, double x, double y, double z)
{
	ShotClassifier *classifier = (ShotClassifier*)obj;
	classifier->AddToTimeSeriesBuffer(x,y,z);
}

extern "C" ShotClassifierAPI void GetBufferAsString(void* obj, char* str, int len)
{
	ShotClassifier *classifier = (ShotClassifier*)obj;
	classifier->GetBufferAsString(str, len);
}

extern "C" ShotClassifierAPI int Predict(void* obj)
{
	ShotClassifier *classifier = (ShotClassifier*)obj;
	return (int)classifier->Predict();
}
