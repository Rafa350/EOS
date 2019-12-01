#include "CppUnitTest.h"
#include "eos.h"
#include "OSAL/osalHeap.h"
#include "System/Collections/eosArrayList.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace eos;


namespace UnitTestArrayList {
	
	TEST_CLASS(UnitTestArrayList) {
	public:

		TEST_METHOD(getCount) {

			ArrayList<int> list;
			for (int i = 0; i < 100; i++)
				list.add(i + 100);

			Assert::AreEqual(double(100), double(list.getCount()), double(0));
		}

		TEST_METHOD(getCapacity) {

			ArrayList<int> list;

			Assert::AreEqual(double(0), double(list.getCapacity()), double(0));
			list.add(1);
			Assert::AreEqual(double(5), double(list.getCapacity()), double(0));

		}
		
		TEST_METHOD(add) {

			ArrayList<int> list;
			for (int i = 0; i < 12; i++)
				list.add(i + 100);

			for (int i = 0; i < list.getCount(); i++) {
				Assert::AreEqual(double(i + 100), double(list[i]), double(0), nullptr);
			}
		}

		TEST_METHOD(remove) {

			ArrayList<int> list;
			for (int i = 0; i < 12; i++)
				list.add(i + 100);
			for (int i = 0; i < 12; i += 2)
				list.remove(i + 100);

			for (int i = 0; i < list.getCount(); i++) {
				Assert::AreEqual(double(i + i + 101), double(list[i]), double(0), nullptr);
			}
		}

		TEST_METHOD(insertAt) {

			ArrayList<int> list;

			// Inserta al principi amb la lista buida
			//
			list.insertAt(0, 100);
			Assert::AreEqual(double(100), double(list[0]), double(0));

			// Insercions pel centre 
			//
			for (int i = 0; i < 15; i++) {
				list.insertAt(1, i + 200);
				Assert::AreEqual(double(i + 200), double(list[1]), double(0));
			}

			// Insercio al final
			//
			list.insertAt(list.getCount(), 300);
			Assert::AreEqual(double(300), double(list[list.getCount() - 1]), double(0));

    	}
	};
}
