#include <iostream>
#include <vector>
#include <bitset>

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

	bitset<32> best = 4294967295, worst = 0, check; //highest unsigned long value, lowest unsigned long value

	for (auto x : users) {
		for (auto y : users) {
			if (x.first == y.first) //check if comparing a user to itself
				continue;

			check = x.second ^ y.second;

			//cout << best.to_string() << endl << "SIZE: " << best.size() << endl;

			if (check.count() < best.count()) { //check if two users are the best match
				best_match.first = x.first;
				best_match.second = y.first;
				best = check;
			}

			if (check.count() > worst.count()) { //check if two users are the worst match
				worst_match.first = x.first;
				worst_match.second = y.first;
				check = worst;
			}
		}
	}
}

void print_users(pair<string, string> best, pair<string, string> worst) {

	cout << best.first << " " << best.second << "\n"
		 << worst.first << " " << worst.second << "\n";
}

