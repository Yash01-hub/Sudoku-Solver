#include "sudoku.h"

int UNSOLVED = 81;
int SIZE_ROWS = 9;
int SIZE_COLUMNS = 9;

int main(){

	cout<<"Enter puzzle:\n";

	int **puzzle; int x;
	puzzle = (int**)malloc(9*sizeof(int*));
	
	for(int i=0;i<SIZE_ROWS;i++){
	
		puzzle[i] = (int*)malloc(9*sizeof(int));
	
		for(int j=0;j<SIZE_COLUMNS;j++){
			cin>>x;
			puzzle[i][j] = x;
		}
	
	}
	
	//int **puzzle = createPuzzle();
	int progress;
	
	Sudoku *sudoku = setUpPuzzle(puzzle);

	printPuzzle(sudoku->squares);

	while(UNSOLVED > 0){
		progress = checkPuzzle(sudoku->squares, sudoku->boxes);
		if(progress == 0){
			cout<<"\nFailed to solve the puzzle!\n";
			break;
		}
	}

	cout<<"\n";

	printPuzzle(sudoku->squares);
	
	return 0;
}