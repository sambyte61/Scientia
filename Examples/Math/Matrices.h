#include <iostream>

#include "Matrix.h"
#include "Utils.h"

void RunMatrixExample()
{
    {
        std::vector<std::vector<float>> MatrixData = {{1.0, 2.0, -1.0, 4.0},
                                                      {2.0, 0.0, -1.0, 1.0},
                                                      {1.0, -2.0, 0.0, -3.0}};
        TMatrix<float> Matrix(MatrixData);

        std::cout << std::endl;
        std::cout << "Matrix" << std::endl << Matrix.ToString() << std::endl << std::endl;
        TMatrix<float> RowReducedMatrix = Matrix.RowReduction();
        std::cout << "Matrix (Row-Reduced)" << std::endl << RowReducedMatrix.ToString() << std::endl << std::endl;
    }

    {
        std::vector<std::vector<float>> MatrixData = {{2.0, 0.0, -1.0, 2.0},
                                                      {6.0, 5.0, 3.0, 7.0},
                                                      {2.0, -1.0, 0.0, 4.0}};
        TMatrix<float> Matrix(MatrixData);

        std::cout << std::endl;
        std::cout << "Matrix" << std::endl << Matrix.ToString() << std::endl << std::endl;
        TMatrix<float> RowReducedMatrix = Matrix.RowReduction();
        std::cout << "Matrix (Row-Reduced)" << std::endl << RowReducedMatrix.ToString() << std::endl << std::endl;
    }

    {
        std::vector<std::vector<float>> MatrixData = {{1.0, 1.0, 2.0},
                                                      {1.0, 1.0, 5.0}};
        TMatrix<float> Matrix(MatrixData);

        std::cout << std::endl;
        std::cout << "Matrix" << std::endl << Matrix.ToString() << std::endl << std::endl;
        TMatrix<float> RowReducedMatrix = Matrix.RowReduction();
        std::cout << "Matrix (Row-Reduced)" << std::endl << RowReducedMatrix.ToString() << std::endl << std::endl;
    }

    {
        std::vector<std::vector<float>> MatrixData = {{1.0, 1.0, -1.0, 7.0},
                                                      {2.0, -1.0, -5.0, 2.0},
                                                      {-5.0, 4.0, 14.0, 1.0},
                                                      {3.0, -1.0, -7.0, 5.0}};
        TMatrix<float> Matrix(MatrixData);

        std::cout << std::endl;
        std::cout << "Matrix" << std::endl << Matrix.ToString() << std::endl << std::endl;
        TMatrix<float> RowReducedMatrix = Matrix.RowReduction();
        std::cout << "Matrix (Row-Reduced)" << std::endl << RowReducedMatrix.ToString() << std::endl << std::endl;
    }

    {
        std::vector<std::vector<float>> MatrixData = {{1.0, 2.0, 2.0},
                                                      {0.0, 5.0, 7.0},
                                                      {1.0, 1.0, 1.0}};
        TMatrix<float> Matrix(MatrixData);

        std::cout << std::endl << "Matrix" << std::endl << Matrix.ToString() << std::endl << std::endl;
        std::cout << "Determinant: " << Matrix.Determinant() << std::endl << std::endl;
    }

    {
        std::vector<std::vector<int>> Matrix1Data = {{1, 2, 2},
                                                     {0, 5, 7},
                                                     {1, 1, 1}};

        TMatrix<int> Matrix1(Matrix1Data);

        std::vector<std::vector<int>> Matrix2Data = {{1, 1, 1},
                                                     {1, 1, 1},
                                                     {1, 1, 1}};

        TMatrix<int> Matrix2(Matrix2Data);

        std::cout << std::endl << "Matrix Addition" << std::endl;
        std::cout << std::endl << "Matrix 1" << std::endl << Matrix1.ToString() << std::endl << std::endl;
        std::cout << std::endl << "Matrix 2" << std::endl << Matrix2.ToString() << std::endl << std::endl;

        Matrix1 += Matrix2;
        std::cout << "Result: " << std::endl << Matrix1.ToString() << std::endl << std::endl;
    }

    // Multiplying a matrix by a number
    {
        std::vector<std::vector<int>> Matrix1Data = {{1, 2, 2},
                                                     {0, 5, 7},
                                                     {1, 1, 1}};

        TMatrix<int> Matrix1(Matrix1Data);
        int Multiplier = 5;

        std::cout << std::endl << "Multiplying a matrix by a number" << std::endl;
        printf("Multiplier: %i\n", Multiplier);
        printf("Matrix 1:\n%s\n", Matrix1.ToString().c_str());

        TMatrix<int> MatrixResult = Matrix1 * Multiplier;

        printf("Matrix 1 (result):\n%s\n", MatrixResult.ToString().c_str());
    }

    // Multiplication of 2 matrices
    {
        std::vector<std::vector<int>> Matrix1Data = {{4, 2},
                                                     {-3, 1}};

        TMatrix<int> Matrix1(Matrix1Data);

        std::vector<std::vector<int>> Matrix2Data = {{1, 5, 3},
                                                     {2, 7, -4}};

        TMatrix<int> Matrix2(Matrix2Data);

        printf("\n");
        printf("-----------------------------\n");
        printf("Multiplication of 2 matrices\n");
        printf("-----------------------------\n");
        printf("Matrix 1:\n%s\n\n", Matrix1.ToString().c_str());
        printf("Matrix 2:\n%s\n\n", Matrix2.ToString().c_str());

        TMatrix<int> MatrixResult = TMatrix<int>::Multiply(Matrix1, Matrix2);

        printf("Matrix (result):\n%s\n\n", MatrixResult.ToString().c_str());
    }

    // Check if 2 matrices are commutative (example when they are)
    {
        std::vector<std::vector<int>> Matrix1Data = {{2, 1},
                                                     {0, 2}};

        TMatrix<int> Matrix1(Matrix1Data);

        std::vector<std::vector<int>> Matrix2Data = {{3, 4},
                                                     {0, 3}};

        TMatrix<int> Matrix2(Matrix2Data);

        printf("\n");
        printf("-----------------------------\n");
        printf("Are 2 Matrices Commutative?\n");
        printf("-----------------------------\n");
        printf("Matrix 1:\n%s\n\n", Matrix1.ToString().c_str());
        printf("Matrix 2:\n%s\n\n", Matrix2.ToString().c_str());

        printf("Matrices \"%s\" commutative:\n", TMatrix<int>::IsCommutative(Matrix1, Matrix2) ? "are" : "are not");
    }

    // Check if 2 matrices are commutative (example when they are NOT)
    {
        std::vector<std::vector<int>> Matrix1Data = {{1, 1},
                                                     {4, 2}};

        TMatrix<int> Matrix1(Matrix1Data);

        std::vector<std::vector<int>> Matrix2Data = {{2, 4},
                                                     {8, 1}};

        TMatrix<int> Matrix2(Matrix2Data);

        printf("\n");
        printf("-----------------------------\n");
        printf("Are 2 Matrices Commutative?\n");
        printf("-----------------------------\n");
        printf("Matrix 1:\n%s\n\n", Matrix1.ToString().c_str());
        printf("Matrix 2:\n%s\n\n", Matrix2.ToString().c_str());

        printf("Matrices \"%s\" commutative:\n", TMatrix<int>::IsCommutative(Matrix1, Matrix2) ? "are" : "are not");
    }

    // Create identity matrices
    {
        std::vector<std::vector<int>> Matrix1Data = {{2, -4},
                                                     {1, -2}};

        TMatrix<int> Matrix1(Matrix1Data);

        printf("\n");
        printf("-----------------\n");
        printf("Identity Matrices\n");
        printf("-----------------\n");
        printf("\n");

        TMatrix<int> I1 = TMatrix<int>::Identity(1);
        TMatrix<int> I2 = TMatrix<int>::Identity(2);
        TMatrix<int> I3 = TMatrix<int>::Identity(3);
        TMatrix<int> I4 = TMatrix<int>::Identity(4);

        printf("Identity Matrix (Order 1):\n%s\n\n", I1.ToString().c_str());
        printf("Identity Matrix (Order 2):\n%s\n\n", I2.ToString().c_str());
        printf("Identity Matrix (Order 3):\n%s\n\n", I3.ToString().c_str());
        printf("Identity Matrix (Order 4):\n%s\n\n", I4.ToString().c_str());

        printf("det(I) (Order 1): %i\n", I1.Determinant());
        printf("det(I) (Order 2): %i\n", I2.Determinant());
        printf("det(I) (Order 3): %i\n", I3.Determinant());
        printf("det(I) (Order 4): %i\n", I4.Determinant());
    }

    // Determinant Multiplication Proof
    {
        std::vector<std::vector<int>> MatrixAData = {{3, -1},
                                                     {-4, 2}};

        TMatrix<int> MatrixA(MatrixAData);

        std::vector<std::vector<int>> MatrixBData = {{5, 2},
                                                     {-7, 3}};

        TMatrix<int> MatrixB(MatrixBData);

        printf("\n");
        printf("--------------------------------\n");
        printf("Determinant Multiplication Proof\n");
        printf("--------------------------------\n");
        printf("\n");

        printf("Verify that det(AB) = det(BA) = (det(A) * det(B))\n\n");

        printf("Matrix (A):\n%s\n\n", MatrixA.ToString().c_str());
        printf("Matrix (B):\n%s\n\n", MatrixB.ToString().c_str());

        TMatrix<int> MatrixAB = TMatrix<int>::Multiply(MatrixA, MatrixB);
        TMatrix<int> MatrixBA = TMatrix<int>::Multiply(MatrixB, MatrixA);

        printf("Matrix (AB):\n%s\n\n", MatrixAB.ToString().c_str());
        printf("Matrix (BA):\n%s\n\n", MatrixBA.ToString().c_str());

        printf("Det (AB): %i\n", MatrixAB.Determinant());
        printf("Det (BA): %i\n", MatrixBA.Determinant());
        printf("Det (A) * Det (B): %i\n", MatrixA.Determinant() * MatrixB.Determinant());
    }

    // Finding the inverse of a matrix
    {
        std::vector<std::vector<int>> MatrixAData = {{1, 5, 3},
                                                     {2, 7, -4},
                                                     {3, 2, -1}};

        TMatrix<int> MatrixA(MatrixAData);

        printf("\n");
        printf("--------------------------------\n");
        printf("Finding the inverse of a matrix\n");
        printf("--------------------------------\n");
        printf("\n");

        printf("Matrix (A):\n%s\n\n", MatrixA.ToString().c_str());

        TMatrix<int> InverseMatrixA = MatrixA.Inverse();

        printf("Inverse (A):\n%s\n\n", InverseMatrixA.ToString().c_str());
    }
}
