#include "stdafx.h"
#include "Activations.h"

float Sigmoid(float x)
{
	float e = exp(x);
	return e / (e + 1);
}
