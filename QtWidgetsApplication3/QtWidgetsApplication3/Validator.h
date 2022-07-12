#include <string>
#include "Locatar.h"
#include <vector>
#include <ostream>
#pragma once
using std::vector;
using std::string;
using std::ostream;
class ValidateException {
	vector<string>errors;
public:
	ValidateException(const vector<string>& errors) : errors{ errors } {}
	friend ostream& operator<<(ostream& out, const ValidateException& ex);
};

ostream& operator<<(ostream& out, const ValidateException& ex);
class Validare {
public:
	void validate(const Locatar& l);
};
void testValidator();