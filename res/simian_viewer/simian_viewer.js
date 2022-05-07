var _data = null;
var _clustersReceived = new Array();
var mindistanceColor= 0;
var maxdistanceColor = 0;
var _dataQueue = new SimianViewerDataQueue(1, queueData);
var cellsForLegend = 6;
var flag = false;
var species1ValueIdentify = "";
var species2ValueIdentify = "";
var uniqueClusters1List = [];
var uniqueClusters2List = [];
/*var dictOfCrossspeciesClusterCordinates = {};
var arrayOfUniqueCrossspeciesClusters = [];*/
window.onresize = doALoadOfStuff;

const cross_speciesClustercolors = { 'Astro_1': '#665C47', 'Chandelier_1': '#F641A8', 'Endo_1': '#8D6C62', 'L2/3 IT_1': '#B1EC30', 'L2/3 IT_2': '#B1EC30', 'L2/3 IT_3': '#B1EC30', 'L4 IT_1': '#00E5E5', 'L4 IT_2': '#00E5E5', 'L5 ET_1': '#0D5B78', 'L5 ET_2': '#0D5B78', 'L5 IT_1': '#50B2AD', 'L5 IT_2': '#50B2AD', 'L5/6 NP_1': '#3E9E64', 'L5/6 NP_2': '#3E9E64', 'L6 CT_1': '#2D8CB8', 'L6 CT_2': '#2D8CB8', 'L6 IT Car3_1': '#5100FF', 'L6 IT Car3_2': '#5100FF', 'L6 IT_1': '#A19922', 'L6b_1': '#7044AA', 'L6b_2': '#7044AA', 'L6b_3': '#7044AA', 'Lamp5_1': '#DA808C', 'Lamp5_2': '#DA808C', 'Lamp5_Lhx6_1': '#935F50', 'Micro-PVM_1': '#94AF97', 'OPC_1': '#374A45', 'OPC_2': '#374A45', 'Oligo_1': '#53776C', 'Pax6_1': '#71238C', 'Pax6_2': '#71238C', 'Pvalb_1': '#D93137', 'Pvalb_2': '#D93137', 'Pvalb_3': '#D93137', 'Pvalb_4': '#D93137', 'Sncg_1': '#DF70FF', 'Sncg_2': '#DF70FF', 'Sncg_3': '#DF70FF', 'Sst Chodl_1': '#B1B10C', 'Sst_1': '#FF9900', 'Sst_2': '#FF9900', 'Sst_3': '#FF9900', 'Sst_4': '#FF9900', 'Sst_5': '#FF9900', 'Sst_6': '#FF9900', 'Sst_7': '#FF9900', 'Sst_8': '#FF9900', 'Sst_9': '#FF9900', 'VLMC_1': '#697255', 'Vip_1': '#A45FBF', 'Vip_2': '#A45FBF', 'Vip_3': '#A45FBF', 'Vip_4': '#A45FBF', 'Vip_5': '#A45FBF', 'Vip_6': '#A45FBF', 'Vip_7': '#A45FBF', 'Vip_8': '#A45FBF' };

const in_speciesClustercolors = { 'Astro_1': '#958F80', 'Astro_2': '#484132', 'Astro_2': '#665C47', 'Astro_2': '#756D5A', 'Astro_2': '#7D7563', 'Astro_3': '#484132', 'Astro_3': '#5C5340', 'Astro_3': '#665C47', 'Astro_4': '#484132', 'Astro_4': '#574E3C', 'Astro_5': '#484132', 'Chandelier_1': '#F87CC3', 'Chandelier_2': '#AD2D76', 'Chandelier_2': '#F641A8', 'Endo_1': '#B09A93', 'Endo_2': '#634C45', 'Endo_2': '#987B72', 'Endo_3': '#7F6158', 'L2/3 IT_1': '#BDEE50', 'L2/3 IT_1': '#C9F170', 'L2/3 IT_10': '#9DD12A', 'L2/3 IT_10': '#A3DA2C', 'L2/3 IT_11': '#94C627', 'L2/3 IT_11': '#9DD12A', 'L2/3 IT_12': '#8CBB25', 'L2/3 IT_12': '#97C928', 'L2/3 IT_13': '#84B023', 'L2/3 IT_13': '#90C026', 'L2/3 IT_14': '#8AB724', 'L2/3 IT_15': '#7DA621', 'L2/3 IT_2': '#B1EC30', 'L2/3 IT_2': '#BDEE50', 'L2/3 IT_2': '#C2EF5D', 'L2/3 IT_2': '#C5F066', 'L2/3 IT_2': '#C6F068', 'L2/3 IT_3': '#97C928', 'L2/3 IT_3': '#B1EC30', 'L2/3 IT_3': '#BBEE4B', 'L2/3 IT_3': '#C1EF5C', 'L2/3 IT_3': '#C3EF60', 'L2/3 IT_4': '#7DA621', 'L2/3 IT_4': '#97C928', 'L2/3 IT_4': '#B4EC39', 'L2/3 IT_4': '#BDEE52', 'L2/3 IT_4': '#C0EF58', 'L2/3 IT_5': '#A9E22D', 'L2/3 IT_5': '#BAED48', 'L2/3 IT_5': '#BDEE50', 'L2/3 IT_6': '#9ACE29', 'L2/3 IT_6': '#B6ED3E', 'L2/3 IT_6': '#BAED48', 'L2/3 IT_7': '#8BBA25', 'L2/3 IT_7': '#B2EC34', 'L2/3 IT_7': '#B7ED40', 'L2/3 IT_8': '#ACE62E', 'L2/3 IT_8': '#B1EC30', 'L2/3 IT_9': '#A4DB2C', 'L2/3 IT_9': '#AAE32E', 'L4 IT_1': '#4FEDED', 'L4 IT_1': '#54E8E4', 'L4 IT_2': '#00A1A1', 'L4 IT_2': '#00E5E5', 'L4 IT_2': '#1AE7E7', 'L4 IT_2': '#2FE9E9', 'L4 IT_3': '#00A1A1', 'L4 IT_3': '#00CECE', 'L4 IT_3': '#0FE6E6', 'L4 IT_3': '#54E8E4', 'L4 IT_4': '#00A1A1', 'L4 IT_4': '#00D7D7', 'L4 IT_4': '#54E8E4', 'L4 IT_5': '#00BCBC', 'L4 IT_5': '#54E8E4', 'L4 IT_6': '#00A1A1', 'L5 ET_1': '#588EA2', 'L5 ET_2': '#094054', 'L5 ET_2': '#0D5B78', 'L5 ET_2': '#32748D', 'L5 ET_3': '#0B4D66', 'L5 ET_4': '#094054', 'L5 IT_1': '#86CAC6', 'L5 IT_2': '#50B2AD', 'L5 IT_2': '#62BAB5', 'L5 IT_2': '#67BCB7', 'L5 IT_2': '#6BBEB9', 'L5 IT_3': '#387D7A', 'L5 IT_3': '#48A09C', 'L5 IT_3': '#50B2AD', 'L5 IT_3': '#57B5B0', 'L5 IT_4': '#387D7A', 'L5 IT_4': '#449793', 'L5 IT_4': '#4CAAA5', 'L5 IT_5': '#459B97', 'L5 IT_6': '#3E8C88', 'L5 IT_7': '#387D7A', 'L5/6 NP_1': '#3E9E64', 'L5/6 NP_1': '#68B386', 'L5/6 NP_1': '#7ABC94', 'L5/6 NP_2': '#2B6F46', 'L5/6 NP_2': '#57AA78', 'L5/6 NP_2': '#5CAD7C', 'L5/6 NP_2': '#6CB589', 'L5/6 NP_3': '#3B975F', 'L5/6 NP_3': '#3E9E64', 'L5/6 NP_3': '#5FAE7E', 'L5/6 NP_4': '#348655', 'L5/6 NP_4': '#358957', 'L5/6 NP_4': '#44A169', 'L5/6 NP_5': '#307C4E', 'L5/6 NP_5': '#3B9860', 'L5/6 NP_6': '#2B6F46', 'L5/6 NP_6': '#378E5A', 'L5/6 NP_7': '#338353', 'L5/6 NP_8': '#2B6F46', 'L6 CT_1': '#4298BF', 'L6 CT_1': '#6EB0CE', 'L6 CT_2': '#1F6282', 'L6 CT_2': '#287EA6', 'L6 CT_2': '#2D8CB8', 'L6 CT_2': '#4D9EC3', 'L6 CT_3': '#1F6282', 'L6 CT_3': '#26779D', 'L6 CT_3': '#2D8CB8', 'L6 CT_4': '#1F6282', 'L6 CT_4': '#26779D', 'L6 IT Car3_1': '#874FFF', 'L6 IT Car3_2': '#3900B4', 'L6 IT Car3_2': '#5100FF', 'L6 IT Car3_2': '#631AFF', 'L6 IT Car3_3': '#3900B4', 'L6 IT Car3_3': '#4900E6', 'L6 IT_1': '#716C18', 'L6 IT_1': '#AFA844', 'L6 IT_1': '#BEB867', 'L6 IT_2': '#716C18', 'L6 IT_2': '#A19922', 'L6 IT_2': '#AAA338', 'L6 IT_3': '#716C18', 'L6 IT_3': '#89821D', 'L6 IT_3': '#918A1E', 'L6 IT_4': '#716C18', 'L6b_1': '#9C7EC4', 'L6b_2': '#7044AA', 'L6b_2': '#764CAD', 'L6b_2': '#7E57B2', 'L6b_2': '#8A66B9', 'L6b_3': '#4F3078', 'L6b_3': '#653D99', 'L6b_3': '#6B41A2', 'L6b_3': '#784FAF', 'L6b_4': '#4F3078', 'L6b_4': '#613B94', 'L6b_4': '#6940A0', 'L6b_5': '#583586', 'L6b_5': '#5C388B', 'L6b_6': '#4F3078', 'Lamp5_1': '#E5A7B0', 'Lamp5_2': '#9A5A62', 'Lamp5_2': '#DA808C', 'Lamp5_2': '#DD8D98', 'Lamp5_2': '#E097A1', 'Lamp5_3': '#9A5A62', 'Lamp5_3': '#C4737E', 'Lamp5_3': '#DC8793', 'Lamp5_4': '#9A5A62', 'Lamp5_4': '#CD7883', 'Lamp5_5': '#B36972', 'Lamp5_6': '#9A5A62', 'Lamp5_Lhx6_1': '#B49186', 'Lamp5_Lhx6_2': '#674338', 'Micro-PVM_1': '#8BA48E', 'Micro-PVM_1': '#B5C8B7', 'Micro-PVM_2': '#687B6A', 'Micro-PVM_2': '#798F7C', 'Micro-PVM_2': '#859D88', 'Micro-PVM_2': '#94AF97', 'Micro-PVM_2': '#9FB7A1', 'Micro-PVM_3': '#687B6A', 'Micro-PVM_3': '#859D88', 'Micro-PVM_4': '#687B6A', 'OPC_1': '#75827F', 'OPC_2': '#263430', 'OPC_2': '#374A45', 'OPC_2': '#4B5C58', 'OPC_3': '#263430', 'OPC_3': '#31423E', 'OPC_4': '#263430', 'Oligo_1': '#88A19A', 'Oligo_2': '#3A544C', 'Oligo_2': '#53776C', 'Oligo_2': '#64857B', 'Oligo_3': '#4A6B61', 'Oligo_4': '#3A544C', 'Pax6_1': '#9D67B0', 'Pax6_2': '#71238C', 'Pax6_2': '#7F3998', 'Pax6_3': '#4F1862', 'Pax6_3': '#651F7E', 'Pax6_4': '#4F1862', 'Pvalb_1': '#DD4C51', 'Pvalb_1': '#E47175', 'Pvalb_10': '#992226', 'Pvalb_10': '#CC2E33', 'Pvalb_11': '#C32C31', 'Pvalb_12': '#BB2A2F', 'Pvalb_13': '#B2282C', 'Pvalb_14': '#AA262A', 'Pvalb_15': '#992226', 'Pvalb_2': '#DA3A3F', 'Pvalb_2': '#E16165', 'Pvalb_2': '#E16267', 'Pvalb_2': '#E2686C', 'Pvalb_3': '#CF2E34', 'Pvalb_3': '#DE5156', 'Pvalb_3': '#DF5459', 'Pvalb_3': '#E15F64', 'Pvalb_4': '#BD2A2F', 'Pvalb_4': '#D93137', 'Pvalb_4': '#DC464B', 'Pvalb_4': '#DF575C', 'Pvalb_5': '#AB262A', 'Pvalb_5': '#C92D32', 'Pvalb_5': '#D12F35', 'Pvalb_5': '#DA383D', 'Pvalb_5': '#DE4E53', 'Pvalb_6': '#992226', 'Pvalb_6': '#B9292E', 'Pvalb_6': '#C32C31', 'Pvalb_6': '#D12F35', 'Pvalb_6': '#DC464B', 'Pvalb_7': '#A9252A', 'Pvalb_7': '#B5282D', 'Pvalb_7': '#C32C31', 'Pvalb_7': '#DB3D43', 'Pvalb_8': '#992226', 'Pvalb_8': '#A72529', 'Pvalb_8': '#B5282D', 'Pvalb_8': '#D9353B', 'Pvalb_9': '#992226', 'Pvalb_9': '#A72529', 'Pvalb_9': '#D43035', 'Sncg_1': '#E99CFF', 'Sncg_10': '#9D4FB4', 'Sncg_2': '#E58DFF', 'Sncg_2': '#E691FF', 'Sncg_2': '#E692FF', 'Sncg_3': '#E27EFF', 'Sncg_3': '#E386FF', 'Sncg_3': '#E488FF', 'Sncg_4': '#DF70FF', 'Sncg_4': '#E17BFF', 'Sncg_4': '#E27EFF', 'Sncg_5': '#C965E6', 'Sncg_5': '#DF70FF', 'Sncg_5': '#E074FF', 'Sncg_6': '#B35ACD', 'Sncg_6': '#CE67EC', 'Sncg_6': '#D76CF6', 'Sncg_7': '#9D4FB4', 'Sncg_7': '#BE5FD9', 'Sncg_7': '#C965E6', 'Sncg_8': '#9D4FB4', 'Sncg_8': '#AD57C6', 'Sncg_8': '#BA5DD5', 'Sncg_9': '#9D4FB4', 'Sncg_9': '#AB56C4', 'Sst Chodl_1': '#C9C958', 'Sst Chodl_2': '#7D7D08', 'Sst Chodl_2': '#B1B10C', 'Sst Chodl_3': '#7D7D08', 'Sst_1': '#FFB446', 'Sst_1': '#FFB84F', 'Sst_10': '#E28700', 'Sst_10': '#F09000', 'Sst_10': '#F69300', 'Sst_10': '#FA9600', 'Sst_10': '#FFA012', 'Sst_11': '#D68000', 'Sst_11': '#E68A00', 'Sst_11': '#EE8F00', 'Sst_11': '#F19100', 'Sst_11': '#FF9D0C', 'Sst_12': '#CB7900', 'Sst_12': '#DC8400', 'Sst_12': '#E68A00', 'Sst_12': '#E88B00', 'Sst_12': '#FF9B06', 'Sst_13': '#BF7200', 'Sst_13': '#C87800', 'Sst_13': '#DD8500', 'Sst_13': '#E08600', 'Sst_13': '#FF9900', 'Sst_14': '#B46C00', 'Sst_14': '#BE7100', 'Sst_14': '#D58000', 'Sst_14': '#D78100', 'Sst_14': '#F99500', 'Sst_15': '#B46C00', 'Sst_15': '#BC7100', 'Sst_15': '#CD7B00', 'Sst_15': '#F39200', 'Sst_16': '#B46C00', 'Sst_16': '#C47600', 'Sst_16': '#ED8E00', 'Sst_17': '#BC7100', 'Sst_17': '#E78B00', 'Sst_18': '#B46C00', 'Sst_18': '#E28700', 'Sst_19': '#DC8400', 'Sst_2': '#FFB13D', 'Sst_2': '#FFB342', 'Sst_2': '#FFB344', 'Sst_2': '#FFB445', 'Sst_20': '#D68000', 'Sst_21': '#D07D00', 'Sst_22': '#CB7900', 'Sst_23': '#C57600', 'Sst_24': '#BF7200', 'Sst_25': '#B96F00', 'Sst_26': '#B46C00', 'Sst_3': '#FFAD34', 'Sst_3': '#FFAE36', 'Sst_3': '#FFAF39', 'Sst_3': '#FFB03C', 'Sst_4': '#FFA92A', 'Sst_4': '#FFAA2B', 'Sst_4': '#FFAB2F', 'Sst_4': '#FFAD33', 'Sst_4': '#FFAE36', 'Sst_5': '#FFA41E', 'Sst_5': '#FFA623', 'Sst_5': '#FFA724', 'Sst_5': '#FFA929', 'Sst_5': '#FFAC30', 'Sst_6': '#FFA012', 'Sst_6': '#FFA31A', 'Sst_6': '#FFA520', 'Sst_6': '#FFA92A', 'Sst_7': '#FF9B06', 'Sst_7': '#FF9F0F', 'Sst_7': '#FF9F11', 'Sst_7': '#FFA217', 'Sst_7': '#FFA724', 'Sst_8': '#F99500', 'Sst_8': '#FF9B05', 'Sst_8': '#FF9C08', 'Sst_8': '#FF9E0D', 'Sst_8': '#FFA41E', 'Sst_9': '#ED8E00', 'Sst_9': '#FA9600', 'Sst_9': '#FF9900', 'Sst_9': '#FF9A04', 'Sst_9': '#FFA218', 'VLMC_1': '#697255', 'VLMC_1': '#848C74', 'VLMC_1': '#979E8A', 'VLMC_2': '#4A503C', 'VLMC_2': '#626B50', 'VLMC_2': '#788066', 'VLMC_3': '#565D45', 'VLMC_3': '#5E664C', 'VLMC_4': '#4A503C', 'Vip_1': '#C091D3', 'Vip_10': '#8B51A3', 'Vip_10': '#9657AF', 'Vip_10': '#9D5BB8', 'Vip_10': '#A561C0', 'Vip_10': '#A968C2', 'Vip_11': '#834C99', 'Vip_11': '#8F53A7', 'Vip_11': '#9758B1', 'Vip_11': '#A15DBC', 'Vip_11': '#A663C0', 'Vip_12': '#7B4790', 'Vip_12': '#884F9F', 'Vip_12': '#9154AA', 'Vip_12': '#9C5AB6', 'Vip_12': '#A45FBF', 'Vip_13': '#734387', 'Vip_13': '#814B97', 'Vip_13': '#8B51A3', 'Vip_13': '#9757B0', 'Vip_13': '#9F5CB9', 'Vip_14': '#7A478F', 'Vip_14': '#854D9C', 'Vip_14': '#9154AA', 'Vip_14': '#9B59B4', 'Vip_15': '#734387', 'Vip_15': '#7F4A95', 'Vip_15': '#8C51A4', 'Vip_15': '#9657AF', 'Vip_16': '#79468E', 'Vip_16': '#874E9E', 'Vip_16': '#9254AA', 'Vip_17': '#734387', 'Vip_17': '#824B98', 'Vip_17': '#8D52A5', 'Vip_18': '#7D4892', 'Vip_18': '#894FA0', 'Vip_19': '#78458C', 'Vip_19': '#844D9B', 'Vip_2': '#BB88CF', 'Vip_2': '#BC89D0', 'Vip_2': '#BC8AD0', 'Vip_2': '#BD8BD0', 'Vip_2': '#BD8CD1', 'Vip_20': '#734387', 'Vip_20': '#804A96', 'Vip_21': '#7B4891', 'Vip_22': '#77458C', 'Vip_23': '#734387', 'Vip_3': '#B680CC', 'Vip_3': '#B882CD', 'Vip_3': '#B984CE', 'Vip_3': '#BA86CE', 'Vip_3': '#BA87CF', 'Vip_4': '#B278C9', 'Vip_4': '#B47BCA', 'Vip_4': '#B57ECB', 'Vip_4': '#B781CC', 'Vip_4': '#B883CD', 'Vip_5': '#AD6FC5', 'Vip_5': '#B074C7', 'Vip_5': '#B278C9', 'Vip_5': '#B47BCA', 'Vip_5': '#B57ECB', 'Vip_6': '#A867C2', 'Vip_6': '#AC6DC4', 'Vip_6': '#AE71C6', 'Vip_6': '#B176C8', 'Vip_6': '#B37AC9', 'Vip_7': '#A45FBF', 'Vip_7': '#A866C1', 'Vip_7': '#AB6BC3', 'Vip_7': '#AE71C6', 'Vip_7': '#B075C8', 'Vip_8': '#9B5AB5', 'Vip_8': '#A45FBF', 'Vip_8': '#A765C1', 'Vip_8': '#AB6CC4', 'Vip_8': '#AE71C6', 'Vip_9': '#9355AC', 'Vip_9': '#9D5BB7', 'Vip_9': '#A45FBF', 'Vip_9': '#A866C2', 'Vip_9': '#AB6CC4',};

const mapDataforBorderChimp = { 'Astro_1': 'Astro_1', 'Astro_2': 'Astro_1', 'Chandelier_1': 'Chandelier_1', 'Chandelier_2': 'Chandelier_1', 'Endo_1': 'Endo_1', 'L2/3 IT_1': 'L2/3 IT_1', 'L2/3 IT_2': 'L2/3 IT_3', 'L2/3 IT_3': 'L2/3 IT_1', 'L2/3 IT_4': 'L2/3 IT_3', 'L2/3 IT_5': 'L2/3 IT_1', 'L2/3 IT_6': 'L2/3 IT_1', 'L2/3 IT_7': 'L2/3 IT_1', 'L4 IT_1': 'L4 IT_1', 'L4 IT_2': 'L4 IT_1', 'L4 IT_3': 'L4 IT_2', 'L4 IT_4': 'L2/3 IT_2', 'L5/6 NP_1': 'L5/6 NP_2', 'L5/6 NP_2': 'L5/6 NP_1', 'L5 ET_1': 'L5 ET_1', 'L5 ET_2': 'L5 ET_2', 'L5 IT_1': 'L5 IT_1', 'L5 IT_2': 'L5 IT_1', 'L5 IT_3': 'L5 IT_2', 'L5 IT_4': 'L5 IT_2', 'L6 CT_1': 'L6 CT_1', 'L6 CT_2': 'L6 CT_2', 'L6 CT_3': 'L6 CT_2', 'L6 IT Car3_1': 'L6 IT Car3_2', 'L6 IT Car3_2': 'L6 IT Car3_1', 'L6 IT_1': 'L6 IT_1', 'L6b_1': 'L6b_3', 'L6b_2': 'L6b_1', 'L6b_3': 'L6b_2', 'L6b_4': 'L6b_2', 'L6b_5': 'L6b_2', 'L6b_6': 'L6b_2', 'Lamp5_1': 'Lamp5_2', 'Lamp5_2': 'Lamp5_1', 'Lamp5_3': 'Lamp5_1', 'Lamp5_Lhx6_1': 'Lamp5_Lhx6_1', 'Lamp5_Lhx6_2': 'Lamp5_Lhx6_1', 'Micro-PVM_1': 'Micro-PVM_1', 'Micro-PVM_2': 'Micro-PVM_1', 'OPC_1': 'OPC_1', 'OPC_2': 'OPC_2', 'Oligo_1': 'Oligo_1', 'Oligo_2': 'Oligo_1', 'Pax6_1': 'Pax6_1', 'Pax6_2': 'Pax6_1', 'Pax6_3': 'Pax6_2', 'Pax6_4': 'Sncg_3', 'Pvalb_1': 'Pvalb_2', 'Pvalb_2': 'Pvalb_4', 'Pvalb_3': 'Pvalb_1', 'Pvalb_4': 'Pvalb_3', 'Pvalb_5': 'Pvalb_4', 'Pvalb_6': 'Pvalb_4', 'Pvalb_7': 'Pvalb_4', 'Pvalb_8': 'Pvalb_4', 'Pvalb_9': 'Sst_5', 'Sncg_1': 'Lamp5_2', 'Sncg_10': 'Vip_8', 'Sncg_2': 'Sncg_2', 'Sncg_3': 'Sncg_3', 'Sncg_4': 'Sncg_3', 'Sncg_5': 'Sncg_1', 'Sncg_6': 'Sncg_2', 'Sncg_7': 'Vip_8', 'Sncg_8': 'Sncg_2', 'Sncg_9': 'Sncg_2', 'Sst Chodl_1': 'Sst Chodl_1', 'Sst_1': 'Sst_5', 'Sst_10': 'Sst_2', 'Sst_11': 'Sst_8', 'Sst_12': 'Sst_8', 'Sst_13': 'Sst_5', 'Sst_14': 'Sst_4', 'Sst_15': 'Sst_3', 'Sst_2': 'Sst_9', 'Sst_3': 'Sst_3', 'Sst_4': 'Sst_3', 'Sst_5': 'Sst_7', 'Sst_6': 'Sst_6', 'Sst_7': 'Sst_7', 'Sst_8': 'Sst_5', 'Sst_9': 'Sst_1', 'VLMC_1': 'VLMC_1', 'Vip_1': 'Vip_8', 'Vip_10': 'Vip_2', 'Vip_11': 'Vip_2', 'Vip_12': 'Vip_8', 'Vip_13': 'Vip_2', 'Vip_14': 'Vip_2', 'Vip_15': 'Vip_8', 'Vip_16': 'Vip_8', 'Vip_17': 'Vip_8', 'Vip_18': 'Vip_7', 'Vip_19': 'Vip_6', 'Vip_2': 'Vip_5', 'Vip_20': 'Vip_7', 'Vip_3': 'Vip_5', 'Vip_4': 'Vip_7', 'Vip_5': 'Vip_1', 'Vip_6': 'Vip_3', 'Vip_7': 'Vip_3', 'Vip_8': 'Vip_3', 'Vip_9': 'Vip_4'  };
const mapDataforBorderGorilla = { 'Astro_1': 'Astro_1', 'Astro_2': 'Astro_1', 'Astro_3': 'Astro_1', 'Astro_4': 'Astro_1', 'Chandelier_1': 'Chandelier_1', 'Chandelier_2': 'Chandelier_1', 'Endo_1': 'Endo_1', 'Endo_2': 'Endo_1', 'L2/3 IT_1': 'L2/3 IT_3', 'L2/3 IT_2': 'L2/3 IT_1', 'L2/3 IT_3': 'L2/3 IT_1', 'L2/3 IT_4': 'L2/3 IT_1', 'L4 IT_1': 'L4 IT_2', 'L4 IT_2': 'L2/3 IT_2', 'L4 IT_3': 'L4 IT_1', 'L4 IT_4': 'L4 IT_1', 'L4 IT_5': 'L2/3 IT_2', 'L5/6 NP_1': 'L5/6 NP_2', 'L5/6 NP_2': 'L5/6 NP_1', 'L5/6 NP_3': 'L5/6 NP_1', 'L5/6 NP_4': 'L5/6 NP_1', 'L5 ET_1': 'L5 ET_1', 'L5 ET_2': 'L5 ET_1', 'L5 ET_3': 'L5 ET_2', 'L5 ET_4': 'L5 ET_2', 'L5 IT_1': 'L5 IT_2', 'L5 IT_2': 'L5 IT_2', 'L5 IT_3': 'L5 IT_1', 'L6 CT_1': 'L6 CT_1', 'L6 CT_2': 'L6 CT_2', 'L6 IT Car3_1': 'L6 IT Car3_2', 'L6 IT Car3_2': 'L6 IT Car3_1', 'L6 IT Car3_3': 'L6 IT Car3_2', 'L6 IT_1': 'L6 IT_1', 'L6 IT_2': 'L6 IT_1', 'L6 IT_3': 'L6 IT_1', 'L6b_1': 'L6b_1', 'L6b_2': 'L6b_2', 'L6b_3': 'L6b_3', 'L6b_4': 'L6b_1', 'L6b_5': 'L6b_2', 'L6b_6': 'L6b_2', 'Lamp5_1': 'Lamp5_2', 'Lamp5_2': 'Lamp5_1', 'Lamp5_Lhx6_1': 'Lamp5_Lhx6_1', 'Lamp5_Lhx6_2': 'Lamp5_Lhx6_1', 'Micro-PVM_1': 'Micro-PVM_1', 'Micro-PVM_2': 'Micro-PVM_1', 'Micro-PVM_3': 'Micro-PVM_1', 'OPC_1': 'OPC_2', 'OPC_2': 'OPC_1', 'OPC_3': 'OPC_2', 'Oligo_1': 'Oligo_1', 'Pax6_1': 'Sncg_3', 'Pax6_2': 'Pax6_2', 'Pax6_3': 'Pax6_1', 'Pax6_4': 'Pax6_1', 'Pvalb_1': 'Pvalb_2', 'Pvalb_2': 'Pvalb_1', 'Pvalb_3': 'Pvalb_3', 'Pvalb_4': 'Pvalb_4', 'Pvalb_5': 'Pvalb_4', 'Pvalb_6': 'Pvalb_4', 'Pvalb_7': 'Pvalb_4', 'Pvalb_8': 'Sst_5', 'Sncg_1': 'Sncg_3', 'Sncg_2': 'Sncg_2', 'Sncg_3': 'Sncg_2', 'Sncg_4': 'Sncg_1', 'Sncg_5': 'Vip_8', 'Sncg_6': 'Sncg_1', 'Sncg_7': 'Vip_8', 'Sst Chodl_1': 'Sst Chodl_1', 'Sst Chodl_2': 'Sst Chodl_1', 'Sst Chodl_3': 'Sst_6', 'Sst_1': 'Sst_8', 'Sst_10': 'Sst_3', 'Sst_11': 'Sst_7', 'Sst_12': 'Sst_4', 'Sst_13': 'Sst_5', 'Sst_14': 'Sst_7', 'Sst_15': 'Sst_7', 'Sst_16': 'Sst_6', 'Sst_17': 'Sst_6', 'Sst_18': 'Sst_9', 'Sst_2': 'Sst_8', 'Sst_3': 'Sst_8', 'Sst_4': 'Sst_1', 'Sst_5': 'Sst_2', 'Sst_6': 'Sst_2', 'Sst_7': 'Sst_3', 'Sst_8': 'Sst_5', 'Sst_9': 'Sst_5', 'VLMC_1': 'VLMC_1', 'VLMC_2': 'VLMC_1', 'VLMC_3': 'VLMC_1', 'VLMC_4': 'VLMC_1', 'Vip_1': 'Vip_5', 'Vip_10': 'Vip_7', 'Vip_11': 'Vip_6', 'Vip_12': 'Vip_7', 'Vip_13': 'Vip_7', 'Vip_14': 'Vip_1', 'Vip_15': 'Vip_4', 'Vip_16': 'Vip_3', 'Vip_17': 'Vip_2', 'Vip_2': 'Vip_2', 'Vip_3': 'Vip_2', 'Vip_4': 'Vip_3', 'Vip_5': 'Vip_3', 'Vip_6': 'Vip_3', 'Vip_7': 'Vip_8', 'Vip_8': 'Vip_8', 'Vip_9': 'Vip_8' };
const mapDataforBorderHuman = { 'Astro_1': 'Astro_1', 'Astro_2': 'Astro_1', 'Astro_3': 'Astro_1', 'Astro_4': 'Astro_1', 'Astro_5': 'Astro_1', 'Chandelier_1': 'Chandelier_1', 'Chandelier_2': 'Chandelier_1', 'Endo_1': 'Endo_1', 'L2/3 IT_1': 'L2/3 IT_1', 'L2/3 IT_10': 'L2/3 IT_3', 'L2/3 IT_11': 'L2/3 IT_1', 'L2/3 IT_12': 'L2/3 IT_1', 'L2/3 IT_13': 'L2/3 IT_1', 'L2/3 IT_2': 'L2/3 IT_1', 'L2/3 IT_3': 'L2/3 IT_1', 'L2/3 IT_4': 'L2/3 IT_1', 'L2/3 IT_5': 'L2/3 IT_1', 'L2/3 IT_6': 'L2/3 IT_3', 'L2/3 IT_7': 'L2/3 IT_3', 'L2/3 IT_8': 'L2/3 IT_3', 'L2/3 IT_9': 'L2/3 IT_3', 'L4 IT_1': 'L4 IT_2', 'L4 IT_2': 'L4 IT_1', 'L4 IT_3': 'L4 IT_1', 'L4 IT_4': 'L2/3 IT_2', 'L5/6 NP_1': 'L5/6 NP_1', 'L5/6 NP_2': 'L5/6 NP_2', 'L5/6 NP_3': 'L5/6 NP_1', 'L5/6 NP_4': 'L5/6 NP_1', 'L5/6 NP_5': 'L5/6 NP_1', 'L5/6 NP_6': 'L5/6 NP_1', 'L5 ET_1': 'L5 ET_1', 'L5 ET_2': 'L5 ET_2', 'L5 IT_1': 'L5 IT_1', 'L5 IT_2': 'L5 IT_2', 'L5 IT_3': 'L5 IT_1', 'L5 IT_4': 'L5 IT_2', 'L5 IT_5': 'L5 IT_2', 'L5 IT_6': 'L5 IT_2', 'L5 IT_7': 'L5 IT_2', 'L6 CT_1': 'L6 CT_1', 'L6 CT_2': 'L6 CT_1', 'L6 CT_3': 'L6 CT_2', 'L6 CT_4': 'L6 CT_2', 'L6 IT Car3_1': 'L6 IT Car3_1', 'L6 IT Car3_2': 'L6 IT Car3_2', 'L6 IT Car3_3': 'L6 IT Car3_2', 'L6 IT_1': 'L6 IT_1', 'L6 IT_2': 'L6 IT_1', 'L6b_1': 'L6b_3', 'L6b_2': 'L6b_1', 'L6b_3': 'L6b_2', 'L6b_4': 'L6b_2', 'L6b_5': 'L6b_2', 'L6b_6': 'L6b_2', 'Lamp5_1': 'Lamp5_1', 'Lamp5_2': 'Lamp5_1', 'Lamp5_3': 'Lamp5_1', 'Lamp5_4': 'Lamp5_2', 'Lamp5_5': 'Lamp5_2', 'Lamp5_6': 'Lamp5_2', 'Lamp5_Lhx6_1': 'Lamp5_Lhx6_1', 'Micro-PVM_1': 'Micro-PVM_1', 'Micro-PVM_2': 'Micro-PVM_1', 'Micro-PVM_3': 'Micro-PVM_1', 'OPC_1': 'OPC_1', 'OPC_2': 'OPC_2', 'Oligo_1': 'Oligo_1', 'Oligo_2': 'Oligo_1', 'Oligo_3': 'Oligo_1', 'Oligo_4': 'Oligo_1', 'Pax6_1': 'Pax6_1', 'Pax6_2': 'Pax6_1', 'Pax6_3': 'Pax6_2', 'Pax6_4': 'Sncg_3', 'Pvalb_1': 'Pvalb_4', 'Pvalb_10': 'Pvalb_3', 'Pvalb_11': 'Pvalb_3', 'Pvalb_12': 'Pvalb_3', 'Pvalb_13': 'Pvalb_3', 'Pvalb_14': 'Pvalb_4', 'Pvalb_15': 'Pvalb_4', 'Pvalb_2': 'Pvalb_4', 'Pvalb_3': 'Pvalb_4', 'Pvalb_4': 'Pvalb_4', 'Pvalb_5': 'Pvalb_4', 'Pvalb_6': 'Pvalb_4', 'Pvalb_7': 'Pvalb_1', 'Pvalb_8': 'Sst_5', 'Pvalb_9': 'Pvalb_2', 'Sncg_1': 'Vip_8', 'Sncg_2': 'Vip_8', 'Sncg_3': 'Sncg_1', 'Sncg_4': 'Sncg_2', 'Sncg_5': 'Sncg_2', 'Sncg_6': 'Sncg_3', 'Sncg_7': 'Sncg_2', 'Sncg_8': 'Vip_8', 'Sst Chodl_1': 'Sst Chodl_1', 'Sst Chodl_2': 'Sst_6', 'Sst_1': 'Sst_1', 'Sst_10': 'Sst_3', 'Sst_11': 'Sst_6', 'Sst_12': 'Sst_2', 'Sst_13': 'Sst_3', 'Sst_14': 'Sst_3', 'Sst_15': 'Sst_2', 'Sst_16': 'Sst_4', 'Sst_17': 'Sst_4', 'Sst_18': 'Sst_3', 'Sst_19': 'Sst_4', 'Sst_2': 'Sst_5', 'Sst_20': 'Sst_5', 'Sst_21': 'Sst_5', 'Sst_22': 'Sst_6', 'Sst_23': 'Sst_7', 'Sst_24': 'Sst_7', 'Sst_25': 'Sst_7', 'Sst_26': 'Sst_7', 'Sst_3': 'Sst_5', 'Sst_4': 'Sst_8', 'Sst_5': 'Sst_8', 'Sst_6': 'Sst_8', 'Sst_7': 'Sst_8', 'Sst_8': 'Sst_3', 'Sst_9': 'Sst_9', 'VLMC_1': 'VLMC_1', 'VLMC_2': 'VLMC_1', 'Vip_1': 'Vip_1', 'Vip_10': 'Vip_7', 'Vip_11': 'Vip_1', 'Vip_12': 'Vip_2', 'Vip_13': 'Vip_1', 'Vip_14': 'Vip_8', 'Vip_15': 'Vip_8', 'Vip_16': 'Vip_8', 'Vip_17': 'Vip_2', 'Vip_18': 'Vip_2', 'Vip_19': 'Vip_2', 'Vip_2': 'Vip_3', 'Vip_20': 'Vip_2', 'Vip_21': 'Vip_4', 'Vip_22': 'Vip_4', 'Vip_23': 'Vip_3', 'Vip_3': 'Vip_3', 'Vip_4': 'Vip_5', 'Vip_5': 'Vip_6', 'Vip_6': 'Vip_7', 'Vip_7': 'Vip_5', 'Vip_8': 'Vip_7', 'Vip_9': 'Vip_7' };
const mapDataforBorderMarmoset = { 'Astro_1': 'Astro_1', 'Astro_2': 'Astro_1', 'Astro_3': 'Astro_1', 'Astro_4': 'Astro_1', 'Chandelier_1': 'Chandelier_1', 'Endo_1': 'Endo_1', 'Endo_2': 'Endo_1', 'Endo_3': 'Endo_1', 'L2/3 IT_1': 'L2/3 IT_3', 'L2/3 IT_2': 'L2/3 IT_1', 'L2/3 IT_3': 'L2/3 IT_1', 'L2/3 IT_4': 'L2/3 IT_1', 'L4 IT_1': 'L2/3 IT_2', 'L4 IT_2': 'L2/3 IT_2', 'L4 IT_3': 'L2/3 IT_1', 'L4 IT_4': 'L4 IT_2', 'L4 IT_5': 'L2/3 IT_2', 'L4 IT_6': 'L4 IT_1', 'L5/6 NP_1': 'L5/6 NP_1', 'L5/6 NP_2': 'L5/6 NP_2', 'L5 ET_1': 'L5 ET_1', 'L5 ET_2': 'L5 ET_2', 'L5 IT_1': 'L5 IT_2', 'L5 IT_2': 'L5 IT_2', 'L5 IT_3': 'L5 IT_1', 'L6 CT_1': 'L6 CT_2', 'L6 CT_2': 'L6 CT_1', 'L6 CT_3': 'L6 CT_2', 'L6 IT Car3_1': 'L6 IT Car3_2', 'L6 IT Car3_2': 'L6 IT Car3_2', 'L6 IT Car3_3': 'L6 IT Car3_1', 'L6 IT_1': 'L6 IT_1', 'L6 IT_2': 'L6 IT_1', 'L6 IT_3': 'L6 IT_1', 'L6b_1': 'L6b_2', 'L6b_2': 'L6b_3', 'L6b_3': 'L6b_1', 'Lamp5_1': 'Lamp5_2', 'Lamp5_2': 'Lamp5_1', 'Lamp5_Lhx6_1': 'Lamp5_Lhx6_1', 'Micro-PVM_1': 'Micro-PVM_1', 'Micro-PVM_2': 'Micro-PVM_1', 'Micro-PVM_3': 'Micro-PVM_1', 'Micro-PVM_4': 'Micro-PVM_1', 'OPC_1': 'OPC_1', 'OPC_2': 'OPC_2', 'OPC_3': 'OPC_2', 'OPC_4': 'OPC_2', 'Oligo_1': 'Oligo_1', 'Oligo_2': 'Oligo_1', 'Pax6_1': 'Pax6_1', 'Pax6_2': 'Pax6_1', 'Pax6_3': 'Sncg_3', 'Pvalb_1': 'Pvalb_3', 'Pvalb_2': 'Pvalb_4', 'Pvalb_3': 'Pvalb_4', 'Pvalb_4': 'Pvalb_4', 'Pvalb_5': 'Pvalb_1', 'Pvalb_6': 'Pvalb_2', 'Sncg_1': 'Pax6_2', 'Sncg_2': 'Vip_8', 'Sncg_3': 'Sncg_2', 'Sncg_4': 'Sncg_3', 'Sncg_5': 'Pax6_2', 'Sncg_6': 'Sncg_3', 'Sncg_7': 'Sncg_1', 'Sncg_8': 'Sncg_1', 'Sncg_9': 'Vip_8', 'Sst Chodl_1': 'Sst Chodl_1', 'Sst Chodl_2': 'Sst_6', 'Sst_1': 'Sst_7', 'Sst_10': 'Sst_8', 'Sst_11': 'Sst_8', 'Sst_12': 'Sst_7', 'Sst_13': 'Sst_6', 'Sst_14': 'Sst_5', 'Sst_15': 'Sst_7', 'Sst_16': 'Sst_5', 'Sst_2': 'Sst_4', 'Sst_3': 'Sst_9', 'Sst_4': 'Sst_3', 'Sst_5': 'Sst_9', 'Sst_6': 'Sst_3', 'Sst_7': 'Sst_1', 'Sst_8': 'Sst_2', 'Sst_9': 'Sst_2', 'VLMC_1': 'VLMC_1', 'VLMC_2': 'VLMC_1', 'VLMC_3': 'VLMC_1', 'VLMC_4': 'VLMC_1', 'Vip_1': 'Vip_6', 'Vip_10': 'Vip_3', 'Vip_11': 'Vip_7', 'Vip_12': 'Vip_7', 'Vip_13': 'Vip_1', 'Vip_2': 'Vip_4', 'Vip_3': 'Vip_5', 'Vip_4': 'Vip_8', 'Vip_5': 'Vip_8', 'Vip_6': 'Vip_2', 'Vip_7': 'Vip_2', 'Vip_8': 'Vip_2', 'Vip_9': 'Vip_2' };
const mapDataforBorderRhesus = { 'Astro_1': 'Astro_1', 'Astro_2': 'Astro_1', 'Astro_3': 'Astro_1', 'Chandelier_1': 'Chandelier_1', 'Chandelier_2': 'Chandelier_1', 'Endo_1': 'Endo_1', 'L2/3 IT_1': 'L2/3 IT_1', 'L2/3 IT_10': 'L2/3 IT_3', 'L2/3 IT_11': 'L2/3 IT_1', 'L2/3 IT_12': 'L2/3 IT_1', 'L2/3 IT_13': 'L2/3 IT_1', 'L2/3 IT_14': 'L2/3 IT_1', 'L2/3 IT_15': 'L2/3 IT_1', 'L2/3 IT_2': 'L2/3 IT_1', 'L2/3 IT_3': 'L2/3 IT_3', 'L2/3 IT_4': 'L2/3 IT_3', 'L2/3 IT_5': 'L2/3 IT_3', 'L2/3 IT_6': 'L2/3 IT_3', 'L2/3 IT_7': 'L2/3 IT_1', 'L2/3 IT_8': 'L2/3 IT_1', 'L2/3 IT_9': 'L2/3 IT_1', 'L4 IT_1': 'L4 IT_1', 'L4 IT_2': 'L4 IT_2', 'L4 IT_3': 'L2/3 IT_2', 'L5/6 NP_1': 'L5/6 NP_2', 'L5/6 NP_2': 'L5/6 NP_1', 'L5/6 NP_3': 'L5/6 NP_1', 'L5/6 NP_4': 'L5/6 NP_1', 'L5/6 NP_5': 'L5/6 NP_1', 'L5/6 NP_6': 'L5/6 NP_1', 'L5/6 NP_7': 'L5/6 NP_1', 'L5/6 NP_8': 'L5/6 NP_1', 'L5 ET_1': 'L5 ET_2', 'L5 ET_2': 'L5 ET_1', 'L5 IT_1': 'L5 IT_2', 'L5 IT_2': 'L5 IT_1', 'L5 IT_3': 'L5 IT_2', 'L5 IT_4': 'L5 IT_2', 'L6 CT_1': 'L6 CT_2', 'L6 CT_2': 'L6 CT_1', 'L6 CT_3': 'L6 CT_1', 'L6 CT_4': 'L6 CT_1', 'L6 IT Car3_1': 'L6 IT Car3_1', 'L6 IT Car3_2': 'L6 IT Car3_2', 'L6 IT_1': 'L6 IT_1', 'L6 IT_2': 'L6 IT_1', 'L6 IT_3': 'L6 IT_1', 'L6 IT_4': 'L6 IT_1', 'L6b_1': 'L6b_2', 'L6b_2': 'L6b_2', 'L6b_3': 'L6b_1', 'L6b_4': 'L6b_3', 'Lamp5_1': 'Lamp5_2', 'Lamp5_2': 'Lamp5_2', 'Lamp5_3': 'Lamp5_1', 'Lamp5_4': 'Lamp5_1', 'Lamp5_Lhx6_1': 'Lamp5_Lhx6_1', 'Micro-PVM_1': 'Micro-PVM_1', 'Micro-PVM_2': 'Micro-PVM_1', 'Micro-PVM_3': 'Micro-PVM_1', 'OPC_1': 'OPC_1', 'OPC_2': 'OPC_2', 'OPC_3': 'OPC_2', 'Oligo_1': 'Oligo_1', 'Oligo_2': 'Oligo_1', 'Pax6_1': 'Pax6_1', 'Pax6_2': 'Pax6_1', 'Pax6_3': 'Pax6_2', 'Pax6_4': 'Sncg_3', 'Pvalb_1': 'Pvalb_3', 'Pvalb_10': 'Pvalb_4', 'Pvalb_2': 'Pvalb_4', 'Pvalb_3': 'Pvalb_2', 'Pvalb_4': 'Pvalb_1', 'Pvalb_5': 'Pvalb_1', 'Pvalb_6': 'Pvalb_4', 'Pvalb_7': 'Pvalb_4', 'Pvalb_8': 'Pvalb_4', 'Pvalb_9': 'Pvalb_4', 'Sncg_1': 'Sncg_2', 'Sncg_2': 'Sncg_2', 'Sncg_3': 'Sncg_2', 'Sncg_4': 'Sncg_2', 'Sncg_5': 'Vip_8', 'Sncg_6': 'Vip_8', 'Sncg_7': 'Sncg_1', 'Sst Chodl_1': 'Sst Chodl_1', 'Sst Chodl_2': 'Sst_6', 'Sst_1': 'Sst_1', 'Sst_10': 'Sst_7', 'Sst_11': 'Sst_6', 'Sst_12': 'Sst_8', 'Sst_13': 'Sst_5', 'Sst_14': 'Sst_2', 'Sst_2': 'Sst_4', 'Sst_3': 'Sst_4', 'Sst_4': 'Sst_9', 'Sst_5': 'Sst_9', 'Sst_6': 'Sst_3', 'Sst_7': 'Sst_3', 'Sst_8': 'Sst_7', 'Sst_9': 'Sst_7', 'VLMC_1': 'VLMC_1', 'VLMC_2': 'VLMC_1', 'Vip_1': 'Vip_8', 'Vip_10': 'Vip_5', 'Vip_11': 'Vip_6', 'Vip_12': 'Vip_7', 'Vip_13': 'Vip_7', 'Vip_14': 'Vip_7', 'Vip_15': 'Vip_7', 'Vip_2': 'Vip_7', 'Vip_3': 'Vip_2', 'Vip_4': 'Vip_1', 'Vip_5': 'Vip_3', 'Vip_6': 'Vip_3', 'Vip_7': 'Vip_4', 'Vip_8': 'Vip_8', 'Vip_9': 'Vip_8'};

try {
    new QWebChannel(qt.webChannelTransport, function (channel) {
        QtBridge = channel.objects.QtBridge;
        QtBridge.qt_setData.connect(function () { setData(arguments[0]); });
        QtBridge.qt_setClusters.connect(function () { setClusters(arguments[0]); });
        notifyBridgeAvailable();
    });
} catch (error) {
    isQtAvailable = false;
    log("could not connect qt");
}


const simianVis = () => {
    log("Creating visualization");
    d3.select("g").remove();
    d3.select("svg").remove();
    var svg = d3.select("#my_dataviz")
    svg.selectAll("*").remove();
    var margin = { top: 35, right: 5, bottom: 80, left: 75 },
        width = window.innerWidth * 0.90 - margin.left - margin.right,
        height = window.innerHeight * 0.95 - margin.top - margin.bottom;
    // append the svg object to the body of the page
    svg = d3
        .select("#my_dataviz")
        .append("svg")
        .attr("width", width + margin.left + margin.right)
        .attr("height", height + margin.top + margin.bottom)
        .append("g")
        .attr("transform", "translate(" + margin.left + "," + (margin.top+15) + ")");

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

    // Build X scales and axis:
   var  x = d3.scaleBand().range([0, width]).domain(cluster_1_Groups).padding(0.05);

    svg
        .append("g")
        .style("font-size", 9)
        //.attr("font-weight", 500)
        .attr("transform", "translate(0," + height + ")")
        .call(d3.axisBottom(x).tickSize(0))
        .selectAll("text")
        //.attr("fill", "black")
        //.attr("fill", "black")
        .attr("fill", function (d) {
            return in_speciesClustercolors[d];
        })
        //.style("stroke-width",0.2)
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
        //.attr("font-weight", 500)
        .call(d3.axisLeft(y).tickSize(0))
        .selectAll("text")
        //.attr("fill", "black")
        //.attr("fill", "black")
        .attr("fill", function (d) {
            return in_speciesClustercolors[d];
        })
        //.style("stroke-width", 0.2)
        .style("text-anchor", "end")
        .attr("dx", "-0.5em")
        .attr("dy", "0.1em")
        .attr("transform", "rotate(0)")
        .select(".domain")
        .remove();

    // Build color scaled3.scaleSequential(d3Chromatic.interpolatePiYG);
    var myColor = d3.scaleSequential(d3.interpolateGreys).domain([maxdistanceColor, mindistanceColor]);//d3 https://github.com/d3/d3-scale-chromatic

    var valnow1;
    var valuenext1;
    var colorNow1;
    for (var i = 0; i < uniqueClusters1List.length; i++)
    {
         if (i == uniqueClusters1List.length - 1) {
            valnow1 = x(uniqueClusters1List[i]);
            valuenext1 = width;
        }
        else{
            valnow1 = x(uniqueClusters1List[i]);
            valuenext1 = x(uniqueClusters1List[i+1]);
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
            .style("paint-order", "stroke");

    }
    var valnow2;
    var valuenext2;
    var colorNow2;
    for (var i = 0; i < uniqueClusters2List.length; i++) {

        if (i == 0) {
            valnow2 =height;
            valuenext2 = y(uniqueClusters2List[i]);
        }
        else {
            valnow2 = y(uniqueClusters2List[i-1]);
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
            .style("paint-order", "stroke");

    }



    // create a tooltip
    var tooltip = d3
        .select("#my_dataviz")
        .append("div")
        .style("opacity", 0)
        .attr("class", "tooltip")
        .style("background-color", "white")
        .style("border", "solid")
        .style("border-width", "2px")
        .style("border-radius", "5px")
        .style("padding", "5px")
        .style("position", "absolute");

    // Three function that change the tooltip when user hover / move / leave a cell
    var mouseover = function (d) {
        tooltip.style("opacity", 1);
        tooltip.style("z-index", 1);
        d3.select(this)
            //.style("stroke-width", 5)
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
                    return 10;
                }
                else {
                    return 5;
                }
            })
            .style("paint-order", "stroke")
            .style("opacity", 1);
    };
    var mousemove = function (d) {
        var crossSpeciesAddToTooltip = "";
        var species1AddToTooltip = "";
        var species2AddToTooltip = "";
        if (d.cross_species_cluster1_species_1 == d.cross_species_cluster2_species_2)
        {
            crossSpeciesAddToTooltip = "<div style=\"color: " + cross_speciesClustercolors[d.cross_species_cluster1_species_1] +"; -webkit-text-stroke: 0.2 black; cursor:pointer;\"> Cross species cluster: <b>" + d.cross_species_cluster1_species_1+"</b></div>";//labelcolorsforAxis[parseInt(d.cross_species_cluster1_species_1)];
        }
        species1AddToTooltip = "<div style=\"color: " + in_speciesClustercolors[d.cluster_1] + ";-webkit-text-stroke: 0.2 black;  cursor:pointer;\"> Cluster1 : <b>" + d.cluster_1 + "</b></div>";

        species2AddToTooltip = "<div style=\"color: " + in_speciesClustercolors[d.cluster_2] + ";-webkit-text-stroke: 0.2 black;  cursor:pointer;\"> Cluster2 : <b>" + d.cluster_2 + "</b></div>";
        //log("see value: "+addtoToolTip);
        tooltip
            .html(
/*                "Cluster_1: " +
                "<b>" + d.cluster_1 +"</b>"  +
                "<br/> Cluster_2: " +
                "<b>" + d.cluster_2 +"</b>" +*/

                "Distance between clusters: "
                +"<b>" + d.dist +"</b>"/*+
                "<br/> Neighborhood: " +
                "<b>" + d.neighborhood + "</b>"*/
                + species1AddToTooltip
                + species2AddToTooltip
                + crossSpeciesAddToTooltip
            )
            .style("left", d3.mouse(this)[0] + 105 + "px")
            .style("top", d3.mouse(this)[1] + "px")
            .style("position", "absolute")
            .style("cursor","default");
    };
    var mouseleave = function (d) {
        tooltip.style("opacity", 0);
        d3.select(this).style("stroke", function (d) {
            //log("here" + d.cross_species_cluster1_species_1)
            if (d.cross_species_cluster1_species_1 == d.cross_species_cluster2_species_2) {
                return cross_speciesClustercolors[d.cross_species_cluster1_species_1];
            }
            else {
                return "black"; 
            }
            //        
        })
            .style("opacity", 0.9).style("stroke-width", function (d) {

                if (d.cross_species_cluster1_species_1 == d.cross_species_cluster2_species_2) {
                    return 2.0;
                }
                else {
                    return 0.2;
                }
            });
    };

    var mouseclick = function (d) {
        
        let selectionIDs = [];
        selectionIDs.push(d.cross_species_cluster1_species_1);
        selectionIDs.push(d.cross_species_cluster2_species_2);
        if (isQtAvailable) {
            log("sending from js...");
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

        .attr("width", x.bandwidth()+1)
        .attr("height", y.bandwidth()+1)
        .style("fill", function (d) {
            
/*            if (crossSpeciesclusterFiltertoggleValue == "All") {*/
            return myColor(d.dist);
/*            }
            else {*/
/*                if (d.cross_species_cluster1_species_1 == d.cross_species_cluster2_species_2) {
                    return myColor(d.dist);
                }*/
            //}
        })
        .style("stroke-width", function (d) {

            if (d.cross_species_cluster1_species_1 == d.cross_species_cluster2_species_2) {

                if (_clustersReceived.indexOf(d.cross_species_cluster1_species_1) !== -1) {
                    return 6.0;
                } else {
                    return 2.0;
                }
              
            }
            else {
                return 0.2;
            }
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

    var svg = d3.select("svg");

    svg.append("g")
        .attr("class", "legendSequential")
        .attr("width", 30)
        .attr("height", 10)
        .attr("transform", "translate(0,0)");

    var legendSequential = d3.legendColor()
        .shapeWidth(30)
        .cells(cellsForLegend)
        .ascending(false)
        .shapePadding(1)
        .labelFormat("0")
        .labelOffset(5)
        .orient("horizontal")
        .scale(myColor);

    svg.select(".legendSequential")
        .call(legendSequential);

/*    var x = document.getElementById("fullVIS");
    x.style.display = "block";*/
};




function setData(d) {
    log("Data received");
    _dataQueue.addData(d);
}

function setClusters(d) {
    log("Clusters received");
    queueClusters(d);
}

function queueClusters(d) {
    _clustersReceived = [];
    log("here clusters");
    //log(d);
    obj = JSON.parse(d);
   // _clustersReceived = obj[0];
    for (const [key, value] of Object.entries(obj[0])) {
        //log(`${key}: ${value}`);
        _clustersReceived.push(value);
    }
    for (var i = 0; i < _clustersReceived.length; i++) {
        log(_clustersReceived[i]);
    }
    simianVis();

}


function queueData(d) {

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
    simianVis();
    flag = true;
}



function doALoadOfStuff() {
    if (flag) {
        simianVis();
    }
   
}