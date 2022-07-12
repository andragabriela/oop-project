#include<string>
#include <iostream>
#pragma once
using std::string;
using std::cout;
using std::endl;

class Locatar {
private:
	int nr_apartament;
	string nume, tip_apartament;
	double suprafata;
public:
	Locatar(int nr_apartament, string nume, double suprafata, string tip_apartament) :nr_apartament{ nr_apartament }, nume{ nume }, suprafata{ suprafata }, tip_apartament{ tip_apartament }{};
	Locatar(const Locatar& ot) :nr_apartament{ ot.nr_apartament }, nume{ ot.nume }, suprafata{ ot.suprafata }, tip_apartament{ ot.tip_apartament }{
		//cout << "Copy constructor called." << endl;
	}
	int getNrAp() const noexcept {
		return nr_apartament;
	}
	string getNumeProprietar() const {
		return nume;
	}
	double getSuprafata() const noexcept {
		return suprafata;
	}
	string getTipApartament() const {
		return tip_apartament;
	}
	bool operator==(const Locatar& ot) noexcept {
		return nr_apartament == ot.getNrAp();
	}
	bool operator!=(const Locatar& ot) noexcept {
		return nr_apartament != ot.getNrAp();
	}
};
//bool cmpNr(const Locatar& l1,const Locatar& l2);
//bool cmp
class LocatarDTO {
private:
	string type;
	int nr;
	int count;

public:
	LocatarDTO() noexcept : nr{ 0 }, type{ "" }, count{ 0 }{}
	void setNr(int new_nr) {
		nr = new_nr;
	}

	void setTip(string new_type) {
		type = new_type;
	}

	void setCount(int new_count)noexcept {
		count = new_count;
	}

	int getNr() {
		return nr;
	}

	string getType() {
		return type;
	}

	int getCount() noexcept {
		return count;
	}
};
void testeDomain();