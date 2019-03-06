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
      if(section == 0)
        return QVariant(QString("Level"));
      else
        return QVariant(QString("Index"));
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
    return 5;
}


int BTableModel::columnCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent)
  // Two columns: Key, and Value.
  return 2;
}

QVariant BTableModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
      return QVariant();

    if(role != Qt::DisplayRole)
      return QVariant();

    if(index.column() == 0)
    {
        return "level_"+QString::number(index.row());
    }
    else
    {
        return "index_"+QString::number(index.row());
    }
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

