#pragma once
#pragma once
#include "CosCrud.h"
#include"CosReadOnly.h"
#include "Service.h"
#include<QtWidgets/qapplication.h>
#include<qlabel.h>
#include <QtWidgets/qlineedit.h>
#include <QPushButton>
#include <QtWidgets/qgroupbox.h>
#include <QtWidgets/qradiobutton.h>
#include <QtWidgets/qtablewidget.h>
#include<QtWidgets/qboxlayout.h>
#include<string>
#include"TableModel.h"

class LocatarGui2 : public QWidget {
	ServiceLocatar& srv;
	TableModel* model;
	QTableView* table = new QTableView;
private:

	QLabel* nr = new QLabel{ "Numar apartament: " };
	QLabel* nume = new QLabel{ "Nume proprietar: " };
	QLabel* sup = new QLabel{ "Suprafata apartament: " };
	QLabel* tip = new QLabel{ "Tip apartament: " };

	QLineEdit* edit_nr;
	QLineEdit* edit_nume;
	QLineEdit* edit_sup;
	QLineEdit* edit_tip;

	QPushButton* addLocatar;

	QLabel* mod_nr = new QLabel{ "Modifica nr apartament: " };
	QLabel* mod_nume = new QLabel{ "Modifica nume proprietar: " };
	QLabel* mod_sup = new QLabel{ "Modifica suprafata: " };
	QLabel* mod_tip = new QLabel{ "Modifica tipul: " };

	QLineEdit* edit_mod_nr;
	QLineEdit* edit_mod_nume;
	QLineEdit* edit_mod_sup;
	QLineEdit* edit_mod_tip;

	QPushButton* modificaProp;

	QLabel* del_nr = new QLabel{ "Nr ap de sters: " };
	QLabel* del_nume = new QLabel{ "Nume proprietar de sters: " };
	QLabel* del_sup = new QLabel{ "Suprafata ap de sters: " };
	QLabel* del_tip = new QLabel{ "Tipul ap de sters: " };

	QLineEdit* edit_del_nr;
	QLineEdit* edit_del_nume;
	QLineEdit* edit_del_sup;
	QLineEdit* edit_del_tip;

	QPushButton* delAp;

	QGroupBox* groupBox = new QGroupBox(tr("Tip sortare"));

	QRadioButton* radioSortSup = new QRadioButton(QString::fromStdString("Suprafata"));
	QRadioButton* radioSortNume = new QRadioButton(QString::fromStdString("Nume"));
	QRadioButton* radioSortSupAndTip = new QRadioButton(QString::fromStdString("Suprafata+Tip"));

	QPushButton* btnsort;

	QPushButton* btnFilter = new QPushButton("&Filtrare");
	QComboBox* cmbFilter = new QComboBox;


	QPushButton* reload_data;

	QPushButton* undo;


	QPushButton* btnNotShow = new QPushButton("&CosCrud");

	GUINotificari* guinot;

	QPushButton* btnReadonly = new QPushButton{ "CosReadOnly" };

	//dinamice
	QVBoxLayout* panelButtonsLayout;
	vector<QPushButton*>buttons;

	void addButtons();

	////slider
	//QLineEdit* editNoSlider;
	//QLabel* lblSlider;
	//QSlider* sliderGenerate;


	void initGUI();
	void connectSignals();
	void reload(vector<Locatar> locatari);



public:
	LocatarGui2(ServiceLocatar& srv) : srv{ srv } {
		initGUI();
		model = new TableModel{ srv.getallLocatari() };
		table->setModel(model);
		connectSignals();
		reload(srv.getallLocatari());
	};
	LocatarGui2(const LocatarGui2& ot) = delete;

	void guiAdd();
	void guiMod();
	void guiDel();
};