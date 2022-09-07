//global Variables
var _data = null;
var _clustersReceived = new Array();
var mindistanceColor = 0;
var maxdistanceColor = 0;
var _dataQueue = new SimianViewerDataQueue(1, queueData);
var cellsForLegend = 6;
var flag = false;
var species1ValueIdentify = "";
var species2ValueIdentify = "";
var uniqueClusters1List = [];
var uniqueClusters2List = [];
var uniqueCrossSpeicesClusters1List = [];
var uniqueCrossSpeciesClusters2List = [];
var crossSpeciesFilterspecies1Cluster = [];
var crossSpeciesFilterspecies2Cluster = [];
//var uniqueCrossspeciesClusters = [];
var inspecies2ClusterCounts = {};
var inspecies1ClusterCounts = {};
var totalInspeciescluster1counts = 0;
var totalInspeciescluster2counts = 0;
var svg;
var qtColor = "Black to white";
var colorMirror = false;
var barflag = false;
var layerFlag = false;
var backgroundColor = "#ffffff";
//onresize adjust chart dimensions
window.onresize = doALoadOfStuff;
var ximage = "";
var yimage = "";
//Species Colors and cluster information
const cross_speciesClustercolors = { 'Chandelier_1': '#F87CC3', 'L2/3 IT_1': '#D9F982', 'L2/3 IT_2': '#99B348', 'L2/3 IT_3': '#596D0F', 'L4 IT_1': '#C1F4F1', 'L4 IT_2': '#00E5E5', 'L5 ET_1': '#79B7C6', 'L5 ET_2': '#0D5B78', 'L5 IT_1': '#A0CEC9', 'L5 IT_2': '#2A5E5A', 'L5/6 NP_1': '#75C591', 'L5/6 NP_2': '#3C7D53', 'L6 CT_1': '#87D7F4', 'L6 CT_2': '#3E7E96', 'L6 IT_1': '#BEB867', 'L6 IT Car3_1': '#B29FF7', 'L6 IT Car3_2': '#8054F7', 'L6b_1': '#C4A4F7', 'L6b_2': '#7E64A9', 'L6b_3': '#39245B', 'Lamp5_1': '#F9B9C5', 'Lamp5_2': '#94606B', 'Lamp5_Lhx6_1': '#B49186', 'Pax6_1': '#CD8CEA', 'Pax6_2': '#6D3C82', 'Pvalb_1': '#F98089', 'Pvalb_2': '#CF5F67', 'Pvalb_3': '#A53E46', 'Pvalb_4': '#7C1E25', 'Sncg_1': '#E99CFF', 'Sncg_2': '#B06DC5', 'Sncg_3': '#773F8C', 'Sst_1': '#FFB84F', 'Sst_2': '#EEA945', 'Sst_3': '#DD9A3C', 'Sst_4': '#CC8C33', 'Sst_5': '#BB7D2A', 'Sst_6': '#AA6E20', 'Sst_7': '#996017', 'Sst_8': '#88510E', 'Sst_9': '#774305', 'Sst Chodl_1': '#C9C958', 'Vip_1': '#E5B9FC', 'Vip_2': '#CBA3E0', 'Vip_3': '#B18DC5', 'Vip_4': '#9877AA', 'Vip_5': '#7E628E', 'Vip_6': '#654C73', 'Vip_7': '#4B3658', 'Vip_8': '#32213D', 'Astro_1': '#D8D4CB', 'Endo_1': '#B09A93', 'Micro-PVM_1': '#798C7A', 'Oligo_1': '#B4D1C8', 'OPC_1': '#939E9C', 'OPC_2': '#263430', 'VLMC_1': '#979E8A' };
const in_speciesClustercolors = { 'Astro_1': '#958F80', 'Astro_2': '#484132', 'Astro_2': '#665C47', 'Astro_2': '#756D5A', 'Astro_2': '#7D7563', 'Astro_3': '#484132', 'Astro_3': '#5C5340', 'Astro_3': '#665C47', 'Astro_4': '#484132', 'Astro_4': '#574E3C', 'Astro_5': '#484132', 'Chandelier_1': '#F87CC3', 'Chandelier_2': '#AD2D76', 'Chandelier_2': '#F641A8', 'Endo_1': '#B09A93', 'Endo_2': '#634C45', 'Endo_2': '#987B72', 'Endo_3': '#7F6158', 'L2/3 IT_1': '#BDEE50', 'L2/3 IT_1': '#C9F170', 'L2/3 IT_10': '#9DD12A', 'L2/3 IT_10': '#A3DA2C', 'L2/3 IT_11': '#94C627', 'L2/3 IT_11': '#9DD12A', 'L2/3 IT_12': '#8CBB25', 'L2/3 IT_12': '#97C928', 'L2/3 IT_13': '#84B023', 'L2/3 IT_13': '#90C026', 'L2/3 IT_14': '#8AB724', 'L2/3 IT_15': '#7DA621', 'L2/3 IT_2': '#B1EC30', 'L2/3 IT_2': '#BDEE50', 'L2/3 IT_2': '#C2EF5D', 'L2/3 IT_2': '#C5F066', 'L2/3 IT_2': '#C6F068', 'L2/3 IT_3': '#97C928', 'L2/3 IT_3': '#B1EC30', 'L2/3 IT_3': '#BBEE4B', 'L2/3 IT_3': '#C1EF5C', 'L2/3 IT_3': '#C3EF60', 'L2/3 IT_4': '#7DA621', 'L2/3 IT_4': '#97C928', 'L2/3 IT_4': '#B4EC39', 'L2/3 IT_4': '#BDEE52', 'L2/3 IT_4': '#C0EF58', 'L2/3 IT_5': '#A9E22D', 'L2/3 IT_5': '#BAED48', 'L2/3 IT_5': '#BDEE50', 'L2/3 IT_6': '#9ACE29', 'L2/3 IT_6': '#B6ED3E', 'L2/3 IT_6': '#BAED48', 'L2/3 IT_7': '#8BBA25', 'L2/3 IT_7': '#B2EC34', 'L2/3 IT_7': '#B7ED40', 'L2/3 IT_8': '#ACE62E', 'L2/3 IT_8': '#B1EC30', 'L2/3 IT_9': '#A4DB2C', 'L2/3 IT_9': '#AAE32E', 'L4 IT_1': '#4FEDED', 'L4 IT_1': '#54E8E4', 'L4 IT_2': '#00A1A1', 'L4 IT_2': '#00E5E5', 'L4 IT_2': '#1AE7E7', 'L4 IT_2': '#2FE9E9', 'L4 IT_3': '#00A1A1', 'L4 IT_3': '#00CECE', 'L4 IT_3': '#0FE6E6', 'L4 IT_3': '#54E8E4', 'L4 IT_4': '#00A1A1', 'L4 IT_4': '#00D7D7', 'L4 IT_4': '#54E8E4', 'L4 IT_5': '#00BCBC', 'L4 IT_5': '#54E8E4', 'L4 IT_6': '#00A1A1', 'L5 ET_1': '#588EA2', 'L5 ET_2': '#094054', 'L5 ET_2': '#0D5B78', 'L5 ET_2': '#32748D', 'L5 ET_3': '#0B4D66', 'L5 ET_4': '#094054', 'L5 IT_1': '#86CAC6', 'L5 IT_2': '#50B2AD', 'L5 IT_2': '#62BAB5', 'L5 IT_2': '#67BCB7', 'L5 IT_2': '#6BBEB9', 'L5 IT_3': '#387D7A', 'L5 IT_3': '#48A09C', 'L5 IT_3': '#50B2AD', 'L5 IT_3': '#57B5B0', 'L5 IT_4': '#387D7A', 'L5 IT_4': '#449793', 'L5 IT_4': '#4CAAA5', 'L5 IT_5': '#459B97', 'L5 IT_6': '#3E8C88', 'L5 IT_7': '#387D7A', 'L5/6 NP_1': '#3E9E64', 'L5/6 NP_1': '#68B386', 'L5/6 NP_1': '#7ABC94', 'L5/6 NP_2': '#2B6F46', 'L5/6 NP_2': '#57AA78', 'L5/6 NP_2': '#5CAD7C', 'L5/6 NP_2': '#6CB589', 'L5/6 NP_3': '#3B975F', 'L5/6 NP_3': '#3E9E64', 'L5/6 NP_3': '#5FAE7E', 'L5/6 NP_4': '#348655', 'L5/6 NP_4': '#358957', 'L5/6 NP_4': '#44A169', 'L5/6 NP_5': '#307C4E', 'L5/6 NP_5': '#3B9860', 'L5/6 NP_6': '#2B6F46', 'L5/6 NP_6': '#378E5A', 'L5/6 NP_7': '#338353', 'L5/6 NP_8': '#2B6F46', 'L6 CT_1': '#4298BF', 'L6 CT_1': '#6EB0CE', 'L6 CT_2': '#1F6282', 'L6 CT_2': '#287EA6', 'L6 CT_2': '#2D8CB8', 'L6 CT_2': '#4D9EC3', 'L6 CT_3': '#1F6282', 'L6 CT_3': '#26779D', 'L6 CT_3': '#2D8CB8', 'L6 CT_4': '#1F6282', 'L6 CT_4': '#26779D', 'L6 IT Car3_1': '#874FFF', 'L6 IT Car3_2': '#3900B4', 'L6 IT Car3_2': '#5100FF', 'L6 IT Car3_2': '#631AFF', 'L6 IT Car3_3': '#3900B4', 'L6 IT Car3_3': '#4900E6', 'L6 IT_1': '#716C18', 'L6 IT_1': '#AFA844', 'L6 IT_1': '#BEB867', 'L6 IT_2': '#716C18', 'L6 IT_2': '#A19922', 'L6 IT_2': '#AAA338', 'L6 IT_3': '#716C18', 'L6 IT_3': '#89821D', 'L6 IT_3': '#918A1E', 'L6 IT_4': '#716C18', 'L6b_1': '#9C7EC4', 'L6b_2': '#7044AA', 'L6b_2': '#764CAD', 'L6b_2': '#7E57B2', 'L6b_2': '#8A66B9', 'L6b_3': '#4F3078', 'L6b_3': '#653D99', 'L6b_3': '#6B41A2', 'L6b_3': '#784FAF', 'L6b_4': '#4F3078', 'L6b_4': '#613B94', 'L6b_4': '#6940A0', 'L6b_5': '#583586', 'L6b_5': '#5C388B', 'L6b_6': '#4F3078', 'Lamp5_1': '#E5A7B0', 'Lamp5_2': '#9A5A62', 'Lamp5_2': '#DA808C', 'Lamp5_2': '#DD8D98', 'Lamp5_2': '#E097A1', 'Lamp5_3': '#9A5A62', 'Lamp5_3': '#C4737E', 'Lamp5_3': '#DC8793', 'Lamp5_4': '#9A5A62', 'Lamp5_4': '#CD7883', 'Lamp5_5': '#B36972', 'Lamp5_6': '#9A5A62', 'Lamp5_Lhx6_1': '#B49186', 'Lamp5_Lhx6_2': '#674338', 'Micro-PVM_1': '#8BA48E', 'Micro-PVM_1': '#B5C8B7', 'Micro-PVM_2': '#687B6A', 'Micro-PVM_2': '#798F7C', 'Micro-PVM_2': '#859D88', 'Micro-PVM_2': '#94AF97', 'Micro-PVM_2': '#9FB7A1', 'Micro-PVM_3': '#687B6A', 'Micro-PVM_3': '#859D88', 'Micro-PVM_4': '#687B6A', 'OPC_1': '#75827F', 'OPC_2': '#263430', 'OPC_2': '#374A45', 'OPC_2': '#4B5C58', 'OPC_3': '#263430', 'OPC_3': '#31423E', 'OPC_4': '#263430', 'Oligo_1': '#88A19A', 'Oligo_2': '#3A544C', 'Oligo_2': '#53776C', 'Oligo_2': '#64857B', 'Oligo_3': '#4A6B61', 'Oligo_4': '#3A544C', 'Pax6_1': '#9D67B0', 'Pax6_2': '#71238C', 'Pax6_2': '#7F3998', 'Pax6_3': '#4F1862', 'Pax6_3': '#651F7E', 'Pax6_4': '#4F1862', 'Pvalb_1': '#DD4C51', 'Pvalb_1': '#E47175', 'Pvalb_10': '#992226', 'Pvalb_10': '#CC2E33', 'Pvalb_11': '#C32C31', 'Pvalb_12': '#BB2A2F', 'Pvalb_13': '#B2282C', 'Pvalb_14': '#AA262A', 'Pvalb_15': '#992226', 'Pvalb_2': '#DA3A3F', 'Pvalb_2': '#E16165', 'Pvalb_2': '#E16267', 'Pvalb_2': '#E2686C', 'Pvalb_3': '#CF2E34', 'Pvalb_3': '#DE5156', 'Pvalb_3': '#DF5459', 'Pvalb_3': '#E15F64', 'Pvalb_4': '#BD2A2F', 'Pvalb_4': '#D93137', 'Pvalb_4': '#DC464B', 'Pvalb_4': '#DF575C', 'Pvalb_5': '#AB262A', 'Pvalb_5': '#C92D32', 'Pvalb_5': '#D12F35', 'Pvalb_5': '#DA383D', 'Pvalb_5': '#DE4E53', 'Pvalb_6': '#992226', 'Pvalb_6': '#B9292E', 'Pvalb_6': '#C32C31', 'Pvalb_6': '#D12F35', 'Pvalb_6': '#DC464B', 'Pvalb_7': '#A9252A', 'Pvalb_7': '#B5282D', 'Pvalb_7': '#C32C31', 'Pvalb_7': '#DB3D43', 'Pvalb_8': '#992226', 'Pvalb_8': '#A72529', 'Pvalb_8': '#B5282D', 'Pvalb_8': '#D9353B', 'Pvalb_9': '#992226', 'Pvalb_9': '#A72529', 'Pvalb_9': '#D43035', 'Sncg_1': '#E99CFF', 'Sncg_10': '#9D4FB4', 'Sncg_2': '#E58DFF', 'Sncg_2': '#E691FF', 'Sncg_2': '#E692FF', 'Sncg_3': '#E27EFF', 'Sncg_3': '#E386FF', 'Sncg_3': '#E488FF', 'Sncg_4': '#DF70FF', 'Sncg_4': '#E17BFF', 'Sncg_4': '#E27EFF', 'Sncg_5': '#C965E6', 'Sncg_5': '#DF70FF', 'Sncg_5': '#E074FF', 'Sncg_6': '#B35ACD', 'Sncg_6': '#CE67EC', 'Sncg_6': '#D76CF6', 'Sncg_7': '#9D4FB4', 'Sncg_7': '#BE5FD9', 'Sncg_7': '#C965E6', 'Sncg_8': '#9D4FB4', 'Sncg_8': '#AD57C6', 'Sncg_8': '#BA5DD5', 'Sncg_9': '#9D4FB4', 'Sncg_9': '#AB56C4', 'Sst Chodl_1': '#C9C958', 'Sst Chodl_2': '#7D7D08', 'Sst Chodl_2': '#B1B10C', 'Sst Chodl_3': '#7D7D08', 'Sst_1': '#FFB446', 'Sst_1': '#FFB84F', 'Sst_10': '#E28700', 'Sst_10': '#F09000', 'Sst_10': '#F69300', 'Sst_10': '#FA9600', 'Sst_10': '#FFA012', 'Sst_11': '#D68000', 'Sst_11': '#E68A00', 'Sst_11': '#EE8F00', 'Sst_11': '#F19100', 'Sst_11': '#FF9D0C', 'Sst_12': '#CB7900', 'Sst_12': '#DC8400', 'Sst_12': '#E68A00', 'Sst_12': '#E88B00', 'Sst_12': '#FF9B06', 'Sst_13': '#BF7200', 'Sst_13': '#C87800', 'Sst_13': '#DD8500', 'Sst_13': '#E08600', 'Sst_13': '#FF9900', 'Sst_14': '#B46C00', 'Sst_14': '#BE7100', 'Sst_14': '#D58000', 'Sst_14': '#D78100', 'Sst_14': '#F99500', 'Sst_15': '#B46C00', 'Sst_15': '#BC7100', 'Sst_15': '#CD7B00', 'Sst_15': '#F39200', 'Sst_16': '#B46C00', 'Sst_16': '#C47600', 'Sst_16': '#ED8E00', 'Sst_17': '#BC7100', 'Sst_17': '#E78B00', 'Sst_18': '#B46C00', 'Sst_18': '#E28700', 'Sst_19': '#DC8400', 'Sst_2': '#FFB13D', 'Sst_2': '#FFB342', 'Sst_2': '#FFB344', 'Sst_2': '#FFB445', 'Sst_20': '#D68000', 'Sst_21': '#D07D00', 'Sst_22': '#CB7900', 'Sst_23': '#C57600', 'Sst_24': '#BF7200', 'Sst_25': '#B96F00', 'Sst_26': '#B46C00', 'Sst_3': '#FFAD34', 'Sst_3': '#FFAE36', 'Sst_3': '#FFAF39', 'Sst_3': '#FFB03C', 'Sst_4': '#FFA92A', 'Sst_4': '#FFAA2B', 'Sst_4': '#FFAB2F', 'Sst_4': '#FFAD33', 'Sst_4': '#FFAE36', 'Sst_5': '#FFA41E', 'Sst_5': '#FFA623', 'Sst_5': '#FFA724', 'Sst_5': '#FFA929', 'Sst_5': '#FFAC30', 'Sst_6': '#FFA012', 'Sst_6': '#FFA31A', 'Sst_6': '#FFA520', 'Sst_6': '#FFA92A', 'Sst_7': '#FF9B06', 'Sst_7': '#FF9F0F', 'Sst_7': '#FF9F11', 'Sst_7': '#FFA217', 'Sst_7': '#FFA724', 'Sst_8': '#F99500', 'Sst_8': '#FF9B05', 'Sst_8': '#FF9C08', 'Sst_8': '#FF9E0D', 'Sst_8': '#FFA41E', 'Sst_9': '#ED8E00', 'Sst_9': '#FA9600', 'Sst_9': '#FF9900', 'Sst_9': '#FF9A04', 'Sst_9': '#FFA218', 'VLMC_1': '#697255', 'VLMC_1': '#848C74', 'VLMC_1': '#979E8A', 'VLMC_2': '#4A503C', 'VLMC_2': '#626B50', 'VLMC_2': '#788066', 'VLMC_3': '#565D45', 'VLMC_3': '#5E664C', 'VLMC_4': '#4A503C', 'Vip_1': '#C091D3', 'Vip_10': '#8B51A3', 'Vip_10': '#9657AF', 'Vip_10': '#9D5BB8', 'Vip_10': '#A561C0', 'Vip_10': '#A968C2', 'Vip_11': '#834C99', 'Vip_11': '#8F53A7', 'Vip_11': '#9758B1', 'Vip_11': '#A15DBC', 'Vip_11': '#A663C0', 'Vip_12': '#7B4790', 'Vip_12': '#884F9F', 'Vip_12': '#9154AA', 'Vip_12': '#9C5AB6', 'Vip_12': '#A45FBF', 'Vip_13': '#734387', 'Vip_13': '#814B97', 'Vip_13': '#8B51A3', 'Vip_13': '#9757B0', 'Vip_13': '#9F5CB9', 'Vip_14': '#7A478F', 'Vip_14': '#854D9C', 'Vip_14': '#9154AA', 'Vip_14': '#9B59B4', 'Vip_15': '#734387', 'Vip_15': '#7F4A95', 'Vip_15': '#8C51A4', 'Vip_15': '#9657AF', 'Vip_16': '#79468E', 'Vip_16': '#874E9E', 'Vip_16': '#9254AA', 'Vip_17': '#734387', 'Vip_17': '#824B98', 'Vip_17': '#8D52A5', 'Vip_18': '#7D4892', 'Vip_18': '#894FA0', 'Vip_19': '#78458C', 'Vip_19': '#844D9B', 'Vip_2': '#BB88CF', 'Vip_2': '#BC89D0', 'Vip_2': '#BC8AD0', 'Vip_2': '#BD8BD0', 'Vip_2': '#BD8CD1', 'Vip_20': '#734387', 'Vip_20': '#804A96', 'Vip_21': '#7B4891', 'Vip_22': '#77458C', 'Vip_23': '#734387', 'Vip_3': '#B680CC', 'Vip_3': '#B882CD', 'Vip_3': '#B984CE', 'Vip_3': '#BA86CE', 'Vip_3': '#BA87CF', 'Vip_4': '#B278C9', 'Vip_4': '#B47BCA', 'Vip_4': '#B57ECB', 'Vip_4': '#B781CC', 'Vip_4': '#B883CD', 'Vip_5': '#AD6FC5', 'Vip_5': '#B074C7', 'Vip_5': '#B278C9', 'Vip_5': '#B47BCA', 'Vip_5': '#B57ECB', 'Vip_6': '#A867C2', 'Vip_6': '#AC6DC4', 'Vip_6': '#AE71C6', 'Vip_6': '#B176C8', 'Vip_6': '#B37AC9', 'Vip_7': '#A45FBF', 'Vip_7': '#A866C1', 'Vip_7': '#AB6BC3', 'Vip_7': '#AE71C6', 'Vip_7': '#B075C8', 'Vip_8': '#9B5AB5', 'Vip_8': '#A45FBF', 'Vip_8': '#A765C1', 'Vip_8': '#AB6CC4', 'Vip_8': '#AE71C6', 'Vip_9': '#9355AC', 'Vip_9': '#9D5BB7', 'Vip_9': '#A45FBF', 'Vip_9': '#A866C2', 'Vip_9': '#AB6CC4', };
const mapDataforBorderChimp = { 'Astro_1': 'Astro_1', 'Astro_2': 'Astro_1', 'Chandelier_1': 'Chandelier_1', 'Chandelier_2': 'Chandelier_1', 'Endo_1': 'Endo_1', 'L2/3 IT_1': 'L2/3 IT_1', 'L2/3 IT_2': 'L2/3 IT_3', 'L2/3 IT_3': 'L2/3 IT_1', 'L2/3 IT_4': 'L2/3 IT_3', 'L2/3 IT_5': 'L2/3 IT_1', 'L2/3 IT_6': 'L2/3 IT_1', 'L2/3 IT_7': 'L2/3 IT_1', 'L4 IT_1': 'L4 IT_1', 'L4 IT_2': 'L4 IT_1', 'L4 IT_3': 'L4 IT_2', 'L4 IT_4': 'L2/3 IT_2', 'L5/6 NP_1': 'L5/6 NP_2', 'L5/6 NP_2': 'L5/6 NP_1', 'L5 ET_1': 'L5 ET_1', 'L5 ET_2': 'L5 ET_2', 'L5 IT_1': 'L5 IT_1', 'L5 IT_2': 'L5 IT_1', 'L5 IT_3': 'L5 IT_2', 'L5 IT_4': 'L5 IT_2', 'L6 CT_1': 'L6 CT_1', 'L6 CT_2': 'L6 CT_2', 'L6 CT_3': 'L6 CT_2', 'L6 IT Car3_1': 'L6 IT Car3_2', 'L6 IT Car3_2': 'L6 IT Car3_1', 'L6 IT_1': 'L6 IT_1', 'L6b_1': 'L6b_3', 'L6b_2': 'L6b_1', 'L6b_3': 'L6b_2', 'L6b_4': 'L6b_2', 'L6b_5': 'L6b_2', 'L6b_6': 'L6b_2', 'Lamp5_1': 'Lamp5_2', 'Lamp5_2': 'Lamp5_1', 'Lamp5_3': 'Lamp5_1', 'Lamp5_Lhx6_1': 'Lamp5_Lhx6_1', 'Lamp5_Lhx6_2': 'Lamp5_Lhx6_1', 'Micro-PVM_1': 'Micro-PVM_1', 'Micro-PVM_2': 'Micro-PVM_1', 'OPC_1': 'OPC_1', 'OPC_2': 'OPC_2', 'Oligo_1': 'Oligo_1', 'Oligo_2': 'Oligo_1', 'Pax6_1': 'Pax6_1', 'Pax6_2': 'Pax6_1', 'Pax6_3': 'Pax6_2', 'Pax6_4': 'Sncg_3', 'Pvalb_1': 'Pvalb_2', 'Pvalb_2': 'Pvalb_4', 'Pvalb_3': 'Pvalb_1', 'Pvalb_4': 'Pvalb_3', 'Pvalb_5': 'Pvalb_4', 'Pvalb_6': 'Pvalb_4', 'Pvalb_7': 'Pvalb_4', 'Pvalb_8': 'Pvalb_4', 'Pvalb_9': 'Sst_5', 'Sncg_1': 'Lamp5_2', 'Sncg_10': 'Vip_8', 'Sncg_2': 'Sncg_2', 'Sncg_3': 'Sncg_3', 'Sncg_4': 'Sncg_3', 'Sncg_5': 'Sncg_1', 'Sncg_6': 'Sncg_2', 'Sncg_7': 'Vip_8', 'Sncg_8': 'Sncg_2', 'Sncg_9': 'Sncg_2', 'Sst Chodl_1': 'Sst Chodl_1', 'Sst_1': 'Sst_5', 'Sst_10': 'Sst_2', 'Sst_11': 'Sst_8', 'Sst_12': 'Sst_8', 'Sst_13': 'Sst_5', 'Sst_14': 'Sst_4', 'Sst_15': 'Sst_3', 'Sst_2': 'Sst_9', 'Sst_3': 'Sst_3', 'Sst_4': 'Sst_3', 'Sst_5': 'Sst_7', 'Sst_6': 'Sst_6', 'Sst_7': 'Sst_7', 'Sst_8': 'Sst_5', 'Sst_9': 'Sst_1', 'VLMC_1': 'VLMC_1', 'Vip_1': 'Vip_8', 'Vip_10': 'Vip_2', 'Vip_11': 'Vip_2', 'Vip_12': 'Vip_8', 'Vip_13': 'Vip_2', 'Vip_14': 'Vip_2', 'Vip_15': 'Vip_8', 'Vip_16': 'Vip_8', 'Vip_17': 'Vip_8', 'Vip_18': 'Vip_7', 'Vip_19': 'Vip_6', 'Vip_2': 'Vip_5', 'Vip_20': 'Vip_7', 'Vip_3': 'Vip_5', 'Vip_4': 'Vip_7', 'Vip_5': 'Vip_1', 'Vip_6': 'Vip_3', 'Vip_7': 'Vip_3', 'Vip_8': 'Vip_3', 'Vip_9': 'Vip_4' };
const mapDataforBorderGorilla = { 'Astro_1': 'Astro_1', 'Astro_2': 'Astro_1', 'Astro_3': 'Astro_1', 'Astro_4': 'Astro_1', 'Chandelier_1': 'Chandelier_1', 'Chandelier_2': 'Chandelier_1', 'Endo_1': 'Endo_1', 'Endo_2': 'Endo_1', 'L2/3 IT_1': 'L2/3 IT_3', 'L2/3 IT_2': 'L2/3 IT_1', 'L2/3 IT_3': 'L2/3 IT_1', 'L2/3 IT_4': 'L2/3 IT_1', 'L4 IT_1': 'L4 IT_2', 'L4 IT_2': 'L2/3 IT_2', 'L4 IT_3': 'L4 IT_1', 'L4 IT_4': 'L4 IT_1', 'L4 IT_5': 'L2/3 IT_2', 'L5/6 NP_1': 'L5/6 NP_2', 'L5/6 NP_2': 'L5/6 NP_1', 'L5/6 NP_3': 'L5/6 NP_1', 'L5/6 NP_4': 'L5/6 NP_1', 'L5 ET_1': 'L5 ET_1', 'L5 ET_2': 'L5 ET_1', 'L5 ET_3': 'L5 ET_2', 'L5 ET_4': 'L5 ET_2', 'L5 IT_1': 'L5 IT_2', 'L5 IT_2': 'L5 IT_2', 'L5 IT_3': 'L5 IT_1', 'L6 CT_1': 'L6 CT_1', 'L6 CT_2': 'L6 CT_2', 'L6 IT Car3_1': 'L6 IT Car3_2', 'L6 IT Car3_2': 'L6 IT Car3_1', 'L6 IT Car3_3': 'L6 IT Car3_2', 'L6 IT_1': 'L6 IT_1', 'L6 IT_2': 'L6 IT_1', 'L6 IT_3': 'L6 IT_1', 'L6b_1': 'L6b_1', 'L6b_2': 'L6b_2', 'L6b_3': 'L6b_3', 'L6b_4': 'L6b_1', 'L6b_5': 'L6b_2', 'L6b_6': 'L6b_2', 'Lamp5_1': 'Lamp5_2', 'Lamp5_2': 'Lamp5_1', 'Lamp5_Lhx6_1': 'Lamp5_Lhx6_1', 'Lamp5_Lhx6_2': 'Lamp5_Lhx6_1', 'Micro-PVM_1': 'Micro-PVM_1', 'Micro-PVM_2': 'Micro-PVM_1', 'Micro-PVM_3': 'Micro-PVM_1', 'OPC_1': 'OPC_2', 'OPC_2': 'OPC_1', 'OPC_3': 'OPC_2', 'Oligo_1': 'Oligo_1', 'Pax6_1': 'Sncg_3', 'Pax6_2': 'Pax6_2', 'Pax6_3': 'Pax6_1', 'Pax6_4': 'Pax6_1', 'Pvalb_1': 'Pvalb_2', 'Pvalb_2': 'Pvalb_1', 'Pvalb_3': 'Pvalb_3', 'Pvalb_4': 'Pvalb_4', 'Pvalb_5': 'Pvalb_4', 'Pvalb_6': 'Pvalb_4', 'Pvalb_7': 'Pvalb_4', 'Pvalb_8': 'Sst_5', 'Sncg_1': 'Sncg_3', 'Sncg_2': 'Sncg_2', 'Sncg_3': 'Sncg_2', 'Sncg_4': 'Sncg_1', 'Sncg_5': 'Vip_8', 'Sncg_6': 'Sncg_1', 'Sncg_7': 'Vip_8', 'Sst Chodl_1': 'Sst Chodl_1', 'Sst Chodl_2': 'Sst Chodl_1', 'Sst Chodl_3': 'Sst_6', 'Sst_1': 'Sst_8', 'Sst_10': 'Sst_3', 'Sst_11': 'Sst_7', 'Sst_12': 'Sst_4', 'Sst_13': 'Sst_5', 'Sst_14': 'Sst_7', 'Sst_15': 'Sst_7', 'Sst_16': 'Sst_6', 'Sst_17': 'Sst_6', 'Sst_18': 'Sst_9', 'Sst_2': 'Sst_8', 'Sst_3': 'Sst_8', 'Sst_4': 'Sst_1', 'Sst_5': 'Sst_2', 'Sst_6': 'Sst_2', 'Sst_7': 'Sst_3', 'Sst_8': 'Sst_5', 'Sst_9': 'Sst_5', 'VLMC_1': 'VLMC_1', 'VLMC_2': 'VLMC_1', 'VLMC_3': 'VLMC_1', 'VLMC_4': 'VLMC_1', 'Vip_1': 'Vip_5', 'Vip_10': 'Vip_7', 'Vip_11': 'Vip_6', 'Vip_12': 'Vip_7', 'Vip_13': 'Vip_7', 'Vip_14': 'Vip_1', 'Vip_15': 'Vip_4', 'Vip_16': 'Vip_3', 'Vip_17': 'Vip_2', 'Vip_2': 'Vip_2', 'Vip_3': 'Vip_2', 'Vip_4': 'Vip_3', 'Vip_5': 'Vip_3', 'Vip_6': 'Vip_3', 'Vip_7': 'Vip_8', 'Vip_8': 'Vip_8', 'Vip_9': 'Vip_8' };
const mapDataforBorderHuman = { 'Astro_1': 'Astro_1', 'Astro_2': 'Astro_1', 'Astro_3': 'Astro_1', 'Astro_4': 'Astro_1', 'Astro_5': 'Astro_1', 'Chandelier_1': 'Chandelier_1', 'Chandelier_2': 'Chandelier_1', 'Endo_1': 'Endo_1', 'L2/3 IT_1': 'L2/3 IT_1', 'L2/3 IT_10': 'L2/3 IT_3', 'L2/3 IT_11': 'L2/3 IT_1', 'L2/3 IT_12': 'L2/3 IT_1', 'L2/3 IT_13': 'L2/3 IT_1', 'L2/3 IT_2': 'L2/3 IT_1', 'L2/3 IT_3': 'L2/3 IT_1', 'L2/3 IT_4': 'L2/3 IT_1', 'L2/3 IT_5': 'L2/3 IT_1', 'L2/3 IT_6': 'L2/3 IT_3', 'L2/3 IT_7': 'L2/3 IT_3', 'L2/3 IT_8': 'L2/3 IT_3', 'L2/3 IT_9': 'L2/3 IT_3', 'L4 IT_1': 'L4 IT_2', 'L4 IT_2': 'L4 IT_1', 'L4 IT_3': 'L4 IT_1', 'L4 IT_4': 'L2/3 IT_2', 'L5/6 NP_1': 'L5/6 NP_1', 'L5/6 NP_2': 'L5/6 NP_2', 'L5/6 NP_3': 'L5/6 NP_1', 'L5/6 NP_4': 'L5/6 NP_1', 'L5/6 NP_5': 'L5/6 NP_1', 'L5/6 NP_6': 'L5/6 NP_1', 'L5 ET_1': 'L5 ET_1', 'L5 ET_2': 'L5 ET_2', 'L5 IT_1': 'L5 IT_1', 'L5 IT_2': 'L5 IT_2', 'L5 IT_3': 'L5 IT_1', 'L5 IT_4': 'L5 IT_2', 'L5 IT_5': 'L5 IT_2', 'L5 IT_6': 'L5 IT_2', 'L5 IT_7': 'L5 IT_2', 'L6 CT_1': 'L6 CT_1', 'L6 CT_2': 'L6 CT_1', 'L6 CT_3': 'L6 CT_2', 'L6 CT_4': 'L6 CT_2', 'L6 IT Car3_1': 'L6 IT Car3_1', 'L6 IT Car3_2': 'L6 IT Car3_2', 'L6 IT Car3_3': 'L6 IT Car3_2', 'L6 IT_1': 'L6 IT_1', 'L6 IT_2': 'L6 IT_1', 'L6b_1': 'L6b_3', 'L6b_2': 'L6b_1', 'L6b_3': 'L6b_2', 'L6b_4': 'L6b_2', 'L6b_5': 'L6b_2', 'L6b_6': 'L6b_2', 'Lamp5_1': 'Lamp5_1', 'Lamp5_2': 'Lamp5_1', 'Lamp5_3': 'Lamp5_1', 'Lamp5_4': 'Lamp5_2', 'Lamp5_5': 'Lamp5_2', 'Lamp5_6': 'Lamp5_2', 'Lamp5_Lhx6_1': 'Lamp5_Lhx6_1', 'Micro-PVM_1': 'Micro-PVM_1', 'Micro-PVM_2': 'Micro-PVM_1', 'Micro-PVM_3': 'Micro-PVM_1', 'OPC_1': 'OPC_1', 'OPC_2': 'OPC_2', 'Oligo_1': 'Oligo_1', 'Oligo_2': 'Oligo_1', 'Oligo_3': 'Oligo_1', 'Oligo_4': 'Oligo_1', 'Pax6_1': 'Pax6_1', 'Pax6_2': 'Pax6_1', 'Pax6_3': 'Pax6_2', 'Pax6_4': 'Sncg_3', 'Pvalb_1': 'Pvalb_4', 'Pvalb_10': 'Pvalb_3', 'Pvalb_11': 'Pvalb_3', 'Pvalb_12': 'Pvalb_3', 'Pvalb_13': 'Pvalb_3', 'Pvalb_14': 'Pvalb_4', 'Pvalb_15': 'Pvalb_4', 'Pvalb_2': 'Pvalb_4', 'Pvalb_3': 'Pvalb_4', 'Pvalb_4': 'Pvalb_4', 'Pvalb_5': 'Pvalb_4', 'Pvalb_6': 'Pvalb_4', 'Pvalb_7': 'Pvalb_1', 'Pvalb_8': 'Sst_5', 'Pvalb_9': 'Pvalb_2', 'Sncg_1': 'Vip_8', 'Sncg_2': 'Vip_8', 'Sncg_3': 'Sncg_1', 'Sncg_4': 'Sncg_2', 'Sncg_5': 'Sncg_2', 'Sncg_6': 'Sncg_3', 'Sncg_7': 'Sncg_2', 'Sncg_8': 'Vip_8', 'Sst Chodl_1': 'Sst Chodl_1', 'Sst Chodl_2': 'Sst_6', 'Sst_1': 'Sst_1', 'Sst_10': 'Sst_3', 'Sst_11': 'Sst_6', 'Sst_12': 'Sst_2', 'Sst_13': 'Sst_3', 'Sst_14': 'Sst_3', 'Sst_15': 'Sst_2', 'Sst_16': 'Sst_4', 'Sst_17': 'Sst_4', 'Sst_18': 'Sst_3', 'Sst_19': 'Sst_4', 'Sst_2': 'Sst_5', 'Sst_20': 'Sst_5', 'Sst_21': 'Sst_5', 'Sst_22': 'Sst_6', 'Sst_23': 'Sst_7', 'Sst_24': 'Sst_7', 'Sst_25': 'Sst_7', 'Sst_26': 'Sst_7', 'Sst_3': 'Sst_5', 'Sst_4': 'Sst_8', 'Sst_5': 'Sst_8', 'Sst_6': 'Sst_8', 'Sst_7': 'Sst_8', 'Sst_8': 'Sst_3', 'Sst_9': 'Sst_9', 'VLMC_1': 'VLMC_1', 'VLMC_2': 'VLMC_1', 'Vip_1': 'Vip_1', 'Vip_10': 'Vip_7', 'Vip_11': 'Vip_1', 'Vip_12': 'Vip_2', 'Vip_13': 'Vip_1', 'Vip_14': 'Vip_8', 'Vip_15': 'Vip_8', 'Vip_16': 'Vip_8', 'Vip_17': 'Vip_2', 'Vip_18': 'Vip_2', 'Vip_19': 'Vip_2', 'Vip_2': 'Vip_3', 'Vip_20': 'Vip_2', 'Vip_21': 'Vip_4', 'Vip_22': 'Vip_4', 'Vip_23': 'Vip_3', 'Vip_3': 'Vip_3', 'Vip_4': 'Vip_5', 'Vip_5': 'Vip_6', 'Vip_6': 'Vip_7', 'Vip_7': 'Vip_5', 'Vip_8': 'Vip_7', 'Vip_9': 'Vip_7' };
const mapDataforBorderMarmoset = { 'Astro_1': 'Astro_1', 'Astro_2': 'Astro_1', 'Astro_3': 'Astro_1', 'Astro_4': 'Astro_1', 'Chandelier_1': 'Chandelier_1', 'Endo_1': 'Endo_1', 'Endo_2': 'Endo_1', 'Endo_3': 'Endo_1', 'L2/3 IT_1': 'L2/3 IT_3', 'L2/3 IT_2': 'L2/3 IT_1', 'L2/3 IT_3': 'L2/3 IT_1', 'L2/3 IT_4': 'L2/3 IT_1', 'L4 IT_1': 'L2/3 IT_2', 'L4 IT_2': 'L2/3 IT_2', 'L4 IT_3': 'L2/3 IT_1', 'L4 IT_4': 'L4 IT_2', 'L4 IT_5': 'L2/3 IT_2', 'L4 IT_6': 'L4 IT_1', 'L5/6 NP_1': 'L5/6 NP_1', 'L5/6 NP_2': 'L5/6 NP_2', 'L5 ET_1': 'L5 ET_1', 'L5 ET_2': 'L5 ET_2', 'L5 IT_1': 'L5 IT_2', 'L5 IT_2': 'L5 IT_2', 'L5 IT_3': 'L5 IT_1', 'L6 CT_1': 'L6 CT_2', 'L6 CT_2': 'L6 CT_1', 'L6 CT_3': 'L6 CT_2', 'L6 IT Car3_1': 'L6 IT Car3_2', 'L6 IT Car3_2': 'L6 IT Car3_2', 'L6 IT Car3_3': 'L6 IT Car3_1', 'L6 IT_1': 'L6 IT_1', 'L6 IT_2': 'L6 IT_1', 'L6 IT_3': 'L6 IT_1', 'L6b_1': 'L6b_2', 'L6b_2': 'L6b_3', 'L6b_3': 'L6b_1', 'Lamp5_1': 'Lamp5_2', 'Lamp5_2': 'Lamp5_1', 'Lamp5_Lhx6_1': 'Lamp5_Lhx6_1', 'Micro-PVM_1': 'Micro-PVM_1', 'Micro-PVM_2': 'Micro-PVM_1', 'Micro-PVM_3': 'Micro-PVM_1', 'Micro-PVM_4': 'Micro-PVM_1', 'OPC_1': 'OPC_1', 'OPC_2': 'OPC_2', 'OPC_3': 'OPC_2', 'OPC_4': 'OPC_2', 'Oligo_1': 'Oligo_1', 'Oligo_2': 'Oligo_1', 'Pax6_1': 'Pax6_1', 'Pax6_2': 'Pax6_1', 'Pax6_3': 'Sncg_3', 'Pvalb_1': 'Pvalb_3', 'Pvalb_2': 'Pvalb_4', 'Pvalb_3': 'Pvalb_4', 'Pvalb_4': 'Pvalb_4', 'Pvalb_5': 'Pvalb_1', 'Pvalb_6': 'Pvalb_2', 'Sncg_1': 'Pax6_2', 'Sncg_2': 'Vip_8', 'Sncg_3': 'Sncg_2', 'Sncg_4': 'Sncg_3', 'Sncg_5': 'Pax6_2', 'Sncg_6': 'Sncg_3', 'Sncg_7': 'Sncg_1', 'Sncg_8': 'Sncg_1', 'Sncg_9': 'Vip_8', 'Sst Chodl_1': 'Sst Chodl_1', 'Sst Chodl_2': 'Sst_6', 'Sst_1': 'Sst_7', 'Sst_10': 'Sst_8', 'Sst_11': 'Sst_8', 'Sst_12': 'Sst_7', 'Sst_13': 'Sst_6', 'Sst_14': 'Sst_5', 'Sst_15': 'Sst_7', 'Sst_16': 'Sst_5', 'Sst_2': 'Sst_4', 'Sst_3': 'Sst_9', 'Sst_4': 'Sst_3', 'Sst_5': 'Sst_9', 'Sst_6': 'Sst_3', 'Sst_7': 'Sst_1', 'Sst_8': 'Sst_2', 'Sst_9': 'Sst_2', 'VLMC_1': 'VLMC_1', 'VLMC_2': 'VLMC_1', 'VLMC_3': 'VLMC_1', 'VLMC_4': 'VLMC_1', 'Vip_1': 'Vip_6', 'Vip_10': 'Vip_3', 'Vip_11': 'Vip_7', 'Vip_12': 'Vip_7', 'Vip_13': 'Vip_1', 'Vip_2': 'Vip_4', 'Vip_3': 'Vip_5', 'Vip_4': 'Vip_8', 'Vip_5': 'Vip_8', 'Vip_6': 'Vip_2', 'Vip_7': 'Vip_2', 'Vip_8': 'Vip_2', 'Vip_9': 'Vip_2' };
const mapDataforBorderRhesus = { 'Astro_1': 'Astro_1', 'Astro_2': 'Astro_1', 'Astro_3': 'Astro_1', 'Chandelier_1': 'Chandelier_1', 'Chandelier_2': 'Chandelier_1', 'Endo_1': 'Endo_1', 'L2/3 IT_1': 'L2/3 IT_1', 'L2/3 IT_10': 'L2/3 IT_3', 'L2/3 IT_11': 'L2/3 IT_1', 'L2/3 IT_12': 'L2/3 IT_1', 'L2/3 IT_13': 'L2/3 IT_1', 'L2/3 IT_14': 'L2/3 IT_1', 'L2/3 IT_15': 'L2/3 IT_1', 'L2/3 IT_2': 'L2/3 IT_1', 'L2/3 IT_3': 'L2/3 IT_3', 'L2/3 IT_4': 'L2/3 IT_3', 'L2/3 IT_5': 'L2/3 IT_3', 'L2/3 IT_6': 'L2/3 IT_3', 'L2/3 IT_7': 'L2/3 IT_1', 'L2/3 IT_8': 'L2/3 IT_1', 'L2/3 IT_9': 'L2/3 IT_1', 'L4 IT_1': 'L4 IT_1', 'L4 IT_2': 'L4 IT_2', 'L4 IT_3': 'L2/3 IT_2', 'L5/6 NP_1': 'L5/6 NP_2', 'L5/6 NP_2': 'L5/6 NP_1', 'L5/6 NP_3': 'L5/6 NP_1', 'L5/6 NP_4': 'L5/6 NP_1', 'L5/6 NP_5': 'L5/6 NP_1', 'L5/6 NP_6': 'L5/6 NP_1', 'L5/6 NP_7': 'L5/6 NP_1', 'L5/6 NP_8': 'L5/6 NP_1', 'L5 ET_1': 'L5 ET_2', 'L5 ET_2': 'L5 ET_1', 'L5 IT_1': 'L5 IT_2', 'L5 IT_2': 'L5 IT_1', 'L5 IT_3': 'L5 IT_2', 'L5 IT_4': 'L5 IT_2', 'L6 CT_1': 'L6 CT_2', 'L6 CT_2': 'L6 CT_1', 'L6 CT_3': 'L6 CT_1', 'L6 CT_4': 'L6 CT_1', 'L6 IT Car3_1': 'L6 IT Car3_1', 'L6 IT Car3_2': 'L6 IT Car3_2', 'L6 IT_1': 'L6 IT_1', 'L6 IT_2': 'L6 IT_1', 'L6 IT_3': 'L6 IT_1', 'L6 IT_4': 'L6 IT_1', 'L6b_1': 'L6b_2', 'L6b_2': 'L6b_2', 'L6b_3': 'L6b_1', 'L6b_4': 'L6b_3', 'Lamp5_1': 'Lamp5_2', 'Lamp5_2': 'Lamp5_2', 'Lamp5_3': 'Lamp5_1', 'Lamp5_4': 'Lamp5_1', 'Lamp5_Lhx6_1': 'Lamp5_Lhx6_1', 'Micro-PVM_1': 'Micro-PVM_1', 'Micro-PVM_2': 'Micro-PVM_1', 'Micro-PVM_3': 'Micro-PVM_1', 'OPC_1': 'OPC_1', 'OPC_2': 'OPC_2', 'OPC_3': 'OPC_2', 'Oligo_1': 'Oligo_1', 'Oligo_2': 'Oligo_1', 'Pax6_1': 'Pax6_1', 'Pax6_2': 'Pax6_1', 'Pax6_3': 'Pax6_2', 'Pax6_4': 'Sncg_3', 'Pvalb_1': 'Pvalb_3', 'Pvalb_10': 'Pvalb_4', 'Pvalb_2': 'Pvalb_4', 'Pvalb_3': 'Pvalb_2', 'Pvalb_4': 'Pvalb_1', 'Pvalb_5': 'Pvalb_1', 'Pvalb_6': 'Pvalb_4', 'Pvalb_7': 'Pvalb_4', 'Pvalb_8': 'Pvalb_4', 'Pvalb_9': 'Pvalb_4', 'Sncg_1': 'Sncg_2', 'Sncg_2': 'Sncg_2', 'Sncg_3': 'Sncg_2', 'Sncg_4': 'Sncg_2', 'Sncg_5': 'Vip_8', 'Sncg_6': 'Vip_8', 'Sncg_7': 'Sncg_1', 'Sst Chodl_1': 'Sst Chodl_1', 'Sst Chodl_2': 'Sst_6', 'Sst_1': 'Sst_1', 'Sst_10': 'Sst_7', 'Sst_11': 'Sst_6', 'Sst_12': 'Sst_8', 'Sst_13': 'Sst_5', 'Sst_14': 'Sst_2', 'Sst_2': 'Sst_4', 'Sst_3': 'Sst_4', 'Sst_4': 'Sst_9', 'Sst_5': 'Sst_9', 'Sst_6': 'Sst_3', 'Sst_7': 'Sst_3', 'Sst_8': 'Sst_7', 'Sst_9': 'Sst_7', 'VLMC_1': 'VLMC_1', 'VLMC_2': 'VLMC_1', 'Vip_1': 'Vip_8', 'Vip_10': 'Vip_5', 'Vip_11': 'Vip_6', 'Vip_12': 'Vip_7', 'Vip_13': 'Vip_7', 'Vip_14': 'Vip_7', 'Vip_15': 'Vip_7', 'Vip_2': 'Vip_7', 'Vip_3': 'Vip_2', 'Vip_4': 'Vip_1', 'Vip_5': 'Vip_3', 'Vip_6': 'Vip_3', 'Vip_7': 'Vip_4', 'Vip_8': 'Vip_8', 'Vip_9': 'Vip_8' };
var cross_speciesClusterInfo = { 'Chandelier_1': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'L2/3 IT_1': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'L2/3 IT_2': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'L2/3 IT_3': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'L4 IT_1': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'L4 IT_2': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'L5 ET_1': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'L5 ET_2': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'L5 IT_1': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'L5 IT_2': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'L5/6 NP_1': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'L5/6 NP_2': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'L6 CT_1': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'L6 CT_2': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'L6 IT_1': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'L6 IT Car3_1': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'L6 IT Car3_2': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'L6b_1': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'L6b_2': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'L6b_3': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Lamp5_1': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Lamp5_2': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Lamp5_Lhx6_1': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Pax6_1': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Pax6_2': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Pvalb_1': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Pvalb_2': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Pvalb_3': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Pvalb_4': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Sncg_1': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Sncg_2': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Sncg_3': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Sst_1': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Sst_2': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Sst_3': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Sst_4': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Sst_5': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Sst_6': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Sst_7': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Sst_8': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Sst_9': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Sst Chodl_1': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Vip_1': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Vip_2': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Vip_3': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Vip_4': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Vip_5': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Vip_6': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Vip_7': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Vip_8': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Astro_1': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Endo_1': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Micro-PVM_1': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Oligo_1': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'OPC_1': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'OPC_2': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'VLMC_1': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 } }

const layerInfoForChimp = { 'Vip_19': { 1: 0.0, 2: 0.67, 3: 0.0, 4: 0.33, 5: 0.0, 6: 0.0 }, 'Lamp5_3': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'L4 IT_3': { 1: 0.0, 2: 0.03, 3: 0.03, 4: 0.47, 5: 0.47, 6: 0.0 }, 'Vip_10': { 1: 0.75, 2: 0.25, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Vip_17': { 1: 0.0, 2: 0.33, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.67 }, 'L5 ET_1': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.5, 5: 0.5, 6: 0.0 }, 'Sst_9': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.25, 6: 0.75 }, 'Vip_20': { 1: 0.67, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.33, 6: 0.0 }, 'L6 IT Car3_2': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.3, 5: 0.4, 6: 0.3 }, 'L5 IT_4': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.32, 5: 0.63, 6: 0.05 }, 'Sst_22': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Pvalb_1': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.15, 5: 0.54, 6: 0.31 }, 'Sncg_6': { 1: 0.87, 2: 0.0, 3: 0.0, 4: 0.04, 5: 0.09, 6: 0.0 }, 'L5 ET_4': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'VLMC_2': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'OPC_2': { 1: 0.33, 2: 0.1, 3: 0.12, 4: 0.08, 5: 0.06, 6: 0.33 }, 'Vip_4': { 1: 1.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Sncg_10': { 1: 0.89, 2: 0.11, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Vip_8': { 1: 0.33, 2: 0.0, 3: 0.0, 4: 0.33, 5: 0.33, 6: 0.0 }, 'Sst_21': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Astro_1': { 1: 0.3, 2: 0.18, 3: 0.14, 4: 0.09, 5: 0.13, 6: 0.16 }, 'L6 IT_2': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'L2/3 IT_10': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'L5 ET_2': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.33, 5: 0.5, 6: 0.17 }, 'Sst Chodl_3': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'L4 IT_1': { 1: 0.0, 2: 0.02, 3: 0.08, 4: 0.59, 5: 0.31, 6: 0.01 }, 'Pax6_1': { 1: 0.0, 2: 0.5, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.5 }, 'L2/3 IT_12': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Sncg_7': { 1: 0.8, 2: 0.0, 3: 0.2, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Pvalb_4': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.15, 6: 0.85 }, 'Endo_1': { 1: 0.67, 2: 0.08, 3: 0.08, 4: 0.0, 5: 0.0, 6: 0.17 }, 'Sst Chodl_2': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Sncg_1': { 1: 0.67, 2: 0.19, 3: 0.1, 4: 0.05, 5: 0.0, 6: 0.0 }, 'Vip_3': { 1: 0.12, 2: 0.25, 3: 0.25, 4: 0.19, 5: 0.19, 6: 0.0 }, 'Sst_5': { 1: 0.38, 2: 0.38, 3: 0.2, 4: 0.02, 5: 0.02, 6: 0.0 }, 'Vip_18': { 1: 0.5, 2: 0.3, 3: 0.2, 4: 0.0, 5: 0.0, 6: 0.0 }, 'L5/6 NP_4': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Sst_26': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Lamp5_5': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Sncg_9': { 1: 1.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Oligo_2': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 1.0 }, 'L4 IT_4': { 1: 0.07, 2: 0.02, 3: 0.12, 4: 0.55, 5: 0.22, 6: 0.02 }, 'Sncg_4': { 1: 0.62, 2: 0.38, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'L2/3 IT_11': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Vip_11': { 1: 1.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Sst_12': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.11, 5: 0.33, 6: 0.56 }, 'L5/6 NP_3': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Sncg_5': { 1: 0.0, 2: 1.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'L2/3 IT_7': { 1: 0.19, 2: 0.0, 3: 0.19, 4: 0.38, 5: 0.25, 6: 0.0 }, 'Pvalb_10': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Vip_5': { 1: 0.31, 2: 0.28, 3: 0.28, 4: 0.07, 5: 0.07, 6: 0.0 }, 'L2/3 IT_3': { 1: 0.41, 2: 0.36, 3: 0.12, 4: 0.04, 5: 0.07, 6: 0.0 }, 'L6 IT Car3_1': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.02, 5: 0.66, 6: 0.32 }, 'Vip_15': { 1: 0.14, 2: 0.43, 3: 0.14, 4: 0.14, 5: 0.0, 6: 0.14 }, 'Micro-PVM_3': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'OPC_1': { 1: 0.5, 2: 0.0, 3: 0.0, 4: 0.5, 5: 0.0, 6: 0.0 }, 'Chandelier_1': { 1: 0.29, 2: 0.21, 3: 0.21, 4: 0.07, 5: 0.0, 6: 0.21 }, 'L5 IT_3': { 1: 0.0, 2: 0.01, 3: 0.0, 4: 0.21, 5: 0.7, 6: 0.08 }, 'L2/3 IT_5': { 1: 0.09, 2: 0.11, 3: 0.29, 4: 0.33, 5: 0.18, 6: 0.0 }, 'Sst_23': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Astro_2': { 1: 0.9, 2: 0.04, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.06 }, 'Pax6_2': { 1: 0.72, 2: 0.17, 3: 0.06, 4: 0.0, 5: 0.0, 6: 0.06 }, 'Pvalb_2': { 1: 0.17, 2: 0.0, 3: 0.0, 4: 0.5, 5: 0.33, 6: 0.0 }, 'Astro_4': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Pvalb_15': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Vip_2': { 1: 0.2, 2: 0.2, 3: 0.0, 4: 0.2, 5: 0.4, 6: 0.0 }, 'Vip_12': { 1: 0.0, 2: 0.0, 3: 0.33, 4: 0.67, 5: 0.0, 6: 0.0 }, 'L2/3 IT_9': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'L2/3 IT_1': { 1: 0.14, 2: 0.29, 3: 0.14, 4: 0.0, 5: 0.43, 6: 0.0 }, 'L5 ET_3': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Lamp5_2': { 1: 0.32, 2: 0.21, 3: 0.15, 4: 0.09, 5: 0.13, 6: 0.09 }, 'Pvalb_3': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.08, 6: 0.92 }, 'L6b_2': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 1.0 }, 'Oligo_3': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Sst_8': { 1: 0.53, 2: 0.29, 3: 0.12, 4: 0.0, 5: 0.06, 6: 0.0 }, 'Sst_25': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'L5/6 NP_2': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.09, 5: 0.45, 6: 0.45 }, 'L6b_3': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.38, 6: 0.62 }, 'L6 IT_3': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Oligo_1': { 1: 0.11, 2: 0.04, 3: 0.05, 4: 0.1, 5: 0.14, 6: 0.57 }, 'Astro_5': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Astro_3': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Sst_14': { 1: 0.0, 2: 0.0, 3: 0.06, 4: 0.67, 5: 0.28, 6: 0.0 }, 'Pvalb_5': { 1: 0.27, 2: 0.0, 3: 0.0, 4: 0.09, 5: 0.45, 6: 0.18 }, 'L5 IT_6': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Sst_24': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Lamp5_1': { 1: 0.87, 2: 0.04, 3: 0.07, 4: 0.02, 5: 0.0, 6: 0.0 }, 'L2/3 IT_4': { 1: 0.28, 2: 0.46, 3: 0.17, 4: 0.04, 5: 0.05, 6: 0.0 }, 'L6 IT_1': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.32, 6: 0.68 }, 'L4 IT_5': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Pvalb_6': { 1: 0.17, 2: 0.23, 3: 0.28, 4: 0.28, 5: 0.03, 6: 0.01 }, 'L5 IT_1': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.94, 6: 0.06 }, 'Vip_16': { 1: 0.0, 2: 0.25, 3: 0.5, 4: 0.0, 5: 0.25, 6: 0.0 }, 'Sst_10': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.5, 6: 0.5 }, 'Pvalb_11': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Sncg_2': { 1: 0.78, 2: 0.06, 3: 0.11, 4: 0.06, 5: 0.0, 6: 0.0 }, 'Sst_16': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Lamp5_6': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Pvalb_12': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'L5/6 NP_6': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Vip_13': { 1: 0.22, 2: 0.15, 3: 0.07, 4: 0.15, 5: 0.07, 6: 0.33 }, 'Micro-PVM_2': { 1: 0.5, 2: 0.0, 3: 0.0, 4: 0.17, 5: 0.17, 6: 0.17 }, 'L6b_6': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 1.0 }, 'L2/3 IT_6': { 1: 0.15, 2: 0.14, 3: 0.43, 4: 0.07, 5: 0.2, 6: 0.01 }, 'Sst_19': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'VLMC_1': { 1: 0.75, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.25 }, 'L6 CT_2': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 1.0 }, 'Sst_1': { 1: 0.21, 2: 0.29, 3: 0.36, 4: 0.07, 5: 0.07, 6: 0.0 }, 'L5 IT_5': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'OPC_3': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Lamp5_Lhx6_1': { 1: 0.32, 2: 0.14, 3: 0.09, 4: 0.14, 5: 0.05, 6: 0.27 }, 'L6b_1': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.09, 6: 0.91 }, 'Pvalb_14': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Sst Chodl_1': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 1.0 }, 'Vip_22': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Chandelier_2': { 1: 0.23, 2: 0.08, 3: 0.0, 4: 0.38, 5: 0.31, 6: 0.0 }, 'Lamp5_4': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Sncg_8': { 1: 0.67, 2: 0.33, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Sncg_3': { 1: 0.6, 2: 0.2, 3: 0.0, 4: 0.0, 5: 0.2, 6: 0.0 }, 'Sst_15': { 1: 0.07, 2: 0.0, 3: 0.0, 4: 0.43, 5: 0.39, 6: 0.11 }, 'L4 IT_2': { 1: 0.06, 2: 0.06, 3: 0.11, 4: 0.56, 5: 0.22, 6: 0.0 }, 'Sst_13': { 1: 0.17, 2: 0.11, 3: 0.23, 4: 0.38, 5: 0.11, 6: 0.02 }, 'L2/3 IT_2': { 1: 0.14, 2: 0.43, 3: 0.29, 4: 0.0, 5: 0.14, 6: 0.0 }, 'Oligo_4': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'L6 CT_4': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Sst_2': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.29, 5: 0.57, 6: 0.14 }, 'Sst_20': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'L2/3 IT_13': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Pax6_3': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.5, 5: 0.5, 6: 0.0 }, 'L2/3 IT_8': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Micro-PVM_1': { 1: 0.36, 2: 0.07, 3: 0.07, 4: 0.21, 5: 0.0, 6: 0.29 }, 'L6b_4': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.8, 6: 0.2 }, 'Vip_9': { 1: 0.69, 2: 0.08, 3: 0.08, 4: 0.0, 5: 0.08, 6: 0.08 }, 'Vip_21': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'L5 IT_2': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.13, 5: 0.74, 6: 0.13 }, 'L5/6 NP_5': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Vip_7': { 1: 0.11, 2: 0.0, 3: 0.0, 4: 0.44, 5: 0.44, 6: 0.0 }, 'Vip_23': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Pvalb_7': { 1: 0.02, 2: 0.07, 3: 0.05, 4: 0.51, 5: 0.22, 6: 0.12 }, 'Sst_3': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.29, 5: 0.14, 6: 0.57 }, 'L6 CT_3': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 1.0 }, 'L6b_5': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.3, 6: 0.7 }, 'L6 CT_1': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.09, 6: 0.91 }, 'Pax6_4': { 1: 0.2, 2: 0.2, 3: 0.2, 4: 0.0, 5: 0.2, 6: 0.2 }, 'Sst_17': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Pvalb_13': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Pvalb_8': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'L5 IT_7': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Sst_6': { 1: 1.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Vip_6': { 1: 0.06, 2: 0.19, 3: 0.25, 4: 0.44, 5: 0.06, 6: 0.0 }, 'Sst_4': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 1.0, 5: 0.0, 6: 0.0 }, 'VLMC_3': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Sst_18': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'L5/6 NP_1': { 1: 0.0, 2: 0.0, 3: 0.02, 4: 0.06, 5: 0.59, 6: 0.33 }, 'Sst_11': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.21, 5: 0.17, 6: 0.62 }, 'Pvalb_9': { 1: 0.0, 2: 0.5, 3: 0.0, 4: 0.0, 5: 0.5, 6: 0.0 }, 'Vip_1': { 1: 1.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Vip_14': { 1: 0.17, 2: 0.2, 3: 0.22, 4: 0.12, 5: 0.29, 6: 0.0 }, 'L6 IT Car3_3': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Sst_7': { 1: 0.36, 2: 0.45, 3: 0.05, 4: 0.09, 5: 0.05, 6: 0.0 }, 'Lamp5_Lhx6_2': { 1: 0.0, 2: 0.0, 3: 0.03, 4: 0.15, 5: 0.09, 6: 0.74 } };
const layerInfoForGorilla = { 'Vip_19': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Lamp5_3': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'L4 IT_3': { 1: 0.0, 2: 0.0, 3: 0.03, 4: 0.57, 5: 0.32, 6: 0.07 }, 'Vip_10': { 1: 0.0, 2: 1.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Vip_17': { 1: 0.61, 2: 0.22, 3: 0.0, 4: 0.17, 5: 0.0, 6: 0.0 }, 'L5 ET_1': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.67, 6: 0.33 }, 'Sst_9': { 1: 0.0, 2: 0.0, 3: 0.61, 4: 0.28, 5: 0.06, 6: 0.06 }, 'Vip_20': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'L6 IT Car3_2': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.27, 5: 0.68, 6: 0.05 }, 'L5 IT_4': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Sst_22': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Pvalb_1': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.78, 6: 0.22 }, 'Sncg_6': { 1: 0.8, 2: 0.2, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'L5 ET_4': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 1.0, 6: 0.0 }, 'VLMC_2': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'OPC_2': { 1: 0.27, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.18, 6: 0.55 }, 'Vip_4': { 1: 0.07, 2: 0.0, 3: 0.4, 4: 0.33, 5: 0.13, 6: 0.07 }, 'Sncg_10': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Vip_8': { 1: 0.0, 2: 0.5, 3: 0.5, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Sst_21': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Astro_1': { 1: 0.21, 2: 0.15, 3: 0.23, 4: 0.16, 5: 0.16, 6: 0.08 }, 'L6 IT_2': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.37, 6: 0.63 }, 'L2/3 IT_10': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'L5 ET_2': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.5, 5: 0.5, 6: 0.0 }, 'Sst Chodl_3': { 1: 0.0, 2: 0.0, 3: 1.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'L4 IT_1': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.55, 5: 0.35, 6: 0.09 }, 'Pax6_1': { 1: 0.0, 2: 0.0, 3: 0.2, 4: 0.2, 5: 0.2, 6: 0.4 }, 'L2/3 IT_12': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Sncg_7': { 1: 0.85, 2: 0.0, 3: 0.11, 4: 0.04, 5: 0.0, 6: 0.0 }, 'Pvalb_4': { 1: 0.0, 2: 0.0, 3: 1.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Endo_1': { 1: 0.0, 2: 0.6, 3: 0.2, 4: 0.2, 5: 0.0, 6: 0.0 }, 'Sst Chodl_2': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 1.0, 5: 0.0, 6: 0.0 }, 'Sncg_1': { 1: 0.92, 2: 0.08, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Vip_3': { 1: 0.0, 2: 0.0, 3: 1.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Sst_5': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.5, 6: 0.5 }, 'Vip_18': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'L5/6 NP_4': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.11, 5: 0.81, 6: 0.08 }, 'Sst_26': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Lamp5_5': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Sncg_9': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Oligo_2': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'L4 IT_4': { 1: 0.0, 2: 0.0, 3: 0.25, 4: 0.38, 5: 0.12, 6: 0.25 }, 'Sncg_4': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'L2/3 IT_11': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Vip_11': { 1: 0.0, 2: 0.83, 3: 0.17, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Sst_12': { 1: 0.0, 2: 0.0, 3: 0.11, 4: 0.56, 5: 0.23, 6: 0.09 }, 'L5/6 NP_3': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.33, 5: 0.5, 6: 0.17 }, 'Sncg_5': { 1: 0.67, 2: 0.33, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'L2/3 IT_7': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Pvalb_10': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Vip_5': { 1: 0.09, 2: 0.09, 3: 0.45, 4: 0.27, 5: 0.09, 6: 0.0 }, 'L2/3 IT_3': { 1: 0.0, 2: 0.19, 3: 0.52, 4: 0.19, 5: 0.04, 6: 0.07 }, 'L6 IT Car3_1': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.02, 5: 0.71, 6: 0.27 }, 'Vip_15': { 1: 1.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Micro-PVM_3': { 1: 0.27, 2: 0.23, 3: 0.14, 4: 0.14, 5: 0.18, 6: 0.05 }, 'OPC_1': { 1: 0.0, 2: 0.0, 3: 1.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Chandelier_1': { 1: 0.0, 2: 0.27, 3: 0.36, 4: 0.18, 5: 0.09, 6: 0.09 }, 'L5 IT_3': { 1: 0.0, 2: 0.01, 3: 0.0, 4: 0.08, 5: 0.79, 6: 0.12 }, 'L2/3 IT_5': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Sst_23': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Astro_2': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 1.0 }, 'Pax6_2': { 1: 0.0, 2: 0.25, 3: 0.5, 4: 0.25, 5: 0.0, 6: 0.0 }, 'Pvalb_2': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.33, 6: 0.67 }, 'Astro_4': { 1: 0.83, 2: 0.08, 3: 0.08, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Pvalb_15': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Vip_2': { 1: 0.09, 2: 0.16, 3: 0.24, 4: 0.2, 5: 0.24, 6: 0.07 }, 'Vip_12': { 1: 0.6, 2: 0.2, 3: 0.2, 4: 0.0, 5: 0.0, 6: 0.0 }, 'L2/3 IT_9': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'L2/3 IT_1': { 1: 0.41, 2: 0.44, 3: 0.13, 4: 0.0, 5: 0.0, 6: 0.02 }, 'L5 ET_3': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.67, 6: 0.33 }, 'Lamp5_2': { 1: 0.22, 2: 0.11, 3: 0.28, 4: 0.22, 5: 0.07, 6: 0.11 }, 'Pvalb_3': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.17, 5: 0.31, 6: 0.52 }, 'L6b_2': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.36, 6: 0.64 }, 'Oligo_3': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Sst_8': { 1: 0.0, 2: 0.0, 3: 0.4, 4: 0.46, 5: 0.11, 6: 0.04 }, 'Sst_25': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'L5/6 NP_2': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.09, 5: 0.91, 6: 0.0 }, 'L6b_3': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.17, 6: 0.83 }, 'L6 IT_3': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.15, 6: 0.85 }, 'Oligo_1': { 1: 0.12, 2: 0.05, 3: 0.09, 4: 0.12, 5: 0.22, 6: 0.4 }, 'Astro_5': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Astro_3': { 1: 0.88, 2: 0.12, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Sst_14': { 1: 0.25, 2: 0.36, 3: 0.31, 4: 0.06, 5: 0.0, 6: 0.03 }, 'Pvalb_5': { 1: 0.0, 2: 0.0, 3: 0.67, 4: 0.33, 5: 0.0, 6: 0.0 }, 'L5 IT_6': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Sst_24': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Lamp5_1': { 1: 0.88, 2: 0.08, 3: 0.04, 4: 0.0, 5: 0.0, 6: 0.0 }, 'L2/3 IT_4': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 1.0, 6: 0.0 }, 'L6 IT_1': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.1, 5: 0.75, 6: 0.15 }, 'L4 IT_5': { 1: 0.0, 2: 0.0, 3: 0.28, 4: 0.54, 5: 0.09, 6: 0.08 }, 'Pvalb_6': { 1: 0.01, 2: 0.1, 3: 0.24, 4: 0.4, 5: 0.21, 6: 0.04 }, 'L5 IT_1': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.17, 5: 0.74, 6: 0.1 }, 'Vip_16': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.5, 5: 0.5, 6: 0.0 }, 'Sst_10': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.37, 5: 0.5, 6: 0.13 }, 'Pvalb_11': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Sncg_2': { 1: 0.82, 2: 0.06, 3: 0.12, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Sst_16': { 1: 0.25, 2: 0.25, 3: 0.5, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Lamp5_6': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Pvalb_12': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'L5/6 NP_6': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Vip_13': { 1: 0.33, 2: 0.47, 3: 0.2, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Micro-PVM_2': { 1: 0.49, 2: 0.06, 3: 0.17, 4: 0.14, 5: 0.09, 6: 0.06 }, 'L6b_6': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.5, 6: 0.5 }, 'L2/3 IT_6': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Sst_19': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'VLMC_1': { 1: 0.12, 2: 0.25, 3: 0.25, 4: 0.12, 5: 0.25, 6: 0.0 }, 'L6 CT_2': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 1.0 }, 'Sst_1': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.78, 6: 0.22 }, 'L5 IT_5': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'OPC_3': { 1: 0.29, 2: 0.2, 3: 0.11, 4: 0.18, 5: 0.16, 6: 0.07 }, 'Lamp5_Lhx6_1': { 1: 0.22, 2: 0.11, 3: 0.22, 4: 0.0, 5: 0.17, 6: 0.28 }, 'L6b_1': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.5, 6: 0.5 }, 'Pvalb_14': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Sst Chodl_1': { 1: 0.0, 2: 0.0, 3: 1.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Vip_22': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Chandelier_2': { 1: 0.0, 2: 0.0, 3: 0.2, 4: 0.6, 5: 0.2, 6: 0.0 }, 'Lamp5_4': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Sncg_8': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Sncg_3': { 1: 0.83, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.17 }, 'Sst_15': { 1: 0.0, 2: 0.2, 3: 0.7, 4: 0.1, 5: 0.0, 6: 0.0 }, 'L4 IT_2': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.67, 5: 0.33, 6: 0.0 }, 'Sst_13': { 1: 0.31, 2: 0.25, 3: 0.22, 4: 0.17, 5: 0.03, 6: 0.03 }, 'L2/3 IT_2': { 1: 0.0, 2: 0.33, 3: 0.5, 4: 0.0, 5: 0.0, 6: 0.17 }, 'Oligo_4': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'L6 CT_4': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Sst_2': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.8, 6: 0.2 }, 'Sst_20': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'L2/3 IT_13': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Pax6_3': { 1: 0.87, 2: 0.07, 3: 0.07, 4: 0.0, 5: 0.0, 6: 0.0 }, 'L2/3 IT_8': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Micro-PVM_1': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 1.0, 6: 0.0 }, 'L6b_4': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 1.0 }, 'Vip_9': { 1: 0.12, 2: 0.25, 3: 0.38, 4: 0.25, 5: 0.0, 6: 0.0 }, 'Vip_21': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'L5 IT_2': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.17, 5: 0.73, 6: 0.1 }, 'L5/6 NP_5': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Vip_7': { 1: 0.0, 2: 0.0, 3: 0.33, 4: 0.0, 5: 0.33, 6: 0.33 }, 'Vip_23': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Pvalb_7': { 1: 0.4, 2: 0.6, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Sst_3': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.56, 6: 0.44 }, 'L6 CT_3': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'L6b_5': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.27, 6: 0.73 }, 'L6 CT_1': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.01, 5: 0.17, 6: 0.83 }, 'Pax6_4': { 1: 0.5, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.5 }, 'Sst_17': { 1: 0.43, 2: 0.57, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Pvalb_13': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Pvalb_8': { 1: 0.67, 2: 0.33, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'L5 IT_7': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Sst_6': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.33, 6: 0.67 }, 'Vip_6': { 1: 0.0, 2: 0.0, 3: 1.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Sst_4': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 1.0 }, 'VLMC_3': { 1: 0.0, 2: 1.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Sst_18': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.08, 5: 0.92, 6: 0.0 }, 'L5/6 NP_1': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Sst_11': { 1: 0.6, 2: 0.27, 3: 0.07, 4: 0.0, 5: 0.0, 6: 0.07 }, 'Pvalb_9': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Vip_1': { 1: 0.09, 2: 0.14, 3: 0.64, 4: 0.09, 5: 0.05, 6: 0.0 }, 'Vip_14': { 1: 0.23, 2: 0.33, 3: 0.33, 4: 0.09, 5: 0.0, 6: 0.02 }, 'L6 IT Car3_3': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.66, 6: 0.34 }, 'Sst_7': { 1: 0.0, 2: 0.0, 3: 0.2, 4: 0.8, 5: 0.0, 6: 0.0 }, 'Lamp5_Lhx6_2': { 1: 0.0, 2: 0.0, 3: 0.14, 4: 0.32, 5: 0.27, 6: 0.27 } };
const layerInfoForHuman = { 'Vip_19': { 1: 0.04, 2: 0.23, 3: 0.21, 4: 0.13, 5: 0.19, 6: 0.21 }, 'Lamp5_3': { 1: 0.69, 2: 0.17, 3: 0.08, 4: 0.0, 5: 0.06, 6: 0.0 }, 'L4 IT_3': { 1: 0.0, 2: 0.02, 3: 0.33, 4: 0.48, 5: 0.17, 6: 0.0 }, 'Vip_10': { 1: 0.05, 2: 0.27, 3: 0.68, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Vip_17': { 1: 0.0, 2: 0.0, 3: 0.27, 4: 0.45, 5: 0.18, 6: 0.09 }, 'L5 ET_1': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.25, 5: 0.75, 6: 0.0 }, 'Sst_9': { 1: 0.0, 2: 0.0, 3: 0.12, 4: 0.16, 5: 0.46, 6: 0.26 }, 'Vip_20': { 1: 0.0, 2: 0.08, 3: 0.0, 4: 0.17, 5: 0.42, 6: 0.33 }, 'L6 IT Car3_2': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.04, 5: 0.61, 6: 0.35 }, 'L5 IT_4': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 1.0, 5: 0.0, 6: 0.0 }, 'Sst_22': { 1: 0.09, 2: 0.68, 3: 0.23, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Pvalb_1': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.15, 5: 0.73, 6: 0.12 }, 'Sncg_6': { 1: 0.64, 2: 0.24, 3: 0.07, 4: 0.0, 5: 0.05, 6: 0.0 }, 'L5 ET_4': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'VLMC_2': { 1: 0.0, 2: 0.0, 3: 0.5, 4: 0.5, 5: 0.0, 6: 0.0 }, 'OPC_2': { 1: 0.04, 2: 0.18, 3: 0.27, 4: 0.19, 5: 0.17, 6: 0.14 }, 'Vip_4': { 1: 0.15, 2: 0.27, 3: 0.42, 4: 0.16, 5: 0.0, 6: 0.0 }, 'Sncg_10': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Vip_8': { 1: 0.57, 2: 0.35, 3: 0.04, 4: 0.04, 5: 0.0, 6: 0.0 }, 'Sst_21': { 1: 0.0, 2: 0.83, 3: 0.17, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Astro_1': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 1.0 }, 'L6 IT_2': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.01, 5: 0.2, 6: 0.8 }, 'L2/3 IT_10': { 1: 0.0, 2: 0.13, 3: 0.82, 4: 0.05, 5: 0.0, 6: 0.0 }, 'L5 ET_2': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.31, 5: 0.69, 6: 0.0 }, 'Sst Chodl_3': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'L4 IT_1': { 1: 0.0, 2: 0.01, 3: 0.05, 4: 0.7, 5: 0.22, 6: 0.02 }, 'Pax6_1': { 1: 0.69, 2: 0.25, 3: 0.04, 4: 0.0, 5: 0.0, 6: 0.01 }, 'L2/3 IT_12': { 1: 0.01, 2: 0.08, 3: 0.84, 4: 0.05, 5: 0.01, 6: 0.0 }, 'Sncg_7': { 1: 0.6, 2: 0.3, 3: 0.1, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Pvalb_4': { 1: 0.0, 2: 0.06, 3: 0.17, 4: 0.5, 5: 0.28, 6: 0.0 }, 'Endo_1': { 1: 0.0, 2: 0.17, 3: 0.5, 4: 0.0, 5: 0.17, 6: 0.17 }, 'Sst Chodl_2': { 1: 0.0, 2: 0.33, 3: 0.67, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Sncg_1': { 1: 0.53, 2: 0.37, 3: 0.1, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Vip_3': { 1: 0.0, 2: 0.0, 3: 0.52, 4: 0.4, 5: 0.08, 6: 0.0 }, 'Sst_5': { 1: 0.0, 2: 0.03, 3: 0.0, 4: 0.03, 5: 0.55, 6: 0.4 }, 'Vip_18': { 1: 0.0, 2: 0.0, 3: 0.42, 4: 0.38, 5: 0.15, 6: 0.04 }, 'L5/6 NP_4': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.09, 5: 0.69, 6: 0.22 }, 'Sst_26': { 1: 0.0, 2: 0.07, 3: 0.83, 4: 0.03, 5: 0.07, 6: 0.0 }, 'Lamp5_5': { 1: 0.85, 2: 0.13, 3: 0.01, 4: 0.0, 5: 0.01, 6: 0.01 }, 'Sncg_9': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Oligo_2': { 1: 0.03, 2: 0.03, 3: 0.17, 4: 0.17, 5: 0.24, 6: 0.35 }, 'L4 IT_4': { 1: 0.0, 2: 0.0, 3: 0.36, 4: 0.52, 5: 0.12, 6: 0.0 }, 'Sncg_4': { 1: 0.72, 2: 0.21, 3: 0.05, 4: 0.0, 5: 0.01, 6: 0.0 }, 'L2/3 IT_11': { 1: 0.0, 2: 0.01, 3: 0.89, 4: 0.09, 5: 0.01, 6: 0.0 }, 'Vip_11': { 1: 0.08, 2: 0.48, 3: 0.42, 4: 0.01, 5: 0.0, 6: 0.01 }, 'Sst_12': { 1: 0.0, 2: 0.02, 3: 0.0, 4: 0.09, 5: 0.43, 6: 0.47 }, 'L5/6 NP_3': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.09, 5: 0.64, 6: 0.27 }, 'Sncg_5': { 1: 0.87, 2: 0.12, 3: 0.0, 4: 0.0, 5: 0.01, 6: 0.0 }, 'L2/3 IT_7': { 1: 0.14, 2: 0.73, 3: 0.11, 4: 0.03, 5: 0.0, 6: 0.0 }, 'Pvalb_10': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.09, 5: 0.39, 6: 0.52 }, 'Vip_5': { 1: 0.08, 2: 0.35, 3: 0.46, 4: 0.12, 5: 0.0, 6: 0.0 }, 'L2/3 IT_3': { 1: 0.01, 2: 0.01, 3: 0.68, 4: 0.29, 5: 0.02, 6: 0.0 }, 'L6 IT Car3_1': { 1: 0.0, 2: 0.0, 3: 0.05, 4: 0.23, 5: 0.55, 6: 0.18 }, 'Vip_15': { 1: 0.15, 2: 0.26, 3: 0.45, 4: 0.06, 5: 0.05, 6: 0.03 }, 'Micro-PVM_3': { 1: 0.25, 2: 0.0, 3: 0.25, 4: 0.12, 5: 0.25, 6: 0.12 }, 'OPC_1': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.5, 6: 0.5 }, 'Chandelier_1': { 1: 0.0, 2: 0.32, 3: 0.47, 4: 0.16, 5: 0.05, 6: 0.0 }, 'L5 IT_3': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.07, 5: 0.7, 6: 0.23 }, 'L2/3 IT_5': { 1: 0.0, 2: 0.01, 3: 0.71, 4: 0.25, 5: 0.02, 6: 0.0 }, 'Sst_23': { 1: 0.12, 2: 0.59, 3: 0.19, 4: 0.0, 5: 0.06, 6: 0.03 }, 'Astro_2': { 1: 0.13, 2: 0.3, 3: 0.22, 4: 0.1, 5: 0.16, 6: 0.09 }, 'Pax6_2': { 1: 0.44, 2: 0.38, 3: 0.06, 4: 0.0, 5: 0.12, 6: 0.0 }, 'Pvalb_2': { 1: 0.0, 2: 0.14, 3: 0.67, 4: 0.16, 5: 0.02, 6: 0.01 }, 'Astro_4': { 1: 0.5, 2: 0.38, 3: 0.0, 4: 0.0, 5: 0.12, 6: 0.0 }, 'Pvalb_15': { 1: 0.0, 2: 0.01, 3: 0.29, 4: 0.37, 5: 0.28, 6: 0.05 }, 'Vip_2': { 1: 0.0, 2: 0.13, 3: 0.72, 4: 0.15, 5: 0.0, 6: 0.0 }, 'Vip_12': { 1: 0.05, 2: 0.29, 3: 0.57, 4: 0.1, 5: 0.0, 6: 0.0 }, 'L2/3 IT_9': { 1: 0.0, 2: 0.17, 3: 0.82, 4: 0.02, 5: 0.0, 6: 0.0 }, 'L2/3 IT_1': { 1: 0.15, 2: 0.55, 3: 0.28, 4: 0.01, 5: 0.01, 6: 0.0 }, 'L5 ET_3': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Lamp5_2': { 1: 0.04, 2: 0.17, 3: 0.49, 4: 0.17, 5: 0.07, 6: 0.06 }, 'Pvalb_3': { 1: 0.03, 2: 0.3, 3: 0.64, 4: 0.03, 5: 0.0, 6: 0.0 }, 'L6b_2': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 1.0 }, 'Oligo_3': { 1: 0.0, 2: 0.5, 3: 0.0, 4: 0.5, 5: 0.0, 6: 0.0 }, 'Sst_8': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.5, 6: 0.5 }, 'Sst_25': { 1: 0.01, 2: 0.54, 3: 0.44, 4: 0.01, 5: 0.0, 6: 0.0 }, 'L5/6 NP_2': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.27, 5: 0.52, 6: 0.21 }, 'L6b_3': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.5, 6: 0.5 }, 'L6 IT_3': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Oligo_1': { 1: 0.09, 2: 0.0, 3: 0.02, 4: 0.11, 5: 0.27, 6: 0.5 }, 'Astro_5': { 1: 0.7, 2: 0.3, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Astro_3': { 1: 0.37, 2: 0.05, 3: 0.0, 4: 0.0, 5: 0.05, 6: 0.53 }, 'Sst_14': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.62, 6: 0.38 }, 'Pvalb_5': { 1: 0.05, 2: 0.52, 3: 0.43, 4: 0.0, 5: 0.0, 6: 0.0 }, 'L5 IT_6': { 1: 0.0, 2: 0.01, 3: 0.13, 4: 0.54, 5: 0.31, 6: 0.01 }, 'Sst_24': { 1: 0.0, 2: 0.8, 3: 0.2, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Lamp5_1': { 1: 0.0, 2: 0.08, 3: 0.18, 4: 0.24, 5: 0.26, 6: 0.24 }, 'L2/3 IT_4': { 1: 0.0, 2: 0.0, 3: 0.68, 4: 0.25, 5: 0.05, 6: 0.02 }, 'L6 IT_1': { 1: 0.0, 2: 0.0, 3: 0.01, 4: 0.06, 5: 0.31, 6: 0.62 }, 'L4 IT_5': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Pvalb_6': { 1: 0.03, 2: 0.09, 3: 0.68, 4: 0.18, 5: 0.03, 6: 0.0 }, 'L5 IT_1': { 1: 0.0, 2: 0.0, 3: 0.01, 4: 0.2, 5: 0.62, 6: 0.17 }, 'Vip_16': { 1: 0.62, 2: 0.15, 3: 0.08, 4: 0.0, 5: 0.08, 6: 0.08 }, 'Sst_10': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.67, 6: 0.33 }, 'Pvalb_11': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.21, 6: 0.79 }, 'Sncg_2': { 1: 0.75, 2: 0.25, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Sst_16': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.12, 5: 0.75, 6: 0.12 }, 'Lamp5_6': { 1: 0.68, 2: 0.26, 3: 0.04, 4: 0.0, 5: 0.02, 6: 0.0 }, 'Pvalb_12': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.04, 5: 0.46, 6: 0.5 }, 'L5/6 NP_6': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.33, 5: 0.67, 6: 0.0 }, 'Vip_13': { 1: 0.04, 2: 0.47, 3: 0.47, 4: 0.01, 5: 0.01, 6: 0.0 }, 'Micro-PVM_2': { 1: 0.12, 2: 0.23, 3: 0.36, 4: 0.08, 5: 0.12, 6: 0.09 }, 'L6b_6': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.01, 5: 0.3, 6: 0.68 }, 'L2/3 IT_6': { 1: 0.06, 2: 0.59, 3: 0.34, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Sst_19': { 1: 0.0, 2: 0.0, 3: 0.13, 4: 0.62, 5: 0.2, 6: 0.04 }, 'VLMC_1': { 1: 0.0, 2: 1.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'L6 CT_2': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.01, 5: 0.3, 6: 0.69 }, 'Sst_1': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.05, 5: 0.5, 6: 0.45 }, 'L5 IT_5': { 1: 0.0, 2: 0.0, 3: 0.06, 4: 0.41, 5: 0.49, 6: 0.04 }, 'OPC_3': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Lamp5_Lhx6_1': { 1: 0.03, 2: 0.08, 3: 0.16, 4: 0.06, 5: 0.2, 6: 0.46 }, 'L6b_1': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 1.0 }, 'Pvalb_14': { 1: 0.09, 2: 0.52, 3: 0.37, 4: 0.02, 5: 0.0, 6: 0.0 }, 'Sst Chodl_1': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.3, 6: 0.7 }, 'Vip_22': { 1: 0.2, 2: 0.5, 3: 0.3, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Chandelier_2': { 1: 0.0, 2: 0.31, 3: 0.38, 4: 0.0, 5: 0.23, 6: 0.08 }, 'Lamp5_4': { 1: 0.86, 2: 0.14, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Sncg_8': { 1: 0.65, 2: 0.29, 3: 0.06, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Sncg_3': { 1: 0.62, 2: 0.23, 3: 0.08, 4: 0.0, 5: 0.08, 6: 0.0 }, 'Sst_15': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.08, 5: 0.67, 6: 0.25 }, 'L4 IT_2': { 1: 0.0, 2: 0.0, 3: 0.2, 4: 0.57, 5: 0.22, 6: 0.01 }, 'Sst_13': { 1: 0.0, 2: 0.04, 3: 0.02, 4: 0.4, 5: 0.42, 6: 0.12 }, 'L2/3 IT_2': { 1: 0.0, 2: 0.0, 3: 0.8, 4: 0.2, 5: 0.0, 6: 0.0 }, 'Oligo_4': { 1: 0.03, 2: 0.01, 3: 0.16, 4: 0.27, 5: 0.23, 6: 0.31 }, 'L6 CT_4': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.17, 6: 0.83 }, 'Sst_2': { 1: 0.0, 2: 0.13, 3: 0.74, 4: 0.09, 5: 0.04, 6: 0.0 }, 'Sst_20': { 1: 0.11, 2: 0.47, 3: 0.42, 4: 0.0, 5: 0.0, 6: 0.0 }, 'L2/3 IT_13': { 1: 0.01, 2: 0.06, 3: 0.71, 4: 0.19, 5: 0.02, 6: 0.01 }, 'Pax6_3': { 1: 0.0, 2: 0.33, 3: 0.44, 4: 0.11, 5: 0.0, 6: 0.11 }, 'L2/3 IT_8': { 1: 0.02, 2: 0.48, 3: 0.48, 4: 0.0, 5: 0.01, 6: 0.0 }, 'Micro-PVM_1': { 1: 0.0, 2: 0.0, 3: 0.5, 4: 0.0, 5: 0.5, 6: 0.0 }, 'L6b_4': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.21, 6: 0.79 }, 'Vip_9': { 1: 0.23, 2: 0.39, 3: 0.39, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Vip_21': { 1: 0.82, 2: 0.18, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'L5 IT_2': { 1: 0.0, 2: 0.01, 3: 0.04, 4: 0.39, 5: 0.47, 6: 0.09 }, 'L5/6 NP_5': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 1.0, 6: 0.0 }, 'Vip_7': { 1: 0.0, 2: 0.2, 3: 0.73, 4: 0.0, 5: 0.07, 6: 0.0 }, 'Vip_23': { 1: 0.03, 2: 0.15, 3: 0.21, 4: 0.32, 5: 0.28, 6: 0.01 }, 'Pvalb_7': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.14, 6: 0.86 }, 'Sst_3': { 1: 0.0, 2: 0.03, 3: 0.59, 4: 0.3, 5: 0.07, 6: 0.01 }, 'L6 CT_3': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.31, 6: 0.69 }, 'L6b_5': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.47, 6: 0.53 }, 'L6 CT_1': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.02, 6: 0.98 }, 'Pax6_4': { 1: 0.39, 2: 0.28, 3: 0.06, 4: 0.0, 5: 0.17, 6: 0.11 }, 'Sst_17': { 1: 0.0, 2: 0.06, 3: 0.06, 4: 0.56, 5: 0.31, 6: 0.0 }, 'Pvalb_13': { 1: 0.09, 2: 0.0, 3: 0.0, 4: 0.05, 5: 0.45, 6: 0.41 }, 'Pvalb_8': { 1: 0.17, 2: 0.33, 3: 0.5, 4: 0.0, 5: 0.0, 6: 0.0 }, 'L5 IT_7': { 1: 0.0, 2: 0.01, 3: 0.02, 4: 0.2, 5: 0.66, 6: 0.11 }, 'Sst_6': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.09, 6: 0.91 }, 'Vip_6': { 1: 0.07, 2: 0.67, 3: 0.26, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Sst_4': { 1: 0.0, 2: 0.03, 3: 0.0, 4: 0.19, 5: 0.38, 6: 0.41 }, 'VLMC_3': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Sst_18': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 1.0, 6: 0.0 }, 'L5/6 NP_1': { 1: 0.01, 2: 0.01, 3: 0.01, 4: 0.11, 5: 0.56, 6: 0.3 }, 'Sst_11': { 1: 0.0, 2: 0.88, 3: 0.12, 4: 0.0, 5: 0.0, 6: 0.0 }, 'Pvalb_9': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.04, 5: 0.52, 6: 0.44 }, 'Vip_1': { 1: 0.06, 2: 0.44, 3: 0.43, 4: 0.05, 5: 0.01, 6: 0.01 }, 'Vip_14': { 1: 0.07, 2: 0.07, 3: 0.57, 4: 0.29, 5: 0.0, 6: 0.0 }, 'L6 IT Car3_3': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.02, 5: 0.55, 6: 0.43 }, 'Sst_7': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.4, 6: 0.6 }, 'Lamp5_Lhx6_2': { 1: 0.0, 2: 0.0, 3: 0.0, 4: 0.0, 5: 0.0, 6: 0.0 } };

const subClassColors = { 'Oligo': '#53776C', 'OPC': '#374A45', 'Astro': '#665C47', 'Micro-PVM': '#94AF97', 'Endo': '#8D6C62', 'VLMC': '#697255', 'L6 CT': '#2D8CB8', 'L6b': '#7044AA', 'L5/6 NP': '#3E9E64', 'L5 ET': '#0D5B78', 'Lamp5': '#DA808C', 'Vip': '#A45FBF', 'Pax6': '#71238C', 'Sncg': '#DF70FF', 'Lamp5_Lhx6': '#935F50', 'Sst': '#FF9900', 'Pvalb': '#D93137', 'Chandelier': '#F641A8', 'Sst Chodl': '#B1B10C', 'L5 IT': '#50B2AD', 'L4 IT': '#00E5E5', 'L6 IT': '#A19922', 'L6 IT Car3': '#5100FF', 'L2/3 IT': '#B1EC30' };
const classColors = { 'exc': '#A1FC4E', 'glia': '#75FBFD', 'inh': '#7514F5' };
const mapDataBarChimp = {};
const mapDataBarHuman = {};
const mapDataBarGorilla = {};
const mapDataBarMarmoset = {};
const mapDataBarRhesus = {};
const crossSpecies_ClassMap = { 'Oligo_1': 'glia', 'OPC_2': 'glia', 'Astro_1': 'glia', 'Micro-PVM_1': 'glia', 'Endo_1': 'glia', 'VLMC_1': 'glia', 'OPC_1': 'glia', 'L6 CT_1': 'exc', 'L6b_2': 'exc', 'L5/6 NP_1': 'exc', 'L5/6 NP_2': 'exc', 'L6 CT_2': 'exc', 'L6b_3': 'exc', 'L5 ET_2': 'exc', 'L5 ET_1': 'exc', 'L6b_1': 'exc', 'Lamp5_1': 'inh', 'Vip_5': 'inh', 'Vip_4': 'inh', 'Pax6_1': 'inh', 'Lamp5_2': 'inh', 'Sncg_3': 'inh', 'Vip_8': 'inh', 'Sncg_2': 'inh', 'Vip_1': 'inh', 'Vip_3': 'inh', 'Lamp5_Lhx6_1': 'inh', 'Vip_7': 'inh', 'Vip_2': 'inh', 'Vip_6': 'inh', 'Sncg_1': 'inh', 'Pax6_2': 'inh', 'Sst_3': 'inh', 'Pvalb_4': 'inh', 'Sst_8': 'inh', 'Pvalb_3': 'inh', 'Sst_1': 'inh', 'Sst_2': 'inh', 'Sst_7': 'inh', 'Sst_6': 'inh', 'Sst_5': 'inh', 'Sst_4': 'inh', 'Chandelier_1': 'inh', 'Sst Chodl_1': 'inh', 'Pvalb_2': 'inh', 'Sst_9': 'inh', 'Pvalb_1': 'inh', 'L5 IT_1': 'exc', 'L4 IT_1': 'exc', 'L5 IT_2': 'exc', 'L6 IT_1': 'exc', 'L6 IT Car3_2': 'exc', 'L4 IT_2': 'exc', 'L2/3 IT_1': 'exc', 'L2/3 IT_3': 'exc', 'L2/3 IT_2': 'exc', 'L6 IT Car3_1': 'exc' };
const crossSpecies_SubClassMap = { 'Oligo_1': 'Oligo', 'OPC_2': 'OPC', 'Astro_1': 'Astro', 'Micro-PVM_1': 'Micro-PVM', 'Endo_1': 'Endo', 'VLMC_1': 'VLMC', 'OPC_1': 'OPC', 'L6 CT_1': 'L6 CT', 'L6b_2': 'L6b', 'L5/6 NP_1': 'L5/6 NP', 'L5/6 NP_2': 'L5/6 NP', 'L6 CT_2': 'L6 CT', 'L6b_3': 'L6b', 'L5 ET_2': 'L5 ET', 'L5 ET_1': 'L5 ET', 'L6b_1': 'L6b', 'Lamp5_1': 'Lamp5', 'Vip_5': 'Vip', 'Vip_4': 'Vip', 'Pax6_1': 'Pax6', 'Lamp5_2': 'Lamp5', 'Sncg_3': 'Pax6', 'Vip_8': 'Sncg', 'Sncg_2': 'Sncg', 'Vip_1': 'Vip', 'Vip_3': 'Vip', 'Lamp5_Lhx6_1': 'Lamp5_Lhx6', 'Vip_7': 'Vip', 'Vip_2': 'Vip', 'Vip_6': 'Vip', 'Sncg_1': 'Sncg', 'Pax6_2': 'Pax6', 'Sst_3': 'Sst', 'Pvalb_4': 'Pvalb', 'Sst_8': 'Sst', 'Pvalb_3': 'Pvalb', 'Sst_1': 'Sst', 'Sst_2': 'Sst', 'Sst_7': 'Sst', 'Sst_6': 'Sst Chodl', 'Sst_5': 'Sst', 'Sst_4': 'Sst', 'Chandelier_1': 'Chandelier', 'Sst Chodl_1': 'Sst Chodl', 'Pvalb_2': 'Pvalb', 'Sst_9': 'Sst', 'Pvalb_1': 'Pvalb', 'L5 IT_1': 'L5 IT', 'L4 IT_1': 'L4 IT', 'L5 IT_2': 'L5 IT', 'L6 IT_1': 'L6 IT', 'L6 IT Car3_2': 'L6 IT Car3', 'L4 IT_2': 'L4 IT', 'L2/3 IT_1': 'L2/3 IT', 'L2/3 IT_3': 'L2/3 IT', 'L2/3 IT_2': 'L4 IT', 'L6 IT Car3_1': 'L6 IT Car3' };
//Qt Connections
try {
    new QWebChannel(qt.webChannelTransport, function (channel) {
        QtBridge = channel.objects.QtBridge;
        QtBridge.qt_setData.connect(function () { setData(arguments[0]); });
        QtBridge.qt_setClusters.connect(function () { setClusters(arguments[0]); });
        QtBridge.qt_setColor.connect(function () { setColor(arguments[0]); });
        QtBridge.qt_setBackgroundColor.connect(function () { setBackgroundColor(arguments[0]); });
        QtBridge.qt_histChart.connect(function () { histChart(arguments[0]); });
        QtBridge.qt_setRangeValue.connect(function () { setRangeValue(arguments[0]); });
        QtBridge.qt_inspeciesClusterCounts.connect(function () { setInspeciesClusterCounts(arguments[0]); });
        notifyBridgeAvailable();
    });
} catch (error) { isQtAvailable = false; }

//Heatmap Visualization
const simianVis = () => {
    d3.select("g").remove();
    d3.select("svg").remove();
    svg = d3.select("#my_dataviz")
    svg.selectAll("*").remove();
    var margin;
    if (barflag) {
        margin = { top: 50, right: 370, bottom: 80, left: 75 },
            width = window.innerWidth * 0.99 - margin.left - margin.right,
            height = window.innerHeight * 0.99 - margin.top - margin.bottom;

    }
    else {
            margin = { top: 5, right: 325, bottom: 80, left: 75 },
            width = window.innerWidth * 0.99 - margin.left - margin.right,
            height = window.innerHeight * 0.97 - margin.top - margin.bottom;
    }


    // append the svg object to the body of the page
    svg = d3
        .select("#my_dataviz")
        .append("svg")
        .style("background", backgroundColor)
        .attr("width", width + margin.left + margin.right)
        .attr("height", height + margin.top + margin.bottom)
        .append("g")
        .attr("transform", "translate(" + margin.left + "," + (margin.top + 15) + ")");

    var cluster_1_Groups = d3
        .map(_data, function (d) {
            return d.cluster_1;
        })
        .keys();
    var cluster_2_Groups = d3
        .map(_data, function (d) {
            return d.cluster_2;
        })
        .keys();
    var cross_species_cluster1_species_1_Groups = d3
        .map(_data, function (d) {
            return d.cross_species_cluster1_species_1;
        })
        .keys();
    var cross_species_cluster2_species_2_Groups = d3
        .map(_data, function (d) {
            return d.cross_species_cluster2_species_2;
        })
        .keys();

    function clickXAxisLabels(d) {
        svg.select("#axisSelectionpolygon").remove();
        svg.select("#axisSelectionText").remove();
        
        var correspondingCrossspeciescluster;
        var XFirstElement = "";
        var XLastElement = "";
        var YFirstElement = "";
        var YLastElement = "";
        var indexOfElement = uniqueClusters1List.indexOf(d);
        if (species1ValueIdentify == "human") {
            correspondingCrossspeciescluster = [mapDataforBorderHuman[uniqueClusters1List[indexOfElement]]];
            for (var i = 0; i < crossSpeciesFilterspecies1Cluster.length; i++) {
                if (mapDataforBorderHuman[crossSpeciesFilterspecies1Cluster[i]] == correspondingCrossspeciescluster) {
                    XFirstElement = x(crossSpeciesFilterspecies1Cluster[i]);
                    if (i + 1 < crossSpeciesFilterspecies1Cluster.length) { XLastElement = x(crossSpeciesFilterspecies1Cluster[i + 1]); }
                    else { XLastElement = width; }
                    break;
                }
            }
        }
        else if (species1ValueIdentify == "chimp") {
            correspondingCrossspeciescluster = [mapDataforBorderChimp[uniqueClusters1List[indexOfElement]]];
            for (var i = 0; i < crossSpeciesFilterspecies1Cluster.length; i++) {
                if (mapDataforBorderChimp[crossSpeciesFilterspecies1Cluster[i]] == correspondingCrossspeciescluster) {
                    XFirstElement = x(crossSpeciesFilterspecies1Cluster[i]);
                    if (i + 1 < crossSpeciesFilterspecies1Cluster.length) { XLastElement = x(crossSpeciesFilterspecies1Cluster[i + 1]); }
                    else { XLastElement = width; }
                    break;
                }
            }
        }
        else if (species1ValueIdentify == "gorilla") {
            correspondingCrossspeciescluster = [mapDataforBorderGorilla[uniqueClusters1List[indexOfElement]]];
            for (var i = 0; i < crossSpeciesFilterspecies1Cluster.length; i++) {
                if (mapDataforBorderGorilla[crossSpeciesFilterspecies1Cluster[i]] == correspondingCrossspeciescluster) {
                    XFirstElement = x(crossSpeciesFilterspecies1Cluster[i]);
                    if (i + 1 < crossSpeciesFilterspecies1Cluster.length) { XLastElement = x(crossSpeciesFilterspecies1Cluster[i + 1]); }
                    else { XLastElement = width; }
                    break;
                }
            }
        }
        else if (species1ValueIdentify == "rhesus") {
            correspondingCrossspeciescluster = [mapDataforBorderRhesus[uniqueClusters1List[indexOfElement]]];
            for (var i = 0; i < crossSpeciesFilterspecies1Cluster.length; i++) {
                if (mapDataforBorderRhesus[crossSpeciesFilterspecies1Cluster[i]] == correspondingCrossspeciescluster) {
                    XFirstElement = x(crossSpeciesFilterspecies1Cluster[i]);
                    if (i + 1 < crossSpeciesFilterspecies1Cluster.length) { XLastElement = x(crossSpeciesFilterspecies1Cluster[i + 1]); }
                    else { XLastElement = width; }
                    break;
                }
            }
        }
        ////y
        if (species2ValueIdentify == "chimp") {
            for (var i = crossSpeciesFilterspecies2Cluster.length - 1; i >= 0; i--) {
                if (mapDataforBorderChimp[crossSpeciesFilterspecies2Cluster[i]] == correspondingCrossspeciescluster) {
                    YFirstElement = y(crossSpeciesFilterspecies2Cluster[i]);
                    if (i > 0) { YLastElement = y(crossSpeciesFilterspecies2Cluster[i - 1]); }
                    else { YLastElement = height; }
                    break;
                }
            }
        }
        else if (species2ValueIdentify == "gorilla") {
            for (var i = crossSpeciesFilterspecies2Cluster.length - 1; i >= 0; i--) {
                if (mapDataforBorderGorilla[crossSpeciesFilterspecies2Cluster[i]] == correspondingCrossspeciescluster) {
                    YFirstElement = y(crossSpeciesFilterspecies2Cluster[i]);
                    if (i > 0) { YLastElement = y(crossSpeciesFilterspecies2Cluster[i - 1]); }
                    else { YLastElement = height; }
                    break;
                }
            }
        }
        else if (species2ValueIdentify == "marmoset") {
            for (var i = crossSpeciesFilterspecies2Cluster.length - 1; i >= 0; i--) {
                if (mapDataforBorderMarmoset[crossSpeciesFilterspecies2Cluster[i]] == correspondingCrossspeciescluster) {
                    YFirstElement = y(crossSpeciesFilterspecies2Cluster[i]);
                    if (i > 0) { YLastElement = y(crossSpeciesFilterspecies2Cluster[i - 1]); }
                    else { YLastElement = height; }
                    break;
                }
            }
        }
        else if (species2ValueIdentify == "rhesus") {
            for (var i = crossSpeciesFilterspecies2Cluster.length - 1; i >= 0; i--) {
                if (mapDataforBorderRhesus[crossSpeciesFilterspecies2Cluster[i]] == correspondingCrossspeciescluster) {
                    YFirstElement = y(crossSpeciesFilterspecies2Cluster[i]);
                    if (i > 0) { YLastElement = y(crossSpeciesFilterspecies2Cluster[i - 1]); }
                    else { YLastElement = height; }
                    break;
                }
            }
        }

        if (YLastElement == "") {
            YLastElement = "0.00";
        }
        if (YFirstElement == "") {
            YFirstElement = y(crossSpeciesFilterspecies2Cluster[crossSpeciesFilterspecies2Cluster.length - 1]);
        }

        var poly = XFirstElement + ',' + YFirstElement + ' ' + XLastElement + ',' + YFirstElement + ' ' + XLastElement + ',' + YLastElement + ' ' + XFirstElement + ',' + YLastElement + ' ' + XFirstElement + ',' + YFirstElement;
        svg.append('polygon')
            .attr("id", "axisSelectionpolygon")
            .attr('points', poly)
            .attr('stroke', cross_speciesClustercolors[correspondingCrossspeciescluster])
            .attr("stroke-width", 10)
            .attr('fill', 'none');

        svg.append("foreignObject")
            .attr("id", "axisSelectionText")
            .style("background-color", "transparent")
            //.style("border", "solid" + cross_speciesClustercolors[correspondingCrossspeciescluster])
            //.style("border-width", "4px")
            //.style("border-radius", "5px")
            .style("padding", "5px")
            .style("position", "absolute")
            .attr("x", width)
            .attr("y", 0)
            .attr("width", 250)
            .attr("height", 200)
            .html(function (d) {
                var average = parseFloat(cross_speciesClusterInfo[correspondingCrossspeciescluster]['averageDistance']) / parseFloat(cross_speciesClusterInfo[correspondingCrossspeciescluster]['numberOfCells']);
                //var value = "<div>Number of cluster blocks:<b>" + cross_speciesClusterInfo[correspondingCrossspeciescluster]['numberOfCells']
                //    + " </b><br/> Minimum distance:<b>" + cross_speciesClusterInfo[correspondingCrossspeciescluster]['minDistance']
                //    + " </b> <br/> Maximum distance: <b>" + cross_speciesClusterInfo[correspondingCrossspeciescluster]['maxDistance']
                //    + "</b><br/>Average distance: <b>" + average
                //    + "</b><br/>Cross-species cluster: <b>" + correspondingCrossspeciescluster
                //    + "</b></div>";
                let minVal = parseFloat(cross_speciesClusterInfo[correspondingCrossspeciescluster]['minDistance']).toFixed(2);
                let maxVal = parseFloat(cross_speciesClusterInfo[correspondingCrossspeciescluster]['maxDistance']).toFixed(2);
                let avgVal = parseFloat(average).toFixed(2);
                var value = "<table border=\"1\" >"
                    + "<tr><td rowspan=\"1\" bgcolor=\"white\"><div><i>Cluster block count</i></div></td><td bgcolor=\"white\"><div>" + cross_speciesClusterInfo[correspondingCrossspeciescluster]['numberOfCells'] + "</div></td></tr>"
                    + "<tr><td rowspan=\"1\" bgcolor=\"white\"><div><i>Minimum distance</i></div></td><td bgcolor=\"white\"><div>" + minVal + "</div></td></tr>"
                    + "<tr><td rowspan=\"1\" bgcolor=\"white\"><div><i>Maximum distance</i></div></td><td bgcolor=\"white\"><div>" + maxVal + "</div></td></tr>"
                    + "<tr><td rowspan=\"1\" bgcolor=\"white\"><div><i>Average distance</i></div></td><td bgcolor=\"white\"><div>" + avgVal + "</div></td></tr>"
                    + "<tr><td rowspan=\"1\" bgcolor=\"white\"><div><i>Cross-species cluster</i></div></td><td colspan=\"2\" bgcolor=\"white\"><div style=\"color:" + cross_speciesClustercolors[correspondingCrossspeciescluster] + "; -webkit-text-stroke: 0.2 black;\">" + correspondingCrossspeciescluster + "</div></td></tr>"
                    + "<tr><td rowspan=\"1\" bgcolor=\"white\"><div><i>Class</i></div></td><td colspan=\"2\" bgcolor=\"white\"><div style=\"color:" + classColors[crossSpecies_ClassMap[correspondingCrossspeciescluster]] + "; -webkit-text-stroke: 0.2 black;\">" + crossSpecies_ClassMap[correspondingCrossspeciescluster] + "</div></td></tr>"
                    + "<tr><td rowspan=\"1\" bgcolor=\"white\"><div><i>Subclass</i></div></td><td colspan=\"2\" bgcolor=\"white\"><div style=\"color:" + subClassColors[crossSpecies_SubClassMap[correspondingCrossspeciescluster]] + "; -webkit-text-stroke: 0.2 black;\">" + crossSpecies_SubClassMap[correspondingCrossspeciescluster] + "</div></td></tr>"
                    + "</table>";


                return value;
            })
        

        if (isQtAvailable) {
            QtBridge.js_passClusterToQt(correspondingCrossspeciescluster.toString());
        }

    }
    function clickYAxisLabels(d) {
        svg.select("#axisSelectionpolygon").remove();
        svg.select("#axisSelectionText").remove();
        var correspondingCrossspeciescluster;
        var XFirstElement = "";
        var XLastElement = "";
        var YFirstElement = "";
        var YLastElement = "";
        var indexOfElement = uniqueClusters2List.indexOf(d);

        ////y
        if (species2ValueIdentify == "chimp") {
            correspondingCrossspeciescluster = [mapDataforBorderChimp[uniqueClusters2List[indexOfElement]]];
            for (var i = crossSpeciesFilterspecies2Cluster.length - 1; i >= 0; i--) {
                if (mapDataforBorderChimp[crossSpeciesFilterspecies2Cluster[i]] == correspondingCrossspeciescluster) {
                    YFirstElement = y(crossSpeciesFilterspecies2Cluster[i]);
                    if (i > 0) { YLastElement = y(crossSpeciesFilterspecies2Cluster[i - 1]); }
                    else { YLastElement = height; }
                    break;
                }
            }
        }
        else if (species2ValueIdentify == "gorilla") {
            correspondingCrossspeciescluster = [mapDataforBorderGorilla[uniqueClusters2List[indexOfElement]]];
            for (var i = crossSpeciesFilterspecies2Cluster.length - 1; i >= 0; i--) {
                if (mapDataforBorderGorilla[crossSpeciesFilterspecies2Cluster[i]] == correspondingCrossspeciescluster) {
                    YFirstElement = y(crossSpeciesFilterspecies2Cluster[i]);
                    if (i > 0) { YLastElement = y(crossSpeciesFilterspecies2Cluster[i - 1]); }
                    else { YLastElement = height; }
                    break;
                }
            }
        }
        else if (species2ValueIdentify == "marmoset") {
            correspondingCrossspeciescluster = [mapDataforBorderMarmoset[uniqueClusters2List[indexOfElement]]];
            for (var i = crossSpeciesFilterspecies2Cluster.length - 1; i >= 0; i--) {
                if (mapDataforBorderMarmoset[crossSpeciesFilterspecies2Cluster[i]] == correspondingCrossspeciescluster) {
                    YFirstElement = y(crossSpeciesFilterspecies2Cluster[i]);
                    if (i > 0) { YLastElement = y(crossSpeciesFilterspecies2Cluster[i - 1]); }
                    else { YLastElement = height; }
                    break;
                }
            }
        }
        else if (species2ValueIdentify == "rhesus") {
            correspondingCrossspeciescluster = [mapDataforBorderRhesus[uniqueClusters2List[indexOfElement]]];
            for (var i = crossSpeciesFilterspecies2Cluster.length - 1; i >= 0; i--) {
                if (mapDataforBorderRhesus[crossSpeciesFilterspecies2Cluster[i]] == correspondingCrossspeciescluster) {
                    YFirstElement = y(crossSpeciesFilterspecies2Cluster[i]);
                    if (i > 0) { YLastElement = y(crossSpeciesFilterspecies2Cluster[i - 1]); }
                    else { YLastElement = height; }
                    break;
                }
            }
        }
        ////x

        if (species1ValueIdentify == "human") {
            for (var i = 0; i < crossSpeciesFilterspecies1Cluster.length; i++) {
                if (mapDataforBorderHuman[crossSpeciesFilterspecies1Cluster[i]] == correspondingCrossspeciescluster) {
                    XFirstElement = x(crossSpeciesFilterspecies1Cluster[i]);
                    if (i + 1 < crossSpeciesFilterspecies1Cluster.length) { XLastElement = x(crossSpeciesFilterspecies1Cluster[i + 1]); }
                    else { XLastElement = width; }
                    break;
                }
            }
        }
        else if (species1ValueIdentify == "chimp") {
            for (var i = 0; i < crossSpeciesFilterspecies1Cluster.length; i++) {
                if (mapDataforBorderChimp[crossSpeciesFilterspecies1Cluster[i]] == correspondingCrossspeciescluster) {
                    XFirstElement = x(crossSpeciesFilterspecies1Cluster[i]);
                    if (i + 1 < crossSpeciesFilterspecies1Cluster.length) { XLastElement = x(crossSpeciesFilterspecies1Cluster[i + 1]); }
                    else { XLastElement = width; }
                    break;
                }
            }
        }
        else if (species1ValueIdentify == "gorilla") {
            for (var i = 0; i < crossSpeciesFilterspecies1Cluster.length; i++) {
                if (mapDataforBorderGorilla[crossSpeciesFilterspecies1Cluster[i]] == correspondingCrossspeciescluster) {
                    XFirstElement = x(crossSpeciesFilterspecies1Cluster[i]);
                    if (i + 1 < crossSpeciesFilterspecies1Cluster.length) { XLastElement = x(crossSpeciesFilterspecies1Cluster[i + 1]); }
                    else { XLastElement = width; }
                    break;
                }
            }
        }
        else if (species1ValueIdentify == "rhesus") {
            for (var i = 0; i < crossSpeciesFilterspecies1Cluster.length; i++) {
                if (mapDataforBorderRhesus[crossSpeciesFilterspecies1Cluster[i]] == correspondingCrossspeciescluster) {
                    XFirstElement = x(crossSpeciesFilterspecies1Cluster[i]);
                    if (i + 1 < crossSpeciesFilterspecies1Cluster.length) { XLastElement = x(crossSpeciesFilterspecies1Cluster[i + 1]); }
                    else { XLastElement = width; }
                    break;
                }
            }
        }

        if (YLastElement == "") {
            YLastElement = "0.00";
        }
        if (YFirstElement == "") {
            YFirstElement = y(crossSpeciesFilterspecies2Cluster[crossSpeciesFilterspecies2Cluster.length - 1]);
        }

        var poly = XFirstElement + ',' + YFirstElement + ' ' + XLastElement + ',' + YFirstElement + ' ' + XLastElement + ',' + YLastElement + ' ' + XFirstElement + ',' + YLastElement + ' ' + XFirstElement + ',' + YFirstElement;
        svg.append('polygon')
            .attr("id", "axisSelectionpolygon")
            .attr('points', poly)
            .attr('stroke', cross_speciesClustercolors[correspondingCrossspeciescluster])
            .attr("stroke-width", 10)
            .attr('fill', 'none');

        svg.append("foreignObject")
            .attr("id", "axisSelectionText")
            .style("background-color", "transparent")
            //.style("border", "solid" + cross_speciesClustercolors[correspondingCrossspeciescluster])
            //.style("border-width", "4px")
            //.style("border-radius", "5px")
            .style("padding", "5px")
            .style("position", "absolute")
            .attr("x", width)
            .attr("y", 0)
            .attr("width", 250)
            .attr("height", 200)
            .html(function (d) {
                var average = parseFloat(cross_speciesClusterInfo[correspondingCrossspeciescluster]['averageDistance']) / parseFloat(cross_speciesClusterInfo[correspondingCrossspeciescluster]['numberOfCells']);
                //var value = "<div>Number of cluster blocks:<b>" + cross_speciesClusterInfo[correspondingCrossspeciescluster]['numberOfCells']
                //    + " </b><br/> Minimum distance:<b>" + cross_speciesClusterInfo[correspondingCrossspeciescluster]['minDistance']
                //    + " </b> <br/> Maximum distance: <b>" + cross_speciesClusterInfo[correspondingCrossspeciescluster]['maxDistance']
                //    + "</b><br/>Average distance: <b>" + average
                //    + "</b><br/>Cross-species cluster: <b>" + correspondingCrossspeciescluster
                //    + "</b></div>";

                let minVal = parseFloat(cross_speciesClusterInfo[correspondingCrossspeciescluster]['minDistance']).toFixed(2);
                let maxVal = parseFloat(cross_speciesClusterInfo[correspondingCrossspeciescluster]['maxDistance']).toFixed(2);
                let avgVal = parseFloat(average).toFixed(2);
                var value = "<table border=\"1\" >"
                    + "<tr><td rowspan=\"1\" bgcolor=\"white\"><div><i>Cluster block count</i></div></td><td bgcolor=\"white\"><div>" + cross_speciesClusterInfo[correspondingCrossspeciescluster]['numberOfCells'] + "</div></td></tr>"
                    + "<tr><td rowspan=\"1\" bgcolor=\"white\"><div><i>Minimum distance</i></div></td><td bgcolor=\"white\"><div>" + minVal + "</div></td></tr>"
                    + "<tr><td rowspan=\"1\" bgcolor=\"white\"><div><i>Maximum distance</i></div></td><td bgcolor=\"white\"><div>" + maxVal + "</div></td></tr>"
                    + "<tr><td rowspan=\"1\" bgcolor=\"white\"><div><i>Average distance</i></div></td><td bgcolor=\"white\"><div>" + avgVal + "</div></td></tr>"
                    + "<tr><td rowspan=\"1\" bgcolor=\"white\"><div><i>Cross-species cluster</i></div></td><td colspan=\"2\" bgcolor=\"white\"><div style=\"color:" + cross_speciesClustercolors[correspondingCrossspeciescluster] + "; -webkit-text-stroke: 0.2 black;\">" + correspondingCrossspeciescluster + "</div></td></tr>"
                    + "<tr><td rowspan=\"1\" bgcolor=\"white\"><div><i>Class</i></div></td><td colspan=\"2\" bgcolor=\"white\"><div style=\"color:" + classColors[crossSpecies_ClassMap[correspondingCrossspeciescluster]] + "; -webkit-text-stroke: 0.2 black;\">" + crossSpecies_ClassMap[correspondingCrossspeciescluster] + "</div></td></tr>"
                    + "<tr><td rowspan=\"1\" bgcolor=\"white\"><div><i>Subclass</i></div></td><td colspan=\"2\" bgcolor=\"white\"><div style=\"color:" + subClassColors[crossSpecies_SubClassMap[correspondingCrossspeciescluster]] + "; -webkit-text-stroke: 0.2 black;\">" + crossSpecies_SubClassMap[correspondingCrossspeciescluster] + "</div></td></tr>"
                    + "</table>";


                return value;
            })
        if (isQtAvailable) {
            QtBridge.js_passClusterToQt(correspondingCrossspeciescluster.toString());
        }
    }

    // Build X scales and axis:
    var x = d3.scaleBand().range([0, width]).domain(cluster_1_Groups).padding(0.05);
    svg
        .append("g")
        .style("font-size", 9)
        .attr("transform", "translate(0," + height + ")")
        .call(d3.axisBottom(x).tickSize(0))
        .selectAll("text")
        .on('click', clickXAxisLabels)
        .style("cursor", "pointer")
        .attr("fill", function (d) {
            return in_speciesClustercolors[d];
        })
        .style("text-anchor", "end")
        .attr("dx", "-1.0em")
        .attr("dy", "0.0em")
        .attr("transform", "rotate(-90)")
        .select(".domain")
        .remove();

    // Build Y scales and axis:
    var y = d3.scaleBand().range([height, 0]).domain(cluster_2_Groups).padding(0.05);
    svg
        .append("g")
        .style("font-size", 8)
        .call(d3.axisLeft(y).tickSize(0))
        .selectAll("text")
        .on('click', clickYAxisLabels)
        .style("cursor", "pointer")
        .attr("fill", function (d) {
            return in_speciesClustercolors[d];
        })
        .style("text-anchor", "end")
        .attr("dx", "-0.5em")
        .attr("dy", "0.1em")
        .attr("transform", "rotate(0)")
        .select(".domain")
        .remove();
    // Build color scaled3.scaleSequential(d3Chromatic.interpolatePiYG);
    if (qtColor == "qualitative") {
        if (colorMirror) {
            var myColor = d3.scaleOrdinal(d3.schemeSet3).domain([maxdistanceColor, mindistanceColor]);
        }
        else {
            var myColor = d3.scaleOrdinal(d3.schemeSet3).domain([maxdistanceColor, mindistanceColor]);
        }
    }
    else if (qtColor == "RdYlBu") {

        if (colorMirror) {
            var myColor = d3.scaleSequential(d3.interpolateRdYlBu).domain([mindistanceColor, maxdistanceColor]);
        }
        else {
            var myColor = d3.scaleSequential(d3.interpolateRdYlBu).domain([maxdistanceColor, mindistanceColor]);
        }
    }
    else if (qtColor == "YlGn") {

        if (colorMirror) {
            var myColor = d3.scaleSequential(d3.interpolateYlGn).domain([mindistanceColor, maxdistanceColor]);
        }
        else {
            var myColor = d3.scaleSequential(d3.interpolateYlGn).domain([maxdistanceColor, mindistanceColor]);
        }
    }
    else if (qtColor == "RdYlGn") {

        if (colorMirror) {
            var myColor = d3.scaleSequential(d3.interpolateRdYlGn).domain([mindistanceColor, maxdistanceColor]);
        }
        else {
            var myColor = d3.scaleSequential(d3.interpolateRdYlGn).domain([maxdistanceColor, mindistanceColor]);
        }
    }
    else if (qtColor == "GnBu") {

        if (colorMirror) {
            var myColor = d3.scaleSequential(d3.interpolateGnBu).domain([mindistanceColor, maxdistanceColor]);
        }
        else {
            var myColor = d3.scaleSequential(d3.interpolateGnBu).domain([maxdistanceColor, mindistanceColor]);
        }
    }
    else if (qtColor == "YlGnBu") {

        if (colorMirror) {
            var myColor = d3.scaleSequential(d3.interpolateYlGnBu).domain([mindistanceColor, maxdistanceColor]);
        }
        else {
            var myColor = d3.scaleSequential(d3.interpolateYlGnBu).domain([maxdistanceColor, mindistanceColor]);
        }
    }
    else if (qtColor == "Spectral") {

        if (colorMirror) {
            var myColor = d3.scaleSequential(d3.interpolateSpectral).domain([mindistanceColor, maxdistanceColor]);
        }
        else {
            var myColor = d3.scaleSequential(d3.interpolateSpectral).domain([maxdistanceColor, mindistanceColor]);
        }
    }
    else if (qtColor == "BrBG") {

        if (colorMirror) {
            var myColor = d3.scaleSequential(d3.interpolateBrBG).domain([mindistanceColor, maxdistanceColor]);
        }
        else {
            var myColor = d3.scaleSequential(d3.interpolateBrBG).domain([maxdistanceColor, mindistanceColor]);
        }
    }
    else if (qtColor == "YlOrBr") {

        if (colorMirror) {
            var myColor = d3.scaleSequential(d3.interpolateYlOrBr).domain([mindistanceColor, maxdistanceColor]);
        }
        else {
            var myColor = d3.scaleSequential(d3.interpolateYlOrBr).domain([maxdistanceColor, mindistanceColor]);
        }
    }
    else if (qtColor == "RdBu") {

        if (colorMirror) {
            var myColor = d3.scaleSequential(d3.interpolateRdBu).domain([mindistanceColor, maxdistanceColor]);
        }
        else {
            var myColor = d3.scaleSequential(d3.interpolateRdBu).domain([maxdistanceColor, mindistanceColor]);
        }
    }
    else if (qtColor == "RdPu") {

        if (colorMirror) {
            var myColor = d3.scaleSequential(d3.interpolateRdPu).domain([mindistanceColor, maxdistanceColor]);
        }
        else {
            var myColor = d3.scaleSequential(d3.interpolateRdPu).domain([maxdistanceColor, mindistanceColor]);
        }
    }
    else if (qtColor == "Plasma") {

        if (colorMirror) {
            var myColor = d3.scaleSequential(d3.interpolatePlasma).domain([mindistanceColor, maxdistanceColor]);
        }
        else {
            var myColor = d3.scaleSequential(d3.interpolatePlasma).domain([maxdistanceColor, mindistanceColor]);
        }
    }
    else if (qtColor == "PuOr") {

        if (colorMirror) {
            var myColor = d3.scaleSequential(d3.interpolatePuOr).domain([mindistanceColor, maxdistanceColor]);
        }
        else {
            var myColor = d3.scaleSequential(d3.interpolatePuOr).domain([maxdistanceColor, mindistanceColor]);
        }
    }
    else if (qtColor == "BuPu") {

        if (colorMirror) {

            var myColor = d3.scaleSequential(d3.interpolateBuPu).domain([mindistanceColor, maxdistanceColor]);
        }
        else {
            var myColor = d3.scaleSequential(d3.interpolateBuPu).domain([maxdistanceColor, mindistanceColor]);
        }
    }
    else if (qtColor == "Reds") {

        if (colorMirror) {
            var myColor = d3.scaleSequential(d3.interpolateReds).domain([mindistanceColor, maxdistanceColor]);
        }
        else {

            var myColor = d3.scaleSequential(d3.interpolateReds).domain([maxdistanceColor, mindistanceColor]);
        }
    }
    else if (qtColor == "Viridis") {

        if (colorMirror) {
            var myColor = d3.scaleSequential(d3.interpolateViridis).domain([mindistanceColor, maxdistanceColor]);
        }
        else {

            var myColor = d3.scaleSequential(d3.interpolateViridis).domain([maxdistanceColor, mindistanceColor]);
        }
    }
    else if (qtColor == "Q_BlGrRd") {

        if (colorMirror) {
            var myColor = d3.scaleSequential(d3.interpolateRdGy).domain([mindistanceColor, maxdistanceColor]);
        }
        else {

            var myColor = d3.scaleSequential(d3.interpolateRdGy).domain([maxdistanceColor, mindistanceColor]);
        }
    }
    else if (qtColor == "Magma") {

        if (colorMirror) {
            var myColor = d3.scaleSequential(d3.interpolateMagma).domain([mindistanceColor, maxdistanceColor]);
        }
        else {

            var myColor = d3.scaleSequential(d3.interpolateMagma).domain([maxdistanceColor, mindistanceColor]);
        }
    }
    else if (qtColor == "PiYG") {

        if (colorMirror) {
            var myColor = d3.scaleSequential(d3.interpolatePiYG).domain([mindistanceColor, maxdistanceColor]);
        }
        else {

            var myColor = d3.scaleSequential(d3.interpolatePiYG).domain([maxdistanceColor, mindistanceColor]);
        }
    }
    else {
        if (colorMirror) {
            var myColor = d3.scaleSequential(d3.interpolateGreys).domain([mindistanceColor, maxdistanceColor]);
        }
        else {
            var myColor = d3.scaleSequential(d3.interpolateGreys).domain([maxdistanceColor, mindistanceColor]);
        }
        //d3 https://github.com/d3/d3-scale-chromatic
    }

    ////////
    //bottom axis

    var valnow1;
    var valuenext1;
    var colorNow1;
    for (var i = 0; i < uniqueClusters1List.length; i++) {
        if (i == uniqueClusters1List.length - 1) {
            valnow1 = x(uniqueClusters1List[i]);
            valuenext1 = width;
        }
        else {
            valnow1 = x(uniqueClusters1List[i]);
            valuenext1 = x(uniqueClusters1List[i + 1]);
        }

        if (species1ValueIdentify == "human") {
            colorNow1 = cross_speciesClustercolors[mapDataforBorderHuman[uniqueClusters1List[i]]];
        }
        else if (species1ValueIdentify == "chimp") {
            colorNow1 = cross_speciesClustercolors[mapDataforBorderChimp[uniqueClusters1List[i]]];
        }
        else if (species1ValueIdentify == "gorilla") {
            colorNow1 = cross_speciesClustercolors[mapDataforBorderGorilla[uniqueClusters1List[i]]];
        }
        else if (species1ValueIdentify == "rhesus") {
            colorNow1 = cross_speciesClustercolors[mapDataforBorderRhesus[uniqueClusters1List[i]]];
        }
        svg.append("line")
            .attr("x1", valnow1)
            .attr("x2", valuenext1)
            .attr("y1", height)
            .attr("y2", height)
            .attr("stroke-width", 10)
            .attr("stroke", colorNow1)
            //.style("paint-order", "stroke")
            .style("stroke-location", "inside");

    }

    //////left axis
    var valnow2;
    var valuenext2;
    var colorNow2;
    for (var i = 0; i < uniqueClusters2List.length; i++) {

        if (i == 0) {
            valnow2 = height;
            valuenext2 = y(uniqueClusters2List[i]);
        }
        else {
            valnow2 = y(uniqueClusters2List[i - 1]);
            valuenext2 = y(uniqueClusters2List[i]);
        }

        if (species2ValueIdentify == "chimp") {
            colorNow2 = cross_speciesClustercolors[mapDataforBorderChimp[uniqueClusters2List[i]]];
        }
        else if (species2ValueIdentify == "gorilla") {
            colorNow2 = cross_speciesClustercolors[mapDataforBorderGorilla[uniqueClusters2List[i]]];
        }
        else if (species2ValueIdentify == "marmoset") {
            colorNow2 = cross_speciesClustercolors[mapDataforBorderMarmoset[uniqueClusters2List[i]]];
        }
        else if (species2ValueIdentify == "rhesus") {
            colorNow2 = cross_speciesClustercolors[mapDataforBorderRhesus[uniqueClusters2List[i]]];
        }
        svg.append("line")
            .attr("x1", 0)
            .attr("x2", 0)
            .attr("y1", valuenext2)
            .attr("y2", valnow2)
            .attr("stroke-width", 10)
            .attr("stroke", colorNow2)
            //.style("paint-order", "stroke")
            .style("stroke-location", "inside");

    }

    ///////top axis
    var valnow1;
    var valuenext1;
    var colorNow1;
    for (var i = 0; i < uniqueClusters1List.length; i++) {
        if (i == uniqueClusters1List.length - 1) {
            valnow1 = x(uniqueClusters1List[i]);
            valuenext1 = width;
        }
        else {
            valnow1 = x(uniqueClusters1List[i]);
            valuenext1 = x(uniqueClusters1List[i + 1]);
        }

        if (species1ValueIdentify == "human") {
            colorNow1 = cross_speciesClustercolors[mapDataforBorderHuman[uniqueClusters1List[i]]];
        }
        else if (species1ValueIdentify == "chimp") {
            colorNow1 = cross_speciesClustercolors[mapDataforBorderChimp[uniqueClusters1List[i]]];
        }
        else if (species1ValueIdentify == "gorilla") {
            colorNow1 = cross_speciesClustercolors[mapDataforBorderGorilla[uniqueClusters1List[i]]];
        }
        else if (species1ValueIdentify == "rhesus") {
            colorNow1 = cross_speciesClustercolors[mapDataforBorderRhesus[uniqueClusters1List[i]]];
        }
        svg.append("line")
            .attr("x1", valnow1)
            .attr("x2", valuenext1)
            .attr("y1", 0)
            .attr("y2", 0)
            .attr("stroke-width", 2)
            .attr("stroke", colorNow1)
            //.style("paint-order", "stroke")
            .style("stroke-location", "inside");
        if (barflag) {
           svg.append("rect")
                .attr("x", valnow1 + ((valuenext1 - valnow1) / 4))
               .attr("y", -((inspecies1ClusterCounts[uniqueClusters1List[i]]))/100  )
                .attr("width", (valuenext1 - valnow1) / 2)
               .attr("height", ((inspecies1ClusterCounts[uniqueClusters1List[i]]) / 100 ))
               .attr("fill", in_speciesClustercolors[uniqueClusters1List[i]]);
        }
    }
    //////right axis
    var valnow2;
    var valuenext2;
    var colorNow2;
    for (var i = 0; i < uniqueClusters2List.length; i++) {

        if (i == 0) {
            valnow2 = height;
            valuenext2 = y(uniqueClusters2List[i]);
        }
        else {
            valnow2 = y(uniqueClusters2List[i - 1]);
            valuenext2 = y(uniqueClusters2List[i]);
        }

        if (species2ValueIdentify == "chimp") {
            colorNow2 = cross_speciesClustercolors[mapDataforBorderChimp[uniqueClusters2List[i]]];
        }
        else if (species2ValueIdentify == "gorilla") {
            colorNow2 = cross_speciesClustercolors[mapDataforBorderGorilla[uniqueClusters2List[i]]];
        }
        else if (species2ValueIdentify == "marmoset") {
            colorNow2 = cross_speciesClustercolors[mapDataforBorderMarmoset[uniqueClusters2List[i]]];
        }
        else if (species2ValueIdentify == "rhesus") {
            colorNow2 = cross_speciesClustercolors[mapDataforBorderRhesus[uniqueClusters2List[i]]];
        }
        svg.append("line")
            .attr("x1", width)
            .attr("x2", width)
            .attr("y1", valuenext2)
            .attr("y2", valnow2)
            .attr("stroke-width", 2)
            .attr("stroke", colorNow2)
            //.style("paint-order", "stroke")
            .style("stroke-location", "inside");
        if (barflag) {
            svg.append("rect")
                .attr("x", width)
                .attr("y", valuenext2 + ((valnow2 - valuenext2) / 4))
                .attr("width", ((inspecies2ClusterCounts[uniqueClusters2List[i]]) / 100 ))
                .attr("height", (valnow2 - valuenext2) / 2)
                .attr("fill", in_speciesClustercolors[uniqueClusters2List[i]]);
        }

    }

    var tooltipWidth;
    if (barflag) {
        tooltipWidth = window.innerWidth -width;

    }
    else {
        tooltipWidth = window.innerWidth -width;
    }


    var m;
    var w;
    var h;
    if (barflag) {
        m = { top: 50, right: 350, bottom: 80, left: 65 },
            w = window.innerWidth-(window.innerWidth * 0.99 - m.left - m.right),
            h = window.innerHeight-(window.innerHeight * 0.99 - m.top - m.bottom);

    }
    else {
        m = { top: 5, right: 305, bottom: 80, left: 65 },
            w = window.innerWidth-(window.innerWidth * 0.99 - m.left - m.right),
            h = window.innerHeight-(window.innerHeight * 0.97 - m.top - m.bottom);
    }

    // create a tooltip
    var tooltip = d3
        .select("#my_dataviz")
        .append("div")
        .style("opacity", 0)
        .attr("class", "tooltip")
        .style("background-color", "white")
        //.style("border", "solid")
        .style("width", w)
        //.style("border-width", "2px")
        //.style("border-radius", "5px")
        //.style("padding", "5px")
        .style("position", "absolute");

    // Three function that change the tooltip when user hover / move / leave a cell
    var mouseover = function (d) {
        svg.select("#axisSelectionpolygon").remove();
        svg.select("#axisSelectionText").remove();
        tooltip.style("opacity", 1);
        tooltip.style("z-index", 1);
        d3.select(this)
            .style("stroke", function (d) {
                if (d.cross_species_cluster1_species_1 == d.cross_species_cluster2_species_2) {
                    return cross_speciesClustercolors[d.cross_species_cluster1_species_1];
                }
                else {
                    return "black";
                }
            })
            .style("fill", function (d) {
                return myColor(d.dist);
            })
            .style("stroke-width", function (d) {

                if (d.cross_species_cluster1_species_1 == d.cross_species_cluster2_species_2) {
                    return 8;
                }
                else {
                    return 5;
                }
            })
            //.style("paint-order", "stroke")
            .style("stroke-location", "inside")
            .style("opacity", 1)
            .style("cursor", "pointer");


    };
    var mousemove = function (d) {
        svg.select("#axisSelectionpolygon").remove();
        svg.select("#axisSelectionText").remove();
        d3.select("#marker2").remove();
        d3.select("#marker1").remove();
        d3.select("#marker3").remove();
        //var crossSpeciesAddToTooltip = "";
        //var species1AddToTooltip = "";
        //var species2AddToTooltip = "";
        //var species1AddToTooltip1 = "";
        //var species2AddToTooltip2 = "";
        var finaltooltip = "";
        if (d.cross_species_cluster1_species_1 == d.cross_species_cluster2_species_2) {
            finaltooltip = finaltooltip + "<table border=\"1\"; style=\"table-layout: auto;width: auto;\" ><tr><th></th><th  bgcolor=\"white\"><img src=\"" + ximage + "\" alt=\"Human\" height=50 width=50 /></th><th  bgcolor=\"white\"><img src=\"" + yimage + "\" alt=\"Marmoset\" height=50 width=50 /></th></tr><tr><td rowspan=\"1\"  bgcolor=\"white\"><div><i>In-species cluster</i></div></td><td  bgcolor=\"white\"><div style=\"color:" + in_speciesClustercolors[d.cluster_1] + "; -webkit-text-stroke: 0.5 black;\">" + d.cluster_1 + "</div></td><td  bgcolor=\"white\"><div style=\"color:" + in_speciesClustercolors[d.cluster_2] +"; -webkit-text-stroke: 0.5 black;\">" + d.cluster_2 + "</div></td></tr>";
        }
        else {
            finaltooltip = finaltooltip + "<table border=\"1\" ; style=\"table-layout: auto;width: auto;\"><tr><th></th><th  bgcolor=\"white\"><img src=\"" + ximage + "\" alt=\"Human\" height=50 width=50 /></th><th  bgcolor=\"white\"><img src=\"" + yimage + "\" alt=\"Marmoset\" height=50 width=50 /></th></tr><tr><td rowspan=\"1\"  bgcolor=\"white\"><i>In-species cluster</i></div></td><td  bgcolor=\"white\"><div style=\"color:" + in_speciesClustercolors[d.cluster_1] + ";\">" + d.cluster_1 + "</div></td><td  bgcolor=\"white\"><div style=\"color:" + in_speciesClustercolors[d.cluster_2] + ";\">" + d.cluster_2 + "</div></td></tr>";
        }
        if (barflag) {
            finaltooltip = finaltooltip + "<tr><td rowspan=\"1\"  bgcolor=\"white\"><div><i>Cluster cell count</i></div></td><td  bgcolor=\"white\">" + inspecies1ClusterCounts[d.cluster_1] + "</td><td  bgcolor=\"white\">" + inspecies2ClusterCounts[d.cluster_2] + "</td></tr>";
        }
        finaltooltip = finaltooltip + "<tr><td rowspan=\"1\"  bgcolor=\"white\"><div><i>Subclass</i></div></td><td  bgcolor=\"white\"><div style=\"color:" + subClassColors[d.subclass_1] + ";\">" + d.subclass_1 + "</div></td><td  bgcolor=\"white\"><div style=\"color:" + subClassColors[d.subclass_2] + ";\">" + d.subclass_2 + "</div></td></tr><tr><td rowspan=\"1\"  bgcolor=\"white\"><div><i>Class</i></div></td><td  bgcolor=\"white\"><div style=\"color:" + classColors[d.class_1] + ";\">" + d.class_1 + "</div></td><td  bgcolor=\"white\"><div style=\"color:" + classColors[d.class_2] + ";\">"+d.class_2+"</div></td></tr>";
        

        //if (layerFlag
        layercheck = ['human','gorilla','chimp'];
        {
            if (layercheck.includes(species1ValueIdentify) || layercheck.includes(species2ValueIdentify)){
                finaltooltip = finaltooltip + "<tr><td rowspan=\"1\" bgcolor=\"white\"><i><div> Layer distribution</div><div style=\" text-align: center;\"><div style=\"color:#7fc97f;text-shadow: black, black,  black,  black;\"> Layer 1</div> <div style=\"color:#beaed4;text-shadow:  black,  black, black, black;\"> Layer 2</div> <div style=\"color:#fdc086;text-shadow:  black,  black,  black, black;\"> Layer 3</div> <div style=\"color:#ffff99;text-shadow:  black,  black,  black,  black;\"> Layer 4</div> <div style=\"color:#386cb0;text-shadow:  black, black,  black,  black; \"> Layer 5</div> <div style=\"color:#f0027f;text-shadow:  black,  black,  black, black; \"> Layer 6</div></div> </i></td>";
            }

            if (layercheck.includes(species1ValueIdentify)) {
                let angle1Sp1 = 0.0 * 100;
                let angle2Sp1 = 0.0 * 100;
                let angle3Sp1 = 0.0 * 100;
                let angle4Sp1 = 0.0 * 100;
                let angle5Sp1 = 0.0 * 100;
                let angle6Sp1 = 0.0 * 100;
                if (species1ValueIdentify == 'human') {
                    angle1Sp1 = layerInfoForHuman[d.cluster_1][1] * 100;
                    angle2Sp1 = layerInfoForHuman[d.cluster_1][2] * 100;
                    angle3Sp1 = layerInfoForHuman[d.cluster_1][3] * 100;
                    angle4Sp1 = layerInfoForHuman[d.cluster_1][4] * 100;
                    angle5Sp1 = layerInfoForHuman[d.cluster_1][5] * 100;
                    angle6Sp1 = layerInfoForHuman[d.cluster_1][6] * 100;
                }
                else if (species1ValueIdentify == 'gorilla') {
                    angle1Sp1 = layerInfoForGorilla[d.cluster_1][1] * 100;
                    angle2Sp1 = layerInfoForGorilla[d.cluster_1][2] * 100;
                    angle3Sp1 = layerInfoForGorilla[d.cluster_1][3] * 100;
                    angle4Sp1 = layerInfoForGorilla[d.cluster_1][4] * 100;
                    angle5Sp1 = layerInfoForGorilla[d.cluster_1][5] * 100;
                    angle6Sp1 = layerInfoForGorilla[d.cluster_1][6] * 100;
                }
                else if (species1ValueIdentify == 'chimp') {
                    angle1Sp1 = layerInfoForChimp[d.cluster_1][1] * 100;
                    angle2Sp1 = layerInfoForChimp[d.cluster_1][2] * 100;
                    angle3Sp1 = layerInfoForChimp[d.cluster_1][3] * 100;
                    angle4Sp1 = layerInfoForChimp[d.cluster_1][4] * 100;
                    angle5Sp1 = layerInfoForChimp[d.cluster_1][5] * 100;
                    angle6Sp1 = layerInfoForChimp[d.cluster_1][6] * 100;
                }
                finaltooltip = finaltooltip + "<td bgcolor=\"white\"><br/><div style=\" align-items: left\"><div>" + "<div style=\"background-color:#7fc97f; width:" + angle1Sp1 + "%\">" + (angle1Sp1 / 100).toFixed(2) + "</div>" + "<div style=\"background-color:#beaed4; width:" + angle2Sp1 + "%\">" + (angle2Sp1 / 100).toFixed(2) + "</div>" + "<div style=\"background-color:#fdc086; width:" + angle3Sp1 + "%\">" + (angle3Sp1 / 100).toFixed(2) + "</div>" + "<div style=\"background-color:#ffff99; width:" + angle4Sp1 + "%\">" + (angle4Sp1 / 100).toFixed(2) + "</div>" + "<div style=\"background-color:#386cb0; width:" + angle5Sp1 + "%\">" + (angle5Sp1 / 100).toFixed(2) + "</div>" + "<div style=\"background-color:#f0027f; width:" + angle6Sp1 + "%\">" + (angle6Sp1 / 100).toFixed(2) + "</div>" + "</div></div></td>";

                }
            if (layercheck.includes(species2ValueIdentify)) {
                let angle1Sp2 = 0.0 * 100;
                let angle2Sp2 = 0.0 * 100;
                let angle3Sp2 = 0.0 * 100;
                let angle4Sp2 = 0.0 * 100;
                let angle5Sp2 = 0.0 * 100;
                let angle6Sp2 = 0.0 * 100;
                if (species2ValueIdentify == 'human') {
                    angle1Sp2 = layerInfoForHuman[d.cluster_2][1] * 100;
                    angle2Sp2 = layerInfoForHuman[d.cluster_2][2] * 100;
                    angle3Sp2 = layerInfoForHuman[d.cluster_2][3] * 100;
                    angle4Sp2 = layerInfoForHuman[d.cluster_2][4] * 100;
                    angle5Sp2 = layerInfoForHuman[d.cluster_2][5] * 100;
                    angle6Sp2 = layerInfoForHuman[d.cluster_2][6] * 100;
                }
                else if (species2ValueIdentify == 'gorilla') {
                    angle1Sp2 = layerInfoForGorilla[d.cluster_2][1] * 100;
                    angle2Sp2 = layerInfoForGorilla[d.cluster_2][2] * 100;
                    angle3Sp2 = layerInfoForGorilla[d.cluster_2][3] * 100;
                    angle4Sp2 = layerInfoForGorilla[d.cluster_2][4] * 100;
                    angle5Sp2 = layerInfoForGorilla[d.cluster_2][5] * 100;
                    angle6Sp2 = layerInfoForGorilla[d.cluster_2][6] * 100;
                }
                else if (species2ValueIdentify == 'chimp') {
                    angle1Sp2 = layerInfoForChimp[d.cluster_2][1] * 100;
                    angle2Sp2 = layerInfoForChimp[d.cluster_2][2] * 100;
                    angle3Sp2 = layerInfoForChimp[d.cluster_2][3] * 100;
                    angle4Sp2 = layerInfoForChimp[d.cluster_2][4] * 100;
                    angle5Sp2 = layerInfoForChimp[d.cluster_2][5] * 100;
                    angle6Sp2 = layerInfoForChimp[d.cluster_2][6] * 100;
                }


                finaltooltip = finaltooltip + "<td bgcolor=\"white\"><br/><div style=\" align-items: right\"><div>" + "<div style=\"background-color:#7fc97f; width:" + angle1Sp2 + "%\">" + (angle1Sp2 / 100).toFixed(2) + "</div>" + "<div style=\"background-color:#beaed4; width:" + angle2Sp2 + "%\">" + (angle2Sp2 / 100).toFixed(2) + "</div>" + "<div style=\"background-color:#fdc086; width:" + angle3Sp2 + "%\">" + (angle3Sp2 / 100).toFixed(2) + "</div>" + "<div style=\"background-color:#ffff99; width:" + angle4Sp2 + "%\">" + (angle4Sp2 / 100).toFixed(2) + "</div>" + "<div style=\"background-color:#386cb0; width:" + angle5Sp2 + "%\">" + (angle5Sp2 / 100).toFixed(2) + "</div>" + "<div style=\"background-color:#f0027f; width:" + angle6Sp2 + "%\">" + (angle6Sp2 / 100).toFixed(2) + "</div>" + "</div></div></td>";

            }
            
            finaltooltip = finaltooltip + "</tr>";
        }
        let clustDistVal = parseFloat(d.dist).toFixed(2);
        finaltooltip = finaltooltip + "<tr><td rowspan=\"1\" bgcolor=\"white\"><div><i>Cluster distance</i></div></td><td colspan=\"2\" bgcolor=\"white\">" + clustDistVal + "</td></tr>";

        if (d.cross_species_cluster1_species_1 == d.cross_species_cluster2_species_2) {
            finaltooltip = finaltooltip + "<tr><td rowspan=\"1\" bgcolor=\"white\"><div><i>Cross-species cluster</i></div></td><td colspan=\"2\" bgcolor=\"white\"><div style=\"color:" + cross_speciesClustercolors[d.cross_species_cluster1_species_1] +"; -webkit-text-stroke: 0.2 black;\" >" + d.cross_species_cluster1_species_1+"</div></td></tr>";
        }
        finaltooltip = finaltooltip + "</table>";

        //if (d.cross_species_cluster1_species_1 == d.cross_species_cluster2_species_2) {
        //    crossSpeciesAddToTooltip = "<div style=\"color: " + cross_speciesClustercolors[d.cross_species_cluster1_species_1] + "; -webkit-text-stroke: 0.2 black; cursor:pointer;\"> Cross species cluster: <b>" + d.cross_species_cluster1_species_1 + "</b></div>";//labelcolorsforAxis[parseInt(d.cross_species_cluster1_species_1)];
        //}
        //species1AddToTooltip = "<div style=\"color: " + in_speciesClustercolors[d.cluster_1] + ";-webkit-text-stroke: 0.2 black;  cursor:pointer;\"> Cluster1 : <b>" + d.cluster_1 + "</b></div>";
        //species2AddToTooltip = "<div style=\"color: " + in_speciesClustercolors[d.cluster_2] + ";-webkit-text-stroke: 0.2 black;  cursor:pointer;\"> Cluster2 : <b>" + d.cluster_2 + "</b></div>";
        //if (barflag) {
        //    species1AddToTooltip1 = "<div style=\"color: " + in_speciesClustercolors[d.cluster_1] + ";-webkit-text-stroke: 0.2 black;  cursor:pointer;\"> Cell count cluster1 : <b>" + inspecies1ClusterCounts[d.cluster_1] + "</b></div>";
        //    species2AddToTooltip2 = "<div style=\"color: " + in_speciesClustercolors[d.cluster_2] + ";-webkit-text-stroke: 0.2 black;  cursor:pointer;\"> Cell count cluster2 : <b>" + inspecies2ClusterCounts[d.cluster_2] + "</b></div>";

        //}


        tooltip
            .html(finaltooltip)
            .style("background-color", "transparent")
            //.style("width", tooltipWidth)
            .style("right", 0)
            .style("top", 0);


        //if (d3.mouse(this)[0] > width/2.5) {
        //    if (d3.mouse(this)[0] < width / 2+width/4) {
        //        tooltip.style("left", d3.mouse(this)[0] - (width / 2.5) + "px");
        //    }
        //    else {
        //        tooltip.style("left", d3.mouse(this)[0] - (width / 2.5) + "px");
        //    }

        //}

        //else {
        //    if (d3.mouse(this)[0] < width / 2 - width / 4) {
        //        tooltip.style("left", d3.mouse(this)[0] + (width / 4) + "px");
        //    }
        //    else {
        //        tooltip.style("left", d3.mouse(this)[0] + (width / 4) + "px");
        //    }

        //}


        //if (d3.mouse(this)[1] > height / 2.2) {
        //    if (d3.mouse(this)[1] < height / 2 + height / 4) {
        //        tooltip.style("top", d3.mouse(this)[1] - height/3 + "px");
        //    }
        //    else {
        //    tooltip.style("top", d3.mouse(this)[1] - height/2 + "px");
        //}
        //}
        //else
        //{
        //    if (d3.mouse(this)[1] < height / 2 - height / 4) {
        //        tooltip.style("top", d3.mouse(this)[1] + height/6 + "px");
        //    }
        //    else {
        //        tooltip.style("top", d3.mouse(this)[1] + height/8 + "px");
        //    }
        //}


    };
    var mouseleave = function (d) {
        tooltip.style("opacity", 0);
        d3.select(this).style("stroke", function (d) {
            if (d.cross_species_cluster1_species_1 == d.cross_species_cluster2_species_2) {
                return cross_speciesClustercolors[d.cross_species_cluster1_species_1];
            }
            else {
                return "black";
            }
        })
            .style("opacity", 0.9).style("stroke-width", function (d) {
                return 0;
            });
    };
    var mouseclick = function (d) {
        d3.select("#marker1").remove();
        d3.select("#marker2").remove();
        d3.select("#marker3").remove();
        if (barflag)
        {
            svg.append("line")
                .attr("id", "marker1")
                .attr("x1", 0)
                .attr("y1", d3.mouse(this)[1])
                .attr("x2", width)
                .attr("y2", d3.mouse(this)[1])
                .attr("stroke-width", 2)
                .style("stroke-dasharray", ("3, 3"))
                .style("stroke-opacity", 0.9)
                .attr("stroke", in_speciesClustercolors[d.cluster_2])
                .attr("marker-end", "url(#triangle)");

            svg.append("line")
                .attr("id", "marker2")
                .attr("x1", d3.mouse(this)[0])
                .attr("y1", 0)
                .attr("x2", d3.mouse(this)[0])
                .attr("y2", height)
                .attr("stroke-width", 2)
                .style("stroke-dasharray", ("3, 3"))
                .style("stroke-opacity", 0.9)
                .attr("stroke", in_speciesClustercolors[d.cluster_1])
                .attr("marker-end", "url(#triangle)");

            svg.append("circle")
                .attr("id", "marker3")
                .attr("cx", d3.mouse(this)[0])
                .attr("cy", d3.mouse(this)[1])
                .attr("r", 5)
                .style("fill", myColor(d.dist))
                .style("stroke", "black")
                .attr("stroke-width", 1);

        }
        else
        {
            svg.append("line")
                .attr("id", "marker1")
                .attr("x1", 0)
                .attr("y1", d3.mouse(this)[1])
                .attr("x2", d3.mouse(this)[0])
                .attr("y2", d3.mouse(this)[1])
                .attr("stroke-width", 2)
                .style("stroke-dasharray", ("3, 3"))
                .style("stroke-opacity", 0.9)
                .attr("stroke", in_speciesClustercolors[d.cluster_2])
                .attr("marker-end", "url(#triangle)");

            svg.append("line")
                .attr("id", "marker2")
                .attr("x1", d3.mouse(this)[0])
                .attr("y1", d3.mouse(this)[1])
                .attr("x2", d3.mouse(this)[0])
                .attr("y2", height)
                .attr("stroke-width", 2)
                .style("stroke-dasharray", ("3, 3"))
                .style("stroke-opacity", 0.9)
                .attr("stroke", in_speciesClustercolors[d.cluster_1])
                .attr("marker-end", "url(#triangle)");

            svg.append("circle")
                .attr("id", "marker3")
                .attr("cx", d3.mouse(this)[0])
                .attr("cy", d3.mouse(this)[1])
                .attr("r", 5)
                .style("fill", myColor(d.dist))
                .style("stroke", "black")
                .attr("stroke-width", 1);
        }


        let selectionIDs = [];
        selectionIDs.push(d.cluster_1);
        selectionIDs.push(d.cluster_2);
        if (isQtAvailable) {
            QtBridge.js_passSelectionToQt(selectionIDs);
        }
    };

    // add the squares
    svg
        .selectAll()
        .data(_data, function (d) {
            return d.cluster_1 + ":" + d.cluster_2;
        })
        .enter()
        .append("rect")
        .attr("x", function (d) {
            return x(d.cluster_1);
        })
        .attr("y", function (d) {
            return y(d.cluster_2);
        })

        .attr("width", x.bandwidth() + 1)
        .attr("height", y.bandwidth() + 1)
        .style("fill", function (d) {
            return myColor(d.dist);
        })
        .style("stroke-width", function (d) {
            return 0;
        })
        .style("stroke", function (d) {
            if (d.cross_species_cluster1_species_1 == d.cross_species_cluster2_species_2) {
                return cross_speciesClustercolors[d.cross_species_cluster1_species_1];
            }
            else {
                return "black";
            }

        })
        .style("opacity", 0.9)
        .on("mouseover", mouseover)
        .on("mousemove", mousemove)
        .on("mouseleave", mouseleave)
        .on("click", mouseclick);



    {
        for (var CrossSpeciesI = 0; CrossSpeciesI < uniqueCrossSpeicesClusters1List.length; CrossSpeciesI++)
        {

            var correspondingCrossspeciescluster;
            var XFirstElement = "";
            var XLastElement = "";
            var YFirstElement = "";
            var YLastElement = "";
            var elementVal = uniqueCrossSpeicesClusters1List[CrossSpeciesI];
            if (species1ValueIdentify == "human") {
                correspondingCrossspeciescluster = mapDataforBorderHuman[elementVal];
                for (var i = 0; i < crossSpeciesFilterspecies1Cluster.length; i++) {
                    if (mapDataforBorderHuman[crossSpeciesFilterspecies1Cluster[i]] == correspondingCrossspeciescluster) {
                        XFirstElement = x(crossSpeciesFilterspecies1Cluster[i]);
                        if (i + 1 < crossSpeciesFilterspecies1Cluster.length) { XLastElement = x(crossSpeciesFilterspecies1Cluster[i + 1]); }
                        else { XLastElement = width; }
                        break;
                    }
                }
            }
            else if (species1ValueIdentify == "chimp") {
                correspondingCrossspeciescluster = mapDataforBorderChimp[elementVal];
                for (var i = 0; i < crossSpeciesFilterspecies1Cluster.length; i++) {
                    if (mapDataforBorderChimp[crossSpeciesFilterspecies1Cluster[i]] == correspondingCrossspeciescluster) {
                        XFirstElement = x(crossSpeciesFilterspecies1Cluster[i]);
                        if (i + 1 < crossSpeciesFilterspecies1Cluster.length) { XLastElement = x(crossSpeciesFilterspecies1Cluster[i + 1]); }
                        else { XLastElement = width; }
                        break;
                    }
                }
            }
            else if (species1ValueIdentify == "gorilla") {
                correspondingCrossspeciescluster = mapDataforBorderGorilla[elementVal];
                for (var i = 0; i < crossSpeciesFilterspecies1Cluster.length; i++) {
                    if (mapDataforBorderGorilla[crossSpeciesFilterspecies1Cluster[i]] == correspondingCrossspeciescluster) {
                        XFirstElement = x(crossSpeciesFilterspecies1Cluster[i]);
                        if (i + 1 < crossSpeciesFilterspecies1Cluster.length) { XLastElement = x(crossSpeciesFilterspecies1Cluster[i + 1]); }
                        else { XLastElement = width; }
                        break;
                    }
                }
            }
            else if (species1ValueIdentify == "rhesus") {
                correspondingCrossspeciescluster = mapDataforBorderRhesus[elementVal];
                for (var i = 0; i < crossSpeciesFilterspecies1Cluster.length; i++) {
                    if (mapDataforBorderRhesus[crossSpeciesFilterspecies1Cluster[i]] == correspondingCrossspeciescluster) {
                        XFirstElement = x(crossSpeciesFilterspecies1Cluster[i]);
                        if (i + 1 < crossSpeciesFilterspecies1Cluster.length) { XLastElement = x(crossSpeciesFilterspecies1Cluster[i + 1]); }
                        else { XLastElement = width; }
                        break;
                    }
                }
            }
            ////y
            if (species2ValueIdentify == "chimp") {
                for (var i = crossSpeciesFilterspecies2Cluster.length - 1; i >= 0; i--) {
                    if (mapDataforBorderChimp[crossSpeciesFilterspecies2Cluster[i]] == correspondingCrossspeciescluster) {
                        YFirstElement = y(crossSpeciesFilterspecies2Cluster[i]);
                        if (i > 0) { YLastElement = y(crossSpeciesFilterspecies2Cluster[i - 1]); }
                        else { YLastElement = height; }
                        break;
                    }
                }
            }
            else if (species2ValueIdentify == "gorilla") {
                for (var i = crossSpeciesFilterspecies2Cluster.length - 1; i >= 0; i--) {
                    if (mapDataforBorderGorilla[crossSpeciesFilterspecies2Cluster[i]] == correspondingCrossspeciescluster) {
                        YFirstElement = y(crossSpeciesFilterspecies2Cluster[i]);
                        if (i > 0) { YLastElement = y(crossSpeciesFilterspecies2Cluster[i - 1]); }
                        else { YLastElement = height; }
                        break;
                    }
                }
            }
            else if (species2ValueIdentify == "marmoset") {
                for (var i = crossSpeciesFilterspecies2Cluster.length - 1; i >= 0; i--) {
                    if (mapDataforBorderMarmoset[crossSpeciesFilterspecies2Cluster[i]] == correspondingCrossspeciescluster) {
                        YFirstElement = y(crossSpeciesFilterspecies2Cluster[i]);
                        if (i > 0) { YLastElement = y(crossSpeciesFilterspecies2Cluster[i - 1]); }
                        else { YLastElement = height; }
                        break;
                    }
                }
            }
            else if (species2ValueIdentify == "rhesus") {
                for (var i = crossSpeciesFilterspecies2Cluster.length - 1; i >= 0; i--) {
                    if (mapDataforBorderRhesus[crossSpeciesFilterspecies2Cluster[i]] == correspondingCrossspeciescluster) {
                        YFirstElement = y(crossSpeciesFilterspecies2Cluster[i]);
                        if (i > 0) { YLastElement = y(crossSpeciesFilterspecies2Cluster[i - 1]); }
                        else { YLastElement = height; }
                        break;
                    }
                }
            }

            if (YLastElement == "") {
                YLastElement = "0.00";
            }
            if (YFirstElement == "") {
                YFirstElement = y(crossSpeciesFilterspecies2Cluster[crossSpeciesFilterspecies2Cluster.length - 1]);
            }
            //log(cross_speciesClustercolors[correspondingCrossspeciescluster]);
            var id1 = "crossSpeciesIdentifierPolygonI" + String(CrossSpeciesI);
            var cols1 = cross_speciesClustercolors[correspondingCrossspeciescluster];
            var poly1 = XFirstElement + ',' + YFirstElement + ' ' + XLastElement + ',' + YFirstElement + ' ' + XLastElement + ',' + YLastElement + ' ' + XFirstElement + ',' + YLastElement + ' ' + XFirstElement + ',' + YFirstElement;
            svg.append('polygon')
                .attr("id", id1)
                .attr('points', poly1)
                .attr('stroke', cols1)
                .attr("stroke-width", 3)
                .attr('fill', 'none');



        }

        for (var CrossSpeciesJ = 0; CrossSpeciesJ < uniqueCrossSpeicesClusters1List.length; CrossSpeciesJ++) {
            svg.select("#axisSelectionpolygon").remove();
            svg.select("#axisSelectionText").remove();
            var correspondingCrossspeciescluster;
            var XFirstElement = "";
            var XLastElement = "";
            var YFirstElement = "";
            var YLastElement = "";
            var elementVal = uniqueCrossSpeicesClusters2List[CrossSpeciesJ];
            ////y
            if (species2ValueIdentify == "chimp") {
                correspondingCrossspeciescluster = mapDataforBorderChimp[elementVal];
                for (var i = crossSpeciesFilterspecies2Cluster.length - 1; i >= 0; i--) {
                    if (mapDataforBorderChimp[crossSpeciesFilterspecies2Cluster[i]] == correspondingCrossspeciescluster) {
                        YFirstElement = y(crossSpeciesFilterspecies2Cluster[i]);
                        if (i > 0) { YLastElement = y(crossSpeciesFilterspecies2Cluster[i - 1]); }
                        else { YLastElement = height; }
                        break;
                    }
                }
            }
            else if (species2ValueIdentify == "gorilla") {
                correspondingCrossspeciescluster = [mapDataforBorderGorilla[elementVal]];
                for (var i = crossSpeciesFilterspecies2Cluster.length - 1; i >= 0; i--) {
                    if (mapDataforBorderGorilla[crossSpeciesFilterspecies2Cluster[i]] == correspondingCrossspeciescluster) {
                        YFirstElement = y(crossSpeciesFilterspecies2Cluster[i]);
                        if (i > 0) { YLastElement = y(crossSpeciesFilterspecies2Cluster[i - 1]); }
                        else { YLastElement = height; }
                        break;
                    }
                }
            }
            else if (species2ValueIdentify == "marmoset") {
                correspondingCrossspeciescluster = mapDataforBorderMarmoset[elementVal];
                for (var i = crossSpeciesFilterspecies2Cluster.length - 1; i >= 0; i--) {
                    if (mapDataforBorderMarmoset[crossSpeciesFilterspecies2Cluster[i]] == correspondingCrossspeciescluster) {
                        YFirstElement = y(crossSpeciesFilterspecies2Cluster[i]);
                        if (i > 0) { YLastElement = y(crossSpeciesFilterspecies2Cluster[i - 1]); }
                        else { YLastElement = height; }
                        break;
                    }
                }
            }
            else if (species2ValueIdentify == "rhesus") {
                correspondingCrossspeciescluster = mapDataforBorderRhesus[elementVal];
                for (var i = crossSpeciesFilterspecies2Cluster.length - 1; i >= 0; i--) {
                    if (mapDataforBorderRhesus[crossSpeciesFilterspecies2Cluster[i]] == correspondingCrossspeciescluster) {
                        YFirstElement = y(crossSpeciesFilterspecies2Cluster[i]);
                        if (i > 0) { YLastElement = y(crossSpeciesFilterspecies2Cluster[i - 1]); }
                        else { YLastElement = height; }
                        break;
                    }
                }
            }
            ////x

            if (species1ValueIdentify == "human") {
                for (var i = 0; i < crossSpeciesFilterspecies1Cluster.length; i++) {
                    if (mapDataforBorderHuman[crossSpeciesFilterspecies1Cluster[i]] == correspondingCrossspeciescluster) {
                        XFirstElement = x(crossSpeciesFilterspecies1Cluster[i]);
                        if (i + 1 < crossSpeciesFilterspecies1Cluster.length) { XLastElement = x(crossSpeciesFilterspecies1Cluster[i + 1]); }
                        else { XLastElement = width; }
                        break;
                    }
                }
            }
            else if (species1ValueIdentify == "chimp") {
                for (var i = 0; i < crossSpeciesFilterspecies1Cluster.length; i++) {
                    if (mapDataforBorderChimp[crossSpeciesFilterspecies1Cluster[i]] == correspondingCrossspeciescluster) {
                        XFirstElement = x(crossSpeciesFilterspecies1Cluster[i]);
                        if (i + 1 < crossSpeciesFilterspecies1Cluster.length) { XLastElement = x(crossSpeciesFilterspecies1Cluster[i + 1]); }
                        else { XLastElement = width; }
                        break;
                    }
                }
            }
            else if (species1ValueIdentify == "gorilla") {
                for (var i = 0; i < crossSpeciesFilterspecies1Cluster.length; i++) {
                    if (mapDataforBorderGorilla[crossSpeciesFilterspecies1Cluster[i]] == correspondingCrossspeciescluster) {
                        XFirstElement = x(crossSpeciesFilterspecies1Cluster[i]);
                        if (i + 1 < crossSpeciesFilterspecies1Cluster.length) { XLastElement = x(crossSpeciesFilterspecies1Cluster[i + 1]); }
                        else { XLastElement = width; }
                        break;
                    }
                }
            }
            else if (species1ValueIdentify == "rhesus") {
                for (var i = 0; i < crossSpeciesFilterspecies1Cluster.length; i++) {
                    if (mapDataforBorderRhesus[crossSpeciesFilterspecies1Cluster[i]] == correspondingCrossspeciescluster) {
                        XFirstElement = x(crossSpeciesFilterspecies1Cluster[i]);
                        if (i + 1 < crossSpeciesFilterspecies1Cluster.length) { XLastElement = x(crossSpeciesFilterspecies1Cluster[i + 1]); }
                        else { XLastElement = width; }
                        break;
                    }
                }
            }

            if (YLastElement == "") {
                YLastElement = "0.00";
            }
            if (YFirstElement == "") {
                YFirstElement = y(crossSpeciesFilterspecies2Cluster[crossSpeciesFilterspecies2Cluster.length - 1]);
            }
            var cols2 = cross_speciesClustercolors[correspondingCrossspeciescluster];
            var id2 = "crossSpeciesIdentifierPolygonJ" + String(CrossSpeciesJ);
            var poly2 = XFirstElement + ',' + YFirstElement + ' ' + XLastElement + ',' + YFirstElement + ' ' + XLastElement + ',' + YLastElement + ' ' + XFirstElement + ',' + YLastElement + ' ' + XFirstElement + ',' + YFirstElement;
            svg.append('polygon')
                .attr("id", id2)
                .attr('points', poly2)
                .attr('stroke', cols2)
                .attr("stroke-width", 3)
                .attr('fill', 'none');

        }
    }







    var c = backgroundColor.substring(1);      // strip #
    var rgb = parseInt(c, 16);   // convert rrggbb to decimal
    var r = (rgb >> 16) & 0xff;  // extract red
    var g = (rgb >> 8) & 0xff;  // extract green
    var b = (rgb >> 0) & 0xff;  // extract blue

    var luma = 0.2126 * r + 0.7152 * g + 0.0722 * b; // per ITU-R BT.709
    

     ximage="";
     yimage="";
    if (species2ValueIdentify == "gorilla") {
        
        if (luma < 40) {
            yimage = 'https://i.ibb.co/0CYCryh/gorilla-light.png';
        }
        else {
            yimage = 'https://i.ibb.co/RNxHKTF/gorilla-dark.png';
        }
    }
    else if (species2ValueIdentify == "marmoset")
    {
        if (luma < 40) {          
            yimage = 'https://i.ibb.co/b3mDHXN/marmoset-light.png';
        }
        else {
            yimage = 'https://i.ibb.co/SXjQXNN/marmoset-dark.png';
        }
    }
    else if (species2ValueIdentify == "rhesus") {
        if (luma < 40) {
            yimage = 'https://i.ibb.co/YTdCB33/rhesus-light.png';
        }
        else {
            yimage = 'https://i.ibb.co/k8FjPSP/rhesus-dark.png';
        }
    }
    else if (species2ValueIdentify == "chimp") {
        if (luma < 40) {
            yimage = 'https://i.ibb.co/j4gpfjp/chimpanzee-light.png';
        }
        else {
            yimage = 'https://i.ibb.co/mvDVVhz/chimpanzee-dark.png';
        }
    }

    if (species1ValueIdentify == "gorilla") {
        if (luma < 40) {
            ximage = 'https://i.ibb.co/0CYCryh/gorilla-light.png';
        }
        else {
            ximage = 'https://i.ibb.co/RNxHKTF/gorilla-dark.png';
        }
    }
    else if (species1ValueIdentify == "chimp") {
        if (luma < 40) {
            ximage = 'https://i.ibb.co/j4gpfjp/chimpanzee-light.png';
        }
        else {
            ximage = 'https://i.ibb.co/mvDVVhz/chimpanzee-dark.png';
        }
    }
    else if (species1ValueIdentify == "rhesus") {
        if (luma < 40) {
            ximage = 'https://i.ibb.co/YTdCB33/rhesus-light.png';
        }
        else {
            ximage = 'https://i.ibb.co/k8FjPSP/rhesus-dark.png';
        }
    }
    else if (species1ValueIdentify == "human") {
        if (luma < 40) {
            ximage = 'https://i.ibb.co/9bBsDpZ/human-light.png';
        }
        else {
            ximage = 'https://i.ibb.co/nD675k0/human-dark.png';
        }
    }


    if (yimage!=="") {
        svg.append('image')
            .attr('xlink:href', yimage)
            .attr('width', width / 20)
            .attr('height', height / 25)
            .attr("x", 0-70)
            .attr("y", height);//
    }

    if (ximage!=="") {
        svg.append('image')
            .attr('xlink:href', ximage)
            .attr('width', width / 20)
            .attr('height', height / 25)
            .attr("x", 0-39)
            .attr("y", height+20);
    }

};



//Data Options
function setData(d) {
    _dataQueue.addData(d);
}
function queueData(d) {
    cross_speciesClusterInfo = { 'Chandelier_1': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'L2/3 IT_1': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'L2/3 IT_2': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'L2/3 IT_3': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'L4 IT_1': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'L4 IT_2': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'L5 ET_1': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'L5 ET_2': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'L5 IT_1': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'L5 IT_2': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'L5/6 NP_1': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'L5/6 NP_2': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'L6 CT_1': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'L6 CT_2': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'L6 IT_1': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'L6 IT Car3_1': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'L6 IT Car3_2': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'L6b_1': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'L6b_2': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'L6b_3': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Lamp5_1': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Lamp5_2': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Lamp5_Lhx6_1': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Pax6_1': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Pax6_2': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Pvalb_1': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Pvalb_2': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Pvalb_3': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Pvalb_4': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Sncg_1': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Sncg_2': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Sncg_3': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Sst_1': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Sst_2': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Sst_3': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Sst_4': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Sst_5': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Sst_6': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Sst_7': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Sst_8': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Sst_9': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Sst Chodl_1': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Vip_1': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Vip_2': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Vip_3': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Vip_4': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Vip_5': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Vip_6': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Vip_7': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Vip_8': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Astro_1': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Endo_1': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Micro-PVM_1': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'Oligo_1': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'OPC_1': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'OPC_2': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 }, 'VLMC_1': { 'averageDistance': 0.0, 'maxDistance': 0.0, 'minDistance': 9999.0, 'numberOfCells': 0 } }

    _data = JSON.parse(d);
    maxdistanceColor = parseInt(Math.max.apply(Math, _data.map(function (o) { return (o.dist); })));
    mindistanceColor = parseInt(Math.min.apply(Math, _data.map(function (o) { return (o.dist); })));
    if (maxdistanceColor == mindistanceColor) {
        cellsForLegend = 2;
    }
    else {
        cellsForLegend = 6;
    }
    species1ValueIdentify = _data[0].species_1;
    species2ValueIdentify = _data[0].species_2;
    uniqueClusters1List = [...new Set(_data.map(item => item.cluster_1))];
    uniqueClusters2List = [...new Set(_data.map(item => item.cluster_2))];
    uniqueCrossSpeicesClusters1List = [...new Set(_data.map(item => item.cross_species_cluster1_species_1))];
    uniqueCrossSpeicesClusters2List = [...new Set(_data.map(item => item.cross_species_cluster2_species_2))];
    //uniqueCrossspeciesClusters = uniqueCrossSpeicesClusters1List.concat(uniqueCrossSpeicesClusters2List);
    //uniqueCrossspeciesClusters = [...new Set([...uniqueCrossSpeicesClusters1List, ...uniqueCrossSpeicesClusters2List])];
    var container = "";
    crossSpeciesFilterspecies1Cluster = [];
    crossSpeciesFilterspecies2Cluster = [];
    crossSpeciesFilterspecies2ClusterTemp = [];
    for (var i = 0; i < _data.length; i++) {
        if (_data[i].cross_species_cluster1_species_1 == _data[i].cross_species_cluster2_species_2) {
            if (i == 0) {
                container = _data[i].cross_species_cluster1_species_1;
                crossSpeciesFilterspecies1Cluster.push(_data[i].cluster_1);
            }
            else {
                if (container != _data[i].cross_species_cluster1_species_1) {
                    container = _data[i].cross_species_cluster1_species_1;
                    crossSpeciesFilterspecies1Cluster.push(_data[i].cluster_1);
                }
            }

        }
    }
    for (var i = _data.length - 1; i >= 0; i--) {
        if (_data[i].cross_species_cluster1_species_1 == _data[i].cross_species_cluster2_species_2) {
            if (i == _data.length) {
                container = _data[i].cross_species_cluster2_species_2;
                crossSpeciesFilterspecies2ClusterTemp.push(_data[i].cluster_2);
            }
            else {
                if (container != _data[i].cross_species_cluster2_species_2) {
                    container = _data[i].cross_species_cluster2_species_2;
                    crossSpeciesFilterspecies2ClusterTemp.push(_data[i].cluster_2);
                }
            }

        }
    }
    for (var i = crossSpeciesFilterspecies2ClusterTemp.length - 1; i >= 0; i--) {
        crossSpeciesFilterspecies2Cluster.push(crossSpeciesFilterspecies2ClusterTemp[i]);
    }

    for (var i = 0; i < _data.length; i++) {
        if (_data[i].cross_species_cluster1_species_1 == _data[i].cross_species_cluster2_species_2) {

            var temp = cross_speciesClusterInfo[_data[i].cross_species_cluster1_species_1]['averageDistance'];
            temp = parseFloat(temp) + parseFloat(_data[i].dist);
            cross_speciesClusterInfo[_data[i].cross_species_cluster1_species_1]['averageDistance'] = temp;
            cross_speciesClusterInfo[_data[i].cross_species_cluster1_species_1]['numberOfCells'] = cross_speciesClusterInfo[_data[i].cross_species_cluster1_species_1]['numberOfCells'] + 1;

            if (parseFloat(cross_speciesClusterInfo[_data[i].cross_species_cluster1_species_1]['maxDistance']) < parseFloat( _data[i].dist)) {
                cross_speciesClusterInfo[_data[i].cross_species_cluster1_species_1]['maxDistance'] = _data[i].dist;
            }
            
            if (parseFloat(cross_speciesClusterInfo[_data[i].cross_species_cluster1_species_1]['minDistance']) > parseFloat(_data[i].dist)) {
                cross_speciesClusterInfo[_data[i].cross_species_cluster1_species_1]['minDistance'] = _data[i].dist;
            }
            
        }
    }

    simianVis();
    flag = true;
}

//Color Options
function setColor(d) {
    const valRa = d.split("*%*");
    queueColor(valRa[0], valRa[1]);
}
function queueColor(colorName, mirrorValue) {
    qtColor = colorName;
    if (mirrorValue == "F") {
        colorMirror = false;
    }
    else {
        colorMirror = true;
    }

    simianVis();
}

//BackgroundColor Options
function setBackgroundColor(d) {
    queueBackgroundColor(d);
}
function queueBackgroundColor(colorName) {
    backgroundColor = colorName;
    simianVis();
}

function histChart(d) {

    queuehistChart(d);
}
function queuehistChart(valD) {
    if (valD == "F") {
        barflag = false;
    }
    else {
        barflag = true;
    }

    simianVis();
}

//Range Options
function setRangeValue(d) {
    const valRa = d.split(" ");
    queueRangeValue(parseFloat(valRa[0]), parseFloat(valRa[1]));
}
function queueRangeValue(minRangeVal, maxRangeVal) {
    mindistanceColor = minRangeVal;
    maxdistanceColor = maxRangeVal;
    simianVis();
}

//Cluster Options
function setClusters(d) {
    queueClusters(d);
}
function queueClusters(d) {
    _clustersReceived = [];
    obj = JSON.parse(d);
    for (const [key, value] of Object.entries(obj[0])) {
        _clustersReceived.push(value);
    }
    for (var i = 0; i < _clustersReceived.length; i++) {
    }
    simianVis();

}

//Resize on window dimension change
function doALoadOfStuff() {
    if (flag) { simianVis(); }
}



function setInspeciesClusterCounts(d) {
    const valRa = d.split("*|||*"); 
    queueInspeciesClusterCounts(valRa[0], valRa[1]);
}
function queueInspeciesClusterCounts(clusterspecies1, clusterspecies2) {
    const valRa1 = clusterspecies1.split("*||*"); 
    const valRa2 = clusterspecies2.split("*||*"); 

    for (var i = 0; i < valRa1.length; i++)
    {
        var temp = valRa1[i].split("*|*");
        if (temp[0] !== "" && parseInt(temp[1]) !== undefined) {
            inspecies1ClusterCounts[temp[0]] = parseInt(temp[1]);

            totalInspeciescluster1counts = totalInspeciescluster1counts + parseInt(temp[1]);
        }
    }

    for (var i = 0; i < valRa2.length; i++)
    {
        var temp = valRa2[i].split("*|*");
        if (temp[0] !== "" && parseInt(temp[1]) !== undefined) {
            inspecies2ClusterCounts[temp[0]] = parseInt(temp[1]);

            totalInspeciescluster2counts = totalInspeciescluster2counts + parseInt(temp[1]);
        }
    }

    simianVis();
}