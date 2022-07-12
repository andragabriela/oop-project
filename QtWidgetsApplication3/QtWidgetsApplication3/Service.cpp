#pragma once
#include<assert.h>
#include<algorithm>
#include<unordered_map>
#include"Service.h"
#include"undo.h"

using std::string;
using std::unordered_map;
const vector<Locatar>& ServiceLocatar::getallLocatari() {
	return repo.getallLocatari();
}
void ServiceLocatar::addLocatar(int nr_ap, string nume, double sup, const string& tip_ap) {
	Locatar l{ nr_ap, nume, sup, tip_ap };
	val.validate(l);
	repo.adauga(l);
	undoActions.push_back(std::make_unique<UndoAdauga>(repo, l));
}
void ServiceLocatar::undo() {
	if (undoActions.empty()) {
		throw RepoException("Nu mai sunt operatii\n");
	}
	undoActions.back()->doUndo();
	undoActions.pop_back();

}
const Locatar& ServiceLocatar::findLoc(int nr_ap) const
{
	return repo.find(nr_ap);
}
void ServiceLocatar::modificaProp(int nr_ap, string nume, double sup, string tip) {
	auto l = repo.find(nr_ap);
	repo.modifica(nr_ap, nume, sup, tip);
	undoActions.push_back(std::make_unique<UndoModifica>(repo, l));

}
void ServiceLocatar::sterge(int nr_ap, string nume, double sup, string tip_ap) {
	Locatar l{ nr_ap, nume, sup, tip_ap };
	repo.stergeRepo(l);
	undoActions.push_back(std::make_unique<UndoSterge>(repo, l));
}
vector<Locatar> ServiceLocatar::filtrareTip(string tip) const {
	vector<Locatar> rez;
	std::copy_if(repo.getallLocatari().begin(), repo.getallLocatari().end(), back_inserter(rez), [tip](const Locatar& l) {return l.getTipApartament() == tip; });
	/*vector<Locatar>dest;
	for (const auto& c : rez) {
		dest.push_back(c);
	}*/
	return rez;
}
vector<Locatar> ServiceLocatar::filtrareSuprafata(double sup) const {
	vector<Locatar> rez;
	std::copy_if(repo.getallLocatari().begin(), repo.getallLocatari().end(), std::back_inserter(rez), [sup](const Locatar& l) {return l.getSuprafata() <= sup; });
	vector<Locatar>dest;
	for (const auto& c : rez) {
		dest.push_back(c);
	}
	return dest;
	/*vector<Masini> rez;
	for (auto& mas : getallMas()) {
		if (mas.get_model() == model) rez.push_back(mas);
	}
	return rez;*/
}
vector<Locatar> ServiceLocatar::sortNume() const {

	vector<Locatar> copie{ repo.getallLocatari() };
	std::sort(copie.begin(), copie.end(), [](const Locatar& c1, const Locatar& c2) {return c1.getNumeProprietar() < c2.getNumeProprietar(); });
	vector<Locatar>dest;
	for (const auto& c : copie) {
		dest.push_back(c);
	}
	return dest;
	/*vector<Car> copie{ repo.getAll() };
	for (size_t i = 0; i < copie.size(); i++) {
		for (size_t j = i + 1; j < copie.size(); j++) {
			if (copie[i].getTip() > copie[j].getTip()) {
				Car aux = copie[i];
				copie[i] = copie[j];
				copie[j] = aux;
			}
		}
	}
	return copie;*/
}
vector<Locatar> ServiceLocatar::sortSup() const {

	vector<Locatar> copie{ repo.getallLocatari() };
	std::sort(copie.begin(), copie.end(), [](const Locatar& c1, const Locatar& c2) {return c1.getSuprafata() < c2.getSuprafata(); });
	vector<Locatar>dest;
	for (const auto& c : copie) {
		dest.push_back(c);
	}
	return dest;
}
vector<Locatar> ServiceLocatar::sortTipSup() const {

	vector<Locatar> copie{ repo.getallLocatari() };
	for (size_t i = 0; i < copie.size(); i++) {
		for (size_t j = i + 1; j < copie.size(); j++) {
			if (copie[i].getTipApartament() > copie[j].getTipApartament()) {
				Locatar aux = copie[i];
				copie[i] = copie[j];
				copie[j] = aux;
			}
			else if (copie[i].getTipApartament() == copie[j].getTipApartament()) {
				if (copie[i].getSuprafata() > copie[j].getSuprafata()) {
					Locatar aux = copie[i];
					copie[i] = copie[j];
					copie[j] = aux;
				}
			}
		}
	}
	return copie;
}
unordered_map<string, LocatarDTO> ServiceLocatar::Create_map() {
	unordered_map<string, LocatarDTO> m;
	for (const auto& loc : repo.getallLocatari()) {
		LocatarDTO dto;
		int ok = 0;
		string tip = loc.getTipApartament();
		int nr = loc.getNrAp();
		for (auto& el : m) {
			if (el.first == tip) {
				el.second.setCount(el.second.getCount() + 1);
				ok = 1;
			}
		}
		if (ok == 0) {
			dto.setNr(nr);
			dto.setTip(tip);
			dto.setCount(1);
			m.insert(pair<string, LocatarDTO>(tip, dto));
		}
	}
	return m;
}

vector<LocatarDTO>ServiceLocatar::raport() {
	vector<LocatarDTO> rez;
	LocatarDTO dto;
	unordered_map<string, LocatarDTO> m = Create_map();

	std::transform(m.begin(), m.end(), std::back_inserter(rez), [](const pair<string, LocatarDTO>pereche) {return pereche.second; });
	return rez;

}
// lista interactiva
void ServiceLocatar::addToWishlist(int nr) {
	repo2.addToWishlist(nr);
}
void ServiceLocatar::deleteAll() noexcept {
	repo2.deleteAll();
}
const vector<Locatar> ServiceLocatar::getAllWishlist() {
	return repo2.getAllWishlist();
}
void ServiceLocatar::addRandom(int cate) {
	repo2.addRandom(cate);
}
void testSortareNume() {
	LocatarRepository test_repo;
	LocatarRepository2 test_repo2{ test_repo };
	Validare val;
	ServiceLocatar srv_test{ test_repo, val,test_repo2 };
	srv_test.addLocatar(2, "Andra", 24.6, "garsoniera");
	srv_test.addLocatar(5, "Gabriela", 24, "3 camere");
	srv_test.addLocatar(3, "Daniel", 35.8, "ap cu 2 camere");
	auto rez = srv_test.sortNume();
	assert(rez[0].getNumeProprietar() == "Andra");
	assert(rez[0].getNrAp() == 2);
	assert(rez[1].getNumeProprietar() == "Daniel");

}

void testSortareSup() {
	LocatarRepository test_repo;
	LocatarRepository2 test_repo2{ test_repo };
	Validare val;
	ServiceLocatar srv_test{ test_repo, val,test_repo2 };
	srv_test.addLocatar(2, "Andra", 24.6, "garsoniera");
	srv_test.addLocatar(5, "Daniel", 24, "3 camere");
	srv_test.addLocatar(3, "Gabriela", 35.8, "ap cu 2 camere");
	auto rez = srv_test.sortSup();
	assert(rez[0].getSuprafata() == 24);
	assert(rez[1].getSuprafata() == 24.6);
	assert(rez[2].getSuprafata() == 35.8);

}
void testSortareTipSup() {
	LocatarRepository test_repo;
	LocatarRepository2 test_repo2{ test_repo };
	Validare val;
	ServiceLocatar srv_test{ test_repo, val,test_repo2 };
	srv_test.addLocatar(2, "Andra", 24.6, "garsoniera");
	srv_test.addLocatar(5, "Daniel", 24, "garsoniera");
	srv_test.addLocatar(3, "Gabriela", 35.8, "ap cu 2 camere");
	auto rez = srv_test.sortTipSup();
	assert(rez[1].getSuprafata() == 24);
	assert(rez[2].getSuprafata() == 24.6);
	assert(rez[0].getSuprafata() == 35.8);
}
void testFiltrareTip() {
	LocatarRepository test_repo;
	LocatarRepository2 test_repo2{ test_repo };
	Validare val;
	ServiceLocatar srv_test{ test_repo, val,test_repo2 };
	srv_test.addLocatar(2, "Andra", 24.6, "garsoniera");
	srv_test.addLocatar(3, "Gabriela", 35.8, "ap cu 2 camere");
	vector<Locatar> listFiltred = srv_test.filtrareTip("garsoniera");
	assert(listFiltred.size() == 1);

}
void testFiltrareSup() {
	LocatarRepository test_repo;
	LocatarRepository2 test_repo2{ test_repo };
	Validare val;
	ServiceLocatar srv_test{ test_repo, val,test_repo2 };
	srv_test.addLocatar(2, "Andra", 24.6, "garsoniera");
	srv_test.addLocatar(3, "Gabriela", 35.8, "ap cu 2 camere");
	auto listFiltred = srv_test.filtrareSuprafata(24.6);
	assert(listFiltred.size() == 1);

}
void testStergeService() {
	LocatarRepository test_repo;
	LocatarRepository2 test_repo2{ test_repo };
	Validare val;
	ServiceLocatar srv_test{ test_repo, val,test_repo2 };
	srv_test.addLocatar(2, "Andra", 24.6, "garsoniera");
	srv_test.addLocatar(3, "Gabriela", 35.8, "ap cu 2 camere");
	srv_test.sterge(2, "Andra", 24.6, "garsoniera");
	assert(srv_test.getallLocatari().size() == 1);
}
void testModificaService() {
	LocatarRepository test_repo;
	LocatarRepository2 test_repo2{ test_repo };
	Validare val;
	ServiceLocatar srv_test{ test_repo, val,test_repo2 };
	srv_test.addLocatar(2, "Andra", 24.6, "garsoniera");
	srv_test.addLocatar(3, "Gabriela", 35.8, "ap cu 2 camere");
	srv_test.modificaProp(2, "Ela", 34, "ap cu 2 camere");
	assert(srv_test.getallLocatari()[0].getNumeProprietar() == "Ela");
	try {
		srv_test.modificaProp(7, "Eli", 50, "garsoniera");
	}
	catch (RepoException& re) {
		assert(re.getError() == "Locatar inexistent!\n");
	}
}
void testAddService() {
	LocatarRepository test_repo;
	LocatarRepository2 test_repo2{ test_repo };
	Validare val;
	ServiceLocatar srv_test{ test_repo, val, test_repo2 };
	assert(srv_test.getallLocatari().size() == 0);
	srv_test.addLocatar(2, "Andra", 24.6, "garsoniera");
	assert(srv_test.getallLocatari().size() == 1);
	srv_test.addLocatar(3, "Gabriela", 35.8, "ap cu 2 camere");
	srv_test.addLocatar(4, "Ela", 23.9, "ap cu 3 camere");
	assert(srv_test.getallLocatari().size() == 3);
	try {
		srv_test.addLocatar(2, "Andra", 24.6, "garsoniera");
	}
	catch (RepoException&) {
		assert(true);
	}
	try {
		srv_test.addLocatar(-2, "", -24.6, "");

	}
	catch (ValidateException&) {
		assert(true);
	}

}
void testSrv2() {
	LocatarRepository repo;
	LocatarRepository2 repo2{ repo };
	Validare valid;
	ServiceLocatar serv{ repo,valid,repo2 };
	serv.addLocatar(2, "Andra", 24.6, "garsoniera");
	serv.addLocatar(3, "Gabriela", 35.8, "ap cu 2 camere");
	serv.addLocatar(4, "Ela", 23.9, "ap cu 3 camere");
	serv.addToWishlist(2);
	serv.addToWishlist(3);
	assert(serv.getAllWishlist().size() == 2);
	serv.deleteAll();
	assert(serv.getAllWishlist().size() == 0);
	serv.addRandom(2);
	assert(serv.getAllWishlist().size() == 2);

}
void testUndo() {
	LocatarRepository repo;
	LocatarRepository2 repo2{ repo };
	Validare val;
	ServiceLocatar serv{ repo, val, repo2 };
	serv.addLocatar(2, "Andra", 24.6, "garsoniera");
	serv.addLocatar(3, "Gabriela", 35.8, "ap cu 2 camere");
	serv.addLocatar(4, "Ela", 23.9, "ap cu 3 camere");
	serv.sterge(2, "Andra", 24.6, "garsoniera");
	serv.undo();
	assert(serv.getallLocatari().size() == 3);
	serv.addLocatar(5, "Gabi", 65, "ap cu 4 camere");
	serv.undo();
	assert(serv.getallLocatari().size() == 3);
	serv.modificaProp(2, "Eli", 25.6, "ap cu 2 camere");
	serv.undo();
	assert(serv.getallLocatari()[2].getNumeProprietar() == "Andra");
	serv.undo();
	assert(serv.getallLocatari().size() == 2);
	serv.undo();
	assert(serv.getallLocatari().size() == 1);
	serv.undo();
	assert(serv.getallLocatari().size() == 0);
	try {
		serv.undo();
	}
	catch (RepoException& re) {
		assert(re.getError() == "Nu mai sunt operatii\n");
	}

}
void testMap() {
	LocatarRepository repo;
	LocatarRepository2 repo2{ repo };
	Validare val;
	ServiceLocatar serv{ repo, val, repo2 };
	serv.addLocatar(2, "Andra", 24.6, "garsoniera");
	serv.addLocatar(5, "Daniel", 24, "garsoniera");
	serv.addLocatar(3, "Gabriela", 35.8, "ap cu 2 camere");
	vector<LocatarDTO> rez;
	rez = serv.raport();
	assert(rez[0].getNr() == 2);
	assert(rez[0].getCount() == 2);
	assert(rez[0].getType() == "garsoniera");
}
void testeService() {
	testModificaService();
	testAddService();
	testStergeService();
	testFiltrareTip();
	testFiltrareSup();
	testSortareSup();
	testSortareTipSup();
	testSortareNume();
	testSrv2();
	testUndo();
	testMap();
}