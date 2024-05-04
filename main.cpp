#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sstream>
using namespace std;

int findMatrixDimension(double** matrix)
{
	int n=0;
	while (matrix[n] != NULL)
	{
		n++;
	}
	return n;
}

double** findSubmatrix(double** matrix, int row, int col)
{
	int n = findMatrixDimension(matrix);
	double** subMatrix = new double* [n - 1];
	for (int i = 0; i < n - 1; i++)
		subMatrix[i] = new double[n - 1];

	int rowoffset = 0;
	int coloffset = 0;

	for (int i = 0; i < n - 1; i++)
	{
		// If we encounter the row to exclude, we need to skip it and adjust the row offset
		if (i == row) {
			rowoffset = 1;
		}

		coloffset = 0;

		for (int j = 0; j < n - 1; j++)
		{
			// If we encounter the column to exclude, we need to skip it and adjust the column offset
			if (j == col) {
				coloffset = 1;
			}

			subMatrix[i][j] = matrix[i + rowoffset][j + coloffset];
		}
	}
	subMatrix[n - 1] = NULL;

	return subMatrix;
}


double calculateDeterminant(double ** matrix)
{
	double determinant;
	if (findMatrixDimension(matrix) == 2)
		return (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]);
	else
	{
		int n = findMatrixDimension(matrix);
		int sign = 1;
		int sum = 0;
		int colNum = 0;
		while (colNum < n)
		{
			double** subMatrix = findSubmatrix(matrix, 0, colNum);
			determinant = calculateDeterminant(subMatrix);
			sum += matrix[0][colNum] * determinant * sign;
			sign = -sign;
			colNum++;
		}
		return sum;
	}

}

void equationsToMatrix(double**& matrix, double* equal, int n, map<char, int>& variables, vector<string> equations)
{
	int sign;

	for (int i = 0; i < n; i++)
	{
		sign = 1;
		stringstream ss(equations[i]);
		char var;
		string term;
		bool eq = false;

		while (ss >> term)
		{
			int coeff = 0;
			if (term == "+") sign = 1;
			else if (term == "-") sign = -1;
			else if (term == "=") eq = true;
			else if (eq) equal[i] = stoi(term);

			else 
			{
				if (term[0] == '-')
				{
					sign = -1;
					term = term.substr(1);
				}
				if (term[0] == '+')
				{
					sign = 1;
					term = term.substr(1);
				}
				
				if(term.length()!=0)
				{
					var = term.back();
					term.pop_back();
					if (term.empty()) term = "1";
				}


				if (variables.find(var) == variables.end() && isalpha(var))
				{
					variables[var] = variables.size();
				}
				
				if (!term.empty()) {
					coeff = stoi(term) * sign;
				}
				 matrix[i][variables[var]] = coeff;
			}

		}

	}
}



//int main()
//{
//	int n = 4;
//	double** matrix= new double *[n+1];
//	for (int i = 0; i < n; i++)
//		matrix[i] = new double[n];
//	int count = 1;
//	for (int i = 0; i < n; i++)
//	{
//		for (int j = 0; j < n; j++)
//		{
//			if (i == j) matrix[i][j] = 1;
//			else matrix[i][j] = 0;
//		}
//	}
//	matrix[n] = NULL; // Terminate the matrix array with NULL
//
//	cout << findMatrixDimension(matrix)<<endl;
//	double** subMatrix = findSubmatrix(matrix, 1, 1);
//	cout << "Submatrix:" << endl;
//	for (int i = 0; i < n - 1; i++) {
//		for (int j = 0; j < n - 1; j++) {
//			cout << subMatrix[i][j] << " ";
//		}
//		cout << endl;
//	}
//	cout<<"Determinent: "<<calculateDeterminant(matrix)<<endl;
//
//	return 0;
//}


int main() {
	// Number of equations
	int n = 3;

	// Coefficient matrix
	double** matrix = new double* [n];

	// Solution matrix
	double* equal = new double[n];

	// Map to store variable indices
	map<char, int> variables;

	// Initialize coefficient matrix and solution matrix
	for (int i = 0; i < n; i++) {
		matrix[i] = new double[n];
		for (int j = 0; j < n; j++) {
			matrix[i][j] = 0;
		}
		equal[i] = 0;
	}

	// Test equations
	vector<string> equations = {
		"2x + 3y - 2z = 2",
		"3x - y + 4z = -5",
		"x + 2y - z = 3"
	};

	// Convert equations to matrix form
	equationsToMatrix(matrix, equal, n, variables, equations);

	// Output coefficient matrix and solution matrix
	cout << "Coefficient matrix:" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}

	cout << "Solution matrix:" << endl;
	for (int i = 0; i < n; i++) {
		cout << equal[i] << endl;
	}

	// Free memory
	for (int i = 0; i < n; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
	delete[] equal;

	return 0;
}