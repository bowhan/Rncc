# Rncc

### Introduction

Simple wrapper for C++ code using Lemon to calculate the number of connected components 
from a graph, whose nodes are strings of the same length and edges are those connect
nodes whose hamming distances are shorter than a certain threshold


### Installation
```r
library(devtools)
install_github("bowhan/Rncc")
```

### Usage
```r
RcppNumberConnectedComponents(c("ACGT", "ACCT", "AccC"), 2)
```