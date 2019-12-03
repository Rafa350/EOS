#include "CppUnitTest.h"
#include "eos.h"
#include "OSAL/osalHeap.h"
#include "System/Collections/eosArrayList.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace eos;


namespace UnitTestArrayList {
	
	TEST_CLASS(UnitTestArrayList) {
	public:

		TEST_METHOD(add) {

			const int numElements = 100;
			ArrayList<int> list;

			for (int i = 0; i < numElements; i++) {

				// Afegeix un element
				//
				int index = list.add(i + 100);

				// Comprova el valor del index retornat
				//
				Assert::AreEqual<int>(i, index, L"L'index retornat es incorrecte.");

				// Comprova la quantitat d'elements en la llista
				//
				Assert::AreEqual<int>(i + 1, list.getCount(), L"La quantitat es incorrecta.");
			}
		}

		TEST_METHOD(remove) {

			const int numElements = 100;
			ArrayList<int> list;
			
			for (int i = 0; i < numElements; i++) {			
				list.add(i + 100);
			}

			for (int i = 0; i < numElements; i += 2) {
				list.remove(i + 100);
			}

			for (int i = 0; i < list.getCount(); i++) {
				Assert::AreEqual<int>(i + i + 101, list[i], L"Els valors en la llista no son correctes.");
			}
		}

		TEST_METHOD(insertAt) {

			const int numElements = 100;
			ArrayList<int> list;

			// Inserta amb index erroni
			//
			bool r1 = list.insertAt(-1, 0);
			Assert::IsFalse(r1, L"Insertar en el index negatiu.");

			bool r2 = list.insertAt(1, 0);
			Assert::IsFalse(r2, L"Insertar amb index posterior a l'ultim element.");

			// Inserta al principi amb la lista buida
			//
			list.insertAt(0, 100);
			Assert::AreEqual<int>(100, list[0], L"El valor insertat no es correcte.");
			Assert::AreEqual<int>(1, list.getCount(), L"La quantitat insertada no es correcte.");

			// Insercions pel centre 
			//
			for (int i = 0; i < numElements - 2; i++) {
				list.insertAt(1, i + 200);
				Assert::AreEqual<int>(i + 200, list[1]);
				Assert::AreEqual<int>(i + 2, list.getCount());
			}

			// Insercio al final
			//
			list.insertAt(list.getCount(), 300);
			Assert::AreEqual<int>(300, list[list.getCount() - 1]);
			Assert::AreEqual<int>(numElements, list.getCount());

		}

		TEST_METHOD(removeAt) {

			ArrayList<int> list;

			// Afegeis elements
			//
			for (int i = 0; i < 100; i++)
				list.add(i + 100);

			// Elimina el primer element
			//
			bool r1 = list.removeAt(0);
			Assert::IsTrue(r1, L"Error al eliminar el primer element");
			Assert::AreEqual<int>(101, list[0], L"El primer element es incorrecte.");
			Assert::AreEqual<int>(199, list[list.getCount() - 1], L"L'ultim element es incorrecte.");
			Assert::AreEqual<int>(99, list.getCount(), L"La quantitat es incorrecte.");

			// Elimina l'ultim element
			//
			bool r2 = list.removeAt(list.getCount() -1);
			Assert::IsTrue(r2, L"Error al eliminar l'ultim element.");
			Assert::AreEqual<int>(101, list[0], L"El primer element es incorrecte.");
			Assert::AreEqual<int>(198, list[list.getCount()], L"L'ultim element es incorrecte.");
			Assert::AreEqual<int>(98, list.getCount(), L"La quantitat es incorrecte.");
		}
	};
}
