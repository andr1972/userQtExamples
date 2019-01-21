/*
The MIT License (MIT)
*/

#include <string>
#include <QFile>
#include <QByteArray>
#include <QImage>
#include <QIcon>
#include "BExampleModel.h"

/**
 * @brief BExampleModel::BExampleModel
 * @param parent: QObject parent for this object
 *
 * Init small tree
 */

BExampleModel::BExampleModel(QObject *parent) : QAbstractItemModel(parent)
{
  root = new TreeNode(nullptr, QString("root"), "value");
  TreeNode *newNode = new TreeNode(root, "key", "val");
  root->children.append(newNode);
  TreeNode *newSubNode = new TreeNode(newNode, "subkey", "subval");
  newNode->children.append(newSubNode);
  newNode = new TreeNode(root, "key2", "val2");
  root->children.append(newNode);
}

/**
 * @brief BExampleModel::~BExampleModel
 *
 * If a root document was allocated, it is deleted.
 *
 */

BExampleModel::~BExampleModel()
{
  if(root != nullptr)
    freeTraverse(root);
}


bool BExampleModel::isModified()
{
  return modified;
}


void BExampleModel::resetModified()
{
  modified = false;
}

/**
 * @brief BExampleModel::freeTraverse
 *
 * Performs a traversal of the tree starting from the given node.
 * This function is used by the destructor to delete the document tree.
 *
 * @param node: Node at which to start the traversal.
 *
 */

void BExampleModel::freeTraverse(TreeNode *node)
{
  for(auto child : node->children) {
      freeTraverse(child);
  }

  delete node;
}


/**
 * @brief BExampleModel::headerData
 *
 * Provide text for the two headers in the Qt tree view.
 * @note the check for Qt::DisplayRole is required otherwise nothing is displayed.
 *
 * @param section: The column number
 * @param orientation: Qt allows for horizontal or verticle headings
 * @param role: Qt role.
 *
 * @return Returns a string (as a variant) to use for the column heading.
 */

QVariant BExampleModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  Q_UNUSED(orientation);
  if (role != Qt::DisplayRole)
      return QVariant();

  if(section == 0)
    return QVariant(QString("Key"));
  else
    return QVariant(QString("Value"));
}


/**
 * @brief BExampleModel::index
 *
 * This function maps from the Qt abstract model row/column to the model's
 * concept of row/column.
 *
 * The @c internalPointer item of QModelIndex stores a pointer to a TreeNode structure.
 *
 * @param row: The row index of the item under its parent item.
 * @param column: The column index of the item
 * @param parent: The index of the item's parent in the tree view.
 * @return Returns a QModelIndex that locates the corresponding item in the UI;
 * Returns an empty index if the @c row and @c column are out of bounds.
 *
 */

QModelIndex BExampleModel::index(int row, int column, const QModelIndex &parent) const
{
  TreeNode *parentNode, *childNode;

  // If the index is out of bounds, return an empty index.
  if(hasIndex(row, column, parent) == false) {
      return QModelIndex();
  }

  // If there is no parent, then Qt is asking us for the index of the root item.
  if(parent.isValid() == false) {
    parentNode = root;
  }
  else {
    parentNode = static_cast<TreeNode *>(parent.internalPointer());
  }

  childNode = parentNode->children[row];
  return createIndex(row, column, childNode);
}


/**
 * @brief BExampleModel::parent
 *
 * Similar to index(), this function receives a QModelIndex and returns
 * an index for its parent.
 *
 * @param index: The index to find the parent of
 * @return Returns a QModelIndex for the parent; Returns an empty index if the
 * parent is the root item.
 */

QModelIndex BExampleModel::parent(const QModelIndex &index) const
{

  if(!index.isValid())
    return QModelIndex();

  TreeNode *childNode  = static_cast<TreeNode *>(index.internalPointer());
  TreeNode *parentNode = childNode->parent;

  if(parentNode == root)
    return QModelIndex();

  return createIndex(parentNode->row(), 0, parentNode);
}


/**
 * @brief BExampleModel::rowCount
 *
 * Returns the number of rows (children) under the parent index.
 *
 * @param parent: Index of the parent item
 * @return Returns the number of children under the given parent.
 */

int BExampleModel::rowCount(const QModelIndex &parent) const
{
  TreeNode *parentNode;


  if(parent.isValid() == false)
      parentNode = root;
  else
      parentNode = static_cast<TreeNode *>(parent.internalPointer());

  return parentNode->children.count();
}


/**
 * @brief BExampleModel::columnCount
 *
 * Returns the number of columns under the parent index.
 *
 * @param parent: Index of the parent item
 * @return Returns 2 columns, regardless of parent.
 */

int BExampleModel::columnCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent)

  // Two columns: Key, and Value.
  return 2;
}


/**
 * @brief BExampleModel::data
 *
 * Returns a variant holding the data at the given model index.
 *
 * @param index: The index for which to return data
 * @param role: The Qt role; we return an empty variant for all but DisplayRole
 * @return Returns a variant with the data to display at the given model index.
 */

QVariant BExampleModel::data(const QModelIndex &index, int role) const
{

  if(!index.isValid())
    return QVariant();

  // Use the index to retrieve the internal pointer
  TreeNode *item = static_cast<TreeNode *>(index.internalPointer());



  if (role == Qt::DecorationRole && index.column() == 0)
  {
        QIcon icon;
        if (item->children.size()>0)
            icon = iconProvider.icon(QFileIconProvider::Folder);
        else
            icon = iconProvider.icon(QFileIconProvider::File);
        return icon;
  }
  if(role != Qt::DisplayRole)
    return QVariant();

  // Column 1 is the data item, column 0 is the key
  if(index.column() == 0)
    return item->key;
  else {
      return item->value;
  }
}


/**
 * @brief BExampleModel::setData
 *
 * Called by Qt when the user edits an item in the tree view. Either the
 * key (column 0) or the value (column 1) has been changed.
 *
 * The updateNode() function is called to set the new value and to propagate the
 * changes up to the root of the document tree.
 *
 * Emits the dataChanged signal once the new value is set.
 *
 * @param index: The model index of the item that was edited.
 * @param value: The new value provided by the user via the UI.
 * @param role: The Qt role (not used in this function)
 * @return Returns true if the change was made; false otherwise.
 */

bool BExampleModel::setData(const QModelIndex &index, const QVariant &value, int role)
{

  if(data(index, role) != value) {

      // Need to get the parent (object or array) and set the key/value
      // To update only the key, need to first remove the key, then add new key/value.
      TreeNode *item = static_cast<TreeNode *>(index.internalPointer());
      if(index.column() == 0) {

          // An empty key means the tree item corresponds to an item in a JsonArray.
          // Edits are disallowed, since it's not really a key.
          if(value.toString().isEmpty() == true)
            return false;

          item->key = value.toString();
          //updateNode(item, index.row(), item->key, newKey, item->value);
      }
      else {
          if(index.column() == 1) {
              item->value = value.toString();
              //QJsonValue newValue = jsonFromVariant(value);
              //updateNode(item, index.row(), item->key, item->key, newValue);
          }
      }

      modified = true;
      emit dataChanged(index, index, QVector<int>() << role);
      return true;
  }

  return false;
}


/**
 * @brief BExampleModel::flags
 *
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
Qt::ItemFlags BExampleModel::flags(const QModelIndex &index) const
{
  if (!index.isValid())
    return Qt::NoItemFlags;

  TreeNode *item = static_cast<TreeNode *>(index.internalPointer());

  // Do not allow edits on keys of array items.
  if(item->key.isEmpty() && index.column() == 0)
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
  else
    return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

