/*
Demonstrates how to initialize, train, and use the DTW algorithm for classification.

The Dynamic Time Warping (DTW) algorithm is a powerful classifier that works very well for recognizing temporal gestures.

In this example we create an instance of an DTW algorithm and then train the algorithm using some pre-recorded training data.
The trained DTW algorithm is then used to predict the class label of some test data.

This example shows you how to:
- Create an initialize the DTW algorithm
- Load some LabelledTimeSeriesClassificationData from a file and partition the training data into a training dataset and a test dataset
- Trim any periods of non-movement from the start and end of each timeseries recording
- Train the DTW algorithm using the training dataset
- Test the DTW algorithm using the test dataset
- Manually compute the accuracy of the classifier
*/

#include "GRT/GRT.h"
using namespace GRT;
using namespace std;

int main(int argc, const char * argv[])
{
	//Parse the training data filename from the command line
	if (argc != 2) {
		cout << "Error: failed to parse data filename from command line. ";
		cout << "You should run this example with one argument pointing to a data file\n";
		return EXIT_FAILURE;
	}
	const string filename = argv[1];

	//Create a new DTW instance, using the default parameters
	DTW dtw;

	dtw.enableNullRejection(true);

	dtw.setNullRejectionCoeff(2.7);

	dtw.setOffsetTimeseriesUsingFirstSample(true);

	//Load some training data to train the classifier - the DTW uses LabelledTimeSeriesClassificationData
	LabelledTimeSeriesClassificationData trainingData;
	//"c:\\Users\\Humberto\\Documents\\Repositories\\Github\\Badminton_Shot_Classifier\\Badminton_Shot_Classifier\\Badminton_Shot_Classifier\\data\\BadmintonStrokes.grt"
	if (!trainingData.loadDatasetFromFile(filename)) {
		cout << "Failed to load training data!\n";
		cin.get();
		return EXIT_FAILURE;
	}

	//Use 20% of the training dataset to create a test dataset
	LabelledTimeSeriesClassificationData testData = trainingData.partition(80);

	//Trim the training data for any sections of non-movement at the start or end of the recordings
	dtw.enableTrimTrainingData(true, 0.1, 90);

	//Train the classifier
	if (!dtw.train(trainingData)) {
		cout << "Failed to train classifier!\n";
		cin.get();
		return EXIT_FAILURE;
	}

	//Save the DTW model to a file
	if (!dtw.saveModelToFile("DTWModel.txt")) {
		cout << "Failed to save the classifier model!\n";
		cin.get();
		return EXIT_FAILURE;
	}

	//Load the DTW model from a file
	if (!dtw.loadModelFromFile("DTWModel.txt")) {
		cout << "Failed to load the classifier model!\n";
		cin.get();
		return EXIT_FAILURE;
	}

	//Use the test dataset to test the DTW model
	double accuracy = 0;
	for (UINT i = 0; i<testData.getNumSamples(); i++) {
		//Get the i'th test sample - this is a timeseries
		UINT classLabel = testData[i].getClassLabel();
		MatrixDouble timeseries = testData[i].getData();

		//Perform a prediction using the classifier
		if (!dtw.predict(timeseries)) {
			cout << "Failed to perform prediction for test sampel: " << i << "\n";
			cin.get();
			return EXIT_FAILURE;
		}

		//Get the predicted class label
		UINT predictedClassLabel = dtw.getPredictedClassLabel();
		double maximumLikelihood = dtw.getMaximumLikelihood();
		VectorDouble classLikelihoods = dtw.getClassLikelihoods();
		VectorDouble classDistances = dtw.getClassDistances();

		//Update the accuracy
		if (classLabel == predictedClassLabel) accuracy++;

		cout << "TestSample: " << i << "\tClassLabel: " << classLabel << "\tPredictedClassLabel: " << predictedClassLabel << "\tMaximumLikelihood: " << maximumLikelihood << endl;
	}

	cout << "Test Accuracy: " << accuracy / double(testData.getNumSamples())*100.0 << "%" << endl;
	cin.get();
	return EXIT_SUCCESS;
}
