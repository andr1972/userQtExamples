/* The MIT License (MIT)
 * Based on sample https://github.com/jcb9000/qjtree
*/

#pragma once

#include <QString>
#include <QAbstractTableModel>
#include "ivariantable.h"

class BTableModel : public QAbstractTableModel
{
  Q_OBJECT    
private:  
  QList<IVariantable*> variantableList;
  QStringList headerList;
public:
  explicit BTableModel(QObject *parent);
  virtual ~BTableModel() override;

  QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

  // Basic functionality:
  QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;

  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
  Qt::ItemFlags flags(const QModelIndex& index) const override;

  void setList(QList<IVariantable*> &variantableList, QStringList &headerList);
};
