/******************************************************************************
 * This file is part of PCPSolver.                                            *
 *                                                                            *
 * Written by Marcel Lippmann <marcel.lippmann@tu-dresden.de>.                *
 * Copyright (c) 2016 by Marcel Lippmann.  All rights reserved.               *
 *                                                                            *
 ******************************************************************************/
#include "PCPSolver.h"

using namespace pcpsolver;


std::experimental::optional<std::vector<indices_t>> pcpsolver::check_indices(PCPInstance const& instance,
                                                                             indices_t const& indices) {

  if (!indices.empty()) {

    std::string firstW = "";
    std::string secondW = "";

    for (auto const& i : indices) {
      auto const& pair = instance.get_pair(i);
      firstW += pair.first;
      secondW += pair.second;
    }

    // Check whether the first word is a prefix of the second word.
    bool const firstPrefixOfSecond = std::equal(std::begin(firstW), std::end(firstW), std::begin(secondW));

    // Check whether the second word is a prefix of the first word.
    bool const secondPrefixOfFirst = std::equal(std::begin(secondW), std::end(secondW), std::begin(firstW));

    if (firstPrefixOfSecond && secondPrefixOfFirst) {

      // Words are equal.
      return std::experimental::nullopt;

    } else if (!firstPrefixOfSecond && !secondPrefixOfFirst) {

      // This sequence of indices cannot be extended to a solution.
      return std::experimental::make_optional(std::vector<indices_t>());
    }
  }

  // Consider all successor nodes, since sequence of indices can possibly be
  // extended to a solution.
  std::vector<indices_t> nextIndices;
  for (auto const& i : instance.get_list_of_indices()) {
    auto next = indices;
    next.push_back(i);
    nextIndices.push_back(next);
  }

  return std::experimental::make_optional(nextIndices);
}


// Helper function for traversing the search space.
indices_t traverse_search_space(PCPInstance const& instance,
                                std::vector<indices_t>& roots) {

  std::vector<indices_t> nextRoots;
  for (auto const& root : roots) {

    auto const nextIndices = check_indices(instance, root);
    if (nextIndices) {

      // Add new indices to search space
      nextRoots.insert(std::end(nextRoots),
                       std::begin(nextIndices.value()),
                       std::end(nextIndices.value()));

    } else {

      // Solution found.
      return root;
    }
  }

  // No solution found (yet), try next roots.
  return traverse_search_space(instance, nextRoots);
}


indices_t pcpsolver::solve(PCPInstance const& instance) {

  std::vector<indices_t> startRoots;
  indices_t start;
  startRoots.push_back(start);

  return traverse_search_space(instance, startRoots);
}
