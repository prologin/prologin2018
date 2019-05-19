# -*- Makefile -*-

lib_TARGETS = champion

# Tu peux rajouter des fichiers sources, headers, ou changer
# des flags de compilation.
champion-srcs = prologin.cc action.cc agent.cc direction.cc position.cc state.cc
champion-dists = action.hh  agent.hh  direction.hh  position.hh  state.hh
champion-cxxflags = -ggdb3 -Wall

# Evite de toucher a ce qui suit
champion-dists += prologin.hh
STECHEC_LANG=cxx
include ../includes/rules.mk
