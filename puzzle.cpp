#include "sudoku.h"

Sudoku *createSudoku(Square ***squares, Box **boxes){
	Sudoku *sudoku = (Sudoku *)malloc(sizeof(Sudoku));

	sudoku->squares = squares;
	sudoku->boxes = boxes;

	return sudoku;
}

Sudoku *setUpPuzzle(int **puzzle){
	
	Square ***sudoku;
	sudoku = (Square ***)malloc(9*sizeof(Square**));

	Box **boxes;
	boxes = createBoxes();

	int currentBox = 0;
	
	for(int i=0;i<SIZE_ROWS;i++){
		
		sudoku[i] = (Square **)malloc(9*sizeof(Square*));
		
		for(int j=0;j<SIZE_COLUMNS;j++){
		
			sudoku[i][j] = (Square *)malloc(9*sizeof(Square));
			sudoku[i][j]->number = puzzle[i][j];
		
			sudoku[i][j]->row = i;
			sudoku[i][j]->column = j;
			sudoku[i][j]->solvable = 9;

			boxes[currentBox]->squares[ boxes[currentBox]->numbers ] = sudoku[i][j];
			sudoku[i][j]->box = boxes[currentBox];
			boxes[currentBox]->numbers++;

			for(int x=0;x<SIZE_ROWS;x++){
				sudoku[i][j]->possible[x] = 0;
			}
		
			if(j == 2)
				currentBox++;
			if(j == 5)
				currentBox++;
		}

		currentBox-=2;
		if(i == 2)
			currentBox = 3;
		if(i == 5)
			currentBox = 6;
	}

	for(int i=0;i<SIZE_ROWS;i++){
		for(int j=0;j<SIZE_COLUMNS;j++){
			if(sudoku[i][j]->number!=0){
				sudoku[i][j]->solvable = 0;
				updateSudoku(sudoku, i, j);
				updateBoxes(sudoku, i, j);
				UNSOLVED--;
			}
		}
	}

	return createSudoku(sudoku, boxes);
}

int updateSudoku(Square ***sudoku, int row, int column){
	int number = sudoku[row][column]->number;
	for(int x=0; x<SIZE_ROWS; x++){
		if(sudoku[x][column]->possible[number-1] == 0){
			sudoku[x][column]->solvable--;
		}
		sudoku[x][column]->possible[number-1] = 1;
	}

	for(int x=0; x<SIZE_COLUMNS; x++){
		if(sudoku[row][x]->possible[number-1] == 0){
			sudoku[row][x]->solvable--;
		}
		sudoku[row][x]->possible[number-1] = 1;
	}
	return 1;
}

int checkPuzzle(Square ***sudoku, Box **boxes){
	for(int i=0;i<SIZE_ROWS;i++){
		for(int j=0;j<SIZE_COLUMNS;j++){
			if(sudoku[i][j]->solvable == 1){
				solveSquare(sudoku[i][j]);
				updateSudoku(sudoku, i, j);
				updateBoxes(sudoku, i, j);

				return 1;
			}
		}
	}

	if(boxSingles(sudoku, boxes))
		return 1;
	
	return checkRows(sudoku, boxes);

}


int **createPuzzle(){
	int **puzzle;
	int i, j;
	int array[9][9] = {0,1,9,	0,0,2,	0,0,0,
					   4,7,0,	6,9,0,	0,0,1,
					   0,0,0,	4,0,0,	0,9,0,

					   8,9,4,	5,0,7,	0,0,0,
					   0,0,0,	0,0,0,	0,0,0,
					   0,0,0,	2,0,1,	9,5,8,

					   0,5,0,	0,0,6,	0,0,0,
					   6,0,0,	0,2,8,	0,7,9,
					   0,0,0,	1,0,0,	8,6,0 };

	puzzle = (int**)malloc(9*sizeof(int*));
	for(int i=0;i<SIZE_ROWS;i++){
		puzzle[i] = (int*)malloc(9*sizeof(int));
		for(int j=0;j<SIZE_COLUMNS;j++){
			puzzle[i][j] = array[i][j];
		}
	}
	return puzzle;
}

void printPuzzle(Square ***puzzle){
	cout<<" -----------------------------\n";
	for(int i=0;i<SIZE_ROWS;i++){
		if(i && i%3==0)
			cout<<" ---------|---------|---------\n";
		for(int j=0;j<SIZE_COLUMNS;j++){
			if(j%3==0)
				cout<<"|";
			cout<<" "<<puzzle[i][j]->number<<" ";
		}
		cout<<"|\n";
	}
	cout<<" -----------------------------\n";
	return;
}

