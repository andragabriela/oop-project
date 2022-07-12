#include"Service.h"
#pragma once
class ConsoleUI {
private:
	ServiceLocatar& srv;

public:
	ConsoleUI(ServiceLocatar& srv)noexcept : srv{ srv } {};
	ConsoleUI(const ConsoleUI& ot) = delete;
	void adaugaUI();
	void modificaUI();
	void printAllLoc();
	void stergeUI();
	void filtrareTipUI();
	void filtrareaSupUI();
	void sortareNumeUI();
	void sortareSupUI();
	void sortareTipSup();
	void undo();
	//Lista interactiva
	void addWishlist();

	void deleteWishlist();

	void addRandom();

	void printRaport(vector<LocatarDTO> locatar);

	void Raport();
	void saveToHtml();
	void print_wishlist();
	void run();
};