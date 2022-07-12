#pragma once
#include <QAbstractTableModel>
#include<qmessagebox.h>
#include "Locatar.h"
#include <vector>
#include <qdebug.h>


class TableModel :public QAbstractTableModel {
	std::vector<Locatar>Locatars;
public:
	TableModel(const std::vector<Locatar>& Locatars) :Locatars{ Locatars } {}

	int rowCount(const QModelIndex& parent = QModelIndex())const override {
		return Locatars.size();
	}
	int columnCount(const QModelIndex& parent = QModelIndex())const override {
		return 4;
	}
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole)const override {
		qDebug() << "row:" << index.row() << " col:" << index.column() << " role" << role;
		if (role == Qt::DisplayRole) {
			Locatar c = Locatars[index.row()]; 
			if (index.column() == 0) {
				return QString::fromStdString(std::to_string(c.getNrAp()));
			}
			else if (index.column() == 1) {
				return QString::fromStdString(c.getNumeProprietar());

			}
			else if (index.column() == 2) {
				return QString::fromStdString(std::to_string(c.getSuprafata()));

			}
			else if (index.column() == 3) {
				return QString::fromStdString(c.getTipApartament());

			}
		}

		return QVariant{};
	}

	void setLocatars(const std::vector<Locatar>& Locatars) {
		this->Locatars = Locatars;
		auto topLeft = createIndex(0, 0);
		auto bottomR = createIndex(rowCount(), columnCount());
		emit dataChanged(topLeft, bottomR);
		emit layoutChanged();
	}
	QVariant headerData(int section, Qt::Orientation orientation, int role) const {

		if (role == Qt::DisplayRole) {
			if (orientation == Qt::Horizontal) {
				return QString("col %1").arg(section);
			}
			else {
				return QString("row %1").arg(section);
			}
		}
		return QVariant();
	}
};