#include"Repo.h"
#include<vector>
#include<fstream>
#include<unordered_map>
#include"Validator.h"
#include"undo.h"
#include "observer.h"

using namespace std;
#pragma once
class ServiceLocatar :public Observable{
private:
	LocatarRepository& repo;
	//lista pt undo
	vector<unique_ptr<ActiuneUndo>> undoActions;
	Validare& val;
	LocatarRepository2& repo2;
public:
	ServiceLocatar(LocatarRepository& repo, Validare& val, LocatarRepository2& repo2)noexcept : repo{ repo }, val{ val }, repo2{ repo2 } {};
	ServiceLocatar(const ServiceLocatar& ot) = delete;
	ServiceLocatar() = default;
	void addLocatar(int nr_ap, string nume, double sup, const string& tip_ap);
	void modificaProp(int, string, double, string);
	void sterge(int nr_ap, string nume, double sup, string tip_ap);
	vector<Locatar> filtrareTip(string tip) const;
	vector<Locatar> filtrareSuprafata(double sup) const;
	vector<Locatar> sortNume() const;
	vector<Locatar> sortSup() const;
	vector<Locatar> sortTipSup() const;
	const vector<Locatar>& getallLocatari();
	void undo();
	const Locatar& findLoc(int nr_ap) const;
	//Lista interactiva
	void addToWishlist(int nr);

	const vector<Locatar> getAllWishlist();

	void deleteAll() noexcept;

	void addRandom(int cate);

	unordered_map<string, LocatarDTO> Create_map();
	void exportNotificariHTML(string path) {
		string fisier=path;
		fisier.append(".html");
		std::ofstream fout(fisier);
		fout << "====LISTA====" << " <p> ";
		fout << "<html><body>" << endl;
		fout << "<table border=\"1\" style=\"width:100 % \">" << endl;
		for (auto& elem : getAllWishlist()) {
			fout << "<tr>";
			fout << "<td>" << elem.getNrAp() << "</td>" << endl;
			fout << "<td>" << elem.getNumeProprietar() << "</td>" << endl;
			fout << "<td>" << elem.getSuprafata() << "</td>" << endl;
			fout << "<td>" << elem.getTipApartament() << "</td>" << endl;
			fout << "</tr>" << endl;
		}
		fout << "</table>" << endl;
		fout << "</body></html>" << endl;
		cout << "Lista a fost salvata cu succes...\n\n";
		fout.close();
	}
	vector<LocatarDTO> raport();

};
void testeService();