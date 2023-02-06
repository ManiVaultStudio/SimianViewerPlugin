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
	//_crossSpeciesFilterAction(this, "Filter clusters"),
	_inSpecies1HeatMapCellAction(this, "Link in-species1 heatmap cell"),
	_inSpecies2HeatMapCellAction(this, "Link in-species2 heatmap cell"),
	_crossSpecies1HeatMapCellAction(this, "Link cross-species1 heatmap cell"),
	_crossSpecies2HeatMapCellAction(this, "Link cross-species2 heatmap cell"),
	//_multiSelectClusterFilterAction(this, "Select cross-species clusters"),
	_colorMapAction(this, "Select color map"),
	_backgroundColoringAction(this, "Select background color", DEFAULT_CONSTANT_COLOR, DEFAULT_CONSTANT_COLOR),
	_species1Holder(*this),
	_species2Holder(*this),
	_visSettingHolder(*this),
	_linkerSettingHolder(*this),
	_distanceNeighborhoodHolder(*this),
	_scatterplotColorHolder(*this),
	//_explorationAction(*this),
	_cellCountHolder(*this),
	_isStarted(false),
	_histBarAction(this,"Cell counts"),
	_modifyDifferentialExpressionAutoUpdate(this, "Automatic Update Switch"),
	_removeLinkingOptionMenuFromUIAction(this, "Remove linking option"),
	_fullHeatMapAction(this,"Full distancemap")/*,
	_explorationModeAction(this)*/,
	//_helpAction(this, "Help"),
	//_screenshotAction(this, "Screenshot"),
	_species1Name(this,"Species1Name"),
	_species2Name(this, "Species2Name"),
	_selectedCrossspeciescluster(this, "Selected CrossSpecies Cluster"),
	_geneExpressionDatasetVariant(this,"Gene Expression Variant"),
	_selectedCrossSpeciesNameList(this,"Selected Cross Species Name List"),
	_scatterplotColorMapAction(this,"Scatterplot color map connection"),
	_harHcondelCountString(this,"Har-Hcondel Count String")
{
	setText("Settings");
	//_species1SelectAction.setConnectionPermissions(ConnectionPermissionFlag::All);
	setSerializationName("SimianSettings");
	_species1SelectAction.setSerializationName( "Species1(X-axis)");
		_species2SelectAction.setSerializationName( "Species2(Y-axis)");
		_neighborhoodAction.setSerializationName( "Neighborhood");
		_scatterplotColorControlAction.setSerializationName( "Scatterplot color");
		//_distanceAction.setSerializationName( "Filter distance :");
		_crossSpecies1DatasetLinkerAction.setSerializationName( "Cross-species cluster dataset1");
		_crossSpecies2DatasetLinkerAction.setSerializationName( "Cross-species  cluster dataset2");
		_species1ScatterplotColorLinkerAction.setSerializationName( "Scatterplot color linker species1");
		_species2ScatterplotColorLinkerAction.setSerializationName( "Scatterplot color linker species2");
		_speciesEmbedding1LinkerAction.setSerializationName( "Embedding dataset1");
		_speciesEmbedding2LinkerAction.setSerializationName( "Embedding dataset2");
		_species1DEStatsLinkerAction.setSerializationName( "DEStats dataset1");
		_species2DEStatsLinkerAction.setSerializationName( "DEStats dataset2");
		_inSpecies1DatasetLinkerAction.setSerializationName( "In-species  cluster dataset1");
		_inSpecies2DatasetLinkerAction.setSerializationName( "In-species  cluster dataset2");
		//_crossSpeciesFilterAction.setSerializationName( "Filter clusters");
		_inSpecies1HeatMapCellAction.setSerializationName( "Link in-species1 heatmap cell");
		_inSpecies2HeatMapCellAction.setSerializationName( "Link in-species2 heatmap cell");
		_crossSpecies1HeatMapCellAction.setSerializationName( "Link cross-species1 heatmap cell");
		_crossSpecies2HeatMapCellAction.setSerializationName( "Link cross-species2 heatmap cell");

		_colorMapAction.setSerializationName( "Select color map");
		_backgroundColoringAction.setSerializationName( "Select background color");
		_histBarAction.setSerializationName( "Cell counts");
		_modifyDifferentialExpressionAutoUpdate.setSerializationName( "Automatic Update Switch");
		_removeLinkingOptionMenuFromUIAction.setSerializationName( "Remove linking option");
		_fullHeatMapAction.setSerializationName( "Full distancemap");
		_species1Name.setSerializationName( "Species1Name");
		_species2Name.setSerializationName( "Species2Name");
		_selectedCrossspeciescluster.setSerializationName( "Selected CrossSpecies Cluster");
		_geneExpressionDatasetVariant.setSerializationName( "Gene Expression Variant");
		_selectedCrossSpeciesNameList.setSerializationName( "Selected Cross Species Name List");
		_scatterplotColorMapAction.setSerializationName( "Scatterplot color map connection");
		_harHcondelCountString.setSerializationName( "Har-Hcondel Count String");



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
	//_fullHeatMapAction.setEnabled(false);
	//_explorationModeAction.setEnabled(false);
	//_crossSpecies1DatasetLinkerAction.setEnabled(false);
	//_crossSpecies2DatasetLinkerAction.setEnabled(false);
	//_species1ScatterplotColorLinkerAction.setEnabled(false);
	//_species2ScatterplotColorLinkerAction.setEnabled(false);
	//_scatterplotColorControlAction.setEnabled(false);
	//_speciesEmbedding1LinkerAction.setEnabled(false);
	//_speciesEmbedding2LinkerAction.setEnabled(false);
	//_species1DEStatsLinkerAction
	//_species1DEStatsLinkerAction.setEnabled(false);
	//_species2DEStatsLinkerAction.setEnabled(false);
	//_inSpecies1DatasetLinkerAction.setEnabled(false);
	//_inSpecies2DatasetLinkerAction.setEnabled(false);
	//_crossSpeciesFilterAction.setEnabled(false);
	//_multiSelectClusterFilterAction.setEnabled(false);
	//_colorMapAction.setEnabled(false);
	//_backgroundColoringAction.setEnabled(false);
	//_visSettingHolder.setEnabled(false);
	//_linkerSettingHolder.setEnabled(false);
	//_distanceNeighborhoodHolder.setEnabled(false);
	_species1SelectAction.setDefaultWidgetFlags(OptionAction::ComboBox);
	//_species1SelectAction.setPlaceHolderString(QString("Choose Species1"));
	_species1SelectAction.initialize(QStringList({ "chimp","gorilla","human","rhesus","marmoset"}), "chimp", "chimp");
	_species2SelectAction.setDefaultWidgetFlags(OptionAction::ComboBox);
	//_species2SelectAction.setPlaceHolderString(QString("Choose Species2"));
	_species2SelectAction.initialize(QStringList({ "gorilla","human","rhesus","marmoset" }), "human", "human");
	//_crossSpeciesFilterAction.setDefaultWidgetFlags(OptionAction::ComboBox);
	//_crossSpeciesFilterAction.initialize(QStringList({ "all clusters","cross-species clusters" }), "cross-species clusters", "cross-species clusters");
	_inSpecies1HeatMapCellAction.setDefaultWidgetFlags(OptionAction::ComboBox);

	_inSpecies2HeatMapCellAction.setDefaultWidgetFlags(OptionAction::ComboBox);
	_crossSpecies1HeatMapCellAction.setDefaultWidgetFlags(OptionAction::ComboBox);
	_crossSpecies2HeatMapCellAction.setDefaultWidgetFlags(OptionAction::ComboBox);
	//_multiSelectClusterFilterAction.setDefaultWidgetFlags(OptionsAction::ComboBox | OptionsAction::Selection | OptionsAction::File);
	//_multiSelectClusterFilterAction.initialize(QStringList{ "" });
	//_multiSelectClusterFilterAction.setSelectedOptions(QStringList());
	_colorMapAction.initialize("Black to white", "Black to white");
	_scatterplotColorMapAction.initialize("Viridis", "Viridis");
	_backgroundColoringAction.initialize(DEFAULT_CONSTANT_COLOR, DEFAULT_CONSTANT_COLOR);
	_neighborhoodAction.setDefaultWidgetFlags(OptionAction::ComboBox);
	_neighborhoodAction.initialize(QStringList({ "Non-neuronal cells","IT-projecting excitatory","Non-IT-projecting excitatory","CGE-derived inhibitory","MGE-derived inhibitory" }), "CGE-derived inhibitory", "CGE-derived inhibitory");
	QStringList defaultTotalValues = QStringList({ " ","exc","glia","inh","Astro_2","Astro_3","Astro_4","Chandelier_1","Chandelier_2","Endo_1","Endo_2","L2/3 IT_1","L2/3 IT_2","L2/3 IT_3","L2/3 IT_4","L4 IT_1","L4 IT_2","L4 IT_3","L4 IT_4","L4 IT_5","L5 ET_1","L5 ET_2","L5 ET_3","L5 ET_4","L5 IT_1","L5 IT_2","L5 IT_3","L5/6 NP_1","L5/6 NP_2","L5/6 NP_3","L5/6 NP_4","L6 CT_1","L6 CT_2","L6 IT Car3_1","L6 IT Car3_2","L6 IT Car3_3","L6 IT_1","L6 IT_2","L6 IT_3","L6b_1","L6b_2","L6b_3","L6b_4","L6b_5","L6b_6","Lamp5_1","Lamp5_2","Lamp5_Lhx6_1","Lamp5_Lhx6_2","Micro-PVM_1","Micro-PVM_2","Micro-PVM_3","OPC_1","OPC_2","OPC_3","Oligo_1","Pax6_1","Pax6_2","Pax6_3","Pax6_4","Pvalb_1","Pvalb_2","Pvalb_3","Pvalb_4","Pvalb_5","Pvalb_6","Pvalb_7","Pvalb_8","Sncg_1","Sncg_2","Sncg_3","Sncg_4","Sncg_5","Sncg_6","Sncg_7","Sst Chodl_1","Sst Chodl_2","Sst Chodl_3","Sst_1","Sst_10","Sst_11","Sst_12","Sst_13","Sst_14","Sst_15","Sst_16","Sst_17","Sst_18","Sst_2","Sst_3","Sst_4","Sst_5","Sst_6","Sst_7","Sst_8","Sst_9","VLMC_1","VLMC_2","VLMC_3","VLMC_4","Vip_1","Vip_10","Vip_11","Vip_12","Vip_13","Vip_14","Vip_15","Vip_16","Vip_17","Vip_2","Vip_3","Vip_4","Vip_5","Vip_6","Vip_7","Vip_8","Vip_9","Astro_5","L2/3 IT_10","L2/3 IT_11","L2/3 IT_12","L2/3 IT_13","L2/3 IT_5","L2/3 IT_6","L2/3 IT_7","L2/3 IT_8","L2/3 IT_9","L5 IT_4","L5 IT_5","L5 IT_6","L5 IT_7","L5/6 NP_5","L5/6 NP_6","L6 CT_3","L6 CT_4","Lamp5_3","Lamp5_4","Lamp5_5","Lamp5_6","Oligo_2","Oligo_3","Oligo_4","Pvalb_10","Pvalb_11","Pvalb_12","Pvalb_13","Pvalb_14","Pvalb_15","Pvalb_9","Sncg_8","Sst_19","Sst_20","Sst_21","Sst_22","Sst_23","Sst_24","Sst_25","Sst_26","Vip_18","Vip_19","Vip_20","Vip_21","Vip_22","Vip_23","Endo_3","L4 IT_6","Micro-PVM_4","OPC_4","Sncg_9","L2/3 IT_14","L2/3 IT_15","L5/6 NP_7","L5/6 NP_8","L6 IT_4","Sncg_10","Glutamatergic","Non-Neuronal","Chandelier","Endo","L2/3 IT","L4 IT","L5 ET","L5 IT","L5/6 NP","L6 CT","L6 IT","L6 IT Car3","L6b","Lamp5","Lamp5_Lhx6","Micro-PVM","OPC","Oligo","Pax6","Pvalb","Sncg","Sst","Sst Chodl","VLMC","Vip","G19.32.002","G20.32.001","G20.32.002","H18.30.002","H19.30.001","H19.30.002","H200.1023","bi006","bi007","Q19.26.011","Q19.26.015","C19.32.002","C19.32.003","C19.32.004","C19.32.005","C19.32.006","C19.32.007","H18.30.001","bi005","Q19.26.010","C19.32.001","it_types","l5et_l56np_l6ct_l6b","lamp5_sncg_vip","sst_sst_chodl_pvalb","Astro_1","GABAergic","Astro","G19.32.001" });
	_crossSpecies2HeatMapCellAction.initialize(defaultTotalValues, "", "");
	_crossSpecies1HeatMapCellAction.initialize(defaultTotalValues, "", "");
	_species1Name.initialize("");
	_species2Name.initialize("");
	_selectedCrossspeciescluster.initialize("");
	_selectedCrossSpeciesNameList.initialize("");
	_inSpecies2HeatMapCellAction.initialize(defaultTotalValues, "", "");
	_inSpecies1HeatMapCellAction.initialize(defaultTotalValues, "", "");

	_scatterplotColorControlAction.setDefaultWidgetFlags(OptionAction::ComboBox);
	_scatterplotColorControlAction.initialize(QStringList({ "cross-species cluster","in-species cluster","differential expression","cross-species sub-class","in-species subclass","donor"}), "cross-species cluster", "cross-species cluster");
	//_distanceAction.setDefaultWidgetFlags(IntegralAction::SpinBox | IntegralAction::Slider);
	//_distanceAction.initialize(0, 105, 105, 105);
	_histBarAction.setDefaultWidgetFlags(ToggleAction::CheckBox);
	_histBarAction.initialize(false, false);

	_removeLinkingOptionMenuFromUIAction.setDefaultWidgetFlags(ToggleAction::CheckBox);
	_removeLinkingOptionMenuFromUIAction.initialize(false, false);
	_fullHeatMapAction.setDefaultWidgetFlags(ToggleAction::CheckBox);
	_fullHeatMapAction.initialize(false, false);
	//_explorationModeAction.setDefaultWidgetFlags(ToggleAction::CheckBox);
	//_explorationModeAction.initialize(false, false);
	_crossSpecies1DatasetLinkerAction.setDefaultWidgetFlags(OptionAction::ComboBox);
	_crossSpecies2DatasetLinkerAction.setDefaultWidgetFlags(OptionAction::ComboBox);
	_species1ScatterplotColorLinkerAction.setDefaultWidgetFlags(OptionAction::ComboBox);
	_species2ScatterplotColorLinkerAction.setDefaultWidgetFlags(OptionAction::ComboBox);
	_speciesEmbedding1LinkerAction.setDefaultWidgetFlags(OptionAction::ComboBox);
	_speciesEmbedding2LinkerAction.setDefaultWidgetFlags(OptionAction::ComboBox);
	_species2DEStatsLinkerAction.setDefaultWidgetFlags(OptionAction::ComboBox);
	_species1DEStatsLinkerAction.setDefaultWidgetFlags(OptionAction::ComboBox);
	_inSpecies1DatasetLinkerAction.setDefaultWidgetFlags(OptionAction::ComboBox);
	_inSpecies2DatasetLinkerAction.setDefaultWidgetFlags(OptionAction::ComboBox);
	_colorMapAction.getSettingsAction().getDiscreteAction().setVisible(false);
	_colorMapAction.getSettingsAction().getEditor1DAction().setVisible(false);

	_scatterplotColorMapAction.getSettingsAction().getDiscreteAction().setVisible(false);
	_scatterplotColorMapAction.getSettingsAction().getEditor1DAction().setVisible(false);
	
	if (!_scatterplotColorMapAction.isPublished())
	{
		_scatterplotColorMapAction.publish("Scatterplot color map connect");
	}
	if (!_crossSpecies1DatasetLinkerAction.isPublished())
	{
		_crossSpecies1DatasetLinkerAction.publish("CrossSpeciesDataset1");
	}
	if (!_crossSpecies2DatasetLinkerAction.isPublished())
	{
		_crossSpecies2DatasetLinkerAction.publish("CrossSpeciesDataset2");
	}
	if (!_species1Name.isPublished())
	{
		_species1Name.publish("Species1Name");
	}
	if (!_species2Name.isPublished())
	{
		_species2Name.publish("Species2Name");
	}
	if (!_selectedCrossspeciescluster.isPublished())
	{
		_selectedCrossspeciescluster.publish("Selected Cross-species cluster");
	}

	if (!_crossSpecies1HeatMapCellAction.isPublished())
	{
		_crossSpecies1HeatMapCellAction.publish("C1");
	}
	if (!_crossSpecies2HeatMapCellAction.isPublished())
	{
		_crossSpecies2HeatMapCellAction.publish("C2");
	}


	if (!_species1ScatterplotColorLinkerAction.isPublished())
	{
		_species1ScatterplotColorLinkerAction.publish("Scatterplot color species1");
	}
	if (!_species2ScatterplotColorLinkerAction.isPublished())
	{
		_species2ScatterplotColorLinkerAction.publish("Scatterplot color species2");
	}

	if (!_speciesEmbedding1LinkerAction.isPublished())
	{
		_speciesEmbedding1LinkerAction.publish("EmbeddingDataset1");
	}
	if (!_speciesEmbedding2LinkerAction.isPublished())
	{
		_speciesEmbedding2LinkerAction.publish("EmbeddingDataset2");
	}

	if (!_species1DEStatsLinkerAction.isPublished())
	{
		_species1DEStatsLinkerAction.publish("DEStatsDataset1");
	}
	if (!_species2DEStatsLinkerAction.isPublished())
	{
		_species2DEStatsLinkerAction.publish("DEStatsDataset2");
	}
	//_inSpecies1DatasetLinkerAction.setVisible(false);
	//_inSpecies2DatasetLinkerAction.setVisible(false);
	//_crossSpecies1DatasetLinkerAction.setVisible(false);
	//_crossSpecies2DatasetLinkerAction.setVisible(false);
	//_species1ScatterplotColorLinkerAction.setVisible(false);
	//_species2ScatterplotColorLinkerAction.setVisible(false);
	//_speciesEmbedding1LinkerAction.setVisible(false);
	//_speciesEmbedding2LinkerAction.setVisible(false);
	//_species1DEStatsLinkerAction.setVisible(false);
	//_species2DEStatsLinkerAction.setVisible(false);
	//_inSpecies1HeatMapCellAction.setVisible(false);
	//_inSpecies2HeatMapCellAction.setVisible(false);

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
		const auto& mirrorAction = _colorMapAction.getSettingsAction().getHorizontalAxisAction().getMirrorAction();
		std::string s1 = _colorMapAction.getColorMap().toStdString();
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
	const auto backgroundColoringFilter = [this]() -> void
	{
		const auto& color = _backgroundColoringAction.getColor();

		_simianViewerPlugin.getSimianViewerWidget().setBackgroundColor(color.name());
	};
	const auto updateColorMapRange = [this]() -> void
	{
		const auto& rangeAction = _colorMapAction.getSettingsAction().getHorizontalAxisAction().getRangeAction();
		std::string s1 = std::to_string(rangeAction.getMinimum());
		std::string s2 = " ";
		std::string s3 = std::to_string(rangeAction.getMaximum());
		std::string full = s1.substr(0, s1.find(".") + 3) + s2 + s3.substr(0, s3.find(".") + 3);
		_simianViewerPlugin.getSimianViewerWidget().setRangeValue(QString::fromStdString(full));
	};

	const auto updateSpecies1 = [this]() -> void
	{
		//if (_species1SelectAction.getCurrentText() != "")
		//{
			//_species2SelectAction.setEnabled(true);
			_species1Name.setString(_species1SelectAction.getCurrentText());
			if (_crossSpecies1DatasetLinkerAction.getNumberOfOptions() > 0)
			{
				QString species1CrossSpeciesClusterDatasetName = _species1SelectAction.getCurrentText() + "-10x-" + _neighborhoodAction.getCurrentText() + "/cross_species_cluster";
				_crossSpecies1DatasetLinkerAction.setCurrentText(species1CrossSpeciesClusterDatasetName);
			}

			if (_inSpecies1DatasetLinkerAction.getNumberOfOptions() > 0)
			{
				QString species1InSpeciesClusterDatasetName = _species1SelectAction.getCurrentText() + "-10x-" + _neighborhoodAction.getCurrentText() + "/cluster";
				_inSpecies1DatasetLinkerAction.setCurrentText(species1InSpeciesClusterDatasetName);
			}

			if (_speciesEmbedding1LinkerAction.getNumberOfOptions() > 0)
			{
				QString species1EmbeddingDatasetName = _species1SelectAction.getCurrentText() + "-10x-" + _neighborhoodAction.getCurrentText();
				_speciesEmbedding1LinkerAction.setCurrentText(species1EmbeddingDatasetName);
			}

			if (_species1DEStatsLinkerAction.getNumberOfOptions() > 0)
			{
				QString species1DEStatsDatasetName = _species1SelectAction.getCurrentText() + "-10x-" + _neighborhoodAction.getCurrentText() + "/cross_species_cluster/DE_Statistics";
				_species1DEStatsLinkerAction.setCurrentText(species1DEStatsDatasetName);
			}
			QString storeSpecies = _species2SelectAction.getCurrentText();
			QStringList speciesNames = { "gorilla","marmoset","rhesus","chimp","human" };
			speciesNames.removeAll(_species1SelectAction.getCurrentText());
			_species2SelectAction.initialize(QStringList({ speciesNames }), storeSpecies, storeSpecies);


			if (_species2SelectAction.getCurrentText() == _species1SelectAction.getCurrentText())
			{

				QStringList speciesNames = { "gorilla","marmoset","rhesus","chimp","human" };
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
						_crossSpecies1HeatMapCellAction.setCurrentText("");
						_crossSpecies2HeatMapCellAction.setCurrentText("");
						_selectedCrossSpeciesNameList.setString("");
						_crossSpecies1HeatMapCellAction.setCurrentText("Astro_1");
						_crossSpecies2HeatMapCellAction.setCurrentText("Astro_1");
						_selectedCrossSpeciesNameList.setString("Astro_1");
					}
					else if (_neighborhoodAction.getCurrentText() == "IT-projecting excitatory")
					{
						_crossSpecies1HeatMapCellAction.setCurrentText("");
						_crossSpecies2HeatMapCellAction.setCurrentText("");
						_selectedCrossSpeciesNameList.setString("");
						_crossSpecies1HeatMapCellAction.setCurrentText("L2/3 IT_1");
						_crossSpecies2HeatMapCellAction.setCurrentText("L2/3 IT_1");
						_selectedCrossSpeciesNameList.setString("L2/3 IT_1");
					}
					else if (_neighborhoodAction.getCurrentText() == "Non-IT-projecting excitatory")
					{
						_crossSpecies1HeatMapCellAction.setCurrentText("");
						_crossSpecies2HeatMapCellAction.setCurrentText("");
						_selectedCrossSpeciesNameList.setString("");
						_crossSpecies1HeatMapCellAction.setCurrentText("L6 CT_1");
						_crossSpecies2HeatMapCellAction.setCurrentText("L6 CT_1");
						_selectedCrossSpeciesNameList.setString("L6 CT_1");
					}
					else if (_neighborhoodAction.getCurrentText() == "CGE-derived inhibitory")
					{
						_crossSpecies1HeatMapCellAction.setCurrentText("");
						_crossSpecies2HeatMapCellAction.setCurrentText("");
						_selectedCrossSpeciesNameList.setString("");
						_crossSpecies1HeatMapCellAction.setCurrentText("Lamp5_1");
						_crossSpecies2HeatMapCellAction.setCurrentText("Lamp5_1");
						_selectedCrossSpeciesNameList.setString("Lamp5_1");
					}
					else if (_neighborhoodAction.getCurrentText() == "MGE-derived inhibitory")
					{
						_crossSpecies1HeatMapCellAction.setCurrentText("");
						_crossSpecies2HeatMapCellAction.setCurrentText("");
						_selectedCrossSpeciesNameList.setString("");
						_crossSpecies1HeatMapCellAction.setCurrentText("Sst Chodl_1");
						_crossSpecies2HeatMapCellAction.setCurrentText("Sst Chodl_1");
						_selectedCrossSpeciesNameList.setString("Sst Chodl_1");
					}
					if (_scatterplotColorControlAction.getCurrentText() == "differential expression")
					{
						_scatterplotColorControlAction.setCurrentText("cross-species cluster");
					}
					_modifyDifferentialExpressionAutoUpdate.trigger();
				//}
			}

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
			//_fullHeatMapAction.setEnabled(false);
			//_crossSpecies1DatasetLinkerAction.setEnabled(false);
			//_crossSpecies2DatasetLinkerAction.setEnabled(false);
			//_species1ScatterplotColorLinkerAction.setEnabled(false);
			//_species2ScatterplotColorLinkerAction.setEnabled(false);
			//_scatterplotColorControlAction.setEnabled(false);
			//_speciesEmbedding1LinkerAction.setEnabled(false);
			//_speciesEmbedding2LinkerAction.setEnabled(false);
			//_species2DEStatsLinkerAction.setEnabled(false);
			//_species1DEStatsLinkerAction.setEnabled(false);
			//_inSpecies1DatasetLinkerAction.setEnabled(false);
			//_inSpecies2DatasetLinkerAction.setEnabled(false);
			//_crossSpeciesFilterAction.setEnabled(false);;
			//_colorMapAction.setEnabled(false);
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
			//_crossSpecies1DatasetLinkerAction.setEnabled(true);
			//_crossSpecies2DatasetLinkerAction.setEnabled(true);
			//_species2Name.setString(_species2SelectAction.getCurrentText());
			//_speciesEmbedding1LinkerAction.setEnabled(true);
			//_speciesEmbedding2LinkerAction.setEnabled(true);
			//_species1DEStatsLinkerAction.setEnabled(true);
			//_species2DEStatsLinkerAction.setEnabled(true);
			//_inSpecies1DatasetLinkerAction.setEnabled(true);
			//_inSpecies2DatasetLinkerAction.setEnabled(true);
			//_crossSpeciesFilterAction.setEnabled(true);
			//_fullHeatMapAction.setEnabled(true);
			//_colorMapAction.setEnabled(true);
			//_backgroundColoringAction.setEnabled(true);
			//_visSettingHolder.setEnabled(true);
			//_linkerSettingHolder.setEnabled(true);
			//_distanceNeighborhoodHolder.setEnabled(true);
			if (_crossSpecies2DatasetLinkerAction.getNumberOfOptions() > 0)
			{
				QString species2CrossSpeciesClusterDatasetName = _species2SelectAction.getCurrentText() + "-10x-" + _neighborhoodAction.getCurrentText() + "/cross_species_cluster";
				_crossSpecies2DatasetLinkerAction.setCurrentText(species2CrossSpeciesClusterDatasetName);
			}

			if (_inSpecies2DatasetLinkerAction.getNumberOfOptions() > 0)
			{
				QString species2InSpeciesClusterDatasetName = _species2SelectAction.getCurrentText() + "-10x-" + _neighborhoodAction.getCurrentText() + "/cluster";
				_inSpecies2DatasetLinkerAction.setCurrentText(species2InSpeciesClusterDatasetName);
			}
			if (_speciesEmbedding2LinkerAction.getNumberOfOptions() > 0)
			{
				QString species2EmbeddingDatasetName = _species2SelectAction.getCurrentText() + "-10x-" + _neighborhoodAction.getCurrentText();
				_speciesEmbedding2LinkerAction.setCurrentText(species2EmbeddingDatasetName);
			}

			if (_species2DEStatsLinkerAction.getNumberOfOptions() > 0)
			{
				QString species2DEStatsDatasetName = _species2SelectAction.getCurrentText() + "-10x-" + _neighborhoodAction.getCurrentText() + "/cross_species_cluster/DE_Statistics";

				_species2DEStatsLinkerAction.setCurrentText(species2DEStatsDatasetName);
			}

			//if (_species1SelectAction.getCurrentText() != "")
			//{
				updateData((_species1SelectAction.getCurrentText()).toStdString(), (_species2SelectAction.getCurrentText()).toStdString(), (_neighborhoodAction.getCurrentText()).toStdString()/*, (_distanceAction.getValue()), (_crossSpeciesFilterAction.getCurrentText()).toStdString()*/);
				QString tempVal = _scatterplotColorControlAction.getCurrentText();
				_scatterplotColorControlAction.setCurrentText("");
				_scatterplotColorControlAction.setCurrentText(tempVal);

				if (_neighborhoodAction.getCurrentText() == "Non-neuronal cells")
				{
					_crossSpecies1HeatMapCellAction.setCurrentText("");
					_crossSpecies2HeatMapCellAction.setCurrentText("");
					_selectedCrossSpeciesNameList.setString("");
					_crossSpecies1HeatMapCellAction.setCurrentText("Astro_1");
					_crossSpecies2HeatMapCellAction.setCurrentText("Astro_1");
					_selectedCrossSpeciesNameList.setString("Astro_1");
				}
				else if (_neighborhoodAction.getCurrentText() == "IT-projecting excitatory")
				{
					_crossSpecies1HeatMapCellAction.setCurrentText("");
					_crossSpecies2HeatMapCellAction.setCurrentText("");
					_selectedCrossSpeciesNameList.setString("");
					_crossSpecies1HeatMapCellAction.setCurrentText("L2/3 IT_1");
					_crossSpecies2HeatMapCellAction.setCurrentText("L2/3 IT_1");
					_selectedCrossSpeciesNameList.setString("L2/3 IT_1");
				}
				else if (_neighborhoodAction.getCurrentText() == "Non-IT-projecting excitatory")
				{
					_crossSpecies1HeatMapCellAction.setCurrentText("");
					_crossSpecies2HeatMapCellAction.setCurrentText("");
					_selectedCrossSpeciesNameList.setString("");
					_crossSpecies1HeatMapCellAction.setCurrentText("L6 CT_1");
					_crossSpecies2HeatMapCellAction.setCurrentText("L6 CT_1");
					_selectedCrossSpeciesNameList.setString("L6 CT_1");
				}
				else if (_neighborhoodAction.getCurrentText() == "CGE-derived inhibitory")
				{
					_crossSpecies1HeatMapCellAction.setCurrentText("");
					_crossSpecies2HeatMapCellAction.setCurrentText("");
					_selectedCrossSpeciesNameList.setString("");
					_crossSpecies1HeatMapCellAction.setCurrentText("Lamp5_1");
					_crossSpecies2HeatMapCellAction.setCurrentText("Lamp5_1");
					_selectedCrossSpeciesNameList.setString("Lamp5_1");
				}
				else if (_neighborhoodAction.getCurrentText() == "MGE-derived inhibitory")
				{
					_crossSpecies1HeatMapCellAction.setCurrentText("");
					_crossSpecies2HeatMapCellAction.setCurrentText("");
					_selectedCrossSpeciesNameList.setString("");
					_crossSpecies1HeatMapCellAction.setCurrentText("Sst Chodl_1");
					_crossSpecies2HeatMapCellAction.setCurrentText("Sst Chodl_1");
					_selectedCrossSpeciesNameList.setString("Sst Chodl_1");
				}
				if (_scatterplotColorControlAction.getCurrentText() == "differential expression")
				{
					_scatterplotColorControlAction.setCurrentText("cross-species cluster");
				}
				_modifyDifferentialExpressionAutoUpdate.trigger();
			//}

		//}
		//else
		//{
			//_simianViewerPlugin.getSimianViewerWidget().resetView("Reset");
			//_neighborhoodAction.setEnabled(false);
			//_screenshotAction.setEnabled(false);
			//_scatterplotColorControlAction.setEnabled(false);
			//_distanceAction.setEnabled(false);
			//_histBarAction.setEnabled(false);
			//_fullHeatMapAction.setEnabled(false);
			//_crossSpecies1DatasetLinkerAction.setEnabled(false);
			//_crossSpecies2DatasetLinkerAction.setEnabled(false);
			//_species1ScatterplotColorLinkerAction.setEnabled(false);
			//_species2ScatterplotColorLinkerAction.setEnabled(false);
			//_speciesEmbedding1LinkerAction.setEnabled(false);
			//_speciesEmbedding2LinkerAction.setEnabled(false);
			//_species2DEStatsLinkerAction.setEnabled(false);
			//_species1DEStatsLinkerAction.setEnabled(false);
			//_inSpecies1DatasetLinkerAction.setEnabled(false);
			//_inSpecies2DatasetLinkerAction.setEnabled(false);
			//_crossSpeciesFilterAction.setEnabled(false);;
			//_colorMapAction.setEnabled(false);
			//_backgroundColoringAction.setEnabled(false);
			//_visSettingHolder.setEnabled(false);
			//_linkerSettingHolder.setEnabled(false);
			//_distanceNeighborhoodHolder.setEnabled(false);
		//}
	};



	const auto updateSelectedCrossSpeciesNameList = [this]() -> void
	{
		if(_species1SelectAction.getCurrentText()=="human"|| _species2SelectAction.getCurrentText() == "human")
		{
			if (_selectedCrossSpeciesNameList.getString() != "")
			{
				QVariant geneExpValue = CalculateGeneExpressionValues(_selectedCrossSpeciesNameList.getString());
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
				_harHcondelCountString.setString( "HARS:"+ QString::number(HARCount)+"\nHCONDELS:"+ QString::number(HCONDELCount));

				//countValues += "HARS:";
				//countValues += QString::number(HARCount);
				//countValues += "\nHCONDELS:";
				//countValues += QString::number(HCONDELCount);
				//qDebug() << geneEXp;
				/*qDebug() << "Count"<< countValues;*/
				_geneExpressionDatasetVariant.setVariant(geneEXp);
			}
		}
		

		else
		{
			QVariantMap geneEXp;
			_geneExpressionDatasetVariant.setVariant(geneEXp);
		}

		
	};
	const auto updateNeighborhood = [this]() -> void
	{
		if (_species1SelectAction.getCurrentText() != "" && _species2SelectAction.getCurrentText() != "")
		{
			updateData((_species1SelectAction.getCurrentText()).toStdString(), (_species2SelectAction.getCurrentText()).toStdString(), (_neighborhoodAction.getCurrentText()).toStdString()/*, (_distanceAction.getValue()), (_crossSpeciesFilterAction.getCurrentText()).toStdString()*/);
			
			
			if (_speciesEmbedding1LinkerAction.getNumberOfOptions() > 0)
			{
				QString species1EmbeddingDatasetName = _species1SelectAction.getCurrentText() + "-10x-" + _neighborhoodAction.getCurrentText();

				_speciesEmbedding1LinkerAction.setCurrentText(species1EmbeddingDatasetName);
			}
			if (_speciesEmbedding2LinkerAction.getNumberOfOptions() > 0)
			{
				QString species2EmbeddingDatasetName = _species2SelectAction.getCurrentText() + "-10x-" + _neighborhoodAction.getCurrentText();
				_speciesEmbedding2LinkerAction.setCurrentText(species2EmbeddingDatasetName);
			}
			if (_scatterplotColorControlAction.getCurrentText() == "differential expression")
			{
				_scatterplotColorControlAction.setCurrentText("cross-species cluster");
			}
			if (_species1ScatterplotColorLinkerAction.getNumberOfOptions() > 0)
			{
				QString species1EmbeddingColorDatasetName = "";
				if (_scatterplotColorControlAction.getCurrentText() == "cross-species cluster")
				{
					species1EmbeddingColorDatasetName = _species1SelectAction.getCurrentText() + "-10x-" + _neighborhoodAction.getCurrentText() + "/cross_species_cluster";
				}
				else if (_scatterplotColorControlAction.getCurrentText() == "in-species cluster")
				{
					species1EmbeddingColorDatasetName = _species1SelectAction.getCurrentText() + "-10x-" + _neighborhoodAction.getCurrentText() + "/cluster";
				}

				else if (_scatterplotColorControlAction.getCurrentText() == "cross-species sub-class")
				{
					species1EmbeddingColorDatasetName = _species1SelectAction.getCurrentText() + "-10x-" + _neighborhoodAction.getCurrentText() + "/cross_species_subclass";
				}
				else if (_scatterplotColorControlAction.getCurrentText() == "in-species subclass")
				{
					species1EmbeddingColorDatasetName = _species1SelectAction.getCurrentText() + "-10x-" + _neighborhoodAction.getCurrentText() + "/subclass";
				}
				else if (_scatterplotColorControlAction.getCurrentText() == "donor")
				{
					species1EmbeddingColorDatasetName = _species1SelectAction.getCurrentText() + "-10x-" + _neighborhoodAction.getCurrentText() + "/donor";
				}
				else if (_scatterplotColorControlAction.getCurrentText() == "differential expression")
				{
					species1EmbeddingColorDatasetName = "Cluster Differential Expression 1: SelectedIDMeanExpressions1";
				}

				_species1ScatterplotColorLinkerAction.setCurrentText(species1EmbeddingColorDatasetName);
				//qDebug() << _species1ScatterplotColorLinkerAction.getCurrentText();
			}
			if (_species2ScatterplotColorLinkerAction.getNumberOfOptions() > 0)
			{
				QString species2EmbeddingColorDatasetName = "";
				if (_scatterplotColorControlAction.getCurrentText() == "cross-species cluster")
				{
					species2EmbeddingColorDatasetName = _species2SelectAction.getCurrentText() + "-10x-" + _neighborhoodAction.getCurrentText() + "/cross_species_cluster";
				}
				else if (_scatterplotColorControlAction.getCurrentText() == "in-species cluster")
				{
					species2EmbeddingColorDatasetName = _species2SelectAction.getCurrentText() + "-10x-" + _neighborhoodAction.getCurrentText() + "/cluster";
				}

				else if (_scatterplotColorControlAction.getCurrentText() == "cross-species sub-class")
				{
					species2EmbeddingColorDatasetName = _species2SelectAction.getCurrentText() + "-10x-" + _neighborhoodAction.getCurrentText() + "/cross_species_subclass";
				}
				else if (_scatterplotColorControlAction.getCurrentText() == "in-species subclass")
				{
					species2EmbeddingColorDatasetName = _species2SelectAction.getCurrentText() + "-10x-" + _neighborhoodAction.getCurrentText() + "/subclass";
				}
				else if (_scatterplotColorControlAction.getCurrentText() == "donor")
				{
					species2EmbeddingColorDatasetName = _species2SelectAction.getCurrentText() + "-10x-" + _neighborhoodAction.getCurrentText() + "/donor";
				}
				else if (_scatterplotColorControlAction.getCurrentText() == "differential expression")
				{
					species2EmbeddingColorDatasetName = "Cluster Differential Expression 1: SelectedIDMeanExpressions2";
				}

				_species2ScatterplotColorLinkerAction.setCurrentText(species2EmbeddingColorDatasetName);
				//qDebug() << _species2ScatterplotColorLinkerAction.getCurrentText();
			}
			if (_species1DEStatsLinkerAction.getNumberOfOptions() > 0)
			{
				QString species1DEStatsDatasetName = _species1SelectAction.getCurrentText() + "-10x-" + _neighborhoodAction.getCurrentText() + "/cross_species_cluster/DE_Statistics";

				_species1DEStatsLinkerAction.setCurrentText(species1DEStatsDatasetName);
			}
			if (_species2DEStatsLinkerAction.getNumberOfOptions() > 0)
			{
				QString species2DEStatsDatasetName = _species2SelectAction.getCurrentText() + "-10x-" + _neighborhoodAction.getCurrentText() + "/cross_species_cluster/DE_Statistics";

				_species2DEStatsLinkerAction.setCurrentText(species2DEStatsDatasetName);
			}
			if (_inSpecies1DatasetLinkerAction.getNumberOfOptions() > 0)
			{
				QString species1InSpeciesClusterDatasetName = _species1SelectAction.getCurrentText() + "-10x-" + _neighborhoodAction.getCurrentText() + "/cluster";
				_inSpecies1DatasetLinkerAction.setCurrentText(species1InSpeciesClusterDatasetName);
			}
			if (_inSpecies2DatasetLinkerAction.getNumberOfOptions() > 0)
			{
				QString species2InSpeciesClusterDatasetName = _species2SelectAction.getCurrentText() + "-10x-" + _neighborhoodAction.getCurrentText() + "/cluster";
				_inSpecies2DatasetLinkerAction.setCurrentText(species2InSpeciesClusterDatasetName);
			}
			if (_crossSpecies1DatasetLinkerAction.getNumberOfOptions() > 0)
			{
				QString species1CrossSpeciesClusterDatasetName = _species1SelectAction.getCurrentText() + "-10x-" + _neighborhoodAction.getCurrentText() + "/cross_species_cluster";

				_crossSpecies1DatasetLinkerAction.setCurrentText(species1CrossSpeciesClusterDatasetName);
			}
			if (_crossSpecies2DatasetLinkerAction.getNumberOfOptions() > 0)
			{
				QString species2CrossSpeciesClusterDatasetName = _species2SelectAction.getCurrentText() + "-10x-" + _neighborhoodAction.getCurrentText() + "/cross_species_cluster";
				_crossSpecies2DatasetLinkerAction.setCurrentText(species2CrossSpeciesClusterDatasetName);
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
				_crossSpecies1HeatMapCellAction.setCurrentText("Astro_1");
				_crossSpecies2HeatMapCellAction.setCurrentText("Astro_1");
				_selectedCrossSpeciesNameList.setString("Astro_1");
			}
			else if (_neighborhoodAction.getCurrentText() == "IT-projecting excitatory")
			{
				_crossSpecies1HeatMapCellAction.setCurrentText("L2/3 IT_1");
				_crossSpecies2HeatMapCellAction.setCurrentText("L2/3 IT_1");
				_selectedCrossSpeciesNameList.setString("L2/3 IT_1");
			}
			else if (_neighborhoodAction.getCurrentText() == "Non-IT-projecting excitatory")
			{
				_crossSpecies1HeatMapCellAction.setCurrentText("L6 CT_1");
				_crossSpecies2HeatMapCellAction.setCurrentText("L6 CT_1");
				_selectedCrossSpeciesNameList.setString("L6 CT_1");
			}
			else if (_neighborhoodAction.getCurrentText() == "CGE-derived inhibitory")
			{
				_crossSpecies1HeatMapCellAction.setCurrentText("Lamp5_1");
				_crossSpecies2HeatMapCellAction.setCurrentText("Lamp5_1");
				_selectedCrossSpeciesNameList.setString("Lamp5_1");
			}
			else if (_neighborhoodAction.getCurrentText() == "MGE-derived inhibitory")
			{
				_crossSpecies1HeatMapCellAction.setCurrentText("Sst Chodl_1");
				_crossSpecies2HeatMapCellAction.setCurrentText("Sst Chodl_1");
				_selectedCrossSpeciesNameList.setString("Sst Chodl_1");
			}

			_modifyDifferentialExpressionAutoUpdate.trigger();
		}
	};
	const auto updateScatterplotColorControl = [this]() -> void
	{

		if (_species1ScatterplotColorLinkerAction.getNumberOfOptions() > 0)
		{
			QString species1EmbeddingColorDatasetName = "";
			if (_scatterplotColorControlAction.getCurrentText() == "cross-species cluster")
			{
				species1EmbeddingColorDatasetName = _species1SelectAction.getCurrentText() + "-10x-" + _neighborhoodAction.getCurrentText() + "/cross_species_cluster" ;
			}
			else if (_scatterplotColorControlAction.getCurrentText() == "in-species cluster")
			{
				species1EmbeddingColorDatasetName = _species1SelectAction.getCurrentText() + "-10x-" + _neighborhoodAction.getCurrentText() + "/cluster";
			}

			else if (_scatterplotColorControlAction.getCurrentText() == "cross-species sub-class")
			{
				species1EmbeddingColorDatasetName = _species1SelectAction.getCurrentText() + "-10x-" + _neighborhoodAction.getCurrentText() + "/cross_species_subclass";
			}
			else if (_scatterplotColorControlAction.getCurrentText() == "in-species subclass")
			{
				species1EmbeddingColorDatasetName = _species1SelectAction.getCurrentText() + "-10x-" + _neighborhoodAction.getCurrentText() + "/subclass" ;
			}
			else if (_scatterplotColorControlAction.getCurrentText() == "donor")
			{
				species1EmbeddingColorDatasetName = _species1SelectAction.getCurrentText() + "-10x-" + _neighborhoodAction.getCurrentText() + "/donor" ;
			}
			else if (_scatterplotColorControlAction.getCurrentText() == "differential expression")
			{
				species1EmbeddingColorDatasetName = "Cluster Differential Expression 1: SelectedIDMeanExpressions1";
			}

			_species1ScatterplotColorLinkerAction.setCurrentText(species1EmbeddingColorDatasetName);
			//qDebug() << _species1ScatterplotColorLinkerAction.getCurrentText();
		}
		if (_species2ScatterplotColorLinkerAction.getNumberOfOptions() > 0)
		{
			QString species2EmbeddingColorDatasetName = "";
			if (_scatterplotColorControlAction.getCurrentText() == "cross-species cluster")
			{
				species2EmbeddingColorDatasetName = _species2SelectAction.getCurrentText() + "-10x-" + _neighborhoodAction.getCurrentText() + "/cross_species_cluster" ;
			}
			else if (_scatterplotColorControlAction.getCurrentText() == "in-species cluster")
			{
				species2EmbeddingColorDatasetName = _species2SelectAction.getCurrentText() + "-10x-" + _neighborhoodAction.getCurrentText() + "/cluster";
			}

			else if (_scatterplotColorControlAction.getCurrentText() == "cross-species sub-class")
			{
				species2EmbeddingColorDatasetName = _species2SelectAction.getCurrentText() + "-10x-" + _neighborhoodAction.getCurrentText() + "/cross_species_subclass" ;
			}
			else if (_scatterplotColorControlAction.getCurrentText() == "in-species subclass")
			{
				species2EmbeddingColorDatasetName = _species2SelectAction.getCurrentText() + "-10x-" + _neighborhoodAction.getCurrentText() + "/subclass" ;
			}
			else if (_scatterplotColorControlAction.getCurrentText() == "donor")
			{
				species2EmbeddingColorDatasetName = _species2SelectAction.getCurrentText() + "-10x-" + _neighborhoodAction.getCurrentText() + + "/donor" ;
			}
			else if (_scatterplotColorControlAction.getCurrentText() == "differential expression")
			{
				species2EmbeddingColorDatasetName = "Cluster Differential Expression 1: SelectedIDMeanExpressions2";
			}
			_species2ScatterplotColorLinkerAction.setCurrentText(species2EmbeddingColorDatasetName);
			//qDebug() << _species2ScatterplotColorLinkerAction.getCurrentText();
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
		if (_removeLinkingOptionMenuFromUIAction.isChecked())
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
		if (_fullHeatMapAction.isChecked())
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
		if (_inSpecies1DatasetLinkerAction.getCurrentText() != "" && _inSpecies2DatasetLinkerAction.getCurrentText() != "")
		{
			sendClusterCountInfoToJS();
			if (_inSpecies1DatasetLinkerAction.getCurrentDataset().isValid() && _inSpecies2DatasetLinkerAction.getCurrentDataset().isValid())
			{
				_histBarAction.setEnabled(true);
				_species1ScatterplotColorLinkerAction.setEnabled(true);
				_species2ScatterplotColorLinkerAction.setEnabled(true);
				_scatterplotColorControlAction.setEnabled(true);

			}
			else
			{
				_histBarAction.setEnabled(false);
				_histBarAction.setChecked(false);
				_species1ScatterplotColorLinkerAction.setEnabled(false);
				_species2ScatterplotColorLinkerAction.setEnabled(false);
				_scatterplotColorControlAction.setEnabled(false);

			}
		}
		else
		{
			_histBarAction.setEnabled(false);
			_histBarAction.setChecked(false);
			_species1ScatterplotColorLinkerAction.setEnabled(false);
			_species2ScatterplotColorLinkerAction.setEnabled(false);
			_scatterplotColorControlAction.setEnabled(false);

		}
	};

	const auto updateInSpecies2DatasetLinker = [this]() -> void
	{
		if (_inSpecies1DatasetLinkerAction.getCurrentText() != "" && _inSpecies2DatasetLinkerAction.getCurrentText() != "")
		{
			sendClusterCountInfoToJS();
			if (_inSpecies1DatasetLinkerAction.getCurrentDataset().isValid() && _inSpecies2DatasetLinkerAction.getCurrentDataset().isValid())
			{
				_histBarAction.setEnabled(true);
				_species1ScatterplotColorLinkerAction.setEnabled(true);
				_species2ScatterplotColorLinkerAction.setEnabled(true);
				_scatterplotColorControlAction.setEnabled(true);
			}
			else
			{
				_histBarAction.setEnabled(false);
				_histBarAction.setChecked(false);
				_species1ScatterplotColorLinkerAction.setEnabled(false);
				_species2ScatterplotColorLinkerAction.setEnabled(false);
				_scatterplotColorControlAction.setEnabled(false);

			}
		}
		else
		{
			_histBarAction.setEnabled(false);
			_histBarAction.setChecked(false);
			_species1ScatterplotColorLinkerAction.setEnabled(false);
			_species2ScatterplotColorLinkerAction.setEnabled(false);
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
		_simianViewerPlugin.getSimianViewerWidget().borderSelectedCrossspeciesCluster(_selectedCrossspeciescluster.getString());

		if (_selectedCrossspeciescluster.getString() == "")
			
		{
			//if (_crossSpeciesFilterAction.getCurrentText() == "cross-species clusters")
			//{
				if (_crossSpecies1DatasetLinkerAction.getCurrentText() != "")
				{
					auto dataset1 = _crossSpecies1DatasetLinkerAction.getCurrentDataset();
					const auto candidateDataset1 = _core->requestDataset<Clusters>(dataset1.getDatasetGuid());
					std::vector<std::uint32_t> selectedIndices1;



					candidateDataset1->getParent()->setSelectionIndices(selectedIndices1);


					events().notifyDatasetSelectionChanged(candidateDataset1->getParent());

				}
				if (_crossSpecies2DatasetLinkerAction.getCurrentText() != "")
				{
					auto dataset2 = _crossSpecies2DatasetLinkerAction.getCurrentDataset();
					const auto candidateDataset2 = _core->requestDataset<Clusters>(dataset2.getDatasetGuid());
					std::vector<std::uint32_t> selectedIndices2;


					candidateDataset2->getParent()->setSelectionIndices(selectedIndices2);
					events().notifyDatasetSelectionChanged(candidateDataset2->getParent());
				}
			//}
			//else
			//{
			//	if (_inSpecies1DatasetLinkerAction.getCurrentText() != "")
			//	{
			//		auto dataset1 = _inSpecies1DatasetLinkerAction.getCurrentDataset();
			//		const auto candidateDataset1 = _core->requestDataset<Clusters>(dataset1.getDatasetGuid());
			//		std::vector<std::uint32_t> selectedIndices1;



			//		candidateDataset1->getParent()->setSelectionIndices(selectedIndices1);


			//		events().notifyDatasetSelectionChanged(candidateDataset1->getParent());

			//	}
			//	if (_inSpecies2DatasetLinkerAction.getCurrentText() != "")
			//	{
			//		auto dataset2 = _inSpecies2DatasetLinkerAction.getCurrentDataset();
			//		const auto candidateDataset2 = _core->requestDataset<Clusters>(dataset2.getDatasetGuid());
			//		std::vector<std::uint32_t> selectedIndices2;


			//		candidateDataset2->getParent()->setSelectionIndices(selectedIndices2);
			//		events().notifyDatasetSelectionChanged(candidateDataset2->getParent());
			//	}
			//}
		}
		else
		{
			_crossSpecies1HeatMapCellAction.setCurrentText(_selectedCrossspeciescluster.getString());

			_crossSpecies2HeatMapCellAction.setCurrentText(_selectedCrossspeciescluster.getString());

			_selectedCrossSpeciesNameList.setString(_selectedCrossspeciescluster.getString());

			//if (_crossSpeciesFilterAction.getCurrentText() == "cross-species clusters")
			//{
				if (_crossSpecies1DatasetLinkerAction.getCurrentText() != "")
				{
					auto dataset1 = _crossSpecies1DatasetLinkerAction.getCurrentDataset();
					const auto candidateDataset1 = _core->requestDataset<Clusters>(dataset1.getDatasetGuid());
					std::vector<std::uint32_t> selectedIndices1;

					for (const auto& cluster : candidateDataset1->getClusters())
					{
						if (cluster.getName() == _selectedCrossspeciescluster.getString())
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
				if (_crossSpecies2DatasetLinkerAction.getCurrentText() != "")
				{
					auto dataset2 = _crossSpecies2DatasetLinkerAction.getCurrentDataset();
					const auto candidateDataset2 = _core->requestDataset<Clusters>(dataset2.getDatasetGuid());
					std::vector<std::uint32_t> selectedIndices2;
					for (const auto& cluster : candidateDataset2->getClusters())
					{
						if (cluster.getName() == _selectedCrossspeciescluster.getString())
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
			//	if (_inSpecies1DatasetLinkerAction.getCurrentText() != "")
			//	{
			//		auto dataset1 = _inSpecies1DatasetLinkerAction.getCurrentDataset();
			//		const auto candidateDataset1 = _core->requestDataset<Clusters>(dataset1.getDatasetGuid());
			//		std::vector<std::uint32_t> selectedIndices1;

			//		for (const auto& cluster : candidateDataset1->getClusters())
			//		{
			//			if (cluster.getName() == _selectedCrossspeciescluster.getString())
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
			//	if (_inSpecies2DatasetLinkerAction.getCurrentText() != "")
			//	{
			//		auto dataset2 = _inSpecies2DatasetLinkerAction.getCurrentDataset();
			//		const auto candidateDataset2 = _core->requestDataset<Clusters>(dataset2.getDatasetGuid());
			//		std::vector<std::uint32_t> selectedIndices2;
			//		for (const auto& cluster : candidateDataset2->getClusters())
			//		{
			//			if (cluster.getName() == _selectedCrossspeciescluster.getString())
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
		_modifyDifferentialExpressionAutoUpdate.trigger();
	};

	connect(&_selectedCrossspeciescluster, &StringAction::stringChanged, this, updateSelectedCrossspeciescluster);

	//connect(&_crossSpeciesFilterAction, &OptionAction::currentIndexChanged, [this, updateCrossSpeciesFilter](const std::int32_t& currentIndex) {
	//	updateCrossSpeciesFilter();
	//	});

	//connect(&_screenshotAction, &TriggerAction::triggered, this, generateScreenshot);
	//connect(&_multiSelectClusterFilterAction, &OptionsAction::selectedOptionsChanged, [this, multiSelectClusterFilter](const QStringList& currentIndex) {
	//	multiSelectClusterFilter();
	//	});

	//
	connect(&_selectedCrossSpeciesNameList, &StringAction::stringChanged, this, updateSelectedCrossSpeciesNameList);
	connect(&_colorMapAction, &ColorMapAction::imageChanged, this, colormapFilter);

	connect(&_backgroundColoringAction, &ColorAction::colorChanged, this, backgroundColoringFilter);

	connect(&_colorMapAction.getSettingsAction().getHorizontalAxisAction().getRangeAction(), &DecimalRangeAction::rangeChanged, this, updateColorMapRange);

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
	connect(&_geneExpressionDatasetVariant, &VariantAction::variantChanged, this, updateGeneExpressionDatasetVariant);

	connect(&_harHcondelCountString, &StringAction::stringChanged, this, updateHarHcondelCountString);

	connect(&_scatterplotColorControlAction, &OptionAction::currentIndexChanged, this, [this, updateScatterplotColorControl](const std::int32_t& currentIndex)
		{
			updateScatterplotColorControl();
		});
	connect(&_inSpecies1HeatMapCellAction, &OptionAction::currentIndexChanged, this, [this, updateInSpecies1HeatMapCell](const std::int32_t& currentIndex)
		{
			updateInSpecies1HeatMapCell();
		});

	connect(&_inSpecies2HeatMapCellAction, &OptionAction::currentIndexChanged, this, [this, updateInSpecies2HeatMapCell](const std::int32_t& currentIndex)
		{
			updateInSpecies2HeatMapCell();
		});
	connect(&_crossSpecies1HeatMapCellAction, &OptionAction::currentIndexChanged, this, [this, updateCrossSpecies1HeatMapCell](const std::int32_t& currentIndex)
		{
			updateCrossSpecies1HeatMapCell();
		});
	connect(&_crossSpecies2HeatMapCellAction, &OptionAction::currentIndexChanged, this, [this, updateCrossSpecies2HeatMapCell](const std::int32_t& currentIndex)
		{
			updateCrossSpecies2HeatMapCell();
		});
	//connect(&_distanceAction, &IntegralAction::valueChanged, this, [this, updateDistance](const std::int32_t& value)
	//	{
	//		updateDistance();
	//	});
	connect(&_histBarAction, &ToggleAction::toggled, this, [this, updateHistBar](const bool& toggled)
		{
			updateHistBar();
		});
	connect(&_modifyDifferentialExpressionAutoUpdate, &ToggleAction::toggled, this, [this, updateModifyDifferentialExpressionAutoUpdate](const bool& toggled)
		{
			updateModifyDifferentialExpressionAutoUpdate();
		});
	connect(&_removeLinkingOptionMenuFromUIAction, &ToggleAction::toggled, this, [this, updateRemoveLinkingOptionMenuFromUIAction](const bool& toggled)
		{
			updateRemoveLinkingOptionMenuFromUIAction();
		});
	connect(&_fullHeatMapAction, &ToggleAction::toggled, this, [this, updateShowFullHeatmap](const bool& toggled)
		{
			updateShowFullHeatmap();
		});

	//connect(&_explorationModeAction, &ToggleAction::toggled, this, [this, updateShowExplorationMode](const bool& toggled)
	//	{
	//		updateShowExplorationMode();
	//	});
	connect(&_crossSpecies1DatasetLinkerAction, &OptionAction::currentIndexChanged, this, [this, updateCrossSpecies1DatasetLinker](const std::int32_t& value) {
		updateCrossSpecies1DatasetLinker();
		});
	connect(&_crossSpecies2DatasetLinkerAction, &OptionAction::currentIndexChanged, this, [this, updateCrossSpecies2DatasetLinker](const std::int32_t& value) {
		updateCrossSpecies2DatasetLinker();
		});


	connect(&_species1ScatterplotColorLinkerAction, &OptionAction::currentIndexChanged, this, [this, updateSpecies1ScatterplotColorLinker](const std::int32_t& value) {
		updateSpecies1ScatterplotColorLinker();
		});
	connect(&_species2ScatterplotColorLinkerAction, &OptionAction::currentIndexChanged, this, [this, updateSpecies2ScatterplotColorLinker](const std::int32_t& value) {
		updateSpecies2ScatterplotColorLinker();
		});

	connect(&_speciesEmbedding1LinkerAction, &OptionAction::currentIndexChanged, this, [this, updateEmbedding1DatasetLinker](const std::int32_t& value) {
		updateEmbedding1DatasetLinker();
		});
	connect(&_speciesEmbedding2LinkerAction, &OptionAction::currentIndexChanged, this, [this, updateEmbedding2DatasetLinker](const std::int32_t& value) {
		updateEmbedding2DatasetLinker();
		});
	connect(&_species1DEStatsLinkerAction, &OptionAction::currentIndexChanged, this, [this, updateDEStats1DatasetLinker](const std::int32_t& value) {
		updateDEStats1DatasetLinker();
		});
	connect(&_species2DEStatsLinkerAction, &OptionAction::currentIndexChanged, this, [this, updateDEStats2DatasetLinker](const std::int32_t& value) {
		updateDEStats2DatasetLinker();
		});
	connect(&_inSpecies1DatasetLinkerAction, &OptionAction::currentIndexChanged, this, [this, updateInSpecies1DatasetLinker](const std::int32_t& value) {
		updateInSpecies1DatasetLinker();
		});
	connect(&_inSpecies2DatasetLinkerAction, &OptionAction::currentIndexChanged, this, [this, updateInSpecies2DatasetLinker](const std::int32_t& value) {
		updateInSpecies2DatasetLinker();
		});
	updateDatasetPickerAction();

	//	updateData((_species1SelectAction.getCurrentText()).toStdString(), (_species2SelectAction.getCurrentText()).toStdString(), (_neighborhoodAction.getCurrentText()).toStdString());

}

SimianOptionsAction::Widget::Widget(QWidget* parent, SimianOptionsAction* SimianOptionsAction) :
	WidgetActionWidget(parent, SimianOptionsAction, State::Standard)
{

}

void SimianOptionsAction::sendClusterCountInfoToJS()
{
	auto dataset1 = _inSpecies1DatasetLinkerAction.getCurrentDataset();
	auto dataset2 = _inSpecies2DatasetLinkerAction.getCurrentDataset();
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
	if (dataEvent->getType() == hdps::EventType::DataAdded)
	{
		updateDatasetPickerAction();
	}
	if (dataEvent->getType() == hdps::EventType::DataRemoved)
	{
		updateDatasetPickerAction();
	}
	if (dataEvent->getType() == hdps::EventType::DataChildAdded)
	{
		updateDatasetPickerAction();
	}
	if (dataEvent->getType() == hdps::EventType::DataChildRemoved)
	{
		updateDatasetPickerAction();
	}
	if (dataEvent->getType() == hdps::EventType::DataChanged)
	{
		updateDatasetPickerAction();
	}
	if (dataEvent->getType() == hdps::EventType::DataGuiNameChanged)
	{
		updateDatasetPickerAction();
	}
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

		auto& colorMapRangeAction = _colorMapAction.getSettingsAction().getHorizontalAxisAction().getRangeAction();
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
	//_crossSpecies2HeatMapCellAction.initialize(crossSpecies2List, "", "");
	//_crossSpecies1HeatMapCellAction.initialize(crossSpecies1List, "", "");

	//_inSpecies2HeatMapCellAction.initialize(inSpecies2List, "", "");
	//_inSpecies1HeatMapCellAction.initialize(inSpecies1List, "", "");




}



void SimianOptionsAction::updateDatasetPickerAction()
{
	auto colorDatasets = _core->requestAllDataSets();
	_species1ScatterplotColorLinkerAction.setDatasets(colorDatasets);
	_species1ScatterplotColorLinkerAction.setPlaceHolderString("Species1 scatterplot color linker");
	_species2ScatterplotColorLinkerAction.setDatasets(colorDatasets);
	_species2ScatterplotColorLinkerAction.setPlaceHolderString("Species2 scatterplot color linker");


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

	_crossSpecies1DatasetLinkerAction.setDatasets(filteredCrossSpeciesDatasets);
	_crossSpecies1DatasetLinkerAction.setPlaceHolderString("Species1 cross-species clusters");
	_crossSpecies2DatasetLinkerAction.setDatasets(filteredCrossSpeciesDatasets);
	_crossSpecies2DatasetLinkerAction.setPlaceHolderString("Species2 cross-species clusters");
	_inSpecies1DatasetLinkerAction.setDatasets(filteredInSpeciesDatasets);
	_inSpecies1DatasetLinkerAction.setPlaceHolderString("Species1 in-species clusters");
	_inSpecies2DatasetLinkerAction.setDatasets(filteredInSpeciesDatasets);
	_inSpecies2DatasetLinkerAction.setPlaceHolderString("Species2 in-species clusters");

	auto embeddings = _core->requestAllDataSets(QVector<hdps::DataType> {PointType});
	auto filteredEmbeddingDatasets = embeddings;
	for (auto embedding : embeddings)
	{
		std::string str1 = embedding->getGuiName().toStdString();
		std::string str2 = "-10x-";
		if (strstr(str1.c_str(), str2.c_str()))
		{
		}
		else {
			filteredEmbeddingDatasets.removeOne(embedding);
		}
	}

	_speciesEmbedding1LinkerAction.setDatasets(filteredEmbeddingDatasets);
	_speciesEmbedding1LinkerAction.setPlaceHolderString("Embedding1 dataset");
	_speciesEmbedding2LinkerAction.setDatasets(filteredEmbeddingDatasets);
	_speciesEmbedding2LinkerAction.setPlaceHolderString("Embedding2 dataset");
	
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

	_species1DEStatsLinkerAction.setDatasets(filteredDEStatsDatasets);
	_species1DEStatsLinkerAction.setPlaceHolderString("DEStats dataset1");
	_species2DEStatsLinkerAction.setDatasets(filteredDEStatsDatasets);
	_species2DEStatsLinkerAction.setPlaceHolderString("DEStats dataset2");

}



SimianOptionsAction::Species1Holder::Widget::Widget(QWidget* parent, Species1Holder* species1SelectHolder) :
	WidgetActionWidget(parent, species1SelectHolder)
{
	auto& simianOptionsAction = species1SelectHolder->_simianOptionsAction;

	auto selectionSpecies1Widget = simianOptionsAction._species1SelectAction.createWidget(this);
	selectionSpecies1Widget->findChild<QComboBox*>("ComboBox")->setSizeAdjustPolicy(QComboBox::AdjustToContents);
	selectionSpecies1Widget->setMaximumWidth(190);

	auto selectionSpecies1OptionLayout = new QFormLayout();

	selectionSpecies1OptionLayout->setContentsMargins(0, 0, 0, 0);
	selectionSpecies1OptionLayout->addRow(simianOptionsAction._species1SelectAction.createLabelWidget(this), selectionSpecies1Widget);


	setPopupLayout(selectionSpecies1OptionLayout);
}

inline SimianOptionsAction::Species1Holder::Species1Holder(SimianOptionsAction& simianOptionsAction) :
	_simianOptionsAction(simianOptionsAction)
{

}


SimianOptionsAction::Species2Holder::Widget::Widget(QWidget* parent, Species2Holder* species2SelectHolder) :
	WidgetActionWidget(parent, species2SelectHolder)
{
	auto& simianOptionsAction = species2SelectHolder->_simianOptionsAction;

	auto selectionSpecies2Widget = simianOptionsAction._species2SelectAction.createWidget(this);
	selectionSpecies2Widget->findChild<QComboBox*>("ComboBox")->setSizeAdjustPolicy(QComboBox::AdjustToContents);
	selectionSpecies2Widget->setMaximumWidth(190);

	auto selectionSpecies2OptionLayout = new QFormLayout();

	selectionSpecies2OptionLayout->setContentsMargins(0, 0, 0, 0);
	selectionSpecies2OptionLayout->addRow(simianOptionsAction._species2SelectAction.createLabelWidget(this), selectionSpecies2Widget);


	setPopupLayout(selectionSpecies2OptionLayout);
}

inline SimianOptionsAction::Species2Holder::Species2Holder(SimianOptionsAction& simianOptionsAction) :
	_simianOptionsAction(simianOptionsAction)
{

}

SimianOptionsAction::CellCountHolder::Widget::Widget(QWidget* parent, CellCountHolder* cellCountHolder) :
	WidgetActionWidget(parent, cellCountHolder)
{
	auto& simianOptionsAction = cellCountHolder->_simianOptionsAction;

	auto selectionHistBarWidget = simianOptionsAction._histBarAction.createWidget(this);
	selectionHistBarWidget->findChild<QCheckBox*>("Checkbox");
	selectionHistBarWidget->setMaximumWidth(100);

	auto cellCountActionLayout = new QFormLayout();

	cellCountActionLayout->setContentsMargins(0, 0, 0, 0);
	cellCountActionLayout->addRow(simianOptionsAction._histBarAction.createLabelWidget(this), selectionHistBarWidget);


	setPopupLayout(cellCountActionLayout);
}

inline SimianOptionsAction::CellCountHolder::CellCountHolder(SimianOptionsAction& simianOptionsAction) :
	_simianOptionsAction(simianOptionsAction)
{

}

//SimianOptionsAction::ExplorationAction::Widget::Widget(QWidget* parent, ExplorationAction* explorationAction) :
//	WidgetActionWidget(parent, explorationAction)
//{
//	auto& simianOptionsAction = explorationAction->_simianOptionsAction;
//
//	auto explorationModeSelectionWidget = simianOptionsAction._explorationModeAction.createWidget(this);
//	explorationModeSelectionWidget->findChild<QCheckBox*>("Checkbox");
//	explorationModeSelectionWidget->setMaximumWidth(97);
//
//	auto explorationModeSelectionLayout = new QFormLayout();
//
//	explorationModeSelectionLayout->setContentsMargins(0, 0, 0, 0);
//	explorationModeSelectionLayout->addRow("Exploration:", explorationModeSelectionWidget);
//
//
//	setPopupLayout(explorationModeSelectionLayout);
//}
//
//inline SimianOptionsAction::ExplorationAction::ExplorationAction(SimianOptionsAction& simianOptionsAction) :
//	_simianOptionsAction(simianOptionsAction)
//{
//
//}


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

SimianOptionsAction::VisSettingHolder::Widget::Widget(QWidget* parent, VisSettingHolder* visSettingHolder) :
	WidgetActionWidget(parent, visSettingHolder)
{
	auto& simianOptionsAction = visSettingHolder->_simianOptionsAction;

	auto fullHeatMapSelectionWidget = simianOptionsAction._fullHeatMapAction.createWidget(this);
	fullHeatMapSelectionWidget->findChild<QCheckBox*>("Checkbox");
	fullHeatMapSelectionWidget->setFixedWidth(200);

	//auto filterCrossSpeciesWidget = simianOptionsAction._crossSpeciesFilterAction.createWidget(this);
	//filterCrossSpeciesWidget->findChild<QComboBox*>("ComboBox")->setSizeAdjustPolicy(QComboBox::AdjustToContents);

	//auto selectScatterplotColorWidget = simianOptionsAction._scatterplotColorControlAction.createWidget(this);
	//selectScatterplotColorWidget->findChild<QComboBox*>("ComboBox")->setSizeAdjustPolicy(QComboBox::AdjustToContents);


	auto backgroundColoringWidget = simianOptionsAction._backgroundColoringAction.createWidget(this);

	auto colorMapWidget = simianOptionsAction._colorMapAction.createWidget(this);



	auto visSettingSelectionLayout = new QFormLayout();
	visSettingSelectionLayout->setContentsMargins(2, 2, 2, 2);
	visSettingSelectionLayout->setObjectName("Vis Setting Options");
	visSettingSelectionLayout->setSpacing(2);
	visSettingSelectionLayout->setVerticalSpacing(2);
	//visSettingSelectionLayout->addRow(simianOptionsAction._crossSpeciesFilterAction.createLabelWidget(this), filterCrossSpeciesWidget);
	visSettingSelectionLayout->addRow(simianOptionsAction._fullHeatMapAction.createLabelWidget(this), fullHeatMapSelectionWidget);
	visSettingSelectionLayout->addRow(simianOptionsAction._colorMapAction.createLabelWidget(this), colorMapWidget);
	//visSettingSelectionLayout->addRow(simianOptionsAction._scatterplotColorControlAction.createLabelWidget(this), selectScatterplotColorWidget);
	visSettingSelectionLayout->addRow(simianOptionsAction._backgroundColoringAction.createLabelWidget(this), backgroundColoringWidget);

	setPopupLayout(visSettingSelectionLayout);

}

inline SimianOptionsAction::VisSettingHolder::VisSettingHolder(SimianOptionsAction& simianOptionsAction) :
	_simianOptionsAction(simianOptionsAction)
{
	setText("Setting Options");
	setIcon(Application::getIconFont("FontAwesome").getIcon("cog"));
}


SimianOptionsAction::LinkerSettingHolder::Widget::Widget(QWidget* parent, LinkerSettingHolder* linkerSettingHolder) :
	WidgetActionWidget(parent, linkerSettingHolder)
{
	auto& simianOptionsAction = linkerSettingHolder->_simianOptionsAction;

	//auto selectionCrossSpecies1DatasetLinkerWidget = simianOptionsAction._crossSpecies1DatasetLinkerAction.createWidget(this);
	//selectionCrossSpecies1DatasetLinkerWidget->setFixedWidth(300);
	//selectionCrossSpecies1DatasetLinkerWidget->findChild<QComboBox*>("ComboBox")->setSizeAdjustPolicy(QComboBox::AdjustToContents);

	//auto selectionCrossSpecies2DatasetLinkerWidget = simianOptionsAction._crossSpecies2DatasetLinkerAction.createWidget(this);
	//selectionCrossSpecies2DatasetLinkerWidget->setFixedWidth(300);
	//selectionCrossSpecies2DatasetLinkerWidget->findChild<QComboBox*>("ComboBox")->setSizeAdjustPolicy(QComboBox::AdjustToContents);


	//auto selectionSpecies1ScatterplotColorLinkerWidget = simianOptionsAction._species1ScatterplotColorLinkerAction.createWidget(this);
	//selectionSpecies1ScatterplotColorLinkerWidget->setFixedWidth(300);
	//selectionSpecies1ScatterplotColorLinkerWidget->findChild<QComboBox*>("ComboBox")->setSizeAdjustPolicy(QComboBox::AdjustToContents);

	//auto selectionSpecies2ScatterplotColorLinkerWidget = simianOptionsAction._species2ScatterplotColorLinkerAction.createWidget(this);
	//selectionSpecies2ScatterplotColorLinkerWidget->setFixedWidth(300);
	//selectionSpecies2ScatterplotColorLinkerWidget->findChild<QComboBox*>("ComboBox")->setSizeAdjustPolicy(QComboBox::AdjustToContents);



	//auto selectionEmbedding1DatasetLinkerWidget = simianOptionsAction._speciesEmbedding1LinkerAction.createWidget(this);
	//selectionEmbedding1DatasetLinkerWidget->setFixedWidth(300);
	//selectionEmbedding1DatasetLinkerWidget->findChild<QComboBox*>("ComboBox")->setSizeAdjustPolicy(QComboBox::AdjustToContents);

	//auto selectionEmbedding2DatasetLinkerWidget = simianOptionsAction._speciesEmbedding2LinkerAction.createWidget(this);
	//selectionEmbedding2DatasetLinkerWidget->setFixedWidth(300);
	//selectionEmbedding2DatasetLinkerWidget->findChild<QComboBox*>("ComboBox")->setSizeAdjustPolicy(QComboBox::AdjustToContents);


	//auto selectionDEStat2DatasetLinkerWidget = simianOptionsAction._species2DEStatsLinkerAction.createWidget(this);
	//selectionDEStat2DatasetLinkerWidget->setFixedWidth(300);
	//selectionDEStat2DatasetLinkerWidget->findChild<QComboBox*>("ComboBox")->setSizeAdjustPolicy(QComboBox::AdjustToContents);

	//auto selectionDEStat1DatasetLinkerWidget = simianOptionsAction._species1DEStatsLinkerAction.createWidget(this);
	//selectionDEStat1DatasetLinkerWidget->setFixedWidth(300);
	//selectionDEStat1DatasetLinkerWidget->findChild<QComboBox*>("ComboBox")->setSizeAdjustPolicy(QComboBox::AdjustToContents);

	//auto selectionInSpecies1DatasetLinkerWidget = simianOptionsAction._inSpecies1DatasetLinkerAction.createWidget(this);
	//selectionInSpecies1DatasetLinkerWidget->setFixedWidth(300);
	//selectionInSpecies1DatasetLinkerWidget->findChild<QComboBox*>("ComboBox")->setSizeAdjustPolicy(QComboBox::AdjustToContents);

	//auto selectionInSpecies2DatasetLinkerWidget = simianOptionsAction._inSpecies2DatasetLinkerAction.createWidget(this);
	//selectionInSpecies2DatasetLinkerWidget->setFixedWidth(300);
	//selectionInSpecies2DatasetLinkerWidget->findChild<QComboBox*>("ComboBox")->setSizeAdjustPolicy(QComboBox::AdjustToContents);


	//auto selectionInSpecies1HeatMapCellWidget = simianOptionsAction._inSpecies1HeatMapCellAction.createWidget(this);
	//selectionInSpecies1HeatMapCellWidget->setFixedWidth(300);
	//selectionInSpecies1HeatMapCellWidget->findChild<QComboBox*>("ComboBox")->setSizeAdjustPolicy(QComboBox::AdjustToContents);
	//auto selectionInSpecies2HeatMapCellWidget = simianOptionsAction._inSpecies2HeatMapCellAction.createWidget(this);
	//selectionInSpecies2HeatMapCellWidget->setFixedWidth(300);
	//selectionInSpecies2HeatMapCellWidget->findChild<QComboBox*>("ComboBox")->setSizeAdjustPolicy(QComboBox::AdjustToContents);
	//auto selectionCrossSpecies1HeatMapCellWidget = simianOptionsAction._crossSpecies1HeatMapCellAction.createWidget(this);
	//selectionCrossSpecies1HeatMapCellWidget->setFixedWidth(300);
	//selectionCrossSpecies1HeatMapCellWidget->findChild<QComboBox*>("ComboBox")->setSizeAdjustPolicy(QComboBox::AdjustToContents);
	//auto selectionCrossSpecies2HeatMapCellWidget = simianOptionsAction._crossSpecies2HeatMapCellAction.createWidget(this);
	//selectionCrossSpecies2HeatMapCellWidget->setFixedWidth(300);
	//selectionCrossSpecies2HeatMapCellWidget->findChild<QComboBox*>("ComboBox")->setSizeAdjustPolicy(QComboBox::AdjustToContents);

		auto autoUpdateWidget = simianOptionsAction._modifyDifferentialExpressionAutoUpdate.createWidget(this);
		//autoUpdateWidget->findChild<QPushButton*>("");
		//autoUpdateWidget->setMaximumWidth(91);

		auto harHcondelCountStringWidget = simianOptionsAction._harHcondelCountString.createWidget(this);
		//geneExpressionDatasetVariantWidget->findChild<QPushButton*>("");
		//geneExpressionDatasetVariantWidget->setMaximumWidth(91);

		auto geneExpressionDatasetVariantWidget = simianOptionsAction._geneExpressionDatasetVariant.createWidget(this);

	auto removeLinkingOptionMenuFromUIActionWidget = simianOptionsAction._removeLinkingOptionMenuFromUIAction.createWidget(this);
	removeLinkingOptionMenuFromUIActionWidget->findChild<QCheckBox*>("Checkbox");
	removeLinkingOptionMenuFromUIActionWidget->setMaximumWidth(91);

	auto linkerSettingSelectionLayout = new QFormLayout();
	linkerSettingSelectionLayout->setContentsMargins(2, 2, 2, 2);
	linkerSettingSelectionLayout->setObjectName("Linker Setting Options");
	linkerSettingSelectionLayout->setSpacing(2);
	linkerSettingSelectionLayout->setVerticalSpacing(2);
	/*linkerSettingSelectionLayout->addRow(simianOptionsAction._crossSpecies1DatasetLinkerAction.createLabelWidget(this), selectionCrossSpecies1DatasetLinkerWidget);
	linkerSettingSelectionLayout->addRow(simianOptionsAction._crossSpecies2DatasetLinkerAction.createLabelWidget(this), selectionCrossSpecies2DatasetLinkerWidget);

	linkerSettingSelectionLayout->addRow(simianOptionsAction._species1ScatterplotColorLinkerAction.createLabelWidget(this), selectionSpecies1ScatterplotColorLinkerWidget);
	linkerSettingSelectionLayout->addRow(simianOptionsAction._species2ScatterplotColorLinkerAction.createLabelWidget(this), selectionSpecies2ScatterplotColorLinkerWidget);

	linkerSettingSelectionLayout->addRow(simianOptionsAction._speciesEmbedding1LinkerAction.createLabelWidget(this), selectionEmbedding1DatasetLinkerWidget);
	linkerSettingSelectionLayout->addRow(simianOptionsAction._speciesEmbedding2LinkerAction.createLabelWidget(this), selectionEmbedding2DatasetLinkerWidget);

	linkerSettingSelectionLayout->addRow(simianOptionsAction._species1DEStatsLinkerAction.createLabelWidget(this), selectionDEStat1DatasetLinkerWidget);

	linkerSettingSelectionLayout->addRow(simianOptionsAction._species2DEStatsLinkerAction.createLabelWidget(this), selectionDEStat2DatasetLinkerWidget);


	linkerSettingSelectionLayout->addRow(simianOptionsAction._inSpecies1DatasetLinkerAction.createLabelWidget(this), selectionInSpecies1DatasetLinkerWidget);
	linkerSettingSelectionLayout->addRow(simianOptionsAction._inSpecies2DatasetLinkerAction.createLabelWidget(this), selectionInSpecies2DatasetLinkerWidget);

	linkerSettingSelectionLayout->addRow(simianOptionsAction._inSpecies1HeatMapCellAction.createLabelWidget(this), selectionInSpecies1HeatMapCellWidget);
	linkerSettingSelectionLayout->addRow(simianOptionsAction._inSpecies2HeatMapCellAction.createLabelWidget(this), selectionInSpecies2HeatMapCellWidget);
	linkerSettingSelectionLayout->addRow(simianOptionsAction._crossSpecies1HeatMapCellAction.createLabelWidget(this), selectionCrossSpecies1HeatMapCellWidget);
	linkerSettingSelectionLayout->addRow(simianOptionsAction._crossSpecies2HeatMapCellAction.createLabelWidget(this), selectionCrossSpecies2HeatMapCellWidget);
*/
	linkerSettingSelectionLayout->addRow(simianOptionsAction._modifyDifferentialExpressionAutoUpdate.createLabelWidget(this), autoUpdateWidget);

	linkerSettingSelectionLayout->addRow(simianOptionsAction._geneExpressionDatasetVariant.createLabelWidget(this), geneExpressionDatasetVariantWidget);

	linkerSettingSelectionLayout->addRow(simianOptionsAction._harHcondelCountString.createLabelWidget(this), harHcondelCountStringWidget);

	linkerSettingSelectionLayout->addRow("Hide menu:", removeLinkingOptionMenuFromUIActionWidget);


	setPopupLayout(linkerSettingSelectionLayout);

}

inline SimianOptionsAction::LinkerSettingHolder::LinkerSettingHolder(SimianOptionsAction& simianOptionsAction) :
	_simianOptionsAction(simianOptionsAction)
{
	setText("Linker Setting Options");
	setIcon(Application::getIconFont("FontAwesome").getIcon("database"));
}



SimianOptionsAction::DistanceNeighborhoodHolder::Widget::Widget(QWidget* parent, DistanceNeighborhoodHolder* distanceNeighborhoodHolder) :
	WidgetActionWidget(parent, distanceNeighborhoodHolder)
{
	auto& simianOptionsAction = distanceNeighborhoodHolder->_simianOptionsAction;

	auto selectionNeighborhoodWidget = simianOptionsAction._neighborhoodAction.createWidget(this);
	selectionNeighborhoodWidget->findChild<QComboBox*>("ComboBox")->setSizeAdjustPolicy(QComboBox::AdjustToContents);

	selectionNeighborhoodWidget->setMaximumWidth(180);


	auto filterOptionLayout = new QFormLayout();

	filterOptionLayout->setContentsMargins(0, 0, 0, 0);
	filterOptionLayout->addRow(simianOptionsAction._neighborhoodAction.createLabelWidget(this), selectionNeighborhoodWidget);


	setPopupLayout(filterOptionLayout);
}

inline SimianOptionsAction::DistanceNeighborhoodHolder::DistanceNeighborhoodHolder(SimianOptionsAction& simianOptionsAction) :
	_simianOptionsAction(simianOptionsAction)
{

}


SimianOptionsAction::ScatterplotColorHolder::Widget::Widget(QWidget* parent, ScatterplotColorHolder* scatterplotColorHolder) :
	WidgetActionWidget(parent, scatterplotColorHolder)
{
	auto& simianOptionsAction = scatterplotColorHolder->_simianOptionsAction;

	auto scatterplotColorChooseWidget = simianOptionsAction._scatterplotColorControlAction.createWidget(this);
	scatterplotColorChooseWidget->findChild<QComboBox*>("ComboBox")->setSizeAdjustPolicy(QComboBox::AdjustToContents);
	scatterplotColorChooseWidget->setMaximumWidth(150);

	auto fsscatterplotColorOptionLayout = new QFormLayout();

	fsscatterplotColorOptionLayout->setContentsMargins(0, 0, 0, 0);
	fsscatterplotColorOptionLayout->addRow(simianOptionsAction._scatterplotColorControlAction.createLabelWidget(this), scatterplotColorChooseWidget);


	setPopupLayout(fsscatterplotColorOptionLayout);
}

inline SimianOptionsAction::ScatterplotColorHolder::ScatterplotColorHolder(SimianOptionsAction& simianOptionsAction) :
	_simianOptionsAction(simianOptionsAction)
{

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
//	auto& colorMapRangeAction = _colorMapAction.getSettingsAction().getHorizontalAxisAction().getRangeAction();
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
	updateData((_species1SelectAction.getCurrentText()).toStdString(), (_species2SelectAction.getCurrentText()).toStdString(), (_neighborhoodAction.getCurrentText()).toStdString());
}

void SimianOptionsAction::fromVariantMap(const QVariantMap& variantMap)
{
	WidgetAction::fromVariantMap(variantMap);

	_species1SelectAction.fromParentVariantMap(variantMap);
	_species2SelectAction.fromParentVariantMap(variantMap);
	_neighborhoodAction.fromParentVariantMap(variantMap);
	_scatterplotColorControlAction.fromParentVariantMap(variantMap);
	//_distanceAction.fromParentVariantMap(variantMap);
	_crossSpecies1DatasetLinkerAction.fromParentVariantMap(variantMap);
	_crossSpecies2DatasetLinkerAction.fromParentVariantMap(variantMap);
	_species1ScatterplotColorLinkerAction.fromParentVariantMap(variantMap);
	_species2ScatterplotColorLinkerAction.fromParentVariantMap(variantMap);
	_speciesEmbedding1LinkerAction.fromParentVariantMap(variantMap);
	_speciesEmbedding2LinkerAction.fromParentVariantMap(variantMap);
	_species1DEStatsLinkerAction.fromParentVariantMap(variantMap);
	_species2DEStatsLinkerAction.fromParentVariantMap(variantMap);
	_inSpecies1DatasetLinkerAction.fromParentVariantMap(variantMap);
	_inSpecies2DatasetLinkerAction.fromParentVariantMap(variantMap);
	//_crossSpeciesFilterAction.fromParentVariantMap(variantMap);
	_inSpecies1HeatMapCellAction.fromParentVariantMap(variantMap);
	_inSpecies2HeatMapCellAction.fromParentVariantMap(variantMap);
	_crossSpecies1HeatMapCellAction.fromParentVariantMap(variantMap);
	_crossSpecies2HeatMapCellAction.fromParentVariantMap(variantMap);
	_colorMapAction.fromParentVariantMap(variantMap);
	_backgroundColoringAction.fromParentVariantMap(variantMap);
	_histBarAction.fromParentVariantMap(variantMap);
	_modifyDifferentialExpressionAutoUpdate.fromParentVariantMap(variantMap);
	_removeLinkingOptionMenuFromUIAction.fromParentVariantMap(variantMap);
	_fullHeatMapAction.fromParentVariantMap(variantMap);
	_species1Name.fromParentVariantMap(variantMap);
	_species2Name.fromParentVariantMap(variantMap);
	_selectedCrossspeciescluster.fromParentVariantMap(variantMap);
	_geneExpressionDatasetVariant.fromParentVariantMap(variantMap);
	_selectedCrossSpeciesNameList.fromParentVariantMap(variantMap);
	_scatterplotColorMapAction.fromParentVariantMap(variantMap);
	_harHcondelCountString.fromParentVariantMap(variantMap);

}

QVariantMap SimianOptionsAction::toVariantMap() const
{
	QVariantMap variantMap = WidgetAction::toVariantMap();

	_species1SelectAction.insertIntoVariantMap(variantMap);
	_species2SelectAction.insertIntoVariantMap(variantMap);
	_neighborhoodAction.insertIntoVariantMap(variantMap);
	_scatterplotColorControlAction.insertIntoVariantMap(variantMap);
	//_distanceAction.insertIntoVariantMap(variantMap);
	_crossSpecies1DatasetLinkerAction.insertIntoVariantMap(variantMap);
	_crossSpecies2DatasetLinkerAction.insertIntoVariantMap(variantMap);
	_species1ScatterplotColorLinkerAction.insertIntoVariantMap(variantMap);
	_species2ScatterplotColorLinkerAction.insertIntoVariantMap(variantMap);
	_speciesEmbedding1LinkerAction.insertIntoVariantMap(variantMap);
	_speciesEmbedding2LinkerAction.insertIntoVariantMap(variantMap);
	_species1DEStatsLinkerAction.insertIntoVariantMap(variantMap);
	_species2DEStatsLinkerAction.insertIntoVariantMap(variantMap);
	_inSpecies1DatasetLinkerAction.insertIntoVariantMap(variantMap);
	_inSpecies2DatasetLinkerAction.insertIntoVariantMap(variantMap);
	//_crossSpeciesFilterAction.insertIntoVariantMap(variantMap);
	_inSpecies1HeatMapCellAction.insertIntoVariantMap(variantMap);
	_inSpecies2HeatMapCellAction.insertIntoVariantMap(variantMap);
	_crossSpecies1HeatMapCellAction.insertIntoVariantMap(variantMap);
	_crossSpecies2HeatMapCellAction.insertIntoVariantMap(variantMap);
	_colorMapAction.insertIntoVariantMap(variantMap);
	_backgroundColoringAction.insertIntoVariantMap(variantMap);
	_histBarAction.insertIntoVariantMap(variantMap);
	_modifyDifferentialExpressionAutoUpdate.insertIntoVariantMap(variantMap);
	_removeLinkingOptionMenuFromUIAction.insertIntoVariantMap(variantMap);
	_fullHeatMapAction.insertIntoVariantMap(variantMap);
	_species1Name.insertIntoVariantMap(variantMap);
	_species2Name.insertIntoVariantMap(variantMap);
	_selectedCrossspeciescluster.insertIntoVariantMap(variantMap);
	_geneExpressionDatasetVariant.insertIntoVariantMap(variantMap);
	_selectedCrossSpeciesNameList.insertIntoVariantMap(variantMap);
	_scatterplotColorMapAction.insertIntoVariantMap(variantMap);
	_harHcondelCountString.insertIntoVariantMap(variantMap);

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
