
#include <iostream>
#include <iomanip>
using namespace std;

int const SIZE = 3;
void convert(int matrix[SIZE][SIZE], int converted[SIZE][SIZE])
{
    for (int i=0; i < SIZE; i++)
    {
        for (int j=0; j < SIZE; j++)
        {
            converted[j][i] = matrix[i][j];
        }
    }
}
int main()
{
    int matrix[SIZE][SIZE] = { 
    { 1, 2, 3 },
    { 0, -1, -2 },
    { 7, 8, 9 } 
    };

    int converted[SIZE][SIZE];
    convert(matrix, converted);

    cout << " Main matrix is: \n\n";
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            cout << setw(3) << matrix[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl << " Converted matrix is: \n\n";
    for (int i = 0; i < SIZE; i++) 
    {
        for (int j = 0; j < SIZE; j++) 
        {
            cout << setw(3) << converted[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}