#include "GUI.h"
#include "CosCrud.h"
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qmessagebox.h>
#include <QtWidgets/qcolordialog.h>
#include"qdebug.h"


void LocatarGui::addButtons()
{
	for (const auto& widget : buttons)
		panelButtonsLayout->removeWidget(widget);
	buttons.clear();
	for (const auto& l : srv.getallLocatari())
	{
		string tip = l.getTipApartament();
		if (std::find_if(buttons.begin(), buttons.end(), [tip](QPushButton* btn) {return btn->text().toStdString() == tip; }) == buttons.end())
		{
			QPushButton* btn = new QPushButton(QString::fromStdString(tip));
			QObject::connect(btn, &QPushButton::clicked, [&, tip]() {
				auto objs = srv.filtrareTip(tip);
				size_t dim = objs.size();
				QMessageBox::warning(this, "warning", QString::fromStdString("Numarul de apartamente de acest tip este: " + std::to_string(dim)));
				});
			panelButtonsLayout->addWidget(btn);
			buttons.push_back(btn);
		}
	}
}

void LocatarGui::initGUI() {



	//impartim fereastra in 2: in stanga, butoane+labels+qlineedits
	//iar in dreapta: tabelul cu melodii



	//"stanga" si "dreapta" pentru ca este QHBoxLayout
	//se adauga componente incepand din stanga, pe orizontala
	//aici: "left" component, then "right" component
	//care la randul lor contin alte componente



	//main layout
	QHBoxLayout* lyMain = new QHBoxLayout;
	this->setLayout(lyMain);

	//left part of the window
	//pentru aceasta parte setam layout vertical
	QWidget* left = new QWidget;
	QVBoxLayout* lyLeft = new QVBoxLayout;
	left->setLayout(lyLeft);



	//componente pentru functionalitatea de adaugare a unui apartament
	QWidget* form = new QWidget;
	QFormLayout* lyForm = new QFormLayout;
	form->setLayout(lyForm);
	edit_nr = new QLineEdit;
	edit_nume = new QLineEdit;
	edit_sup = new QLineEdit;
	edit_tip = new QLineEdit;



	lyForm->addRow(nr, edit_nr);
	lyForm->addRow(nume, edit_nume);
	lyForm->addRow(sup, edit_sup);
	lyForm->addRow(tip, edit_tip);
	addLocatar = new QPushButton("Adauga locatar");
	lyForm->addWidget(addLocatar);



	//adaugam toate componentele legate de adaugare medicamentului
	//in layout-ul care corespunde partii din stanga a ferestrei
	lyLeft->addWidget(form);




	QWidget* formMod = new QWidget;
	QFormLayout* lyFormMod = new QFormLayout;
	formMod->setLayout(lyFormMod);
	//de aici pt fereastra noua nu mai scriu
	edit_mod_nr = new QLineEdit;
	edit_mod_nume = new QLineEdit;
	edit_mod_sup = new QLineEdit;
	edit_mod_tip = new QLineEdit;



	lyFormMod->addRow(mod_nr, edit_mod_nr);
	lyFormMod->addRow(mod_nume, edit_mod_nume);
	lyFormMod->addRow(mod_sup, edit_mod_sup);
	lyFormMod->addRow(mod_tip, edit_mod_tip);
	//pana aici
	modificaProp = new QPushButton("Modifica locatar");
	lyFormMod->addWidget(modificaProp);

	lyLeft->addWidget(formMod);

	QWidget* formDel = new QWidget;
	QFormLayout* lyFormDel = new QFormLayout;
	formDel->setLayout(lyFormDel);
	edit_del_nr = new QLineEdit;
	edit_del_nume = new QLineEdit;
	edit_del_sup = new QLineEdit;
	edit_del_tip = new QLineEdit;



	lyFormDel->addRow(del_nr, edit_del_nr);
	lyFormDel->addRow(del_nume, edit_del_nume);
	lyFormDel->addRow(del_sup, edit_del_sup);
	lyFormDel->addRow(del_tip, edit_del_tip);
	delAp = new QPushButton("Sterge apartament");
	lyFormDel->addWidget(delAp);

	lyLeft->addWidget(formDel);

	QVBoxLayout* lyRadioBox = new QVBoxLayout;
	this->groupBox->setLayout(lyRadioBox);
	lyRadioBox->addWidget(radioSortNume);
	lyRadioBox->addWidget(radioSortSup);
	lyRadioBox->addWidget(radioSortSupAndTip);



	btnsort = new QPushButton("Sorteaza apartamente");
	lyRadioBox->addWidget(btnsort);



	//adaugam acest grup in partea stanga,
	//dupa componentele pentru adaugare in layout-ul vertical
	lyLeft->addWidget(groupBox);



	/*QVBoxLayout* lyRadioBox2 = new QVBoxLayout;
	this->filterBox->setLayout(lyRadioBox2);
	lyRadioBox2->addWidget(filtru_tip);
	lyRadioBox2->addWidget(filtru_sup);
	edit_filtru_tip = new QLineEdit;
	edit_filtru_sup = new QLineEdit;

	filtru = new QPushButton("Filtreaza apartamente");
	lyRadioBox2->addWidget(filtru);


	lyLeft->addWidget(filterBox);*/
	
	//incerc un combobox
	auto* filterL = new QHBoxLayout;
	filterL->addWidget(btnFilter);
	cmbFilter->addItem("Tip");
	cmbFilter->addItem("Suprafata");
	filterL->addWidget(cmbFilter);
	lyLeft->addLayout(filterL);

	// Buton folosit pentru a reincarca datele
	//i.e. afisam toti prop in tabel, in ordinea initiala din fisier
	reload_data = new QPushButton("Reload data");
	lyLeft->addWidget(reload_data);

	undo = new QPushButton("Undo");
	lyLeft->addWidget(undo);


	QWidget* right = new QWidget;
	QVBoxLayout* lyRight = new QVBoxLayout;
	right->setLayout(lyRight);

	int noLines = 10;
	int noColumns = 4;
	this->apartamente = new QTableWidget{ noLines, noColumns };
	apartamente->setSelectionBehavior(QAbstractItemView::SelectRows);
	QObject::connect(apartamente, &QTableWidget::currentCellChanged, [&](int currentRow, int currentCol, int pr, int pc) {
		//int indexRow = apartamente->currentRow();
		//int indexCell=apartamente->currentCellChanged()
		//apartamente->currentItem()->setBackground(QBrush{Qt::red, Qt::SolidPattern});
		//apartamente->rowAt(index);
		//apartamente->indexWidget(index);
		if (currentRow< 0) return;
		Locatar l = srv.getallLocatari()[currentRow];
		edit_del_nr->setText(std::to_string(l.getNrAp()).c_str());
		edit_del_nume->setText(l.getNumeProprietar().c_str());
		edit_del_tip->setText(l.getTipApartament().c_str());
		edit_del_sup->setText(std::to_string(l.getSuprafata()).c_str());
		});

	//setam header-ul tabelului
	QStringList tblHeaderList;
	tblHeaderList << "Nr apartament" << "Nume proprietar" << "Suprafata" << "Tip";
	this->apartamente->setHorizontalHeaderLabels(tblHeaderList);

	////optiune pentru a se redimensiona celulele din tabel in functie de continut
	//this->apartamente->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

	lyLeft->addWidget(btnReadonly);


	lyRight->addWidget(apartamente);

	lyMain->addWidget(left);
	lyMain->addWidget(right);

	//notificari
	lyLeft->addWidget(btnNotShow);
	guinot = new GUINotificari(srv);

	//butoane dinamice
	panelButtonsLayout = new QVBoxLayout;
	lyMain->addLayout(panelButtonsLayout);

	////slider
	//sliderGenerate = new QSlider{};
	//sliderGenerate->setMinimum(1);
	//sliderGenerate->setMaximum(srv.getallLocatari().size());

	/*lyMain->addWidget(sliderGenerate);*/
}



void LocatarGui::reload(vector<Locatar> apartamente) {
	this->apartamente->clearContents();
	this->apartamente->setRowCount(apartamente.size());

	int lineNumber = 0;
	for (auto& m : apartamente) {
		auto item = new QTableWidgetItem(QString::number(m.getNrAp()));
		item->setBackground(Qt::magenta);
		this->apartamente->setItem(lineNumber, 0, item);
		this->apartamente->setItem(lineNumber, 1, new QTableWidgetItem(QString::fromStdString(m.getNumeProprietar())));
		this->apartamente->setItem(lineNumber, 2, new QTableWidgetItem(QString::number(m.getSuprafata())));
		this->apartamente->setItem(lineNumber, 3, new QTableWidgetItem(QString::fromStdString(m.getTipApartament())));
		lineNumber++;
	}
	
}



void LocatarGui::connectSignals() 
{
	
	QObject::connect(addLocatar, &QPushButton::clicked, this, &LocatarGui::guiAdd);

	addLocatar->setStyleSheet("background-color: #fe7ee0");

	QObject::connect(modificaProp, &QPushButton::clicked, this, &LocatarGui::guiMod);

	modificaProp->setStyleSheet("background-color: #fe7ee0");

	QObject::connect(delAp, &QPushButton::clicked, this, &LocatarGui::guiDel);

	delAp->setStyleSheet("background-color: #fe7ee0");

	QObject::connect(btnsort, &QPushButton::clicked, [&]() {
		if (this->radioSortSup->isChecked())
			this->reload(srv.sortSup());
		else if (this->radioSortNume->isChecked())
			this->reload(srv.sortNume());
		else if (this->radioSortSupAndTip->isChecked())
			this->reload(srv.sortTipSup());
		});

	QObject::connect(btnReadonly, &QPushButton::clicked, [&]() {
		auto cosReadOnly = new CosReadOnly{ srv };
		cosReadOnly->show();
		});

	//QObject::connect(filtru, &QPushButton::clicked, [&]() {
	//	//string filtru_subs = this->editFilterCriteria->text().toStdString();
	//	if (this->filtru_sup->isChecked()) {
	//		try {
	//			this->reload(srv.filtrareSuprafata(50));
	//		}
	//		catch (RepoException& re) {
	//			QMessageBox::information(this, "Info", QString::fromStdString(re.getError()));
	//		}
	//	}
	//	else if (this->filtru_tip->isChecked()) {

	//		try {
	//			this->reload(srv.filtrareTip("garsoniera"));
	//		}
	//		catch (RepoException& re) {
	//			QMessageBox::information(this, "Info", "Eroare de validare");
	//		}
	//	}
	//	});

	QObject::connect(btnFilter, &QPushButton::clicked, [&]() {
		if (cmbFilter->currentText() == "Tip")
		{
			vector<Locatar> locatari = srv.filtrareTip("garsoniera");
			reload(srv.filtrareTip("garsoniera"));
		}
		else if (cmbFilter->currentText() == "Suprafata")
		{
			vector<Locatar> locatari = srv.filtrareSuprafata(50);
			reload(srv.filtrareSuprafata(50));
		}
		});

	QObject::connect(reload_data, &QPushButton::clicked, [&]() {
		this->reload(srv.getallLocatari());
		});



	QObject::connect(undo, &QPushButton::clicked, [&]() {
		try {
			srv.undo();
		}
		catch (RepoException& re) {
			QMessageBox::information(this, "Info", QString::fromStdString(re.getError()));
		}
		this->reload(srv.getallLocatari());
		});

	QObject::connect(btnNotShow, &QPushButton::clicked, [&]() {
		guinot->show();
		});
	QObject::connect(apartamente, &QTableWidget::itemSelectionChanged, [&]() {
		auto selItms = apartamente->selectedItems();
		for (auto item : selItms) {
			/*qDebug() << item->text();*/
			item->setBackground(Qt::magenta); // sets magenta background
			item->setForeground(Qt::blue);
			item->setData(Qt::UserRole, QString{ "informatii care nu se vad" });
			item->setCheckState(Qt::Checked);
			item->setIcon(QApplication::style()->standardIcon(QStyle::SP_BrowserReload));

		}

		});
	/*QObject::connect(sliderGenerate, &QSlider::sliderReleased, [&]() {
		qDebug() << sliderGenerate->value();
		});*/

}



void LocatarGui::guiAdd() {
	try {
		//preluare detalii din QLineEdit-uri
		int nr = edit_nr->text().toInt();
		string nume = edit_nume->text().toStdString();
		double sup = edit_sup->text().toDouble();
		string tip = edit_tip->text().toStdString();


		//optional - golim QLineEdit-urile dupa apasarea butonului
		edit_nr->clear();
		edit_nume->clear();
		edit_sup->clear();
		edit_tip->clear();

		this->srv.addLocatar(nr, nume, sup, tip);
		this->reload(this->srv.getallLocatari());
		addButtons();

		QMessageBox::information(this, "Info", QString::fromStdString("Locatar adaugat cu succes."));

	}
	catch (RepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getError()));
	}
	catch (ValidateException& ve) {
		QMessageBox::warning(this, "Warning","Validation error");
	}

}

void LocatarGui::guiMod() {
	try {
		//preluare detalii din QLineEdit-uri
		int mod_nr = edit_mod_nr->text().toInt();
		string mod_nume = edit_mod_nume->text().toStdString();
		double mod_sup = edit_mod_sup->text().toDouble();
		string mod_tip = edit_mod_tip->text().toStdString();



		//optional - golim QLineEdit-urile dupa apasarea butonului
		edit_mod_nr->clear();
		edit_mod_nume->clear();
		edit_mod_sup->clear();
		edit_mod_tip->clear();



		this->srv.modificaProp(mod_nr, mod_nume, mod_sup, mod_tip);
		this->reload(this->srv.getallLocatari());
		

		//afisam un mesaj pentru a anunta utilizatorul ca melodia s-a adaugat
		QMessageBox::information(this, "Info", QString::fromStdString("Apartament modificat cu succes."));
	}
	catch (RepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getError()));
	}
	catch (ValidateException& ve) {
		QMessageBox::warning(this, "Warning", "Validation error");
	}
	//pt fereastra noua
	//QWidget* windowWidget = new QWidget;
	//QWidget* fromwidget = new QWidget;
	//QFormLayout* form4 = new QFormLayout;

	//QLabel* denLabel = new QLabel("Nr: ");
	//QLineEdit* denLine = new QLineEdit;
	//form4->addRow(denLabel, denLine);

	//QLabel* producatorLabel = new QLabel("Producator: ");
	//QLineEdit* producatorLine = new QLineEdit;
	//form4->addRow(producatorLabel, producatorLine);



	//QLabel* subsLabel = new QLabel("Model: ");
	//QLineEdit* subsLine = new QLineEdit;
	//form4->addRow(subsLabel, subsLine);



	//QLabel* pretLabel = new QLabel("Tip: ");
	//QLineEdit* pretLine = new QLineEdit;
	//form4->addRow(pretLabel, pretLine);



	//fromwidget->setLayout(form4);



	//QVBoxLayout* vLayout = new QVBoxLayout;
	//vLayout->addWidget(fromwidget);



	//QPushButton* modifica = new QPushButton("&Modifica");
	//QObject::connect(modifica, &QPushButton::clicked, [=]() {
	//	try {
	//		this->srv.modificaMas(denLine->text().toInt(), producatorLine->text().toStdString(), subsLine->text().toStdString(), pretLine->text().toStdString());
	//		this->reload(this->srv.getallMas());
	//		windowWidget->close();
	//	}
	//	catch (const ValidateException& ve) {
	//		QMessageBox msgBox;
	//		QMessageBox::warning(this, "warning", "Validation error");
	//		windowWidget->close();
	//	}
	//	catch (const RepoException& re) {
	//		QMessageBox::warning(this, "warning", QString::fromStdString(re.get_err()));
	//		windowWidget->close();
	//	}
	//	});
	//vLayout->addWidget(modifica);

	//windowWidget->setLayout(vLayout);
	//windowWidget->show();

}



void LocatarGui::guiDel() {
	try {
		//preluare detalii din QLineEdit-uri
		int del_nr = edit_del_nr->text().toInt();
		string del_nume = edit_del_nume->text().toStdString();
		double del_sup = edit_del_sup->text().toDouble();
		string del_tip = edit_del_tip->text().toStdString();
		qDebug() << del_nr;
		qDebug() << del_sup;

		//optional - golim QLineEdit-urile dupa apasarea butonului
		edit_del_nr->clear();
		edit_del_nume->clear();
		edit_del_sup->clear();
		edit_del_tip->clear();

		this->srv.sterge(del_nr, del_nume, del_sup, del_tip);
		this->reload(this->srv.getallLocatari());
		
		QMessageBox::information(this, "Info", QString::fromStdString("Apartament sters cu succes."));
	}
	catch (RepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getError()));
	}
	catch (ValidateException& ve) {
		QMessageBox::warning(this, "Warning", "Validation error");
	}

}