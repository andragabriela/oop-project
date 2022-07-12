#pragma once
#include"Locatar.h"
#include<vector>
using std::vector;
class RepoException {
private:
	string error;
public:
	RepoException(string error) :error{ error } {};
	string getError() { return error; }
};
class LocatarRepository {
private:
	vector<Locatar> allLocatari;
public:
	LocatarRepository() noexcept = default;
	LocatarRepository(const LocatarRepository& ot) = delete;
	virtual void adauga(const Locatar& l);
	virtual void modifica(int, string, double, string);
	virtual void stergeRepo(Locatar l);
	virtual const vector<Locatar>& getallLocatari();
	const Locatar& find(int nr_ap) const;
	bool exista(const Locatar& l);
};
//lista interactiva
class LocatarRepository2 {
private:
	LocatarRepository& repo;
	vector<Locatar> wishlist;
public:
	LocatarRepository2(const LocatarRepository2& ot) = delete;
	LocatarRepository2(LocatarRepository& repo)noexcept :repo{ repo } {};

	void addToWishlist(int nr);

	void deleteAll()noexcept;

	const vector<Locatar> getAllWishlist();

	void addRandom(int cate);
};
class RepoFile : public LocatarRepository {
private:
	string filename;
	void loadFromFile();
	void saveToFile();
public:
	RepoFile(string filename) : LocatarRepository(), filename{ filename }{
		loadFromFile(); };
	void adauga(const Locatar& l) override;
	void modifica(int, string, double, string) override;
	void stergeRepo(Locatar l) override;
};
void testeRepo();