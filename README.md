# Roogle (Google For Research Papers)

Search Engine for research papers hosted on arXiv

Uses pagerank algorithm to rank papers based on authority and hub scores.
Paper that references more papers will have a higher hub score, paper that is referenced more will have higher authority score

Uses OpenMPI to parse abstracts in parallel, Compressed Sparse Row encoding to store connectivity matrix
