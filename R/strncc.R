#' Calculate the number of connected components from a vector of strings
#'
#' Tokes in a vector of strings, and a threshold for number of mismatches allowed (hamming distance)
#' @param strvectors A vector of strings
#' @param mm Maximal hamming distance allowed to add an edge between two strings
#' @return The number of connected components (UMI)
#' @examples 
#' RcppNumberConnectedComponents(c("ATTG","ACTG","CCGG"), 1)
#' dataframe %>% dplyr::group_by(sample) %>% dplyr::summarise(n_umi=Rncc::RcppNumberConnectedComponents(kmer, 3))
#' dataframe %>% multidplyr::partition(sample, cluster = cluster24) %>% dplyr::summarise(n_umi=Rncc::RcppNumberConnectedComponents(kmer, 3)) %>% collect()
#' @export
RcppNumberConnectedComponents = function(strvectors, mm) {
    NumberConnectedComponents(strvectors, mm)
}
