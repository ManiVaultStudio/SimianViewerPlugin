
# Cytosplore Simian Viewer

![App Screenshot](https://www.thomashollt.com/assets/papers/2023_vcbm_soumyadeep/2023_vcbm_soumyadeep_teaser.png)

The Cytosplore Simian Viewer system is designed to enable researchers to analyze and compare cell and gene expression variations across multiple species.
##Repositories Used

The Cytosplore Simian Viewer system makes use of the following repositories:

1. **Core**
   - Description: Core application manages data sets and plugins.
   - Repository Link: [ManiVaultCore](https://github.com/ManiVaultStudio/core.git)

2. **Scatterplot View Plugin**
   - Repository Link: [SimianViewerScatterplotPlugin](https://github.com/ManiVaultStudio/SimianViewerScatterplotPlugin.git)

3. **Differential Expression View Plugin**
   - Repository Link: [ClusterDifferentialExpressionPlugin](https://github.com/ManiVaultStudio/ClusterDifferentialExpressionPlugin.git)

4. **Pairwise Expression Comparison View Plugin**
   - Repository Link: [SimianViewerPairExpCompPlugin](https://github.com/ManiVaultStudio/SimianViewerPairExpCompPlugin.git)   

5. **Multi-species Expression Comparison View Plugin**
   - Repository Link: [SimianViewerMultExpCompPlugin](https://github.com/ManiVaultStudio/SimianViewerMultExpCompPlugin.git)

5. **Distancemap View Plugin**
   - Repository Link: [SimianViewerPlugin](https://github.com/ManiVaultStudio/SimianViewerPlugin.git)

## Installers

Installer executables are available for download on the [Cytosplore Viewer website](https://viewer.cytosplore.org/). 

## Publications

If you use this project in your research or find it helpful, please consider citing the publications:

- **Cytosplore Simian Viewer: Visual Exploration for Multi-Species Single-Cell RNA Sequencing Data**
  - *Authors*: Soumyadeep Basu, Jeroen Eggermont, Thomas Kroes, Nicholas L. Jorstad, Trygve Bakken, Ed Lein, Boudewijn P.F. Lelieveldt, Thomas Höllt
  - *Published in*: Eurographics Workshop on Visual Computing for Biology and Medicine, page 111-120 - Sep 2023
  - *Link*: [Publisher](https://doi.org/10.2312/vcbm.20231219)
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
  - *Published in*: Science, 2023
  - *Link*: [Publisher](https://doi.org/10.1126/science.ade9516)
  - *BibTeX*:
    ```bibtex
    @article{jorstad2022comparative,
      DOI={10.1126/science.ade9516},
      author = {Nikolas L. Jorstad  and Janet H. T. Song  and David Exposito-Alonso  and Hamsini Suresh  and Nathan Castro-Pacheco  and Fenna M. Krienen  and Anna Marie Yanny  and Jennie Close  and Emily Gelfand  and Brian Long  and Stephanie C. Seeman  and Kyle J. Travaglini  and Soumyadeep Basu  and Marc Beaudin  and Darren Bertagnolli  and Megan Crow  and Song-Lin Ding  and Jeroen Eggermont  and Alexandra Glandon  and Jeff Goldy  and Katelyn Kiick  and Thomas Kroes  and Delissa McMillen  and Trangthanh Pham  and Christine Rimorin  and Kimberly Siletti  and Saroja Somasundaram  and Michael Tieu  and Amy Torkelson  and Guoping Feng  and William D. Hopkins  and Thomas Höllt  and C. Dirk Keene  and Sten Linnarsson  and Steven A. McCarroll  and Boudewijn P. Lelieveldt  and Chet C. Sherwood  and Kimberly Smith  and Christopher A. Walsh  and Alexander Dobin  and Jesse Gillis  and Ed S. Lein  and Rebecca D. Hodge  and Trygve E. Bakken },
      title = {Comparative transcriptomics reveals human-specific cortical features},
      journal = {Science},
      volume = {382},
      number = {6667},
      pages = {eade9516},
      year = {2023},
      doi = {10.1126/science.ade9516},
      URL = {https://www.science.org/doi/abs/10.1126/science.ade9516},
      eprint = {https://www.science.org/doi/pdf/10.1126/science.ade9516},
    }
       
  -*Abstract:* The cognitive abilities of humans are distinctive among primates, but their molecular and cellular substrates are poorly understood. We used comparative single-nucleus transcriptomics to analyze samples of the middle temporal gyrus (MTG) from adult humans, chimpanzees, gorillas, rhesus macaques, and common marmosets to understand human-specific features of the neocortex. Human, chimpanzee, and gorilla MTG showed highly similar cell-type composition and laminar organization as well as a large shift in proportions of deep-layer intratelencephalic-projecting neurons compared with macaque and marmoset MTG. Microglia, astrocytes, and oligodendrocytes had more-divergent expression across species compared with neurons or oligodendrocyte precursor cells, and neuronal expression diverged more rapidly on the human lineage. Only a few hundred genes showed human-specific patterning, suggesting that relatively few cellular and molecular changes distinctively define adult human cortical structure.
