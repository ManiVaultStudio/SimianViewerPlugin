#pragma once

#include <actions/WidgetAction.h>
#include <actions/IntegralAction.h>
#include <actions/VariantAction.h>
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
#include <event/Event.h>
#include <QDebug>
#include <QLabel>

using namespace hdps::gui;
class QMenu;
class SimianViewerPlugin;
//class SimianViewerWidget;
class FetchMetaData;
namespace hdps
{
    class CoreInterface;
}
class SimianOptionsAction : public WidgetAction
{
public:
    class Species1Holder : public WidgetAction
    {
    protected:
        class Widget : public hdps::gui::WidgetActionWidget {
        public:
            Widget(QWidget* parent, Species1Holder* species1Holder);

            friend class Species1Holder;
        };

        QWidget* getWidget(QWidget* parent, const std::int32_t& widgetFlags) override {
            return new Species1Holder::Widget(parent, this);
        };

    public:
        Species1Holder(SimianOptionsAction& simianOptionsAction);

    protected:
        SimianOptionsAction& _simianOptionsAction;

        friend class SimianOptionsAction;
    };
    class Species2Holder : public WidgetAction
    {
    protected:
        class Widget : public hdps::gui::WidgetActionWidget {
        public:
            Widget(QWidget* parent, Species2Holder* species2Holder);

            friend class Species2Holder;
        };

        QWidget* getWidget(QWidget* parent, const std::int32_t& widgetFlags) override {
            return new Species2Holder::Widget(parent, this);
        };

    public:
        Species2Holder(SimianOptionsAction& simianOptionsAction);

    protected:
        SimianOptionsAction& _simianOptionsAction;

        friend class SimianOptionsAction;
    };
    class VisSettingHolder : public WidgetAction
    {
    protected:
        class Widget : public hdps::gui::WidgetActionWidget {
        public:
            Widget(QWidget* parent, VisSettingHolder* visSettingHolder);

            friend class VisSettingHolder;
        };

        QWidget* getWidget(QWidget* parent, const std::int32_t& widgetFlags) override {
            return new VisSettingHolder::Widget(parent, this);
        };

    public:
        VisSettingHolder(SimianOptionsAction& simianOptionsAction);

    protected:
        SimianOptionsAction& _simianOptionsAction;

       // friend class SimianOptionsAction;
    };
    class LinkerSettingHolder : public WidgetAction
    {
    protected:
        class Widget : public hdps::gui::WidgetActionWidget {
        public:
            Widget(QWidget* parent, LinkerSettingHolder* linkerSettingHolder);

            friend class LinkerSettingWidget;
        };

        QWidget* getWidget(QWidget* parent, const std::int32_t& widgetFlags) override {
            return new LinkerSettingHolder::Widget(parent, this);
        };

    public:
        LinkerSettingHolder(SimianOptionsAction& simianOptionsAction);

    protected:
        SimianOptionsAction& _simianOptionsAction;

        friend class SimianOptionsAction;
    };
    class ScatterplotColorHolder : public WidgetAction
    {
    protected:
        class Widget : public hdps::gui::WidgetActionWidget {
        public:
            Widget(QWidget* parent, ScatterplotColorHolder* scatterplotColorHolder);

            friend class ScatterplotColorHolder;
        };

        QWidget* getWidget(QWidget* parent, const std::int32_t& widgetFlags) override {
            return new ScatterplotColorHolder::Widget(parent, this);
        };

    public:
        ScatterplotColorHolder(SimianOptionsAction& simianOptionsAction);

    protected:
        SimianOptionsAction& _simianOptionsAction;

        friend class SimianOptionsAction;
    };
    class DistanceNeighborhoodHolder : public WidgetAction
    {
    protected:
        class Widget : public hdps::gui::WidgetActionWidget {
        public:
            Widget(QWidget* parent, DistanceNeighborhoodHolder* distanceNeighborhoodHolder);

            friend class DistanceNeighborhoodHolder;
        };

        QWidget* getWidget(QWidget* parent, const std::int32_t& widgetFlags) override {
            return new DistanceNeighborhoodHolder::Widget(parent, this);
        };

    public:
        DistanceNeighborhoodHolder(SimianOptionsAction& simianOptionsAction);

    protected:
        SimianOptionsAction& _simianOptionsAction;

        friend class SimianOptionsAction;
    };
    class CellCountHolder : public WidgetAction
    {
    protected:
        class Widget : public hdps::gui::WidgetActionWidget {
        public:
            Widget(QWidget* parent, CellCountHolder* cellCountHolder);

            friend class CellCountHolder;
        };

        QWidget* getWidget(QWidget* parent, const std::int32_t& widgetFlags) override {
            return new CellCountHolder::Widget(parent, this);
        };

    public:
        CellCountHolder(SimianOptionsAction& simianOptionsAction);

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
    void updateData(std::string Species1, std::string Species2, std::string neighborhood/*, int distance, std::string CrossSpeciesFilter*/);
    QVariant CalculateGeneExpressionValues(QString crossSpeciesCluster);
    //void filterMultiSelect();
    bool QStringlistContainsQString(const QStringList& list, const QString& str);
    //QString selectFromQStringList(const QStringList& fileList, const QString& speciesType, const QString& fileType, const QString& neighborhoodType);
protected:
    void updateDatasetPickerAction();
    void sendClusterCountInfoToJS();
    //void updateMultiSelectionDropdown(std::vector<std::vector<std::string>>& filteredVisData);
public: // Action getters

    OptionAction& getSpecies1SelectAction() { return _species1SelectAction; }
    OptionAction& getSpecies2SelectAction() { return _species2SelectAction; }
    OptionAction& getScatterplotColorControlAction() { return _scatterplotColorControlAction; }
    OptionAction& getNeighborhoodAction() { return _neighborhoodAction; }
    //IntegralAction& getDistanceAction() { return _distanceAction; };
    ToggleAction& getHistBarAction() { return _histBarAction; };
    TriggerAction& getmodifyDifferentialExpressionAutoUpdateAction() { return _modifyDifferentialExpressionAutoUpdate; };
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
    //OptionAction& getCrossSpeciesFilterAction() { return _crossSpeciesFilterAction; }
    OptionAction& getInSpecies1HeatMapCellAction() { return _inSpecies1HeatMapCellAction; }
    OptionAction& getInSpecies2HeatMapCellAction() { return _inSpecies2HeatMapCellAction; }
    OptionsAction& getCrossSpecies1HeatMapCellAction() { return _crossSpecies1HeatMapCellAction; }
    OptionsAction& getCrossSpecies2HeatMapCellAction() { return _crossSpecies2HeatMapCellAction; }
    Species1Holder& getSpecies1Holder() { return _species1Holder; }
    Species2Holder& getSpecies2Holder() { return _species2Holder; }
    VisSettingHolder& getVisSettingHolder() { return _visSettingHolder; }
    LinkerSettingHolder& getLinkerSettingHolder() { return _linkerSettingHolder; }
    DistanceNeighborhoodHolder& getDistanceNeighborhoodHolder() { return _distanceNeighborhoodHolder; }
    ScatterplotColorHolder& getScatterplotColorHolder() { return _scatterplotColorHolder; }
    ColorMapAction& getColorMapAction() { return _colorMapAction; }
    //ColorAction& getBackgroundColoringAction() { return _backgroundColoringAction; }
    CellCountHolder& getCellCountHolder() { return _cellCountHolder; }
    //TriggerAction& getHelpAction() { return _helpAction; }
    //TriggerAction& getScreenshotAction() { return _screenshotAction; }
    StringAction& getSpecies1Name() { return _species1Name; }
    StringAction& getSelectedCrossSpeciesNameList() { return _selectedCrossSpeciesNameList; }
    //OptionAction& getScatterplotColorControl() { return _scatterplotColorControlAction; }
    StringAction& getSpecies2Name() { return _species2Name; }
    StringAction& getSelectedCrossspeciescluster() { return _selectedCrossspeciescluster; }
    VariantAction& getGeneExpressionDatasetVariant() { return _geneExpressionDatasetVariant; }
    StringAction& getHarHcondelCountString() { return _harHcondelCountString; }
    ColorMapAction& getScatterplot1ColorMapAction() { return _scatterplot1ColorMapAction; }
    ColorMapAction& getScatterplot2ColorMapAction() { return _scatterplot2ColorMapAction; }
    //ExplorationAction& getExplorationAction() { return _explorationAction; }
public:
    void initLoader();

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

protected:
    SimianViewerPlugin&          _simianViewerPlugin;
    OptionAction                 _species1SelectAction;
    OptionAction                 _species2SelectAction;
    OptionAction                 _scatterplotColorControlAction;
    OptionAction                 _neighborhoodAction;
    //IntegralAction               _distanceAction;
    DatasetPickerAction           _crossSpecies1DatasetLinkerAction;
    DatasetPickerAction          _crossSpecies2DatasetLinkerAction;

    DatasetPickerAction           _species1ScatterplotColorLinkerAction;
    DatasetPickerAction          _species2ScatterplotColorLinkerAction;

    DatasetPickerAction           _speciesEmbedding1LinkerAction;
    DatasetPickerAction          _speciesEmbedding2LinkerAction;

    DatasetPickerAction           _species1DEStatsLinkerAction;
    DatasetPickerAction           _species2DEStatsLinkerAction;

    DatasetPickerAction           _inSpecies1DatasetLinkerAction;
    DatasetPickerAction          _inSpecies2DatasetLinkerAction;
    //OptionAction                 _crossSpeciesFilterAction;
    hdps::CoreInterface*         _core;
    FetchMetaData*                _metaData;
    std::vector<std::vector<std::string>>                _simianData;
    QVariantMap _geneExpressionData;
    //OptionsAction                 _multiSelectClusterFilterAction;
    ToggleAction _histBarAction;
    ToggleAction _fullHeatMapAction;
    //ToggleAction _explorationModeAction;
    OptionAction                 _inSpecies1HeatMapCellAction;
    OptionAction                 _inSpecies2HeatMapCellAction;
    OptionsAction                 _crossSpecies1HeatMapCellAction;
    OptionsAction                 _crossSpecies2HeatMapCellAction;
    Species1Holder               _species1Holder;
    Species2Holder             _species2Holder;
    VisSettingHolder              _visSettingHolder;
    LinkerSettingHolder               _linkerSettingHolder;
    DistanceNeighborhoodHolder                _distanceNeighborhoodHolder;
    ScatterplotColorHolder         _scatterplotColorHolder;
    CellCountHolder              _cellCountHolder;
    //ExplorationAction               _explorationAction;
    ToggleAction                _removeLinkingOptionMenuFromUIAction;
    //TriggerAction                _helpAction;
    //TriggerAction                _screenshotAction;
    TriggerAction                 _modifyDifferentialExpressionAutoUpdate;
    StringAction                  _species1Name;
    StringAction                  _species2Name;
    StringAction                    _selectedCrossspeciescluster;
    StringAction                    _harHcondelCountString;
    VariantAction                  _geneExpressionDatasetVariant;
    StringAction                _selectedCrossSpeciesNameList;
    bool _isStarted;
    ColorMapAction          _colorMapAction;
    ColorMapAction _scatterplot1ColorMapAction;
    ColorMapAction _scatterplot2ColorMapAction;
    //ColorAction              _backgroundColoringAction;
    hdps::EventListener     _eventListener;
    /** Default constant color */
    static const QColor DEFAULT_CONSTANT_COLOR;
    friend class ChannelAction;
};