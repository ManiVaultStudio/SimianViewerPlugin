#pragma once

#include <actions/WidgetAction.h>
#include <actions/IntegralAction.h>
#include <actions/OptionAction.h>
#include <actions/OptionsAction.h>
#include <actions/ToggleAction.h>
#include "actions/DatasetPickerAction.h"
#include "PointData.h"
#include "ClusterData.h"
#include "event/EventListener.h"
#include "actions/Actions.h"
#include "Plugin.h"
#include "DataHierarchyItem.h"
#include "Set.h"
#include <AnalysisPlugin.h>
#include <memory>
#include "../SimianViewerWidget.h"
#include "../Data/globalMetadata.h"
#include <algorithm>    
#include <QDebug>
#include <QLabel>
#include <QComboBox>
#include <QGroupBox>
#include <QPushButton>
#include <QGridLayout>
#include <QFormLayout>
#include <QString>
#include <string>
#include "../simianViewerPlugin.h"
#include <event/Event.h>

#include <QDebug>
#include <QLabel>

using namespace hdps::gui;
class QMenu;
class SimianViewerPlugin;
class SimianViewerWidget;
class FetchMetaData;
namespace hdps
{
    class CoreInterface;
}
class SimianOptionsAction : public WidgetAction, public hdps::EventListener
{
public:
    class SpeciesAction : public WidgetAction
    {
    protected:
        class Widget : public hdps::gui::WidgetActionWidget {
        public:
            Widget(QWidget* parent, SpeciesAction* speciesAction);

            friend class SpeciesAction;
        };

        QWidget* getWidget(QWidget* parent, const std::int32_t& widgetFlags) override {
            return new SpeciesAction::Widget(parent, this);
        };

    public:
        SpeciesAction(SimianOptionsAction& simianOptionsAction);

    protected:
        SimianOptionsAction& _simianOptionsAction;

        friend class SimianOptionsAction;
    };
    class ColorMapOptionAction : public WidgetAction
    {
    protected:
        class Widget : public hdps::gui::WidgetActionWidget {
        public:
            Widget(QWidget* parent, ColorMapOptionAction* speciesAction);

            friend class ColorMapOptionAction;
        };

        QWidget* getWidget(QWidget* parent, const std::int32_t& widgetFlags) override {
            return new ColorMapOptionAction::Widget(parent, this);
        };

    public:
        ColorMapOptionAction(SimianOptionsAction& simianOptionsAction);

    protected:
        SimianOptionsAction& _simianOptionsAction;

        friend class SimianOptionsAction;
    };
    class ClusterAction : public WidgetAction
    {
    protected:
        class Widget : public hdps::gui::WidgetActionWidget {
        public:
            Widget(QWidget* parent, ClusterAction* clusterAction);

            friend class ClusterAction;
        };

        QWidget* getWidget(QWidget* parent, const std::int32_t& widgetFlags) override {
            return new ClusterAction::Widget(parent, this);
        };

    public:
        ClusterAction(SimianOptionsAction& simianOptionsAction);

    protected:
        SimianOptionsAction& _simianOptionsAction;

        friend class SimianOptionsAction;
    };

    class DistanceNeighborhoodAction : public WidgetAction
    {
    protected:
        class Widget : public hdps::gui::WidgetActionWidget {
        public:
            Widget(QWidget* parent, DistanceNeighborhoodAction* distanceNeighborhoodAction);

            friend class DistanceNeighborhoodAction;
        };

        QWidget* getWidget(QWidget* parent, const std::int32_t& widgetFlags) override {
            return new DistanceNeighborhoodAction::Widget(parent, this);
        };

    public:
        DistanceNeighborhoodAction(SimianOptionsAction& simianOptionsAction);

    protected:
        SimianOptionsAction& _simianOptionsAction;

        friend class SimianOptionsAction;
    };

public:
    void onDataEvent(hdps::DataEvent* dataEvent);
protected:

    class Widget : public hdps::gui::WidgetActionWidget {
    public:
        Widget(QWidget* parent, SimianOptionsAction* simianOptionsAction);
    };

    QWidget* getWidget(QWidget* parent, const std::int32_t& widgetFlags) override {
        return new SimianOptionsAction::Widget(parent, this);
    };

public:
    SimianOptionsAction(SimianViewerPlugin& simianViewerPlugin, hdps::CoreInterface* core);

private:
    void updateData(std::string Species1, std::string Species2, std::string neighborhood, int distance, std::string CrossSpeciesFilter);
    void filterMultiSelect();
protected:
    void updateDatasetPickerAction();
    void updateMultiSelectionDropdown(std::vector<std::vector<std::string>>& filteredVisData);
public: // Action getters

    OptionAction& getSpecies1Action() { return _species1Action; }
    OptionAction& getSpecies2Action() { return _species2Action; }
    OptionAction& getNeighborhoodAction() { return _neighborhoodAction; }
    IntegralAction& getDistanceAction() { return _distanceAction; };
    DatasetPickerAction& getSpecies1DatasetLinkerAction() { return _species1DatasetLinkerAction; };
    DatasetPickerAction& getSpecies2DatasetLinkerAction() { return _species2DatasetLinkerAction; };
    OptionAction& getCrossSpeciesFilterAction() { return _crossSpeciesFilterAction; }
    SpeciesAction& getSpeciesAction() { return _speciesAction; }
    ClusterAction& getClusterAction() { return _clusterAction; }
    DistanceNeighborhoodAction& getDistanceNeighborhoodAction() { return _distanceNeighborhoodAction; }
    ColorMapAction& getColorMapAction() { return _colorMapAction; }

protected:
    SimianViewerPlugin&          _simianViewerPlugin;
    OptionAction                 _species1Action;
    OptionAction                 _species2Action;
    OptionAction                 _neighborhoodAction;
    IntegralAction               _distanceAction;
    DatasetPickerAction           _species1DatasetLinkerAction;
    DatasetPickerAction          _species2DatasetLinkerAction;
    OptionAction                 _crossSpeciesFilterAction;
    hdps::CoreInterface*         _core;
    FetchMetaData*                _metaData;
    std::vector<std::vector<std::string>>                _simianData;
    OptionsAction                 _multiSelectClusterFilterAction;

    bool                        _isLoading;
    SpeciesAction               _speciesAction;
    ClusterAction               _clusterAction;
    DistanceNeighborhoodAction               _distanceNeighborhoodAction;
    bool _isStarted;
    ColorMapAction          _colorMapAction;
    friend class ChannelAction;
};