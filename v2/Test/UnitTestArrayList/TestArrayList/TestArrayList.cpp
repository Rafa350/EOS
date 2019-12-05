#include "eos.h"
#include "OSAL/osalHeap.h"
#include "System/Collections/eosArrayList.h"


using namespace eos;


int main() {


	ArrayList<int> list;

	for (int i = 0; i < 6; i++)
		list.add(100 + i);

	list.removeAt(0);
	list.removeAt(list.getCount() - 1);

}
