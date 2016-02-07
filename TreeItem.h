/*!
 *##########################################################
 * \class   TreeItem
 * \package Model
 * \author  Aziz Ghannami
 *          aziz.ghannami@gmail.com
 * \date    08.2013
 * \brief
 *
 *##########################################################
 */
#ifndef TREEITEM_H
#define TREEITEM_H

#include <QList>
#include <QVariant>
#include <QVector>
#include <QSqlRecord>

class TreeModel;

class TreeItem
{
    friend class TreeModel;

public:
    TreeItem(QSqlRecord record, TreeItem *parent = 0);
    TreeItem();
    ~TreeItem();

    TreeItem *child(int row);
    QList<TreeItem*> childItems();

    int childRow(TreeItem * child);
    int childCount() const;
    QVariant data(int column, int role) const;
    int row() const;
    void setParent(TreeItem * parent);
    TreeItem *parent();
    TreeModel * model();
    void setModel(TreeModel * model);
    void setFlags(Qt::ItemFlags itemFlags);
    Qt::ItemFlags flags();
    int position();   /// Die Position des Items bei seinem Parent
private:
    void appendChild(TreeItem *child);
    void addChild(TreeItem * child, int position);
    void detachChild(TreeItem * child);

    QList<TreeItem*> m_childItems;
    TreeItem *m_parentItem;
    TreeModel *m_model;
    Qt::ItemFlags m_itemFlags;
    QSqlRecord m_record;
};

#endif // TREEITEM_H
