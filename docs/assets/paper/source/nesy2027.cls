% Copied from clear2024.cls
\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{nesy2027}[2026/05/09 v1.1 NeSy 2026 Proceedings]
\newcommand{\todo}{\color{red}}

\@ifundefined{ifanonsubmission}{
  \newif\ifanonsubmission
  \anonsubmissionfalse
}{}

\@ifundefined{iffinalsubmission}{
  \newif\iffinalsubmission
  \finalsubmissionfalse
}{}

\DeclareOption{anon}{\anonsubmissiontrue}
\DeclareOption{final}{\finalsubmissiontrue}
\ProcessOptions\relax

\LoadClass[pmlr]{jmlr}

\jmlrvolume{vol 284}
\jmlryear{2026}
\jmlrproceedings{PMLR}{Proceedings of Machine Learning Research}

\ifanonsubmission
 \newcommand{\clearauthor}[1]{}
 \author{Author names withheld}
 \editor{Under Review for NeSy 2026}
 \jmlrworkshop{20th Conference on Neurosymbolic Learning and Reasoning}
 \renewcommand{\acks}[1]{}
\else
 \newcommand{\clearauthor}[1]{\author{#1}}
 \iffinalsubmission
  \editors{Alessandra Mileo, Andrea Passerini and Cogan Shimizu}
  \jmlrworkshop{20th Conference on Neurosymbolic Learning and Reasoning}
 \fi
\fi


