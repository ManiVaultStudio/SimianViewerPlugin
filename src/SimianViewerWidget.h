#pragma once

#include "PointData.h"
#include "widgets/WebWidget.h"
#include <QMouseEvent>
#include <QComboBox>
#include <QList>
#include <QVariant>

class QWebEngineView;
class QWebEnginePage;
class QWebChannel;


class SimianViewerWidget;

class SimianViewerCommunicationObject : public hdps::gui::WebCommunicationObject
{
    Q_OBJECT
public:
    SimianViewerCommunicationObject(SimianViewerWidget* parent);

signals:
    void qt_setData(QString data); 
    void qt_setClusters(QString data);
    //void qt_resetView(QString data);
    void qt_setColor(QString data);
    void qt_setBackgroundColor(QString data);
    void qt_histChart(QString data);
    void qt_showFullHeatmap(QString data);
    void qt_borderSelectedCrossspeciesCluster(QString data);
    //void qt_generateScreenshot(QString data);
    //void qt_showExplorationMode(QString data);
    void qt_inspeciesClusterCounts(QString data);
    void qt_setRangeValue(QString data);
    void qt_addAvailableData(QString name);

public slots:
    //void js_passSelectionToQt(QVariantList data);
    void js_passClusterToQt(QVariant data);
    void js_removeSelectionFromScatterplot(QVariant data);
   // void js_generatedScreenshotData(QVariant data);

private:
    SimianViewerWidget* _parent;
};

class SimianViewerWidget : public hdps::gui::WebWidget
{
    Q_OBJECT
public:
    SimianViewerWidget();
    ~SimianViewerWidget() override;

    void addDataOption(const QString option);
    void setData(std::string visDataContent); 
    //void resetView(std::string visDataContent);
    void setClusters(QStringList visClusterContent);
    void setColor(QString visColorContent);
    void setBackgroundColor(QString visColorContent);
    void histChart(QString visColorContent);
    void showFullHeatmap(QString visColorContent); 
    void borderSelectedCrossspeciesCluster(QString visColorContent);
    //void generateScreenshot(QString visColorContent);
    //void showExplorationMode(QString visColorContent);
    void inspeciesClusterCounts(QString visCountClusterContent);
    void setRangeValue(QString visRangeValueContent);
protected:


signals:

    //void passSelectionToQt(std::vector<std::string> selectedIDs);
    void passClusterToQt(std::string clusterName);
    void removeSelectionFromScatterplot(std::string clusterName);
    //void generatedScreenshotData(std::string clusterName);

public:

    //void js_passSelectionToQt(std::vector<std::string> selectedIDs);
    void js_passClusterToQt(std::string clusterName);
    void js_removeSelectionFromScatterplot(std::string clusterName);
    //void js_generatedScreenshotData(std::string clusterName);

private slots:
    void initWebPage() override;

private:
    SimianViewerCommunicationObject* _communicationObject;


    /** Whether the web view has loaded and web-functions are ready to be called. */
    bool loaded;
    /** Temporary storage for added data options until webview is loaded */
    QList<QString> dataOptionBuffer;
};
