
#pragma once

#include "Matrix.h"

template <typename T>
TMatrix<T>::TMatrix(size_t InRows,
                    size_t InCols)
    : Rows(InRows)
    , Cols(InCols)
    , Data(std::make_unique<std::unique_ptr<T[]>[]>(InRows))
{
    if (this->Rows == 0 || this->Cols == 0)
    {
        return;
    }

    // Allocate Columns for each Row
    for (size_t Row = 0; Row < this->Rows; ++Row) {
        this->Data[Row] = std::make_unique<T[]>(this->Cols);

        // Initialize all elements to zero
        for (size_t Col = 0; Col < this->Cols; ++Col) {
            this->Data[Row][Col] = static_cast<T>(0);
        }
    }
}

template <typename T>
TMatrix<T>::TMatrix(std::vector<std::vector<T>> InData)
{
    if (InData.empty() || InData[0].empty())
    {
        throw std::invalid_argument("InData must not be empty!");
    }

    this->Rows = InData.size();
    this->Cols = InData[0].size();
    this->Data = std::make_unique<std::unique_ptr<T[]>[]>(this->Rows);

    for (size_t Row = 0; Row < this->Rows; ++Row)
    {
        if (InData[Row].size() != this->Cols)
        {
            throw std::invalid_argument("All rows must have the same number of columns");
        }

        this->Data[Row] = std::make_unique<T[]>(this->Cols);
        for (size_t Col = 0; Col < this->Cols; ++Col)
        {
            this->Data[Row][Col] = InData[Row][Col];
        }
    }
}

template <typename T>
TMatrix<T>::TMatrix(TMatrix&& Other) noexcept
    : Rows(Other.Rows)
    , Cols(Other.Cols)
    , Data(std::move(Other.Data))
{
    Other.Rows = 0;
    Other.Cols = 0;
    Other.Data = nullptr;
}

template <typename T>
TMatrix<T>::TMatrix(const TMatrix& Other)
    : Rows(Other.Rows)
    , Cols(Other.Cols)
    , Data(std::make_unique<std::unique_ptr<T[]>[]>(Other.Rows))
{
    for (size_t Row = 0; Row < this->Rows; ++Row) {
        this->Data[Row] = std::make_unique<T[]>(this->Cols);

        for (size_t Col = 0; Col < this->Cols; ++Col)
        {
            this->Data[Row][Col] = Other.Data[Row][Col];
        }
    }
}

template <typename T>
TMatrix<T>::~TMatrix()
{
}

template <typename T>
TMatrix<T>& TMatrix<T>::operator=(TMatrix&& Other) noexcept
{
    if (this != &Other)
    {
        // Free current resources
        this->Data = nullptr;

        // Transfer ownership
        this->Rows = Other.Rows;
        this->Cols = Other.Cols;
        this->Data = std::move(Other.Data);

        // Nullify source
        Other.Rows = 0;
        Other.Cols = 0;
        Other.Data = nullptr;
    }
    return *this;
}

template <typename T>
TMatrix<T>& TMatrix<T>::operator=(const TMatrix<T>& Other)
{
    if (this == &Other)
    {
        return *this;
    }

    this->Rows = Other.Rows;
    this->Cols = Other.Cols;

    // Allocate new data
    this->Data = std::make_unique<std::unique_ptr<T[]>[]>(this->Rows);

    for (size_t Row = 0; Row < this->Rows; ++Row)
    {
        this->Data[Row] = std::make_unique<T[]>(this->Cols);
        for (size_t Col = 0; Col < this->Cols; ++Col)
        {
            this->Data[Row][Col] = Other.Data[Row][Col];
        }
    }

    return *this;
}

template <typename T>
T& TMatrix<T>::operator()(size_t Row, size_t Col)
{
    if (Row >= this->Rows || Col >= this->Cols)
    {
        throw std::out_of_range("Matrix indices out of bounds");
    }

    return this->Data[Row][Col];
}

template <typename T>
const T& TMatrix<T>::operator()(size_t Row, size_t Col) const
{
    if (Row >= this->Rows || Col >= this->Cols) {
        throw std::out_of_range("Matrix indices out of bounds");
    }
    return this->Data[Row][Col];
}

template <typename T>
TMatrix<T> TMatrix<T>::operator+(const TMatrix<T>& B)
{
    return TMatrix<T>::Add(*this, B);
}

template <typename T>
TMatrix<T> TMatrix<T>::operator-(const TMatrix<T>& B)
{
    return TMatrix<T>::Subtract(*this, B);
}

template <typename T>
TMatrix<T> TMatrix<T>::operator*(const TMatrix<T>& B)
{
    return TMatrix<T>::Multiply(*this, B);
}

template <typename T>
TMatrix<T>& TMatrix<T>::operator+=(const TMatrix<T>& B)
{
    if (this->Rows != B.Rows || this->Cols != B.Cols)
    {
        return *this;
    }

    for (size_t Row = 0; Row < this->Rows; Row++)
    {
        for (size_t Col = 0; Col < this->Cols; Col++)
        {
            this->Data[Row][Col] += B.Data[Row][Col];
        }
    }

    return *this;
}

template <typename T>
TMatrix<T> TMatrix<T>::operator*(T Multiplier)
{
    TMatrix<T> Result = *this;
    for (size_t Row = 0; Row < Result.Rows; Row++)
    {
        for (size_t Col = 0; Col < Result.Cols; Col++)
        {
            Result.Data[Row][Col] *= Multiplier;
        }
    }

    return Result;
}

template <typename T>
TMatrix<T>& TMatrix<T>::operator*=(T Multiplier)
{
    for (size_t Row = 0; Row < this->Rows; Row++)
    {
        for (size_t Col = 0; Col < this->Cols; Col++)
        {
            this->Data[Row][Col] *= Multiplier;
        }
    }

    return *this;
}

template <typename T>
bool TMatrix<T>::operator==(const TMatrix<T>& Other) const
{
    if (this->Rows != Other.Rows)
    {
        return false;
    }

    if (this->Cols != Other.Cols)
    {
        return false;
    }

    for (size_t Row = 0; Row < this->Rows; ++Row)
    {
        for (size_t Col = 0; Col < this->Cols; ++Col)
        {
            if (this->Data[Row][Col] != Other.Data[Row][Col])
            {
                return false;
            }
        }
    }

    return true;
}

template <typename T>
TMatrix<T> TMatrix<T>::Identity(size_t Order)
{
    if (Order <= 0)
    {
        throw("Order must be greater than zero when creating identity matrices!");
    }

    TMatrix<T> IMatrix(Order, Order);

    size_t Row = 0;
    size_t Col = 0;

    while (Row < Order && Col < Order)
    {
        IMatrix.Data[Row][Col] = 1;
        Row++;
        Col++;
    }

    return IMatrix;
}

template <typename T>
TMatrix<T> TMatrix<T>::Multiply(const TMatrix<T>& A,
                                const TMatrix<T>& B)
{
    // Num of elements in a row of (A) must equal the num of elements in a col of (B)
    if (A.Cols != B.Rows)
    {
        throw std::invalid_argument("Cols of matrix (A) must equal rows of matrix (B)");
    }

    TMatrix<T> Result(A.Rows, B.Cols);

    for (size_t Row = 0; Row < Result.Rows; Row++)
    {
        for (size_t Col = 0; Col < Result.Cols; Col++)
        {
            // (K) is the shared dimension (n) index which will go from 0 to (n) when computing each (AB)_ij for sum of
            // (A)_ik times (B)_kj
            for (size_t K = 0; K < A.Cols; K++)
            {
                Result.Data[Row][Col] += A.Data[Row][K] * B.Data[K][Col];
            }
        }
    }

    return Result;
}

template <typename T>
TMatrix<T> TMatrix<T>::Add(const TMatrix<T>& A,
                           const TMatrix<T>& B)
{
    // Both matrices must be of same dimensions
    if (A.Rows != B.Rows || A.Cols != B.Cols)
    {
        throw std::invalid_argument("Matrices must have the same dimensions for addition");
    }

    TMatrix<T> Result(A.Rows, A.Cols);

    for (size_t Row = 0; Row < Result.Rows; Row++)
    {
        for (size_t Col = 0; Col < Result.Cols; Col++)
        {
            Result.Data[Row][Col] = A.Data[Row][Col] + B.Data[Row][Col];
        }
    }

    return Result;
}

template <typename T>
TMatrix<T> TMatrix<T>::Subtract(const TMatrix<T>& A,
                                const TMatrix<T>& B)
{
    // Both matrices must be of same dimensions
    if (A.Rows != B.Rows || A.Cols != B.Cols)
    {
        throw std::invalid_argument("Matrices must have the same dimensions for subtraction");
    }

    TMatrix<T> Result(A.Rows, A.Cols);

    for (size_t Row = 0; Row < Result.Rows; Row++)
    {
        for (size_t Col = 0; Col < Result.Cols; Col++)
        {
            Result.Data[Row][Col] = A.Data[Row][Col] - B.Data[Row][Col];
        }
    }

    return Result;
}

template <typename T>
bool TMatrix<T>::IsCommutative(const TMatrix<T>& A,
                               const TMatrix<T>& B)
{
    TMatrix<T> AB = TMatrix<T>::Multiply(A, B);
    TMatrix<T> BA = TMatrix<T>::Multiply(B, A);

    return AB == BA;
}

template <typename T>
size_t TMatrix<T>::GetNumRows() const
{
    return this->Rows;
}

template <typename T>
size_t TMatrix<T>::GetNumCols() const
{
    return this->Cols;
}

template <typename T>
std::string TMatrix<T>::ToString() const
{
    std::string MatrixAsString;

    if (!this->Data)
    {
        return "";
    }

    for (size_t Row = 0; Row < this->Rows; ++Row) {
        if (!this->Data[Row])
        {
            return "";
        }

        MatrixAsString += "[";

        for (size_t Col = 0; Col < this->Cols; ++Col) {
            MatrixAsString += std::to_string(this->Data[Row][Col]);

            if (Col != this->Cols - 1)
            {
                MatrixAsString += " ";
            }
        }

        MatrixAsString += "]";

        if (Row != this->Rows - 1)
        {
            MatrixAsString += "\n";
        }
    }

    return MatrixAsString;
}

template <typename T>
TMatrix<T> TMatrix<T>::RowReduction() const
{
    if (Rows == 0 || Cols == 0)
    {
        return *this;
    }

    TMatrix<T> Result(*this);
    size_t Lead = 0;

    for (size_t Col = 0; Col < Result.Cols; ++Col)
    {
        // Find pivot
        size_t PivotRow = Lead;
        while (PivotRow < Result.Rows && abs(Result(PivotRow, Col)) < 1e-8)
        {
            PivotRow++;
        }

        if (PivotRow == Result.Rows)
        {
            continue;
        }

        // Swap rows if necessary
        if (PivotRow != Lead)
        {
            SwapRows(Result, Lead, PivotRow);
        }

        // Make pivot 1
        T Pivot = Result(Lead, Col);
        if (abs(Pivot) > 1e-8)
        {
            for (size_t C = Col; C < Result.Cols; ++C)
            {
                Result(Lead, C) /= Pivot;
            }
        }

        // Eliminate column
        for (size_t Row = 0; Row < Result.Rows; ++Row)
        {
            if (Row != Lead)
            {
                T Factor = Result(Row, Col);
                for (size_t C = Col; C < Result.Cols; ++C)
                {
                    Result(Row, C) -= Factor * Result(Lead, C);
                }
            }
        }

        Lead++;
        if (Lead >= Result.Rows)
        {
            break;
        }
    }

    return Result;
}

template <typename T>
T TMatrix<T>::Determinant() const
{
    if (!this->IsSquare())
    {
        throw std::invalid_argument("Matrix must be square to calculate its determinant!");
    }

    // 1x1
    if (this->Rows == 1)
    {
        return (*this)(0,0);
    }

    if (this->Rows == 2)
    {
        return (this->Data[0][0] * this->Data[1][1]) - (this->Data[1][0] * this->Data[0][1]);
    }

    // For larger matrices, use cofactor expansion along first row
    T Determinant = static_cast<T>(0);
    for (size_t j = 0; j < this->Cols; ++j)
    {
        // Create minor matrix
        TMatrix<T> minor(this->Rows - 1, this->Cols - 1);
        size_t minorRow = 0;

        // Copy elements to minor matrix
        for (size_t Row = 1; Row < this->Rows; ++Row)
        {
            size_t minorCol = 0;
            for (size_t k = 0; k < this->Cols; ++k)
            {
                if (k != j)
                {
                    minor(minorRow, minorCol) = (*this)(Row, k);
                    minorCol++;
                }
            }
            minorRow++;
        }

        // Calculate cofactor and add to determinant
        T cofactor = minor.Determinant();
        Determinant += static_cast<T>(pow(-1, j)) * (*this)(0, j) * cofactor;
    }

    return Determinant;
}

template <typename T>
T TMatrix<T>::Cofactor(size_t Row, size_t Col) const
{
    if (Row < 0 || Row >= this->Rows)
    {
        throw std::invalid_argument("Row is out of bounds!");
    }

    if (Col < 0 || Col >= this->Cols)
    {
        throw std::invalid_argument("Col is out of bounds!");
    }

    if (!this->IsSquare())
    {
        throw std::invalid_argument("Matrix must be square to get one of its cofactors!");
    }

    TMatrix<T> Minor(Rows - 1, Cols - 1);
    for (size_t i = 0, mi = 0; i < Rows; ++i)
    {
        if (i == Row) continue;
        for (size_t j = 0, mj = 0; j < Cols; ++j)
        {
            if (j == Col) continue;
            Minor(mi, mj) = Data[i][j];
            ++mj;
        }
        ++mi;
    }
    return ((Row + Col) % 2 == 0 ? 1 : -1) * Minor.Determinant();
}

template <typename T>
TMatrix<T> TMatrix<T>::Inverse() const
{
    // The inverse of a matrix (M^-1) is
    //
    // M^-1 = (1 / det(M)) * (C^T)
    //
    // M^-1: inverse of the matrix
    // M:    original matrix
    // C:    cofactor matrix
    // C^T:  transpose of the cofactor matrix


    if (!this->IsSquare())
    {
        throw std::invalid_argument("Only square matrices can have inverses!");
    }

    TMatrix<T> InverseMatrix(this->Rows, this->Cols);

    // STEP 1: Get the determinant of the matrix
    T Determinant = this->Determinant();

    // STEP 2: Get the cofactor matrix
    TMatrix<T> CofactorMatrix(this->Rows, this->Cols);

    for (size_t Row = 0; Row < this->Rows; Row++)
    {
        for (size_t Col = 0; Col < this->Cols; Col++)
        {
            CofactorMatrix.Data[Col][Row] = this->Cofactor(Row, Col);
        }
    }

    // STEP 3: Transpose the cofactor matrix
    TMatrix<T> TransposedCofactorMatrix = CofactorMatrix.Transposed();

    // STEP 4: Multiply one of the det of M by the transposed cofactor matrix
    InverseMatrix = TransposedCofactorMatrix * (1 / Determinant);

    return InverseMatrix;
}

template <typename T>
TMatrix<T> TMatrix<T>::Transposed() const
{
    // Remember: we are swapping rows with columns when transposing a matrix
    // Row(1) -> Col(1)
    // Row(2) -> Col(2)
    // ...    -> ...
    // Row(N) -> Col(N)
    TMatrix<T> Result(this->Cols, this->Rows);

    if (!this->Data)
    {
        return Result;
    }

    Result.Data = std::make_unique<std::unique_ptr<T[]>[]>(this->Cols);

    for (size_t Col = 0; Col < this->Cols; Col++)
    {
        Result.Data[Col] = std::make_unique<T[]>(this->Rows);

        for (size_t Row = 0; Row < this->Rows; Row++)
        {
            Result.Data[Col][Row] = this->Data[Row][Col];
        }
    }

    return Result;
}

template <typename T>
bool TMatrix<T>::IsSquare() const
{
    return this->Rows == this->Cols;
}

template <typename T>
void TMatrix<T>::NormalizeRow(TMatrix<T>& Matrix, size_t Row, const T& PivotValue)
{
    for (size_t Col = 0; Col < Matrix.Rows; ++Col) {
        Matrix(Row, Col) /= PivotValue;
    }
}

template <typename T>
void TMatrix<T>::EliminateBelow(TMatrix<T>& Matrix, size_t TargetRow, size_t PivotRow, const T& Factor) {
    for (size_t Col = 0; Col < Matrix.Cols; ++Col) {
        Matrix(TargetRow, Col) -= Factor * Matrix(PivotRow, Col);
    }
}

template <typename T>
void TMatrix<T>::SwapRows(TMatrix<T>& Matrix, size_t FirstRow, size_t SecondRow)
{
    if (!Matrix.Data)
    {
        return;
    }

    if (FirstRow < 0 || FirstRow >= Matrix.Rows)
    {
        return;
    }

    if (SecondRow < 0 || SecondRow >= Matrix.Rows)
    {
        return;
    }

    if (FirstRow == SecondRow)
    {
        return;
    }

    std::swap(Matrix.Data[FirstRow], Matrix.Data[SecondRow]);
}