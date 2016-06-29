/******************************************************************************
 * This file is part of PCPSolver.                                            *
 *                                                                            *
 * Written by Marcel Lippmann <marcel.lippmann@tu-dresden.de>.                *
 * Copyright (c) 2016 by Marcel Lippmann.  All rights reserved.               *
 *                                                                            *
 ******************************************************************************/
#include "PCPTools.h"

using namespace pcpsolver;


solution_t pcpsolver::check(PCPInstance const& instance,
                            std::vector<std::string> const& indices) {

  // An empty list of indices can possibly be extended to a solution.
  if (indices.empty()) {
    return EXTENSION_POSSIBLE;
  }

  std::string firstW = "";
  std::string secondW = "";

  for (auto const& i : indices) {
    auto const& pair = instance.get_pair(i);
    firstW += pair.first;
    secondW += pair.second;
  }

  // Check whether the first word is a prefix of the second word.
  bool const firstPrefixOfSecond = std::equal(firstW.begin(), firstW.end(), secondW.begin());

  // Check whether the second word is a prefix of the first word.
  bool const secondPrefixOfFirst = std::equal(secondW.begin(), secondW.end(), firstW.begin());

  if (firstPrefixOfSecond && secondPrefixOfFirst) {

    // Words are equal
    return SOLUTION;

  } else if (!firstPrefixOfSecond && !secondPrefixOfFirst) {

    return NOT_SOLUTION;

  } else {

    return EXTENSION_POSSIBLE;
  }

}


// Helper function for traversing the search tree.
void traverse_tree(PCPInstance const& instance,
                   std::vector<std::string>& root,
                   int maxLevel) {

  auto const prune = check(instance, root);

  if (prune == SOLUTION) {
    throw root;
  }

  if (prune == EXTENSION_POSSIBLE && root.size() < maxLevel) {

    for (auto const& i : instance.get_list_of_indices()) {
      root.push_back(i);
      traverse_tree(instance, root, maxLevel);
      root.pop_back();
    }
  }
}

std::vector<std::string> pcpsolver::solve(PCPInstance const& instance) {

  try {

    int maxLevel = 1;
    std::vector<std::string> root;
    while (true) {
      ++maxLevel;
      traverse_tree(instance, root, maxLevel);
    }

  } catch (std::vector<std::string> const& solution) {

    return solution;
  }
}
