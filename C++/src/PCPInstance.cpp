/******************************************************************************
 * This file is part of PCPSolver.                                            *
 *                                                                            *
 * Written by Marcel Lippmann <marcel.lippmann@tu-dresden.de>.                *
 * Copyright (c) 2016 by Marcel Lippmann.  All rights reserved.               *
 *                                                                            *
 ******************************************************************************/
#include "PCPInstance.h"

using namespace pcpsolver;


PCPInstance::PCPInstance() {
}


PCPInstance::~PCPInstance() {
}


void PCPInstance::add_pair(std::string const& index,
                           std::string const& first,
                           std::string const& second) {

  const auto pair = std::make_pair(first, second);

  // Add pair to list of indices only if it does not exist before.
  if (instance_.find(index) == instance_.end()) {
    indices_.push_back(index);
  }

  // Possibly override previous pair at index.
  instance_[index] = pair;
}

wordpair_t const& PCPInstance::get_pair(std::string const& index) const {

  return instance_.at(index);
}

indices_t const& PCPInstance::get_list_of_indices() const {
  return indices_;
}
