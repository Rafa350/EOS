#include "eos.h"
#include "OSAL/osalHeap.h"
#include "System/Collections/eosDynamicArray.h"
#include "StringV2.h"


using namespace eos;


int main() {


	/*DynamicArray<int> list;

	for (int i = 0; i < 6; i++)
		list.pushBack(100 + i);

	list.removeAt(0);
	list.removeAt(list.getSize() - 1);
	*/

	StringV2 s1("Hola que tal.");
	StringV2 s2(s1);

	{
		StringV2 s3("caca");
		s3 = s1;
	}
}
