#define CATCH_CONFIG_MAIN

#include <catch2/catch_test_macros.hpp>

#include <Matrix.h>

TEST_CASE("TMatrix construction", "[Matrix][constructor]")
{
    TMatrix<int> M(2, 2);

    REQUIRE(M.GetNumRows() == 2);
    REQUIRE(M.GetNumCols() == 2);
}

TEST_CASE("TMatrix identity", "[Matrix][identity]")
{
    TMatrix<float> IdentityMatrix3 = TMatrix<float>::Identity(3);

    REQUIRE(IdentityMatrix3(0,0) == 1.0f);
    REQUIRE(IdentityMatrix3(1,1) == 1.0f);
    REQUIRE(IdentityMatrix3(2,2) == 1.0f);
    REQUIRE(IdentityMatrix3(0,1) == 0.0f);
}

TEST_CASE("Add 2 matrices", "[Matrix][add]")
{
    static std::vector<std::vector<int>> TestMatrix1Data = {{1, 3, -2},
                                                            {4, 7, 1}};

    static std::vector<std::vector<int>> TestMatrix2Data = {{2, -1, 4},
                                                            {3, -7, -2}};

    TMatrix<int> TestMatrix1(TestMatrix1Data);
    TMatrix<int> TestMatrix2(TestMatrix2Data);

    TMatrix<int> Result = TestMatrix1 + TestMatrix2;

    REQUIRE(Result.GetNumRows() == 2);
    REQUIRE(Result.GetNumCols() == 3);

    // Row 0
    REQUIRE(Result(0,0) == 3);
    REQUIRE(Result(0,1) == 2);
    REQUIRE(Result(0,2) == 2);

    // Row 1
    REQUIRE(Result(1,0) == 7);
    REQUIRE(Result(1,1) == 0);
    REQUIRE(Result(1,2) == -1);
}

TEST_CASE("Multiply a TMatrix by a number", "[Matrix][Multiply]")
{
    static std::vector<std::vector<int>> TestMatrixData = {{1, 2, 2},
                                                           {0, 5, 7},
                                                           {1, 1, 1}};

    int Multiplier = 2;
    TMatrix<int> TestMatrix(TestMatrixData);

    TMatrix<int> Result = TestMatrix * Multiplier;

    // Row 0
    REQUIRE(Result(0,0) == 2);
    REQUIRE(Result(0,1) == 4);
    REQUIRE(Result(0,2) == 4);

    // Row 1
    REQUIRE(Result(1,0) == 0);
    REQUIRE(Result(1,1) == 10);
    REQUIRE(Result(1,2) == 14);

    // Row 2
    REQUIRE(Result(2,0) == 2);
    REQUIRE(Result(2,1) == 2);
    REQUIRE(Result(2,2) == 2);
}

TEST_CASE("Multiply a TMatrix by another", "[Matrix][Multiply]")
{
    static std::vector<std::vector<int>> TestMatrix1Data = {{4, 2},
                                                            {-3, 1}};

    static std::vector<std::vector<int>> TestMatrix2Data = {{1, 5, 3},
                                                            {2, 7, -4}};

    TMatrix<int> TestMatrix1(TestMatrix1Data);
    TMatrix<int> TestMatrix2(TestMatrix2Data);

    TMatrix<int> Result = TestMatrix1 * TestMatrix2;

    REQUIRE(Result.GetNumRows() == 2);
    REQUIRE(Result.GetNumCols() == 3);

    // Row 0
    REQUIRE(Result(0,0) == 8);
    REQUIRE(Result(0,1) == 34);
    REQUIRE(Result(0,2) == 4);

    // Row 1
    REQUIRE(Result(1,0) == -1);
    REQUIRE(Result(1,1) == -8);
    REQUIRE(Result(1,2) == -13);
}

TEST_CASE("Matrix multiplication throws on invalid dimensions", "[Matrix][Multiply][Exception]") {
    TMatrix<int> A(2, 3); // 2x3
    TMatrix<int> B(2, 2); // 2x2 — incompatible with A

    REQUIRE_THROWS_AS(TMatrix<int>::Multiply(A, B), std::invalid_argument);
}

TEST_CASE("Matrices are commutative", "[Matrix][IsCommutative]") {
    TMatrix<int> A({{2, 1},
                    {0, 2}});

    TMatrix<int> B({{3, 4},
                    {0, 3}});

    REQUIRE(TMatrix<int>::IsCommutative(A, B) == true);
}

TEST_CASE("Matrices are not commutative", "[Matrix][IsCommutative]") {
    TMatrix<int> A({{1, 1},
                    {4, 2}});

    TMatrix<int> B({{2, 4},
                    {8, 1}});

    REQUIRE(TMatrix<int>::IsCommutative(A, B) == false);
}
