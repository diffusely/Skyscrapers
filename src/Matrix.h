#pragma once
#include <vector>
#include <iostream>

class Matrix
{
public:

	Matrix(std::vector<std::vector<int>> arr);
	

	void print();
	

	void operator =(std::vector<std::vector<int>>& ob);
	
	std::vector<std::vector<int>> getVector();
	

private:

	std::vector<std::vector<int>> arr;
	int size;

};

