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
   /*registerDataEventByType(ClusterType, std::bind(&SimianViewerPlugin::onDataEvent, this, std::placeholders::_1));*/
}

SimianViewerPlugin::~SimianViewerPlugin()
{
}

void SimianViewerPlugin::init()
{
    _simian_viewer->setPage(":/simian_viewer/simian_viewer.html", "qrc:/simian_viewer/");

    _simianOptionsAction = new SimianOptionsAction(*this, _core);
    connect(_simian_viewer, &SimianViewerWidget::passSelectionToQt, this, &SimianViewerPlugin::publishSelection);
    registerDataEventByType(ClusterType, std::bind(&SimianViewerPlugin::onDataEvent, this, std::placeholders::_1));
    //QFrame* sideBar = new QFrame;
    //QStackedWidget* contentStack = new QStackedWidget;
    //QFrame* contentPage = new QFrame;
    //QWidget* centralWidget = new QWidget;

    //QVBoxLayout* sideBarLayout = new QVBoxLayout;
    //QGridLayout* pageGridLayout = new QGridLayout;
    //QGridLayout* centralLayout = new QGridLayout;


    ///* Setup the sidebar: */
    //sideBarLayout->addWidget(_simianOptionsAction->getSpeciesAction().createCollapsedWidget(&_widget));
    //sideBarLayout->addWidget(_simianOptionsAction->getDistanceNeighborhoodAction().createCollapsedWidget(&_widget));
    //sideBarLayout->addWidget(_simianOptionsAction->getClusterAction().createCollapsedWidget(&_widget));
    //sideBarLayout->addStretch();

    //sideBar->setAutoFillBackground(true);
    //sideBar->setWindowTitle("Simian Options");
    //sideBar->setLayout(sideBarLayout);
    //sideBar->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    ///* Setup the content stacked widget */
    //pageGridLayout->addWidget(_simian_viewer, 0, 0, 3, 1);
    //contentPage->setLayout(pageGridLayout);
    //contentStack->addWidget(contentPage);
    //contentStack->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    ///* Finally we setup the main elements into the central layout... */

    //centralLayout->addWidget(sideBar, 0, 0, 1, 1);
    //centralLayout->addWidget(contentStack, 0, 1, 1, 1);
    ////centralWidget->setLayout(centralLayout);
    //
    ////setCentralWidget(centralWidget);

    //_widget.setLayout(centralLayout);

    //_widget.setStyleSheet("QWidget {"
    //    //"border: 0.5px solid grey;"
    //    "color: black"
    //    "}");

    auto topToolbarWidget = new QWidget();
    auto topToolbarLayout = new QHBoxLayout();
    topToolbarLayout->addWidget(_simianOptionsAction->getSpeciesAction().createCollapsedWidget(&_widget));
    topToolbarLayout->addStretch(1);
    topToolbarLayout->addWidget(_simianOptionsAction->getDistanceNeighborhoodAction().createCollapsedWidget(&_widget));
    topToolbarLayout->addStretch(1);
    topToolbarLayout->addWidget(_simianOptionsAction->getClusterAction().createCollapsedWidget(&_widget));
    topToolbarLayout->addStretch(1);
    topToolbarWidget->setAutoFillBackground(true);
    topToolbarWidget->setLayout(topToolbarLayout);
    auto layout = new QVBoxLayout();
    layout->addWidget(topToolbarWidget);
    layout->addWidget(_simian_viewer, 100);
    _widget.setLayout(layout);


}

void SimianViewerPlugin::onDataEvent(hdps::DataEvent* dataEvent)
{
    //qDebug() << "dataset has changed" << (int) dataEvent->getType() << dataEvent->getDataset()->getGuiName();
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


        if (_simianOptionsAction->getSpecies1DatasetLinkerAction().getCurrentText() != "")
        {
            auto dataset1 = _simianOptionsAction->getSpecies1DatasetLinkerAction().getCurrentDataset();
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
        if (_simianOptionsAction->getSpecies2DatasetLinkerAction().getCurrentText() != "")
        {
            auto dataset2 = _simianOptionsAction->getSpecies2DatasetLinkerAction().getCurrentDataset();
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

        if (_simianOptionsAction->getSpecies1DatasetLinkerAction().getCurrentText() != "")
        {
            auto dataset1 = _simianOptionsAction->getSpecies1DatasetLinkerAction().getCurrentDataset();
            const auto candidateDataset1 = _core->requestDataset<Clusters>(dataset1.getDatasetGuid());
            std::vector<std::uint32_t> selectedIndices1;
            candidateDataset1->getParent()->setSelectionIndices(selectedIndices1);
            _core->notifyDatasetSelectionChanged(candidateDataset1->getParent());
        }
        if (_simianOptionsAction->getSpecies2DatasetLinkerAction().getCurrentText() != "")
        {
            auto dataset2 = _simianOptionsAction->getSpecies2DatasetLinkerAction().getCurrentDataset();
            const auto candidateDataset2 = _core->requestDataset<Clusters>(dataset2.getDatasetGuid());
            std::vector<std::uint32_t> selectedIndices2;
            candidateDataset2->getParent()->setSelectionIndices(selectedIndices2);
            _core->notifyDatasetSelectionChanged(candidateDataset2->getParent());
        }

    }
}

void SimianViewerPlugin::selectIndividualSpeciesClusterPoints(std::vector<std::string> selectedIDs)
{
    if (_simianOptionsAction->getSpecies1DatasetLinkerAction().getCurrentText() != "")
    {
        auto dataset1 = _simianOptionsAction->getSpecies1DatasetLinkerAction().getCurrentDataset();
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
    if (_simianOptionsAction->getSpecies2DatasetLinkerAction().getCurrentText() != "")
    {
        auto dataset2 = _simianOptionsAction->getSpecies2DatasetLinkerAction().getCurrentDataset();
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