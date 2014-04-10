#include "cdtprojecttreemodel.h"
#include "cdtprojecttreeitem.h"
#include <QtCore>

CDTProjectTreeModel::CDTProjectTreeModel(QObject *parent) :
    QStandardItemModel(parent)
{
    setColumnCount(2);
    setHorizontalHeaderLabels(QStringList()<<tr("Layer")<<tr("Value"));
}

//void CDTProjectTreeModel::update(CDTProject *project)
//{
//    this->removeRows(0,this->rowCount());
//    CDTProjectTreeItem *item = new CDTProjectTreeItem(
//                CDTProjectTreeItem::PROJECT_ROOT,CDTProjectTreeItem::GROUP,project->projectName,project);
//    CDTProjectTreeItem *value = new CDTProjectTreeItem(
//                CDTProjectTreeItem::VALUE,CDTProjectTreeItem::EMPTY,project->projectPath,project);

//    this->invisibleRootItem()->setChild(0,0,item);
//    this->invisibleRootItem()->setChild(0,1,value);

//    for (int i=0;i<(project->images).size();++i)
//    {
//         project->images[i]->updateTreeModel(item);
//    }

//    emit updated();
//}
