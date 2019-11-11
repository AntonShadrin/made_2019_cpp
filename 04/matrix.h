#include <vector>

class Matrix
{
	std::vector<std::vector<int>> matrix;
public:
	Matrix(size_t n_rows, size_t n_col);
	~Matrix() {};
	int getRows() const;
	int getColumns() const;
	void operator *= (const int& vol);
	bool operator == (const Matrix& other) const;
	bool operator != (const Matrix& other) const;
	class Proxy
	{
		std::vector<int>* rowPtr;
	public:
		Proxy(std::vector<int>* ptr) : rowPtr(ptr) {}
		int& operator [] (int j);
	};
	Proxy operator [] (int i);
};
