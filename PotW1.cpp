#include <iostream>
#include <vector>

using namespace std;

void fill_vector(int, vector< pair <string, unsigned long int>>&);
void find_match(vector< pair <string, unsigned long int>>, pair<string, string>&, pair<string, string>&);
void print_users(pair <string, string>, pair <string, string>);

int main () {

	int num_users;
	vector <pair <string,unsigned long int>> users;
	pair <string, string> best_match, worst_match;


	cin >> num_users;
	fill_vector(num_users, users);
	find_match(users, best_match, worst_match);
	print_users(best_match, worst_match);

	return 0;
}

void fill_vector(int size, vector< pair <string, unsigned long int>>& users) {

	pair <string, unsigned long int> cur_user;

	for (int i = 0; i < size; i++) { //fill vector with users
		cin >> cur_user.first >> cur_user.second;
		users.push_back(cur_user);
	}
}

void find_match(vector< pair <string, unsigned long int>> users, pair<string, string>& best_match, pair<string, string>& worst_match) {

	unsigned long int best = 4294967295, worst = 0, second_worst = 0; //highest unsigned long value, lowest unsigned long value

	for (auto x : users) {
		for (auto y : users) {
			if (x.first == y.first) //check if comparing a user to itself
				continue;

			auto check = x.second ^ y.second;

			if (check < best) { //check if two users are the best match
				best_match.first = x.first;
				best_match.second = y.first;
				best = check;
			}

			if (check > worst) //set the value for worst match
				worst = check;

			/* since we must consider that opposites attract, using the absolute worst match would mean that the current
			   couple is actually a plausible good match. So by taking the second worst match, we have the true worst couple
			   because the 'opposites attract' rule does is not as strong as it is for the absolute worst couple
			*/
			if ((check < worst) && (check > second_worst)) { //check if two users are the worst match
				worst_match.first = x.first;
				worst_match.second = y.first;
				check = second_worst;
			}
		}
	}
}

void print_users(pair<string, string> best, pair<string, string> worst) {

	cout << best.first << " " << best.second << "\n"
		 << worst.first << " " << worst.second << "\n";
}

