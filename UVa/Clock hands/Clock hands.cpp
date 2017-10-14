#include <stdio.h>
#include <math.h>
#include <ios>

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	int h = 0, m = 0;
	while (scanf("%d:%d", &h, &m), h || m)
	{
		const auto m_angle = m * 6;
		const double h_angle = h * 30 + m / 2.0;
		double h_m_angle = abs(m_angle - h_angle);
		if (h_m_angle > 180)
		{
			h_m_angle = abs(360 - h_m_angle);
		}

		printf("%.3f\n", h_m_angle);
	}

	return 0;
}
