#ifndef CDTPROJECTWIDGET_H
#define CDTPROJECTWIDGET_H

#include <QWidget>
#include "cdtproject.h"
#include "cdtprojecttreemodel.h"
#include "mainwindow.h"
#include <QPoint>
#include <QModelIndex>
#include <QFile>
#include <qgsmapcanvas.h>
#include <qgsmaptool.h>

class CDTProjectWidget : public QWidget
{
    Q_OBJECT
public:
    friend class CDTProjectTabWidget;
    friend class CDTProjectWidget;
    friend class MainWindow;
    explicit CDTProjectWidget(QWidget *parent = 0);
    ~CDTProjectWidget();

    bool readProject(QString &filepath);
    bool writeProject();
    bool saveAsProject(QString &path);
    int  maybeSave();
    QString filePath();
    bool closeProject(CDTProjectTabWidget *parent,const int &index);

signals:
    void projectChanged(CDTProject*);
public slots:
    void onContextMenu(QPoint pt,QModelIndex index);
    void setProjectName(const QString& name);
    void setProjectPath(const QString& path);
    void setIsChanged();
    bool saveProject(QString &path);

    void onZoomOutTool(bool toggle);
    void onZoomInTool(bool toggle);
    void onPanTool(bool toggle);
    void onFullExtent();
    void appendLayers(QList<QgsMapLayer*> layers);
    void removeLayer(QList<QgsMapLayer*> layer);
    void refreshMapCanvas(bool zoomToFullExtent=true);
    void onItemChanged(QStandardItem*item);

private slots:
    void untoggledToolBar();
    void onHehe();
private:
    bool isChanged;
    CDTProject *project;
    QFile file;
    CDTProjectTreeModel* treeModel;

    QgsMapCanvas* mapCanvas;
    QToolBar *initToolBar();
    QgsMapTool *panTool;
    QgsMapTool *zoomInTool;
    QgsMapTool *zoomOutTool;
    QAction *actionZoomOut;
    QAction *actionZoomIn;
    QAction *actionPan;
    QAction *actionFullExtent;

    QList<QgsMapLayer*>     activeLayers;
    QMap<QgsMapLayer*,bool> layersVisible;

};

#endif // CDTPROJECTWIDGET_H
