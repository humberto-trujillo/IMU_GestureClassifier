#include "TiltClassifier.h"
#define TiltClassifierAPI _declspec(dllexport)

//extern "C" TiltClassifierAPI void* NewShotClassifier()
//{
//	return new TiltClassifier;
//}
//
//extern "C" TiltClassifierAPI double GrtVersion(void* obj)
//{
//	TiltClassifier *classifier = (TiltClassifier*)obj;
//	return classifier->GrtVersion();
//}

extern "C" TiltClassifierAPI double GrtVersion()
{
	return atof(GRT::GRTBase::getGRTVersion().c_str());
}

extern "C" TiltClassifierAPI int DLLSUM(int a, int b)
{
	return a+b;
}