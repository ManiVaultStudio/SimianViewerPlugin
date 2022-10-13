#include "SimianOptionsAction.h"
#include "SimianViewerPlugin.h"

using namespace hdps;
using namespace hdps::gui;
const QColor SimianOptionsAction::DEFAULT_CONSTANT_COLOR = qRgb(255, 255, 255);

SimianOptionsAction::SimianOptionsAction(SimianViewerPlugin& simianViewerPlugin, hdps::CoreInterface* core) :
    WidgetAction(&simianViewerPlugin),
    _simianViewerPlugin(simianViewerPlugin),
    _core(core),
    _species1SelectAction(this, "Select species1"),
    _species2SelectAction(this, "Select species2"),
    _neighborhoodAction(this, "Select neighborhood"),
    _scatterplotColorControlAction(this, "Scatterplot color"),
    _distanceAction(this, "Filter distance :"),
    _crossSpecies1DatasetLinkerAction(this, "Cross-species cluster dataset1"),
    _crossSpecies2DatasetLinkerAction(this, "Cross-species  cluster dataset2"),

    _species1ScatterplotColorLinkerAction(this, "Scatterplot color linker species1"),
    _species2ScatterplotColorLinkerAction(this, "Scatterplot color linker species2"),

    _speciesEmbedding1LinkerAction(this, "Embedding dataset1"),
    _speciesEmbedding2LinkerAction(this, "Embedding dataset2"),

    _inSpecies1DatasetLinkerAction(this, "In-species  cluster dataset1"),
    _inSpecies2DatasetLinkerAction(this, "In-species  cluster dataset2"),
    _crossSpeciesFilterAction(this, "Filter clusters"),
    _inSpecies1HeatMapCellAction(this, "Link in-species1 heatmap cell"),
    _inSpecies2HeatMapCellAction(this, "Link in-species2 heatmap cell"),
    _crossSpecies1HeatMapCellAction(this, "Link cross-species1 heatmap cell"),
    _crossSpecies2HeatMapCellAction(this, "Link cross-species2 heatmap cell"),
    _multiSelectClusterFilterAction(this, "Select cross-species clusters"),
    _colorMapAction(this, "Select color map"),
    _backgroundColoringAction(this, "Select background color", DEFAULT_CONSTANT_COLOR, DEFAULT_CONSTANT_COLOR),
    _isLoading(false),
    _species1Action(*this),
    _species2Action(*this),
    _clusterAction(*this), 
    _visSettingAction(*this),
    _linkerSettingAction(*this),
    _distanceNeighborhoodAction(*this),
    _isStarted(false),
    _histBarAction(this),
    _fullHeatMapAction(this),
    _explorationModeAction(this)
{
    _eventListener.setEventCore(core);
    _eventListener.addSupportedEventType(static_cast<std::uint32_t>(EventType::DataAdded));
    _eventListener.addSupportedEventType(static_cast<std::uint32_t>(EventType::DataRemoved));
    _eventListener.addSupportedEventType(static_cast<std::uint32_t>(EventType::DataChildAdded));
    _eventListener.addSupportedEventType(static_cast<std::uint32_t>(EventType::DataChildRemoved));
    _eventListener.addSupportedEventType(static_cast<std::uint32_t>(EventType::DataChanged));
    _eventListener.addSupportedEventType(static_cast<std::uint32_t>(EventType::DataGuiNameChanged));
    _eventListener.registerDataEventByType(PointType, std::bind(&SimianOptionsAction::onDataEvent, this, std::placeholders::_1));
    //_histBarAction.setToolTip("Show histogram bars");
    //_fullHeatMapAction.setToolTip("Show full Heatmap");
    //_explorationModeAction.setToolTip("Exploration mode");
    _metaData = new FetchMetaData();
     _metaData->getData(&_simianData);
    _species2SelectAction.setEnabled(false);
    _neighborhoodAction.setEnabled(false);
    _distanceAction.setEnabled(false);
    _distanceAction.setVisible(false);
    _histBarAction.setEnabled(false);
    _fullHeatMapAction.setEnabled(false);
    _explorationModeAction.setEnabled(false);
    _crossSpecies1DatasetLinkerAction.setEnabled(false);
    _crossSpecies2DatasetLinkerAction.setEnabled(false);
    _species1ScatterplotColorLinkerAction.setEnabled(false);
    _species2ScatterplotColorLinkerAction.setEnabled(false);
    _scatterplotColorControlAction.setEnabled(false);
    _speciesEmbedding1LinkerAction.setEnabled(false);
    _speciesEmbedding2LinkerAction.setEnabled(false);

    _inSpecies1DatasetLinkerAction.setEnabled(false);
    _inSpecies2DatasetLinkerAction.setEnabled(false);
    _crossSpeciesFilterAction.setEnabled(false);
    //_crossSpecies1HeatMapCellAction.setEnabled(false);
    //_crossSpecies2HeatMapCellAction.setEnabled(false);
    //_inSpecies1HeatMapCellAction.setEnabled(false);
    //_inSpecies2HeatMapCellAction.setEnabled(false);
    _multiSelectClusterFilterAction.setEnabled(false);
    _colorMapAction.setEnabled(false);
    _backgroundColoringAction.setEnabled(false);
    _clusterAction.setEnabled(false);
    _visSettingAction.setEnabled(false);
    _linkerSettingAction.setEnabled(false);
    _distanceNeighborhoodAction.setEnabled(false);
    _species1SelectAction.setDefaultWidgetFlags(OptionAction::ComboBox);
    _species1SelectAction.setPlaceHolderString(QString("Choose Species1"));
    _species1SelectAction.initialize(QStringList({ "chimp","gorilla","human","rhesus","marmoset"}), _species1SelectAction.getPlaceholderString(), _species1SelectAction.getPlaceholderString());
    _species2SelectAction.setDefaultWidgetFlags(OptionAction::ComboBox);
    _species2SelectAction.setPlaceHolderString(QString("Choose Species2"));
 //   _species2Action.initialize(QStringList({ "gorilla","marmoset","rhesus","chimp","human"}), _species2Action.getPlaceholderString(), _species2Action.getPlaceholderString());
    _crossSpeciesFilterAction.setDefaultWidgetFlags(OptionAction:: ComboBox);
    _crossSpeciesFilterAction.initialize(QStringList({ "all clusters","cross-species clusters" }), "cross-species clusters", "cross-species clusters");
    _inSpecies1HeatMapCellAction.setDefaultWidgetFlags(OptionAction::ComboBox);
    _inSpecies2HeatMapCellAction.setDefaultWidgetFlags(OptionAction::ComboBox);
    _crossSpecies1HeatMapCellAction.setDefaultWidgetFlags(OptionAction::ComboBox);
    _crossSpecies2HeatMapCellAction.setDefaultWidgetFlags(OptionAction::ComboBox);
    _multiSelectClusterFilterAction.setDefaultWidgetFlags(OptionsAction::ComboBox | OptionsAction::ListView | OptionsAction::Selection | OptionsAction::File);
    _multiSelectClusterFilterAction.initialize(QStringList{ "" });
    _multiSelectClusterFilterAction.setSelectedOptions(QStringList());
    _colorMapAction.initialize("Black to white","Black to white");
    _backgroundColoringAction.initialize(DEFAULT_CONSTANT_COLOR, DEFAULT_CONSTANT_COLOR);
    _neighborhoodAction.setDefaultWidgetFlags(OptionAction::ComboBox);
    _neighborhoodAction.initialize(QStringList({ "glia","it_types","l5et_l56np_l6ct_l6b","lamp5_sncg_vip","sst_sst_chodl_pvalb" }), "glia", "glia");
    _scatterplotColorControlAction.setDefaultWidgetFlags(OptionAction::ComboBox);
    _scatterplotColorControlAction.initialize(QStringList({ "in-species class","in-species cluster","cross-species class","cross-species cluster","cross-species sub-class","donor","neighborhood","sex","in-species subclass","constant"}), "constant", "constant");
    
    _distanceAction.setDefaultWidgetFlags(IntegralAction::SpinBox | IntegralAction::Slider);
    _distanceAction.initialize(0, 105, 105, 105); 
    _histBarAction.setDefaultWidgetFlags(ToggleAction::CheckBox);
    _histBarAction.initialize(false,false);
    _fullHeatMapAction.setDefaultWidgetFlags(ToggleAction::CheckBox);
    _fullHeatMapAction.initialize(false, false);
    _explorationModeAction.setDefaultWidgetFlags(ToggleAction::CheckBox);
    _explorationModeAction.initialize(false, false);
    _crossSpecies1DatasetLinkerAction.setDefaultWidgetFlags(OptionAction::ComboBox);
    _crossSpecies2DatasetLinkerAction.setDefaultWidgetFlags(OptionAction::ComboBox);
    
    _species1ScatterplotColorLinkerAction.setDefaultWidgetFlags(OptionAction::ComboBox);
    _species2ScatterplotColorLinkerAction.setDefaultWidgetFlags(OptionAction::ComboBox);

    _speciesEmbedding1LinkerAction.setDefaultWidgetFlags(OptionAction::ComboBox);
    _speciesEmbedding2LinkerAction.setDefaultWidgetFlags(OptionAction::ComboBox);
    
    _inSpecies1DatasetLinkerAction.setDefaultWidgetFlags(OptionAction::ComboBox);
    _inSpecies2DatasetLinkerAction.setDefaultWidgetFlags(OptionAction::ComboBox);
    _colorMapAction.getSettingsAction().getDiscreteAction().setVisible(false);
    _colorMapAction.getSettingsAction().getEditor1DAction().setVisible(false);

    //if (!_inSpecies1DatasetLinkerAction.isPublished())
    //{
    //    _inSpecies1DatasetLinkerAction.publish("InSpeciesDataset1");
    //}
    //if (!_inSpecies2DatasetLinkerAction.isPublished())
    //{
    //    _inSpecies2DatasetLinkerAction.publish("InSpeciesDataset2");
    //}
    if (!_crossSpecies1DatasetLinkerAction.isPublished())
    {
        _crossSpecies1DatasetLinkerAction.publish("CrossSpeciesDataset1");
    }
    if (!_crossSpecies2DatasetLinkerAction.isPublished())
    {
        _crossSpecies2DatasetLinkerAction.publish("CrossSpeciesDataset2");
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
    _inSpecies1DatasetLinkerAction.setVisible(false);
    _inSpecies2DatasetLinkerAction.setVisible(false);
    _crossSpecies1DatasetLinkerAction.setVisible(false);
    _crossSpecies2DatasetLinkerAction.setVisible(false);
    _species1ScatterplotColorLinkerAction.setVisible(false);
    _species2ScatterplotColorLinkerAction.setVisible(false);
    _speciesEmbedding1LinkerAction.setVisible(false);
    _speciesEmbedding2LinkerAction.setVisible(false);
    _inSpecies1HeatMapCellAction.setVisible(false);
    _inSpecies2HeatMapCellAction.setVisible(false);
   
    const auto updateCrossSpeciesFilter = [this]() -> void
    {
        updateDatasetPickerAction();
        if ((_crossSpeciesFilterAction.getCurrentText()).toStdString()=="all clusters")
        {
            _multiSelectClusterFilterAction.setEnabled(false);
            _multiSelectClusterFilterAction.setSelectedOptions(QStringList());
        }
        else {
            _multiSelectClusterFilterAction.setEnabled(true);
        }
        updateData((_species1SelectAction.getCurrentText()).toStdString(), (_species2SelectAction.getCurrentText()).toStdString(), (_neighborhoodAction.getCurrentText()).toStdString(), (_distanceAction.getValue()),(_crossSpeciesFilterAction.getCurrentText()).toStdString());



    };

    const auto multiSelectClusterFilter = [this]() -> void
    {
        if (_isStarted)
        {
            if ((_crossSpeciesFilterAction.getCurrentText()).toStdString() == "cross-species clusters")
            {
                filterMultiSelect();
            }         
        }
    };

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
        std::string full = s1+s2+s3;
        _simianViewerPlugin.getWidget()->setColor(QString::fromStdString(full));
    };
    const auto backgroundColoringFilter = [this]() -> void
    {
        const auto& color= _backgroundColoringAction.getColor();
        //const auto& colorName=  color.name().toStdString();
        _simianViewerPlugin.getWidget()->setBackgroundColor(color.name());
    };
        const auto updateColorMapRange = [this]() -> void
    {
        const auto& rangeAction = _colorMapAction.getSettingsAction().getHorizontalAxisAction().getRangeAction();
        std::string s1 = std::to_string(rangeAction.getMinimum());
        std::string s2 = " ";
        std::string s3 = std::to_string(rangeAction.getMaximum());    
        std::string full = s1.substr(0, s1.find(".") + 3) + s2 + s3.substr(0, s3.find(".") + 3);
        _simianViewerPlugin.getWidget()->setRangeValue(QString::fromStdString(full));
    };

    const auto updateSpecies1 = [this]() -> void
    {
        if (_species1SelectAction.getCurrentText()!="" && _species1SelectAction.getCurrentText().isValidUtf16())
        {
            _species2SelectAction.setEnabled(true);
            if (!_crossSpecies1DatasetLinkerAction.getOptions().isEmpty()) 
            {
                auto datasetOptions1 = _crossSpecies1DatasetLinkerAction.getOptions();
                for (const auto& datasets1 : datasetOptions1)
                {
                    if (datasets1.toLower().contains(_species1SelectAction.getCurrentText().toLower()))
                    {
                        
                        _crossSpecies1DatasetLinkerAction.setCurrentText(datasets1);

                    }
                }
            }

            if (!_inSpecies1DatasetLinkerAction.getOptions().isEmpty())
            {
                auto datasetOptions1 = _inSpecies1DatasetLinkerAction.getOptions();
                for (const auto& datasets1 : datasetOptions1)
                {
                    if (datasets1.toLower().contains( _species1SelectAction.getCurrentText().toLower() ))
                    {

                        _inSpecies1DatasetLinkerAction.setCurrentText(datasets1);
                    }
                }
            }

            if (!_speciesEmbedding1LinkerAction.getOptions().isEmpty())
            {
                auto datasetOptions1 = _speciesEmbedding1LinkerAction.getOptions();
                for (const auto& datasets1 : datasetOptions1)
                {
                    if (datasets1.toLower().contains(_species1SelectAction.getCurrentText().toLower()))
                    {

                        _speciesEmbedding1LinkerAction.setCurrentText(datasets1);
                    }
                }
            }


            if (_species2SelectAction.getCurrentText().isValidUtf16() && _species2SelectAction.getCurrentText() != "")
            {
                    if (_species2SelectAction.getCurrentText() == _species1SelectAction.getCurrentText())
                    {
                        _simianViewerPlugin.getWidget()->resetView("Reset");
                        _species2SelectAction.setCurrentIndex(0);
                        _species2SelectAction.setPlaceHolderString(QString("Choose Species2"));
                        _species2SelectAction.initialize(QStringList({ }), _species2SelectAction.getPlaceholderString(), _species2SelectAction.getPlaceholderString());
                        QStringList speciesNames = { "gorilla","marmoset","rhesus","chimp","human" };
                        speciesNames.removeAll(_species1SelectAction.getCurrentText());
                        _species2SelectAction.initialize(QStringList({ speciesNames }), _species2SelectAction.getPlaceholderString(), _species2SelectAction.getPlaceholderString());




                    }
                    else
                    {
                        QString storeSpecies = _species2SelectAction.getCurrentText();
                        //_species2Action.setPlaceHolderString(QString("Choose Species2"));
                        _species2SelectAction.initialize(QStringList({ }), _species2SelectAction.getPlaceholderString(), _species2SelectAction.getPlaceholderString());
                        QStringList speciesNames = { "gorilla","marmoset","rhesus","chimp","human" };
                        speciesNames.removeAll(_species1SelectAction.getCurrentText());
                        _species2SelectAction.initialize(QStringList({ speciesNames }), _species2SelectAction.getPlaceholderString(), _species2SelectAction.getPlaceholderString());
                        _species2SelectAction.setCurrentText(storeSpecies);
                       QString tempVal = _scatterplotColorControlAction.getCurrentText();
                       _scatterplotColorControlAction.setCurrentText("");
                       _scatterplotColorControlAction.setCurrentText(tempVal);
                        updateData((_species1SelectAction.getCurrentText()).toStdString(), (_species2SelectAction.getCurrentText()).toStdString(), (_neighborhoodAction.getCurrentText()).toStdString(), (_distanceAction.getValue()), (_crossSpeciesFilterAction.getCurrentText()).toStdString());


                    }
            }
            else {
                
                _simianViewerPlugin.getWidget()->resetView("Reset");
                _species2SelectAction.setCurrentIndex(0);
                _species2SelectAction.setPlaceHolderString(QString("Choose Species2"));
                _species2SelectAction.initialize(QStringList({ }), _species2SelectAction.getPlaceholderString(), _species2SelectAction.getPlaceholderString());
                QStringList speciesNames = { "gorilla","marmoset","rhesus","chimp","human" };
                speciesNames.removeAll(_species1SelectAction.getCurrentText());
                _species2SelectAction.initialize(QStringList({ speciesNames }), _species2SelectAction.getPlaceholderString(), _species2SelectAction.getPlaceholderString());
                _scatterplotColorControlAction.setCurrentText("constant");

            }

        }

        else {
            _species2SelectAction.setEnabled(false);
            _neighborhoodAction.setEnabled(false);

            _distanceAction.setEnabled(false);
            _histBarAction.setEnabled(false);
            _fullHeatMapAction.setEnabled(false);
            _explorationModeAction.setEnabled(false);
            _crossSpecies1DatasetLinkerAction.setEnabled(false);
            _crossSpecies2DatasetLinkerAction.setEnabled(false);

            _species1ScatterplotColorLinkerAction.setEnabled(false);
            _species2ScatterplotColorLinkerAction.setEnabled(false);
            _scatterplotColorControlAction.setEnabled(false);
            _speciesEmbedding1LinkerAction.setEnabled(false);
            _speciesEmbedding2LinkerAction.setEnabled(false);
            _inSpecies1DatasetLinkerAction.setEnabled(false);
            _inSpecies2DatasetLinkerAction.setEnabled(false);
            _crossSpeciesFilterAction.setEnabled(false);
            _multiSelectClusterFilterAction.setEnabled(false);
            _multiSelectClusterFilterAction.setSelectedOptions(QStringList());
            _colorMapAction.setEnabled(false);
            _backgroundColoringAction.setEnabled(false);
            _clusterAction.setEnabled(false);
            _visSettingAction.setEnabled(false);
            _linkerSettingAction.setEnabled(false);
            _distanceNeighborhoodAction.setEnabled(false);
        }

    };
    const auto updateSpecies2 = [this]() -> void
    {
        if (_species2SelectAction.getCurrentText().isValidUtf16())
        {
            _neighborhoodAction.setEnabled(true);

            _crossSpecies1DatasetLinkerAction.setEnabled(true);
            _crossSpecies2DatasetLinkerAction.setEnabled(true);

            _speciesEmbedding1LinkerAction.setEnabled(true);
            _speciesEmbedding2LinkerAction.setEnabled(true);
            _inSpecies1DatasetLinkerAction.setEnabled(true);
            _inSpecies2DatasetLinkerAction.setEnabled(true);
            _crossSpeciesFilterAction.setEnabled(true);
            _fullHeatMapAction.setEnabled(true);
            _explorationModeAction.setEnabled(true);
            _multiSelectClusterFilterAction.setEnabled(true);
            _colorMapAction.setEnabled(true);
            _backgroundColoringAction.setEnabled(true);
            _clusterAction.setEnabled(true);
            _visSettingAction.setEnabled(true);
            _linkerSettingAction.setEnabled(true);
            _distanceNeighborhoodAction.setEnabled(true);
            if (!_crossSpecies2DatasetLinkerAction.getOptions().isEmpty())
            {
                auto datasetOptions2 = _crossSpecies2DatasetLinkerAction.getOptions();
                for (const auto& dataset2 : datasetOptions2)
                {
                    if (dataset2.toLower().contains(_species2SelectAction.getCurrentText().toLower()))
                    {

                        _crossSpecies2DatasetLinkerAction.setCurrentText(dataset2);
                    }
                }
            }

            if (!_inSpecies2DatasetLinkerAction.getOptions().isEmpty())
            {
                auto datasetOptions2 = _inSpecies2DatasetLinkerAction.getOptions();
                for (const auto& dataset2 : datasetOptions2)
                {
                    if (dataset2.toLower().contains(_species2SelectAction.getCurrentText().toLower()))
                    {

                        _inSpecies2DatasetLinkerAction.setCurrentText(dataset2);
                    }
                }
            }
            if (!_speciesEmbedding2LinkerAction.getOptions().isEmpty())
            {
                auto datasetOptions2 = _speciesEmbedding2LinkerAction.getOptions();
                for (const auto& datasets2 : datasetOptions2)
                {
                    if (datasets2.toLower().contains(_species2SelectAction.getCurrentText().toLower()))
                    {

                        _speciesEmbedding2LinkerAction.setCurrentText(datasets2);
                    }
                }
            }

        }
        else {
            _neighborhoodAction.setEnabled(false);
            _scatterplotColorControlAction.setEnabled(false);
            _distanceAction.setEnabled(false);
            _histBarAction.setEnabled(false);
            _fullHeatMapAction.setEnabled(false);
            _explorationModeAction.setEnabled(false);
            _crossSpecies1DatasetLinkerAction.setEnabled(false);
            _crossSpecies2DatasetLinkerAction.setEnabled(false);

            _species1ScatterplotColorLinkerAction.setEnabled(false);
            _species2ScatterplotColorLinkerAction.setEnabled(false);

            _speciesEmbedding1LinkerAction.setEnabled(false);
            _speciesEmbedding2LinkerAction.setEnabled(false);
            _inSpecies1DatasetLinkerAction.setEnabled(false);
            _inSpecies2DatasetLinkerAction.setEnabled(false);
            _crossSpeciesFilterAction.setEnabled(false);
            _multiSelectClusterFilterAction.setEnabled(false);
            _multiSelectClusterFilterAction.setSelectedOptions(QStringList());
            _colorMapAction.setEnabled(false);
            _backgroundColoringAction.setEnabled(false);
            _clusterAction.setEnabled(false);
            _visSettingAction.setEnabled(false);
            _linkerSettingAction.setEnabled(false);
            _distanceNeighborhoodAction.setEnabled(false);
        }
        
        if (_species2SelectAction.getCurrentText() != "" && _species2SelectAction.getCurrentText() != "")
        {
            updateData((_species1SelectAction.getCurrentText()).toStdString(), (_species2SelectAction.getCurrentText()).toStdString(), (_neighborhoodAction.getCurrentText()).toStdString(), (_distanceAction.getValue()), (_crossSpeciesFilterAction.getCurrentText()).toStdString());
            QString tempVal = _scatterplotColorControlAction.getCurrentText();
            _scatterplotColorControlAction.setCurrentText("");
            _scatterplotColorControlAction.setCurrentText(tempVal);
        }
    };
    const auto updateNeighborhood = [this]() -> void
    {
        if (_species1SelectAction.getCurrentText() != "" && _species2SelectAction.getCurrentText() != "")
        {
            updateData((_species1SelectAction.getCurrentText()).toStdString(), (_species2SelectAction.getCurrentText()).toStdString(), (_neighborhoodAction.getCurrentText()).toStdString(), (_distanceAction.getValue()), (_crossSpeciesFilterAction.getCurrentText()).toStdString());
        }
    };
    const auto updateScatterplotColorControl = [this]() -> void
    {


        if(_species1ScatterplotColorLinkerAction.getNumberOfOptions()>0 && _species2ScatterplotColorLinkerAction.getNumberOfOptions() > 0)
        {
            if (_scatterplotColorControlAction.getCurrentText() != "" && _scatterplotColorControlAction.getCurrentText().isValidUtf16())
        {
                auto species1SelectedOption = selectFromQStringList(_species1ScatterplotColorLinkerAction.getOptions(), _species1SelectAction.getCurrentText(), _scatterplotColorControlAction.getCurrentText());
                if (species1SelectedOption!="constant")
                {
                    _species1ScatterplotColorLinkerAction.setCurrentText(species1SelectedOption);
                }
                auto species2SelectedOption = selectFromQStringList(_species2ScatterplotColorLinkerAction.getOptions(), _species2SelectAction.getCurrentText(), _scatterplotColorControlAction.getCurrentText());
                if (species2SelectedOption != "constant")
                {
                    _species2ScatterplotColorLinkerAction.setCurrentText(species2SelectedOption);
                }
        }
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

    const auto updateDistance = [this]() -> void
    {
        if (_species1SelectAction.getCurrentText() != "" && _species2SelectAction.getCurrentText() != "")
        {
            updateData((_species1SelectAction.getCurrentText()).toStdString(), (_species2SelectAction.getCurrentText()).toStdString(), (_neighborhoodAction.getCurrentText()).toStdString(), (_distanceAction.getValue()), (_crossSpeciesFilterAction.getCurrentText()).toStdString());
        }
    };
    
        const auto updateHistBar = [this]() -> void
    {
            if (_histBarAction.isChecked())
            {
                _simianViewerPlugin.getWidget()->histChart(QString::fromStdString("T"));
            }
            else
            {
                _simianViewerPlugin.getWidget()->histChart(QString::fromStdString("F"));
            }


    };

        const auto updateShowFullHeatmap = [this]() -> void
        {
            if (_fullHeatMapAction.isChecked())
            {
                _simianViewerPlugin.getWidget()->showFullHeatmap(QString::fromStdString("T"));
            }
            else
            {
                _simianViewerPlugin.getWidget()->showFullHeatmap(QString::fromStdString("F"));
            }


        };
        const auto updateShowExplorationMode = [this]() -> void
        {
            if (_explorationModeAction.isChecked())
            {
                _simianViewerPlugin.getWidget()->showExplorationMode(QString::fromStdString("T"));
            }
            else
            {
                _simianViewerPlugin.getWidget()->showExplorationMode(QString::fromStdString("F"));
            }


        };


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

    const auto updateInSpecies1DatasetLinker = [this]() -> void
    {
        if (_inSpecies1DatasetLinkerAction.getCurrentText()!= "" && _inSpecies2DatasetLinkerAction.getCurrentText() != "")
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
                _scatterplotColorControlAction.setCurrentText("constant");
                //updateHistBar();
            }
        }
        else
        {
            _histBarAction.setEnabled(false);
            _histBarAction.setChecked(false);
            _species1ScatterplotColorLinkerAction.setEnabled(false);
            _species2ScatterplotColorLinkerAction.setEnabled(false);
            _scatterplotColorControlAction.setEnabled(false);
            _scatterplotColorControlAction.setCurrentText("constant");
            //updateHistBar();
        }
    };

    const auto updateInSpecies2DatasetLinker = [this]() -> void
    {
        if (_inSpecies1DatasetLinkerAction.getCurrentText() != "" && _inSpecies2DatasetLinkerAction.getCurrentText() != "")
        {
            sendClusterCountInfoToJS();
            if (_inSpecies1DatasetLinkerAction.getCurrentDataset().isValid()  && _inSpecies2DatasetLinkerAction.getCurrentDataset().isValid())
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
                _scatterplotColorControlAction.setCurrentText("constant");
                //updateHistBar();
            }          
        }
        else
        {
            _histBarAction.setEnabled(false);
            _histBarAction.setChecked(false);
            _species1ScatterplotColorLinkerAction.setEnabled(false);
            _species2ScatterplotColorLinkerAction.setEnabled(false);
            _scatterplotColorControlAction.setEnabled(false);
            _scatterplotColorControlAction.setCurrentText("constant");
            //updateHistBar();
        }
    };

    connect(&_crossSpeciesFilterAction, &OptionAction::currentIndexChanged, [this, updateCrossSpeciesFilter](const std::int32_t& currentIndex) {
        updateCrossSpeciesFilter();
        });

    connect(&_multiSelectClusterFilterAction, &OptionsAction::selectedOptionsChanged, [this, multiSelectClusterFilter](const QStringList& currentIndex) {
        multiSelectClusterFilter();
        });

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
    connect(&_distanceAction, &IntegralAction::valueChanged, this, [this, updateDistance](const std::int32_t& value)
        {
            updateDistance();
        });
    connect(&_histBarAction, &ToggleAction::toggled, this, [this, updateHistBar](const bool& toggled)
        {
            updateHistBar();
        });

    connect(&_fullHeatMapAction, &ToggleAction::toggled, this, [this, updateShowFullHeatmap](const bool& toggled)
        {
            updateShowFullHeatmap();
        });
    
    connect(&_explorationModeAction, &ToggleAction::toggled, this, [this, updateShowExplorationMode](const bool& toggled)
        {
            updateShowExplorationMode();
        });
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
    connect(&_inSpecies1DatasetLinkerAction, &OptionAction::currentIndexChanged, this, [this, updateInSpecies1DatasetLinker](const std::int32_t& value) {
        updateInSpecies1DatasetLinker();
        });
    connect(&_inSpecies2DatasetLinkerAction, &OptionAction::currentIndexChanged, this, [this, updateInSpecies2DatasetLinker](const std::int32_t& value) {
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
    auto dataset1 = _inSpecies1DatasetLinkerAction.getCurrentDataset();
    auto dataset2 = _inSpecies2DatasetLinkerAction.getCurrentDataset();
    const auto candidateDataset1 = _core->requestDataset<Clusters>(dataset1.getDatasetGuid());
    const auto candidateDataset2 = _core->requestDataset<Clusters>(dataset2.getDatasetGuid());
    std::string jsonSend="";
    for (const auto& cluster : candidateDataset1->getClusters())
    {
        //qDebug() << cluster.getName();
        //qDebug() << cluster.getNumberOfIndices();
        jsonSend= jsonSend+ cluster.getName().toStdString();
        jsonSend = jsonSend + "*|*";
        jsonSend = jsonSend + std::to_string(cluster.getNumberOfIndices());
        jsonSend = jsonSend + "*||*";
    }
    jsonSend = jsonSend + "*|||*";
    for (const auto& cluster : candidateDataset2->getClusters())
    {
        //qDebug() << cluster.getName();
        //qDebug() << cluster.getNumberOfIndices();
        jsonSend = jsonSend + cluster.getName().toStdString();
        jsonSend = jsonSend + "*|*";
        jsonSend = jsonSend + std::to_string(cluster.getNumberOfIndices());
        jsonSend = jsonSend + "*||*";
    }


    _simianViewerPlugin.getWidget()->inspeciesClusterCounts(QString::fromStdString(jsonSend) );

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

void SimianOptionsAction::updateData(std::string Species1, std::string Species2, std::string neighborhood, int distance, std::string CrossSpeciesFilter)
{
    _isStarted = false;
    std::vector<std::vector<std::string>>    filteredVisData;


	if (CrossSpeciesFilter == "cross-species clusters")
	{
		for (int i = 0; i < _simianData.size(); i++)

		{
			if (_simianData[i][7] == _simianData[i][8] && _simianData[i][1] == Species1 && _simianData[i][3] == Species2 && _simianData[i][6] == neighborhood && stoi(_simianData[i][5]) < distance)
			{
				std::vector<std::string> temp;
				for (int j = 0; j < _simianData[i].size(); j++)
				{
					temp.push_back(_simianData[i][j]);
				}
				filteredVisData.push_back(temp);
			}
		}
	}
	else
	{
		for (int i = 0; i < _simianData.size(); i++)

		{
			if (_simianData[i][1] == Species1 && _simianData[i][3] == Species2 && _simianData[i][6] == neighborhood && stoi(_simianData[i][5]) < distance)
			{
				std::vector<std::string> temp;
				for (int j = 0; j < _simianData[i].size(); j++)
				{
					temp.push_back(_simianData[i][j]);
				}
				filteredVisData.push_back(temp);
			}
		}
	}

    updateMultiSelectionDropdown(filteredVisData);

    QString _jsonObject;
    _jsonObject += "[";

    QStringList columnNames = { "RowNumber", "species_1", "cluster_1", "species_2", "cluster_2", "dist", "neighborhood", "cross_species_cluster1_species_1", "cross_species_cluster2_species_2", "sortColumn","subclass_1","class_1","subclass_2","class_2"};

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
    _simianViewerPlugin.getWidget()->setData(_jsonObject.toStdString());

    auto& colorMapRangeAction = _colorMapAction.getSettingsAction().getHorizontalAxisAction().getRangeAction();
    float colorMapRangeMin=1200.0;
    float colorMapRangeMax=0.0;
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
        if(!QStringlistContainsQString(inSpecies1List, QString::fromStdString(filteredVisData[i][2])))
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
    _crossSpecies2HeatMapCellAction.initialize(crossSpecies2List, "", "");
_crossSpecies1HeatMapCellAction.initialize(crossSpecies1List, "", "");

_inSpecies2HeatMapCellAction.initialize(inSpecies2List, "", "");
_inSpecies1HeatMapCellAction.initialize(inSpecies1List, "", "");

}



void SimianOptionsAction::updateDatasetPickerAction()
{
    auto datasets = _core->requestAllDataSets(QVector<hdps::DataType> {ClusterType});
    _species1ScatterplotColorLinkerAction.setDatasets(datasets);
    _species1ScatterplotColorLinkerAction.setPlaceHolderString("Species1 scatterplot color linker");
    _species2ScatterplotColorLinkerAction.setDatasets(datasets);
    _species2ScatterplotColorLinkerAction.setPlaceHolderString("Species2 scatterplot color linker");

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
        std::string str2 = "Numerical MetaData";
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

}



SimianOptionsAction::Species1Action::Widget::Widget(QWidget* parent, Species1Action* species1SelectAction) :
    WidgetActionWidget(parent, species1SelectAction)
{
    auto& simianOptionsAction = species1SelectAction->_simianOptionsAction;

    auto selectionSpecies1Widget = simianOptionsAction._species1SelectAction.createWidget(this);
    selectionSpecies1Widget->findChild<QComboBox*>("ComboBox")->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    selectionSpecies1Widget->setMaximumWidth(170);

    auto selectionSpecies1OptionLayout = new QFormLayout();

    selectionSpecies1OptionLayout->setContentsMargins(0, 0, 0, 0);
    selectionSpecies1OptionLayout->addRow("Species1:", selectionSpecies1Widget);


    setPopupLayout(selectionSpecies1OptionLayout);
}

inline SimianOptionsAction::Species1Action::Species1Action(SimianOptionsAction& simianOptionsAction) :
    _simianOptionsAction(simianOptionsAction)
{

}


SimianOptionsAction::Species2Action::Widget::Widget(QWidget* parent, Species2Action* species2SelectAction) :
    WidgetActionWidget(parent, species2SelectAction)
{
    auto& simianOptionsAction = species2SelectAction->_simianOptionsAction;

    auto selectionSpecies2Widget = simianOptionsAction._species2SelectAction.createWidget(this);
    selectionSpecies2Widget->findChild<QComboBox*>("ComboBox")->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    selectionSpecies2Widget->setMaximumWidth(170);

    auto selectionSpecies2OptionLayout = new QFormLayout();

    selectionSpecies2OptionLayout->setContentsMargins(0, 0, 0, 0);
    selectionSpecies2OptionLayout->addRow("Species2:", selectionSpecies2Widget);


    setPopupLayout(selectionSpecies2OptionLayout);
}

inline SimianOptionsAction::Species2Action::Species2Action(SimianOptionsAction& simianOptionsAction) :
    _simianOptionsAction(simianOptionsAction)
{

}







SimianOptionsAction::ColorMapOptionAction::Widget::Widget(QWidget* parent, ColorMapOptionAction* colorMapAction) :
    WidgetActionWidget(parent, colorMapAction)
{
    auto& simianOptionsAction = colorMapAction->_simianOptionsAction;
    auto colorMapWidget = simianOptionsAction._colorMapAction.createWidget(this);
    auto colorSelectionLayout = new QFormLayout();
    colorSelectionLayout->setContentsMargins(2, 2, 2, 2);
    colorSelectionLayout->addRow(simianOptionsAction._colorMapAction.createLabelWidget(this), colorMapWidget);
    colorSelectionLayout->setObjectName("Color Options");
    colorSelectionLayout->setSpacing(2);
    colorSelectionLayout->setVerticalSpacing(2);

    setPopupLayout(colorSelectionLayout);
}

inline SimianOptionsAction::ColorMapOptionAction::ColorMapOptionAction(SimianOptionsAction& simianOptionsAction) :
    _simianOptionsAction(simianOptionsAction)
{
    setText("Color Options");
    setIcon(Application::getIconFont("FontAwesome").getIcon("palette"));
}

//
SimianOptionsAction::BackgroundColorOptionAction::Widget::Widget(QWidget* parent, BackgroundColorOptionAction* colorAction) :
    WidgetActionWidget(parent, colorAction)
{
    auto& simianOptionsAction = colorAction->_simianOptionsAction;
    auto backgroundColoringWidget = simianOptionsAction._backgroundColoringAction.createWidget(this);
    auto backgroundColorSelectionLayout = new QFormLayout();
    backgroundColorSelectionLayout->setContentsMargins(2, 2, 2, 2);
    backgroundColorSelectionLayout->addRow(simianOptionsAction._backgroundColoringAction.createLabelWidget(this), backgroundColoringWidget);
    backgroundColorSelectionLayout->setObjectName("background Color Options");
    backgroundColorSelectionLayout->setSpacing(2);
    backgroundColorSelectionLayout->setVerticalSpacing(2);

    setPopupLayout(backgroundColorSelectionLayout);
}

inline SimianOptionsAction::BackgroundColorOptionAction::BackgroundColorOptionAction(SimianOptionsAction& simianOptionsAction) :
    _simianOptionsAction(simianOptionsAction)
{
    setText("Background color Options");
    setIcon(Application::getIconFont("FontAwesome").getIcon("search"));
}

//


void SimianOptionsAction::updateMultiSelectionDropdown(std::vector<std::vector<std::string>>&    filteredVisData)
{
    std::vector<std::string> store;
    for (int i = 0; i < filteredVisData.size(); i++)

    {
        store.push_back(filteredVisData[i][7]);
        store.push_back(filteredVisData[i][8]);
    }
    sort(store.begin(), store.end());
    store.erase(unique(store.begin(), store.end()), store.end());
    QStringList finalClusters{};
    for (int i = 0; i < store.size(); i++)
    {
        finalClusters.append(QString::fromUtf8((store.at(i)).c_str()));
    }

    _multiSelectClusterFilterAction.initialize(finalClusters);
    _multiSelectClusterFilterAction.setSelectedOptions(finalClusters);


}


SimianOptionsAction::ClusterAction::Widget::Widget(QWidget* parent, ClusterAction* clusterAction) :
    WidgetActionWidget(parent, clusterAction)
{
    auto& simianOptionsAction = clusterAction->_simianOptionsAction;

    auto crossSpeciesClusterSelectionWidget = simianOptionsAction._multiSelectClusterFilterAction.createWidget(this);
    crossSpeciesClusterSelectionWidget->findChild<QComboBox*>("ComboBox")->setSizeAdjustPolicy(QComboBox::AdjustToContents);

    auto crossSpeciesClusterSelectionLayout = new QFormLayout();
    crossSpeciesClusterSelectionLayout->setContentsMargins(2, 2, 2, 2);
    crossSpeciesClusterSelectionLayout->setObjectName("Cluster Options");
    crossSpeciesClusterSelectionLayout->setSpacing(2);
    crossSpeciesClusterSelectionLayout->setVerticalSpacing(2);
    crossSpeciesClusterSelectionLayout->addRow(simianOptionsAction._multiSelectClusterFilterAction.createLabelWidget(this), crossSpeciesClusterSelectionWidget);

    setPopupLayout(crossSpeciesClusterSelectionLayout);
}

inline SimianOptionsAction::ClusterAction::ClusterAction(SimianOptionsAction& simianOptionsAction) :
    _simianOptionsAction(simianOptionsAction)
{
    setText("Cluster Options");
    setIcon(Application::getIconFont("FontAwesome").getIcon("filter"));
}


SimianOptionsAction::VisSettingAction::Widget::Widget(QWidget* parent, VisSettingAction* visSettingAction) :
    WidgetActionWidget(parent, visSettingAction)
{
    auto& simianOptionsAction = visSettingAction->_simianOptionsAction;

    auto fullHeatMapSelectionWidget = simianOptionsAction._fullHeatMapAction.createWidget(this);
    fullHeatMapSelectionWidget->findChild<QCheckBox*>("Checkbox");
    fullHeatMapSelectionWidget->setFixedWidth(100);

    auto explorationModeSelectionWidget = simianOptionsAction._explorationModeAction.createWidget(this);
    explorationModeSelectionWidget->findChild<QCheckBox*>("Checkbox");
    explorationModeSelectionWidget->setFixedWidth(100);

    auto selectionHistBarWidget = simianOptionsAction._histBarAction.createWidget(this);
    selectionHistBarWidget->findChild<QCheckBox*>("Checkbox");
    selectionHistBarWidget->setFixedWidth(100);

    auto filterCrossSpeciesWidget = simianOptionsAction._crossSpeciesFilterAction.createWidget(this);
    filterCrossSpeciesWidget->findChild<QComboBox*>("ComboBox")->setSizeAdjustPolicy(QComboBox::AdjustToContents);

    auto selectScatterplotColorWidget = simianOptionsAction._scatterplotColorControlAction.createWidget(this);
    selectScatterplotColorWidget->findChild<QComboBox*>("ComboBox")->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    
    auto visSettingSelectionLayout = new QFormLayout();
    visSettingSelectionLayout->setContentsMargins(2, 2, 2, 2);
    visSettingSelectionLayout->setObjectName("Vis Setting Options");
    visSettingSelectionLayout->setSpacing(2);
    visSettingSelectionLayout->setVerticalSpacing(2);
    visSettingSelectionLayout->addRow("Cluster filter:", filterCrossSpeciesWidget);
    visSettingSelectionLayout->addRow("Full heatmap:", fullHeatMapSelectionWidget);
    visSettingSelectionLayout->addRow("Exploration mode:", explorationModeSelectionWidget);
    visSettingSelectionLayout->addRow("Cell counts:", selectionHistBarWidget);
    visSettingSelectionLayout->addRow("Scatterplot color:", selectScatterplotColorWidget);

    setPopupLayout(visSettingSelectionLayout);

}

inline SimianOptionsAction::VisSettingAction::VisSettingAction(SimianOptionsAction& simianOptionsAction) :
    _simianOptionsAction(simianOptionsAction)
{
    setText("Vis Setting Options");
    setIcon(Application::getIconFont("FontAwesome").getIcon("cog"));
}


SimianOptionsAction::LinkerSettingAction::Widget::Widget(QWidget* parent, LinkerSettingAction* linkerSettingAction) :
    WidgetActionWidget(parent, linkerSettingAction)
{
    auto& simianOptionsAction = linkerSettingAction->_simianOptionsAction;

    auto selectionCrossSpecies1DatasetLinkerWidget = simianOptionsAction._crossSpecies1DatasetLinkerAction.createWidget(this);
    selectionCrossSpecies1DatasetLinkerWidget->setFixedWidth(300);
    selectionCrossSpecies1DatasetLinkerWidget->findChild<QComboBox*>("ComboBox")->setSizeAdjustPolicy(QComboBox::AdjustToContents);

    auto selectionCrossSpecies2DatasetLinkerWidget = simianOptionsAction._crossSpecies2DatasetLinkerAction.createWidget(this);
    selectionCrossSpecies2DatasetLinkerWidget->setFixedWidth(300);
    selectionCrossSpecies2DatasetLinkerWidget->findChild<QComboBox*>("ComboBox")->setSizeAdjustPolicy(QComboBox::AdjustToContents);


    auto selectionSpecies1ScatterplotColorLinkerWidget = simianOptionsAction._species1ScatterplotColorLinkerAction.createWidget(this);
    selectionSpecies1ScatterplotColorLinkerWidget->setFixedWidth(300);
    selectionSpecies1ScatterplotColorLinkerWidget->findChild<QComboBox*>("ComboBox")->setSizeAdjustPolicy(QComboBox::AdjustToContents);

    auto selectionSpecies2ScatterplotColorLinkerWidget = simianOptionsAction._species2ScatterplotColorLinkerAction.createWidget(this);
    selectionSpecies2ScatterplotColorLinkerWidget->setFixedWidth(300);
    selectionSpecies2ScatterplotColorLinkerWidget->findChild<QComboBox*>("ComboBox")->setSizeAdjustPolicy(QComboBox::AdjustToContents);



    auto selectionEmbedding1DatasetLinkerWidget = simianOptionsAction._speciesEmbedding1LinkerAction.createWidget(this);
    selectionEmbedding1DatasetLinkerWidget->setFixedWidth(300);
    selectionEmbedding1DatasetLinkerWidget->findChild<QComboBox*>("ComboBox")->setSizeAdjustPolicy(QComboBox::AdjustToContents);

    auto selectionEmbedding2DatasetLinkerWidget = simianOptionsAction._speciesEmbedding2LinkerAction.createWidget(this);
    selectionEmbedding2DatasetLinkerWidget->setFixedWidth(300);
    selectionEmbedding2DatasetLinkerWidget->findChild<QComboBox*>("ComboBox")->setSizeAdjustPolicy(QComboBox::AdjustToContents);





    auto selectionInSpecies1DatasetLinkerWidget = simianOptionsAction._inSpecies1DatasetLinkerAction.createWidget(this);
    selectionInSpecies1DatasetLinkerWidget->setFixedWidth(300);
    selectionInSpecies1DatasetLinkerWidget->findChild<QComboBox*>("ComboBox")->setSizeAdjustPolicy(QComboBox::AdjustToContents);

    auto selectionInSpecies2DatasetLinkerWidget = simianOptionsAction._inSpecies2DatasetLinkerAction.createWidget(this);
    selectionInSpecies2DatasetLinkerWidget->setFixedWidth(300);
    selectionInSpecies2DatasetLinkerWidget->findChild<QComboBox*>("ComboBox")->setSizeAdjustPolicy(QComboBox::AdjustToContents);


    auto selectionInSpecies1HeatMapCellWidget = simianOptionsAction._inSpecies1HeatMapCellAction.createWidget(this);
    selectionInSpecies1HeatMapCellWidget->setFixedWidth(300);
    selectionInSpecies1HeatMapCellWidget->findChild<QComboBox*>("ComboBox")->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    auto selectionInSpecies2HeatMapCellWidget = simianOptionsAction._inSpecies2HeatMapCellAction.createWidget(this);
    selectionInSpecies2HeatMapCellWidget->setFixedWidth(300);
    selectionInSpecies2HeatMapCellWidget->findChild<QComboBox*>("ComboBox")->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    auto selectionCrossSpecies1HeatMapCellWidget = simianOptionsAction._crossSpecies1HeatMapCellAction.createWidget(this);
    selectionCrossSpecies1HeatMapCellWidget->setFixedWidth(300);
    selectionCrossSpecies1HeatMapCellWidget->findChild<QComboBox*>("ComboBox")->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    auto selectionCrossSpecies2HeatMapCellWidget = simianOptionsAction._crossSpecies2HeatMapCellAction.createWidget(this);
    selectionCrossSpecies2HeatMapCellWidget->setFixedWidth(300);
    selectionCrossSpecies2HeatMapCellWidget->findChild<QComboBox*>("ComboBox")->setSizeAdjustPolicy(QComboBox::AdjustToContents);

    auto linkerSettingSelectionLayout = new QFormLayout();
    linkerSettingSelectionLayout->setContentsMargins(2, 2, 2, 2);
    linkerSettingSelectionLayout->setObjectName("Linker Setting Options");
    linkerSettingSelectionLayout->setSpacing(2);
    linkerSettingSelectionLayout->setVerticalSpacing(2);
    linkerSettingSelectionLayout->addRow(simianOptionsAction._crossSpecies1DatasetLinkerAction.createLabelWidget(this), selectionCrossSpecies1DatasetLinkerWidget);
    linkerSettingSelectionLayout->addRow(simianOptionsAction._crossSpecies2DatasetLinkerAction.createLabelWidget(this), selectionCrossSpecies2DatasetLinkerWidget);

    linkerSettingSelectionLayout->addRow(simianOptionsAction._species1ScatterplotColorLinkerAction.createLabelWidget(this), selectionSpecies1ScatterplotColorLinkerWidget);
    linkerSettingSelectionLayout->addRow(simianOptionsAction._species2ScatterplotColorLinkerAction.createLabelWidget(this), selectionSpecies2ScatterplotColorLinkerWidget);

    linkerSettingSelectionLayout->addRow(simianOptionsAction._speciesEmbedding1LinkerAction.createLabelWidget(this), selectionEmbedding1DatasetLinkerWidget);
    linkerSettingSelectionLayout->addRow(simianOptionsAction._speciesEmbedding2LinkerAction.createLabelWidget(this), selectionEmbedding2DatasetLinkerWidget);

    linkerSettingSelectionLayout->addRow(simianOptionsAction._inSpecies1DatasetLinkerAction.createLabelWidget(this), selectionInSpecies1DatasetLinkerWidget);
    linkerSettingSelectionLayout->addRow(simianOptionsAction._inSpecies2DatasetLinkerAction.createLabelWidget(this), selectionInSpecies2DatasetLinkerWidget);

    linkerSettingSelectionLayout->addRow(simianOptionsAction._inSpecies1HeatMapCellAction.createLabelWidget(this), selectionInSpecies1HeatMapCellWidget);
    linkerSettingSelectionLayout->addRow(simianOptionsAction._inSpecies2HeatMapCellAction.createLabelWidget(this), selectionInSpecies2HeatMapCellWidget);
    linkerSettingSelectionLayout->addRow(simianOptionsAction._crossSpecies1HeatMapCellAction.createLabelWidget(this), selectionCrossSpecies1HeatMapCellWidget);
    linkerSettingSelectionLayout->addRow(simianOptionsAction._crossSpecies2HeatMapCellAction.createLabelWidget(this), selectionCrossSpecies2HeatMapCellWidget);

    setPopupLayout(linkerSettingSelectionLayout);

}

inline SimianOptionsAction::LinkerSettingAction::LinkerSettingAction(SimianOptionsAction& simianOptionsAction) :
    _simianOptionsAction(simianOptionsAction)
{
    setText("Linker Setting Options");
    setIcon(Application::getIconFont("FontAwesome").getIcon("database"));
}



SimianOptionsAction::DistanceNeighborhoodAction::Widget::Widget(QWidget* parent, DistanceNeighborhoodAction* distanceNeighborhoodAction) :
    WidgetActionWidget(parent, distanceNeighborhoodAction)
{
    auto& simianOptionsAction = distanceNeighborhoodAction->_simianOptionsAction;

    auto selectionNeighborhoodWidget = simianOptionsAction._neighborhoodAction.createWidget(this);
    selectionNeighborhoodWidget->findChild<QComboBox*>("ComboBox")->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    selectionNeighborhoodWidget->setMaximumWidth(150);

    auto filterOptionLayout = new QFormLayout();

    filterOptionLayout->setContentsMargins(0, 0, 0, 0);
    filterOptionLayout->addRow("Neighborhood:", selectionNeighborhoodWidget);


    setPopupLayout(filterOptionLayout);
}

inline SimianOptionsAction::DistanceNeighborhoodAction::DistanceNeighborhoodAction(SimianOptionsAction& simianOptionsAction) :
    _simianOptionsAction(simianOptionsAction)
{
    //setText("Distance-Neighborhood Options");
    //setText("Neighborhood Option");

    //setIcon(Application::getIconFont("FontAwesome").getIcon("cog"));
}



void SimianOptionsAction::filterMultiSelect()
{
    QStringList clusterValues = _multiSelectClusterFilterAction.getSelectedOptions();

    std::vector<std::vector<std::string>>    filteredVisData;
    std::vector<std::vector<std::string>>    clusterfilteredVisData;



    if ((_crossSpeciesFilterAction.getCurrentText()).toStdString() == "cross-species clusters")
    {
        for (int i = 0; i < _simianData.size(); i++)

        {
            if (_simianData[i][7] == _simianData[i][8] && _simianData[i][1] == (_species1SelectAction.getCurrentText()).toStdString() && _simianData[i][3] == (_species2SelectAction.getCurrentText()).toStdString() && _simianData[i][6] == (_neighborhoodAction.getCurrentText()).toStdString() && stoi(_simianData[i][5]) < (_distanceAction.getValue()))
            {
                std::vector<std::string> temp;
                for (int j = 0; j < _simianData[i].size(); j++)
                {
                    temp.push_back(_simianData[i][j]);
                }
                filteredVisData.push_back(temp);
            }
        }
    }
    else
    {
        for (int i = 0; i < _simianData.size(); i++)

        {
            if (_simianData[i][1] == (_species1SelectAction.getCurrentText()).toStdString() && _simianData[i][3] == (_species2SelectAction.getCurrentText()).toStdString() && _simianData[i][6] == (_neighborhoodAction.getCurrentText()).toStdString() && stoi(_simianData[i][5]) < (_distanceAction.getValue()))
            {
                std::vector<std::string> temp;
                for (int j = 0; j < _simianData[i].size(); j++)
                {
                    temp.push_back(_simianData[i][j]);
                }
                filteredVisData.push_back(temp);
            }
        }
    }
    
    for (int i = 0; i < filteredVisData.size(); i++)
    {
        for (int j = 0; j < clusterValues.size(); j++)
        {
            if (QString::fromStdString(filteredVisData[i][7])== clusterValues[j])
            {
                clusterfilteredVisData.push_back(filteredVisData[i]);
                continue;
            }
            
        }
    }



    QString _jsonObject;
    _jsonObject += "[";

    QStringList columnNames = { "RowNumber", "species_1", "cluster_1", "species_2", "cluster_2", "dist", "neighborhood", "cross_species_cluster1_species_1", "cross_species_cluster2_species_2", "sortColumn","subclass_1","class_1","subclass_2","class_2" };

    for (int i = 0; i < clusterfilteredVisData.size(); i++)
    {
        _jsonObject += "{";

        for (int j = 0; j < clusterfilteredVisData[i].size(); j++)
        {
            QString columnName = columnNames[j];
            _jsonObject += QString("\"%1\":\"%2\",").arg(columnName, clusterfilteredVisData[i][j].c_str());
        }

        _jsonObject.chop(1);

        _jsonObject += "},";
    }
    _jsonObject.chop(1);
    _jsonObject += "]";
    _simianViewerPlugin.getWidget()->setData(_jsonObject.toStdString());
    auto& colorMapRangeAction = _colorMapAction.getSettingsAction().getHorizontalAxisAction().getRangeAction();
    float colorMapRangeMin = 1200.0;
    float colorMapRangeMax = 0.0;
    for (int i = 0; i < clusterfilteredVisData.size(); i++)
    {
        const float temp = std::stof(clusterfilteredVisData[i][5]);
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
}

QString SimianOptionsAction::selectFromQStringList(const QStringList& fileList, const QString& speciesType, const QString& fileType)
{
    QString foundFile = "constant";

    for (const auto& file : fileList)
    {
        if (file.toLower().contains(speciesType.toLower()))
        {
            if (fileType == "in-species class")
            {
                if (file.toLower().endsWith("/class"))
                {
                    foundFile= file;
                }
            }
            else if (fileType == "in-species cluster")
            {
                if (file.toLower().endsWith("/cluster"))
                {
                    foundFile = file;
                }

            }
            else if (fileType == "cross-species class")
            {
                if (file.toLower().endsWith("/cross_species_class"))
                {
                    foundFile = file;
                }
            }
            else if (fileType == "cross-species cluster")
            {
                if (file.toLower().endsWith("/cross_species_cluster"))
                {
                    foundFile = file;
                }
            }
            else if (fileType == "cross-species sub-class")
            {
                if (file.toLower().endsWith("/cross_species_subclass"))
                {
                    foundFile = file;
                }
            }

            else if (fileType == "donor")
            {
                if (file.toLower().endsWith("/donor"))
                {
                    foundFile = file;
                }

            }
            else if (fileType == "neighborhood")
            {
                if (file.toLower().endsWith("/neighborhood"))
                {
                    foundFile = file;
                }

            }
            else if (fileType == "sex")
            {
                if (file.toLower().endsWith("/sex"))
                {
                    foundFile = file;
                }

            }
            else if (fileType == "in-species subclass")
            {
                if (file.toLower().endsWith("/subclass"))
                {
                    foundFile = file;
                }
            }
        }      
    }
    return foundFile;
}



bool SimianOptionsAction::QStringlistContainsQString(const QStringList& list, const QString& str)
{
    QStringMatcher matcher(str);
    foreach(const QString & listitem, list) {
        if (matcher.indexIn(listitem) != -1) return true;
    }
    return false;
}

