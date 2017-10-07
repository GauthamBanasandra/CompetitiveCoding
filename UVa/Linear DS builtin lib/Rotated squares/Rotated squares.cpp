#include <iostream>
#include <vector>
#include <string>

using big_int = unsigned long long;
inline void Swap(char *a, char *b)
{
	auto t = *a;
	*a = *b;
	*b = t;
}

class Matrix
{
public:
	Matrix(big_int dim);
	~Matrix();

	void PrintMatrix();
	void Rotate90Clk();

private:
	big_int dim;
	std::vector<std::string> m;
};

Matrix::Matrix(big_int dim)
{
	this->dim = dim;
	m.reserve(dim);
	for (auto i = 0; i < dim; i++)
	{
		m.push_back("");
		std::getline(std::cin, m[i]);
	}
}

Matrix::~Matrix()
{
}

void Matrix::PrintMatrix()
{
	for (auto i = 0; i < dim; i++)
	{
		std::cout << m[i] << std::endl;
	}
}

void Matrix::Rotate90Clk()
{
	if (dim == 1)
	{
		return;
	}

	for (auto i = 0; i < dim >> 1; i++)
	{
		auto &a = m[i][i];
		auto &b = m[i][dim - i - 1];
		auto &c = m[dim - i - 1][dim - i - 1];
		auto &d = m[dim - i - 1][i];

		auto t = a;
		Swap(&b, &t);
		Swap(&c, &t);
		Swap(&d, &t);
		Swap(&a, &t);
	}
}

int main()
{
	big_int N, n;
	while (scanf("%llu %llu\n", &N, &n), N || n)
	{
		Matrix nm(N);
		Matrix Nm(n);
		nm.PrintMatrix();
		std::cout << "After rotating" << std::endl;
		nm.Rotate90Clk();
		nm.PrintMatrix();
		std::cout << "After rotating" << std::endl;
		nm.Rotate90Clk();
		nm.PrintMatrix();
		std::cout << "After rotating" << std::endl;
		nm.Rotate90Clk();
		nm.PrintMatrix();
		std::cout << "After rotating" << std::endl;
		nm.Rotate90Clk();
		nm.PrintMatrix();
	}

	return 0;
}