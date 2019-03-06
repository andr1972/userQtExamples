#ifndef TABLEMODEL_H
#define TABLEMODEL_H
#include <QAbstractTableModel>

class TableModel : public QAbstractTableModel
{
public:
    TableModel();
    int rowCount(const QModelIndex &parent = QModelIndex()) const override {return 5;}
    int columnCount(const QModelIndex &parent = QModelIndex()) const override {return 2;}
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {return "QVariant()";}
};

#endif // TABLEMODEL_H
