#pragma once
class NeuralNet
{
	int _inputNodes, _hiddenNodes, _outputNodes;
	arma::Mat<float> weights0_1;
	arma::Mat<float> weights1_2;

	void (*_Activation)(float &);

public:
	NeuralNet(int inputNodes, int hiddenNodes, int outputNodes, void(*_Activation)(float &));
	~NeuralNet();

	// It should probably work on const references or sth in the future
	arma::Row<float> PredictVal(arma::Row<short> inputs);
};

