#include "SimianViewerWidget.h"
#include "PointData.h"
#include "ClusterData.h"
#include "util/FileUtil.h"
#include <fstream>
#include <string>
#include <iostream>
#include <QVBoxLayout>
#include <chrono>
#include <cassert>

SimianViewerCommunicationObject::SimianViewerCommunicationObject(SimianViewerWidget* parent)
    :
    _parent(parent)
{

}



void SimianViewerCommunicationObject::js_passSelectionToQt(QVariantList data)
{
    // convert data structure
    std::vector<std::string> selectedIDs;
    
    for (QVariantList::iterator j = data.begin(); j != data.end(); j++)
    {
        selectedIDs.push_back(((*j).toString()).toStdString()); // Print QVariant
    }
    _parent->js_passSelectionToQt(selectedIDs);
}

SimianViewerWidget::SimianViewerWidget() :
    loaded(false)
{
    Q_INIT_RESOURCE(simian_viewer_resources);
    _communicationObject = new SimianViewerCommunicationObject(this);
    init(_communicationObject);
}

SimianViewerWidget::~SimianViewerWidget()
{

}

void SimianViewerWidget::addDataOption(const QString option)
{
    if (loaded)
        emit _communicationObject->qt_addAvailableData(option);
    else
        dataOptionBuffer.append(option);
}

void SimianViewerWidget::setData(std::string visDataContent)
{ 
    //for (int i = 0; i < (*speciesContent).size(); i++)
    //{
    //    for (int j = 0; j < (*speciesContent)[i].size(); j++)
    //    {
    //       //std::cout << ((*speciesContent)[i][j]);
    //    }
    //    //std::cout << "\n";
    //}
    
    
    //std::string _jsonObject = *speciesContent;
    //_jsonObject += "[";
    //int i = 0;
    //while (i < data->getNumPoints()* data->getNumDimensions())
    //{
    //    _jsonObject += "{";
    //    /*qDebug() << dimNames.size();*/
    //    for (int j =  0; j < dimNames.size(); j++)
    //    {
    //        _jsonObject += '"';
    //        _jsonObject += dimNames[j].toStdString();
    //        _jsonObject += '"';
    //        _jsonObject += ':';
    //        _jsonObject += '"';
    //        _jsonObject += std::to_string(data->getValueAt(i));
    //        _jsonObject += '"';
    //        if (j < data->getNumDimensions() - 1)
    //        {
    //            _jsonObject += ',';
    //        }
    //        i = i + 1;
    //    }
    //    if (i< data->getNumPoints() * data->getNumDimensions()-1)
    //    {
    //        _jsonObject += "},";
    //    }
    //    else {
    //        _jsonObject += "}]";
    //    }
    //}
    //qDebug() << "Sending data";
    emit _communicationObject->qt_setData(QString((visDataContent).c_str()));
}


void SimianViewerWidget::setClusters(QStringList visClusterContent)
{
   // qDebug() << "Sending clusters";

    std::string _jsonObject;
    _jsonObject += "[";
    int i = 0;
    _jsonObject += "{";
    for (int j =  0; j < visClusterContent.size(); j++)
    {
        _jsonObject += '"';
        _jsonObject += std::to_string(j);
        _jsonObject += '"';
        _jsonObject += ':';
        _jsonObject += '"';
        _jsonObject += (visClusterContent[i]).toStdString();
        _jsonObject += '"';
        if (j < visClusterContent.size() - 1)
        {
            _jsonObject += ',';
        }
        i = i + 1;
    }
        _jsonObject += "}]";

    emit _communicationObject->qt_setClusters(QString((_jsonObject).c_str()));
}




void SimianViewerWidget::initWebPage()
{
    loaded = true;

    for (QString option : dataOptionBuffer) {
        emit _communicationObject->qt_addAvailableData(option);
    }
    dataOptionBuffer.clear();
    //qDebug() << "JS Ready for events";
}


void SimianViewerWidget::js_passSelectionToQt(std::vector<std::string> selectedIDs)
{   
    emit passSelectionToQt(selectedIDs);
}