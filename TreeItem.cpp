#include <QStringList>
#include "TreeItem.h"

TreeItem::TreeItem(QSqlRecord record, TreeItem *parent):
    m_record(record)
{
    m_parentItem = parent;
    if(m_parentItem)
        setModel(m_parentItem->model());

    m_itemFlags = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

TreeItem::TreeItem()
{

}

TreeItem::~TreeItem()
{
    if(!m_childItems.isEmpty())
        qDeleteAll(m_childItems);
}

void TreeItem::appendChild(TreeItem *item)
{
    m_childItems.append(item);
}

void TreeItem::addChild(TreeItem *child, int position)
{
//    if(position < 0 || position > childItems.size())
//        return;
    m_childItems.insert(position, child);
    child->setParent(this);
}

void TreeItem::detachChild(TreeItem *child)
{
    child->setParent(0);
    if(!m_childItems.isEmpty())
        m_childItems.removeAll(child);
}

TreeItem *TreeItem::child(int row)
{
    return m_childItems.value(row);
}

QList<TreeItem *> TreeItem::childItems()
{
    return m_childItems;
}

int TreeItem::childRow(TreeItem *child)
{
    return m_childItems.indexOf(child);
}

int TreeItem::childCount() const
{
    return m_childItems.count();
}

QVariant TreeItem::data(int column, int role) const
{
    if(role == Qt::DisplayRole)
    {
        if(column == 0)
        {
            return m_record.value("name");
        }
    }
    return QVariant();
}

TreeItem *TreeItem::parent()
{
    return m_parentItem;
}

TreeModel *TreeItem::model()
{
    return m_model;
}

void TreeItem::setModel(TreeModel *model)
{
    m_model = model;
}

void TreeItem::setFlags(Qt::ItemFlags itemFlags)
{
    m_itemFlags = itemFlags;
}

int TreeItem::row() const
{
    if (m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<TreeItem*>(this));

    return 0;
}

void TreeItem::setParent(TreeItem *parent)
{
    /// Parent und Child müssen im selben Model sein
    m_parentItem = parent;
    if(m_parentItem)
        setModel(m_parentItem->model());
}

Qt::ItemFlags TreeItem::flags()
{
    return m_itemFlags;
}

int TreeItem::position()
{
    return parent()->childRow(this);
}
