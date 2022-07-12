#include "Validator.h"
#include <assert.h>
#include <iostream>
#include <sstream>
using std::cout;
void Validare::validate(const Locatar& l) {
	vector<string>mesg;
	if (l.getNrAp() < 0) mesg.push_back("Nr. negativ!\n");
	if (l.getNumeProprietar().size() == 0) mesg.push_back("Nume vid!\n");
	if (l.getSuprafata() < 0) mesg.push_back("Suprafata negativa!\n");
	if (l.getTipApartament().size() == 0) mesg.push_back("Tip vid!\n");
	if (mesg.size() > 0) {
		throw ValidateException(mesg);
	}
}
ostream& operator<<(ostream& out, const ValidateException& ex) {
	for (const auto& mesg : ex.errors) {
		out << mesg << " ";
	}
	return out;
}
void testValidator() {
	Validare v;
	Locatar l{ 2,"",-3,"" };
	try {
		v.validate(l);
	}
	catch (const ValidateException& ex) {
		std::stringstream sout;
		sout << ex;
		auto mesaj = sout.str();
		assert(mesaj.find("negativ") >= 0);
		assert(mesaj.find("vid") >= 0);
	}
}