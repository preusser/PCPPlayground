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


void PCPInstance::add_pair(const std::string &index, const std::string &first, const std::string &second) {

  const auto pair = std::make_pair(first, second);

  // Add pair to list of indices only if it does not exist before.
  if (m_instance.find(index) == m_instance.end()) {
    m_indices.push_back(index);
  }

  // Possibly override previous pair at index.
  m_instance[index] = pair;
}

const std::pair<std::string, std::string> &PCPInstance::get_pair(const std::string &index) const {

  return m_instance.at(index);
}

const std::vector<std::string> &PCPInstance::get_list_of_indices() const {
  return m_indices;
}
