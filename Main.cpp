#include <Windows.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <iostream>

//using namespace std;
//using namespace DirectX;
//using namespace DirectX::PackedVector;

std::ostream& XM_CALLCONV operator<<(std::ostream& os, DirectX::FXMVECTOR v);
int SENTINEL = -99;
#pragma region Vector Algebra
void VectorSetter();
void VectorFunctions();
#pragma endregion

int main()
{
	std::cout.setf(std::ios_base::boolalpha);
	if (!DirectX::XMVerifyCPUSupport())
	{
		std::cout << "DirectX math not supported" << std::endl;
		return 0;
	}

	int input;
	do 
	{
		std::cout << "Input: ";
		std::cin >> input;
		switch (input)
		{
		case 1:
			VectorSetter();
			break;
		case 2:
			VectorFunctions();
			break;
		default:
			std::cout << "Invalid input!\nType -99 to end\n";
			break;
		}
	} while (input != SENTINEL);

	return 0;
}

std::ostream& XM_CALLCONV operator<<(std::ostream& os, DirectX::FXMVECTOR v)
{
	DirectX::XMFLOAT3 dest;
	DirectX::XMStoreFloat3(&dest, v);

	os << "(" << dest.x << ", " << dest.y << ", " << dest.z << ")";
	return os;
}

void VectorSetter()
{
	DirectX::XMVECTOR p = DirectX::XMVectorZero();
	DirectX::XMVECTOR q = DirectX::XMVectorSplatOne();
	DirectX::XMVECTOR u = DirectX::XMVectorSet(1.0f, 2.0f, 3.0f, 0.0f);
	DirectX::XMVECTOR v = DirectX::XMVectorReplicate(-2.0f);
	DirectX::XMVECTOR w = DirectX::XMVectorSplatZ(u);

	std::cout << "p = " << p << std::endl;
	std::cout << "q = " << q << std::endl;
	std::cout << "u = " << u << std::endl;
	std::cout << "v = " << v << std::endl;
	std::cout << "w = " << w << std::endl;
}

void VectorFunctions()
{
	DirectX::XMVECTOR n = DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	DirectX::XMVECTOR u = DirectX::XMVectorSet(1.0f, 2.0f, 3.0f, 0.0f);
	DirectX::XMVECTOR v = DirectX::XMVectorSet(-2.0f, 1.0f, -3.0f, 0.0f);
	DirectX::XMVECTOR w = DirectX::XMVectorSet(0.707f, 0.707f, 0.0f, 0.0f);

	DirectX::XMVECTOR a = DirectX::XMVectorAdd(u, v);
	DirectX::XMVECTOR b = DirectX::XMVectorSubtract(u, v);
	DirectX::XMVECTOR c = DirectX::operator*(10.0f, u);
	DirectX::XMVECTOR L = DirectX::XMVector3Length(u);
	DirectX::XMVECTOR d = DirectX::XMVector3Normalize(u);
	DirectX::XMVECTOR s = DirectX::XMVector3Dot(u, v);
	DirectX::XMVECTOR e = DirectX::XMVector3Cross(u, v);

	DirectX::XMVECTOR projW, perpW;
	DirectX::XMVector3ComponentsFromNormal(&projW, &perpW, w, n);

	bool equal = DirectX::XMVector3Equal(DirectX::XMVectorAdd(projW, perpW), w) != 0;
	bool notEqual = DirectX::XMVector3NotEqual(DirectX::XMVectorAdd(projW, perpW), w) != 0;

	DirectX::XMVECTOR angleVec = DirectX::XMVector3AngleBetweenVectors(projW, perpW);
	float angleRadians = DirectX::XMVectorGetX(angleVec);
	float angleDegrees = DirectX::XMConvertToDegrees(angleRadians);

	std::cout << "u \t = " << u << std::endl;
	std::cout << "v \t = " << v << std::endl;
	std::cout << "w \t = " << w << std::endl;
	std::cout << "n \t = " << n << std::endl;
	std::cout << "Vector Addition: " << a << std::endl;
	std::cout << "Vector Subtraction: " << b << std::endl;
	std::cout << "Vector Multiplication: " << c << std::endl;
	std::cout << "Vector Length: " << L << std::endl;
	std::cout << "Vector Normalize: " << d << std::endl;
	std::cout << "Vector Dot Product: " << s << std::endl;
	std::cout << "Vector Cross Product: " << e << std::endl;
	std::cout << "projW \t = " << projW << std::endl;
	std::cout << "perpW \t = " << perpW << std::endl;
	std::cout << "projW + perpW == w = " << equal << std::endl;
	std::cout << "projW + perpW != w = " << notEqual << std::endl;
	std::cout << "angle \t = " << angleDegrees << std::endl;
}