#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;


string translate(int t) {

	switch (t)
	{

	case 1: 

		return "Up";
		break;

	case 2: 

		return "Left";
		break;
	case 3: 

		return "Right";
		break;

	case 4:
		return "Down";
		break;
	default:
		return "Start";
		break;
	}



}
struct state {
	int id;
	int parent_id;
	vector<int> grid;
	int last_move;
	int zero_index;
};

class Puzzle {
public:
	vector<int> moves;
	queue<state> puzzle;
	int search_id;
	int expansions;
	vector<state> visited_states;
	void BFS(int start[] , int goal[], int n);
	void store_moves();
	void print_moves();

};

void Puzzle::print_moves() {

	reverse(moves.begin(), moves.end());

	for (int i = 1; i < moves.size(); i++) {

		cout << translate(moves[i])<<endl;
		/*if (i != moves.size() - 1) {

			cout << " -> ";
		}
		*/

	}


}
void Puzzle::store_moves() {

	for (auto i = visited_states.begin(); i != visited_states.end(); i++) {

		if (i->id == search_id) {


			moves.push_back(i->last_move);
			search_id = i->parent_id;

			if (search_id == 0) {

				return;
			}
			store_moves();

		}



	}//end of for loop




	return;
}

void Puzzle::BFS(int start[], int goal[] , int n ) {

	state first_state;

	for (int i = 0; i < n; i++) {

			first_state.grid.push_back(start[i]);

		if (start[i] == 0) first_state.zero_index = i;

	}

	vector<int> goal_grid;

	for (int i = 0; i < n; i++) {

		goal_grid.push_back(goal[i]);
	}
	
	first_state.last_move = 0;

	first_state.id = 1;
	first_state.parent_id = 0;

	puzzle.push(first_state);

	state s;
	int id_counter = 2;
	while (!puzzle.empty()) {

	
	s =	puzzle.front();
	visited_states.push_back(s);
	puzzle.pop();
	expansions++;

	

		if (s.last_move != 4 /* if last move is not down, you can move up*/ && s.zero_index > 2) { //move up

			state child_s;

			child_s.grid = s.grid;

			swap(child_s.grid[s.zero_index], child_s.grid[s.zero_index - 3]);

		

			child_s.zero_index = s.zero_index - 3;
			child_s.last_move = 1;

			child_s.parent_id = s.id;
			child_s.id = id_counter;
			id_counter++;

			if (child_s.grid == goal_grid) {

				search_id = child_s.id;
				visited_states.push_back(child_s);
				break;

			}

			puzzle.push(child_s);


		}


		if (s.last_move != 3 /* if last move is not right, you can move left*/ && (s.zero_index % 3) != 0) { //move left

			state child_s;

			child_s.grid = s.grid;

			swap(child_s.grid[s.zero_index], child_s.grid[s.zero_index - 1]);

			child_s.zero_index = s.zero_index - 1;
			child_s.last_move = 2;

			child_s.parent_id = s.id;
			child_s.id = id_counter;
			id_counter++;

			if (child_s.grid == goal_grid) {

				search_id = child_s.id;
				visited_states.push_back(child_s);
				break;

			}

			puzzle.push(child_s);


		}

		if (s.last_move != 2 /* if last move is not left, you can move right*/ && ((s.zero_index - 2) % 3) != 0) { //move right

			state child_s;

			child_s.grid = s.grid;

			swap(child_s.grid[s.zero_index], child_s.grid[s.zero_index + 1]);

			child_s.zero_index = s.zero_index + 1;
			child_s.last_move = 3;

			child_s.parent_id = s.id;
			child_s.id = id_counter;
			id_counter++;

			if (child_s.grid == goal_grid) {

				search_id = child_s.id;
				visited_states.push_back(child_s);
				break;

			}

			puzzle.push(child_s);


		}

		if (s.last_move != 1 /* if last move is not up, you can move down*/ && s.zero_index < 6) { //move down

			state child_s;

			child_s.grid = s.grid;

			swap(child_s.grid[s.zero_index], child_s.grid[s.zero_index + 3]);

			child_s.zero_index = s.zero_index + 3;
			child_s.last_move = 4;

			child_s.parent_id = s.id;
			child_s.id = id_counter;
			id_counter++;

			if (child_s.grid == goal_grid) {

				search_id = child_s.id;
				visited_states.push_back(child_s);
				break;

			}

			puzzle.push(child_s);


		}

	}//end of while loop

	store_moves();
	print_moves();
	cout << endl << "Expansions: " << expansions;

}

int main() {

	Puzzle p;

	int a[] = { 3 , 1 , 4 , 2, 8 , 6 , 7 , 0 ,5};
	int goal[] = {1, 2 , 3 , 8 , 0 , 4 , 7 , 6 , 5 };
	int n = 9;

	p.BFS(a , goal , n);

	return 0;
}