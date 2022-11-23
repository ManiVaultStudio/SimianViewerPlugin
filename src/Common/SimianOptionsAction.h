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
class SimianOptionsAction : public WidgetAction
{
public:
    class Species1Action : public WidgetAction
    {
    protected:
        class Widget : public hdps::gui::WidgetActionWidget {
        public:
            Widget(QWidget* parent, Species1Action* species1Action);

            friend class Species1Action;
        };

        QWidget* getWidget(QWidget* parent, const std::int32_t& widgetFlags) override {
            return new Species1Action::Widget(parent, this);
        };

    public:
        Species1Action(SimianOptionsAction& simianOptionsAction);

    protected:
        SimianOptionsAction& _simianOptionsAction;

        friend class SimianOptionsAction;
    };
    class Species2Action : public WidgetAction
    {
    protected:
        class Widget : public hdps::gui::WidgetActionWidget {
        public:
            Widget(QWidget* parent, Species2Action* species2Action);

            friend class Species2Action;
        };

        QWidget* getWidget(QWidget* parent, const std::int32_t& widgetFlags) override {
            return new Species2Action::Widget(parent, this);
        };

    public:
        Species2Action(SimianOptionsAction& simianOptionsAction);

    protected:
        SimianOptionsAction& _simianOptionsAction;

        friend class SimianOptionsAction;
    };
    class VisSettingAction : public WidgetAction
    {
    protected:
        class Widget : public hdps::gui::WidgetActionWidget {
        public:
            Widget(QWidget* parent, VisSettingAction* visSettingAction);

            friend class VisSettingAction;
        };

        QWidget* getWidget(QWidget* parent, const std::int32_t& widgetFlags) override {
            return new VisSettingAction::Widget(parent, this);
        };

    public:
        VisSettingAction(SimianOptionsAction& simianOptionsAction);

    protected:
        SimianOptionsAction& _simianOptionsAction;

        friend class SimianOptionsAction;
    };
    class LinkerSettingAction : public WidgetAction
    {
    protected:
        class Widget : public hdps::gui::WidgetActionWidget {
        public:
            Widget(QWidget* parent, LinkerSettingAction* linkerSettingAction);

            friend class LinkerSettingAction;
        };

        QWidget* getWidget(QWidget* parent, const std::int32_t& widgetFlags) override {
            return new LinkerSettingAction::Widget(parent, this);
        };

    public:
        LinkerSettingAction(SimianOptionsAction& simianOptionsAction);

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
    class CellCountAction : public WidgetAction
    {
    protected:
        class Widget : public hdps::gui::WidgetActionWidget {
        public:
            Widget(QWidget* parent, CellCountAction* cellCountAction);

            friend class CellCountAction;
        };

        QWidget* getWidget(QWidget* parent, const std::int32_t& widgetFlags) override {
            return new CellCountAction::Widget(parent, this);
        };

    public:
        CellCountAction(SimianOptionsAction& simianOptionsAction);

    protected:
        SimianOptionsAction& _simianOptionsAction;

        friend class SimianOptionsAction;
    };
    //class ExplorationAction : public WidgetAction
    //{
    //protected:
    //    class Widget : public hdps::gui::WidgetActionWidget {
    //    public:
    //        Widget(QWidget* parent, ExplorationAction* explorationAction);

    //        friend class ExplorationAction;
    //    };

    //    QWidget* getWidget(QWidget* parent, const std::int32_t& widgetFlags) override {
    //        return new ExplorationAction::Widget(parent, this);
    //    };

    //public:
    //    ExplorationAction(SimianOptionsAction& simianOptionsAction);

    //protected:
    //    SimianOptionsAction& _simianOptionsAction;

    //    friend class SimianOptionsAction;
    //};
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
    //void filterMultiSelect();
    bool QStringlistContainsQString(const QStringList& list, const QString& str);
    QString selectFromQStringList(const QStringList& fileList, const QString& speciesType, const QString& fileType, const QString& neighborhoodType);
protected:
    void updateDatasetPickerAction();
    void sendClusterCountInfoToJS();
    //void updateMultiSelectionDropdown(std::vector<std::vector<std::string>>& filteredVisData);
public: // Action getters

    OptionAction& getSpecies1SelectAction() { return _species1SelectAction; }
    OptionAction& getSpecies2SelectAction() { return _species2SelectAction; }
    OptionAction& getScatterplotColorControlAction() { return _scatterplotColorControlAction; }
    OptionAction& getNeighborhoodAction() { return _neighborhoodAction; }
    IntegralAction& getDistanceAction() { return _distanceAction; };
    ToggleAction& getHistBarAction() { return _histBarAction; };
    ToggleAction& getRemoveLinkingOptionMenuFromUIAction() { return _removeLinkingOptionMenuFromUIAction; };
    ToggleAction& getFullHeatmapAction() { return _fullHeatMapAction; };
    //ToggleAction& getExplorationModeAction() { return _explorationModeAction; };
    DatasetPickerAction& getCrossSpecies1DatasetLinkerAction() { return _crossSpecies1DatasetLinkerAction; };
    DatasetPickerAction& getCrossSpecies2DatasetLinkerAction() { return _crossSpecies2DatasetLinkerAction; };

    DatasetPickerAction& getSpecies1ScatterplotColorLinkerAction() { return _species1ScatterplotColorLinkerAction; };
    DatasetPickerAction& getSpecies2ScatterplotColorLinkerAction() { return _species2ScatterplotColorLinkerAction; };

    DatasetPickerAction& getSpeciesEmbedding1LinkerAction() { return _speciesEmbedding1LinkerAction; };
    DatasetPickerAction& getSpeciesEmbedding2LinkerAction() { return _speciesEmbedding2LinkerAction; };

    DatasetPickerAction& getInSpecies1DatasetLinkerAction() { return _inSpecies1DatasetLinkerAction; };
    DatasetPickerAction& getInSpecies2DatasetLinkerAction() { return _inSpecies2DatasetLinkerAction; };
    OptionAction& getCrossSpeciesFilterAction() { return _crossSpeciesFilterAction; }
    OptionAction& getInSpecies1HeatMapCellAction() { return _inSpecies1HeatMapCellAction; }
    OptionAction& getInSpecies2HeatMapCellAction() { return _inSpecies2HeatMapCellAction; }
    OptionAction& getCrossSpecies1HeatMapCellAction() { return _crossSpecies1HeatMapCellAction; }
    OptionAction& getCrossSpecies2HeatMapCellAction() { return _crossSpecies2HeatMapCellAction; }
    Species1Action& getSpecies1Action() { return _species1Action; }
    Species2Action& getSpecies2Action() { return _species2Action; }
    VisSettingAction& getVisSettingAction() { return _visSettingAction; }
    LinkerSettingAction& getLinkerSettingAction() { return _linkerSettingAction; }
    DistanceNeighborhoodAction& getDistanceNeighborhoodAction() { return _distanceNeighborhoodAction; }
    ColorMapAction& getColorMapAction() { return _colorMapAction; }
    ColorAction& getBackgroundColoringAction() { return _backgroundColoringAction; }
    CellCountAction& getCellCountAction() { return _cellCountAction; }
    TriggerAction& getHelpAction() { return _helpAction; }
    TriggerAction& getScreenshotAction() { return _screenshotAction; }
    OptionAction& getBarLinkerSpecies1() { return _barLinkerAction1; }
    OptionAction& getBarLinkerSpecies2() { return _barLinkerAction2; }
    OptionAction& getScatterplotColorControl() { return _scatterplotColorControlAction; }
    //ExplorationAction& getExplorationAction() { return _explorationAction; }
protected:
    SimianViewerPlugin&          _simianViewerPlugin;
    OptionAction                 _species1SelectAction;
    OptionAction                 _species2SelectAction;
    OptionAction                 _scatterplotColorControlAction;
    OptionAction                 _neighborhoodAction;
    IntegralAction               _distanceAction;
    DatasetPickerAction           _crossSpecies1DatasetLinkerAction;
    DatasetPickerAction          _crossSpecies2DatasetLinkerAction;

    DatasetPickerAction           _species1ScatterplotColorLinkerAction;
    DatasetPickerAction          _species2ScatterplotColorLinkerAction;

    DatasetPickerAction           _speciesEmbedding1LinkerAction;
    DatasetPickerAction          _speciesEmbedding2LinkerAction;

    DatasetPickerAction           _inSpecies1DatasetLinkerAction;
    DatasetPickerAction          _inSpecies2DatasetLinkerAction;
    OptionAction                 _crossSpeciesFilterAction;
    hdps::CoreInterface*         _core;
    FetchMetaData*                _metaData;
    std::vector<std::vector<std::string>>                _simianData;
    //OptionsAction                 _multiSelectClusterFilterAction;
    ToggleAction _histBarAction;
    ToggleAction _fullHeatMapAction;
    //ToggleAction _explorationModeAction;
    OptionAction                 _inSpecies1HeatMapCellAction;
    OptionAction                 _inSpecies2HeatMapCellAction;
    OptionAction                 _crossSpecies1HeatMapCellAction;
    OptionAction                 _crossSpecies2HeatMapCellAction;
    bool                        _isLoading;
    Species1Action               _species1Action;
    Species2Action               _species2Action;
    VisSettingAction               _visSettingAction;
    LinkerSettingAction               _linkerSettingAction;
    DistanceNeighborhoodAction               _distanceNeighborhoodAction;
    CellCountAction               _cellCountAction;
    //ExplorationAction               _explorationAction;
    ToggleAction                _removeLinkingOptionMenuFromUIAction;
    TriggerAction                _helpAction;
    TriggerAction                _screenshotAction;

    OptionAction                 _barLinkerAction1;
    OptionAction                 _barLinkerAction2;

    bool _isStarted;
    ColorMapAction          _colorMapAction;
    ColorAction              _backgroundColoringAction;
    hdps::EventListener     _eventListener;
    /** Default constant color */
    static const QColor DEFAULT_CONSTANT_COLOR;
    friend class ChannelAction;
};