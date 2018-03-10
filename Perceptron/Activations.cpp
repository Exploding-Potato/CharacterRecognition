#include "stdafx.h"
#include "Activations.h"

float Sigmoid(float x)
{
	return 1 / (1 + exp(-x));
}

void SigmoidInPlace(float &x)
{
	x = 1 / (1 + exp(-x));
}