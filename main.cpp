#include <stdio.h>
#include <array>

// Define a vector as an array of floats
template<size_t N>
using TVector = std::array<float, N>;

// Define a matrix as an array of vectors
template<size_t M, size_t N>
using TMatrix = std::array<TVector<N>, M>;

// Helper function to fill out a matrix
template <size_t M, size_t N>
TMatrix<M, N> MakeMatrix(std::initializer_list<std::initializer_list<float>> matrixData)
{
    TMatrix<M, N> matrix;

    size_t m = 0;
    assert(matrixData.size() == M);
    for (const std::initializer_list<float>& rowData : matrixData)
    {
        assert(rowData.size() == N);
        size_t n = 0;
        for (float value : rowData)
        {
            matrix[m][n] = value;
            ++n;
        }
        ++m;
    }

    return matrix;
}

// Make a specific row have a 1 in the colIndex, and make all other rows have 0 there
template <size_t M, size_t N>
bool MakeRowClaimVariable(TMatrix<M, N>& matrix, size_t rowIndex, size_t colIndex)
{
    // Find a row that has a non zero value in this column and swap it with this row
    {
        // Find a row that has a non zero value
        size_t nonZeroRowIndex = rowIndex;
        while (nonZeroRowIndex < M && matrix[nonZeroRowIndex][colIndex] == 0.0f)
            ++nonZeroRowIndex;

        // If there isn't one, nothing to do
        if (nonZeroRowIndex == M)
            return false;

        // Otherwise, swap the row
        if (rowIndex != nonZeroRowIndex)
            std::swap(matrix[rowIndex], matrix[nonZeroRowIndex]);
    }

    // Scale this row so that it has a leading one
    float scale = 1.0f / matrix[rowIndex][colIndex];
    for (size_t normalizeColIndex = colIndex; normalizeColIndex < N; ++normalizeColIndex)
        matrix[rowIndex][normalizeColIndex] *= scale;

    // Make sure all rows except this one have a zero in this column.
    // Do this by subtracting this row from other rows, multiplied by a multiple that makes the column disappear.
    for (size_t eliminateRowIndex = 0; eliminateRowIndex < M; ++eliminateRowIndex)
    {
        if (eliminateRowIndex == rowIndex)
            continue;

        float scale = matrix[eliminateRowIndex][colIndex];
        for (size_t eliminateColIndex = 0; eliminateColIndex < N; ++eliminateColIndex)
            matrix[eliminateRowIndex][eliminateColIndex] -= matrix[rowIndex][eliminateColIndex] * scale;
    }

    return true;
}

// make matrix into reduced row echelon form
template <size_t M, size_t N>
void GaussJordanElimination(TMatrix<M, N>& matrix)
{
    size_t rowIndex = 0;
    for (size_t colIndex = 0; colIndex < N; ++colIndex)
    {
        if (MakeRowClaimVariable(matrix, rowIndex, colIndex))
        {
            ++rowIndex;
            if (rowIndex == M)
                return;
        }
    }
}

/*
template <typename LAMBDA_FUNCTION, typename LAMBDA_CONSTRAINT, size_t N>
float Maximize_1Constraint(std::array<float, N>& result, LAMBDA_FUNCTION& function, LAMBDA_CONSTRAINT& constraint)
{

}
*/

int main(int argc, char** argv)
{

    // minimize y=x^2+3x-2, where x^2+y^2 = 1
    //
    // L(x,y) = x^2+3x-2 - L*(x^2+y^2-1)
    //
    // d/dx = 2x+3 - 2Lx
    // d/dy = 0 - 2Ly
    // d/dL = -x^2-y^2-1
    // 

    return 0;
}

/*

TODO:

? get gradient numerically? does that make sense?

* simpler function example

* could do ray vs sphere after
 * then some more complex shape?

* multiple constraints
* inequalities


BLOG:
* optimization but with a constraint
* link to gauss jordan elimination post: https://blog.demofox.org/2017/04/10/solving-n-equations-and-n-unknowns-the-fine-print-gauss-jordan-elimination/

NOTES:
* After setting up lagrane equation and solving for where gradient is 0, the Lagrange multiplier tells you how much the value grows when you change the constraint.
 * Seems likely only true for small values, cause its a derivative. Kinda cool though.


articles...
1) https://www.khanacademy.org/math/multivariable-calculus/applications-of-multivariable-derivatives/constrained-optimization/a/lagrange-multipliers-single-constraint
2) https://www.khanacademy.org/math/multivariable-calculus/applications-of-multivariable-derivatives/constrained-optimization/a/lagrange-multipliers-examples
3) https://www.khanacademy.org/math/multivariable-calculus/applications-of-multivariable-derivatives/constrained-optimization/a/interpretation-of-lagrange-multipliers


videos?
https://www.khanacademy.org/math/multivariable-calculus/applications-of-multivariable-derivatives/lagrange-multipliers-and-constrained-optimization/v/lagrange-multiplier-example-part-1

Multiple constraints video: https://youtu.be/qXhcpqslNUU
Inequalities: https://youtu.be/eREvLgRJWrE
 
 ! put a zz top picture at the top of the post

*/