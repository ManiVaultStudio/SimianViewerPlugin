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
//class SimianViewerWidget;

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

    SimianViewerWidget* getSimianViewerWidget() { return _simian_viewer; }
    SimianOptionsAction& getSimianOptionsAction() { return _simianOptionsAction; }
    
public: // Serialization

    /**
     * Load widget action from variant map
     * @param Variant map representation of the widget action
     */
    void fromVariantMap(const QVariantMap& variantMap) override;

    /**
     * Save widget action to variant map
     * @return Variant map representation of the widget action
     */
    QVariantMap toVariantMap() const override;

protected slots:


private:

    //void publishSelection(std::vector<std::string> selectedIDs);
    void publishCluster(std::string clusterName);
    void removeSelectionFromScatterplot(std::string clusterName);
    //void generatedScreenshotData(std::string clusterName);
    void selectCrossSpeciesClusterPoints(std::vector<std::string> selectedIDs);
    //void selectIndividualSpeciesClusterPoints(std::vector<std::string> selectedIDs);

    SimianOptionsAction        _simianOptionsAction;
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
    SimianViewerPluginFactory(void);
    ~SimianViewerPluginFactory(void) override {}

    /**
     * Get plugin icon
     * @param color Icon color for flat (font) icons
     * @return Icon
     */
    QIcon getIcon(const QColor& color = Qt::black) const override;
    
    ViewPlugin* produce() override;

    hdps::DataTypes supportedDataTypes() const override;

    /**
     * Get plugin trigger actions given \p datasets
     * @param datasets Vector of input datasets
     * @return Vector of plugin trigger actions
     */
    PluginTriggerActions getPluginTriggerActions(const hdps::Datasets& datasets) const override;

//public: // Help

    /**
     * Get whether the plugin has help information or not
     * @return Boolean determining whether the plugin has help information or not
     */
    //bool hasHelp() override;
};
