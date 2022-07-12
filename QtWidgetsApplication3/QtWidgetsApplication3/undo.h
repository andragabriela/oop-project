#pragma once
#include "Repo.h"

class ActiuneUndo {
public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo()=default;
};

class UndoAdauga : public ActiuneUndo {
private:
	Locatar addedLocatar;
	LocatarRepository& repo;
public:
	UndoAdauga(LocatarRepository& repo, const Locatar& l) : repo{ repo }, addedLocatar{ l }{}
	void doUndo() override {
		repo.stergeRepo(addedLocatar);
	}
};
class UndoSterge : public ActiuneUndo {
private:
	Locatar deletedLocatar;
	LocatarRepository& repo;
public:
	UndoSterge(LocatarRepository& repo, const Locatar& l) : repo{ repo }, deletedLocatar{ l }{}
	void doUndo() override {
		repo.adauga(deletedLocatar);
	}
};
class UndoModifica : public ActiuneUndo {
private:
	Locatar modifiedLocatar;
	LocatarRepository& repo;
public:
	UndoModifica(LocatarRepository& repo, Locatar& l) : repo{ repo }, modifiedLocatar{ l }{}
	void doUndo() override {
		repo.modifica(modifiedLocatar.getNrAp(), modifiedLocatar.getNumeProprietar(), modifiedLocatar.getSuprafata(), modifiedLocatar.getTipApartament());
	}
};