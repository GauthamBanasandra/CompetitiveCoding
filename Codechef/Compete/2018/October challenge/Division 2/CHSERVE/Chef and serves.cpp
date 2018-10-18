//
// Created by Gautham on 18-10-2018.
//

#include <iostream>
#include <string>
#include <ios>

using ll = long long;

std::string GetNextServer(ll chef, ll cook, ll k)
{
	return ((chef + cook) / k) % 2 ? "COOK" : "CHEF";
}

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	int t;
	ll chef, cook, k;

	std::cin >> t;
	while (t--)
	{
		std::cin >> chef >> cook >> k;
		std::cout << GetNextServer(chef, cook, k) << std::endl;
	}
	return 0;
}
