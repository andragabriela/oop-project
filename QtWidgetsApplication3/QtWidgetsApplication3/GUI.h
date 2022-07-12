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
//#include <QtWidgets/qtablewidget.h>

class LocatarGui : public QWidget {
	ServiceLocatar& srv;

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

	QLabel* mod_nr= new QLabel{ "Modifica nr apartament: " };
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

	/*QGroupBox* filterBox = new QGroupBox(tr("Tip filtrare"));

	QRadioButton* filtru_tip = new QRadioButton(QString::fromStdString("Tip"));
	QRadioButton* filtru_sup = new QRadioButton(QString::fromStdString("Suprafata"));

	QLabel* filer_tip = new QLabel{ "Criteriu tip" };
	QLabel* filer_sup = new QLabel{ "Criteriu suprafata" };

	QLineEdit* edit_filtru_tip;
	QLineEdit* edit_filtru_sup;

	QPushButton* filtru;*/
	
	QPushButton* reload_data;

	QPushButton* undo;

	QTableWidget* apartamente;

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
	LocatarGui(ServiceLocatar& srv) : srv{ srv } {
		initGUI();
		connectSignals();
		reload(srv.getallLocatari());
	};
	LocatarGui(const LocatarGui& ot) = delete;

	void guiAdd();
	void guiMod();
	void guiDel();
};