#pragma once

#include "SelectionListener.h"
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
    void qt_setColor(QString data);
    void qt_setRangeValue(QString data);
    void qt_addAvailableData(QString name);

public slots:
    void js_passSelectionToQt(QVariantList data);
    void js_passClusterToQt(QVariant data);

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
    void setClusters(QStringList visClusterContent);
    void setColor(QString visColorContent);
    void setRangeValue(QString visRangeValueContent);
protected:


signals:

    void passSelectionToQt(std::vector<std::string> selectedIDs);
    void passClusterToQt(std::string clusterName);

public:

    void js_passSelectionToQt(std::vector<std::string> selectedIDs);
    void js_passClusterToQt(std::string clusterName);

private slots:
    void initWebPage() override;

private:
    SimianViewerCommunicationObject* _communicationObject;


    /** Whether the web view has loaded and web-functions are ready to be called. */
    bool loaded;
    /** Temporary storage for added data options until webview is loaded */
    QList<QString> dataOptionBuffer;
};
