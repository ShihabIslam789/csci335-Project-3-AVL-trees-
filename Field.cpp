#include <iostream>
#include <algorithm>
#include "Field.h"


Field::Field(const vector<vector<int>>& value) { // (O)N
	// copy function
	matrix_box = value;
	ROWS = value.size();
	COLUMNS = value[0].size();
	area.resize(ROWS, vector<int>(COLUMNS));
	// take the paramertized value and use it to create space in the amtrix
	for (int a{ 0 }; a < ROWS; a++) {
		for (int b{ 0 }; b < COLUMNS; b++) {
			if (a == 0 and b == 0) {
				area[a][b] = matrix_box[a][b];
			}			
			else if (a == 0) {
				area[a][b] = matrix_box[a][b] + area[a][b-1];
			}
			else if (b == 0) {
				area[a][b] = matrix_box[a][b] + area[a-1][b];
			}
			else {
				area[a][b] = matrix_box[a][b] + area[a - 1][b] + area[a][b - 1]
					+ area[a - 1][b - 1];
			}
		}
	}
}

Field::Field(vector<vector<int>>&& value) { // (O)N
	// move function
	matrix_box = value;
	ROWS = value.size();
	COLUMNS = value[0].size();
	area.resize(ROWS, vector<int>(COLUMNS));
	// taking the parameter to actually fill the matrix with values
	for (int a{ 0 }; a < ROWS; a++) {
		for (int b{ 0 }; b < COLUMNS; b++) {
			if (a == 0 && b == 0) {
				area[a][b] = matrix_box[a][b];
			}
			else if (a == 0) {
				area[a][b] = matrix_box[a][b] + area[a][b - 1];
			}
			else if (b == 0) {
				area[a][b] = matrix_box[a][b] + area[a - 1][b];
			}
			else {
				area[a][b] = matrix_box[a][b] + area[a - 1][b] + area[a][b - 1]
					+ area[a - 1][b - 1];
			}
		}
	}
}

int Field::Weight(int x1, int y1, int x2, int y2) { //(O)N
	int Weight;
	// must be greater or equal to zero b/c no input is possible
	if ((0 <= x1 < ROWS) && (0 <= x2 < ROWS) && (0 <= y1 < COLUMNS) && (0 <= y2 < COLUMNS)) {
		// min/max must be used to figure out the edge cases  of the matrix
		// then the rest of the values can be figured out correctly using Dynamic programming
		int top_left_x = min(y1, y2);
		int top_left_y = min(x1, x2);
		int bottom_right_x = max(y1, y2);
		int bottom_right_y = max(x1, x2);
		Weight = area[bottom_right_x][bottom_right_y];
		if (top_left_y >= 1) {
			Weight = Weight - area[bottom_right_x][top_left_y - 1];
		}
		if (top_left_x >= 1) {
			Weight = Weight - area[top_left_x - 1][bottom_right_y];
		}
		if (top_left_x >= 1 && top_left_y >= 1) {
			Weight = Weight + area[top_left_x - 1][top_left_y - 1];
		}
		else
		{//throw out values greater then the matrix can take
			throw std::out_of_range("not in Matrix");
		}

	}
	return Weight;
}



int Field::PathCost() { // (O)N
	//takes left most COLUMN and bottom most row to get cheapest path
	vector<vector<int>>  cheapest_path(ROWS, vector<int>(COLUMNS));
	// Dynamic programming
	// iterates through the vector in nested for loop
	// will add up the column and row of caller and add them together
	for (int a{ 0 }; a < ROWS; a++) {
		for (int b{ 0 }; b < COLUMNS; b++) {
			if (a == 0  && b == 0) {
				cheapest_path[a][b] = matrix_box[a][b];
			}
			else if (a == 0) { //edge case of first row
				cheapest_path[a][b] = matrix_box[a][b] + cheapest_path[a][b - 1];
			}
			else if (b == 0) { //edge case of first column
				cheapest_path[a][b] = matrix_box[a][b] + cheapest_path[a - 1][b];
			}
			else {// must take min to find lowest number to find cheapest path
				cheapest_path[a][b] = matrix_box[a][b] + min(cheapest_path[a - 1][b], cheapest_path[a][b - 1]);
			}
		}                                      
	}
	return cheapest_path[ROWS - 1][COLUMNS - 1];
}
