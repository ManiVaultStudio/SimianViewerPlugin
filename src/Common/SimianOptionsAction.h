#pragma once

#include <actions/WidgetAction.h>
#include <actions/IntegralAction.h>
#include <actions/VariantAction.h>
#include <actions/ToggleAction.h>
#include "actions/DatasetPickerAction.h"
#include "actions/HorizontalGroupAction.h"
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
    class OptionsHolder : public HorizontalGroupAction
    {
    public:
        OptionsHolder(SimianOptionsAction& simianOptionsAction);

    protected:
        SimianOptionsAction& _simianOptionsAction;

        friend class SimianOptionsAction;
    };

    class VisSettingHolder : public GroupAction
    {
    public:
        VisSettingHolder(SimianOptionsAction& simianOptionsAction);

        const ToggleAction& getFullHeatmapAction() const { return _fullHeatMapAction; };
        const ColorMapAction& getColorMapAction() const { return _colorMapAction; }
        const OptionAction& getPluginVisibilityAction() const { return _pluginVisibility; }
        const ColorAction& getSelectionColorAction() const { return _selectionColorAction; }
        ToggleAction& getFullHeatmapAction() { return _fullHeatMapAction; };
        ColorMapAction& getColorMapAction() { return _colorMapAction; }
        OptionAction& getPluginVisibilityAction() { return _pluginVisibility; }
        ColorAction& getSelectionColorAction() { return _selectionColorAction; }
    protected:
        SimianOptionsAction& _simianOptionsAction;
        ToggleAction            _fullHeatMapAction;
        ColorMapAction          _colorMapAction;
        OptionAction            _pluginVisibility;
        ColorAction             _selectionColorAction;
        // friend class SimianOptionsAction;
    };
    class LinkerSettingHolder : public GroupAction
    {
    public:
        LinkerSettingHolder(SimianOptionsAction& simianOptionsAction);
        const DatasetPickerAction& getSmartSeqDataset1Action() const { return _smartSeqDataset1; };
        const DatasetPickerAction& getSmartSeqDataset2Action() const { return _smartSeqDataset2; };

        const DatasetPickerAction& getCrossSpecies1DatasetLinkerAction() const { return _crossSpecies1DatasetLinkerAction; };
        const DatasetPickerAction& getCrossSpecies2DatasetLinkerAction() const { return _crossSpecies2DatasetLinkerAction; };
        const DatasetPickerAction& getSpecies1ScatterplotColorLinkerAction() const { return _species1ScatterplotColorLinkerAction; };
        const DatasetPickerAction& getSpecies2ScatterplotColorLinkerAction()const { return _species2ScatterplotColorLinkerAction; };

        const DatasetPickerAction& getSpeciesEmbedding1LinkerAction() const { return _speciesEmbedding1LinkerAction; };
        const DatasetPickerAction& getSpeciesEmbedding2LinkerAction() const { return _speciesEmbedding2LinkerAction; };

        const DatasetPickerAction& getSpecies1DEStatsLinkerAction()const { return _species1DEStatsLinkerAction; };
        const DatasetPickerAction& getSpecies2DEStatsLinkerAction()const { return _species2DEStatsLinkerAction; };

        const DatasetPickerAction& getInSpecies1DatasetLinkerAction()const { return _inSpecies1DatasetLinkerAction; };
        const  DatasetPickerAction& getInSpecies2DatasetLinkerAction() const { return _inSpecies2DatasetLinkerAction; };
        const VariantAction& getGeneExpressionDatasetVariant() const { return _geneExpressionDatasetVariant; }
        const StringAction& getHarHcondelCountString() const { return _harHcondelCountString; }
        const VariantAction& getCommandAction() const { return _commandAction; }

        const OptionAction& getInSpecies1HeatMapCellAction() const { return _inSpecies1HeatMapCellAction; }
        const OptionAction& getInSpecies2HeatMapCellAction() const { return _inSpecies2HeatMapCellAction; }
        const OptionsAction& getCrossSpecies1HeatMapCellAction() const { return _crossSpecies1HeatMapCellAction; }
        const OptionsAction& getCrossSpecies2HeatMapCellAction() const { return _crossSpecies2HeatMapCellAction; }

        const TriggerAction& getmodifyDifferentialExpressionAutoUpdateAction()const { return _modifyDifferentialExpressionAutoUpdate; };
        const ToggleAction& getRemoveLinkingOptionMenuFromUIAction()const { return _removeLinkingOptionMenuFromUIAction; };

        const StringAction& getSpecies1Name() const { return _species1Name; }
        const StringAction& getSelectedCrossSpeciesNameList() const { return _selectedCrossSpeciesNameList; }
        const StringAction& getSpecies2Name() const { return _species2Name; }
        const  StringAction& getSelectedCrossspeciescluster() const { return _selectedCrossspeciescluster; }

        const ToggleAction& getParallelBarPluginVisibility() const { return _parallelBarPluginVisibility; }
        const ToggleAction& getPopPyramidPluginVisibility() const { return _popPyramidPluginVisibility; }

        DatasetPickerAction& getCrossSpecies1DatasetLinkerAction() { return _crossSpecies1DatasetLinkerAction; };
        DatasetPickerAction& getCrossSpecies2DatasetLinkerAction() { return _crossSpecies2DatasetLinkerAction; };


        DatasetPickerAction& getSmartSeqDataset1Action() { return _smartSeqDataset1; };
        DatasetPickerAction& getSmartSeqDataset2Action() { return _smartSeqDataset2; };

        DatasetPickerAction& getSpecies1ScatterplotColorLinkerAction() { return _species1ScatterplotColorLinkerAction; };
        DatasetPickerAction& getSpecies2ScatterplotColorLinkerAction() { return _species2ScatterplotColorLinkerAction; };

        DatasetPickerAction& getSpeciesEmbedding1LinkerAction() { return _speciesEmbedding1LinkerAction; };
        DatasetPickerAction& getSpeciesEmbedding2LinkerAction() { return _speciesEmbedding2LinkerAction; };

        DatasetPickerAction& getSpecies1DEStatsLinkerAction() { return _species1DEStatsLinkerAction; };
        DatasetPickerAction& getSpecies2DEStatsLinkerAction() { return _species2DEStatsLinkerAction; };

        DatasetPickerAction& getInSpecies1DatasetLinkerAction() { return _inSpecies1DatasetLinkerAction; };
        DatasetPickerAction& getInSpecies2DatasetLinkerAction() { return _inSpecies2DatasetLinkerAction; };
        VariantAction& getGeneExpressionDatasetVariant() { return _geneExpressionDatasetVariant; }

        VariantAction& getCommandAction() { return _commandAction; }
        StringAction& getHarHcondelCountString() { return _harHcondelCountString; }

        OptionAction& getInSpecies1HeatMapCellAction() { return _inSpecies1HeatMapCellAction; }
        OptionAction& getInSpecies2HeatMapCellAction() { return _inSpecies2HeatMapCellAction; }
        OptionsAction& getCrossSpecies1HeatMapCellAction() { return _crossSpecies1HeatMapCellAction; }
        OptionsAction& getCrossSpecies2HeatMapCellAction() { return _crossSpecies2HeatMapCellAction; }

        TriggerAction& getmodifyDifferentialExpressionAutoUpdateAction() { return _modifyDifferentialExpressionAutoUpdate; };
        ToggleAction& getRemoveLinkingOptionMenuFromUIAction() { return _removeLinkingOptionMenuFromUIAction; };

        StringAction& getSpecies1Name() { return _species1Name; }
        StringAction& getSelectedCrossSpeciesNameList() { return _selectedCrossSpeciesNameList; }
        StringAction& getSpecies2Name() { return _species2Name; }
        StringAction& getSelectedCrossspeciescluster() { return _selectedCrossspeciescluster; }
        ToggleAction& getParallelBarPluginVisibility() { return _parallelBarPluginVisibility; }
        ToggleAction& getPopPyramidPluginVisibility() { return _popPyramidPluginVisibility; }
    protected:
        ToggleAction                _popPyramidPluginVisibility;
        ToggleAction                _parallelBarPluginVisibility;
        DatasetPickerAction           _crossSpecies1DatasetLinkerAction;
        DatasetPickerAction          _crossSpecies2DatasetLinkerAction;

        DatasetPickerAction _smartSeqDataset1;
        DatasetPickerAction _smartSeqDataset2;

        DatasetPickerAction           _species1ScatterplotColorLinkerAction;
        DatasetPickerAction          _species2ScatterplotColorLinkerAction;

        DatasetPickerAction           _speciesEmbedding1LinkerAction;
        DatasetPickerAction          _speciesEmbedding2LinkerAction;

        DatasetPickerAction           _species1DEStatsLinkerAction;
        DatasetPickerAction           _species2DEStatsLinkerAction;

        DatasetPickerAction           _inSpecies1DatasetLinkerAction;
        DatasetPickerAction          _inSpecies2DatasetLinkerAction;
        ToggleAction                _removeLinkingOptionMenuFromUIAction;
        VariantAction                  _geneExpressionDatasetVariant;
        VariantAction                       _commandAction;
        StringAction                    _harHcondelCountString;
        TriggerAction                 _modifyDifferentialExpressionAutoUpdate;
        OptionAction                 _inSpecies1HeatMapCellAction;
        OptionAction                 _inSpecies2HeatMapCellAction;
        OptionsAction                 _crossSpecies1HeatMapCellAction;
        OptionsAction                 _crossSpecies2HeatMapCellAction;

        StringAction                  _species1Name;
        StringAction                  _species2Name;
        StringAction                    _selectedCrossspeciescluster;

        SimianOptionsAction& _simianOptionsAction;
        StringAction                _selectedCrossSpeciesNameList;
        // friend class SimianOptionsAction;
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

    OptionAction& getNeighborhoodAction() { return _neighborhoodAction; }
    //IntegralAction& getDistanceAction() { return _distanceAction; };
    ToggleAction& getHistBarAction() { return _histBarAction; };


    //ToggleAction& getExplorationModeAction() { return _explorationModeAction; };



    //OptionAction& getCrossSpeciesFilterAction() { return _crossSpeciesFilterAction; }

    OptionsHolder& getOptionsHolder() { return _optionsHolder; }
    //Species2Holder& getSpecies2Holder() { return _species2Holder; }
    VisSettingHolder& getVisSettingHolder() { return _visSettingHolder; }
    LinkerSettingHolder& getLinkerSettingHolder() { return _linkerSettingHolder; }
    //DistanceNeighborhoodHolder& getDistanceNeighborhoodHolder() { return _distanceNeighborhoodHolder; }
    //ScatterplotColorHolder& getScatterplotColorHolder() { return _scatterplotColorHolder; }
    OptionAction& getScatterplotColorControlAction() { return _scatterplotColorControlAction; }
    //ColorAction& getBackgroundColoringAction() { return _backgroundColoringAction; }
    //CellCountHolder& getCellCountHolder() { return _cellCountHolder; }
    //TriggerAction& getHelpAction() { return _helpAction; }
    //TriggerAction& getScreenshotAction() { return _screenshotAction; }

    //OptionAction& getScatterplotColorControl() { return _scatterplotColorControlAction; }

    bool& getStopMethodFlagFromSpecies1() { return _stopMethodFlagFromSpecies1; }
    bool& getStopMethodFlagFromSpecies2() { return _stopMethodFlagFromSpecies2; }
    //ColorMapAction& getScatterplotColorMapAction() { return _scatterplotColorMapAction; }
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
    SimianViewerPlugin& _simianViewerPlugin;
    OptionAction                 _species1SelectAction;
    OptionAction                 _species2SelectAction;
    OptionAction                 _scatterplotColorControlAction;
    OptionAction                 _neighborhoodAction;
    //IntegralAction               _distanceAction;

    //OptionAction                 _crossSpeciesFilterAction;
    hdps::CoreInterface* _core;
    FetchMetaData* _metaData;
    std::vector<std::vector<std::string>>                _simianData;
    QVariantMap _geneExpressionData;
    //OptionsAction                 _multiSelectClusterFilterAction;
    ToggleAction _histBarAction;

    //ToggleAction _explorationModeAction;
    VisSettingHolder              _visSettingHolder;
    OptionsHolder               _optionsHolder;
    //Species2Holder             _species2Holder;
    LinkerSettingHolder               _linkerSettingHolder;
    //DistanceNeighborhoodHolder                _distanceNeighborhoodHolder;
    //ScatterplotColorHolder         _scatterplotColorHolder;
    //CellCountHolder              _cellCountHolder;
    //ExplorationAction               _explorationAction;
    //TriggerAction                _helpAction;
    //TriggerAction                _screenshotAction;
    bool _stopMethodFlagFromSpecies1 = false;
    bool _stopMethodFlagFromSpecies2 = false;
    bool _isStarted;
    //ColorMapAction _scatterplotColorMapAction;
    //ColorAction              _backgroundColoringAction;
    hdps::EventListener     _eventListener;
    /** Default constant color */
    static const QColor DEFAULT_CONSTANT_COLOR;
    friend class ChannelAction;
};