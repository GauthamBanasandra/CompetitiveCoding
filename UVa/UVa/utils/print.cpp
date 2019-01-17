//
// Created by gauth on 03-07-2018.
//

#include <iostream>
#include <vector>

using ll = long long;

void Print(const std::vector<int> &elements) {
	for (const auto element : elements) {
		std::cout << element << " ";
	}

	std::cout << std::endl;
}

template<typename T>
void Print(const std::vector<std::vector<T>> &matrix, const char separator = ' ') {
	for (const auto &row : matrix) {
		for (int element : row) {
			std::cout << element << separator;
		}
		std::cout << std::endl;
	}
}

void Print(const std::vector<std::vector<int>> &matrix) {
	Print<int>(matrix);
}

void Print(const std::vector<std::vector<ll>> &matrix) {
	Print<ll>(matrix);
}
void Print(const std::vector<std::vector<double>> &matrix)
{
	Print<double>(matrix);
}

template<typename T>
void Print(const std::vector<T> &numbers, char separator = ' ') {
	for (const auto &number : numbers) {
		std::cout << number << separator;
	}
	std::cout << std::endl;
}

void Print(const std::vector<ll> &numbers, char separator = ' ') {
	Print<ll>(numbers, separator);
}

void Print(const std::vector<std::size_t> &numbers, char separator = ' ') {
	Print<std::size_t>(numbers, separator);
}