/******************************************************************************
 * This file is part of PCPSolver.                                            *
 *                                                                            *
 * Written by Marcel Lippmann <marcel.lippmann@tu-dresden.de>.                *
 * Copyright (c) 2016 by Marcel Lippmann.  All rights reserved.               *
 *                                                                            *
 ******************************************************************************/
#include "PCPSolver.h"

using namespace pcpsolver;


PCPSolver::PCPSolver(PCPInstance const& instance) : instance_(instance) {
}


PCPSolver::~PCPSolver() {
}


std::experimental::optional<std::tuple<indices_t, indices_t, wordpair_t>>
  PCPSolver::check_indices(indices_t const& indices,
			   index_t const& index,
			   wordpair_t const& wordpair) const {

  // Get the index pair and append it to the given word pair.
  auto const& pair = instance_.get_pair(index);
  auto newpair = std::make_pair(wordpair.first + pair.first,
                                wordpair.second + pair.second);

  // Truncate the new word pair by dropping equal prefixes.
  size_t const  cnt = std::mismatch(newpair.first.begin(),
				    newpair.first.begin()+std::min(newpair.first.size(), newpair.second.size()),
				    newpair.second.begin()).first - newpair.first.begin();
  newpair.first.erase(0, cnt);
  newpair.second.erase(0, cnt);

  // Check whether words are equal, i.e. we have found a solution.
  if (newpair.first.empty() && newpair.second.empty()) {

    return std::experimental::nullopt;
  }

  auto newIndices = indices;
  newIndices.push_back(index);

  // Check whether sequence of indices cannot be extended to a solution.
  if (!newpair.first.empty() && !newpair.second.empty()) {

    return std::experimental::make_optional(std::make_tuple(indices_t(), indices_t(), std::make_pair(std::string(), std::string())));
  }

  // Consider all successor indices, since sequence of indices can possibly be
  // extended to a solution.
  return std::experimental::make_optional(std::make_tuple(std::move(newIndices), instance_.get_list_of_indices(), std::move(newpair)));
}


std::experimental::optional<indices_t> PCPSolver::traverse_search_space(std::vector<std::tuple<indices_t, indices_t, wordpair_t>> const& candidates) const {

  // Store next candidates in a vector to apply BFS.
  std::vector<std::tuple<indices_t, indices_t, wordpair_t>> nextCandidates;

  for (auto const& candidate : candidates) {

    auto const& indices = std::get<0>(candidate);
    auto const& extensions = std::get<1>(candidate);
    auto const& wordpair = std::get<2>(candidate);

    for (auto const& extension : extensions) {

      auto const& nextTuple = check_indices(indices, extension, wordpair);

      // Check whether a solution was found.
      if (!nextTuple) {

        auto solution = indices;
        solution.push_back(extension);

        return std::experimental::make_optional(solution);

      } else {

        // Add new tuple to search space if it provides extensions.
        if (!std::get<1>(nextTuple.value()).empty()) {

          nextCandidates.push_back(nextTuple.value());
        }
      }
    }
  }

  // No solution found (yet), try next candidates if there are any.
  if (nextCandidates.empty()) {

    // No more candidates left: there is no solution.
    return std::experimental::nullopt;

  } else {

    return traverse_search_space(nextCandidates);
  }
}


std::experimental::optional<indices_t> PCPSolver::solve() const {

  // Start the search with an empty sequence of indices, all possible
  // extensions, and an empty word pair.
  std::vector<std::tuple<indices_t, indices_t, wordpair_t>> startCandidate;

  indices_t emptyIndices;
  auto startIndices = instance_.get_list_of_indices();
  auto emptyWordpair = std::make_pair("", "");

  startCandidate.push_back(std::make_tuple(emptyIndices, startIndices, emptyWordpair));

  return traverse_search_space(startCandidate);
}
