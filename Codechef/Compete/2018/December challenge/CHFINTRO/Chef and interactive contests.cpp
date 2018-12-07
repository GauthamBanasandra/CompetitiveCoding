#include <iostream>

class Classifier
{
public:
	explicit Classifier(const int r) :r_(r) {}

	const char* Classify(const int rating) const { return rating < r_ ? "Bad boi" : "Good boi"; }

private:
	int r_;
};

int main(int argc, char* argv[])
{
	int num_contestants, r, rating;

	std::cin >> num_contestants >> r;
	Classifier classifier(r);
	for (auto i = 0; i < num_contestants; ++i)
	{
		std::cin >> rating;
		std::cout << classifier.Classify(rating) << std::endl;
	}
	return 0;
}
