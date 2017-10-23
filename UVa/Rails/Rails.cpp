#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <sstream>

int main(int argc, char* argv[])
{
	int n, cid;
	std::string line;
	while (scanf("%d\n", &n), n)
	{
		while (getline(std::cin, line), line != "0")
		{
			std::istringstream buf(line);
			std::queue<int> train_enter;
			std::queue<int> train_exit;
			std::stack<int> station;
			for (auto i = 1; i < n + 1; ++i)
			{
				buf >> cid;
				train_exit.push(cid);
				train_enter.push(i);
			}

			auto stack_order = true;
			while (!train_exit.empty())
			{
				if (!train_enter.empty())
				{
					if (!station.empty() && station.top() == train_exit.front())
					{
						station.pop();
						train_exit.pop();
					}
					else if (train_exit.front() == train_enter.front())
					{
						train_exit.pop();
						train_enter.pop();
					}
					else
					{
						station.push(train_enter.front());
						train_enter.pop();
					}
				}
				else
				{
					const auto i = station.top();
					station.pop();
					const auto j = train_exit.front();
					train_exit.pop();
					if (i != j)
					{
						stack_order = false;
						break;
					}
				}
			}

			printf("%s\n", stack_order ? "Yes" : "No");
		}

		printf("\n");
	}

	return 0;
}
