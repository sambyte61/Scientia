
#pragma once

#include <cmath>
#include <cstddef>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <vector>
#include <memory>

template <typename T>
class TMatrix
{
public:
    /**
     * @brief       Construct a new TMatrix object (empty)
     *
     * @param[in]   InRows  Num of rows
     * @param[in]   InCols  Num of cols
     */
    TMatrix(size_t InRows = 0,
            size_t InCols = 0);

    /**
     * @brief       Construct a new TMatrix object (from a data source)
     *
     * @param[in]   InData  Data source to build the matrix from. Each row and col *MUST* be the same size!
     */
    TMatrix(std::vector<std::vector<T>> InData);

    /**
     * @brief       Construct a new TMatrix object (Copy Constructor)
     *
     * @param[in]   Other   Other TMatrix to copy from
     */
    TMatrix(const TMatrix& Other);

    /**
     * @brief       Construct a new TMatrix object (Move Constructor)
     *
     * @param[in]   Other   Other matrix to move the data from into this one
     *
     * @return      New matrix with the moved data
     */
    TMatrix(TMatrix&& Other) noexcept;

    ~TMatrix();

    /**
     * @brief       Assign the value of this matrix (Move assignment operator)
     *
     * @param[in]   Other   Other matrix to move the data from into this one
     *
     * @return      Matrix with moved data
     */
    TMatrix<T>& operator=(TMatrix&& Other) noexcept;

    // Deep Copy assignment op
    TMatrix<T>& operator=(const TMatrix<T>& Other);

    // Element access operator
    T& operator()(size_t Row, size_t Col);

    const T& operator()(size_t Row, size_t Col) const;

    TMatrix<T> operator+(const TMatrix<T>& B);
    TMatrix<T> operator-(const TMatrix<T>& B);
    TMatrix<T> operator*(const TMatrix<T>& B);
    TMatrix<T> operator*(T Multiplier);

    TMatrix<T>& operator+=(const TMatrix<T>& B);
    TMatrix<T>& operator*=(T Multiplier);

    bool operator==(const TMatrix<T>& Other) const;

    /**
     * Create an identity matrix
     *
     * @param[in]   Order   Specifies the size of the square matrix (equal to the num of rows and cols). An order of 3
     *                      would result in a (3x3) identity matrix
     *
     * @return      Identity matrix of size (nxn) dictated by Order
     */
    static TMatrix<T> Identity(size_t Order);

    static bool IsCommutative(const TMatrix<T>& A,
                              const TMatrix<T>& B);

    size_t GetNumRows() const;

    size_t GetNumCols() const;

    std::string ToString() const;

    TMatrix<T> RowReduction() const;

    T Determinant() const;

    T Cofactor(size_t Row, size_t Col) const;

    TMatrix<T> Inverse() const;

    /**
     * @brief   Get a transposed version of this matrix (The rows and cols are swapped)
     *
     * @return  Transposed version of this matrix
     */
    TMatrix<T> Transposed() const;

    bool IsSquare() const;

    /**
     * Multiply matrix (A) by matrix (B)
     *
     * @param[in]   A       First matrix (m x n)
     * @param[in]   B       Second matrix (n x p)
     * @param[out]  Result  Product matrix of (AB) (m x p)
     *
     * @note    ORDER MATTERS! AB is not always equal to BA when multiplying matrices.
     *
     *          Num of elements of the rows of matrix (A) must equal the number of elements in the cols of matrix (B)
     *          for the multiplication to be performed
     *
     * @return
     */
    static TMatrix<T> Multiply(const TMatrix<T>& A,
                               const TMatrix<T>& B);

    static TMatrix<T> Add(const TMatrix<T>& A,
                          const TMatrix<T>& B);

    static TMatrix<T> Subtract(const TMatrix<T>& A,
                               const TMatrix<T>& B);

private:
    // Helper function for normalizing a row
    static void NormalizeRow(TMatrix<T>& Matrix, size_t Row, const T& PivotValue);

    // Helper function for eliminating entries below pivot
    static void EliminateBelow(TMatrix<T>& Matrix, size_t TargetRow, size_t PivotRow, const T& Factor);

    static void SwapRows(TMatrix<T>& Matrix, size_t FirstRow, size_t SecondRow);

    std::unique_ptr<std::unique_ptr<T[]>[]> Data;

    size_t Rows;

    size_t Cols;
};

#include "Matrix.inl"
