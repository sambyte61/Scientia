
#include <cmath>
#include <string>

template <typename T>
class TVector3
{
public:
    TVector3()
        : X(0)
        , Y(0)
        , Z(0)
    {
    };

    TVector3(T InX, T InY, T InZ)
        : X(InX)
        , Y(InY)
        , Z(InZ)
    {
    };

    static T DotProduct(const TVector3& A, const TVector3& B)
    {
        // A (dot) B = |A||B|cos(theta) = Ax*Bx + Ay*By + Az*Bz
        return (A.X * B.X) + (A.Y * B.Y) + (A.Z * B.Z);
    };

    static TVector3 CrossProduct(const TVector3& A, const TVector3& B)
    {
        // A x B = i(AyBz - AzBy) + j(AzBx - AxBz) + k(AxBy - AyBz)
        return TVector3((A.Y * B.Z) - (A.Z * B.Y),
                        (A.Z * B.X) - (A.X * B.Z),
                        (A.X * B.Y) - (A.Y * B.X));
    };

    T Length()
    {
        return std::sqrt(std::pow(this->X, 2) + std::pow(this->Y, 2) + std::pow(this->Z, 2));
    }

    std::string ToString()
    {
        std::string String;

        String += "(X:" + std::to_string(this->X);
        String += ",Y:" + std::to_string(this->Y);
        String += ",Z:" + std::to_string(this->Z) + ")";

        return String;
    }

    T X;

    T Y;

    T Z;
};

using FVector = TVector3<float>;
using IVector = TVector3<int>;

