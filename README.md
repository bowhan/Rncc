# Rncc

### Introduction

Simple wrapper of C++ code using Lemon Graph Library to calculate the number of connected components 
from a graph, whose nodes are strings of the same length and edges are those connecting
nodes whose hamming distances are shorter than a certain threshold


### Installation

Pre-requisite: Lemon C++ Graph Library

```r
library(devtools)
install_github("bowhan/Rncc")
```

### Usage
```r
library(Rncc)
Rncc::RcppNumberConnectedComponents(c("ACGT", "ACCT", "AccC"), 2) # 1
```