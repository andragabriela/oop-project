#include"Locatar.h"
#include<assert.h>

void testeDomain() {
	Locatar l1{ 1, "Andra", 23.4, "garsoniera" };
	assert(l1.getNrAp() == 1);
	assert(l1.getNumeProprietar() == "Andra");
	assert(l1.getSuprafata() == 23.4);
	assert(l1.getTipApartament() == "garsoniera");
}