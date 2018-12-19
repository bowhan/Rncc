# Rncc
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/811be06a238a4acf99e80e4dd28d768c)](https://www.codacy.com/app/bowhan/Rncc?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=bowhan/Rncc&amp;utm_campaign=Badge_Grade)
[![Build Status](https://travis-ci.org/bowhan/Rncc.svg?branch=master)](https://travis-ci.org/bowhan/Rncc)
[![codecov](https://codecov.io/gh/bowhan/rncc/branch/master/graph/badge.svg)](https://codecov.io/gh/bowhan/rncc)

### Introduction

Simple wrapper of C++ code using Lemon Graph Library to calculate the number of connected components 
from a graph, whose nodes are strings of the same length and edges are those connecting
nodes whose hamming distances are shorter than a certain threshold

This is mainly used to collapse UMI. And this package is developed to calculate it without leaving the R
enviroment.

### Installation

Pre-requisite: Lemon C++ Graph Library

```r
library(devtools)
install_github("bowhan/Rncc")
```

### Usage
#### Count the number of Connected Components (UMIs)
```r
library(Rncc)
# simple case
Rncc::RcppNumberConnectedComponents(c("ACGT", "ACCT", "AccC"), 2) # 1

# useful case:
dataframe %>% 
    group_by(sample) %>%
    summarise(n_umi=Rncc::RcppNumberConnectedComponents(kmer, 3))

# parallelized version
library(multidplyr)
cluster24 = create_cluster(24)
dataframe %>% 
    multidplyr::partition(sample, cluster = cluster24) %>%
    summarise(n_umi=Rncc::RcppNumberConnectedComponents(kmer, 3)) %>%
    collect()
```

#### Assign each kmer to connected components
```r
library(Rncc)
df = tibble(kmers=c("ACCC", "TTCC", "GCCC", "GCCC", "TTTC", "TTCC"))
df %>% mutate(ncc_id = Rncc::RcppConnectedComponents(strs, 1))

#   A tibble: 6 x 2
#   kmers ncc_id
#   <chr>  <dbl>
# 1 ACCC       1
# 2 TTCC       0
# 3 GCCC       1
# 4 GCCC       1
# 5 TTTC       0
# 6 TTCC       0
```

### Benchmark
```r
# calculate connected components using stringdist & igraph
library(stringdist)
library(igraph)
stringdis_count_cc = function(x, mm) {
  # calculate string distance matrix, then convert it to boolean matrix based on the distance
  strdisedges = melt(as.matrix(stringdistmatrix(x, method="hamming", nthread=32)), na.rm=T)
  if(nrow(strdisedges) > 0) {
    strdisedges = strdisedges %>% filter(Var1 <= Var2 & value <= mm) %>% select(-value)
    # generate graph based on the matrix
    g = graph_from_data_frame(strdisedges, directed=F)
    # return the number of connected components
    no.clusters(g)
  } else {
    0
  }
}

# benchmark
benchmark(
  stringdis_count_cc(kmers, 3),
  Rncc::RcppNumberConnectedComponents(kmers, 3),
  replications=5
)
# RcppNumberConnectedComponents is ~14x faster than stringdis_count_cc
                                        #    test replications elapsed relative user.self sys.self user.child sys.child
# 2 Rncc::RcppNumberConnectedComponents(kmers, 3)            5  12.598     1.00    12.520    0.080          0         0
# 1                     stringdis_count_cc(kmers)            5 181.534    14.41   329.784    3.824          0         0
```