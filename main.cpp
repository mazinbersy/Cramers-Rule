#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sstream>
using namespace std;

double** duplicateMatrix(double** original, int rows, int cols) {
	// Allocate memory for the new array
	double** duplicate = new double* [rows];
	for (int i = 0; i < rows; ++i) {
		duplicate[i] = new double[cols];
	}

	// Copy the contents of the original array to the duplicate
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			duplicate[i][j] = original[i][j];
		}
	}

	return duplicate;
}


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

void equationsToMatrix(double**& matrix, double* equal, int n, map<string, int>& variables, vector<string> equations)
{
	int sign;

	for (int i = 0; i < n; i++)
	{
		sign = 1;
		stringstream ss(equations[i],'+');
		string var;
		string term;
		bool eq = false;
		bool foundvar;
		while (ss >> term)
		{
			int coeff = 0;
			foundvar = false;
			if (term == "+") sign = 1;
			else if (term == "-") sign = -1;
			else if (term == "=") eq = true;
			else if (eq) equal[i] = stod(term);
			else if (term[0] == '=')
			{
				term = term.substr(1);
				eq = true;
				equal[i] = stod(term);
			}
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
				if (term.back() == '=')
				{
					eq = true;
					term.pop_back();
				}

				  if(!term.empty())
				{
					  for (int i = 0; term.size(); i++)
					  {
						  if (isalpha(term[i]) && !isdigit(term[i]))
						  {
							  var = term.substr(i);
							  term = term.substr(0, i);
							  break;
						  }
					}
					  if (term.empty()) term = "1";
				}
		

				if (variables.find(var) == variables.end())
				{
			
					variables[var] = variables.size();
				}
				
				if (!term.empty()) {
					coeff = stod(term) * sign;
				}
				 matrix[i][variables[var]] = coeff;
			}

		}

	}
}

bool cramers(double** matrix, double* equal, int n, map<string, int> variables, vector<string> equations)
{	
	equationsToMatrix(matrix, equal, n, variables, equations);
	if (variables.size() > n)
	{
		cout << "Too Many Variables Entered for Size of Array." << endl;
		return false;
	}
	double det = calculateDeterminant(matrix);
	string var;
	if (det == 0) 
	{
		cout << "Matrix is Not Invertible: No Unique Solution Set."<<endl;
		return false;
	}
	else
	{
		for (int i = 0; i < n; i++)
		{
			double** temp = duplicateMatrix(matrix, n, n);
			for (int j = 0; j < n; j++)
			{
				temp[j][i] = equal[j];
			}
			temp[n] = NULL;
			double detTemp = calculateDeterminant(temp);
			for (auto& pair : variables)
			{
				if (pair.second == i)
					var = pair.first;
			}
			double result = detTemp / det;
			
			
			cout << var << " = " << result <<endl;


		}
	}
	return true;
}


int main() {
	cout << "=========================Cramer's Rule Calculator=========================" << endl <<endl;
	cout << "Enter Equations in the following form: i.e. 2x + 3y + 4z = 5 "<<endl;
		cout<<"(Make Sure to Include Spaces After Each Variable)" << endl<<endl;
	// Number of equations
	cout << "Enter Size of nxn Matrix: ";
	int n;
	do
	{
		cin >> n;
		if (n < 2) cout << "Enter Valid Size." << endl;
	} while (n < 2);
	
	// Coefficient matrix
	double** matrix = new double* [n];
	// Solution matrix
	double* equal = new double[n];

	// Map to store variable indices
	map<string, int> variables;

	// Initialize coefficient matrix and solution matrix
	for (int i = 0; i < n; i++) {
		matrix[i] = new double[n];
		for (int j = 0; j < n; j++) {
			matrix[i][j] = 0;
		}
		equal[i] = 0;
	}
	matrix[n] = NULL;
	// Test equations
	vector<string> equations;
	string temp;
	// Clear input buffer
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	for (int i = 0; i < n; i++)
	{
		cout << "Enter Equation " << i + 1 << ": ";
		getline(cin, temp);		
		equations.push_back(temp);
	}

	cout << endl;
	// Convert equations to matrix form
	bool done = cramers(matrix, equal, n, variables, equations);
	
	if(done)
	{
		cout << endl;
		// Output coefficient matrix and solution matrix
		cout << "Coefficient matrix:" << endl;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cout << matrix[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
		cout << "Solution vector:" << endl;
		for (int i = 0; i < n; i++) {
			cout << equal[i] << endl;
		}
	}

	return 0;
}