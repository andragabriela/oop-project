#include"Repo.h"
#include<assert.h>
#include<vector>
#include<fstream>
#include <sstream>
#include <random>
using std::ifstream;
using std::stringstream;
using std::ofstream;
const Locatar& LocatarRepository::find(int nr_ap) const {
	auto rez = std::find_if(allLocatari.begin(), allLocatari.end(), [nr_ap](const Locatar& l) {return l.getNrAp() == nr_ap; });
	if (!(rez != allLocatari.end())) {
		throw RepoException("Locatar inexistent!\n");
	}
	else {
		const Locatar& gasit = *rez;
		return gasit;
	}
}



bool LocatarRepository::exista(const Locatar& l) {
	try {
		find(l.getNrAp());
		return true;
	}
	catch (RepoException) {
		return false;
	}
}
const vector<Locatar>& LocatarRepository::getallLocatari() {
	return allLocatari;
}
void LocatarRepository::adauga(const Locatar& l1) {
	if (exista(l1)) { throw RepoException("Locatar existent!"); }
	allLocatari.push_back(l1);

}

void LocatarRepository::modifica(int nr_ap, string numenou, double supNoua, string tipNou) {
	int found = 0;
	for (size_t i = 0; i < allLocatari.size(); i++) {
		if (allLocatari[i].getNrAp() == nr_ap) {
			found = 1;
			Locatar newLoc{ nr_ap,numenou,supNoua,tipNou };
			allLocatari[i] = newLoc;
			break;
		}
	}
}
void LocatarRepository::stergeRepo(Locatar l) {
	int found = 0, index = 0;
	for (auto const& loc : allLocatari) {
		if (loc.getNumeProprietar() == l.getNumeProprietar() && loc.getNrAp() == l.getNrAp()) {
			found = 1;
			allLocatari.erase(allLocatari.begin() + index);
			break;
		}
		else index++;
	}
	if (found == 0)
		throw RepoException("Locatarul cu numele dat nu exista!\n");
}
void LocatarRepository2::addToWishlist(int nr)
{
	int found = 0;
	for (const auto& loc : repo.getallLocatari()) {
		if (loc.getNrAp() == nr) {
			wishlist.push_back(loc);
			found = 1;
			break;
		}
	}
	if (found == 0)
		throw RepoException("Locatar inexistent!\n");
	else return;
}

const vector<Locatar> LocatarRepository2::getAllWishlist() {
	return wishlist;
}
void LocatarRepository2::deleteAll() noexcept {
	wishlist.clear();
}
void LocatarRepository2::addRandom(int cate) {
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_int_distribution<> const dist(0, repo.getallLocatari().size() - 1);
	vector<Locatar> dest{ repo.getallLocatari() };
	for (int i = 0; i < cate; i++) {//imi ia locatarii in ordine random
		const int rndNr = dist(mt);
		wishlist.push_back(dest[rndNr]);
	}
}
void testAddRepo() {
	LocatarRepository testList;
	Locatar l(2, "Andra", 24.6, "garsoniera");
	testList.adauga(l);
	assert(testList.getallLocatari().size() == 1);

	Locatar l2(3, "Gabriela", 34.6, "ap cu 2 camere");
	Locatar l3(2, "Andra", 24.6, "garsoniera");
	try {
		testList.adauga(l3);
	}
	catch (RepoException) {
		assert(true);
	}
}
void testFindRepo() {
	LocatarRepository test_repo;
	Locatar l1{ 1,"Andra",24.5,"garsoniera" };
	Locatar l3{ 3,"Daniel",50,"ap. cu 2 camere" };
	test_repo.adauga(l1);

	assert(test_repo.exista(l1));
	assert(!test_repo.exista(l3));

	auto foundAp = test_repo.find(1);
	assert(foundAp.getNrAp() == 1);
	assert(foundAp.getSuprafata() == 24.5);
	assert(foundAp.getTipApartament() == "garsoniera");

	try {
		test_repo.find(10);

	}
	catch (RepoException& ve) {
		assert(ve.getError() == "Locatar inexistent!\n");

	}
}

void testSterge() {
	LocatarRepository testList;
	Locatar l(2, "Andra", 24.6, "garsoniera");
	testList.adauga(l);
	testList.stergeRepo(l);
	assert(testList.getallLocatari().size() == 0);
	Locatar l2{ 1,"Andra",24.5,"garsoniera" };
	Locatar l3{ 3,"Daniel",50,"ap. cu 2 camere" };
	Locatar l4{ 4,"Gabriela",50.7,"ap. cu 2 camere" };
	testList.adauga(l2);
	testList.adauga(l3);
	testList.stergeRepo(l2);
	assert(testList.getallLocatari().size() == 1);
	try {
		testList.stergeRepo(l4);

	}
	catch (RepoException&) {
		assert(true);
	}
}
void testRepo2() {
	LocatarRepository repo;
	LocatarRepository2 repo2{ repo };
	Locatar c1{ 1,"Andra",23,"garsoniera" };
	Locatar c2{ 2,"Gabriela",45,"ap cu 2 camere" };
	repo.adauga(c1);
	repo.adauga(c2);
	assert(repo.getallLocatari().size() == 2);
	repo2.addToWishlist(1);
	assert(repo2.getAllWishlist().size() == 1);
	try {
		repo2.addToWishlist(5);

	}
	catch (RepoException& ex) {
		assert(true);
		assert(ex.getError() == "Locatar inexistent!\n");
	}
	repo2.addToWishlist(2);
	repo2.deleteAll();
	assert(repo2.getAllWishlist().size() == 0);
	repo2.addRandom(1);
	assert(repo2.getAllWishlist().size() == 1);
	repo2.deleteAll();

}

void RepoFile::loadFromFile()
{
	ifstream LocatarFile(this->filename);
	if (!LocatarFile.is_open()) {
		throw RepoException("Cannot read from file " + filename);
	}
	string line;
	while (getline(LocatarFile, line))
	{
		int nr_ap;
		string nume, tip;
		double sup;

		stringstream linestream(line);
		string current_item;
		int item_no = 0;
		while (getline(linestream, current_item, ','))
		{
			if (item_no == 0) nr_ap = stoi(current_item);
			if (item_no == 1) nume = current_item;
			if (item_no == 2) sup = stod(current_item);
			if (item_no == 3) tip = current_item;
			item_no++;
		}
		Locatar l{ nr_ap, nume, sup, tip };
		LocatarRepository::adauga(l);
	}
	LocatarFile.close();
}

void RepoFile::saveToFile()
{
	ofstream outFile(filename);
	if (!outFile.is_open()) {
		throw RepoException("File can not open!\n");
	}
	for (auto& loc : getallLocatari()) {
		outFile << loc.getNrAp() << "," << loc.getNumeProprietar() << "," << loc.getSuprafata() << "," << loc.getTipApartament() << endl;
	}
	outFile.close();
}

void RepoFile::adauga(const Locatar& l)
{
LocatarRepository::adauga(l);
	saveToFile();
}

void RepoFile::modifica(int nr, string nume, double sup , string tip)
{
	LocatarRepository::modifica(nr, nume, sup, tip);
	saveToFile();
}

void RepoFile::stergeRepo(Locatar l)
{
	LocatarRepository::stergeRepo(l);
	saveToFile();
}
void testRepoFile() {
	std::ofstream fout("testLocatar.txt", std::ios::trunc);
	fout.close();
	RepoFile repo{ "testCar.txt" };
	Locatar l1{ 1,"Andra",24.5,"garsoniera" };
	repo.adauga (l1);
	repo.adauga(Locatar{ 3,"Ela",50,"ap. cu 2 camere" });
	repo.adauga(Locatar{ 4,"Gabriela",50.7,"ap. cu 2 camere" });
	Locatar l2{ 4,"Gabriela",50.7,"ap. cu 2 camere" };
	auto c = repo.find(1);
	assert(c.getNumeProprietar() == "Andra");
	repo.stergeRepo(l1);
	assert(repo.getallLocatari().size() == 2);
	try {
		repo.stergeRepo(l2);
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}
	try {
		repo.adauga(Locatar{ 1,"Gabriela",50.7,"ap. cu 2 camere" });
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}
	repo.modifica(1, "Gabriela", 50.7, "ap. cu 2 camere");
	c = repo.find(1);
	assert(c.getNumeProprietar() == "Gabriela");
	try {
		repo.find(10);
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}
	try {
		RepoFile repo2{ "nou/car.txt" };
		assert(false);
	}
	catch (RepoException& ex) {
		assert(ex.getError() == "File can not open!\n");
		assert(true);
	}


}
void testeRepo() {
	testAddRepo();
	testFindRepo();
	testSterge();
	testRepo2();
	testRepoFile();
}
