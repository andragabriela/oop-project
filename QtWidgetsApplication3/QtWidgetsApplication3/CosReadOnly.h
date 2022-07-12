#pragma once
#include <qwidget.h>
#include <qtimer.h>
#include <QtWidgets/QHBoxLayout>
#include <qpushbutton.h>
#include <qlistwidget.h>
#include <qtablewidget.h>
#include <qlineedit.h>
#include <qstring.h>
#include <qlabel.h>
#include <vector>
#include <qpainter.h>
#include <qimage.h>

#include "observer.h"
#include "Service.h"

class CosReadOnly :public QWidget, public Observer {
	ServiceLocatar& serv;
public:
	CosReadOnly(ServiceLocatar& serv) :serv{ serv } {
		serv.addObserver(this);
	}

	void paintEvent(QPaintEvent* ev)override {
		QPainter p{ this };

		auto img1 = QImage("ap1.jpg");
		auto img2 = QImage("ap2.jpg");
		auto img3 = QImage("ap3.jpg");
		auto img4 = QImage("gheorgheni.jpg");
		for (auto& car : serv.getAllWishlist()) {
			int x = rand() % 400;
			int y = rand() % 400;
			if (car.getTipApartament() == "garsoniera")
				p.drawImage(x, y, img1.scaled(300, 100));
			else if (car.getTipApartament() == "ap cu 2 camere")
				p.drawImage(x, y, img2.scaled(300, 100));
			else if (car.getTipApartament() == "ap cu 3 camere")
				p.drawImage(x, y, img3.scaled(300, 100));
			else if (car.getTipApartament() == "gheorgheni")
				p.drawImage(x, y, img4.scaled(300, 100));
			else
				p.drawRect(x, y, 80, 80);
		}

	}

	void update()override {
		repaint();
	}

	~CosReadOnly() {
		serv.removeObserver(this);
	}

};