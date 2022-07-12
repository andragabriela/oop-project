#include"Locatar.h"
#include"Repo.h"
#include"Validator.h"
#include"Service.h"
#include"GUI.h"
#include"GUIptModel.h"
#include <QtWidgets/QApplication>
void teste() {
	testeService();
	testeDomain();
	testeRepo();
	testValidator();
}
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	RepoFile repo{"locatar.txt"};
	LocatarRepository2 repo2{repo};
	Validare val;
	ServiceLocatar srv{repo, val, repo2};
	/*LocatarGui gui{ srv };
	gui.show();*/
	LocatarGui2 gui{ srv };
	gui.show();
	return a.exec();

	//teste();
}
