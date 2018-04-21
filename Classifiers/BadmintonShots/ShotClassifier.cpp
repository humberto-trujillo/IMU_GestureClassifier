#include "ShotClassifier.h"
#include <stdlib.h>

ShotClassifier::ShotClassifier()
{
	dtw.enableNullRejection(true);
	timeSeriesBuffer.resize(75);
}

ShotClassifier::~ShotClassifier()
{
	//nothing to deallocate
}

double ShotClassifier::GrtVersion()
{
	return atof(GRTBase::getGRTVersion().c_str());
}

int ShotClassifier::LoadTrainingData(char* filePath)
{
	return trainingData.load(std::string(filePath));
}

int ShotClassifier::LoadModelFromFile(const char* filePath)
{
	return dtw.loadModelFromFile(filePath);
}

void ShotClassifier::AddToTimeSeriesBuffer(double x, double y, double z)
{
	VectorDouble v(3);
	v[0] = x;
	v[1] = y;
	v[2] = z;
	timeSeriesBuffer.push_back(v);
}

void ShotClassifier::GetBufferAsString(char *str, int len)
{
	string buffer = "TimeSeries\n";
	MatrixDouble timeseries = timeSeriesBuffer.getData();
	for (UINT i = 0; i < timeseries.getNumRows(); i++)
	{
		buffer += to_string(timeseries[i][0]) + ", "+ to_string(timeseries[i][1]) + ", " + to_string(timeseries[i][2]) + "\n";
	}
	strcpy(str,buffer.c_str());
}

int ShotClassifier::Predict()
{
	MatrixDouble timeseries = timeSeriesBuffer.getData();
	if (!dtw.predict(timeseries))
	{
		return -1;
	}
	return dtw.getPredictedClassLabel();
}
