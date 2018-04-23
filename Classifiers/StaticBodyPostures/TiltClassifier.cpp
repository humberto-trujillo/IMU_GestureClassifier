#include "TiltClassifier.h"
#include <stdlib.h>

TiltClassifier::TiltClassifier()
{

}

TiltClassifier::~TiltClassifier()
{

}

double TiltClassifier::GrtVersion()
{
	return atof(GRT::GRTBase::getGRTVersion().c_str());
}