#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

template<typename T>
class FileToArray
{
private:

public:

	// Pass pointer by reference since we're modifying the pointer
	static void ReadFileTo_Array_1D(std::string path, int size, T*& myArray);
	static void ReadFileTo_Array_2D(std::string path, int sizeH, int sizeW, T**& myArray);

	static void ReadFileTo_Vector_1D(std::string path, std::vector<T>& myVector);
};

// Pass pointer by reference since we're modifying the pointer
template<typename T>
void FileToArray<T>::ReadFileTo_Array_1D(std::string path, int size, T*& myArray)
{
	myArray = new T[size];
	memset(myArray, 0, sizeof(T) * size);

	// ifsteam/ofstream == IO read write streams, fstream does both
	// Open the file on the stream
	std::ifstream myStream(path);

	// Read the file containing the animation's tile values

	std::string line = "";
	std::string strTileIndex = "";

	size_t endPos = 0;
	int index = 0;

	std::getline(myStream, line);

	// npos equals -1, which means the maximum value for its containing type, unsigned long long / unsigned __int64
	while (endPos != std::string::npos) // Npos means not found
	{
		endPos = line.find_first_of(","); // Returns npos if nothing is found
		strTileIndex = line.substr(0, endPos); // Substrings left of endPos (From some position for some amount of chars)

		if (strTileIndex.length() > 0) // Only proceed if there is a value to work on
		{
			line = line.substr(endPos + (size_t)1); // Substrings right from endPos (From some positon until the end)
			myArray[index] = std::stoul(strTileIndex); // Assign left substring as unsigned long
			index++;
		}
		else if (endPos != std::string::npos)
		{
			// Avoid getting stuck if some middle value is empty instead of having a number
			// For instance if we have a ...1,2,,4,5... sequence, the ,, is problematic and would cause an infinite loop without this
			line = line.substr(endPos + (size_t)1);
			myArray[index] = 0;
			index++;
		}
	}
}

template<typename T>
void FileToArray<T>::ReadFileTo_Array_2D(std::string path, int sizeH, int sizeW, T**& myArray)
{
	// Initializing the two dimentional array that will contain our values

	// Create 1nd dimension
	myArray = new unsigned long* [sizeH];
	memset(myArray, 0, sizeof(unsigned long*) * sizeH);

	// Create 2nd dimension
	for (int i = 0; i < sizeH; i++)
	{
		myArray[i] = new unsigned long[sizeW];
		memset(myArray[i], 0, sizeof(unsigned long) * sizeW);
	}

	// ifsteam/ofstream == IO read write streams, fstream does both
	// Open the file on the stream
	std::ifstream myStream(path);

	// Read the file containing the map's tile values

	std::string line = "";
	std::string strTileIndex = "";

	// size_t will work since we compare endPos to std::string::npos, which is a size_t type
	// size_t is actually a typedef for unsigned long long

	// npos is actually equal to -1, which when converted to size_t becomes the max value for that type

	// When comparing a signed type with an unsigned type, the signed type is converted to the unsigned type
	// This means instead of reading the 1st binary 1 as negative and adding the rest as positive, we read everything as positive

	// This is why using int works (Stored negative -1 becomes max value of unsigned long long)
	// Unsigned long long works too (Stored value is already max value since we tried to assign -1 to an unsigned type)

	// Meanwhile, a simple unsigned long will not work (Stored value is already max value... of long... and long is smaller than long long)

	size_t endPos = 0;

	int index_X = 0;
	int index_Y = 0;

	while (std::getline(myStream, line)) // Read line by line
	{
		// npos equals -1, which means the maximum value for its containing type, unsigned long long / unsigned __int64
		while (endPos != std::string::npos) // Npos means not found
		{
			endPos = line.find_first_of(","); // Returns npos if nothing is found
			strTileIndex = line.substr(0, endPos); // Substrings left of endPos (From some position for some amount of chars)

			if (strTileIndex.length() > 0) // Only proceed if there is a value to work on
			{
				line = line.substr(endPos + (size_t)1); // Substrings right from endPos (From some positon until the end)
				myArray[index_Y][index_X] = std::stoul(strTileIndex); // Assign left substring as unsigned long
				index_X++;
			}
			else if (endPos != std::string::npos)
			{
				// Avoid getting stuck if some middle value is empty instead of having a number
				// For instance if we have a ...1,2,,4,5... sequence, the ,, is problematic and would cause an infinite loop without this
				line = line.substr(endPos + (size_t)1);
				myArray[index_Y][index_X] = 0;
				index_X++;
			}
		}

		index_Y++;
		index_X = 0;
		endPos = 0;
	}

	// Closing the stream
	myStream.close();
}

template<typename T>
void FileToArray<T>::ReadFileTo_Vector_1D(std::string path, std::vector<T>& myVector)
{
	myVector = std::vector<unsigned long>(50);

	std::ifstream myStream(path);

	std::string line = "";
	std::string strTileIndex = "";

	size_t endPos = 0;

	while (std::getline(myStream, line)) // Read line by line
	{
		// npos equals -1, which means the maximum value for its containing type, unsigned long long / unsigned __int64
		while (endPos != std::string::npos) // Npos means not found
		{
			endPos = line.find_first_of(","); // Returns npos if nothing is found
			strTileIndex = line.substr(0, endPos); // Substrings left of endPos (From some position for some amount of chars)

			if (strTileIndex.length() > 0) // Only proceed if there is a value to work on
			{
				line = line.substr(endPos + (size_t)1); // Substrings right from endPos (From some positon until the end)
				myVector.push_back(std::stoul(strTileIndex)); // Assign left substring as unsigned long
			}
			else if (endPos != std::string::npos)
			{
				// Avoid getting stuck if some middle value is empty instead of having a number
				// For instance if we have a ...1,2,,4,5... sequence, the ,, is problematic and would cause an infinite loop without this
				line = line.substr(endPos + (size_t)1);
				myVector.push_back(0);
			}
		}

		endPos = 0;
	}

	myStream.close();
}
