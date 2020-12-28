#include "pch.h"
#include "CppUnitTest.h"
#include "../lab12.10/lab12_10.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1210
{
	TEST_CLASS(UnitTest1210)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			Node* root = NULL;
			int t;
			t = Height(root);
			Assert::AreEqual(t, 0);
		}
	};
}