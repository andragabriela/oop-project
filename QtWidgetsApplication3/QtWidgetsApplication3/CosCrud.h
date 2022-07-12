#pragma once

#include "service.h"

#include <QtWidgets/qwidget.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qspinbox.h>
#include <qmessagebox.h>
#include <QtWidgets/qcombobox.h>
#include <QTWidgets/qgridlayout.h>

class GUINotificari : public QWidget, public Observer {
private:
    ServiceLocatar& srv;

    QListWidget* lst = new QListWidget;

    QLineEdit* Nr = new QLineEdit;
    QLineEdit* Nume = new QLineEdit;
    QLineEdit* Suprafata = new QLineEdit;
    QLineEdit* Tip = new QLineEdit;

    QPushButton* btnNotAdd = new QPushButton("&Adauga cos");
    QPushButton* btnNotGen = new QPushButton("&Genereaza random");
    QSpinBox* spinBox = new QSpinBox;
    QPushButton* btnNotClear = new QPushButton("&Sterge cos");
    QPushButton* btnNotExportHTML = new QPushButton("&Exporta HTML");
    QLineEdit* Path = new QLineEdit;

    //pt slider
    
    QLineEdit* editNoSlider2;
    QLabel* lblSlider2;
    QSlider* sliderGenerate;
    // constructor methods
    void initGUI() {
        QHBoxLayout* htable;
        QWidget* panel1, * panel2;
        QVBoxLayout* p1l, * p2l;

        // horizontal table
        htable = new QHBoxLayout;
        panel1 = new QWidget;
        panel2 = new QWidget;
        htable->addWidget(panel1);
        htable->addWidget(panel2);
        p1l = new QVBoxLayout(panel1);
        p2l = new QVBoxLayout(panel2);
        panel1->setLayout(p1l);
        panel2->setLayout(p2l);
        setLayout(htable); 

        //// panel 1
        p1l->addWidget(lst);

        // panel 2
        auto* card = new QFormLayout;
        card->addRow("Nr Apartament", Nr);
        card->addRow("Nume", Nume);
        card->addRow("Suprafata", Suprafata);
        card->addRow("Tip", Tip);
        p2l->addLayout(card);
        p2l->addStretch();

        //notificari
        auto* notL1 = new QHBoxLayout;
        notL1->addWidget(btnNotAdd);
        notL1->addWidget(btnNotClear);
        p2l->addLayout(notL1);
        auto* notL2 = new QHBoxLayout;
        notL2->addWidget(btnNotGen);
        /*notL2->addWidget(spinBox);*/
        p2l->addLayout(notL2);
        auto* notL3 = new QHBoxLayout;
        QLabel* lblPath = new QLabel("Nume fisier");
        notL3->addWidget(lblPath);
        notL3->addWidget(Path);
        notL3->addWidget(btnNotExportHTML);
        p2l->addLayout(notL3);

        sliderGenerate = new QSlider{};
        sliderGenerate->setMinimum(1);
        sliderGenerate->setMaximum(srv.getallLocatari().size());

        notL2->addWidget(sliderGenerate);
    }

    template<class T>
    void loadData(T& collection) {
        lst->clear();
        for (const auto& l : collection) {
            lst->addItem(QString::fromStdString(std::to_string(l.getNrAp()) + " " + l.getNumeProprietar()+" "+ std::to_string(l.getSuprafata())+" "+l.getTipApartament()));
        }
    }

    void init_connect() {
        // lista
        QObject::connect(lst, &QListWidget::itemSelectionChanged, [&]() {
            if (lst->selectedItems().isEmpty()) {
                //daca nu e nimic selectat golesc campurile
                Nr->setText("");
                Nume->setText("");
                Suprafata->setText("");
                Tip->setText("");
                return;
            }
            auto* currentItem = lst->selectedItems().at(0);
            string text = currentItem->text().toStdString();
            string nrt = text.substr(0, text.find(" "));
            int nr_ap = std::stoi(nrt);
            auto loc = srv.findLoc(nr_ap);
            Nr->setText(QString::fromStdString(std::to_string(loc.getNrAp())));
            Nume->setText(QString::fromStdString(loc.getNumeProprietar()));
            Suprafata->setText(QString::fromStdString(std::to_string(loc.getSuprafata())));
            Tip->setText(QString::fromStdString(loc.getTipApartament()));
            });


        QObject::connect(btnNotAdd, &QPushButton::clicked, [&]() {
            auto apartament = Nr->text().toInt();
            try {
                srv.addToWishlist(apartament);
                vector<Locatar> loc = srv.getAllWishlist();
                loadData(loc);
            }
            catch (RepoException& re) {
                QMessageBox::warning(this, "Warning", QString::fromStdString(re.getError()));
            }
            });
        QObject::connect(btnNotClear, &QPushButton::clicked, [&]() {
            srv.deleteAll();
            lst->clear();
            QMessageBox::warning(this, "Warning", "Lista de notificari a fost stearsa!");
            });
      /*  QObject::connect(btnNotGen, &QPushButton::clicked, [&]() {
            int nr = spinBox->value();
            try {
                srv.addRandom(nr);
                vector<Locatar> loc = srv.getAllWishlist();
                loadData(loc);
            }
            catch (RepoException& re) {
                QMessageBox::warning(this, "Warning", QString::fromStdString(re.getError()));
            }
            });*/
        QObject::connect(sliderGenerate, &QSlider::sliderReleased, [&]() {
            qDebug() << sliderGenerate->value();
            });
        QObject::connect(btnNotGen, &QPushButton::clicked, [&]() {
            int noSongs = this->sliderGenerate->value();
            srv.addRandom(noSongs);
            vector<Locatar> loc = srv.getAllWishlist();
            loadData(loc);
            });
        QObject::connect(btnNotExportHTML, &QPushButton::clicked, [&]() {
           string path = Path->text().toStdString();
            srv.exportNotificariHTML(path);
            });
        
    }

public:
    explicit GUINotificari(ServiceLocatar& srv) : srv{ srv } {
        initGUI();
        loadData(srv.getAllWishlist());
        init_connect();
    }
    void update()override {
        loadData(srv.getAllWishlist());
    }

    ~GUINotificari() {
        srv.removeObserver(this);
    }
};
