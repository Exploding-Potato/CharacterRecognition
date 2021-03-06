// Perceptron.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MNISTRead.h"
#include "NeuralNet.h"
#include "Activations.h"
#include "MatToVec.h"


int main()
{
	// Variables used in the program
	int maxExamples = 100;
	int labelsCount = 10;

	// Loads the datasets
	std::vector<short> &trainingLabels = *MNISTReadLabels("MNIST\\train-labels.idx1-ubyte", maxExamples);
	std::vector<arma::Row<short>> &transformedLabels = *MNISTTransformLabels(trainingLabels, 10);
	std::vector<arma::Mat<short>> &trainingImages = *MNISTReadImages("MNIST\\train-images.idx3-ubyte", maxExamples); // Might want to normalize those
	//arma::Row<short> &testLabels;
	//std::vector<arma::Mat<float>> &testImages;

	//// Checking file loading for tha lulz
	//for (int n = 0; n < 100; n++)
	//{
	//	for (int i = 0; i < trainingImages[n].n_rows; i++)
	//	{
	//		std::cout << std::endl;
	//		for (int j = 0; j < trainingImages[n].n_cols; j++)
	//		{
	//			std::cout << trainingImages[n](i, j) / 26 << ' ';
	//		}
	//	}
	//	std::cout << std::endl << trainingLabels[n];
	//}

	NeuralNet net((int) trainingImages[0].n_elem, 100, labelsCount, SigmoidInPlace);

	arma::Row<float> predicted = net.PredictVal(*MatToVec(trainingImages[0]));

	
	system("pause>nul");
    return 0;
}

