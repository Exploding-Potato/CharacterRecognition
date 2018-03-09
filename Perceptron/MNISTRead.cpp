#include "stdafx.h"
#include "MNISTRead.h"
#include <fstream>

int32_t FourCharsToIntBigEndian(unsigned char *chars) {
	return 16777216 * chars[0] + 65536 * chars[1] + 256 * chars[2] + chars[3];
}

arma::Row<short> *MNISTReadLabels(std::string filePath, int32_t maxExamples)
{
	// Initializes the values used in the function
	arma::Row<short> *returnRow;
	int32_t exampleCount;

	// Opens the file stream
	std::ifstream stream;
	stream.open(filePath, std::ios::in | std::ios::binary);

	// Checks the magic number for some dumb reason. It's supposed to be (int)2049 or (hex)801. Also, it's written in big endian, but that matters only in a few reads per file;
	unsigned char temp[4];
	stream.read((char *)temp, 4);
	if (FourCharsToIntBigEndian(temp) != 2049) {
		throw std::runtime_error("Found a problem in the magic number in the file. The data at " + filePath + " might be corrupted.");
	}

	// Reads the number of examples and checks against the maxExamples. Also, it's written in big endian, but that matters only in a few reads per file;
	stream.read((char *)temp, 4);
	exampleCount = std::min(FourCharsToIntBigEndian(temp), maxExamples);

	// Initializes the returnRow with the correct number of values
	returnRow = new arma::Row<short>(exampleCount);

	// Dumb, but don't have an idea how to make it work on all numbers of labels
	unsigned char *buffer = new unsigned char();

	// This could possibly be optimized by reading bigger chunks of data at the same time
	// Load the file, into the returnRow, in chunks of 1 byte
	for (int i = 0; i < exampleCount; i++)
	{
		stream.read((char *)buffer, 1);
		(*returnRow)(i) = (short)(*buffer);
	}

	return returnRow;
}

std::vector<arma::Mat<short>> *MNISTReadImages(std::string filePath, int32_t maxExamples)
{
	// Initializes the values used in the function
	std::vector<arma::Mat<short>> *returnVec;
	int32_t exampleCount;
	int32_t rowCount;
	int32_t columnCount;
	int32_t pixelCount;

	// Opens the file stream
	std::ifstream stream;
	stream.open(filePath, std::ios::in | std::ios::binary);

	// Checks the magic number for some dumb reason. It's supposed to be (int)2049 or (hex)801. Also, it's written in big endian, but that matters only in a few reads per file;
	unsigned char temp[4];
	stream.read((char *)temp, 4);
	if (FourCharsToIntBigEndian(temp) != 2051) {
		throw std::runtime_error("Found a problem in the magic number in the file. The data at " + filePath + " might be corrupted.");
	}

	// Reads the number of examples and checks against the maxExamples. Also, it's written in big endian, but that matters only in a few reads per file;
	stream.read((char *)temp, 4);
	exampleCount = std::min(FourCharsToIntBigEndian(temp), maxExamples);

	// Reads the rowCount and columnCount Also written in big endian so... yeah
	stream.read((char *)temp, 4);
	rowCount = FourCharsToIntBigEndian(temp);

	stream.read((char *)temp, 4);
	columnCount = FourCharsToIntBigEndian(temp);

	pixelCount = rowCount * columnCount;

	// Initializes the returnVec
	returnVec = new std::vector<arma::Mat<short>>(exampleCount);

	// Creates buffer used for loading from file
	unsigned char *buffer = new unsigned char[pixelCount];

	// Loops through all examples and loads them into the returnVec
	for (int i = 0; i < exampleCount; i++)
	{
		// Initializes elemnts of ReturnVec
		(*returnVec)[i] = arma::Mat<short>(rowCount, columnCount);

		// Reads to buffer from file
		stream.read((char *)buffer, pixelCount);

		for (int j = 0; j < rowCount; j++)
		{
			for (int k = 0; k < columnCount; k++)
			{
				// Loads every element individually
				(*returnVec)[i](j, k) = buffer[j * columnCount + k];
			}
		}
	}

	// Deletes the buffer to avoid memory leaks
	delete[] buffer;

	return returnVec;
}
