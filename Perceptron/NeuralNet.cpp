#include "stdafx.h"
#include "NeuralNet.h"


NeuralNet::NeuralNet(int inputNodes, int hiddenNodes, int outputNodes, void(*activation)(float &)) :
		_inputNodes(inputNodes), _hiddenNodes(hiddenNodes), _outputNodes(outputNodes), _Activation(activation) {
	weights0_1.set_size(hiddenNodes, inputNodes + 1);
	weights1_2.set_size(outputNodes, hiddenNodes + 1);

	weights0_1.randu();
	weights1_2.randu();
}

NeuralNet::~NeuralNet()
{
}

// Predicts the output using the input. Input's size has to be equal to the inputNodes. Also: ugly and inefficient.
arma::Row<float> NeuralNet::PredictVal(arma::Row<short> inputs)
{
	//Adds the bias unit
	arma::Mat<short> inputsPlus = arma::join_horiz(inputs, arma::Row<short>(1).ones());

	// Computes the hidden layer
	arma::Row<float> hidden = inputsPlus * weights0_1.t();
	hidden.for_each(_Activation);

	//Adds the bias unit
	arma::Row<float> hiddenPlus = arma::join_horiz(hidden, arma::Row<float>(1).ones());

	// Computes the output layer 
	arma::Row<float> output = hiddenPlus * weights1_2.t();
	output = output.for_each(_Activation);

	return output;
}
