
# Cytosplore Simian Viewer

![App Screenshot](https://www.thomashollt.com/assets/papers/2023_vcbm_soumyadeep/2023_vcbm_soumyadeep_teaser.png)

The Cytosplore Simian Viewer system is designed to enable researchers to analyze and compare cell and gene expression variations across multiple species.
##Repositories Used

The Cytosplore Simian Viewer system makes use of the following repositories:

1. **Core**
   - Description: Core application manages data sets and plugins.
   - Repository Link: [ManiVaultCore](https://github.com/ManiVaultStudio/core.git)

2. **SimianViewerScatterplotPlugin**
   - Description: Plugin for Scatterplot view.
   - Repository Link: [SimianViewerScatterplotPlugin](https://github.com/ManiVaultStudio/SimianViewerScatterplotPlugin.git)

3. **ClusterDifferentialExpressionPlugin**
   - Description: Plugin to compute and view Differential Expression.
   - Repository Link: [ClusterDifferentialExpressionPlugin](https://github.com/ManiVaultStudio/ClusterDifferentialExpressionPlugin.git)

4. **SimianViewerPairExpCompPlugin**
   - Description: Plugin for Pairwise Expression Comparison.
   - Repository Link: [SimianViewerPairExpCompPlugin](https://github.com/ManiVaultStudio/SimianViewerPairExpCompPlugin.git)   

5. **SimianViewerMultExpCompPlugin**
   - Description: Plugin for Multi-Species Expression Comparison.
   - Repository Link: [SimianViewerMultExpCompPlugin](https://github.com/ManiVaultStudio/SimianViewerMultExpCompPlugin.git)

5. **SimianViewerPlugin**
   - Description: Plugin for Distancemap view.
   - Repository Link: [SimianViewerPlugin](https://github.com/ManiVaultStudio/SimianViewerPlugin.git)
## Installers

Installer executables can be downloaded from the [Cytosplore website](https://viewer.cytosplore.org/).

## Publications

If you use this project in your research or find it helpful, please consider citing the publications:

- **Cytosplore Simian Viewer: Visual Exploration for Multi-Species Single-Cell RNA Sequencing Data**
  - *Authors*: Soumyadeep Basu, Jeroen Eggermont, Thomas Kroes, Nicholas L. Jorstad, Trygve Bakken, Ed Lein, Boudewijn P.F. Lelieveldt, Thomas Höllt
  - *Published in*: Eurographics Workshop on Visual Computing for Biology and Medicine, page 111-120 - Sep 2023
  - *Link*: [Paper](https://diglib.eg.org/handle/10.2312/vcbm20231219)
  - *BibTeX*:
    ```bibtex
    @article{10.2312:vcbm.20231219,
      booktitle = {Eurographics Workshop on Visual Computing for Biology and Medicine},
      editor = {Hansen, Christian and Procter, James and Renata G. Raidou and Jönsson, Daniel and Höllt, Thomas},
      title = {{Cytosplore Simian Viewer: Visual Exploration for Multi-Species Single-Cell RNA Sequencing Data}},
      author = {Basu, Soumyadeep and Eggermont, Jeroen and Kroes, Thomas and Jorstad, Nikolas and Bakken, Trygve and Lein, Ed and Lelieveldt, Boudewijn and Höllt, Thomas},
      year = {2023},
      publisher = {The Eurographics Association},
      ISSN = {2070-5786},
      ISBN = {978-3-03868-216-5},
      DOI = {10.2312/vcbm.20231219}
    }
  -*Abstract:* With the rapid advances in single-cell sequencing technologies, novel types of studies into the cell-type makeup of the brain have become possible. Biologists often analyze large and complex single-cell transcriptomic datasets to enhance knowledge of the intricate features of cellular and molecular tissue organization. A particular area of interest is the study of whether cell types and their gene regulation are conserved across species during evolution. However, in-depth comparisons across species of such high-dimensional, multi-modal single-cell data pose considerable visualization challenges. This paper introduces Cytosplore Simian Viewer, a visualization system that combines various views and linked interaction methods for comparative analysis of single-cell transcriptomic datasets across multiple species. Cytosplore Simian Viewer enables biologists to help gain insights into the cell type and gene expression differences and similarities among different species, particularly focusing on comparing human data to other species. The system validation in discovery research on real-world datasets demonstrates its utility in visualizing valuable results related to the evolutionary development of the middle temporal gyrus.


- **Comparative transcriptomics reveals human-specific cortical features**
  - *Authors*: Nikolas L Jorstad, Janet HT Song, David Exposito-Alonso, Hamsini Suresh, Nathan Castro, et al.
  - *Published in*: bioRxiv, 2022
  - *Link*: [Paper](https://www.biorxiv.org/content/10.1101/2022.09.19.508480v1)
  - *BibTeX*:
    ```bibtex
    @article{jorstad2022comparative
      title={Comparative transcriptomics reveals human-specific cortical features},
      author={Jorstad, Nikolas L and Song, Janet HT and Exposito-Alonso, David and Suresh, Hamsini and Castro, Nathan and Krienen, Fenna M and Yanny, Anna Marie and Close, Jennie and Gelfand, Emily and Travaglini, Kyle J and others},
      journal={bioRxiv},
      pages={2022--09},
      year={2022},
      publisher={Cold Spring Harbor Laboratory}
      DOI = {10.1101/2022.09.19.508480}
    }
  -*Abstract:* Humans have unique cognitive abilities among primates, including language, but their molecular, cellular, and circuit substrates are poorly understood. We used comparative single nucleus transcriptomics in adult humans, chimpanzees, gorillas, rhesus macaques, and common marmosets from the middle temporal gyrus (MTG) to understand human-specific features of cellular and molecular organization. Human, chimpanzee, and gorilla MTG showed highly similar cell type composition and laminar organization, and a large shift in proportions of deep layer intratelencephalic-projecting neurons compared to macaque and marmoset. Species differences in gene expression generally mirrored evolutionary distance and were seen in all cell types, although chimpanzees were more similar to gorillas than humans, consistent with faster divergence along the human lineage. Microglia, astrocytes, and oligodendrocytes showed accelerated gene expression changes compared to neurons or oligodendrocyte precursor cells, indicating either relaxed evolutionary constraints or positive selection in these cell types. Only a few hundred genes showed human-specific patterning in all or specific cell types, and were significantly enriched near human accelerated regions (HARs) and conserved deletions (hCONDELS) and in cell adhesion and intercellular signaling pathways. These results suggest that relatively few cellular and molecular changes uniquely define adult human cortical structure, particularly by affecting circuit connectivity and glial cell function
