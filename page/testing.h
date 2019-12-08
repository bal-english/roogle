#include "document.h"

#define TESTDOCSAMPLESIZE 5

void get_sample_docs(struct Document* docs) {
  struct Document doc_1;
  char* id_1 = "0704.0001";
  char* title_1 = "Calculation of prompt diphoton production cross sections at Tevatron and   LHC energies";
  int authornum_1 = 4;
  //char* authors_1 = malloc(authornum_1*sizeof(char));
  char* authors_1 = "C. Bal\'azs, E. L. Berger, P. M. Nadolsky, C.-P. Yuan";
  char* abstract_1 = "A fully differential calculation in perturbative quantum chromodynamics is presented for the production of massive photon pairs at hadron colliders. All next-to-leading order perturbative contributions from quark-antiquark, gluon-(anti)quark, and gluon-gluon subprocesses are included, as well as all-orders resummation of initial-state gluon radiation valid at next-to-next-to-leading logarithmic accuracy. The region of phase space is specified in which the calculation is most reliable. Good agreement is demonstrated with data from the Fermilab Tevatron, and predictions are made for more detailed tests with CDF and DO data. Predictions are shown for distributions of diphoton pairs produced at the energy of the Large Hadron Collider (LHC). Distributions of the diphoton pairs from the decay of a Higgs boson are contrasted with those produced from QCD processes at the LHC, showing that enhanced sensitivity to the signal can be obtained with judicious selection of events.";
  create_new_document(&doc_1, id_1, title_1, authors_1, abstract_1);
  docs[0] = doc_1;

  struct Document doc_2;
  char* id_2 = "0704.0002";
  char* title_2 = "Sparsity-certifying Graph Decompositions";
  int authornum_2 = 2;
  //char* authors_2 = malloc(authornum_1*sizeof(char));
  char* authors_2 = "Ileana Streinu, Louis Theran";
  char* abstract_2 = "We describe a new algorithm, the $(k,\ell)$-pebble game with colors, and use it obtain a characterization of the family of $(k,\ell)$-sparse graphs and algorithmic solutions to a family of problems concerning tree decompositions of graphs. Special instances of sparse graphs appear in rigidity theory and have received increased attention in recent years. In particular, our colored pebbles generalize and strengthen the previous results of Lee and Streinu and give a new proof of the Tutte-Nash-Williams characterization of arboricity. We also present a new decomposition that certifies sparsity based on the $(k,\ell)$-pebble game with colors. Our work also exposes connections between pebble game algorithms and previous sparse graph algorithms by Gabow, Gabow and Westermann and Hendrickson.";
  create_new_document(&doc_2, id_2, title_2, authors_2, abstract_2);
  docs[1] = doc_2;

  struct Document doc_3;
  char* id_3 = "0704.0003";
  char* title_3 = "The evolution of the Earth-Moon system based on the dark matter field   fluid model";
  int authornum_3 = 1;
  // char* authors_3 = malloc(authornum_3*sizeof(char));
  char* authors_3 = "Hongjun Pan";
  char* abstract_3 = "The evolution of Earth-Moon system is described by the dark matter field fluid model proposed in the Meeting of Division of Particle and Field 2004, American Physical Society. The current behavior of the Earth-Moon system agrees with this model very well and the general pattern of the evolution of the Moon-Earth system described by this model agrees with geological and fossil evidence. The closest distance of the Moon to Earth was about 259000 km at 4.5 billion years ago, which is far beyond the Roche's limit. The result suggests that the tidal friction may not be the primary cause for the evolution of the Earth-Moon system. The average dark matter field fluid constant derived from Earth-Moon system data is 4.39 x 10^(-22) s^(-1)m^(-1). This model predicts that the Mars's rotation is also slowing with the angular acceleration rate about -4.38 x 10^(-22) rad s^(-2).";
  create_new_document(&doc_3, id_3, title_3, authors_3, abstract_3);
  docs[2] = doc_3;

  struct Document doc_4;
  char* id_4 = "0704.0004";
  char* title_4 = "A determinant of Stirling cycle numbers counts unlabeled acyclic   single-source automata";
  int authornum_4 = 1;
  // char* authors_4 = malloc(authornum_4*sizeof(char));
  char* authors_4 = "David Callan";
  char* abstract_4 = "We show that a determinant of Stirling cycle numbers counts unlabeled acyclic single-source automata. The proof involves a bijection from these automata to certain marked lattice paths and a sign-reversing involution to evaluate the determinant.";
  create_new_document(&doc_4, id_4, title_4, authors_4, abstract_4);
  docs[3] = doc_4;

  struct Document doc_5;
  char* id_5 = "0704.0005";
  char* title_5 = "From dyadic $\Lambda_{\alpha}$ to $\Lambda_{\alpha}$";
  int authornum_5 = 2;
  // char* authors_5 = malloc(authornum_5*sizeof(char));
  char* authors_5 = "Wael Abu-Shammala, Alberto Torchinsky";
  char* abstract_5 = "We show that a determinant of Stirling cycle numbers counts unlabeled acyclic single-source automata. The proof involves a bijection from these automata to certain marked lattice paths and a sign-reversing involution to evaluate the determinant.";
  create_new_document(&doc_5, id_5, title_5, authors_5, abstract_5);
  docs[4] = doc_5;
}
