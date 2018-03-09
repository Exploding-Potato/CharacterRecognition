#pragma once
class NeuralNet
{
	int _inputNodes, _hiddenNodes, _outputNodes;
	arma::Mat<float> weights0_1;
	arma::Mat<float> weights1_2;

	float(*_Activation)(float);

public:
	NeuralNet(int inputNodes, int hiddenNodes, int outputNodes, float(*activation)(float));
	~NeuralNet();

	// It should probably work on const references or sth in the future
	arma::Row<float> PredictVal(arma::Row<short> inputs);
};

