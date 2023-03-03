#include "SimianOptionsAction.h"
#include "SimianViewerPlugin.h"
#include <QFileDialog>
#include <QPageLayout>
#include <QWebEngineView>
using namespace hdps;
using namespace hdps::gui;
const QColor SimianOptionsAction::DEFAULT_CONSTANT_COLOR = qRgb(255, 255, 255);

SimianOptionsAction::SimianOptionsAction(SimianViewerPlugin& simianViewerPlugin, hdps::CoreInterface* core) :
	WidgetAction(&simianViewerPlugin),
	_simianViewerPlugin(simianViewerPlugin),
	_core(core),
	_species1SelectAction(this,"Species1(X-axis)"),
	_species2SelectAction(this,"Species2(Y-axis)"),
	_neighborhoodAction(this,"Neighborhood"),
	_scatterplotColorControlAction(this, "Scatterplot color"),
	//_distanceAction(this, "Filter distance :"),

	//_crossSpeciesFilterAction(this, "Filter clusters"),

	//_multiSelectClusterFilterAction(this, "Select cross-species clusters"),
	//_backgroundColoringAction(this, "Select background color", DEFAULT_CONSTANT_COLOR, DEFAULT_CONSTANT_COLOR),
	_optionsHolder(*this),
	//_species2Holder(*this),
	_visSettingHolder(*this),
	_linkerSettingHolder(*this),
	//_distanceNeighborhoodHolder(*this),
	//_scatterplotColorHolder(*this),
	//_explorationAction(*this),
	//_cellCountHolder(*this),
	_isStarted(false),
	_histBarAction(this,"Cell counts")
	/*,
	_explorationModeAction(this)*/
	//_helpAction(this, "Help"),
	//_screenshotAction(this, "Screenshot"),

	//_scatterplotColorMapAction(this,"Scatterplot1 color map connection"),
	
{
	setText("Settings");
	setSerializationName("SimianSettings");
	_species1SelectAction.setSerializationName( "Species1(X-axis)");
		_species2SelectAction.setSerializationName( "Species2(Y-axis)");
		_neighborhoodAction.setSerializationName( "Neighborhood");
		_scatterplotColorControlAction.setSerializationName( "Scatterplot color");
		//_distanceAction.setSerializationName( "Filter distance :");
		_linkerSettingHolder.getCrossSpecies1DatasetLinkerAction().setSerializationName( "Cross-species cluster dataset1");
		_linkerSettingHolder.getCrossSpecies2DatasetLinkerAction().setSerializationName( "Cross-species  cluster dataset2");
		_linkerSettingHolder.getSpecies1ScatterplotColorLinkerAction().setSerializationName( "Scatterplot color linker species1");
		_linkerSettingHolder.getSpecies2ScatterplotColorLinkerAction().setSerializationName( "Scatterplot color linker species2");
		_linkerSettingHolder.getSpeciesEmbedding1LinkerAction().setSerializationName( "Embedding dataset1");
		_linkerSettingHolder.getSpeciesEmbedding2LinkerAction().setSerializationName( "Embedding dataset2");
		_linkerSettingHolder.getSpecies1DEStatsLinkerAction().setSerializationName( "DEStats dataset1");
		_linkerSettingHolder.getSpecies2DEStatsLinkerAction().setSerializationName( "DEStats dataset2");
		_linkerSettingHolder.getInSpecies1DatasetLinkerAction().setSerializationName( "In-species  cluster dataset1");
		_linkerSettingHolder.getInSpecies2DatasetLinkerAction().setSerializationName( "In-species  cluster dataset2");
		//_crossSpeciesFilterAction.setSerializationName( "Filter clusters");
		_linkerSettingHolder.getInSpecies1HeatMapCellAction().setSerializationName( "Link in-species1 heatmap cell");
		_linkerSettingHolder.getInSpecies2HeatMapCellAction().setSerializationName( "Link in-species2 heatmap cell");
		_linkerSettingHolder.getCrossSpecies1HeatMapCellAction().setSerializationName( "Link cross-species1 heatmap cell");
		_linkerSettingHolder.getCrossSpecies2HeatMapCellAction().setSerializationName( "Link cross-species2 heatmap cell");
		_linkerSettingHolder.getmodifyDifferentialExpressionAutoUpdateAction().setSerializationName( "Automatic Update Switch");
		_linkerSettingHolder.getRemoveLinkingOptionMenuFromUIAction().setSerializationName( "Remove linking option");
		_linkerSettingHolder.getSpecies1Name().setSerializationName( "Species1Name");
		_linkerSettingHolder.getSpecies2Name().setSerializationName( "Species2Name");
		_linkerSettingHolder.getSelectedCrossspeciescluster().setSerializationName( "Selected CrossSpecies Cluster");
		_linkerSettingHolder.getGeneExpressionDatasetVariant().setSerializationName( "Gene Expression Variant");
		_linkerSettingHolder.getCommandAction().setSerializationName( "Command Action Variant");

		_linkerSettingHolder.getSelectedCrossSpeciesNameList().setSerializationName( "Selected Cross Species Name List");
		_linkerSettingHolder.getHarHcondelCountString().setSerializationName("Har-Hcondel Count String");
		_visSettingHolder.getColorMapAction().setSerializationName("Color map");

		_visSettingHolder.getPluginVisibilityAction().setSerializationName("PairwiseORMultiSpeciesComparison");
		
		//_backgroundColoringAction.setSerializationName("Select background color");
		//_scatterplot1ColorMapAction.setSerializationName( "Scatterplot1 color map connection");
		//_scatterplot2ColorMapAction.setSerializationName("Scatterplot2 color map connection");
		_visSettingHolder.getFullHeatmapAction().setSerializationName("Full distancemap");
		_histBarAction.setSerializationName("Cell counts");
		

	//_helpAction.setDefaultWidgetFlags(TriggerAction::Icon);
	//_screenshotAction.setDefaultWidgetFlags(TriggerAction::Icon);

	//connect(&_helpAction, &TriggerAction::triggered, this, [this]() -> void {
	//	_simianViewerPlugin.getTriggerHelpAction().trigger();
	//});


	_eventListener.addSupportedEventType(static_cast<std::uint32_t>(EventType::DataAdded));
	_eventListener.addSupportedEventType(static_cast<std::uint32_t>(EventType::DataRemoved));
	_eventListener.addSupportedEventType(static_cast<std::uint32_t>(EventType::DataChildAdded));
	_eventListener.addSupportedEventType(static_cast<std::uint32_t>(EventType::DataChildRemoved));
	_eventListener.addSupportedEventType(static_cast<std::uint32_t>(EventType::DataChanged));
	_eventListener.addSupportedEventType(static_cast<std::uint32_t>(EventType::DataGuiNameChanged));
	_eventListener.registerDataEventByType(PointType, std::bind(&SimianOptionsAction::onDataEvent, this, std::placeholders::_1));
	_metaData = new FetchMetaData();
	_metaData->getData(&_simianData);
	_metaData->getGeneExpressionData(&_geneExpressionData);
	//_species2SelectAction.setEnabled(false);
	//_neighborhoodAction.setEnabled(false);
	//_distanceAction.setEnabled(false);
	//_screenshotAction.setEnabled(false);
	//_distanceAction.setVisible(false);
	//_histBarAction.setEnabled(false);
	//_visSettingHolder.getFullHeatmapAction().setEnabled(false);
	//_explorationModeAction.setEnabled(false);
	//_linkerSettingHolder.getCrossSpecies1DatasetLinkerAction().setEnabled(false);
	//_linkerSettingHolder.getCrossSpecies2DatasetLinkerAction().setEnabled(false);
	//_linkerSettingHolder.getSpecies1ScatterplotColorLinkerAction().setEnabled(false);
	//_linkerSettingHolder.getSpecies2ScatterplotColorLinkerAction().setEnabled(false);
	//_scatterplotColorControlAction.setEnabled(false);
	//_linkerSettingHolder.getSpeciesEmbedding1LinkerAction().setEnabled(false);
	//_linkerSettingHolder.getSpeciesEmbedding2LinkerAction().setEnabled(false);
	//_species1DEStatsLinkerAction
	//_linkerSettingHolder.getSpecies1DEStatsLinkerAction().setEnabled(false);
	//_linkerSettingHolder.getSpecies2DEStatsLinkerAction().setEnabled(false);
	//_linkerSettingHolder.getInSpecies1DatasetLinkerAction().setEnabled(false);
	//_linkerSettingHolder.getInSpecies2DatasetLinkerAction().setEnabled(false);
	//_crossSpeciesFilterAction.setEnabled(false);
	//_multiSelectClusterFilterAction.setEnabled(false);
	//_visSettingHolder.getColorMapAction().setEnabled(false);
	//_backgroundColoringAction.setEnabled(false);
	//_visSettingHolder.setEnabled(false);
	//_linkerSettingHolder.setEnabled(false);
	//_distanceNeighborhoodHolder.setEnabled(false);
	_species1SelectAction.setDefaultWidgetFlags(OptionAction::ComboBox);
	//_species1SelectAction.setPlaceHolderString(QString("Choose Species1"));
	_species1SelectAction.initialize(QStringList({ "human","chimp","gorilla","rhesus","marmoset"}), "chimp", "chimp");
	_species2SelectAction.setDefaultWidgetFlags(OptionAction::ComboBox);
	//_species2SelectAction.setPlaceHolderString(QString("Choose Species2"));
	_species2SelectAction.initialize(QStringList({ "human","gorilla","rhesus","marmoset" }), "human", "human");
	_visSettingHolder.getPluginVisibilityAction().initialize(QStringList({ "pairwise","multi" }), "multi", "multi");
	//_crossSpeciesFilterAction.setDefaultWidgetFlags(OptionAction::ComboBox);
	//_crossSpeciesFilterAction.initialize(QStringList({ "all clusters","cross-species clusters" }), "cross-species clusters", "cross-species clusters");
	_linkerSettingHolder.getInSpecies1HeatMapCellAction().setDefaultWidgetFlags(OptionAction::ComboBox);

	_linkerSettingHolder.getInSpecies2HeatMapCellAction().setDefaultWidgetFlags(OptionAction::ComboBox);
	_linkerSettingHolder.getCrossSpecies1HeatMapCellAction().setDefaultWidgetFlags(OptionAction::ComboBox);
	_linkerSettingHolder.getCrossSpecies2HeatMapCellAction().setDefaultWidgetFlags(OptionAction::ComboBox);
	//_multiSelectClusterFilterAction.setDefaultWidgetFlags(OptionsAction::ComboBox | OptionsAction::Selection | OptionsAction::File);
	//_multiSelectClusterFilterAction.initialize(QStringList{ "" });
	//_multiSelectClusterFilterAction.setSelectedOptions(QStringList());
	_visSettingHolder.getColorMapAction().initialize("Black to white", "Black to white");
	_visSettingHolder.setConfigurationFlag(WidgetAction::ConfigurationFlag::AlwaysCollapsed);
	_visSettingHolder.setConfigurationFlag(WidgetAction::ConfigurationFlag::NoLabelInGroup);
	//_scatterplot1ColorMapAction.initialize("Viridis", "Viridis");
	//_scatterplot2ColorMapAction.initialize("Viridis", "Viridis");
	//_backgroundColoringAction.initialize(DEFAULT_CONSTANT_COLOR, DEFAULT_CONSTANT_COLOR);
	_neighborhoodAction.setDefaultWidgetFlags(OptionAction::ComboBox);
	_neighborhoodAction.initialize(QStringList({ "Non-neuronal cells","IT-projecting excitatory","Non-IT-projecting excitatory","CGE-derived inhibitory","MGE-derived inhibitory" }), "CGE-derived inhibitory", "CGE-derived inhibitory");
	QStringList defaultTotalValues = QStringList({ " ","exc","glia","inh","Astro_2","Astro_3","Astro_4","Chandelier_1","Chandelier_2","Endo_1","Endo_2","L2/3 IT_1","L2/3 IT_2","L2/3 IT_3","L2/3 IT_4","L4 IT_1","L4 IT_2","L4 IT_3","L4 IT_4","L4 IT_5","L5 ET_1","L5 ET_2","L5 ET_3","L5 ET_4","L5 IT_1","L5 IT_2","L5 IT_3","L5/6 NP_1","L5/6 NP_2","L5/6 NP_3","L5/6 NP_4","L6 CT_1","L6 CT_2","L6 IT Car3_1","L6 IT Car3_2","L6 IT Car3_3","L6 IT_1","L6 IT_2","L6 IT_3","L6b_1","L6b_2","L6b_3","L6b_4","L6b_5","L6b_6","Lamp5_1","Lamp5_2","Lamp5_Lhx6_1","Lamp5_Lhx6_2","Micro-PVM_1","Micro-PVM_2","Micro-PVM_3","OPC_1","OPC_2","OPC_3","Oligo_1","Pax6_1","Pax6_2","Pax6_3","Pax6_4","Pvalb_1","Pvalb_2","Pvalb_3","Pvalb_4","Pvalb_5","Pvalb_6","Pvalb_7","Pvalb_8","Sncg_1","Sncg_2","Sncg_3","Sncg_4","Sncg_5","Sncg_6","Sncg_7","Sst Chodl_1","Sst Chodl_2","Sst Chodl_3","Sst_1","Sst_10","Sst_11","Sst_12","Sst_13","Sst_14","Sst_15","Sst_16","Sst_17","Sst_18","Sst_2","Sst_3","Sst_4","Sst_5","Sst_6","Sst_7","Sst_8","Sst_9","VLMC_1","VLMC_2","VLMC_3","VLMC_4","Vip_1","Vip_10","Vip_11","Vip_12","Vip_13","Vip_14","Vip_15","Vip_16","Vip_17","Vip_2","Vip_3","Vip_4","Vip_5","Vip_6","Vip_7","Vip_8","Vip_9","Astro_5","L2/3 IT_10","L2/3 IT_11","L2/3 IT_12","L2/3 IT_13","L2/3 IT_5","L2/3 IT_6","L2/3 IT_7","L2/3 IT_8","L2/3 IT_9","L5 IT_4","L5 IT_5","L5 IT_6","L5 IT_7","L5/6 NP_5","L5/6 NP_6","L6 CT_3","L6 CT_4","Lamp5_3","Lamp5_4","Lamp5_5","Lamp5_6","Oligo_2","Oligo_3","Oligo_4","Pvalb_10","Pvalb_11","Pvalb_12","Pvalb_13","Pvalb_14","Pvalb_15","Pvalb_9","Sncg_8","Sst_19","Sst_20","Sst_21","Sst_22","Sst_23","Sst_24","Sst_25","Sst_26","Vip_18","Vip_19","Vip_20","Vip_21","Vip_22","Vip_23","Endo_3","L4 IT_6","Micro-PVM_4","OPC_4","Sncg_9","L2/3 IT_14","L2/3 IT_15","L5/6 NP_7","L5/6 NP_8","L6 IT_4","Sncg_10","Glutamatergic","Non-Neuronal","Chandelier","Endo","L2/3 IT","L4 IT","L5 ET","L5 IT","L5/6 NP","L6 CT","L6 IT","L6 IT Car3","L6b","Lamp5","Lamp5_Lhx6","Micro-PVM","OPC","Oligo","Pax6","Pvalb","Sncg","Sst","Sst Chodl","VLMC","Vip","G19.32.002","G20.32.001","G20.32.002","H18.30.002","H19.30.001","H19.30.002","H200.1023","bi006","bi007","Q19.26.011","Q19.26.015","C19.32.002","C19.32.003","C19.32.004","C19.32.005","C19.32.006","C19.32.007","H18.30.001","bi005","Q19.26.010","C19.32.001","it_types","l5et_l56np_l6ct_l6b","lamp5_sncg_vip","sst_sst_chodl_pvalb","Astro_1","GABAergic","Astro","G19.32.001" });
	_linkerSettingHolder.getCrossSpecies2HeatMapCellAction().initialize(defaultTotalValues, { "" });
	_linkerSettingHolder.getCrossSpecies1HeatMapCellAction().initialize(defaultTotalValues, { "" });
	_linkerSettingHolder.getSpecies1Name().initialize("");
	_linkerSettingHolder.getSpecies2Name().initialize("");
	_linkerSettingHolder.getSelectedCrossspeciescluster().initialize("");
	_linkerSettingHolder.getSelectedCrossSpeciesNameList().initialize("");
	_linkerSettingHolder.getInSpecies2HeatMapCellAction().initialize(defaultTotalValues, "", "");
	_linkerSettingHolder.getInSpecies1HeatMapCellAction().initialize(defaultTotalValues, "", "");

	_scatterplotColorControlAction.setDefaultWidgetFlags(OptionAction::ComboBox);
	_scatterplotColorControlAction.initialize(QStringList({ "cross-species cluster","in-species cluster","differential expression","cross-species sub-class","in-species subclass","donor"}), "cross-species cluster", "cross-species cluster");
	//_distanceAction.setDefaultWidgetFlags(IntegralAction::SpinBox | IntegralAction::Slider);
	//_distanceAction.initialize(0, 105, 105, 105);
	_histBarAction.setDefaultWidgetFlags(ToggleAction::CheckBox);
	_histBarAction.initialize(false, false);
	//_histBarAction.setDefaultWidgetFlags(ToggleAction::PushButton);

	_linkerSettingHolder.getRemoveLinkingOptionMenuFromUIAction().setDefaultWidgetFlags(ToggleAction::CheckBox);
	_linkerSettingHolder.getRemoveLinkingOptionMenuFromUIAction().initialize(false, false);
	_visSettingHolder.getFullHeatmapAction().setDefaultWidgetFlags(ToggleAction::CheckBox);
	_visSettingHolder.getFullHeatmapAction().initialize(false, false);
	//_explorationModeAction.setDefaultWidgetFlags(ToggleAction::CheckBox);
	//_explorationModeAction.initialize(false, false);
	_linkerSettingHolder.getCrossSpecies1DatasetLinkerAction().setDefaultWidgetFlags(OptionAction::ComboBox);
	_linkerSettingHolder.getCrossSpecies2DatasetLinkerAction().setDefaultWidgetFlags(OptionAction::ComboBox);
	_linkerSettingHolder.getSpecies1ScatterplotColorLinkerAction().setDefaultWidgetFlags(OptionAction::ComboBox);
	_linkerSettingHolder.getSpecies2ScatterplotColorLinkerAction().setDefaultWidgetFlags(OptionAction::ComboBox);
	_linkerSettingHolder.getSpeciesEmbedding1LinkerAction().setDefaultWidgetFlags(OptionAction::ComboBox);
	_linkerSettingHolder.getSpeciesEmbedding2LinkerAction().setDefaultWidgetFlags(OptionAction::ComboBox);
	_linkerSettingHolder.getSpecies2DEStatsLinkerAction().setDefaultWidgetFlags(OptionAction::ComboBox);
	_linkerSettingHolder.getSpecies1DEStatsLinkerAction().setDefaultWidgetFlags(OptionAction::ComboBox);
	_linkerSettingHolder.getInSpecies1DatasetLinkerAction().setDefaultWidgetFlags(OptionAction::ComboBox);
	_linkerSettingHolder.getInSpecies2DatasetLinkerAction().setDefaultWidgetFlags(OptionAction::ComboBox);
	_visSettingHolder.getColorMapAction().getSettingsAction().getDiscreteAction().setVisible(false);
	_visSettingHolder.getColorMapAction().getSettingsAction().getEditor1DAction().setVisible(false);

	//_scatterplot1ColorMapAction.getSettingsAction().getDiscreteAction().setVisible(false);
	//_scatterplot1ColorMapAction.getSettingsAction().getEditor1DAction().setVisible(false);

	//_scatterplot2ColorMapAction.getSettingsAction().getDiscreteAction().setVisible(false);
	//_scatterplot2ColorMapAction.getSettingsAction().getEditor1DAction().setVisible(false);

	_linkerSettingHolder.getmodifyDifferentialExpressionAutoUpdateAction().setConnectionPermissionsFlag(ConnectionPermissionFlag::All);
	_linkerSettingHolder.getmodifyDifferentialExpressionAutoUpdateAction().connectToPublicActionByName("Cluster Differential Expression 1::CalculateDifferentialExpression");
	_linkerSettingHolder.getGeneExpressionDatasetVariant().setConnectionPermissionsFlag(ConnectionPermissionFlag::All);
	_linkerSettingHolder.getGeneExpressionDatasetVariant().connectToPublicActionByName("Cluster Differential Expression 1::TableViewLeftSideInfo");
	_linkerSettingHolder.getCommandAction().setConnectionPermissionsFlag(ConnectionPermissionFlag::All);
	_linkerSettingHolder.getCommandAction().connectToPublicActionByName("Cluster Differential Expression 1::InvokeMethods");
	_linkerSettingHolder.getCrossSpecies1DatasetLinkerAction().setConnectionPermissionsFlag(ConnectionPermissionFlag::All);
	_linkerSettingHolder.getCrossSpecies1DatasetLinkerAction().connectToPublicActionByName("Cluster Differential Expression 1::Dataset1");
	_linkerSettingHolder.getCrossSpecies2DatasetLinkerAction().setConnectionPermissionsFlag(ConnectionPermissionFlag::All);
	_linkerSettingHolder.getCrossSpecies2DatasetLinkerAction().connectToPublicActionByName("Cluster Differential Expression 1::Dataset2");
	_linkerSettingHolder.getSpecies1Name().setConnectionPermissionsFlag(ConnectionPermissionFlag::All);
	_linkerSettingHolder.getSpecies1Name().connectToPublicActionByName("Cluster Differential Expression 1::DatasetName1");
	_linkerSettingHolder.getSpecies2Name().setConnectionPermissionsFlag(ConnectionPermissionFlag::All);
	_linkerSettingHolder.getSpecies2Name().connectToPublicActionByName("Cluster Differential Expression 1::DatasetName2");
	_linkerSettingHolder.getCrossSpecies1HeatMapCellAction().setConnectionPermissionsFlag(ConnectionPermissionFlag::All);
	_linkerSettingHolder.getCrossSpecies1HeatMapCellAction().connectToPublicActionByName("Cluster Differential Expression 1::SelectClusters1");
	_linkerSettingHolder.getCrossSpecies2HeatMapCellAction().setConnectionPermissionsFlag(ConnectionPermissionFlag::All);
	_linkerSettingHolder.getCrossSpecies2HeatMapCellAction().connectToPublicActionByName("Cluster Differential Expression 1::SelectClusters2");
	_linkerSettingHolder.getHarHcondelCountString().setConnectionPermissionsFlag(ConnectionPermissionFlag::All);
	_linkerSettingHolder.getHarHcondelCountString().connectToPublicActionByName("Cluster Differential Expression 1::IntoText");

	_linkerSettingHolder.getSelectedCrossspeciescluster().setConnectionPermissionsFlag(ConnectionPermissionFlag::All);
	_linkerSettingHolder.getSelectedCrossspeciescluster().connectToPublicActionByName("Pop Pyramid:: Selected CrossSpecies Cluster");
	_linkerSettingHolder.getSpecies1DEStatsLinkerAction().setConnectionPermissionsFlag(ConnectionPermissionFlag::All);
	_linkerSettingHolder.getSpecies1DEStatsLinkerAction().connectToPublicActionByName("Pop Pyramid:: DE Dataset1");
	_linkerSettingHolder.getSpecies2DEStatsLinkerAction().setConnectionPermissionsFlag(ConnectionPermissionFlag::All);
	_linkerSettingHolder.getSpecies2DEStatsLinkerAction().connectToPublicActionByName("Pop Pyramid:: DE Dataset2");

	_linkerSettingHolder.getPopPyramidPluginVisibility().setConnectionPermissionsFlag(ConnectionPermissionFlag::All);
	_linkerSettingHolder.getPopPyramidPluginVisibility().connectToPublicActionByName("Pop Pyramid::PluginVisibility");
	_linkerSettingHolder.getSpecies1ScatterplotColorLinkerAction().setConnectionPermissionsFlag(ConnectionPermissionFlag::All);
	_linkerSettingHolder.getSpecies1ScatterplotColorLinkerAction().connectToPublicActionByName("Scatterplot View 1::Color");
	_linkerSettingHolder.getSpecies2ScatterplotColorLinkerAction().setConnectionPermissionsFlag(ConnectionPermissionFlag::All);
	_linkerSettingHolder.getSpecies2ScatterplotColorLinkerAction().connectToPublicActionByName("Scatterplot View 2::Color");
	_linkerSettingHolder.getSpeciesEmbedding1LinkerAction().setConnectionPermissionsFlag(ConnectionPermissionFlag::All);
	_linkerSettingHolder.getSpeciesEmbedding1LinkerAction().connectToPublicActionByName("Scatterplot View 1::Embedding");
	_linkerSettingHolder.getSpeciesEmbedding2LinkerAction().setConnectionPermissionsFlag(ConnectionPermissionFlag::All);
	_linkerSettingHolder.getSpeciesEmbedding2LinkerAction().connectToPublicActionByName("Scatterplot View 2::Embedding");

	_neighborhoodAction.setConnectionPermissionsFlag(ConnectionPermissionFlag::ConnectViaApi);
	_neighborhoodAction.connectToPublicActionByName("ParallelBars::Neighbhorhood");
	_linkerSettingHolder.getParallelBarPluginVisibility().setConnectionPermissionsFlag(ConnectionPermissionFlag::All);
	_linkerSettingHolder.getParallelBarPluginVisibility().connectToPublicActionByName("ParallelBars::PluginVisibility");


	//const auto globalColorMapName = "GlobalColorMap";
	//_scatterplotColorMapAction.setConnectionPermissionsFlag(ConnectionPermissionFlag::All);
	//_scatterplotColorMapAction.connectToPublicActionByName(globalColorMapName);
	//_scatterplot1ColorMapAction.setConnectionPermissionsFlag(ConnectionPermissionFlag::All);
	//_scatterplot1ColorMapAction.connectToPublicActionByName("Scatterplot View 1::Color map");
	//_scatterplot2ColorMapAction.setConnectionPermissionsFlag(ConnectionPermissionFlag::All);
	//_scatterplot2ColorMapAction.connectToPublicActionByName("Scatterplot View 2::Color map");


	//_linkerSettingHolder.getInSpecies1DatasetLinkerAction().setVisible(false);
	//_linkerSettingHolder.getInSpecies2DatasetLinkerAction().setVisible(false);
	//_linkerSettingHolder.getCrossSpecies1DatasetLinkerAction().setVisible(false);
	//_linkerSettingHolder.getCrossSpecies2DatasetLinkerAction().setVisible(false);
	//_linkerSettingHolder.getSpecies1ScatterplotColorLinkerAction().setVisible(false);
	//_linkerSettingHolder.getSpecies2ScatterplotColorLinkerAction().setVisible(false);
	//_linkerSettingHolder.getSpeciesEmbedding1LinkerAction().setVisible(false);
	//_linkerSettingHolder.getSpeciesEmbedding2LinkerAction().setVisible(false);
	//_linkerSettingHolder.getSpecies1DEStatsLinkerAction().setVisible(false);
	//_linkerSettingHolder.getSpecies2DEStatsLinkerAction().setVisible(false);
	//_linkerSettingHolder.getInSpecies1HeatMapCellAction().setVisible(false);
	//_linkerSettingHolder.getInSpecies2HeatMapCellAction().setVisible(false);

	//_helpAction.setIcon(Application::getIconFont("FontAwesome").getIcon("question"));
	//_screenshotAction.setIcon(Application::getIconFont("FontAwesome").getIcon("camera"));
	//const auto updateCrossSpeciesFilter = [this]() -> void
	//{
	//	updateDatasetPickerAction();
	//	//if ((_crossSpeciesFilterAction.getCurrentText()).toStdString() == "all clusters")
	//	//{
	//	//	_multiSelectClusterFilterAction.setEnabled(false);
	//	//	_multiSelectClusterFilterAction.setSelectedOptions(QStringList());
	//	//}
	//	//else {
	//	//	_multiSelectClusterFilterAction.setEnabled(true);
	//	//}
	//	if (_species1SelectAction.getCurrentText() != "" && _species2SelectAction.getCurrentText() != "")
	//	{
	//		updateData((_species1SelectAction.getCurrentText()).toStdString(), (_species2SelectAction.getCurrentText()).toStdString(), (_neighborhoodAction.getCurrentText()).toStdString()/*, (_distanceAction.getValue()), (_crossSpeciesFilterAction.getCurrentText()).toStdString()*/);
	//	}




	//};

	//const auto multiSelectClusterFilter = [this]() -> void
	//{
	//	if (_isStarted)
	//	{
	//		if ((_crossSpeciesFilterAction.getCurrentText()).toStdString() == "cross-species clusters")
	//		{
	//			filterMultiSelect();
	//		}
	//	}
	//};

	const auto colormapFilter = [this]() -> void
	{
		const auto& mirrorAction = _visSettingHolder.getColorMapAction().getSettingsAction().getHorizontalAxisAction().getMirrorAction();
		std::string s1 = _visSettingHolder.getColorMapAction().getColorMap().toStdString();
		std::string s2 = "*%*";
		std::string s3;
		if (mirrorAction.isChecked())
		{
			s3 = "T";
		}
		else
		{
			s3 = "F";
		}
		std::string full = s1 + s2 + s3;
		_simianViewerPlugin.getSimianViewerWidget().setColor(QString::fromStdString(full));
	};
	//const auto backgroundColoringFilter = [this]() -> void
	//{
	//	const auto& color = _backgroundColoringAction.getColor();

	//	_simianViewerPlugin.getSimianViewerWidget().setBackgroundColor(color.name());
	//};
	const auto updateColorMapRange = [this]() -> void
	{
		const auto& rangeAction = _visSettingHolder.getColorMapAction().getSettingsAction().getHorizontalAxisAction().getRangeAction();
		std::string s1 = std::to_string(rangeAction.getMinimum());
		std::string s2 = " ";
		std::string s3 = std::to_string(rangeAction.getMaximum());
		std::string full = s1.substr(0, s1.find(".") + 3) + s2 + s3.substr(0, s3.find(".") + 3);
		_simianViewerPlugin.getSimianViewerWidget().setRangeValue(QString::fromStdString(full));
	};

	const auto updateSpecies1 = [this]() -> void
	{
		_stopMethodFlagFromSpecies1 = true;

		QString storeCrossSpeciesClusterSelection = _linkerSettingHolder.getSelectedCrossspeciescluster().getString();
		_linkerSettingHolder.getSelectedCrossspeciescluster().setString("");
		//if (_species1SelectAction.getCurrentText() != "")
		//{
			//_species2SelectAction.setEnabled(true);
			_linkerSettingHolder.getSpecies1Name().setString(_species1SelectAction.getCurrentText());

			if (_linkerSettingHolder.getCrossSpecies1DatasetLinkerAction().getNumberOfOptions() > 0)
			{
				QString species1CrossSpeciesClusterDatasetName = _species1SelectAction.getCurrentText() + "_" + _neighborhoodAction.getCurrentText() + "_cross_species_cluster";
				_linkerSettingHolder.getCrossSpecies1DatasetLinkerAction().setCurrentText(species1CrossSpeciesClusterDatasetName);
			}

			if (_linkerSettingHolder.getInSpecies1DatasetLinkerAction().getNumberOfOptions() > 0)
			{
				QString species1InSpeciesClusterDatasetName = _species1SelectAction.getCurrentText() + "_" + _neighborhoodAction.getCurrentText() + "_cluster";
				_linkerSettingHolder.getInSpecies1DatasetLinkerAction().setCurrentText(species1InSpeciesClusterDatasetName);
			}

			if (_linkerSettingHolder.getSpeciesEmbedding1LinkerAction().getNumberOfOptions() > 0)
			{
				QString species1EmbeddingDatasetName = _species1SelectAction.getCurrentText() + "_" + _neighborhoodAction.getCurrentText()+"_embedding";
				_linkerSettingHolder.getSpeciesEmbedding1LinkerAction().setCurrentText(species1EmbeddingDatasetName);
			}

			if (_linkerSettingHolder.getSpecies1DEStatsLinkerAction().getNumberOfOptions() > 0)
			{

				const QString child_DE_Statistics_DatasetName = "DE_Statistics";
				hdps::Dataset<Clusters> clusterDataset = _linkerSettingHolder.getCrossSpecies1DatasetLinkerAction().getCurrentDataset();
				QString DatasetGUID = "";
					const auto& childDatasets = clusterDataset->getChildren({ PointType });
					for (qsizetype i = 0; i < childDatasets.size(); ++i)
					{
						if (childDatasets[i]->getGuiName() == child_DE_Statistics_DatasetName)
						{
							DatasetGUID = childDatasets[i].getDatasetGuid();
							_linkerSettingHolder.getSpecies1DEStatsLinkerAction().setCurrentDataset(DatasetGUID);
							break;
						} 
					}
				
				
				//QString species1DEStatsDatasetName = _species1SelectAction.getCurrentText() + "_" + _neighborhoodAction.getCurrentText() + "_DE_Statistics";
				
			}

			QString storeSpecies = _species2SelectAction.getCurrentText();
			QStringList speciesNames = { "human","chimp","gorilla","rhesus","marmoset"};
			speciesNames.removeAll(_species1SelectAction.getCurrentText());
			_species2SelectAction.initialize(QStringList({ speciesNames }), storeSpecies, storeSpecies);


			if (_species2SelectAction.getCurrentText() == _species1SelectAction.getCurrentText())
			{

				QStringList speciesNames = { "human","chimp","gorilla","rhesus","marmoset" };
				speciesNames.removeAll(_species1SelectAction.getCurrentText());
				_species2SelectAction.initialize(QStringList({ speciesNames }), "", "");
				//QString tempVal = _scatterplotColorControlAction.getCurrentText();
				//_scatterplotColorControlAction.setCurrentText("");
				//_scatterplotColorControlAction.setCurrentText(tempVal);
				_species2SelectAction.setCurrentIndex(0);
				//_simianViewerPlugin.getSimianViewerWidget().resetView("Reset");
			}
			
			else
			{
				//if (_species2SelectAction.getCurrentText() != "")
				//{
					QString tempVal = _scatterplotColorControlAction.getCurrentText();
					_scatterplotColorControlAction.setCurrentText("");
					_scatterplotColorControlAction.setCurrentText(tempVal);
					updateData((_species1SelectAction.getCurrentText()).toStdString(), (_species2SelectAction.getCurrentText()).toStdString(), (_neighborhoodAction.getCurrentText()).toStdString()/*, (_distanceAction.getValue()), (_crossSpeciesFilterAction.getCurrentText()).toStdString()*/);
					if (_neighborhoodAction.getCurrentText() == "Non-neuronal cells")
					{
						_linkerSettingHolder.getCrossSpecies1HeatMapCellAction().setSelectedOptions({ "" });
						_linkerSettingHolder.getCrossSpecies2HeatMapCellAction().setSelectedOptions({ "" });
						_linkerSettingHolder.getSelectedCrossSpeciesNameList().setString("");
						_linkerSettingHolder.getCrossSpecies1HeatMapCellAction().setSelectedOptions({ "Astro_1" });
						_linkerSettingHolder.getCrossSpecies2HeatMapCellAction().setSelectedOptions({ "Astro_1" });
						_linkerSettingHolder.getSelectedCrossSpeciesNameList().setString("Astro_1");
					}
					else if (_neighborhoodAction.getCurrentText() == "IT-projecting excitatory")
					{
						_linkerSettingHolder.getCrossSpecies1HeatMapCellAction().setSelectedOptions({ "" });
						_linkerSettingHolder.getCrossSpecies2HeatMapCellAction().setSelectedOptions({ "" });
						_linkerSettingHolder.getSelectedCrossSpeciesNameList().setString("");
						_linkerSettingHolder.getCrossSpecies1HeatMapCellAction().setSelectedOptions({ "L2/3 IT_1" });
						_linkerSettingHolder.getCrossSpecies2HeatMapCellAction().setSelectedOptions({ "L2/3 IT_1" });
						_linkerSettingHolder.getSelectedCrossSpeciesNameList().setString("L2/3 IT_1");
					}
					else if (_neighborhoodAction.getCurrentText() == "Non-IT-projecting excitatory")
					{
						_linkerSettingHolder.getCrossSpecies1HeatMapCellAction().setSelectedOptions({ "" });
						_linkerSettingHolder.getCrossSpecies2HeatMapCellAction().setSelectedOptions({ "" });
						_linkerSettingHolder.getSelectedCrossSpeciesNameList().setString("");
						_linkerSettingHolder.getCrossSpecies1HeatMapCellAction().setSelectedOptions({ "L6 CT_1" });
						_linkerSettingHolder.getCrossSpecies2HeatMapCellAction().setSelectedOptions({ "L6 CT_1" });
						_linkerSettingHolder.getSelectedCrossSpeciesNameList().setString("L6 CT_1");
					}
					else if (_neighborhoodAction.getCurrentText() == "CGE-derived inhibitory")
					{
						_linkerSettingHolder.getCrossSpecies1HeatMapCellAction().setSelectedOptions({ "" });
						_linkerSettingHolder.getCrossSpecies2HeatMapCellAction().setSelectedOptions({ "" });
						_linkerSettingHolder.getSelectedCrossSpeciesNameList().setString("");
						_linkerSettingHolder.getCrossSpecies1HeatMapCellAction().setSelectedOptions({ "Lamp5_1" });
						_linkerSettingHolder.getCrossSpecies2HeatMapCellAction().setSelectedOptions({ "Lamp5_1" });
						_linkerSettingHolder.getSelectedCrossSpeciesNameList().setString("Lamp5_1");
					}
					else if (_neighborhoodAction.getCurrentText() == "MGE-derived inhibitory")
					{
						_linkerSettingHolder.getCrossSpecies1HeatMapCellAction().setSelectedOptions({ "" });
						_linkerSettingHolder.getCrossSpecies2HeatMapCellAction().setSelectedOptions({ "" });
						_linkerSettingHolder.getSelectedCrossSpeciesNameList().setString("");
						_linkerSettingHolder.getCrossSpecies1HeatMapCellAction().setSelectedOptions({ "Sst Chodl_1" });
						_linkerSettingHolder.getCrossSpecies2HeatMapCellAction().setSelectedOptions({ "Sst Chodl_1" });
						_linkerSettingHolder.getSelectedCrossSpeciesNameList().setString("Sst Chodl_1");
					}
					if (_scatterplotColorControlAction.getCurrentText() == "differential expression")
					{
						_scatterplotColorControlAction.setCurrentText("cross-species cluster");
					}
					_linkerSettingHolder.getSelectedCrossspeciescluster().setString("");
					_linkerSettingHolder.getSelectedCrossspeciescluster().setString(storeCrossSpeciesClusterSelection);
					_linkerSettingHolder.getmodifyDifferentialExpressionAutoUpdateAction().trigger();
				//}

			}
			_stopMethodFlagFromSpecies1 = false;
		//}
		//else
		//{
			//_species2SelectAction.setCurrentText("");
			//_simianViewerPlugin.getSimianViewerWidget().resetView("Reset");
			//_species2SelectAction.setEnabled(false);
			//_neighborhoodAction.setEnabled(false);
			//_screenshotAction.setEnabled(false);
			//_distanceAction.setEnabled(false);
			//_histBarAction.setEnabled(false);
			//_visSettingHolder.getFullHeatmapAction().setEnabled(false);
			//_linkerSettingHolder.getCrossSpecies1DatasetLinkerAction().setEnabled(false);
			//_linkerSettingHolder.getCrossSpecies2DatasetLinkerAction().setEnabled(false);
			//_linkerSettingHolder.getSpecies1ScatterplotColorLinkerAction().setEnabled(false);
			//_linkerSettingHolder.getSpecies2ScatterplotColorLinkerAction().setEnabled(false);
			//_scatterplotColorControlAction.setEnabled(false);
			//_linkerSettingHolder.getSpeciesEmbedding1LinkerAction().setEnabled(false);
			//_linkerSettingHolder.getSpeciesEmbedding2LinkerAction().setEnabled(false);
			//_linkerSettingHolder.getSpecies2DEStatsLinkerAction().setEnabled(false);
			//_linkerSettingHolder.getSpecies1DEStatsLinkerAction().setEnabled(false);
			//_linkerSettingHolder.getInSpecies1DatasetLinkerAction().setEnabled(false);
			//_linkerSettingHolder.getInSpecies2DatasetLinkerAction().setEnabled(false);
			//_crossSpeciesFilterAction.setEnabled(false);;
			//_visSettingHolder.getColorMapAction().setEnabled(false);
			//_backgroundColoringAction.setEnabled(false);
			//_visSettingHolder.setEnabled(false);
			//_linkerSettingHolder.setEnabled(false);
			//_distanceNeighborhoodHolder.setEnabled(false);
		//}
	};



	const auto updateSpecies2 = [this]() -> void
	{
		//if (_species2SelectAction.getCurrentText() != "")
		//{
			//_neighborhoodAction.setEnabled(true);
			//_screenshotAction.setEnabled(true);
			//_linkerSettingHolder.getCrossSpecies1DatasetLinkerAction().setEnabled(true);
			//_linkerSettingHolder.getCrossSpecies2DatasetLinkerAction().setEnabled(true);
			//_linkerSettingHolder.getSpecies2Name().setString(_species2SelectAction.getCurrentText());
			//_linkerSettingHolder.getSpeciesEmbedding1LinkerAction().setEnabled(true);
			//_linkerSettingHolder.getSpeciesEmbedding2LinkerAction().setEnabled(true);
			//_linkerSettingHolder.getSpecies1DEStatsLinkerAction().setEnabled(true);
			//_linkerSettingHolder.getSpecies2DEStatsLinkerAction().setEnabled(true);
			//_linkerSettingHolder.getInSpecies1DatasetLinkerAction().setEnabled(true);
			//_linkerSettingHolder.getInSpecies2DatasetLinkerAction().setEnabled(true);
			//_crossSpeciesFilterAction.setEnabled(true);
			//_visSettingHolder.getFullHeatmapAction().setEnabled(true);
			//_visSettingHolder.getColorMapAction().setEnabled(true);
			//_backgroundColoringAction.setEnabled(true);
			//_visSettingHolder.setEnabled(true);
			//_linkerSettingHolder.setEnabled(true);
			//_distanceNeighborhoodHolder.setEnabled(true);
		_stopMethodFlagFromSpecies2 = true;
		QString storeCrossSpeciesClusterSelection = _linkerSettingHolder.getSelectedCrossspeciescluster().getString();
		_linkerSettingHolder.getSelectedCrossspeciescluster().setString("");
		_linkerSettingHolder.getSpecies2Name().setString(_species2SelectAction.getCurrentText());

			if (_linkerSettingHolder.getCrossSpecies2DatasetLinkerAction().getNumberOfOptions() > 0)
			{
				QString species2CrossSpeciesClusterDatasetName = _species2SelectAction.getCurrentText() + "_" + _neighborhoodAction.getCurrentText() + "_cross_species_cluster";
				_linkerSettingHolder.getCrossSpecies2DatasetLinkerAction().setCurrentText(species2CrossSpeciesClusterDatasetName);
			}

			if (_linkerSettingHolder.getInSpecies2DatasetLinkerAction().getNumberOfOptions() > 0)
			{
				QString species2InSpeciesClusterDatasetName = _species2SelectAction.getCurrentText() + "_" + _neighborhoodAction.getCurrentText() + "_cluster";
				_linkerSettingHolder.getInSpecies2DatasetLinkerAction().setCurrentText(species2InSpeciesClusterDatasetName);
			}
			if (_linkerSettingHolder.getSpeciesEmbedding2LinkerAction().getNumberOfOptions() > 0)
			{
				QString species2EmbeddingDatasetName = _species2SelectAction.getCurrentText() + "_" + _neighborhoodAction.getCurrentText() + "_embedding";
				_linkerSettingHolder.getSpeciesEmbedding2LinkerAction().setCurrentText(species2EmbeddingDatasetName);
			}

			if (_linkerSettingHolder.getSpecies2DEStatsLinkerAction().getNumberOfOptions() > 0)
			{
				const QString child_DE_Statistics_DatasetName = "DE_Statistics";
				hdps::Dataset<Clusters> clusterDataset = _linkerSettingHolder.getCrossSpecies2DatasetLinkerAction().getCurrentDataset();
				QString DatasetGUID = "";
				const auto& childDatasets = clusterDataset->getChildren({ PointType });
				for (qsizetype i = 0; i < childDatasets.size(); ++i)
				{
					if (childDatasets[i]->getGuiName() == child_DE_Statistics_DatasetName)
					{
						DatasetGUID = childDatasets[i].getDatasetGuid();
						_linkerSettingHolder.getSpecies2DEStatsLinkerAction().setCurrentDataset(DatasetGUID);
						break;
					}
				}


				//QString species2DEStatsDatasetName = _species2SelectAction.getCurrentText() + "_" + _neighborhoodAction.getCurrentText() + "_DE_Statistics";

				//_linkerSettingHolder.getSpecies2DEStatsLinkerAction().setCurrentText(species2DEStatsDatasetName);
			}

			//if (_species1SelectAction.getCurrentText() != "")
			//{
			updateData((_species1SelectAction.getCurrentText()).toStdString(), (_species2SelectAction.getCurrentText()).toStdString(), (_neighborhoodAction.getCurrentText()).toStdString()/*, (_distanceAction.getValue()), (_crossSpeciesFilterAction.getCurrentText()).toStdString()*/);
			QString tempVal = _scatterplotColorControlAction.getCurrentText();
			_scatterplotColorControlAction.setCurrentText("");
			_scatterplotColorControlAction.setCurrentText(tempVal);

			if (_neighborhoodAction.getCurrentText() == "Non-neuronal cells")
			{
				_linkerSettingHolder.getCrossSpecies1HeatMapCellAction().setSelectedOptions({ "" });
				_linkerSettingHolder.getCrossSpecies2HeatMapCellAction().setSelectedOptions({ "" });
				_linkerSettingHolder.getSelectedCrossSpeciesNameList().setString("");
				_linkerSettingHolder.getCrossSpecies1HeatMapCellAction().setSelectedOptions({ "Astro_1" });
				_linkerSettingHolder.getCrossSpecies2HeatMapCellAction().setSelectedOptions({ "Astro_1" });
				_linkerSettingHolder.getSelectedCrossSpeciesNameList().setString("Astro_1");
			}
			else if (_neighborhoodAction.getCurrentText() == "IT-projecting excitatory")
			{
				_linkerSettingHolder.getCrossSpecies1HeatMapCellAction().setSelectedOptions({ "" });
				_linkerSettingHolder.getCrossSpecies2HeatMapCellAction().setSelectedOptions({ "" });
				_linkerSettingHolder.getSelectedCrossSpeciesNameList().setString("");
				_linkerSettingHolder.getCrossSpecies1HeatMapCellAction().setSelectedOptions({ "L2/3 IT_1" });
				_linkerSettingHolder.getCrossSpecies2HeatMapCellAction().setSelectedOptions({ "L2/3 IT_1" });
				_linkerSettingHolder.getSelectedCrossSpeciesNameList().setString("L2/3 IT_1");
			}
			else if (_neighborhoodAction.getCurrentText() == "Non-IT-projecting excitatory")
			{
				_linkerSettingHolder.getCrossSpecies1HeatMapCellAction().setSelectedOptions({ "" });
				_linkerSettingHolder.getCrossSpecies2HeatMapCellAction().setSelectedOptions({ "" });
				_linkerSettingHolder.getSelectedCrossSpeciesNameList().setString("");
				_linkerSettingHolder.getCrossSpecies1HeatMapCellAction().setSelectedOptions({ "L6 CT_1" });
				_linkerSettingHolder.getCrossSpecies2HeatMapCellAction().setSelectedOptions({ "L6 CT_1" });
				_linkerSettingHolder.getSelectedCrossSpeciesNameList().setString("L6 CT_1");
			}
			else if (_neighborhoodAction.getCurrentText() == "CGE-derived inhibitory")
			{
				_linkerSettingHolder.getCrossSpecies1HeatMapCellAction().setSelectedOptions({ "" });
				_linkerSettingHolder.getCrossSpecies2HeatMapCellAction().setSelectedOptions({ "" });
				_linkerSettingHolder.getSelectedCrossSpeciesNameList().setString("");
				_linkerSettingHolder.getCrossSpecies1HeatMapCellAction().setSelectedOptions({ "Lamp5_1" });
				_linkerSettingHolder.getCrossSpecies2HeatMapCellAction().setSelectedOptions({ "Lamp5_1" });
				_linkerSettingHolder.getSelectedCrossSpeciesNameList().setString("Lamp5_1");
			}
			else if (_neighborhoodAction.getCurrentText() == "MGE-derived inhibitory")
			{
				_linkerSettingHolder.getCrossSpecies1HeatMapCellAction().setSelectedOptions({ "" });
				_linkerSettingHolder.getCrossSpecies2HeatMapCellAction().setSelectedOptions({ "" });
				_linkerSettingHolder.getSelectedCrossSpeciesNameList().setString("");
				_linkerSettingHolder.getCrossSpecies1HeatMapCellAction().setSelectedOptions({ "Sst Chodl_1" });
				_linkerSettingHolder.getCrossSpecies2HeatMapCellAction().setSelectedOptions({ "Sst Chodl_1" });
				_linkerSettingHolder.getSelectedCrossSpeciesNameList().setString("Sst Chodl_1");
			}
			if (_scatterplotColorControlAction.getCurrentText() == "differential expression")
			{
				_scatterplotColorControlAction.setCurrentText("cross-species cluster");
			}
			if (!_stopMethodFlagFromSpecies1)
			{
				_linkerSettingHolder.getSelectedCrossspeciescluster().setString("");
				_linkerSettingHolder.getSelectedCrossspeciescluster().setString(storeCrossSpeciesClusterSelection);
				_linkerSettingHolder.getmodifyDifferentialExpressionAutoUpdateAction().trigger();
			}
			//}
			_stopMethodFlagFromSpecies2 = false;
		//}
		//else
		//{
			//_simianViewerPlugin.getSimianViewerWidget().resetView("Reset");
			//_neighborhoodAction.setEnabled(false);
			//_screenshotAction.setEnabled(false);
			//_scatterplotColorControlAction.setEnabled(false);
			//_distanceAction.setEnabled(false);
			//_histBarAction.setEnabled(false);
			//_visSettingHolder.getFullHeatmapAction().setEnabled(false);
			//_linkerSettingHolder.getCrossSpecies1DatasetLinkerAction().setEnabled(false);
			//_linkerSettingHolder.getCrossSpecies2DatasetLinkerAction().setEnabled(false);
			//_linkerSettingHolder.getSpecies1ScatterplotColorLinkerAction().setEnabled(false);
			//_linkerSettingHolder.getSpecies2ScatterplotColorLinkerAction().setEnabled(false);
			//_linkerSettingHolder.getSpeciesEmbedding1LinkerAction().setEnabled(false);
			//_linkerSettingHolder.getSpeciesEmbedding2LinkerAction().setEnabled(false);
			//_linkerSettingHolder.getSpecies2DEStatsLinkerAction().setEnabled(false);
			//_linkerSettingHolder.getSpecies1DEStatsLinkerAction().setEnabled(false);
			//_linkerSettingHolder.getInSpecies1DatasetLinkerAction().setEnabled(false);
			//_linkerSettingHolder.getInSpecies2DatasetLinkerAction().setEnabled(false);
			//_crossSpeciesFilterAction.setEnabled(false);;
			//_visSettingHolder.getColorMapAction().setEnabled(false);
			//_backgroundColoringAction.setEnabled(false);
			//_visSettingHolder.setEnabled(false);
			//_linkerSettingHolder.setEnabled(false);
			//_distanceNeighborhoodHolder.setEnabled(false);
		//}
	};



	const auto updateSelectedCrossSpeciesNameList = [this]() -> void
	{
		QVariantList commands;

			QVariantList command;
			//command << QString("TableView") << QString("SLOT_setColumnWidth") << int(0) << int(120);
			//commands.push_back(command);
			//command.clear();
			//command << QString("TableView") << QString("SLOT_setColumnWidth") << int(1) << int(40);
			//commands.push_back(command);
			//command.clear();
			//command << QString("TableView") << QString("SLOT_setColumnWidth") << int(2) << int(40);
			//commands.push_back(command);
			//command.clear();
			//command << QString("TableView") << QString("SLOT_setColumnWidth") << int(3) << int(120);
			//commands.push_back(command);
			//command.clear();
			//command << QString("TableView") << QString("SLOT_setColumnWidth") << int(4) << int(120);
			//commands.push_back(command);
			//command.clear();
			//command << QString("TableViewClusterSelection1") << QString("setDisabled") << bool(true);
			//commands.push_back(command);
			//command.clear();
			//command << QString("TableViewClusterSelection2") << QString("setDisabled") << bool(true);
			//commands.push_back(command);
			//command.clear();

			//command << QString("LoadedDataSettings") << "hide";
			//commands.push_back(command);
			//command.clear();


			//Qt::SortOrder sortOrder = Qt::DescendingOrder;
			//QVariant sortOrderVariant(QMetaType::fromType<Qt::SortOrder>(), & sortOrder);
			//command<<QString("TableView")<<QString("sortByColumn")<< int(3) <<sortOrderVariant;
			//commands.push_back(command);

		if((_species1SelectAction.getCurrentText() == "human" || _species2SelectAction.getCurrentText() == "human") && _linkerSettingHolder.getSelectedCrossSpeciesNameList().getString() != "")
		{
			//if (_linkerSettingHolder.getSelectedCrossSpeciesNameList().getString() != "")
			//{
				QVariant geneExpValue = CalculateGeneExpressionValues(_linkerSettingHolder.getSelectedCrossSpeciesNameList().getString());
				QVariantMap geneEXp;
				QVariantMap HARs;
				QVariantMap CONDELs;
				int HARCount = 0;
				int HCONDELCount = 0;
				//tempVariantMap[QString::number(Qt::ForegroundRole)] = QBrush(QColor::fromRgb(128, 128, 128));

				for (auto gene : geneExpValue.toMap().keys())
				{
					//qDebug() << geneExpValue.toMap().value(gene).toMap().value("HARs").toString() << '\n';
					//qDebug() << geneExpValue.toMap().value(gene).toMap().value("hCONDELs").toString() << '\n';
					// 

					//HAR Process
					if (geneExpValue.toMap().value(gene).toMap().value("HARs").toString() != "0")
					{
						QVariantMap tempHARVariantMap;
						//tempHARVariantMap[QString::number(Qt::DecorationRole)] = QColor::fromRgb(0, 0, 0);
						tempHARVariantMap[QString::number(Qt::DecorationRole)] = Application::getIconFont("FontAwesome").getIcon("check", Qt::black);
						tempHARVariantMap[QString::number(Qt::SizeHintRole)] = QSize(1, 1);
						tempHARVariantMap[QString::number(Qt::DisplayRole)] = QString(" ");
						tempHARVariantMap[QString::number(Qt::ToolTipRole)] = QString(geneExpValue.toMap().value(gene).toMap().value("HARs").toString());

						HARs.insert(gene, tempHARVariantMap);
						HARCount = HARCount+1;
					}

					//HCONDEL Process
					if (geneExpValue.toMap().value(gene).toMap().value("hCONDELs").toString() != "0")
					{
						QVariantMap tempHCONDELVariantMap;
						//tempHCONDELVariantMap[QString::number(Qt::DecorationRole)] = QColor::fromRgb(0, 0, 0);
						tempHCONDELVariantMap[QString::number(Qt::DecorationRole)] = Application::getIconFont("FontAwesome").getIcon("check", Qt::black);
						tempHCONDELVariantMap[QString::number(Qt::SizeHintRole)] = QSize(1, 1);
						tempHCONDELVariantMap[QString::number(Qt::DisplayRole)] = QString(" ");
						tempHCONDELVariantMap[QString::number(Qt::ToolTipRole)] = QString(geneExpValue.toMap().value(gene).toMap().value("hCONDELs").toString());

						CONDELs.insert(gene, tempHCONDELVariantMap);
						HCONDELCount = HCONDELCount+1;
					}
				}
				geneEXp.insert("H A R s", HARs);
				geneEXp.insert("h C O N D E L s", CONDELs);
				
				_linkerSettingHolder.getHarHcondelCountString().setString( "Genes associated with HARs: <b>" + QString::number(HARCount) + "</b> and hCONDELs: <b>" + QString::number(HCONDELCount) + "</b>");

				//countValues += "HARS:";
				//countValues += QString::number(HARCount);
				//countValues += "\nHCONDELS:";
				//countValues += QString::number(HCONDELCount);
				//qDebug() << geneEXp;
				/*qDebug() << "Count"<< countValues;*/
				_linkerSettingHolder.getGeneExpressionDatasetVariant().setVariant(geneEXp);
				QVariantList command;
				command << QString("TableView") << QString("showColumn") << int(1);
				commands.push_back(command);
				command.clear();
				command << QString("TableView") << QString("showColumn") << int(2);
				commands.push_back(command);
			//}
		}
		

		else
		{
			QVariantMap geneEXp;
			QVariantMap HARs;
			QVariantMap CONDELs;
			geneEXp.insert("H A R s", HARs);
			geneEXp.insert("h C O N D E L s", CONDELs);
			_linkerSettingHolder.getGeneExpressionDatasetVariant().setVariant(geneEXp);
			_linkerSettingHolder.getHarHcondelCountString().setString("");
			QVariantList command;
			command << QString("TableView") << QString("hideColumn") << int(1);
			commands.push_back(command);
			command.clear();
			command << QString("TableView") << QString("hideColumn") << int(2);
			commands.push_back(command);
		}
		_linkerSettingHolder.getCommandAction
			().setVariant(commands);
		
	};
	const auto updateNeighborhood = [this]() -> void
	{
		
		if (_species1SelectAction.getCurrentText() != "" && _species2SelectAction.getCurrentText() != "")
		{
			updateData((_species1SelectAction.getCurrentText()).toStdString(), (_species2SelectAction.getCurrentText()).toStdString(), (_neighborhoodAction.getCurrentText()).toStdString()/*, (_distanceAction.getValue()), (_crossSpeciesFilterAction.getCurrentText()).toStdString()*/);
			_linkerSettingHolder.getSelectedCrossspeciescluster().setString("");
			
			if (_linkerSettingHolder.getSpeciesEmbedding1LinkerAction().getNumberOfOptions() > 0)
			{
				QString species1EmbeddingDatasetName = _species1SelectAction.getCurrentText() + "_" + _neighborhoodAction.getCurrentText()+"_embedding";

				_linkerSettingHolder.getSpeciesEmbedding1LinkerAction().setCurrentText(species1EmbeddingDatasetName);
			}
			if (_linkerSettingHolder.getSpeciesEmbedding2LinkerAction().getNumberOfOptions() > 0)
			{
				QString species2EmbeddingDatasetName = _species2SelectAction.getCurrentText() + "_" + _neighborhoodAction.getCurrentText() + "_embedding";
				_linkerSettingHolder.getSpeciesEmbedding2LinkerAction().setCurrentText(species2EmbeddingDatasetName);
			}
			if (_scatterplotColorControlAction.getCurrentText() == "differential expression")
			{
				_scatterplotColorControlAction.setCurrentText("cross-species cluster");
			}
			if (_linkerSettingHolder.getSpecies1ScatterplotColorLinkerAction().getNumberOfOptions() > 0)
			{
				QString species1EmbeddingColorDatasetName = "";
				if (_scatterplotColorControlAction.getCurrentText() == "cross-species cluster")
				{
					species1EmbeddingColorDatasetName = _species1SelectAction.getCurrentText() + "_" + _neighborhoodAction.getCurrentText() + "_cross_species_cluster";
				}
				else if (_scatterplotColorControlAction.getCurrentText() == "in-species cluster")
				{
					species1EmbeddingColorDatasetName = _species1SelectAction.getCurrentText() + "_" + _neighborhoodAction.getCurrentText() + "_cluster";
				}

				else if (_scatterplotColorControlAction.getCurrentText() == "cross-species sub-class")
				{
					species1EmbeddingColorDatasetName = _species1SelectAction.getCurrentText() + "_" + _neighborhoodAction.getCurrentText() + "_cross_species_subclass";
				}
				else if (_scatterplotColorControlAction.getCurrentText() == "in-species subclass")
				{
					species1EmbeddingColorDatasetName = _species1SelectAction.getCurrentText() + "_" + _neighborhoodAction.getCurrentText() + "_subclass";
				}
				else if (_scatterplotColorControlAction.getCurrentText() == "donor")
				{
					species1EmbeddingColorDatasetName = _species1SelectAction.getCurrentText() + "_" + _neighborhoodAction.getCurrentText() + "_donor";
				}
				else if (_scatterplotColorControlAction.getCurrentText() == "differential expression")
				{
					species1EmbeddingColorDatasetName = "Cluster Differential Expression 1::SelectedIDMeanExpressionsDataset 0";
				}

				_linkerSettingHolder.getSpecies1ScatterplotColorLinkerAction().setCurrentText(species1EmbeddingColorDatasetName);
				//qDebug() << _linkerSettingHolder.getSpecies1ScatterplotColorLinkerAction().getCurrentText();
			}
			if (_linkerSettingHolder.getSpecies2ScatterplotColorLinkerAction().getNumberOfOptions() > 0)
			{
				QString species2EmbeddingColorDatasetName = "";
				if (_scatterplotColorControlAction.getCurrentText() == "cross-species cluster")
				{
					species2EmbeddingColorDatasetName = _species2SelectAction.getCurrentText() + "_" + _neighborhoodAction.getCurrentText() + "_cross_species_cluster";
				}
				else if (_scatterplotColorControlAction.getCurrentText() == "in-species cluster")
				{
					species2EmbeddingColorDatasetName = _species2SelectAction.getCurrentText() + "_" + _neighborhoodAction.getCurrentText() + "_cluster";
				}

				else if (_scatterplotColorControlAction.getCurrentText() == "cross-species sub-class")
				{
					species2EmbeddingColorDatasetName = _species2SelectAction.getCurrentText() + "_" + _neighborhoodAction.getCurrentText() + "_cross_species_subclass";
				}
				else if (_scatterplotColorControlAction.getCurrentText() == "in-species subclass")
				{
					species2EmbeddingColorDatasetName = _species2SelectAction.getCurrentText() + "_" + _neighborhoodAction.getCurrentText() + "_subclass";
				}
				else if (_scatterplotColorControlAction.getCurrentText() == "donor")
				{
					species2EmbeddingColorDatasetName = _species2SelectAction.getCurrentText() + "_" + _neighborhoodAction.getCurrentText() + "_donor";
				}
				else if (_scatterplotColorControlAction.getCurrentText() == "differential expression")
				{
					species2EmbeddingColorDatasetName = "Cluster Differential Expression 1::SelectedIDMeanExpressionsDataset 1";
				}

				_linkerSettingHolder.getSpecies2ScatterplotColorLinkerAction().setCurrentText(species2EmbeddingColorDatasetName);
				//qDebug() << _linkerSettingHolder.getSpecies2ScatterplotColorLinkerAction().getCurrentText();
			}


				
				//QString species2DEStatsDatasetName = _species2SelectAction.getCurrentText() + "_" + _neighborhoodAction.getCurrentText() + "_DE_Statistics";

				//_linkerSettingHolder.getSpecies2DEStatsLinkerAction().setCurrentText(species2DEStatsDatasetName);
			}
			if (_linkerSettingHolder.getInSpecies1DatasetLinkerAction().getNumberOfOptions() > 0)
			{
				QString species1InSpeciesClusterDatasetName = _species1SelectAction.getCurrentText() + "_" + _neighborhoodAction.getCurrentText() + "_cluster";
				_linkerSettingHolder.getInSpecies1DatasetLinkerAction().setCurrentText(species1InSpeciesClusterDatasetName);
			}
			if (_linkerSettingHolder.getInSpecies2DatasetLinkerAction().getNumberOfOptions() > 0)
			{
				QString species2InSpeciesClusterDatasetName = _species2SelectAction.getCurrentText() + "_" + _neighborhoodAction.getCurrentText() + "_cluster";
				_linkerSettingHolder.getInSpecies2DatasetLinkerAction().setCurrentText(species2InSpeciesClusterDatasetName);
			}
			if (_linkerSettingHolder.getCrossSpecies1DatasetLinkerAction().getNumberOfOptions() > 0)
			{
				QString species1CrossSpeciesClusterDatasetName = _species1SelectAction.getCurrentText() + "_" + _neighborhoodAction.getCurrentText() + "_cross_species_cluster";

				_linkerSettingHolder.getCrossSpecies1DatasetLinkerAction().setCurrentText(species1CrossSpeciesClusterDatasetName);
			}
			if (_linkerSettingHolder.getCrossSpecies2DatasetLinkerAction().getNumberOfOptions() > 0)
			{
				QString species2CrossSpeciesClusterDatasetName = _species2SelectAction.getCurrentText() + "_" + _neighborhoodAction.getCurrentText() + "_cross_species_cluster";
				_linkerSettingHolder.getCrossSpecies2DatasetLinkerAction().setCurrentText(species2CrossSpeciesClusterDatasetName);
			}
			if (_linkerSettingHolder.getSpecies1DEStatsLinkerAction().getNumberOfOptions() > 0)
			{
				const QString child_DE_Statistics_DatasetName = "DE_Statistics";
				hdps::Dataset<Clusters> clusterDataset = _linkerSettingHolder.getCrossSpecies1DatasetLinkerAction().getCurrentDataset();
				QString DatasetGUID = "";
				const auto& childDatasets = clusterDataset->getChildren({ PointType });
				for (qsizetype i = 0; i < childDatasets.size(); ++i)
				{
					if (childDatasets[i]->getGuiName() == child_DE_Statistics_DatasetName)
					{
						DatasetGUID = childDatasets[i].getDatasetGuid();
						_linkerSettingHolder.getSpecies1DEStatsLinkerAction().setCurrentDataset(DatasetGUID);
						break;
					}
				}

				//QString species1DEStatsDatasetName = _species1SelectAction.getCurrentText() + "_" + _neighborhoodAction.getCurrentText() + "_DE_Statistics";

				//_linkerSettingHolder.getSpecies1DEStatsLinkerAction().setCurrentText(species1DEStatsDatasetName);
			}
			if (_linkerSettingHolder.getSpecies2DEStatsLinkerAction().getNumberOfOptions() > 0)
			{
				const QString child_DE_Statistics_DatasetName = "DE_Statistics";
				hdps::Dataset<Clusters> clusterDataset = _linkerSettingHolder.getCrossSpecies2DatasetLinkerAction().getCurrentDataset();
				QString DatasetGUID = "";
				const auto& childDatasets = clusterDataset->getChildren({ PointType });
				for (qsizetype i = 0; i < childDatasets.size(); ++i)
				{
					if (childDatasets[i]->getGuiName() == child_DE_Statistics_DatasetName)
					{
						DatasetGUID = childDatasets[i].getDatasetGuid();
						_linkerSettingHolder.getSpecies2DEStatsLinkerAction().setCurrentDataset(DatasetGUID);
						break;
					}
				}

			////have to add this
//_selectedCrossSpeciesNameList
		//it_types -> L2/3 IT_1
//glia -> Astro_1
//l5et_l56np_l6ct_l6b -> L6 CT_1
//lamp5_sncg_vip -> Lamp5_1
//sst_sst_chodl_pvalb -> Sst Chodl_1
			//"glia","it_types","l5et_l56np_l6ct_l6b","lamp5_sncg_vip","sst_sst_chodl_pvalb"

			//_crossSpecies1HeatMapCellAction
			if (_neighborhoodAction.getCurrentText()=="Non-neuronal cells")
			{
				_linkerSettingHolder.getCrossSpecies1HeatMapCellAction().setSelectedOptions({ "Astro_1" });
				_linkerSettingHolder.getCrossSpecies2HeatMapCellAction().setSelectedOptions({ "Astro_1" });
				_linkerSettingHolder.getSelectedCrossSpeciesNameList().setString("Astro_1");
			}
			else if (_neighborhoodAction.getCurrentText() == "IT-projecting excitatory")
			{
				_linkerSettingHolder.getCrossSpecies1HeatMapCellAction().setSelectedOptions({ "L2/3 IT_1" });
				_linkerSettingHolder.getCrossSpecies2HeatMapCellAction().setSelectedOptions({ "L2/3 IT_1" });
				_linkerSettingHolder.getSelectedCrossSpeciesNameList().setString("L2/3 IT_1");
			}
			else if (_neighborhoodAction.getCurrentText() == "Non-IT-projecting excitatory")
			{
				_linkerSettingHolder.getCrossSpecies1HeatMapCellAction().setSelectedOptions({ "L6 CT_1" });
				_linkerSettingHolder.getCrossSpecies2HeatMapCellAction().setSelectedOptions({ "L6 CT_1" });
				_linkerSettingHolder.getSelectedCrossSpeciesNameList().setString("L6 CT_1");
			}
			else if (_neighborhoodAction.getCurrentText() == "CGE-derived inhibitory")
			{
				_linkerSettingHolder.getCrossSpecies1HeatMapCellAction().setSelectedOptions({ "Lamp5_1" });
				_linkerSettingHolder.getCrossSpecies2HeatMapCellAction().setSelectedOptions({ "Lamp5_1" });
				_linkerSettingHolder.getSelectedCrossSpeciesNameList().setString("Lamp5_1");
			}
			else if (_neighborhoodAction.getCurrentText() == "MGE-derived inhibitory")
			{
				_linkerSettingHolder.getCrossSpecies1HeatMapCellAction().setSelectedOptions({ "Sst Chodl_1" });
				_linkerSettingHolder.getCrossSpecies2HeatMapCellAction().setSelectedOptions({ "Sst Chodl_1" });
				_linkerSettingHolder.getSelectedCrossSpeciesNameList().setString("Sst Chodl_1");
			}

			if (!_stopMethodFlagFromSpecies1 && !_stopMethodFlagFromSpecies2)
			{
				_linkerSettingHolder.getmodifyDifferentialExpressionAutoUpdateAction().trigger();
			}
		}
	};
	const auto updateScatterplotColorControl = [this]() -> void
	{

		if (_linkerSettingHolder.getSpecies1ScatterplotColorLinkerAction().getNumberOfOptions() > 0)
		{
			QString species1EmbeddingColorDatasetName = "";
			if (_scatterplotColorControlAction.getCurrentText() == "cross-species cluster")
			{
				species1EmbeddingColorDatasetName = _species1SelectAction.getCurrentText() + "_" + _neighborhoodAction.getCurrentText() + "_cross_species_cluster" ;
			}
			else if (_scatterplotColorControlAction.getCurrentText() == "in-species cluster")
			{
				species1EmbeddingColorDatasetName = _species1SelectAction.getCurrentText() + "_" + _neighborhoodAction.getCurrentText() + "_cluster";
			}

			else if (_scatterplotColorControlAction.getCurrentText() == "cross-species sub-class")
			{
				species1EmbeddingColorDatasetName = _species1SelectAction.getCurrentText() + "_" + _neighborhoodAction.getCurrentText() + "_cross_species_subclass";
			}
			else if (_scatterplotColorControlAction.getCurrentText() == "in-species subclass")
			{
				species1EmbeddingColorDatasetName = _species1SelectAction.getCurrentText() + "_" + _neighborhoodAction.getCurrentText() + "_subclass" ;
			}
			else if (_scatterplotColorControlAction.getCurrentText() == "donor")
			{
				species1EmbeddingColorDatasetName = _species1SelectAction.getCurrentText() + "_" + _neighborhoodAction.getCurrentText() + "_donor" ;
			}
			else if (_scatterplotColorControlAction.getCurrentText() == "differential expression")
			{
				species1EmbeddingColorDatasetName = "Cluster Differential Expression 1::SelectedIDMeanExpressionsDataset 0";
			}

			_linkerSettingHolder.getSpecies1ScatterplotColorLinkerAction().setCurrentText(species1EmbeddingColorDatasetName);
			//qDebug() << _linkerSettingHolder.getSpecies1ScatterplotColorLinkerAction().getCurrentText();
		}
		if (_linkerSettingHolder.getSpecies2ScatterplotColorLinkerAction().getNumberOfOptions() > 0)
		{
			QString species2EmbeddingColorDatasetName = "";
			if (_scatterplotColorControlAction.getCurrentText() == "cross-species cluster")
			{
				species2EmbeddingColorDatasetName = _species2SelectAction.getCurrentText() + "_" + _neighborhoodAction.getCurrentText() + "_cross_species_cluster" ;
			}
			else if (_scatterplotColorControlAction.getCurrentText() == "in-species cluster")
			{
				species2EmbeddingColorDatasetName = _species2SelectAction.getCurrentText() + "_" + _neighborhoodAction.getCurrentText() + "_cluster";
			}

			else if (_scatterplotColorControlAction.getCurrentText() == "cross-species sub-class")
			{
				species2EmbeddingColorDatasetName = _species2SelectAction.getCurrentText() + "_" + _neighborhoodAction.getCurrentText() + "_cross_species_subclass" ;
			}
			else if (_scatterplotColorControlAction.getCurrentText() == "in-species subclass")
			{
				species2EmbeddingColorDatasetName = _species2SelectAction.getCurrentText() + "_" + _neighborhoodAction.getCurrentText() + "_subclass" ;
			}
			else if (_scatterplotColorControlAction.getCurrentText() == "donor")
			{
				species2EmbeddingColorDatasetName = _species2SelectAction.getCurrentText() + "_" + _neighborhoodAction.getCurrentText() + + "_donor" ;
			}
			else if (_scatterplotColorControlAction.getCurrentText() == "differential expression")
			{
				species2EmbeddingColorDatasetName = "Cluster Differential Expression 1::SelectedIDMeanExpressionsDataset 1";
			}
			_linkerSettingHolder.getSpecies2ScatterplotColorLinkerAction().setCurrentText(species2EmbeddingColorDatasetName);
			//qDebug() << _linkerSettingHolder.getSpecies2ScatterplotColorLinkerAction().getCurrentText();
		}

	};

	const auto updateInSpecies1HeatMapCell = [this]() -> void
	{

	};

	const auto updateInSpecies2HeatMapCell = [this]() -> void
	{

	};

	const auto updateCrossSpecies1HeatMapCell = [this]() -> void
	{

	};

	const auto updateCrossSpecies2HeatMapCell = [this]() -> void
	{

	};

	//const auto updateDistance = [this]() -> void
	//{
	//	if (_species1SelectAction.getCurrentText() != "" && _species2SelectAction.getCurrentText() != "")
	//	{
	//		updateData((_species1SelectAction.getCurrentText()).toStdString(), (_species2SelectAction.getCurrentText()).toStdString(), (_neighborhoodAction.getCurrentText()).toStdString(), /*(_distanceAction.getValue()),*/ (_crossSpeciesFilterAction.getCurrentText()).toStdString());
	//	}
	//};

	const auto updateHistBar = [this]() -> void
	{

		
		if (_histBarAction.isChecked())
		{
			_simianViewerPlugin.getSimianViewerWidget().histChart(QString::fromStdString("T"));
		}
		else
		{
			_simianViewerPlugin.getSimianViewerWidget().histChart(QString::fromStdString("F"));
		}
		
	};

	const auto updateModifyDifferentialExpressionAutoUpdate = [this]() -> void
	{

	};

	const auto updateRemoveLinkingOptionMenuFromUIAction = [this]() -> void
	{
		if (_linkerSettingHolder.getRemoveLinkingOptionMenuFromUIAction().isChecked())
		{
			_linkerSettingHolder.setVisible(false);

		}
		else
		{
			_linkerSettingHolder.setVisible(true);
		}


	};

	const auto updateShowFullHeatmap = [this]() -> void
	{
		if (_visSettingHolder.getFullHeatmapAction().isChecked())
		{
			_simianViewerPlugin.getSimianViewerWidget().showFullHeatmap(QString::fromStdString("T"));
		}
		else
		{
			_simianViewerPlugin.getSimianViewerWidget().showFullHeatmap(QString::fromStdString("F"));
		}


	};
	//const auto updateShowExplorationMode = [this]() -> void
	//{
	//	if (_explorationModeAction.isChecked())
	//	{
	//		_simianViewerPlugin.getWidget()->showExplorationMode(QString::fromStdString("T"));
	//	}
	//	else
	//	{
	//		_simianViewerPlugin.getWidget()->showExplorationMode(QString::fromStdString("F"));
	//	}


	//};


	const auto updateCrossSpecies1DatasetLinker = [this]() -> void
	{

	};

	const auto updateCrossSpecies2DatasetLinker = [this]() -> void
	{

	};

	const auto updateSpecies1ScatterplotColorLinker = [this]() -> void
	{

	};
	
	const auto updateSpecies2ScatterplotColorLinker = [this]() -> void
	{

	};


	const auto updateEmbedding1DatasetLinker = [this]() -> void
	{

	};

	const auto updateEmbedding2DatasetLinker = [this]() -> void
	{

	};
	const auto updateGeneExpressionDatasetVariant = [this]() -> void
	{

	};

	const auto updatecommandAction = [this]() -> void
	{

	};

	const auto updateHarHcondelCountString = [this]() -> void
	{

	};

	const auto updateDEStats1DatasetLinker = [this]() -> void
	{

	};
	const auto updateDEStats2DatasetLinker = [this]() -> void
	{

	};
	const auto updateInSpecies1DatasetLinker = [this]() -> void
	{
		if (_linkerSettingHolder.getInSpecies1DatasetLinkerAction().getCurrentText() != "" && _linkerSettingHolder.getInSpecies2DatasetLinkerAction().getCurrentText() != "")
		{
			sendClusterCountInfoToJS();
				_histBarAction.setChecked(true);
				_linkerSettingHolder.getSpecies1ScatterplotColorLinkerAction().setEnabled(true);
				_linkerSettingHolder.getSpecies2ScatterplotColorLinkerAction().setEnabled(true);
				_scatterplotColorControlAction.setEnabled(true);
		}
		else
		{
			_histBarAction.setChecked(false);
			_linkerSettingHolder.getSpecies1ScatterplotColorLinkerAction().setEnabled(false);
			_linkerSettingHolder.getSpecies2ScatterplotColorLinkerAction().setEnabled(false);
			_scatterplotColorControlAction.setEnabled(false);

		}
	};

	const auto updateInSpecies2DatasetLinker = [this]() -> void
	{
		if (_linkerSettingHolder.getInSpecies1DatasetLinkerAction().getCurrentText() != "" && _linkerSettingHolder.getInSpecies2DatasetLinkerAction().getCurrentText() != "")
		{
			sendClusterCountInfoToJS();

				_histBarAction.setChecked(true);
				_linkerSettingHolder.getSpecies1ScatterplotColorLinkerAction().setEnabled(true);
				_linkerSettingHolder.getSpecies2ScatterplotColorLinkerAction().setEnabled(true);
				_scatterplotColorControlAction.setEnabled(true);

		}
		else
		{
			_histBarAction.setChecked(false);
			_linkerSettingHolder.getSpecies1ScatterplotColorLinkerAction().setEnabled(false);
			_linkerSettingHolder.getSpecies2ScatterplotColorLinkerAction().setEnabled(false);
			_scatterplotColorControlAction.setEnabled(false);

		}
	};



	// Generate the cluster colors in the model
	//const auto generateScreenshot = [this]() -> void {
	//	
	//		
	//	QFileDialog saveFileDialog;

	//	saveFileDialog.setAcceptMode(QFileDialog::AcceptSave);
	//	saveFileDialog.setDirectory(QDir::home().absolutePath());

	//	saveFileDialog.selectFile("SimianViewerScreenshot.pdf");
	//	saveFileDialog.setNameFilter(tr("PDF Files (*.pdf)"));

	//	QString fileName;
	//	if (saveFileDialog.exec())
	//	{
	//		fileName = saveFileDialog.selectedFiles().first();



	//		QPageLayout pl;
	//		QPageSize ps;
	//		//qDebug() << "height" << _simianViewerPlugin.getSimianViewerWidget().height();
	//		
	//		int width = _simianViewerPlugin.getSimianViewerWidget().width();
	//		int height = _simianViewerPlugin.getSimianViewerWidget().height();
	//		int reducedWidth =  static_cast<double>(width) / 100 * 75;
	//		int reducedHeight = static_cast<double>(height) / 100 * 78;
	//		//qDebug() << "width" << width;
	//		//qDebug() << "reduced width" << reducedWidth;
	//		//qDebug() << "height" << height;
	//		//qDebug() << "reduced height" << reducedHeight;
	//		ps = QPageSize(QSizeF(reducedWidth, reducedHeight), QPageSize::Point, QString(), QPageSize::ExactMatch);
	//		pl.setPageSize(ps);
	//		pl.setOrientation(QPageLayout::Portrait);


	//		_simianViewerPlugin.getSimianViewerWidget().getPage()->printToPdf(fileName, pl);

	//	}
	//		//..getSimianViewerWidget().getPage()->printToPdf(fileName, pl);

	//};

	const auto updateSelectedCrossspeciescluster = [this]() -> void
	{
		//qDebug() << "updateSelectedCrossspeciescluster : triggered "<< _linkerSettingHolder.getSelectedCrossspeciescluster().getString();
		_simianViewerPlugin.getSimianViewerWidget().borderSelectedCrossspeciesCluster(_linkerSettingHolder.getSelectedCrossspeciescluster().getString());

		if (_linkerSettingHolder.getSelectedCrossspeciescluster().getString() == "")
			
		{
			//if (_crossSpeciesFilterAction.getCurrentText() == "cross-species clusters")
			//{
				if (_linkerSettingHolder.getCrossSpecies1DatasetLinkerAction().getCurrentText() != "")
				{
					auto dataset1 = _linkerSettingHolder.getCrossSpecies1DatasetLinkerAction().getCurrentDataset();
					const auto candidateDataset1 = _core->requestDataset<Clusters>(dataset1.getDatasetGuid());
					std::vector<std::uint32_t> selectedIndices1;



					candidateDataset1->getParent()->setSelectionIndices(selectedIndices1);


					events().notifyDatasetSelectionChanged(candidateDataset1->getParent());

				}
				if (_linkerSettingHolder.getCrossSpecies2DatasetLinkerAction().getCurrentText() != "")
				{
					auto dataset2 = _linkerSettingHolder.getCrossSpecies2DatasetLinkerAction().getCurrentDataset();
					const auto candidateDataset2 = _core->requestDataset<Clusters>(dataset2.getDatasetGuid());
					std::vector<std::uint32_t> selectedIndices2;


					candidateDataset2->getParent()->setSelectionIndices(selectedIndices2);
					events().notifyDatasetSelectionChanged(candidateDataset2->getParent());
				}
			//}
			//else
			//{
			//	if (_linkerSettingHolder.getInSpecies1DatasetLinkerAction().getCurrentText() != "")
			//	{
			//		auto dataset1 = _linkerSettingHolder.getInSpecies1DatasetLinkerAction().getCurrentDataset();
			//		const auto candidateDataset1 = _core->requestDataset<Clusters>(dataset1.getDatasetGuid());
			//		std::vector<std::uint32_t> selectedIndices1;



			//		candidateDataset1->getParent()->setSelectionIndices(selectedIndices1);


			//		events().notifyDatasetSelectionChanged(candidateDataset1->getParent());

			//	}
			//	if (_linkerSettingHolder.getInSpecies2DatasetLinkerAction().getCurrentText() != "")
			//	{
			//		auto dataset2 = _linkerSettingHolder.getInSpecies2DatasetLinkerAction().getCurrentDataset();
			//		const auto candidateDataset2 = _core->requestDataset<Clusters>(dataset2.getDatasetGuid());
			//		std::vector<std::uint32_t> selectedIndices2;


			//		candidateDataset2->getParent()->setSelectionIndices(selectedIndices2);
			//		events().notifyDatasetSelectionChanged(candidateDataset2->getParent());
			//	}
			//}
		}
		else
		{
			_linkerSettingHolder.getCrossSpecies1HeatMapCellAction().setSelectedOptions({ _linkerSettingHolder.getSelectedCrossspeciescluster().getString() });

			_linkerSettingHolder.getCrossSpecies2HeatMapCellAction().setSelectedOptions({ _linkerSettingHolder.getSelectedCrossspeciescluster().getString() });

			_linkerSettingHolder.getSelectedCrossSpeciesNameList().setString(_linkerSettingHolder.getSelectedCrossspeciescluster().getString());

			//if (_crossSpeciesFilterAction.getCurrentText() == "cross-species clusters")
			//{
				if (_linkerSettingHolder.getCrossSpecies1DatasetLinkerAction().getCurrentText() != "")
				{
					auto dataset1 = _linkerSettingHolder.getCrossSpecies1DatasetLinkerAction().getCurrentDataset();
					const auto candidateDataset1 = _core->requestDataset<Clusters>(dataset1.getDatasetGuid());
					std::vector<std::uint32_t> selectedIndices1;

					for (const auto& cluster : candidateDataset1->getClusters())
					{
						if (cluster.getName() == _linkerSettingHolder.getSelectedCrossspeciescluster().getString())
						{
							for (const auto& index : cluster.getIndices())
							{
								selectedIndices1.push_back(index);
							}
						}

					}

					candidateDataset1->getParent()->setSelectionIndices(selectedIndices1);


					events().notifyDatasetSelectionChanged(candidateDataset1->getParent());

				}
				if (_linkerSettingHolder.getCrossSpecies2DatasetLinkerAction().getCurrentText() != "")
				{
					auto dataset2 = _linkerSettingHolder.getCrossSpecies2DatasetLinkerAction().getCurrentDataset();
					const auto candidateDataset2 = _core->requestDataset<Clusters>(dataset2.getDatasetGuid());
					std::vector<std::uint32_t> selectedIndices2;
					for (const auto& cluster : candidateDataset2->getClusters())
					{
						if (cluster.getName() == _linkerSettingHolder.getSelectedCrossspeciescluster().getString())
						{
							for (const auto& index : cluster.getIndices())
							{
								selectedIndices2.push_back(index);
							}
						}

					}

					candidateDataset2->getParent()->setSelectionIndices(selectedIndices2);
					events().notifyDatasetSelectionChanged(candidateDataset2->getParent());
				}
			//}
			//else
			//{
			//	if (_linkerSettingHolder.getInSpecies1DatasetLinkerAction().getCurrentText() != "")
			//	{
			//		auto dataset1 = _linkerSettingHolder.getInSpecies1DatasetLinkerAction().getCurrentDataset();
			//		const auto candidateDataset1 = _core->requestDataset<Clusters>(dataset1.getDatasetGuid());
			//		std::vector<std::uint32_t> selectedIndices1;

			//		for (const auto& cluster : candidateDataset1->getClusters())
			//		{
			//			if (cluster.getName() == _linkerSettingHolder.getSelectedCrossspeciescluster().getString())
			//			{
			//				for (const auto& index : cluster.getIndices())
			//				{
			//					selectedIndices1.push_back(index);
			//				}
			//			}

			//		}

			//		candidateDataset1->getParent()->setSelectionIndices(selectedIndices1);


			//		events().notifyDatasetSelectionChanged(candidateDataset1->getParent());

			//	}
			//	if (_linkerSettingHolder.getInSpecies2DatasetLinkerAction().getCurrentText() != "")
			//	{
			//		auto dataset2 = _linkerSettingHolder.getInSpecies2DatasetLinkerAction().getCurrentDataset();
			//		const auto candidateDataset2 = _core->requestDataset<Clusters>(dataset2.getDatasetGuid());
			//		std::vector<std::uint32_t> selectedIndices2;
			//		for (const auto& cluster : candidateDataset2->getClusters())
			//		{
			//			if (cluster.getName() == _linkerSettingHolder.getSelectedCrossspeciescluster().getString())
			//			{
			//				for (const auto& index : cluster.getIndices())
			//				{
			//					selectedIndices2.push_back(index);
			//				}
			//			}

			//		}

			//		candidateDataset2->getParent()->setSelectionIndices(selectedIndices2);
			//		events().notifyDatasetSelectionChanged(candidateDataset2->getParent());
			//	}
			//}
		}
		if (!_stopMethodFlagFromSpecies1 && !_stopMethodFlagFromSpecies2)
		{
			_linkerSettingHolder.getmodifyDifferentialExpressionAutoUpdateAction().trigger();
		}
	};

	connect(&_linkerSettingHolder.getSelectedCrossspeciescluster(), &StringAction::stringChanged, this, updateSelectedCrossspeciescluster);

	//connect(&_crossSpeciesFilterAction, &OptionAction::currentIndexChanged, [this, updateCrossSpeciesFilter](const std::int32_t& currentIndex) {
	//	updateCrossSpeciesFilter();
	//	});

	//connect(&_screenshotAction, &TriggerAction::triggered, this, generateScreenshot);
	//connect(&_multiSelectClusterFilterAction, &OptionsAction::selectedOptionsChanged, [this, multiSelectClusterFilter](const QStringList& currentIndex) {
	//	multiSelectClusterFilter();
	//	});

	//

	const auto updatePluginvisibility = [this]() -> void
	{
		if (_visSettingHolder.getPluginVisibilityAction().getCurrentText()== "pairwise")
		{
			_linkerSettingHolder.getPopPyramidPluginVisibility().setChecked(true); 
			_linkerSettingHolder.getParallelBarPluginVisibility().setChecked(false);
		}
		else if (_visSettingHolder.getPluginVisibilityAction().getCurrentText() == "multi")
		{
			_linkerSettingHolder.getPopPyramidPluginVisibility().setChecked(false);
			_linkerSettingHolder.getParallelBarPluginVisibility().setChecked(true);
		}
	};
	const auto updateParallelBarPluginVisibility = [this]() -> void
	{

	};
	const auto updatePopPyramidPluginVisibility = [this]() -> void
	{

	};
	connect(&_visSettingHolder.getPluginVisibilityAction(), &OptionAction::currentTextChanged, this, updatePluginvisibility);
	connect(&_linkerSettingHolder.getParallelBarPluginVisibility(), &ToggleAction::toggled, this, updateParallelBarPluginVisibility);
	connect(&_linkerSettingHolder.getPopPyramidPluginVisibility(), &ToggleAction::toggled, this, updatePopPyramidPluginVisibility);


	connect(&_linkerSettingHolder.getSelectedCrossSpeciesNameList(), &StringAction::stringChanged, this, updateSelectedCrossSpeciesNameList);
	connect(&_linkerSettingHolder.getSelectedCrossSpeciesNameList(), &StringAction::stringChanged, this, updateSelectedCrossSpeciesNameList);
	connect(&_visSettingHolder.getColorMapAction(), &ColorMapAction::imageChanged, this, colormapFilter);

	//connect(&_backgroundColoringAction, &ColorAction::colorChanged, this, backgroundColoringFilter);

	connect(&_visSettingHolder.getColorMapAction().getSettingsAction().getHorizontalAxisAction().getRangeAction(), &DecimalRangeAction::rangeChanged, this, updateColorMapRange);

	connect(&_species1SelectAction, &OptionAction::currentIndexChanged, [this, updateSpecies1](const std::int32_t& currentIndex) {
		updateSpecies1();

		});
	connect(&_species2SelectAction, &OptionAction::currentIndexChanged, [this, updateSpecies2](const std::int32_t& currentIndex) {
		updateSpecies2();
		});
	connect(&_neighborhoodAction, &OptionAction::currentIndexChanged, this, [this, updateNeighborhood](const std::int32_t& currentIndex)
		{
			updateNeighborhood();
		});
	connect(&_linkerSettingHolder.getGeneExpressionDatasetVariant(), &VariantAction::variantChanged, this, updateGeneExpressionDatasetVariant);	
	connect(&_linkerSettingHolder.getCommandAction(), &VariantAction::variantChanged, this, updatecommandAction);

	connect(&_linkerSettingHolder.getHarHcondelCountString(), &StringAction::stringChanged, this, updateHarHcondelCountString);

	connect(&_scatterplotColorControlAction, &OptionAction::currentIndexChanged, this, [this, updateScatterplotColorControl](const std::int32_t& currentIndex)
		{
			updateScatterplotColorControl();
		});
	connect(&_linkerSettingHolder.getInSpecies1HeatMapCellAction(), &OptionAction::currentIndexChanged, this, [this, updateInSpecies1HeatMapCell](const std::int32_t& currentIndex)
		{
			updateInSpecies1HeatMapCell();
		});

	connect(&_linkerSettingHolder.getInSpecies2HeatMapCellAction(), &OptionAction::currentIndexChanged, this, [this, updateInSpecies2HeatMapCell](const std::int32_t& currentIndex)
		{
			updateInSpecies2HeatMapCell();
		});

	connect(&_linkerSettingHolder.getCrossSpecies2HeatMapCellAction(), &OptionsAction::selectedOptionsChanged, this, updateCrossSpecies2HeatMapCell);
	connect(&_linkerSettingHolder.getCrossSpecies1HeatMapCellAction(), &OptionsAction::selectedOptionsChanged, this, updateCrossSpecies1HeatMapCell);


	//connect(&_distanceAction, &IntegralAction::valueChanged, this, [this, updateDistance](const std::int32_t& value)
	//	{
	//		updateDistance();
	//	});
	connect(&_histBarAction, &ToggleAction::toggled, this, [this, updateHistBar](const bool& toggled)
		{
			updateHistBar();
		});
	connect(&_linkerSettingHolder.getmodifyDifferentialExpressionAutoUpdateAction(), &TriggerAction::triggered, this, updateModifyDifferentialExpressionAutoUpdate);

	connect(&_linkerSettingHolder.getRemoveLinkingOptionMenuFromUIAction(), &ToggleAction::toggled, this, [this, updateRemoveLinkingOptionMenuFromUIAction](const bool& toggled)
		{
			updateRemoveLinkingOptionMenuFromUIAction();
		});
	connect(&_visSettingHolder.getFullHeatmapAction(), &ToggleAction::toggled, this, [this, updateShowFullHeatmap](const bool& toggled)
		{
			updateShowFullHeatmap();
		});

	//connect(&_explorationModeAction, &ToggleAction::toggled, this, [this, updateShowExplorationMode](const bool& toggled)
	//	{
	//		updateShowExplorationMode();
	//	});
	connect(&_linkerSettingHolder.getCrossSpecies1DatasetLinkerAction(), &OptionAction::currentIndexChanged, this, [this, updateCrossSpecies1DatasetLinker](const std::int32_t& value) {
		updateCrossSpecies1DatasetLinker();
		});
	connect(&_linkerSettingHolder.getCrossSpecies2DatasetLinkerAction(), &OptionAction::currentIndexChanged, this, [this, updateCrossSpecies2DatasetLinker](const std::int32_t& value) {
		updateCrossSpecies2DatasetLinker();
		});


	connect(&_linkerSettingHolder.getSpecies1ScatterplotColorLinkerAction(), &OptionAction::currentIndexChanged, this, [this, updateSpecies1ScatterplotColorLinker](const std::int32_t& value) {
		updateSpecies1ScatterplotColorLinker();
		});
	connect(&_linkerSettingHolder.getSpecies2ScatterplotColorLinkerAction(), &OptionAction::currentIndexChanged, this, [this, updateSpecies2ScatterplotColorLinker](const std::int32_t& value) {
		updateSpecies2ScatterplotColorLinker();
		});

	connect(&_linkerSettingHolder.getSpeciesEmbedding1LinkerAction(), &OptionAction::currentIndexChanged, this, [this, updateEmbedding1DatasetLinker](const std::int32_t& value) {
		updateEmbedding1DatasetLinker();
		});
	connect(&_linkerSettingHolder.getSpeciesEmbedding2LinkerAction(), &OptionAction::currentIndexChanged, this, [this, updateEmbedding2DatasetLinker](const std::int32_t& value) {
		updateEmbedding2DatasetLinker();
		});
	connect(&_linkerSettingHolder.getSpecies1DEStatsLinkerAction(), &OptionAction::currentIndexChanged, this, [this, updateDEStats1DatasetLinker](const std::int32_t& value) {
		updateDEStats1DatasetLinker();
		});
	connect(&_linkerSettingHolder.getSpecies2DEStatsLinkerAction(), &OptionAction::currentIndexChanged, this, [this, updateDEStats2DatasetLinker](const std::int32_t& value) {
		updateDEStats2DatasetLinker();
		});
	connect(&_linkerSettingHolder.getInSpecies1DatasetLinkerAction(), &OptionAction::currentIndexChanged, this, [this, updateInSpecies1DatasetLinker](const std::int32_t& value) {
		updateInSpecies1DatasetLinker();
		});
	connect(&_linkerSettingHolder.getInSpecies2DatasetLinkerAction(), &OptionAction::currentIndexChanged, this, [this, updateInSpecies2DatasetLinker](const std::int32_t& value) {
		updateInSpecies2DatasetLinker();
		});
	updateDatasetPickerAction();

}

SimianOptionsAction::Widget::Widget(QWidget* parent, SimianOptionsAction* SimianOptionsAction) :
	WidgetActionWidget(parent, SimianOptionsAction, State::Standard)
{

}

void SimianOptionsAction::sendClusterCountInfoToJS()
{
	auto dataset1 = _linkerSettingHolder.getInSpecies1DatasetLinkerAction().getCurrentDataset();
	auto dataset2 = _linkerSettingHolder.getInSpecies2DatasetLinkerAction().getCurrentDataset();
	const auto candidateDataset1 = _core->requestDataset<Clusters>(dataset1.getDatasetGuid());
	const auto candidateDataset2 = _core->requestDataset<Clusters>(dataset2.getDatasetGuid());
	std::string jsonSend = "";
	for (const auto& cluster : candidateDataset1->getClusters())
	{

		jsonSend = jsonSend + cluster.getName().toStdString();
		jsonSend = jsonSend + "*|*";
		jsonSend = jsonSend + std::to_string(cluster.getNumberOfIndices());
		jsonSend = jsonSend + "*||*";
	}
	jsonSend = jsonSend + "*|||*";
	for (const auto& cluster : candidateDataset2->getClusters())
	{

		jsonSend = jsonSend + cluster.getName().toStdString();
		jsonSend = jsonSend + "*|*";
		jsonSend = jsonSend + std::to_string(cluster.getNumberOfIndices());
		jsonSend = jsonSend + "*||*";
	}


	_simianViewerPlugin.getSimianViewerWidget().inspeciesClusterCounts(QString::fromStdString(jsonSend));

}

void SimianOptionsAction::onDataEvent(hdps::DataEvent* dataEvent)
{
	//if (dataEvent->getType() == hdps::EventType::DataAdded)
	//{
	//	updateDatasetPickerAction();
	//}
	//if (dataEvent->getType() == hdps::EventType::DataRemoved)
	//{
	//	updateDatasetPickerAction();
	//}
	//if (dataEvent->getType() == hdps::EventType::DataChildAdded)
	//{
	//	updateDatasetPickerAction();
	//}
	//if (dataEvent->getType() == hdps::EventType::DataChildRemoved)
	//{
	//	updateDatasetPickerAction();
	//}
	//if (dataEvent->getType() == hdps::EventType::DataChanged)
	//{
	//	updateDatasetPickerAction();
	//}
	//if (dataEvent->getType() == hdps::EventType::DataGuiNameChanged)
	//{
	//	updateDatasetPickerAction();
	//}
}

void SimianOptionsAction::updateData(std::string Species1, std::string Species2, std::string neighborhood/*, int distance, std::string CrossSpeciesFilter*/)
{
	_isStarted = false;
	std::vector<std::vector<std::string>>    filteredVisData;


	//if (CrossSpeciesFilter == "cross-species clusters")
	//{
		for (int i = 0; i < _simianData.size(); i++)

		{
			if (_simianData[i][7] == _simianData[i][8] && _simianData[i][1] == Species1 && _simianData[i][3] == Species2 && _simianData[i][6] == neighborhood /*&& stoi(_simianData[i][5]) < distance*/)
			{
				std::vector<std::string> temp;
				for (int j = 0; j < _simianData[i].size(); j++)
				{
					temp.push_back(_simianData[i][j]);
				}
				filteredVisData.push_back(temp);
			}
		}
	//}
	//else
	//{
	//	for (int i = 0; i < _simianData.size(); i++)

	//	{
	//		if (_simianData[i][1] == Species1 && _simianData[i][3] == Species2 && _simianData[i][6] == neighborhood /*&& stoi(_simianData[i][5]) < distance*/)
	//		{
	//			std::vector<std::string> temp;
	//			for (int j = 0; j < _simianData[i].size(); j++)
	//			{
	//				temp.push_back(_simianData[i][j]);
	//			}
	//			filteredVisData.push_back(temp);
	//		}
	//	}
	//}

	//updateMultiSelectionDropdown(filteredVisData);

	if(filteredVisData.size()>0)
	{

		QString _jsonObject;
		_jsonObject += "[";

		QStringList columnNames = { "RowNumber", "species_1", "cluster_1", "species_2", "cluster_2", "dist", "neighborhood", "cross_species_cluster1_species_1", "cross_species_cluster2_species_2", "sortColumn","subclass_1","class_1","subclass_2","class_2" };

		for (int i = 0; i < filteredVisData.size(); i++)
		{
			_jsonObject += "{";

			for (int j = 0; j < filteredVisData[i].size(); j++)
			{
				QString columnName = columnNames[j];
				_jsonObject += QString("\"%1\":\"%2\",").arg(columnName, filteredVisData[i][j].c_str());
			}

			_jsonObject.chop(1);

			_jsonObject += "},";
		}
		_jsonObject.chop(1);
		_jsonObject += "]";
		_simianViewerPlugin.getSimianViewerWidget().setData(_jsonObject.toStdString());

		auto& colorMapRangeAction = _visSettingHolder.getColorMapAction().getSettingsAction().getHorizontalAxisAction().getRangeAction();
		float colorMapRangeMin = 1200.0;
		float colorMapRangeMax = 0.0;
		for (int i = 0; i < filteredVisData.size(); i++)
		{
			const float temp = std::stof(filteredVisData[i][5]);
			if (temp < colorMapRangeMin)
			{
				colorMapRangeMin = temp;
			}
			if (temp > colorMapRangeMax)
			{
				colorMapRangeMax = temp;
			}
		}
		// Initialize the color map range action with the color map range from the scatter plot 
		colorMapRangeAction.initialize(colorMapRangeMin, colorMapRangeMax, colorMapRangeMin, colorMapRangeMax, colorMapRangeMin, colorMapRangeMax);

		if (!_isStarted)
		{
			_isStarted = true;
		}

		QStringList inSpecies1List; QStringList inSpecies2List; QStringList crossSpecies1List; QStringList crossSpecies2List;
		for (int i = 0; i < filteredVisData.size(); i++)
		{
			if (!QStringlistContainsQString(inSpecies1List, QString::fromStdString(filteredVisData[i][2])))
			{
				inSpecies1List.append(QString::fromStdString(filteredVisData[i][2]));
			}
			if (!QStringlistContainsQString(inSpecies2List, QString::fromStdString(filteredVisData[i][4])))
			{
				inSpecies2List.append(QString::fromStdString(filteredVisData[i][4]));
			}
			if (!QStringlistContainsQString(crossSpecies1List, QString::fromStdString(filteredVisData[i][7])))
			{
				crossSpecies1List.append(QString::fromStdString(filteredVisData[i][7]));
			}
			if (!QStringlistContainsQString(crossSpecies2List, QString::fromStdString(filteredVisData[i][8])))
			{
				crossSpecies2List.append(QString::fromStdString(filteredVisData[i][8]));
			}
		}

	}

	//else
	//{
//		_simianViewerPlugin.getSimianViewerWidget().resetView("Reset");
//	}
	//_linkerSettingHolder.getCrossSpecies2HeatMapCellAction().initialize(crossSpecies2List, "", "");
	//_linkerSettingHolder.getCrossSpecies1HeatMapCellAction().initialize(crossSpecies1List, "", "");

	//_linkerSettingHolder.getInSpecies2HeatMapCellAction().initialize(inSpecies2List, "", "");
	//_linkerSettingHolder.getInSpecies1HeatMapCellAction().initialize(inSpecies1List, "", "");




}



void SimianOptionsAction::updateDatasetPickerAction()
{
	auto colorDatasets = _core->requestAllDataSets();
	_linkerSettingHolder.getSpecies1ScatterplotColorLinkerAction().setDatasets(colorDatasets);
	_linkerSettingHolder.getSpecies1ScatterplotColorLinkerAction().setPlaceHolderString("Species1 scatterplot color linker");
	_linkerSettingHolder.getSpecies2ScatterplotColorLinkerAction().setDatasets(colorDatasets);
	_linkerSettingHolder.getSpecies2ScatterplotColorLinkerAction().setPlaceHolderString("Species2 scatterplot color linker");


	auto datasets = _core->requestAllDataSets(QVector<hdps::DataType> {ClusterType});
	auto filteredCrossSpeciesDatasets = datasets;
	auto filteredInSpeciesDatasets = datasets;
	for (auto dataset : datasets)
	{
		std::string str1 = dataset->getGuiName().toStdString();
		std::string str2 = "cluster";
		if (strstr(str1.c_str(), str2.c_str()))
		{
		}
		else {
			filteredCrossSpeciesDatasets.removeOne(dataset);
			filteredInSpeciesDatasets.removeOne(dataset);
		}
	}

	datasets = filteredCrossSpeciesDatasets;
	for (auto dataset : datasets)
	{
		std::string str3 = dataset->getGuiName().toStdString();
		std::string str4 = "cross";

		if (strstr(str3.c_str(), str4.c_str()))
		{
			filteredInSpeciesDatasets.removeOne(dataset);
		}
		else
		{
			filteredCrossSpeciesDatasets.removeOne(dataset);
		}
	}

	_linkerSettingHolder.getCrossSpecies1DatasetLinkerAction().setDatasets(filteredCrossSpeciesDatasets);
	_linkerSettingHolder.getCrossSpecies1DatasetLinkerAction().setPlaceHolderString("Species1 cross-species clusters");
	_linkerSettingHolder.getCrossSpecies2DatasetLinkerAction().setDatasets(filteredCrossSpeciesDatasets);
	_linkerSettingHolder.getCrossSpecies2DatasetLinkerAction().setPlaceHolderString("Species2 cross-species clusters");
	_linkerSettingHolder.getInSpecies1DatasetLinkerAction().setDatasets(filteredInSpeciesDatasets);
	_linkerSettingHolder.getInSpecies1DatasetLinkerAction().setPlaceHolderString("Species1 in-species clusters");
	_linkerSettingHolder.getInSpecies2DatasetLinkerAction().setDatasets(filteredInSpeciesDatasets);
	_linkerSettingHolder.getInSpecies2DatasetLinkerAction().setPlaceHolderString("Species2 in-species clusters");

	auto embeddings = _core->requestAllDataSets(QVector<hdps::DataType> {PointType});
	auto filteredEmbeddingDatasets = embeddings;
	for (auto embedding : embeddings)
	{
		std::string str1 = embedding->getGuiName().toStdString();
		/*qDebug() << QString::fromStdString(str1);*/
		std::string str2 = "embedding";
		if (strstr(str1.c_str(), str2.c_str()))
		{
		}
		else {
			filteredEmbeddingDatasets.removeOne(embedding);
		}
	}

	_linkerSettingHolder.getSpeciesEmbedding1LinkerAction().setDatasets(filteredEmbeddingDatasets);
	_linkerSettingHolder.getSpeciesEmbedding1LinkerAction().setPlaceHolderString("Embedding1 dataset");
	_linkerSettingHolder.getSpeciesEmbedding2LinkerAction().setDatasets(filteredEmbeddingDatasets);
	_linkerSettingHolder.getSpeciesEmbedding2LinkerAction().setPlaceHolderString("Embedding2 dataset");
	
	auto deStats = _core->requestAllDataSets(QVector<hdps::DataType> {PointType});
	auto filteredDEStatsDatasets = deStats;
	for (auto deStat : deStats)
	{
		std::string str1 = deStat->getGuiName().toStdString();
		std::string str2 = "DE_Statistics";
		if (strstr(str1.c_str(), str2.c_str()))
		{
		}
		else {
			filteredDEStatsDatasets.removeOne(deStat);
		}
	}

	_linkerSettingHolder.getSpecies1DEStatsLinkerAction().setDatasets(filteredDEStatsDatasets);
	_linkerSettingHolder.getSpecies1DEStatsLinkerAction().setPlaceHolderString("DEStats dataset1");
	_linkerSettingHolder.getSpecies2DEStatsLinkerAction().setDatasets(filteredDEStatsDatasets);
	_linkerSettingHolder.getSpecies2DEStatsLinkerAction().setPlaceHolderString("DEStats dataset2");

}



inline SimianOptionsAction::OptionsHolder::OptionsHolder(SimianOptionsAction& simianOptionsAction) :
	HorizontalGroupAction(&simianOptionsAction, "Toolbar"),
	_simianOptionsAction(simianOptionsAction)
{
	addAction(&_simianOptionsAction._species1SelectAction);
	addAction(&_simianOptionsAction._species2SelectAction);
	addAction(&_simianOptionsAction._neighborhoodAction);
	addAction(&_simianOptionsAction._scatterplotColorControlAction);
	addAction(&_simianOptionsAction._histBarAction);
	addAction(&_simianOptionsAction._visSettingHolder);
}

//void SimianOptionsAction::updateMultiSelectionDropdown(std::vector<std::vector<std::string>>& filteredVisData)
//{
//	std::vector<std::string> store;
//	for (int i = 0; i < filteredVisData.size(); i++)
//
//	{
//		store.push_back(filteredVisData[i][7]);
//		store.push_back(filteredVisData[i][8]);
//	}
//	sort(store.begin(), store.end());
//	store.erase(unique(store.begin(), store.end()), store.end());
//	QStringList finalClusters{};
//	for (int i = 0; i < store.size(); i++)
//	{
//		finalClusters.append(QString::fromUtf8((store.at(i)).c_str()));
//	}
//
//	_multiSelectClusterFilterAction.initialize(finalClusters);
//	_multiSelectClusterFilterAction.setSelectedOptions(finalClusters);
//
//
//}



inline SimianOptionsAction::VisSettingHolder::VisSettingHolder(SimianOptionsAction& simianOptionsAction) :
	GroupAction(&simianOptionsAction, "Setting Options"),
	_simianOptionsAction(simianOptionsAction),
	_fullHeatMapAction(this, "Full distancemap"),
	_colorMapAction(this, "Color map"),
	_pluginVisibility(this, "Expression type")
{
	setText("Setting Options");
	setIcon(Application::getIconFont("FontAwesome").getIcon("cog"));
	setPopupSizeHint(QSize(350, 0));
}

inline SimianOptionsAction::LinkerSettingHolder::LinkerSettingHolder(SimianOptionsAction& simianOptionsAction) :
	GroupAction(&simianOptionsAction, "Linking Options"),
	_simianOptionsAction(simianOptionsAction),
	_crossSpecies1DatasetLinkerAction(this, "Cross-species cluster dataset1"),
	_crossSpecies2DatasetLinkerAction(this, "Cross-species  cluster dataset2"),
	_species1ScatterplotColorLinkerAction(this, "Scatterplot color linker species1"),
	_species2ScatterplotColorLinkerAction(this, "Scatterplot color linker species2"),
	_speciesEmbedding1LinkerAction(this, "Embedding dataset1"),
	_speciesEmbedding2LinkerAction(this, "Embedding dataset2"),
	_species1DEStatsLinkerAction(this, "DEStats dataset1"),
	_species2DEStatsLinkerAction(this, "DEStats dataset2"),
	_inSpecies1DatasetLinkerAction(this, "In-species  cluster dataset1"),
	_inSpecies2DatasetLinkerAction(this, "In-species  cluster dataset2"),
	_inSpecies1HeatMapCellAction(this, "Link in-species1 heatmap cell"),
	_inSpecies2HeatMapCellAction(this, "Link in-species2 heatmap cell"),
	_crossSpecies1HeatMapCellAction(this, "Link cross-species1 heatmap cell"),
	_crossSpecies2HeatMapCellAction(this, "Link cross-species2 heatmap cell"),
	_modifyDifferentialExpressionAutoUpdate(this, "Automatic Update Switch"),
	_removeLinkingOptionMenuFromUIAction(this, "Remove widget"),
	_species1Name(this, "Species1Name"),
	_species2Name(this, "Species2Name"),
	_selectedCrossspeciescluster(this, "Selected CrossSpecies Cluster"),
	_geneExpressionDatasetVariant(this, "Gene Expression Variant"),
	_commandAction(this, "Command Action Variant"),
	_selectedCrossSpeciesNameList(this, "Selected Cross Species Name List"),
	_harHcondelCountString(this, "Har-Hcondel Count String"),
	_popPyramidPluginVisibility(this,"PopPyramidPluginVisibility"),
	_parallelBarPluginVisibility(this, "ParallelBarPluginVisibility")
{
	setText("Linking Options");
	setIcon(Application::getIconFont("FontAwesome").getIcon("link"));
	setPopupSizeHint(QSize(350, 0));

	//connect(&_popPyramidPluginVisibility, &ToggleAction::toggled, this, [](bool toggled) -> void {
	//	qDebug() << "_popPyramidPluginVisibility" << "toggled changed to" << toggled;
	//	});
}


//void SimianOptionsAction::filterMultiSelect()
//{
//	QStringList clusterValues = _multiSelectClusterFilterAction.getSelectedOptions();
//
//	std::vector<std::vector<std::string>>    filteredVisData;
//	std::vector<std::vector<std::string>>    clusterfilteredVisData;
//
//
//
//	if ((_crossSpeciesFilterAction.getCurrentText()).toStdString() == "cross-species clusters")
//	{
//		for (int i = 0; i < _simianData.size(); i++)
//
//		{
//			if (_simianData[i][7] == _simianData[i][8] && _simianData[i][1] == (_species1SelectAction.getCurrentText()).toStdString() && _simianData[i][3] == (_species2SelectAction.getCurrentText()).toStdString() && _simianData[i][6] == (_neighborhoodAction.getCurrentText()).toStdString() && stoi(_simianData[i][5]) < (_distanceAction.getValue()))
//			{
//				std::vector<std::string> temp;
//				for (int j = 0; j < _simianData[i].size(); j++)
//				{
//					temp.push_back(_simianData[i][j]);
//				}
//				filteredVisData.push_back(temp);
//			}
//		}
//	}
//	else
//	{
//		for (int i = 0; i < _simianData.size(); i++)
//
//		{
//			if (_simianData[i][1] == (_species1SelectAction.getCurrentText()).toStdString() && _simianData[i][3] == (_species2SelectAction.getCurrentText()).toStdString() && _simianData[i][6] == (_neighborhoodAction.getCurrentText()).toStdString() && stoi(_simianData[i][5]) < (_distanceAction.getValue()))
//			{
//				std::vector<std::string> temp;
//				for (int j = 0; j < _simianData[i].size(); j++)
//				{
//					temp.push_back(_simianData[i][j]);
//				}
//				filteredVisData.push_back(temp);
//			}
//		}
//	}
//
//	for (int i = 0; i < filteredVisData.size(); i++)
//	{
//		for (int j = 0; j < clusterValues.size(); j++)
//		{
//			if (QString::fromStdString(filteredVisData[i][7]) == clusterValues[j])
//			{
//				clusterfilteredVisData.push_back(filteredVisData[i]);
//				continue;
//			}
//
//		}
//	}
//
//
//
//	QString _jsonObject;
//	_jsonObject += "[";
//
//	QStringList columnNames = { "RowNumber", "species_1", "cluster_1", "species_2", "cluster_2", "dist", "neighborhood", "cross_species_cluster1_species_1", "cross_species_cluster2_species_2", "sortColumn","subclass_1","class_1","subclass_2","class_2" };
//
//	for (int i = 0; i < clusterfilteredVisData.size(); i++)
//	{
//		_jsonObject += "{";
//
//		for (int j = 0; j < clusterfilteredVisData[i].size(); j++)
//		{
//			QString columnName = columnNames[j];
//			_jsonObject += QString("\"%1\":\"%2\",").arg(columnName, clusterfilteredVisData[i][j].c_str());
//		}
//
//		_jsonObject.chop(1);
//
//		_jsonObject += "},";
//	}
//	_jsonObject.chop(1);
//	_jsonObject += "]";
//	_simianViewerPlugin.getSimianViewerWidget().setData(_jsonObject.toStdString());
//	auto& colorMapRangeAction = _visSettingHolder.getColorMapAction().getSettingsAction().getHorizontalAxisAction().getRangeAction();
//	float colorMapRangeMin = 1200.0;
//	float colorMapRangeMax = 0.0;
//	for (int i = 0; i < clusterfilteredVisData.size(); i++)
//	{
//		const float temp = std::stof(clusterfilteredVisData[i][5]);
//		if (temp < colorMapRangeMin)
//		{
//			colorMapRangeMin = temp;
//		}
//		if (temp > colorMapRangeMax)
//		{
//			colorMapRangeMax = temp;
//		}
//	}
//	// Initialize the color map range action with the color map range from the scatter plot 
//	colorMapRangeAction.initialize(colorMapRangeMin, colorMapRangeMax, colorMapRangeMin, colorMapRangeMax, colorMapRangeMin, colorMapRangeMax);
//	if (!_isStarted)
//	{
//		_isStarted = true;
//	}
//}

//QString SimianOptionsAction::selectFromQStringList(const QStringList& fileList, const QString& speciesType, const QString& fileType, const QString& neighborhoodType)
//{
//	QString foundFile = "";
//
//	for (const auto& file : fileList)
//	{
//		if (file.toLower().contains(speciesType.toLower())) 
//		{
//			if (file.toLower().contains(neighborhoodType.toLower()))
//			{
//				if (fileType == "in-species class")
//				{
//					if (file.toLower().endsWith("/class"))
//					{
//						foundFile = file;
//					}
//				}
//				else if (fileType == "in-species cluster")
//				{
//					if (file.toLower().endsWith("/cluster"))
//					{
//						foundFile = file;
//					}
//
//				}
//				else if (fileType == "cross-species class")
//				{
//					if (file.toLower().endsWith("/cross_species_class"))
//					{
//						foundFile = file;
//					}
//				}
//				else if (fileType == "cross-species cluster")
//				{
//					if (file.toLower().endsWith("/cross_species_cluster"))
//					{
//						foundFile = file;
//					}
//				}
//				else if (fileType == "cross-species sub-class")
//				{
//					if (file.toLower().endsWith("/cross_species_subclass"))
//					{
//						foundFile = file;
//					}
//				}
//
//				else if (fileType == "donor")
//				{
//					if (file.toLower().endsWith("/donor"))
//					{
//						foundFile = file;
//					}
//
//				}
//				else if (fileType == "neighborhood")
//				{
//					if (file.toLower().endsWith("/neighborhood"))
//					{
//						foundFile = file;
//					}
//
//				}
//				else if (fileType == "sex")
//				{
//					if (file.toLower().endsWith("/sex"))
//					{
//						foundFile = file;
//					}
//
//				}
//				else if (fileType == "in-species subclass")
//				{
//					if (file.toLower().endsWith("/subclass"))
//					{
//						foundFile = file;
//					}
//				}
//			}
//		}
//	}
//
//	return foundFile;
//}



bool SimianOptionsAction::QStringlistContainsQString(const QStringList& list, const QString& str)
{
	QStringMatcher matcher(str);
	foreach(const QString & listitem, list) {
		if (matcher.indexIn(listitem) != -1) return true;
	}
	return false;
}

void SimianOptionsAction::initLoader()
{
	if (_species1SelectAction.getCurrentText() != "" && _species2SelectAction.getCurrentText() != "")
	{
		updateData((_species1SelectAction.getCurrentText()).toStdString(), (_species2SelectAction.getCurrentText()).toStdString(), (_neighborhoodAction.getCurrentText()).toStdString());


		if (_linkerSettingHolder.getInSpecies1DatasetLinkerAction().getCurrentText() != "" && _linkerSettingHolder.getInSpecies2DatasetLinkerAction().getCurrentText() != "")
		{
			sendClusterCountInfoToJS();
		}


		if (_histBarAction.isChecked())
		{
			_simianViewerPlugin.getSimianViewerWidget().histChart(QString::fromStdString("T"));
		}
		else
		{
			_simianViewerPlugin.getSimianViewerWidget().histChart(QString::fromStdString("F"));
		}

		const auto& mirrorAction = _visSettingHolder.getColorMapAction().getSettingsAction().getHorizontalAxisAction().getMirrorAction();
		std::string s1 = _visSettingHolder.getColorMapAction().getColorMap().toStdString();
		std::string s2 = "*%*";
		std::string s3;
		if (mirrorAction.isChecked())
		{
			s3 = "T";
		}
		else
		{
			s3 = "F";
		}
		std::string full = s1 + s2 + s3;
		_simianViewerPlugin.getSimianViewerWidget().setColor(QString::fromStdString(full));

		if (_visSettingHolder.getFullHeatmapAction().isChecked())
		{
			_simianViewerPlugin.getSimianViewerWidget().showFullHeatmap(QString::fromStdString("T"));
		}
		else
		{
			_simianViewerPlugin.getSimianViewerWidget().showFullHeatmap(QString::fromStdString("F"));
		}
	}


	QVariantList commands;

	QVariantList command;
	command << QString("TableView") << QString("SLOT_setColumnWidth") << int(0) << int(120);
	commands.push_back(command);
	command.clear();
	command << QString("TableView") << QString("SLOT_setColumnWidth") << int(1) << int(40);
	commands.push_back(command);
	command.clear();
	command << QString("TableView") << QString("SLOT_setColumnWidth") << int(2) << int(40);
	commands.push_back(command);
	command.clear();
	command << QString("TableView") << QString("SLOT_setColumnWidth") << int(3) << int(120);
	commands.push_back(command);
	command.clear();
	command << QString("TableView") << QString("SLOT_setColumnWidth") << int(4) << int(120);
	commands.push_back(command);
	command.clear();
	command << QString("TableViewClusterSelection1") << QString("setDisabled") << bool(true);
	commands.push_back(command);
	command.clear();
	command << QString("TableViewClusterSelection2") << QString("setDisabled") << bool(true);
	commands.push_back(command);
	command.clear();

	command << QString("LoadedDataSettings") << "hide";
	commands.push_back(command);
	command.clear();


	Qt::SortOrder sortOrder = Qt::DescendingOrder;
	QVariant sortOrderVariant(QMetaType::fromType<Qt::SortOrder>(), &sortOrder);
	command << QString("TableView") << QString("sortByColumn") << int(3) << sortOrderVariant;
	commands.push_back(command);
	_linkerSettingHolder.getCommandAction().setVariant(commands);

	if (!_stopMethodFlagFromSpecies1 && !_stopMethodFlagFromSpecies2)
	{
		_linkerSettingHolder.getmodifyDifferentialExpressionAutoUpdateAction().trigger();
	}

}

void SimianOptionsAction::fromVariantMap(const QVariantMap& variantMap)
{
	WidgetAction::fromVariantMap(variantMap);

	_species1SelectAction.fromParentVariantMap(variantMap);
	_species2SelectAction.fromParentVariantMap(variantMap);
	_neighborhoodAction.fromParentVariantMap(variantMap);
	_scatterplotColorControlAction.fromParentVariantMap(variantMap);
	_visSettingHolder.getPluginVisibilityAction().fromParentVariantMap(variantMap);
	//_distanceAction.fromParentVariantMap(variantMap);
	_linkerSettingHolder.getCrossSpecies1DatasetLinkerAction().fromParentVariantMap(variantMap);
	_linkerSettingHolder.getCrossSpecies2DatasetLinkerAction().fromParentVariantMap(variantMap);
	_linkerSettingHolder.getSpecies1ScatterplotColorLinkerAction().fromParentVariantMap(variantMap);
	_linkerSettingHolder.getSpecies2ScatterplotColorLinkerAction().fromParentVariantMap(variantMap);
	_linkerSettingHolder.getSpeciesEmbedding1LinkerAction().fromParentVariantMap(variantMap);
	_linkerSettingHolder.getSpeciesEmbedding2LinkerAction().fromParentVariantMap(variantMap);
	_linkerSettingHolder.getSpecies1DEStatsLinkerAction().fromParentVariantMap(variantMap);
	_linkerSettingHolder.getSpecies2DEStatsLinkerAction().fromParentVariantMap(variantMap);
	_linkerSettingHolder.getInSpecies1DatasetLinkerAction().fromParentVariantMap(variantMap);
	_linkerSettingHolder.getInSpecies2DatasetLinkerAction().fromParentVariantMap(variantMap);
	//_crossSpeciesFilterAction.fromParentVariantMap(variantMap);
	_linkerSettingHolder.getInSpecies1HeatMapCellAction().fromParentVariantMap(variantMap);
	_linkerSettingHolder.getInSpecies2HeatMapCellAction().fromParentVariantMap(variantMap);
	_linkerSettingHolder.getCrossSpecies1HeatMapCellAction().fromParentVariantMap(variantMap);
	_linkerSettingHolder.getCrossSpecies2HeatMapCellAction().fromParentVariantMap(variantMap);
	_linkerSettingHolder.getmodifyDifferentialExpressionAutoUpdateAction().fromParentVariantMap(variantMap);
	_linkerSettingHolder.getRemoveLinkingOptionMenuFromUIAction().fromParentVariantMap(variantMap);
	_linkerSettingHolder.getSpecies1Name().fromParentVariantMap(variantMap);
	_linkerSettingHolder.getSpecies2Name().fromParentVariantMap(variantMap);
	_linkerSettingHolder.getSelectedCrossspeciescluster().fromParentVariantMap(variantMap);
	_linkerSettingHolder.getGeneExpressionDatasetVariant().fromParentVariantMap(variantMap);	
	_linkerSettingHolder.getCommandAction().fromParentVariantMap(variantMap);
	_linkerSettingHolder.getSelectedCrossSpeciesNameList().fromParentVariantMap(variantMap);
	_linkerSettingHolder.getHarHcondelCountString().fromParentVariantMap(variantMap);
	_visSettingHolder.getColorMapAction().fromParentVariantMap(variantMap);
	//_backgroundColoringAction.fromParentVariantMap(variantMap);
	_visSettingHolder.getFullHeatmapAction().fromParentVariantMap(variantMap);
	_histBarAction.fromParentVariantMap(variantMap);
}

QVariantMap SimianOptionsAction::toVariantMap() const
{
	QVariantMap variantMap = WidgetAction::toVariantMap();

	_species1SelectAction.insertIntoVariantMap(variantMap);
	_species2SelectAction.insertIntoVariantMap(variantMap);
	_neighborhoodAction.insertIntoVariantMap(variantMap);
	_scatterplotColorControlAction.insertIntoVariantMap(variantMap);
	//_distanceAction.insertIntoVariantMap(variantMap);
	_linkerSettingHolder.getCrossSpecies1DatasetLinkerAction().insertIntoVariantMap(variantMap);
	_linkerSettingHolder.getCrossSpecies2DatasetLinkerAction().insertIntoVariantMap(variantMap);
	_linkerSettingHolder.getSpecies1ScatterplotColorLinkerAction().insertIntoVariantMap(variantMap);
	_linkerSettingHolder.getSpecies2ScatterplotColorLinkerAction().insertIntoVariantMap(variantMap);
	_linkerSettingHolder.getSpeciesEmbedding1LinkerAction().insertIntoVariantMap(variantMap);
	_linkerSettingHolder.getSpeciesEmbedding2LinkerAction().insertIntoVariantMap(variantMap);
	_linkerSettingHolder.getSpecies1DEStatsLinkerAction().insertIntoVariantMap(variantMap);
	_linkerSettingHolder.getSpecies2DEStatsLinkerAction().insertIntoVariantMap(variantMap);
	_linkerSettingHolder.getInSpecies1DatasetLinkerAction().insertIntoVariantMap(variantMap);
	_linkerSettingHolder.getInSpecies2DatasetLinkerAction().insertIntoVariantMap(variantMap);
	//_crossSpeciesFilterAction.insertIntoVariantMap(variantMap);
	_linkerSettingHolder.getInSpecies1HeatMapCellAction().insertIntoVariantMap(variantMap);
	_linkerSettingHolder.getInSpecies2HeatMapCellAction().insertIntoVariantMap(variantMap);
	_linkerSettingHolder.getCrossSpecies1HeatMapCellAction().insertIntoVariantMap(variantMap);
	_linkerSettingHolder.getCrossSpecies2HeatMapCellAction().insertIntoVariantMap(variantMap);
	_linkerSettingHolder.getmodifyDifferentialExpressionAutoUpdateAction().insertIntoVariantMap(variantMap);
	_linkerSettingHolder.getRemoveLinkingOptionMenuFromUIAction().insertIntoVariantMap(variantMap);
	_linkerSettingHolder.getSpecies1Name().insertIntoVariantMap(variantMap);
	_linkerSettingHolder.getSpecies2Name().insertIntoVariantMap(variantMap);
	_linkerSettingHolder.getSelectedCrossspeciescluster().insertIntoVariantMap(variantMap);
	_linkerSettingHolder.getGeneExpressionDatasetVariant().insertIntoVariantMap(variantMap);
	_linkerSettingHolder.getCommandAction().insertIntoVariantMap(variantMap);
	_linkerSettingHolder.getSelectedCrossSpeciesNameList().insertIntoVariantMap(variantMap);
	_linkerSettingHolder.getHarHcondelCountString().insertIntoVariantMap(variantMap);
	_visSettingHolder.getFullHeatmapAction().insertIntoVariantMap(variantMap);
	
	_visSettingHolder.getPluginVisibilityAction().insertIntoVariantMap(variantMap);
	//_backgroundColoringAction.insertIntoVariantMap(variantMap);
	_visSettingHolder.getColorMapAction().insertIntoVariantMap(variantMap);
	_histBarAction.insertIntoVariantMap(variantMap);
	return variantMap;
}

QVariant SimianOptionsAction::CalculateGeneExpressionValues(QString crossSpeciesCluster)
{
	QVariant QVariantMapValue;
	//qDebug() << "+_+_+_";
	for (auto e : _geneExpressionData.keys())
	{
		if (e == crossSpeciesCluster)
		{
			//qDebug() << e;// << "," << _geneExpressionData.value(e) << '\n';
			QVariantMapValue = _geneExpressionData.value(e);
		}
	}
	//qDebug() << "+_+_+_";


	return QVariantMapValue;
}
