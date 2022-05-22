#include "SimianOptionsAction.h"
#include "SimianViewerPlugin.h"

using namespace hdps;
using namespace hdps::gui;

SimianOptionsAction::SimianOptionsAction(SimianViewerPlugin& simianViewerPlugin, hdps::CoreInterface* core) :
    WidgetAction(&simianViewerPlugin),
    _simianViewerPlugin(simianViewerPlugin),
    _core(core),
    _species1Action(this, "Select species1 :"),
    _species2Action(this, "Select species2 :"),
    _neighborhoodAction(this, "Select neighborhood :"),
    _distanceAction(this, "Filter distance :"),
    _species1DatasetLinkerAction(this, "Species1 cluster dataset :"),
    _species2DatasetLinkerAction(this, "Species2 cluster dataset :"),
    _crossSpeciesFilterAction(this, "Filter clusters :"),
    _multiSelectClusterFilterAction(this, "Select cross-species clusters :"),
    _colorMapAction(this, "Select color map"),
    _isLoading(false),
    _speciesAction(*this),
    _clusterAction(*this), 
    _distanceNeighborhoodAction(*this),
    _isStarted(false)
{
    _eventListener.setEventCore(core);
    _eventListener.addSupportedEventType(static_cast<std::uint32_t>(EventType::DataAdded));
    _eventListener.addSupportedEventType(static_cast<std::uint32_t>(EventType::DataRemoved));
    _eventListener.addSupportedEventType(static_cast<std::uint32_t>(EventType::DataChildAdded));
    _eventListener.addSupportedEventType(static_cast<std::uint32_t>(EventType::DataChildRemoved));
    _eventListener.addSupportedEventType(static_cast<std::uint32_t>(EventType::DataChanged));
    _eventListener.addSupportedEventType(static_cast<std::uint32_t>(EventType::DataGuiNameChanged));
    _eventListener.registerDataEventByType(PointType, std::bind(&SimianOptionsAction::onDataEvent, this, std::placeholders::_1));

    _metaData = new FetchMetaData();
     _metaData->getData(&_simianData);
    _species2Action.setEnabled(false);
    _neighborhoodAction.setEnabled(false);
    _distanceAction.setEnabled(false);
    _species1DatasetLinkerAction.setEnabled(false);
    _species2DatasetLinkerAction.setEnabled(false);
    _crossSpeciesFilterAction.setEnabled(false);
    _multiSelectClusterFilterAction.setEnabled(false);
    _colorMapAction.setEnabled(false);
    _clusterAction.setEnabled(false);
    _distanceNeighborhoodAction.setEnabled(false);
    _species1Action.setDefaultWidgetFlags(OptionAction::ComboBox);
    _species1Action.setPlaceHolderString(QString("Choose Species1"));
    _species1Action.initialize(QStringList({ "chimp","gorilla","human","rhesus" }), _species1Action.getPlaceholderString(), _species1Action.getPlaceholderString());
 
    _species2Action.setDefaultWidgetFlags(OptionAction::ComboBox);
    _species2Action.setPlaceHolderString(QString("Choose Species2"));
    _species2Action.initialize(QStringList({ "gorilla","marmoset","rhesus","chimp" }), _species2Action.getPlaceholderString(), _species2Action.getPlaceholderString());

    _crossSpeciesFilterAction.setDefaultWidgetFlags(OptionAction:: ComboBox);
    _crossSpeciesFilterAction.initialize(QStringList({ "all clusters","cross-species clusters" }), "cross-species clusters", "cross-species clusters");

    _multiSelectClusterFilterAction.setDefaultWidgetFlags(OptionsAction::ComboBox | OptionsAction::ListView | OptionsAction::Selection | OptionsAction::File);
    _multiSelectClusterFilterAction.initialize(QStringList{ "" });
    _multiSelectClusterFilterAction.setSelectedOptions(QStringList());
    _colorMapAction.initialize("Black to white","Black to white");
    _neighborhoodAction.setDefaultWidgetFlags(OptionAction::ComboBox);
    _neighborhoodAction.initialize(QStringList({ "glia","it_types","l5et_l56np_l6ct_l6b","lamp5_sncg_vip","sst_sst_chodl_pvalb" }), "sst_sst_chodl_pvalb", "sst_sst_chodl_pvalb");
    
    _distanceAction.setDefaultWidgetFlags(IntegralAction::SpinBox | IntegralAction::Slider);
    _distanceAction.initialize(0, 105, 105, 105);
   
    _species1DatasetLinkerAction.setDefaultWidgetFlags(OptionAction::ComboBox);

    _species2DatasetLinkerAction.setDefaultWidgetFlags(OptionAction::ComboBox);

    _colorMapAction.getSettingsAction().getDiscreteAction().setVisible(false);
    _colorMapAction.getSettingsAction().getEditor1DAction().setVisible(false);

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
        updateData((_species1Action.getCurrentText()).toStdString(), (_species2Action.getCurrentText()).toStdString(), (_neighborhoodAction.getCurrentText()).toStdString(), (_distanceAction.getValue()),(_crossSpeciesFilterAction.getCurrentText()).toStdString());
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
        //qDebug() << _colorMapAction.getColorMapImage();// .mirrored(false, true);
        //qDebug() << _colorMapAction.getColorMapImage().mirrored();
        const auto& mirrorAction = _colorMapAction.getSettingsAction().getHorizontalAxisAction().getMirrorAction();
        //qDebug() << mirrorAction.isChecked();
        _simianViewerPlugin.getWidget()->setColor(_colorMapAction.getColorMap());
    };
    
        const auto updateColorMapRange = [this]() -> void
    {
       
        // Get color map range action
        const auto& rangeAction = _colorMapAction.getSettingsAction().getHorizontalAxisAction().getRangeAction();
        //qDebug() << rangeAction.getMinimum();
        //qDebug() << rangeAction.getMaximum();

        //_simianViewerPlugin.getWidget()->setColor(_colorMapAction.getColorMap());

    };

    const auto updateSpecies1 = [this]() -> void
    {
        if (_species1Action.getCurrentText().isValidUtf16())
        {
            _species2Action.setEnabled(true);
        }
        else {
            _species2Action.setEnabled(false);
            _neighborhoodAction.setEnabled(false);
            _distanceAction.setEnabled(false);
            _species1DatasetLinkerAction.setEnabled(false);
            _species2DatasetLinkerAction.setEnabled(false);
            _crossSpeciesFilterAction.setEnabled(false);
            _multiSelectClusterFilterAction.setEnabled(false);
            _multiSelectClusterFilterAction.setSelectedOptions(QStringList());
            _colorMapAction.setEnabled(false);
            _clusterAction.setEnabled(false);
            _distanceNeighborhoodAction.setEnabled(false);
        }
        if (_species1Action.getCurrentText() !="" && _species2Action.getCurrentText() != "")
        {
            updateData((_species1Action.getCurrentText()).toStdString(), (_species2Action.getCurrentText()).toStdString(), (_neighborhoodAction.getCurrentText()).toStdString(), (_distanceAction.getValue()), (_crossSpeciesFilterAction.getCurrentText()).toStdString());
        }


    };
    const auto updateSpecies2 = [this]() -> void
    {
        if (_species2Action.getCurrentText().isValidUtf16())
        {
            _neighborhoodAction.setEnabled(true);
            //_distanceAction.setEnabled(true);
            _species1DatasetLinkerAction.setEnabled(true);
            _species2DatasetLinkerAction.setEnabled(true);
            _crossSpeciesFilterAction.setEnabled(true);
            _multiSelectClusterFilterAction.setEnabled(true);
            _colorMapAction.setEnabled(true);
            _clusterAction.setEnabled(true);
            _distanceNeighborhoodAction.setEnabled(true);
        }
        else {
            _neighborhoodAction.setEnabled(false);
            _distanceAction.setEnabled(false);
            _species2DatasetLinkerAction.setEnabled(false);
            _species1DatasetLinkerAction.setEnabled(false);
            _crossSpeciesFilterAction.setEnabled(false);
            _multiSelectClusterFilterAction.setEnabled(false);
            _multiSelectClusterFilterAction.setSelectedOptions(QStringList());
            _colorMapAction.setEnabled(false);
            _clusterAction.setEnabled(false);
            _distanceNeighborhoodAction.setEnabled(false);
        }
        
        if (_species1Action.getCurrentText() != "" && _species2Action.getCurrentText() != "")
        {
            updateData((_species1Action.getCurrentText()).toStdString(), (_species2Action.getCurrentText()).toStdString(), (_neighborhoodAction.getCurrentText()).toStdString(), (_distanceAction.getValue()), (_crossSpeciesFilterAction.getCurrentText()).toStdString());
        }
    };
    const auto updateNeighborhood = [this]() -> void
    {
        if (_species1Action.getCurrentText() != "" && _species2Action.getCurrentText() != "")
        {
            updateData((_species1Action.getCurrentText()).toStdString(), (_species2Action.getCurrentText()).toStdString(), (_neighborhoodAction.getCurrentText()).toStdString(), (_distanceAction.getValue()), (_crossSpeciesFilterAction.getCurrentText()).toStdString());
        }
    };
    const auto updateDistance = [this]() -> void
    {
        if (_species1Action.getCurrentText() != "" && _species2Action.getCurrentText() != "")
        {
            updateData((_species1Action.getCurrentText()).toStdString(), (_species2Action.getCurrentText()).toStdString(), (_neighborhoodAction.getCurrentText()).toStdString(), (_distanceAction.getValue()), (_crossSpeciesFilterAction.getCurrentText()).toStdString());
        }
    };


    const auto updateSpecies1DatasetLinker = [this]() -> void
    {

    };

    const auto updateSpecies2DatasetLinker = [this]() -> void
    {

    };


    connect(&_crossSpeciesFilterAction, &OptionAction::currentIndexChanged, [this, updateCrossSpeciesFilter](const std::int32_t& currentIndex) {
        updateCrossSpeciesFilter();

        });

    connect(&_multiSelectClusterFilterAction, &OptionsAction::selectedOptionsChanged, [this, multiSelectClusterFilter](const QStringList& currentIndex) {
        multiSelectClusterFilter();

        });

    connect(&_colorMapAction, &ColorMapAction::imageChanged, this, colormapFilter);

    connect(&_colorMapAction.getSettingsAction().getHorizontalAxisAction().getRangeAction(), &DecimalRangeAction::rangeChanged, this, updateColorMapRange);

    connect(&_species1Action, &OptionAction::currentIndexChanged, [this, updateSpecies1](const std::int32_t& currentIndex) {
        updateSpecies1();

        });
    connect(&_species2Action, &OptionAction::currentIndexChanged, [this, updateSpecies2](const std::int32_t& currentIndex) {
        updateSpecies2();
        });
    connect(&_neighborhoodAction, &OptionAction::currentIndexChanged, this, [this, updateNeighborhood](const std::int32_t& currentIndex)
        {
            updateNeighborhood();
        });
    connect(&_distanceAction, &IntegralAction::valueChanged, this, [this, updateDistance](const std::int32_t& value)
        {
            updateDistance();
        });

    connect(&_species1DatasetLinkerAction, &OptionAction::currentIndexChanged, this, [this, updateSpecies1DatasetLinker](const std::int32_t& value) {
        updateSpecies1DatasetLinker();
        });
    connect(&_species2DatasetLinkerAction, &OptionAction::currentIndexChanged, this, [this, updateSpecies2DatasetLinker](const std::int32_t& value) {
        updateSpecies2DatasetLinker();
        });

    updateDatasetPickerAction();

}

SimianOptionsAction::Widget::Widget(QWidget* parent, SimianOptionsAction* SimianOptionsAction) :
    WidgetActionWidget(parent, SimianOptionsAction, State::Standard)
{








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

    QStringList columnNames = { "RowNumber", "species_1", "cluster_1", "species_2", "cluster_2", "dist", "neighborhood", "cross_species_cluster1_species_1", "cross_species_cluster2_species_2", "sortColumn" };

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
}


void SimianOptionsAction::updateDatasetPickerAction()
{
    auto datasets = _core->requestAllDataSets(QVector<hdps::DataType> {ClusterType});
    auto filteredDatasets = datasets;
    for (auto dataset : datasets)
    {
        std::string str1 = dataset->getGuiName().toStdString();
        std::string str2 = "cluster";
        if (strstr(str1.c_str(), str2.c_str()))
        {
        }
        else {
            filteredDatasets.removeOne(dataset);
        }
    }

    datasets = filteredDatasets;
    for (auto dataset : datasets) 
    {
        std::string str3 = dataset->getGuiName().toStdString();
        std::string str4 = "cross";

        if (getCrossSpeciesFilterAction().getCurrentText() == "cross-species clusters")
        {
            if (strstr(str3.c_str(), str4.c_str()))
            {

            }
            else
            {
                filteredDatasets.removeOne(dataset);
            }
        }
        else //if (getCrossSpeciesFilterAction().getCurrentText() == "all clsuters")
        {
            if (strstr(str3.c_str(), str4.c_str()))
            {
                filteredDatasets.removeOne(dataset);
            }
            else 
            {

            }
        }
    }
    _species1DatasetLinkerAction.setDatasets(filteredDatasets);
    _species1DatasetLinkerAction.setPlaceHolderString("Species1 clusters");
    _species2DatasetLinkerAction.setDatasets(filteredDatasets);
    _species2DatasetLinkerAction.setPlaceHolderString("Species2 clusters");


}

SimianOptionsAction::SpeciesAction::Widget::Widget(QWidget* parent, SpeciesAction* speciesAction) :
    WidgetActionWidget(parent, speciesAction)
{
    auto& simianOptionsAction = speciesAction->_simianOptionsAction;

    auto selectionSpecies1Widget = simianOptionsAction._species1Action.createWidget(this);
    selectionSpecies1Widget->setFixedWidth(150);
    selectionSpecies1Widget->findChild<QComboBox*>("ComboBox")->setSizeAdjustPolicy(QComboBox::AdjustToContents);

    auto selectionSpecies2Widget = simianOptionsAction._species2Action.createWidget(this);
    selectionSpecies2Widget->setFixedWidth(150);
    selectionSpecies2Widget->findChild<QComboBox*>("ComboBox")->setSizeAdjustPolicy(QComboBox::AdjustToContents);

    auto selectionSpecies1DatasetLinkerWidget = simianOptionsAction._species1DatasetLinkerAction.createWidget(this);
    selectionSpecies1DatasetLinkerWidget->setFixedWidth(300);
    selectionSpecies1DatasetLinkerWidget->findChild<QComboBox*>("ComboBox")->setSizeAdjustPolicy(QComboBox::AdjustToContents);

    auto selectionSpecies2DatasetLinkerWidget = simianOptionsAction._species2DatasetLinkerAction.createWidget(this);
    selectionSpecies2DatasetLinkerWidget->setFixedWidth(300);
    selectionSpecies2DatasetLinkerWidget->findChild<QComboBox*>("ComboBox")->setSizeAdjustPolicy(QComboBox::AdjustToContents);

    auto speciesSelectionLayout = new QFormLayout();

    speciesSelectionLayout->setMargin(2);
    speciesSelectionLayout->addRow(new QLabel("Species1: *"), selectionSpecies1Widget);
    speciesSelectionLayout->addRow(new QLabel("Species2: *"), selectionSpecies2Widget);
    speciesSelectionLayout->addRow(new QLabel("Species1 linker:"), selectionSpecies1DatasetLinkerWidget);
    speciesSelectionLayout->addRow(new QLabel("Species2 linker:"), selectionSpecies2DatasetLinkerWidget);
    speciesSelectionLayout->setObjectName("Species Options");
    speciesSelectionLayout->setSpacing(2);
    speciesSelectionLayout->setVerticalSpacing(2);

    setPopupLayout(speciesSelectionLayout);
}

inline SimianOptionsAction::SpeciesAction::SpeciesAction(SimianOptionsAction& simianOptionsAction) :
    _simianOptionsAction(simianOptionsAction)
{
    setText("Species Options");
    setIcon(Application::getIconFont("FontAwesome").getIcon("search"));
}


SimianOptionsAction::ColorMapOptionAction::Widget::Widget(QWidget* parent, ColorMapOptionAction* colorMapAction) :
    WidgetActionWidget(parent, colorMapAction)
{
    auto& simianOptionsAction = colorMapAction->_simianOptionsAction;

    auto colorMapWidget = simianOptionsAction._colorMapAction.createWidget(this);
    //colorMapWidget->findChild<QComboBox*>("ComboBox")->setSizeAdjustPolicy(QComboBox::AdjustToContents);

    auto colorSelectionLayout = new QFormLayout();
    colorSelectionLayout->setMargin(2);
    colorSelectionLayout->addRow(new QLabel("heatmap color: *"), colorMapWidget);
    colorSelectionLayout->setObjectName("Color Options");
    colorSelectionLayout->setSpacing(2);
    colorSelectionLayout->setVerticalSpacing(2);

    setPopupLayout(colorSelectionLayout);
}

inline SimianOptionsAction::ColorMapOptionAction::ColorMapOptionAction(SimianOptionsAction& simianOptionsAction) :
    _simianOptionsAction(simianOptionsAction)
{
    setText("Color Options");
    setIcon(Application::getIconFont("FontAwesome").getIcon("search"));
}




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
    auto filterCrossSpeciesWidget = simianOptionsAction._crossSpeciesFilterAction.createWidget(this);
    filterCrossSpeciesWidget->findChild<QComboBox*>("ComboBox")->setSizeAdjustPolicy(QComboBox::AdjustToContents);

    auto crossSpeciesClusterSelectionWidget = simianOptionsAction._multiSelectClusterFilterAction.createWidget(this);
    crossSpeciesClusterSelectionWidget->findChild<QComboBox*>("ComboBox")->setSizeAdjustPolicy(QComboBox::AdjustToContents);

    auto crossSpeciesClusterSelectionLayout = new QFormLayout();
    crossSpeciesClusterSelectionLayout->setMargin(2);
    crossSpeciesClusterSelectionLayout->setObjectName("Cluster Options");
    crossSpeciesClusterSelectionLayout->setSpacing(2);
    crossSpeciesClusterSelectionLayout->setVerticalSpacing(2);
    crossSpeciesClusterSelectionLayout->addRow(new QLabel("Cluster filter:"), filterCrossSpeciesWidget);
    crossSpeciesClusterSelectionLayout->addRow(new QLabel("Cross-species cluster filter:"), crossSpeciesClusterSelectionWidget);

    setPopupLayout(crossSpeciesClusterSelectionLayout);
}

inline SimianOptionsAction::ClusterAction::ClusterAction(SimianOptionsAction& simianOptionsAction) :
    _simianOptionsAction(simianOptionsAction)
{
    setText("Cluster Options");
    setIcon(Application::getIconFont("FontAwesome").getIcon("filter"));
}


SimianOptionsAction::DistanceNeighborhoodAction::Widget::Widget(QWidget* parent, DistanceNeighborhoodAction* distanceNeighborhoodAction) :
    WidgetActionWidget(parent, distanceNeighborhoodAction)
{
    auto& simianOptionsAction = distanceNeighborhoodAction->_simianOptionsAction;

    auto selectionNeighborhoodWidget = simianOptionsAction._neighborhoodAction.createWidget(this);
    selectionNeighborhoodWidget->findChild<QComboBox*>("ComboBox")->setSizeAdjustPolicy(QComboBox::AdjustToContents);

    auto selectionDistanceWidget = simianOptionsAction._distanceAction.createWidget(this);
    selectionDistanceWidget->setFixedWidth(200);
    selectionDistanceWidget->findChild<QSlider*>("Slider");
    selectionDistanceWidget->findChild<QSpinBox*>("SpinBox");
    auto filterOptionLayout = new QFormLayout();
    filterOptionLayout->setMargin(2);
    filterOptionLayout->addRow(new QLabel("Neighborhood:"), selectionNeighborhoodWidget);
    filterOptionLayout->addRow(new QLabel("Distance:") , selectionDistanceWidget);

    filterOptionLayout->setObjectName("Simian Options");
    filterOptionLayout->setSpacing(2);
    filterOptionLayout->setVerticalSpacing(2);

    setPopupLayout(filterOptionLayout);
}

inline SimianOptionsAction::DistanceNeighborhoodAction::DistanceNeighborhoodAction(SimianOptionsAction& simianOptionsAction) :
    _simianOptionsAction(simianOptionsAction)
{
    setText("Distance-Neighborhood Options");


    setIcon(Application::getIconFont("FontAwesome").getIcon("cog"));
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
            if (_simianData[i][7] == _simianData[i][8] && _simianData[i][1] == (_species1Action.getCurrentText()).toStdString() && _simianData[i][3] == (_species2Action.getCurrentText()).toStdString() && _simianData[i][6] == (_neighborhoodAction.getCurrentText()).toStdString() && stoi(_simianData[i][5]) < (_distanceAction.getValue()))
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
            if (_simianData[i][1] == (_species1Action.getCurrentText()).toStdString() && _simianData[i][3] == (_species2Action.getCurrentText()).toStdString() && _simianData[i][6] == (_neighborhoodAction.getCurrentText()).toStdString() && stoi(_simianData[i][5]) < (_distanceAction.getValue()))
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

    QStringList columnNames = { "RowNumber", "species_1", "cluster_1", "species_2", "cluster_2", "dist", "neighborhood", "cross_species_cluster1_species_1", "cross_species_cluster2_species_2", "sortColumn" };

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