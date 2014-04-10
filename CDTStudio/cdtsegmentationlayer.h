#ifndef CDTSEGMENTATIONLAYER_H
#define CDTSEGMENTATIONLAYER_H

#include <QObject>
#include <QMap>
#include <QVector>
#include <QVariant>
#include <QAction>
#include "cdtprojecttreeitem.h"
#include "cdtbaseobject.h"
#include "cdtattributeswidget.h"
#include "cdttrainingsamplesform.h"

class CDTClassification;
struct CDTDatabaseConnInfo;
typedef QMap<int,QString> TrainingSample;
typedef QList<TrainingSample > CDTTrainingSampleList;

class CDTSegmentationLayer:public CDTBaseObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString shapefilePath READ shapefilePath WRITE setShapefilePath NOTIFY shapefilePathChanged)
    Q_PROPERTY(QString markfilePath READ markfilePath WRITE setMarkfilePath NOTIFY markfilePathChanged)
    Q_PROPERTY(QString method READ method)

public:
    explicit CDTSegmentationLayer(QString imagePath,QObject *parent = 0);

    friend QDataStream &operator<<(QDataStream &out,const CDTSegmentationLayer &segmentation);
    friend QDataStream &operator>>(QDataStream &in, CDTSegmentationLayer &segmentation);

    void addClassification(CDTClassification* classification);

    QString name()const;
    QString shapefilePath() const;
    QString markfilePath() const;
    QString method()const;
    CDTDatabaseConnInfo databaseURL() const;
    QString imagePath()const;

signals:
    void nameChanged();
    void shapefilePathChanged();
    void markfilePathChanged();
    void methodParamsChanged();
    void segmentationChanged();
    void removeSegmentation(CDTSegmentationLayer*);
public slots:
    void updateTreeModel(CDTProjectTreeItem* parent);
    void onContextMenuRequest(QWidget *parent);
    void onActionRename();
    void addClassification();
    void remove();
    void removeClassification(CDTClassification *);
    void removeAllClassifications();
    void onTrainingSamples();
    void setName(const QString& name);
    void setShapefilePath(const QString &shpPath);
    void setMarkfilePath(const QString &mkPath);
    void setMethodParams(const QString& methodName,const QMap<QString,QVariant> &params);
    void setDatabaseURL(CDTDatabaseConnInfo url);
private:
    QString m_name;
    QString m_imagePath;
    QString m_shapefilePath;
    QString m_markfilePath;
    CDTDatabaseConnInfo    m_dbUrl;
    QString m_method;    
    QMap<QString,QVariant> m_params;
    QVector<CDTClassification *> classifications;
    CDTTrainingSampleList trainingSampleList;

    CDTTrainingSamplesForm* trainingSamplesForm;

    QAction *addClassifications;
    QAction *actionRemoveSegmentation;
    QAction *actionRemoveAllClassifications;
    QAction *actionRename;
    QAction *actionTrainingSamples;

    CDTProjectTreeItem* shapefileItem;
    CDTProjectTreeItem* markfileItem;
    CDTProjectTreeItem* paramRootItem;
    CDTProjectTreeItem* paramRootValueItem;
};
QDataStream &operator<<(QDataStream &out,const CDTSegmentationLayer &segmentation);
QDataStream &operator>>(QDataStream &in, CDTSegmentationLayer &segmentation);
#endif // CDTSEGMENTATIONLAYER_H
