#include "TiltClassifier.h"
#define TiltClassifierAPI _declspec(dllexport)

//extern "C" TiltClassifierAPI void* NewTiltClassifier()
//{
//	return new TiltClassifier;
//}
//
//extern "C" TiltClassifierAPI void DeleteClassifier(void* obj)
//{
//	delete(obj);
//}

extern "C" TiltClassifierAPI double GrtVersion()
{
	return atof(GRT::GRTBase::getGRTVersion().c_str());
}
extern "C" TiltClassifierAPI int PredictTilt(const char* modelFilePath,double x, double y, double z)
{
	//Create a new SVM classifier with a linear kernel
	//Other kernel options you could choose are: POLY_KERNEL, RBF_KERNEL, SIGMOID_KERNEL, PRECOMPUTED_KERNEL
	GRT::SVM svm(GRT::SVM::LINEAR_KERNEL);

	//The SVM will typically work much better if we scale the training and prediction data, so turn scaling on
	svm.enableScaling(true);

	//Load the knn model from a file
	bool loadSuccess = svm.loadModelFromFile(modelFilePath);

	if (!loadSuccess) {
		//std::cout << "Failed to load the classifier model!\n";
		return -1;
	}
	GRT::VectorDouble v(3);
	v[0] = x;
	v[1] = y;
	v[2] = z;
	//Perform a prediction using the classifier
	bool predictSuccess = svm.predict(v);

	if (!predictSuccess) {
		//cout << "Failed to perform prediction for test sampel: " << i << "\n";
		return -1;
	}
	return svm.getPredictedClassLabel();;
}