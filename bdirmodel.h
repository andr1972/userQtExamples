/* The MIT License (MIT)
 * Based on sample https://github.com/jcb9000/qjtree
*/

#pragma once

#include <QString>
#include <QAbstractItemModel>
#include <QFileIconProvider>

/**
 * An implementation of the QAbstractItemModel class. This class re-implements
 * the necessary virtual functions to display and edit model elements in a QTreeView.
 *
 */
class BDirModel : public QAbstractItemModel
{
  Q_OBJECT
    struct TreeNode {
      TreeNode *parent;
      QList<TreeNode *> children;
      QFileInfo fi;
      bool opened = false;
      TreeNode(TreeNode *p, QFileInfo fi) : parent(p),fi(fi) {}
      ~TreeNode() {}

      /**
       * @return Returns an integer corresponding to the row of this node under its
       * parent. For the root of the tree, the row count is always 0.
       */
      int row() const {
        if(parent != nullptr)
          return parent->children.indexOf(const_cast<TreeNode *>(this));
        return 0;
      }
    };
private:
  TreeNode      *root;
  void freeTraverse(TreeNode *node);
  QFileIconProvider iconProvider;
  int maxLevel;
  int usualSize;
public:
  explicit BDirModel(QObject *parent, int maxLevel, int usualSize);
  virtual ~BDirModel() override;

  // Header:
  QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

  // Basic functionality:
  QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
  QModelIndex parent(const QModelIndex &index) const override;

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;

  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
  bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

  Qt::ItemFlags flags(const QModelIndex& index) const override;
};
