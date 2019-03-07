/*
The MIT License (MIT)
*/
#include <string>
#include <QFile>
#include <QByteArray>
#include <QImage>
#include <QIcon>
#include "btablemodel.h"

BTableModel::BTableModel(QObject *parent) : QAbstractTableModel(parent)
{
}

BTableModel::~BTableModel()
{
}

QVariant BTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  Q_UNUSED(orientation);
  if (role != Qt::DisplayRole)
      return QVariant();
  if (orientation==Qt::Orientation::Horizontal)
  {
      return QVariant(headerList[section]);
  }
  else
    return QString::number(section);
}

QModelIndex BTableModel::index(int row, int column, const QModelIndex &parent) const
{
  if(hasIndex(row, column, parent) == false) {
      return QModelIndex();
  }
  return createIndex(row, column, nullptr);
}


int BTableModel::rowCount(const QModelIndex &parent) const
{
    return variantableList.count();
}


int BTableModel::columnCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent)
  return headerList.count();
}

QVariant BTableModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
      return QVariant();

    if(role != Qt::DisplayRole)
      return QVariant();

    return variantableList[index.row()]->getData(index.column());
}

/**
 * Returns flags for the item at the given model index.
 * An index corresponding to the key of an array item (column 0, empty key)
 * is enabled and selectable but cannot be edited.
 *
 * All other items are enabled, selectable, and editable.
 *
 * @param index: Index of the item for which flags are returned
 * @return  A Qt::ItemFlags value for the item at the given index
 *
 */
Qt::ItemFlags BTableModel::flags(const QModelIndex &index) const
{
  if (!index.isValid())
    return Qt::NoItemFlags;
  return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

void BTableModel::setList(QList<IVariantable*> &variantableList, QStringList &headerList)
{
    this->variantableList = variantableList;
    this->headerList = headerList;
}
