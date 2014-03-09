#include "cdtprojectwidget.h"
#include "cdtprojecttabwidget.h"
#include <QFileDialog>
#include <QMessageBox>
#include "cdtbaseobject.h"

CDTProjectWidget::CDTProjectWidget(QWidget *parent) :
    QWidget(parent),
    project(new CDTProject(this)),
    treeModel(new CDTProjectTreeModel(this)),
    isChanged(false)
{
    connect(this,SIGNAL(projectChanged(CDTProject*)),treeModel,SLOT(update(CDTProject*)));
    connect(this,SIGNAL(projectChanged(CDTProject*)),this,SLOT(setIsChanged()));
    connect(project,SIGNAL(projectChanged(CDTProject*)),this,SIGNAL(projectChanged(CDTProject*)));

//    project->addImageLayer("image.1","c:/image1.tif");
//    project->addImageLayer("image.2","c:/image2.tif");
}

void CDTProjectWidget::onContextMenu(QPoint pt, QModelIndex index)
{
    CDTProjectTreeItem *item =(CDTProjectTreeItem*)treeModel->itemFromIndex(index);
    if(item ==NULL)
        return;
    int type = item->getType();

/*    if(type ==CDTProjectTreeItem::PROJECT_ROOT)
    {
        CDTProject *correspondingObject =(CDTProject*) item->getCorrespondingObject();
        correspondingObject->onContextMenu(this);
        emit projectChanged(project);
    }

    else if(type ==CDTProjectTreeItem::IMAGE_ROOT||type ==CDTProjectTreeItem::SEGMENTION_ROOT)
    {
        CDTImageLayer *correspondingObject =(CDTImageLayer*) item->getCorrespondingObject();
        correspondingObject->onContextMenu(this);
        emit projectChanged(project);
    }

    else if(type ==CDTProjectTreeItem::SEGMENTION||type ==CDTProjectTreeItem::CLASSIFICATION_ROOT)
    {
        CDTSegmentationLayer *correspondingObject =(CDTSegmentationLayer*) item->getCorrespondingObject();
        correspondingObject->onContextMenu(this);
        emit projectChanged(project);
    }*/
    CDTBaseObject* correspondingObject = item->getCorrespondingObject();
    if (correspondingObject)
    {
        correspondingObject->onContextMenuRequest(this);
//        emit projectChanged(project);
    }
}

bool CDTProjectWidget::readProject(QString &filepath)
{
//    QString filepath = QFileDialog::getOpenFileName(this,tr("Open an project file"),QString(),"*.cdtpro");
    QFileInfo info(filepath);
    if(info.exists())
    {
        setProjectFile(filepath);
        QDataStream in(&(file));
        quint32 magicNumber;
        in>>  magicNumber;
        if (magicNumber != (quint32)0xABCDEF)
            return false;
        in>>*project;
        emit projectChanged(project);
        isChanged = false;
        return true;
    }
    else
    {
        return false;
    }
}

bool CDTProjectWidget::writeProject()
{
    file.seek(0);
    QDataStream out(&file);
    out << (quint32)0xABCDEF;
    out<<*project;
    file.flush();
    isChanged = false;
    return true;
}

bool CDTProjectWidget::saveAsProject(QString &path)
{

    if (path.isEmpty())
        return false;
    else
    {
        return saveFile(path);
    }
}

bool CDTProjectWidget::saveProject(QString &path)
{
    if(file.size()==0)
    {
        return saveAsProject(path);
    }
    else
    {
        return writeProject();
    }
}

bool CDTProjectWidget::saveFile(QString &filepath)
{
    QFile savefile(filepath);

    if (!savefile.open(QFile::ReadWrite)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(filepath)
                             .arg(savefile.errorString()));
        return false;
    }
    savefile.seek(0);
    QDataStream out(&savefile);
    out << (quint32)0xABCDEF;
    out<<*project;
    savefile.flush();
    isChanged = false;
    return true;
}

int CDTProjectWidget::maybeSave()
{
    if(isChanged)
    {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, tr("Application"),
                     tr("The document has been modified.\n"
                        "Do you want to save your changes?"),
                                   QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if (ret == QMessageBox::Save)
        {
            writeProject();

        }
        return ret;
    }
    return -1;
}

QString CDTProjectWidget::filePath()
{
    return QFileInfo(file).absoluteFilePath();
}

bool CDTProjectWidget::closeProject(CDTProjectTabWidget* parent,const int &index)
{
    int a = this->maybeSave();
    if(a == QMessageBox::Cancel  )
    {
        return false;
    }
    else
    {
        parent->removeTab(index);
        return true;
    }
}


CDTProjectWidget::~CDTProjectWidget()
{
    file.close();
}

void CDTProjectWidget::setProjectName(const QString &name)
{
    project->setName(name);
    emit projectChanged(project);

}

void CDTProjectWidget::setProjectPath(const QString &path)
{
    project->setPath(path);
    emit projectChanged(project);
}

void CDTProjectWidget::setProjectFile(const QString &filepath)
{
    file.setFileName(filepath);
    file.open(QIODevice::ReadWrite);

    emit projectChanged(project);
}

void CDTProjectWidget::setIsChanged()
{
    if(!isChanged)
        isChanged = true;
}

