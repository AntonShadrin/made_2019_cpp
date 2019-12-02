#include <iostream>
#include "matrix.h"

bool test_matrix()
{
	int row = 3, col = 3;
	//инициализация 
	Matrix m(row, col);
	//задание элементов
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; j++)
			m[i][j] = i;
	//проверка
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; j++)
			if (m[i][j] != i)
				return false;
	//умножение
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; j++)
			m[i][j] *= j;
	//проверка
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; j++)
			if (m[i][j] != i*j) return false;
	//инициализация второй матрицы
	Matrix m2(row, col);
	//задание элементов
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; j++)
			m2[i][j] = 1;
	//проверка равенства
	if(m2==m) return false;
	//изменение элементов второй матрицы
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; j++)
			m2[i][j] *= i*j;
	//проверка равенства
	if (m2 != m) return false;
	try
	{
		m[0][4] = 5;
		return false;
	}
	catch (const std::out_of_range& arr)
	{
		std::cout << arr.what() << " True exception!\n";
	}
	return true;
}

int main()
{
	if (!test_matrix())
	{
		std::cout << "test_matrix FAILED!\n";
		return 1;
	}
	std::cout << "All test COMPLETED!\n";
	return 0;
}