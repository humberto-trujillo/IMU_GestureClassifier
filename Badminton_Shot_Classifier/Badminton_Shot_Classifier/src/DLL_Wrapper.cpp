#include "ShotClassifier.h"

extern "C" _declspec(dllexport) void* DllNewShotPredict()
{
	return new ShotClassifier;
}

extern "C" _declspec(dllexport) double DllGrtVersion(void* obj)
{
	ShotClassifier *classifier = (ShotClassifier*)obj;
	return classifier->GrtVersion();
}

extern "C" _declspec(dllexport) int DllLoadTrainingData(void* obj, char* filePath)
{
	ShotClassifier *classifier = (ShotClassifier*)obj;
	return classifier->LoadTrainingData(filePath);
}

extern "C" _declspec(dllexport) int DllLoadModelFromFile(void* obj, const char* filePath)
{
	ShotClassifier *classifier = (ShotClassifier*)obj;
	return classifier->LoadModelFromFile(filePath);
}

extern "C" _declspec(dllexport) void DllAddToTimeSeriesBuffer(void* obj, double x, double y, double z)
{
	ShotClassifier *classifier = (ShotClassifier*)obj;
	classifier->AddToTimeSeriesBuffer(x,y,z);
}

extern "C" _declspec(dllexport) void DllGetBufferAsString(void* obj, char* str, int len)
{
	ShotClassifier *classifier = (ShotClassifier*)obj;
	classifier->GetBufferAsString(str, len);
}

extern "C" _declspec(dllexport) int DllPredict(void* obj)
{
	ShotClassifier *classifier = (ShotClassifier*)obj;
	return (int)classifier->Predict();
}
