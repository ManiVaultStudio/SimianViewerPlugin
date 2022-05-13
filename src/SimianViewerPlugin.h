#pragma once

#include <ViewPlugin.h>
#include "Dataset.h"
#include "Common/SimianOptionsAction.h"
#include "SimianViewerWidget.h"
#include "widgets/DropWidget.h"
#include "Data/globalMetadata.h"
#include <QBoxLayout>
#include <QLabel>
#include <QStackedWidget>
#include <QList>

using namespace hdps::plugin;
using namespace hdps::util;

class Points;
class SimianViewerWidget;
class SimianOptionsAction;

// =============================================================================
// View
// =============================================================================

/**
 * SimianViewer Plugin
 */
class SimianViewerPlugin : public ViewPlugin
{
    Q_OBJECT
    
public:
    SimianViewerPlugin(const PluginFactory* factory);
    ~SimianViewerPlugin(void) override;

    void init() override;

    void onDataEvent(hdps::DataEvent* dataEvent);

    hdps::CoreInterface* getCore() { return _core; }

    SimianViewerWidget* getWidget() { return _simian_viewer; }
    SimianOptionsAction& getSimianOptionsAction() { return *_simianOptionsAction; }
    
protected slots:


private:

    void publishSelection(std::vector<std::string> selectedIDs);
    void publishCluster(std::string clusterName);
    void selectCrossSpeciesClusterPoints(std::vector<std::string> selectedIDs);
    void selectIndividualSpeciesClusterPoints(std::vector<std::string> selectedIDs);

    SimianOptionsAction*        _simianOptionsAction;
    /** SimianViewer widget displaying cluster data */
    SimianViewerWidget*             _simian_viewer;
    hdps::EventListener     _eventListener;
};

// =============================================================================
// Factory
// =============================================================================

class SimianViewerPluginFactory : public ViewPluginFactory
{
    Q_INTERFACES(hdps::plugin::ViewPluginFactory hdps::plugin::PluginFactory)
    Q_OBJECT
    Q_PLUGIN_METADATA(IID   "nl.tudelft.SimianViewerPlugin"
                      FILE  "SimianViewerPlugin.json")
    
public:
    SimianViewerPluginFactory(void) {}
    ~SimianViewerPluginFactory(void) override {}

    /** Returns the plugin icon */
    QIcon getIcon() const override;
    
    ViewPlugin* produce() override;

    hdps::DataTypes supportedDataTypes() const override;
};
