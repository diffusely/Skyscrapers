#include "Matrix.h"

Matrix::Matrix(std::vector<std::vector<int>> arr) 
	: arr(arr)
{
	this->size = 4;
}

void Matrix::print()
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			std::cout << arr[i][j] << " ";
		}
		std::cout << "\n";
	}
}

void Matrix::operator=(std::vector<std::vector<int>>& ob)
{
	this->arr = ob;
}

std::vector<std::vector<int>> Matrix::getVector()
{
	return this->arr;
}


