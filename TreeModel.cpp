#include <QtGui>
#include "TreeItem.h"
#include "TreeModel.h"
#include <QSqlQuery>

TreeModel::TreeModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    setRoot(new TreeItem());
}

TreeModel::~TreeModel()
{
    delete m_rootItem;
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

void TreeModel::setRoot(TreeItem *root)
{
    m_rootItem = root;
    m_rootItem->setModel(this);
}

TreeItem *TreeModel::rootItem() const
{
    return m_rootItem;
}

void TreeModel::addItem(TreeItem * child, TreeItem * parent, int position)
{
    if(!parent)
    {
        qWarning()<<"FTreeModel::addItem der parent ist ungueltig";
        return;
    }
    beginInsertRows(index(parent), position, position);
    parent->addChild(child, position);
    endInsertRows();
}

void TreeModel::clearModel()
{
    /// löscht alle Unterelemente von m_rootItem
    /// die einzelne TreeItem löschen wiederum ihre Children im Destruktor
    foreach(TreeItem * child, m_rootItem->childItems())
    {
        child->detachChild(child);
        /// TODO
        delete child;
    }
    setRoot(m_rootItem);
}

void TreeModel::changeParent(TreeItem *item, TreeItem * newParent, int position)
{
    if(item->parent() == newParent)
        return;
    if(position < 0 || position > newParent->childCount())
        position = newParent->childCount();

    beginMoveRows(index(item->parent()), item->position(), item->position(), index(newParent), position);
    item->parent()->detachChild(item);
    newParent->addChild(item, position);
    endMoveRows();
}

void TreeModel::setHeaders(QStringList headers, Qt::Orientation orientation)
{
    if (orientation == Qt::Horizontal)
        m_hHeaders = headers;
    else
        m_vHeaders = headers;
    emit headerDataChanged(orientation, 0, headers.size() - 1);
}

void TreeModel::updateModel()
{
    clearModel();

}

TreeItem *TreeModel::item(QModelIndex index) const
{
    return static_cast<TreeItem*>(index.internalPointer());
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    TreeItem *treeItem = item(index);
    return data(treeItem, index.column(), role);
}

QVariant TreeModel::data(TreeItem *treeItem, int column, int role) const
{    
    if(treeItem)
        return treeItem->data(column, role);
    return QVariant();
}

bool TreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    return true;
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return item(index)->flags();
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        if(!m_hHeaders.isEmpty() && section >= 0 && section < m_hHeaders.size())
            return m_hHeaders.at(section);
        else
            return m_rootItem->data(section, role);
    }
    else{
        if(!m_vHeaders.isEmpty() && section >= 0 && section < m_vHeaders.size())
            return m_vHeaders.at(section);
        return QVariant();
    }
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent)
            const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItem *parentItem = 0;

    if (!parent.isValid())
        parentItem = rootItem();
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    TreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex TreeModel::index(TreeItem *item)
{
    QStack<TreeItem *> parents;
    TreeItem *curr = item;
    parents.push(curr);
    while(curr->parent())
    {
        parents.push(curr);
        curr = curr->parent();
    }
    /// der erste Index ist immer vom rootItem
    QModelIndex mIndex = createIndex(-1,-1, rootItem());
    parents.pop();
    TreeItem * tmpParent = rootItem();
    QModelIndex pIndex = mIndex;

    while(!parents.isEmpty())
    {
        TreeItem *tmp = parents.pop();
        mIndex = index(tmpParent->childRow(tmp), 0, pIndex);
        tmpParent = tmp;
        pIndex = mIndex;
    }

    return mIndex;
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem *parentItem = childItem->parent();

    if (parentItem == rootItem())
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    TreeItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem();
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    return parentItem->childCount();
}
