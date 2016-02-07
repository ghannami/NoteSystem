/*!
 *##########################################################
 * \class   TreeModel
 * \package Model
 * \author  Aziz Ghannami
 *          aziz.ghannami@gmail.com
 * \date    08.2013
 * \brief
 *
 *##########################################################
 */
#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include <QStringList>

class TreeItem;

class TreeModel : public QAbstractItemModel
{
public:
    TreeModel(QObject *parent = 0);
    ~TreeModel();

    QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;
    QVariant data ( TreeItem * treeItem, int column, int role = Qt::DisplayRole ) const;
    bool setData ( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );

    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const;
    QModelIndex index(TreeItem * item);
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    void setRoot(TreeItem * root);
    TreeItem * rootItem() const;
    TreeItem * item(QModelIndex index) const;
    void addItem(TreeItem *child, TreeItem *parent, int position);
    void clearModel();              /// !< \brief löscht alle TreeItem s unter dem rootItem
    void changeParent(TreeItem * item, TreeItem *newParent, int position);

    void setHeaders(QStringList headers, Qt::Orientation orientation = Qt::Horizontal);
    void updateModel();
private:
    TreeItem * m_rootItem;         /// Das root Element für die Baumstruktur des Models
                                    /// ab welchem Knoten das Model den Baum darstellen soll
    QStringList m_hHeaders;     /// Horizontal Header Liste
    QStringList m_vHeaders;     /// Vertical Header Liste
};
#endif // TREEMODEL_H
