#include "SimianViewerPlugin.h"

#include "PointData/PointData.h"
#include "event/Event.h"
#include "ColorData/ColorData.h"
#include <QMessageBox>
#include <actions/PluginTriggerAction.h>
#include <QFileDialog>
#include <QtCore>
#include <QtDebug>
#include <QWebEngineView>
#include<ios>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <QDesktopServices>
#include <QMainWindow>
#include <QMenuBar>
#include <QUrl>
#include <QWindowList>
#include <QWindow>

Q_PLUGIN_METADATA(IID "nl.tudelft.SimianViewerPlugin")

using namespace mv;

// =============================================================================
// View
// =============================================================================

SimianViewerPlugin::SimianViewerPlugin(const PluginFactory* factory) :
    ViewPlugin(factory),
    _simian_viewer(),
    _simianOptionsAction(*this, _core)
{
    setSerializationName("SimianViewer");
    //_simian_viewer = new SimianViewerWidget();
}

SimianViewerPlugin::~SimianViewerPlugin()
{
}

void SimianViewerPlugin::init()
{
    connect(&_simian_viewer, &SimianViewerWidget::widgetInitialized, &_simianOptionsAction, &SimianOptionsAction::initLoader);

    _simian_viewer.setPage(":/simian_viewer/simian_viewer.html", "qrc:/simian_viewer/");
    _simian_viewer.setContentsMargins(0, 0, 0, 0);
    _simian_viewer.layout()->setContentsMargins(0, 0, 0, 0);

    connect(&_simian_viewer, &SimianViewerWidget::passClusterToQt, this, &SimianViewerPlugin::publishCluster);
    connect(&_simian_viewer, &SimianViewerWidget::removeSelectionFromScatterplot, this, &SimianViewerPlugin::removeSelectionFromScatterplot);
    //connect(_simian_viewer, &SimianViewerWidget::generatedScreenshotData, this, &SimianViewerPlugin::generatedScreenshotData);

    _eventListener.addSupportedEventType(static_cast<std::uint32_t>(EventType::DatasetDataSelectionChanged));
    _eventListener.registerDataEventByType(ClusterType, std::bind(&SimianViewerPlugin::onDataEvent, this, std::placeholders::_1));

    auto topToolbarLayout = new QHBoxLayout();

    topToolbarLayout->setContentsMargins(4, 4, 4, 4);
    topToolbarLayout->setSpacing(0);
    topToolbarLayout->addWidget(_simianOptionsAction.getOptionsHolder().createWidget(&getWidget()));
    //topToolbarLayout->addWidget(_simianOptionsAction.getLinkerSettingHolder().createWidget(&getWidget()));
    topToolbarLayout->addStretch(1);

    //auto species2ActionWidget = _simianOptionsAction.getSpecies2Holder().createWidget(&getWidget());
    //species2ActionWidget->setMaximumWidth(200);
    //topToolbarLayout->addWidget(species2ActionWidget);

    //auto distanceNeighborhoodActionwidget = _simianOptionsAction.getDistanceNeighborhoodHolder().createWidget(&getWidget());
    //distanceNeighborhoodActionwidget->setMaximumWidth(280);

    //topToolbarLayout->addWidget(distanceNeighborhoodActionwidget);

    //auto cellCountActionwidget = _simianOptionsAction.getCellCountHolder().createWidget(&getWidget());
    //cellCountActionwidget->setMaximumWidth(100);
    //topToolbarLayout->addWidget(cellCountActionwidget);

    //auto scatterplotColorwidget = _simianOptionsAction.getScatterplotColorHolder().createWidget(&getWidget());
    //scatterplotColorwidget->setMaximumWidth(255);
    //topToolbarLayout->addWidget(scatterplotColorwidget);

    //auto explorationActionwidget = _simianOptionsAction.getExplorationAction().createWidget(&_widget);
    //explorationActionwidget->setMaximumWidth(97);
    //topToolbarLayout->addWidget(explorationActionwidget);
    //topToolbarLayout->addWidget(_simianOptionsAction.getScreenshotAction().createWidget(&getWidget()));
    //topToolbarLayout->addWidget(_simianOptionsAction.getLinkerSettingHolder().createCollapsedWidget(&getWidget()));
    //topToolbarLayout->addWidget(_simianOptionsAction.getHelpAction().createWidget(&getWidget()));




    auto layout = new QVBoxLayout();

    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addLayout(topToolbarLayout);
    layout->addWidget(&_simian_viewer, 1);

    getWidget().setLayout(layout);

    //_simianOptionsAction.initLoader();



    //auto datasets = _core->requestAllDataSets(QVector<mv::DataType> {PointType});
    //auto filteredDatasets = datasets;
    //for (auto dataset : datasets)
    //{
    //    std::string str1 = dataset->getGuiName().toStdString();
    //    std::string str2 = "Numerical MetaData";
    //    if (strstr(str1.c_str(), str2.c_str()))
    //    {
    //        filteredDatasets.removeOne(dataset);
    //    }
    //    else {

    //    }
    //}

}

void SimianViewerPlugin::onDataEvent(mv::DatasetEvent* dataEvent)
{
    if (dataEvent->getType() == mv::EventType::DatasetDataSelectionChanged)
    {
        const auto selectionChangedEvent = static_cast<DatasetDataSelectionChangedEvent*>(dataEvent);
        const auto& changedDataSet = mv::data().getDataset<Clusters>(selectionChangedEvent->getDataset()->getId());
        const auto& selectionSet = changedDataSet->getSelectionNames();
        //qDebug() << selectionSet;
        _simian_viewer.setClusters(selectionSet);
    }
}

void SimianViewerPlugin::fromVariantMap(const QVariantMap& variantMap)
{
    ViewPlugin::fromVariantMap(variantMap);

    _simianOptionsAction.fromParentVariantMap(variantMap);
}

QVariantMap SimianViewerPlugin::toVariantMap() const
{
    QVariantMap variantMap = ViewPlugin::toVariantMap();

    _simianOptionsAction.insertIntoVariantMap(variantMap);

    return variantMap;
}

//void SimianViewerPlugin::publishSelection(std::vector<std::string> selectedIDs)
//{
//    
//   // if (_simianOptionsAction.getCrossSpeciesFilterAction().getCurrentText() == "cross species clusters")
//   // {
//    //    selectCrossSpeciesClusterPoints(selectedIDs);
//   // }
//    //else
//    //{
//        selectIndividualSpeciesClusterPoints(selectedIDs);
//    //}
//
//
//
//}


//void SimianViewerPlugin::generatedScreenshotData(std::string selectedIDs)
//{
//    QFileDialog saveFileDialog;
//    //QString xml = QString::fromStdString(selectedIDs);
//    saveFileDialog.setAcceptMode(QFileDialog::AcceptSave);
//    saveFileDialog.setDirectory(QDir::home().absolutePath());
//    //saveFileDialog.setDefaultSuffix("svg");
//    saveFileDialog.selectFile("SimianViewerScreenshot.pdf");
//    saveFileDialog.setNameFilter(tr("PDF Image Files (*.pdf)"));
//
//    QString fileName;
//    if (saveFileDialog.exec())
//    {
//        fileName = saveFileDialog.selectedFiles().first();
//
//        //QString typeInfo = " xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\"";
//
//        //int offset = xml.indexOf("<svg") + 4;
//        //xml.insert(offset, typeInfo);
//
//        //offset = xml.indexOf("</svg>");
//        //xml.insert(offset, _css);
//
//        /* Try and open a file for output */
//        //QFile outputFile(fileName);
//        //outputFile.open(QIODevice::ReadWrite | QIODevice::Truncate);
//
//        /* Check it opened OK */
//        //if (!outputFile.isOpen()) { return; }
//
//        /* Point a QTextStream object at the file */
//        //QTextStream outStream(&outputFile);
//
//        /* Write the line to the file */
//        //outStream << xml;
//        
//        QPageLayout pl;
//        QPageSize ps;
//        qDebug() << "height" << _simian_viewer.height();
//        qDebug() << "width" << _simian_viewer.width();
//        ps = QPageSize(QSizeF(_simian_viewer.width(), _simian_viewer.height()), QPageSize::Point, QString(), QPageSize::ExactMatch);
//        pl.setPageSize(ps);
//        pl.setOrientation(QPageLayout::Portrait);
//
//
//        _simian_viewer.getPage()->printToPdf(fileName, pl);//grab().save(fileName, "PNG");
//        /* Close the file */
//        //outputFile.close();
//    }
//
//
//
//}

void SimianViewerPlugin::publishCluster(std::string clusterName)
{
    if (clusterName != "")
    {
        _simianOptionsAction.getLinkerSettingHolder().getSelectedCrossspeciescluster().setString(QString::fromStdString(clusterName));
    }
}


void SimianViewerPlugin::removeSelectionFromScatterplot(std::string clusterName)
{
    if (clusterName == "")
    {
        _simianOptionsAction.getLinkerSettingHolder().getSelectedCrossspeciescluster().setString("");
    }
}

//const auto showHelpbox = []() -> void
//{
//    //qDebug() << "Simian viewer plugin help requested...";
//    QMessageBox msgBox;
//    msgBox.setTextFormat(Qt::RichText); // this does the magic trick and allows you to click the link
//    msgBox.setText("<div><article class=\"post - body\"><img src=\"https://www.cytosplore.org/assets/images/cytosplore.png\" class=\"post-featured\"><small>December 2022</small><br><h3 class=\"post-title\"><a href=\"https://www.biorxiv.org/content/10.1101/2022.09.19.508480v1\">Comparative transcriptomics reveals human-specific cortical features</a></h3><div class=\"post-meta\">Humans have unique cognitive abilities among primates, including language, but their molecular, cellular, and circuit substrates are poorly understood. We used comparative single nucleus transcriptomics in adult humans, chimpanzees, gorillas, rhesus macaques, and common marmosets from the middle temporal gyrus (MTG) to understand human-specific features of cellular and molecular organization. Human, chimpanzee, and gorilla MTG showed highly similar cell type composition and laminar organization, and a large shift in proportions of deep layer intratelencephalic-projecting neurons compared to macaque and marmoset. Species differences in gene expression generally mirrored evolutionary distance and were seen in all cell types, although chimpanzees were more similar to gorillas than humans, consistent with faster divergence along the human lineage. Microglia, astrocytes, and oligodendrocytes showed accelerated gene expression changes compared to neurons or oligodendrocyte precursor cells, indicating either relaxed evolutionary constraints or positive selection in these cell types. Only a few hundred genes showed human-specific patterning in all or specific cell types, and were significantly enriched near human accelerated regions (HARs) and conserved deletions (hCONDELS) and in cell adhesion and intercellular signaling pathways. These results suggest that relatively few cellular and molecular changes uniquely define adult human cortical structure, particularly by affecting circuit connectivity and glial cell function.</div></article></div>");
//    //msgBox.setIcon(yourIcon);
//    msgBox.exec();
//};



SimianViewerPluginFactory::SimianViewerPluginFactory() :
    ViewPluginFactory()
{
    connect(&getTriggerHelpAction(), &TriggerAction::triggered, this, [this]() -> void {
        QDesktopServices::openUrl(QUrl("https://www.dropbox.com/s/e9200b3zphzsw3b/Cytosplore_Simian_Viewer_Technical_Document_1.pdf?dl=0"));
        });
}

// =============================================================================
// Factory
// =============================================================================

QIcon SimianViewerPluginFactory::getIcon(const QColor& color /*= Qt::black*/) const
{
    return Application::getIconFont("FontAwesome").getIcon("chart-area", color);
}


QMenu *findHelpMenu()
{
    // find the mainwindow
    foreach(QWidget * widget, qApp->topLevelWidgets())
        if (QMainWindow* mainWindow = qobject_cast<QMainWindow*>(widget))
        {
            // now get the menu bar and find the Help menu
            QMenuBar* theMenuBar = mainWindow->menuBar();
            auto menuBarActions = theMenuBar->actions();
            for (auto it = menuBarActions.begin(); it != menuBarActions.end(); ++it)
            {
               
                if ((*it)->text() == "Help")
                {
                    QMenu *helpMenu =  QMenu::menuInAction(*it);
                    return helpMenu;
                }
                
            }

        }
    return nullptr;
}
ViewPlugin* SimianViewerPluginFactory::produce()
{
    
    static bool first = true;

    
    if(first)
    {

        QMenu *helpMenu = findHelpMenu();
        if(helpMenu)
        {
           
            auto *documentation = new TriggerAction(this, " Documentation");
            QIcon icon = Application::getIconFont("FontAwesome").getIcon("file-pdf", Qt::black);
            documentation->setIcon(icon);
            connect(documentation, &QAction::triggered, this, [this](bool)
            {
            	auto urlString = QString("file:///") + QApplication::applicationDirPath() + "/SimianViewerDocumentation.pdf";
	            QDesktopServices::openUrl(QUrl(urlString, QUrl::TolerantMode));
            });
            helpMenu->addAction(documentation);
            first = false;
        }



    }
    
    
    return new SimianViewerPlugin(this);
}

mv::DataTypes SimianViewerPluginFactory::supportedDataTypes() const
{
    DataTypes supportedTypes;
    return supportedTypes;
}


mv::gui::PluginTriggerActions SimianViewerPluginFactory::getPluginTriggerActions(const mv::Datasets& datasets) const
{
    PluginTriggerActions pluginTriggerActions;

    const auto getInstance = [this]() -> SimianViewerPlugin* {
        return dynamic_cast<SimianViewerPlugin*>(plugins().requestViewPlugin(getKind()));
    };

    const auto numberOfDatasets = datasets.count();

    if (PluginFactory::areAllDatasetsOfTheSameType(datasets, PointType)) {
        if (numberOfDatasets >= 1) {
            if (datasets.first()->getDataType() == PointType) {
                auto pluginTriggerAction = new PluginTriggerAction(const_cast<SimianViewerPluginFactory*>(this), this, "Simian viewer", "Load dataset in Simian viewer", getIcon(), [this, getInstance, datasets](PluginTriggerAction& pluginTriggerAction) -> void {
                    for (auto dataset : datasets)
                        getInstance()->loadData(Datasets({ dataset }));
                    });

                pluginTriggerActions << pluginTriggerAction;
            }
        }
    }

    return pluginTriggerActions;
}

//bool SimianViewerPluginFactory::hasHelp()
//{
//    return true;
//}

void SimianViewerPlugin::selectCrossSpeciesClusterPoints(std::vector<std::string> selectedIDs)
{
    if (selectedIDs[0] == selectedIDs[1])
    {


        if (_simianOptionsAction.getLinkerSettingHolder().getCrossSpecies1DatasetLinkerAction().getCurrentText() != "")
        {
            auto dataset1 = _simianOptionsAction.getLinkerSettingHolder().getCrossSpecies1DatasetLinkerAction().getCurrentDataset();
            const auto candidateDataset1 = mv::data().getDataset<Clusters>(dataset1.getDatasetId());
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


            events().notifyDatasetDataSelectionChanged(candidateDataset1->getParent());

        }
        if (_simianOptionsAction.getLinkerSettingHolder().getCrossSpecies2DatasetLinkerAction().getCurrentText() != "")
        {
            auto dataset2 = _simianOptionsAction.getLinkerSettingHolder().getCrossSpecies2DatasetLinkerAction().getCurrentDataset();
            const auto candidateDataset2 = mv::data().getDataset<Clusters>(dataset2.getDatasetId());
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
            events().notifyDatasetDataSelectionChanged(candidateDataset2->getParent());
        }

    }

    else {

        if (_simianOptionsAction.getLinkerSettingHolder().getCrossSpecies1DatasetLinkerAction().getCurrentText() != "")
        {
            auto dataset1 = _simianOptionsAction.getLinkerSettingHolder().getCrossSpecies1DatasetLinkerAction().getCurrentDataset();
            const auto candidateDataset1 = mv::data().getDataset<Clusters>(dataset1.getDatasetId());
            std::vector<std::uint32_t> selectedIndices1;
            candidateDataset1->getParent()->setSelectionIndices(selectedIndices1);
            events().notifyDatasetDataSelectionChanged(candidateDataset1->getParent());
        }
        if (_simianOptionsAction.getLinkerSettingHolder().getCrossSpecies2DatasetLinkerAction().getCurrentText() != "")
        {
            auto dataset2 = _simianOptionsAction.getLinkerSettingHolder().getCrossSpecies2DatasetLinkerAction().getCurrentDataset();
            const auto candidateDataset2 = mv::data().getDataset<Clusters>(dataset2.getDatasetId());
            std::vector<std::uint32_t> selectedIndices2;
            candidateDataset2->getParent()->setSelectionIndices(selectedIndices2);
            events().notifyDatasetDataSelectionChanged(candidateDataset2->getParent());
        }

    }
}

//void SimianViewerPlugin::selectIndividualSpeciesClusterPoints(std::vector<std::string> selectedIDs)
//{
//    if (_simianOptionsAction.getScatterplotColorControlAction().getCurrentText() == "cross-species cluster")
//    {
//        if (selectedIDs[2]== selectedIDs[3])
//        {
//            _simianOptionsAction.getSelectedCrossSpeciesNameList().setString(QString::fromStdString(selectedIDs[2]));
//            _simianOptionsAction.getSelectedCrossspeciescluster().setString(QString::fromStdString(selectedIDs[2]));
//        }
//    }
//
//
//    
//   // _simianOptionsAction.getInSpecies1HeatMapCellAction().setCurrentText(QString::fromStdString(selectedIDs[0]));
//    //_simianOptionsAction.getInSpecies2HeatMapCellAction().setCurrentText(QString::fromStdString(selectedIDs[1]));
//    _simianOptionsAction.getCrossSpecies1HeatMapCellAction().setCurrentText(QString::fromStdString(selectedIDs[2]));
//
//    _simianOptionsAction.getCrossSpecies2HeatMapCellAction().setCurrentText(QString::fromStdString(selectedIDs[3]));
//    if (_simianOptionsAction.getInSpecies1DatasetLinkerAction().getCurrentText() != "")
//    {
//        auto dataset1 = _simianOptionsAction.getInSpecies1DatasetLinkerAction().getCurrentDataset();
//        const auto candidateDataset1 = _core->requestDataset<Clusters>(dataset1.getDatasetGuid());
//        std::vector<std::uint32_t> selectedIndices1;
//
//        for (const auto& cluster : candidateDataset1->getClusters())
//        {
//            if (cluster.getName() == QString::fromUtf8(selectedIDs.at(0).c_str()))
//            {
//                for (const auto& index : cluster.getIndices())
//                {
//                    selectedIndices1.push_back(index);
//                }
//            }
//
//        }
//
//        candidateDataset1->getParent()->setSelectionIndices(selectedIndices1);
//
//        events().notifyDatasetSelectionChanged(candidateDataset1->getParent());
//
//    }
//    if (_simianOptionsAction.getInSpecies2DatasetLinkerAction().getCurrentText() != "")
//    {
//        auto dataset2 = _simianOptionsAction.getInSpecies2DatasetLinkerAction().getCurrentDataset();
//        const auto candidateDataset2 = _core->requestDataset<Clusters>(dataset2.getDatasetGuid());
//        std::vector<std::uint32_t> selectedIndices2;
//        for (const auto& cluster : candidateDataset2->getClusters())
//        {
//            if (cluster.getName() == QString::fromUtf8(selectedIDs.at(1).c_str()))
//            {
//                for (const auto& index : cluster.getIndices())
//                {
//                    selectedIndices2.push_back(index);
//                }
//            }
//
//        }
//
//        candidateDataset2->getParent()->setSelectionIndices(selectedIndices2);
//        events().notifyDatasetSelectionChanged(candidateDataset2->getParent());
//    }
//
//
//
//    _simianOptionsAction.getmodifyDifferentialExpressionAutoUpdateAction().trigger();
//}
