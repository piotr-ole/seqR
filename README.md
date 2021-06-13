
# seqR - fast and comprehensive k-mer counting package

<!-- badges: start -->

[![R build
status](https://github.com/slowikj/seqR/workflows/R-CMD-check/badge.svg)](https://github.com/slowikj/seqR/actions)
<!-- badges: end -->

## About

`seqR` is an R package for fast k-mer counting. It provides

-   **highly optimized** (the core algorithm is written in C++)
-   **in-memory**
-   **probabilistic** (with configurable dimensionality of a hash value
    used for storing k-mers internally),
-   **multi-threaded**

implementation that supports

-   **various variants of k-mers** (contiguous, gapped, and positional
    counterparts)
-   **all biological sequences** (e.g., nucleic acids and proteins)

Moreover, the result optimizes memory consumption by the application of
**sparse matrices**, compatible with machine learning packages such as
[ranger](https://cran.r-project.org/web/packages/ranger/index.html) and
[xgboost](https://cran.r-project.org/web/packages/xgboost/index.html).

### Available functions

The package provides three functions that facilitate k-mer counting and
processing k-mer matrices:

-   `count_kmers` (used for counting k-mers of one type)
-   `count_multimers` (a wrapper of `count_kmers`, used for counting
    k-mers of many types in a single invocation of the function)
-   `rbind_columnwise` (a helper function used for merging several k-mer
    matrices that do not have same sets of columns)

## How to…

### How to install

It is possible to download the development version directly from GitHub
repository:

``` r
# install.packages("devtools")
devtools::install_github("slowikj/seqR")
```

### How to use

\[TODO\] Link to the documentation and vignettes

See features overview vignette and documentation to learn how to use
**seqR**.

### How to cite

\[TODO\]

## Benchmarks

\[TODO\]
