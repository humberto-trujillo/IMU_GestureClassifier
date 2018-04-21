/*
GRT SVM Example
This examples demonstrates how to initialize, train, and use the SVM algorithm for classification.

The Support Vector Machine (SVM) classifier is a powerful classifier that works well on a wide range of classification problems, even problems in high dimensions and that are not linearly separable.

In this example we create an instance of a SVM algorithm and then train the algorithm using some pre-recorded training data.
The trained SVM algorithm is then used to predict the class label of some test data.

This example shows you how to:
- Create an initialize the SVM algorithm using a LINEAR kernel
- Load some ClassificationData from a file and partition the training data into a training dataset and a test dataset
- Train the SVM algorithm using the training dataset
- Test the SVM algorithm using the test dataset
- Manually compute the accuracy of the classifier
*/

//You might need to set the specific path of the GRT header relative to your project
#include "GRT/GRT.h"
using namespace GRT;

int main(int argc, const char * argv[])
{
	//Create a new SVM classifier with a linear kernel
	//Other kernel options you could choose are: POLY_KERNEL, RBF_KERNEL, SIGMOID_KERNEL, PRECOMPUTED_KERNEL
	SVM svm(SVM::LINEAR_KERNEL);

	//The SVM will typically work much better if we scale the training and prediction data, so turn scaling on
	svm.enableScaling(true);

	//Train the classifier with some training data
	ClassificationData trainingData;

	if (!trainingData.loadDatasetFromFile("data/SVMTrainingData.txt")) {
		std::cout << "Failed to load training data!\n";
		std::getchar();
		return EXIT_FAILURE;
	}

	//Use 20% of the training dataset to create a test dataset
	ClassificationData testData = trainingData.partition(80);

	//Train the classifier
	if (!svm.train(trainingData)) {
		std::cout << "Failed to train classifier!\n";
		std::getchar();
		return EXIT_FAILURE;
	}

	//Save the svm model to a file
	if (!svm.saveModelToFile("SVMModel.txt")) {
		std::cout << "Failed to save the classifier model!\n";
		std::getchar();
		return EXIT_FAILURE;
	}

	//Load the knn model from a file
	if (!svm.loadModelFromFile("SVMModel.txt")) {
		std::cout << "Failed to load the classifier model!\n";
		std::getchar();
		return EXIT_FAILURE;
	}

	//Use the test dataset to test the SVM model
	double accuracy = 0;
	for (UINT i = 0; i<testData.getNumSamples(); i++) {
		//Get the i'th test sample
		UINT classLabel = testData[i].getClassLabel();
		VectorFloat inputVector = testData[i].getSample();

		//Perform a prediction using the classifier
		bool predictSuccess = svm.predict(inputVector);
		if (!predictSuccess) {
			std::cout << "Failed to perform prediction for test sampel: " << i << "\n";
			std::getchar();
			return EXIT_FAILURE;
		}

		//Get the predicted class label
		UINT predictedClassLabel = svm.getPredictedClassLabel();
		std::vector< double > classLikelihoods = svm.getClassLikelihoods();
		std::vector< double > classDistances = svm.getClassDistances();

		//Update the accuracy
		if (classLabel == predictedClassLabel) accuracy++;

		std::cout << "TestSample: " << i << " ClassLabel: " << classLabel << " PredictedClassLabel: " << predictedClassLabel << std::endl;
	}

	std::cout << "Test Accuracy: " << accuracy / double(testData.getNumSamples())*100.0 << "%" << std::endl;
	std::getchar();
	return EXIT_SUCCESS;
}