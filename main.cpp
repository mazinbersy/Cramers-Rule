#include <iostream>
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




int main()
{
	int n = 4;
	double** matrix= new double *[n+1];
	for (int i = 0; i < n; i++)
		matrix[i] = new double[n];
	int count = 1;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i == j) matrix[i][j] = 1;
			else matrix[i][j] = 0;
		}
	}
	matrix[n] = NULL; // Terminate the matrix array with NULL

	cout << findMatrixDimension(matrix)<<endl;
	double** subMatrix = findSubmatrix(matrix, 1, 1);
	cout << "Submatrix:" << endl;
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - 1; j++) {
			cout << subMatrix[i][j] << " ";
		}
		cout << endl;
	}
	cout<<"Determinent: "<<calculateDeterminant(matrix)<<endl;

	return 0;
}
