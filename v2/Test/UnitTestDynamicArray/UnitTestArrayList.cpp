#include "CppUnitTest.h"
#include "eos.h"
#include "OSAL/osalHeap.h"
#include "System/Collections/eosDynamicArray.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace eos;


namespace UnitTestArrayList {
	
	TEST_CLASS(UnitTestArrayList) {
	public:

		TEST_METHOD(add) {

			const int numElements = 100;
			DynamicArray<int> list;

			for (int i = 0; i < numElements; i++) {

				// Afegeix un element
				//
				list.pushBack(i + 100);
				int index = list.getSize() - 1;

				// Comprova el valor del index retornat
				//
				Assert::AreEqual<int>(i, index, L"L'index retornat es incorrecte.");

				// Comprova la quantitat d'elements en la llista
				//
				Assert::AreEqual<int>(i + 1, list.getSize(), L"La quantitat es incorrecta.");
			}
		}

		TEST_METHOD(remove) {

			const int numElements = 100;
			DynamicArray<int> list;
			
			// Afegeig elements
			//
			for (int i = 0; i < numElements; i++) {			
				list.pushBack(i + 100);
			}

			// Elimina un de cada dos.
			//
			for (int i = 0; i < numElements; i += 2) {
				list.removeAt(i + 100);
			}

			// Comprova que els que resten son els correctes.
			//
			for (int i = 0; i < list.getSize(); i++) {
				Assert::AreEqual<int>(i + i + 101, list[i], L"Els valors en la llista no son correctes.");
			}
			Assert::AreEqual<int>(numElements / 2, list.getSize(), L"La quantitat no coincideix.");
		}

		TEST_METHOD(insertAt) {

			const int numElements = 100;
			DynamicArray<int> list;

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
			Assert::AreEqual<int>(1, list.getSize(), L"La quantitat insertada no es correcte.");

			// Insercions pel centre 
			//
			for (int i = 0; i < numElements - 2; i++) {
				list.insertAt(1, i + 200);
				Assert::AreEqual<int>(i + 200, list[1]);
				Assert::AreEqual<int>(i + 2, list.getSize());
			}

			// Insercio al final
			//
			list.insertAt(list.getSize(), 300);
			Assert::AreEqual<int>(300, list[list.getSize() - 1]);
			Assert::AreEqual<int>(numElements, list.getSize());

		}

		TEST_METHOD(removeAt) {

			DynamicArray<int> list;

			// Afegeis elements
			//
			for (int i = 0; i < 100; i++)
				list.pushBack(i + 100);

			// Elimina el primer element
			//
			bool r1 = list.removeAt(0);
			Assert::IsTrue(r1, L"Error al eliminar el primer element");
			Assert::AreEqual<int>(101, list[0], L"El primer element es incorrecte.");
			Assert::AreEqual<int>(199, list[list.getSize() - 1], L"L'ultim element es incorrecte.");
			Assert::AreEqual<int>(99, list.getSize(), L"La quantitat es incorrecte.");

			// Elimina l'ultim element
			//
			bool r2 = list.removeAt(list.getSize() -1);
			Assert::IsTrue(r2, L"Error al eliminar l'ultim element.");
			Assert::AreEqual<int>(101, list[0], L"El primer element es incorrecte.");
			Assert::AreEqual<int>(198, list[list.getSize() - 1], L"L'ultim element es incorrecte.");
			Assert::AreEqual<int>(98, list.getSize(), L"La quantitat es incorrecte.");

			// Eliina un element central
			//
			bool r3 = list.removeAt(10);
     		Assert::IsTrue(r2, L"Error al eliminar element.");
			Assert::AreEqual<int>(112, list[10], L"El element 10, es incorrecte.");
			Assert::AreEqual<int>(97, list.getSize(), L"La quantitat es incorrecte.");
		}
	};
}
