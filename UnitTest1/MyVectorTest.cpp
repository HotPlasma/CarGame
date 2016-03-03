#include "stdafx.h"
#include "CppUnitTest.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Vector.h"


////////////////////////////////////////////////////////////
//
// PLEASE USE DEBUG MODE FOR RUNNING
// UNIT TESTS!!
//
////////////////////////////////////////////////////////////
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

myVector VectorA(200, 200);
myVector VectorB(200, 200);

namespace GameTest
{
	TEST_CLASS(GameTestClass)
	{
	public:
		

		TEST_METHOD(myVectorReturningValues)
		{
			// Valid
			Assert::AreEqual(VectorA.x(), 200, 0);
			Assert::AreEqual(VectorA.y(), 200, 0);

			// Invalid
			Assert::AreNotEqual(VectorA.x(), 300, 0);
			Assert::AreNotEqual(VectorA.y(), 9000, 0);
		}
		TEST_METHOD(myVectorAddition)
		{
			myVector VectorC = VectorA.add(VectorB);

			// Valid
			Assert::AreEqual(VectorC.x(), 400, 0);
			Assert::AreEqual(VectorC.y(), 400, 0);

			// Invalid
			Assert::AreNotEqual(VectorC.x(), 200, 0);
			Assert::AreNotEqual(VectorC.y(), 200, 0);
		}
		TEST_METHOD(myVectorSubtract)
		{
			myVector VectorC = VectorA.subtract(VectorB);

			// Valid
			Assert::AreEqual(VectorC.x(), 0, 0);
			Assert::AreEqual(VectorC.y(), 0, 0);

			//Invalid
			Assert::AreNotEqual(VectorC.x(), 600, 0);
			Assert::AreNotEqual(VectorC.y(), 500, 0);
		}
		TEST_METHOD(myVectorMultiplyVector)
		{
			myVector VectorC = VectorA.multiply(VectorB);
			// Valid
			Assert::AreEqual(VectorC.x(), 40000, 0);
			Assert::AreEqual(VectorC.y(), 40000, 0);

			//Invalid
			Assert::AreNotEqual(VectorC.x(), 3000, 0);
			Assert::AreNotEqual(VectorC.y(), 700, 0);
		}
		TEST_METHOD(myVectorMultiplyScalar)
		{
			myVector VectorC = VectorA.multiply(5);
			// Valid
			Assert::AreEqual(VectorC.x(), 1000, 0);
			Assert::AreEqual(VectorC.y(), 1000, 0);

			//Invalid
			Assert::AreNotEqual(VectorC.x(), 600, 0);
			Assert::AreNotEqual(VectorC.y(), 500, 0);
		}
		TEST_METHOD(myVectorDotProduct)
		{
			double Dotproduct = VectorA.dotProduct(VectorB);
			// Valid
			Assert::AreEqual(Dotproduct, 80000, 0);

			//Invalid
			Assert::AreNotEqual(Dotproduct, 100, 0);
		}
		TEST_METHOD(myVectorMagnitude)
		{
			float Magnitude = VectorA.magnitude();
			// Valid
			Assert::AreEqual(Magnitude, 282, 1);

			//Invalid
			Assert::AreNotEqual(Magnitude, 100, 0);
		}
		TEST_METHOD(myVectorNormalise)
		{
			myVector NormalisedA = myVector::normalise(VectorA);
			// Valid
			Assert::AreEqual(NormalisedA.x(), 0, 1);
			Assert::AreEqual(NormalisedA.y(), 0, 1);

			// Invalid
			Assert::AreNotEqual(NormalisedA.x(), 500, 1);
			Assert::AreNotEqual(NormalisedA.y(), 400, 1);
		}
		TEST_METHOD(myVectorConvert2f)
		{
			Vector2f ConvertedVect = VectorA.Convert2f();
			// Valid
			Assert::AreEqual(ConvertedVect.x, 200, 0);
			Assert::AreEqual(ConvertedVect.y, 200, 0);

			// Invalid
			Assert::AreNotEqual(ConvertedVect.x, 5000, 1);
			Assert::AreNotEqual(ConvertedVect.x, 700, 1);
		}
		TEST_METHOD(myVectorConvertToMyVector)
		{
			Vector2f Vector(200, 200);
			myVector ConvertedVect = myVector::ConvertToMyVector(Vector);
			// Valid
			Assert::AreEqual(ConvertedVect.x(), 200, 0);
			Assert::AreEqual(ConvertedVect.y(), 200, 0);

			// Invalid
			Assert::AreNotEqual(ConvertedVect.x(), 5000, 1);
			Assert::AreNotEqual(ConvertedVect.x(), 700, 1);
		}
		TEST_METHOD(myVectorMakeNegative)
		{
			myVector VectorANeg = VectorA.MakeNegetive();
			// Valid
			Assert::AreEqual(VectorANeg.x(), -200, 0);
			Assert::AreEqual(VectorANeg.y(), -200, 0);

			// Invalid
			Assert::AreNotEqual(VectorANeg.x(), 200, 1);
			Assert::AreNotEqual(VectorANeg.x(), 200, 1);
		}
		TEST_METHOD(myVectorRotate)
		{
			myVector VectorARot = VectorA.RotateVector(10);
			// Valid
			Assert::AreEqual(VectorARot.x(),162, 10);
			Assert::AreEqual(VectorARot.y(), 231, 10);

			// Invalid
			Assert::AreNotEqual(VectorARot.x(), 7500, 0);
			Assert::AreNotEqual(VectorARot.x(), 0, 0);
		}
	};
}