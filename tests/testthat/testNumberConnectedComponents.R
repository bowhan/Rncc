library(Rncc)
library(readr)
library(dplyr)

context("Number of Connect Components")

df = readr::read_csv("../data.csv")

test_that("calculate UMI with dplyr::summarise", {
    res = df %>% dplyr::group_by(Sample) %>% dplyr::summarise(umi = Rncc::RcppNumberConnectedComponents(Kmer, 1))
    expect_true(res %>% filter(Sample=="A") %>% select(umi) %>% unlist == 2)
    expect_true(res %>% filter(Sample=="B") %>% select(umi) %>% unlist == 1)
    expect_true(res %>% filter(Sample=="C") %>% select(umi) %>% unlist == 1)
})