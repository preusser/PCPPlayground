/******************************************************************************
 * This file is part of PCPSolver.                                            *
 *                                                                            *
 * Written by Marcel Lippmann <marcel.lippmann@tu-dresden.de>.                *
 * Copyright (c) 2016 by Marcel Lippmann.  All rights reserved.               *
 *                                                                            *
 ******************************************************************************/
#include "PCPXmlReader.h"

#include <iostream>
#include <memory>
#include <stdexcept>
#include <libxml++/libxml++.h>

#include "PCPInstance.h"

using namespace pcpsolver;


template<typename T, typename E=std::runtime_error, typename... U>
T* throw_exception_if_nullptr(T* const arg, U&&... u) {

  if (arg == nullptr) {
    throw E(std::forward<U>(u)...);
  }

  return arg;
}

PCPInstance* pcpsolver::read_pcp_instance_from_xml_file(std::string const& filepath) {

  xmlpp::DomParser parser;
  parser.parse_file(filepath);

  auto const doc = throw_exception_if_nullptr(parser.get_document(),
                     "Could not get document");

  auto const root = throw_exception_if_nullptr(doc->get_root_node(),
                       "Could not get root node");

  auto instance = std::make_unique<PCPInstance>();

  for (auto const node : root->find("/PCPInstance/Pair")) {

    auto const pair = throw_exception_if_nullptr(dynamic_cast<xmlpp::Element*>(node),
                        "Could not read PCP pair");

    auto const nameAttr = throw_exception_if_nullptr(pair->get_attribute("name"),
                            "Found PCP pair without attribute \"name\"");

    auto const firstAttr = throw_exception_if_nullptr(pair->get_attribute("first"),
                             "Found PCP pair without attribute \"first\"");

    auto const secondAttr = throw_exception_if_nullptr(pair->get_attribute("second"),
                              "Found PCP pair without attribute \"second\"");

    auto const& index = nameAttr->get_value();
    auto const& first = firstAttr->get_value();
    auto const& second = secondAttr->get_value();

    instance->add_pair(index, first, second);
  }

  return instance.release();
}
