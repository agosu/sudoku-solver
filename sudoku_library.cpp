#include "sudoku_header.hpp"
#include <iostream>

using namespace std;

//---- pakoreguoja koordinates mažojo kvadratėlio tikrinimui
int adjust_square_coord(int a) {
	if (a % 3 == 0);
		else if (a % 3 == 1) a--;
		else if (a % 3 == 2) a -= 2;
	return a;
}

//------- užpildo langelio masyvą galimomis reikšmėmis
void possible_values_array(int M[9][9], int N[9][9][9], int y, int x) {
	int h = 0;
	for (int i = 1; i <= 9; i++) { //einam nuo 1 iki 9
		bool nera = true;
		for (int k = 0; k < 9; k++) { //pereinam per eilutę
			if (M[y][k] == i) {
				nera = false;
				break;
			}
		}
		if (nera) { //pereinam per stulpelį
			for (int k = 0; k < 9; k++) {
				if (M[k][x] == i) {
					nera = false;
					break;
				}
			}
		}
		if (nera) { //pereinam per mažąjį kvadratėlį
			for (int k = adjust_square_coord(y); k < adjust_square_coord(y) + 3; k++) {
				for (int m = adjust_square_coord(x); m < adjust_square_coord(x) + 3; m++) {
					if (M[k][m] == i) {
						nera = false;
						break;
					}
				}
			}
		}
		if (nera) { //jeigu nebuvo skaitmens niekur, įrašom į masyvą
			N[y][x][h] = i;
			h++;
		}
	}
}

void go_back(int &x, int &y) {
	if (x != 0)
	    x--;
	else {
	    x = 8;
	    y--;
	}
}

void go_further(int &x, int &y) {
    if (x != 8)
        x++;
    else {
        x = 0;
        y++;
    }
}

void solve_sudoku(int sudoku[9][9]) {
	int possible_array[9][9][9];
	bool need_to_go_back = false;

//----- užpildom galimybių masyvą 0
	for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            for (int k = 0; k < 9; k++)
                possible_array[i][j][k] = 0;

//----- išsisaugom, kuriose koordinatėse yra konstantos
	int const_sudoku[9][9];
	for (int y = 0; y < 9; y++) {
        for (int x = 0; x < 9; x++) {
            if (sudoku[y][x] != 0)
                const_sudoku[y][x] = 10;
            else
                const_sudoku[y][x] = 0;
        }
	}

//---- einam per sudoku
	int x = -1, y = 0;
	int operacija = 1; /////////////////
	while (true) {
		cout << operacija << " "; /////////////////
		operacija++; /////////////////
		x++;
		if (need_to_go_back) {
			x--;
			sudoku[y][x] = 0;
			go_back(x, y);
			while (const_sudoku[y][x] == 10) // kad nestovėtume ant const
                go_back(x, y);
		}
		need_to_go_back = false;

        while (const_sudoku[y][x] == 10) // kad nestovėtume ant const
            go_further(x, y);

        if (sudoku[y][x] == 0) // jeigu nulis, perskaičiuojam galimybių masyvą
            possible_values_array(sudoku, possible_array, y, x);

        if (possible_array[y][x][0] != 0) {
	        sudoku[y][x] = possible_array[y][x][0];
	        for (int i = 0; i < 8; i++) // ištrinam panaudotą masyvo elementą
	        	possible_array[y][x][i] = possible_array[y][x][i+1];
	        if (x == 8 && y != 8) { // jeigu reikia, peršokam į kitą eilutę
	        	x = -1;
	        	y++;
	        } else if (x == 8 && y == 8) // jeigu užpildėm paskutinį langelį, sustojam
                break;
	    } else if (possible_array[y][x][0] == 0) { // jeigu nebėra ką įrašyti, grįžtam
	        need_to_go_back = true;
	    }
    }
}

void print_sudoku(int sudoku[0][9]) {
	cout << endl;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cout << sudoku[i][j] << " ";
		}
		cout << endl;
	}
}