#include "stdafx.h"

arma::Row<short> *MatToVec(arma::Mat<short> matrix) {
	arma::Row<short> *returnVec = new arma::Row<short>(matrix.n_elem);

	int matrixRows = matrix.n_rows;
	int matrixCols = matrix.n_cols;
	for (int i = 0; i < matrixRows; i++)
	{
		(*returnVec)(arma::span(i * matrixCols, (i + 1) * matrixCols - 1)) = matrix.row(i);
	}

	return returnVec;
}