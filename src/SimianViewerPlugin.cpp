#include "SimianViewerPlugin.h"

#include "PointData.h"
#include "event/Event.h"
#include "ColorData.h"
#include <QtCore>
#include <QtDebug>
#include <QWebEngineView>
#include<ios>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

Q_PLUGIN_METADATA(IID "nl.tudelft.SimianViewerPlugin")

using namespace hdps;

// =============================================================================
// View
// =============================================================================

SimianViewerPlugin::SimianViewerPlugin(const PluginFactory* factory) :
    ViewPlugin(factory),
    _simianOptionsAction(nullptr)
{
    _simian_viewer = new SimianViewerWidget();
}

SimianViewerPlugin::~SimianViewerPlugin()
{
}

void SimianViewerPlugin::init()
{
    _simian_viewer->setPage(":/simian_viewer/simian_viewer.html", "qrc:/simian_viewer/");

    _simianOptionsAction = new SimianOptionsAction(*this, _core);
    connect(_simian_viewer, &SimianViewerWidget::passSelectionToQt, this, &SimianViewerPlugin::publishSelection);
    connect(_simian_viewer, &SimianViewerWidget::passClusterToQt, this, &SimianViewerPlugin::publishCluster);
    
    _eventListener.setEventCore(Application::core());
    _eventListener.addSupportedEventType(static_cast<std::uint32_t>(EventType::DataSelectionChanged));
    _eventListener.registerDataEventByType(ClusterType, std::bind(&SimianViewerPlugin::onDataEvent, this, std::placeholders::_1));

    auto topToolbarWidget = new QWidget();
    auto topToolbarLayout = new QHBoxLayout();
    topToolbarLayout->setMargin(0);
    topToolbarLayout->setSpacing(0);
    topToolbarLayout->addWidget(_simianOptionsAction->getSpeciesAction().createCollapsedWidget(&_widget));
    topToolbarLayout->addWidget(_simianOptionsAction->getDistanceNeighborhoodAction().createCollapsedWidget(&_widget));
    topToolbarLayout->addWidget(_simianOptionsAction->getColorMapAction().createCollapsedWidget(&_widget));
    topToolbarLayout->addWidget(_simianOptionsAction->getClusterAction().createCollapsedWidget(&_widget));
    topToolbarLayout->addStretch(0);
    topToolbarWidget->setAutoFillBackground(true);
    topToolbarWidget->setLayout(topToolbarLayout);
    auto layout = new QVBoxLayout();
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(topToolbarWidget);
    layout->addWidget(_simian_viewer, 1);
    _widget.setLayout(layout);


}

void SimianViewerPlugin::onDataEvent(hdps::DataEvent* dataEvent)
{
    if (dataEvent->getType() == hdps::EventType::DataSelectionChanged)
    {
        const auto selectionChangedEvent = static_cast<DataSelectionChangedEvent*>(dataEvent);
        const auto& changedDataSet = _core->requestDataset<Clusters>(selectionChangedEvent->getDataset()->getGuid());
        const auto& selectionSet = changedDataSet->getSelectionNames(); 
        qDebug() << selectionSet;
        _simian_viewer->setClusters(selectionSet);
    }
}

void SimianViewerPlugin::publishSelection(std::vector<std::string> selectedIDs)
{
    
    if (_simianOptionsAction->getCrossSpeciesFilterAction().getCurrentText() == "cross species clusters")
    {
        selectCrossSpeciesClusterPoints(selectedIDs);
    }
    else
    {
        selectIndividualSpeciesClusterPoints(selectedIDs);
    }



}

void SimianViewerPlugin::publishCluster(std::string clusterName)
{
    if (clusterName != "")
    {
        if(_simianOptionsAction->getCrossSpeciesFilterAction().getCurrentText() == "cross-species clusters")
        {
        if (_simianOptionsAction->getCrossSpecies1DatasetLinkerAction().getCurrentText() != "")
        {
            auto dataset1 = _simianOptionsAction->getCrossSpecies1DatasetLinkerAction().getCurrentDataset();
            const auto candidateDataset1 = _core->requestDataset<Clusters>(dataset1.getDatasetGuid());
            std::vector<std::uint32_t> selectedIndices1;

            for (const auto& cluster : candidateDataset1->getClusters())
            {
                if (cluster.getName() == QString::fromStdString(clusterName))
                {
                    for (const auto& index : cluster.getIndices())
                    {
                        selectedIndices1.push_back(index);
                    }
                }

            }

            candidateDataset1->getParent()->setSelectionIndices(selectedIndices1);


            _core->notifyDatasetSelectionChanged(candidateDataset1->getParent());

        }
        if (_simianOptionsAction->getCrossSpecies2DatasetLinkerAction().getCurrentText() != "")
        {
            auto dataset2 = _simianOptionsAction->getCrossSpecies2DatasetLinkerAction().getCurrentDataset();
            const auto candidateDataset2 = _core->requestDataset<Clusters>(dataset2.getDatasetGuid());
            std::vector<std::uint32_t> selectedIndices2;
            for (const auto& cluster : candidateDataset2->getClusters())
            {
                if (cluster.getName() == QString::fromStdString(clusterName))
                {
                    for (const auto& index : cluster.getIndices())
                    {
                        selectedIndices2.push_back(index);
                    }
                }

            }

            candidateDataset2->getParent()->setSelectionIndices(selectedIndices2);
            _core->notifyDatasetSelectionChanged(candidateDataset2->getParent());
        }
    }
        else
        {
            if (_simianOptionsAction->getInSpecies1DatasetLinkerAction().getCurrentText() != "")
            {
                auto dataset1 = _simianOptionsAction->getInSpecies1DatasetLinkerAction().getCurrentDataset();
                const auto candidateDataset1 = _core->requestDataset<Clusters>(dataset1.getDatasetGuid());
                std::vector<std::uint32_t> selectedIndices1;

                for (const auto& cluster : candidateDataset1->getClusters())
                {
                    if (cluster.getName() == QString::fromStdString(clusterName))
                    {
                        for (const auto& index : cluster.getIndices())
                        {
                            selectedIndices1.push_back(index);
                        }
                    }

                }

                candidateDataset1->getParent()->setSelectionIndices(selectedIndices1);


                _core->notifyDatasetSelectionChanged(candidateDataset1->getParent());

            }
            if (_simianOptionsAction->getInSpecies2DatasetLinkerAction().getCurrentText() != "")
            {
                auto dataset2 = _simianOptionsAction->getInSpecies2DatasetLinkerAction().getCurrentDataset();
                const auto candidateDataset2 = _core->requestDataset<Clusters>(dataset2.getDatasetGuid());
                std::vector<std::uint32_t> selectedIndices2;
                for (const auto& cluster : candidateDataset2->getClusters())
                {
                    if (cluster.getName() == QString::fromStdString(clusterName))
                    {
                        for (const auto& index : cluster.getIndices())
                        {
                            selectedIndices2.push_back(index);
                        }
                    }

                }

                candidateDataset2->getParent()->setSelectionIndices(selectedIndices2);
                _core->notifyDatasetSelectionChanged(candidateDataset2->getParent());
            }
        }
    }



}




// =============================================================================
// Factory
// =============================================================================

QIcon SimianViewerPluginFactory::getIcon() const
{
    return Application::getIconFont("FontAwesome").getIcon("braille");
}

ViewPlugin* SimianViewerPluginFactory::produce()
{
    return new SimianViewerPlugin(this);
}

hdps::DataTypes SimianViewerPluginFactory::supportedDataTypes() const
{
    DataTypes supportedTypes;
    return supportedTypes;
}


void SimianViewerPlugin::selectCrossSpeciesClusterPoints(std::vector<std::string> selectedIDs)
{
    if (selectedIDs[0] == selectedIDs[1])
    {


        if (_simianOptionsAction->getCrossSpecies1DatasetLinkerAction().getCurrentText() != "")
        {
            auto dataset1 = _simianOptionsAction->getCrossSpecies1DatasetLinkerAction().getCurrentDataset();
            const auto candidateDataset1 = _core->requestDataset<Clusters>(dataset1.getDatasetGuid());
            std::vector<std::uint32_t> selectedIndices1;

            for (const auto& cluster : candidateDataset1->getClusters())
            {
                if (cluster.getName() == QString::fromUtf8(selectedIDs.at(0).c_str()))
                {
                    for (const auto& index : cluster.getIndices())
                    {
                        selectedIndices1.push_back(index);
                    }
                }

            }

            candidateDataset1->getParent()->setSelectionIndices(selectedIndices1);


            _core->notifyDatasetSelectionChanged(candidateDataset1->getParent());

        }
        if (_simianOptionsAction->getCrossSpecies2DatasetLinkerAction().getCurrentText() != "")
        {
            auto dataset2 = _simianOptionsAction->getCrossSpecies2DatasetLinkerAction().getCurrentDataset();
            const auto candidateDataset2 = _core->requestDataset<Clusters>(dataset2.getDatasetGuid());
            std::vector<std::uint32_t> selectedIndices2;
            for (const auto& cluster : candidateDataset2->getClusters())
            {
                if (cluster.getName() == QString::fromUtf8(selectedIDs.at(0).c_str()))
                {
                    for (const auto& index : cluster.getIndices())
                    {
                        selectedIndices2.push_back(index);
                    }
                }

            }

            candidateDataset2->getParent()->setSelectionIndices(selectedIndices2);
            _core->notifyDatasetSelectionChanged(candidateDataset2->getParent());
        }

    }

    else {

        if (_simianOptionsAction->getCrossSpecies1DatasetLinkerAction().getCurrentText() != "")
        {
            auto dataset1 = _simianOptionsAction->getCrossSpecies1DatasetLinkerAction().getCurrentDataset();
            const auto candidateDataset1 = _core->requestDataset<Clusters>(dataset1.getDatasetGuid());
            std::vector<std::uint32_t> selectedIndices1;
            candidateDataset1->getParent()->setSelectionIndices(selectedIndices1);
            _core->notifyDatasetSelectionChanged(candidateDataset1->getParent());
        }
        if (_simianOptionsAction->getCrossSpecies2DatasetLinkerAction().getCurrentText() != "")
        {
            auto dataset2 = _simianOptionsAction->getCrossSpecies2DatasetLinkerAction().getCurrentDataset();
            const auto candidateDataset2 = _core->requestDataset<Clusters>(dataset2.getDatasetGuid());
            std::vector<std::uint32_t> selectedIndices2;
            candidateDataset2->getParent()->setSelectionIndices(selectedIndices2);
            _core->notifyDatasetSelectionChanged(candidateDataset2->getParent());
        }

    }
}

void SimianViewerPlugin::selectIndividualSpeciesClusterPoints(std::vector<std::string> selectedIDs)
{
    if (_simianOptionsAction->getInSpecies1DatasetLinkerAction().getCurrentText() != "")
    {
        auto dataset1 = _simianOptionsAction->getInSpecies1DatasetLinkerAction().getCurrentDataset();
        const auto candidateDataset1 = _core->requestDataset<Clusters>(dataset1.getDatasetGuid());
        std::vector<std::uint32_t> selectedIndices1;

        for (const auto& cluster : candidateDataset1->getClusters())
        {
            if (cluster.getName() == QString::fromUtf8(selectedIDs.at(0).c_str()))
            {
                for (const auto& index : cluster.getIndices())
                {
                    selectedIndices1.push_back(index);
                }
            }

        }

        candidateDataset1->getParent()->setSelectionIndices(selectedIndices1);

        _core->notifyDatasetSelectionChanged(candidateDataset1->getParent());

    }
    if (_simianOptionsAction->getInSpecies2DatasetLinkerAction().getCurrentText() != "")
    {
        auto dataset2 = _simianOptionsAction->getInSpecies2DatasetLinkerAction().getCurrentDataset();
        const auto candidateDataset2 = _core->requestDataset<Clusters>(dataset2.getDatasetGuid());
        std::vector<std::uint32_t> selectedIndices2;
        for (const auto& cluster : candidateDataset2->getClusters())
        {
            if (cluster.getName() == QString::fromUtf8(selectedIDs.at(1).c_str()))
            {
                for (const auto& index : cluster.getIndices())
                {
                    selectedIndices2.push_back(index);
                }
            }

        }

        candidateDataset2->getParent()->setSelectionIndices(selectedIndices2);
        _core->notifyDatasetSelectionChanged(candidateDataset2->getParent());
    }

}

