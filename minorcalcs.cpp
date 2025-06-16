/*
    This file has purpose to join all together minor calcs needed by this programm.
*/

inline double det(double **mat, unsigned int N)
{
    double main, side;
    if (N == 3) // Matrix 3x3
    {
        main = mat[0][0] * mat[1][1] * mat[2][2] + mat[1][0] * mat[2][1] * mat[0][2] + mat[2][0] * mat[0][1] * mat[1][2];
        side = mat[0][2] * mat[1][1] * mat[2][0] + mat[0][0] * mat[2][1] * mat[1][2] + mat[1][0] * mat[0][1] * mat[2][2];
    }
    else if (N == 2) // Matrix 2x2
    {
        main = mat[0][0] * mat[1][1];
        side = mat[0][1] * mat[1][0];
    }
    else throw "Incomplete size of matrix or null matrix in 'det'.";
    return (main - side);
}
