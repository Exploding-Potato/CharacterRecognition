#include "stdafx.h"
#include "NeuralNet.h"


NeuralNet::NeuralNet(int inputNodes, int hiddenNodes, int outputNodes, float(*activation)(float)) :
		_inputNodes(inputNodes), _hiddenNodes(hiddenNodes), _outputNodes(outputNodes), _Activation(activation) {
	weights0_1.set_size(hiddenNodes, inputNodes);
	weights1_2.set_size(outputNodes, hiddenNodes);

	weights0_1.randu();
	weights1_2.randu();
}

NeuralNet::~NeuralNet()
{
}

// Predicts the output using the input. Input's size has to be equal to the inputNodes
arma::Row<float> NeuralNet::PredictVal(arma::Row<short> inputs)
{
	// Computes the hidden layer
	arma::Row<float> hidden = inputs * weights0_1.t();
	hidden.for_each(_Activation);

	// Computes the output layer 
	arma::Row<float> output = hidden * weights1_2.t();
	output.for_each(_Activation);

	return output;
}
