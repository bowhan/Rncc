# Rncc

### Introduction

Simple wrapper of C++ code using Lemon Graph Library to calculate the number of connected components 
from a graph, whose nodes are strings of the same length and edges are those connecting
nodes whose hamming distances are shorter than a certain threshold

This is mainly used to collapse UMI. And this package is written to calculate it without leaving the R
enviroment.

### Installation

Pre-requisite: Lemon C++ Graph Library

```r
library(devtools)
install_github("bowhan/Rncc")
```

### Usage
```r
library(Rncc)
# simple case
Rncc::RcppNumberConnectedComponents(c("ACGT", "ACCT", "AccC"), 2) # 1

# useful case:
dataframe %>% 
    group_by(sample) %>%
    summarise(n_umi=Rncc::RcppNumberConnectedComponents(kmer))
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
    print("cleaning edge list")
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