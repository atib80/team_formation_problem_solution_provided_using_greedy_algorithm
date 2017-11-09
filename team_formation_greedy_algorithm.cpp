#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
// #include <fstream>
#include <cstdio>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>

using namespace std;

using team_cases = vector<multiset<long long>>;
using team_cases_unique = vector<set<long long>>;

int main() {

	size_t t{}; 
	
	cin >> t;

	team_cases data(t, multiset<long long>{});

	for (size_t i = 0u, n{}; i < t; ++i) {

		cin >> n;

		if (!n) continue;

		long long skill_value;

		for (size_t j{}; j < n; ++j) {

			cin >> skill_value;

			data[i].insert(skill_value); // O(logN)

		}

	}

	for (size_t i{}; i < t; i++) {

		const auto team_size{ data[i].size() };

		if (!team_size) {
			printf("0\n");
			continue;
		}		

		if (team_size == 1)
		{
			printf("1\n");
			continue;
		}
			
		auto current{ cbegin(data[i]) };
		
		auto prev_value_count{ data[i].count(*current) };
		auto current_value_count{ prev_value_count };
		size_t next_value_count;
		
		auto next { data[i].upper_bound(*current) };		

		auto minimum_team_size {string::npos};
		size_t current_team_size{1u};

		auto found_sts{ false };

		while (next != cend(data[i]))
		{
			if (prev_value_count > team_size / 2)
			{
				printf("1\n");
				found_sts = true;
				break;
			}

			const auto next_next = data[i].upper_bound(*next);

			if (next_next == cend(data[i]))
			{
				next_value_count = current_value_count;

			}
			else			
			{
				next_value_count = data[i].count(*next_next);
			}

			if ( (current_value_count != prev_value_count) && ( (current_value_count != next_value_count) || (next_next == cend(data[i]) ) ) )
			{
				printf("1\n");
				found_sts = true;
				break;				
			}

			if ( (*next - *current) > 1 )
			{
				if ( (current_team_size == 1) || (next_next == cend(data[i]) ) )
				{
					printf("1\n");
					found_sts = true;
					break;
				}

				if (current_team_size < minimum_team_size) minimum_team_size = current_team_size;
				
				current_team_size = 1;				
				
			} else
			{
				current_team_size++;
			}

			prev_value_count = current_value_count;
			current_value_count = next_value_count;
			current = next;
			next = next_next;
		}		

		if (!found_sts) {
			if (current_team_size < minimum_team_size) minimum_team_size = current_team_size;
			printf("%lu\n", minimum_team_size);
		}
		
	}

	return 0;
}
