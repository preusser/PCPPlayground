/******************************************************************************
 * This file is part of PCPSolver.                                            *
 *                                                                            *
 * Written by Marcel Lippmann <marcel.lippmann@tu-dresden.de>.                *
 * Copyright (c) 2016 by Marcel Lippmann.  All rights reserved.               *
 *                                                                            *
 ******************************************************************************/
#include "PCPTools.h"

using namespace pcpsolver;


solution_t pcpsolver::check(const PCPInstance &instance, const std::vector<std::string> &indices) {

  // An empty list of indices can possibly be extended to a solution.
  if (indices.empty()) {
    return EXTENSION_POSSIBLE; } 
  std::string firstW = "";
  std::string secondW = "";

  for (const auto &i : indices) {
    const auto &pair = instance.get_pair(i);
    firstW += pair.first;
    secondW += pair.second;
  }

  // Check whether the first word is a prefix of the second word.
  bool firstPrefixOfSecond = std::equal(firstW.begin(), firstW.end(), secondW.begin());

  // Check whether the second word is a prefix of the first word.
  bool secondPrefixOfFirst = std::equal(secondW.begin(), secondW.end(), firstW.begin());

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
void traverse_tree(const PCPInstance &instance, std::vector<std::string> &root, int maxLevel) {

  const auto prune = check(instance, root);

  if (prune == SOLUTION) {
    throw root;
  }

  if (prune == EXTENSION_POSSIBLE && root.size() < maxLevel) {

    for (const auto &i : instance.get_list_of_indices()) {
      root.push_back(i);
      traverse_tree(instance, root, maxLevel);
      root.pop_back();
    }
  }
}

std::vector<std::string> pcpsolver::solve(const PCPInstance &instance) {

  try {

    int maxLevel = 0;
    std::vector<std::string> root;
    while (true) {
      maxLevel++;
      traverse_tree(instance, root, maxLevel);
    }

  } catch (const std::vector<std::string> &solution) {

    return solution;
  }
}
