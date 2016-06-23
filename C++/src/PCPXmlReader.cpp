/******************************************************************************
 * This file is part of PCPSolver.                                            *
 *                                                                            *
 * Written by Marcel Lippmann <marcel.lippmann@tu-dresden.de>.                *
 * Copyright (c) 2016 by Marcel Lippmann.  All rights reserved.               *
 *                                                                            *
 ******************************************************************************/
#include "PCPXmlReader.h"

#include <iostream>
#include <stdexcept>
#include <libxml++/libxml++.h>

#include "PCPInstance.h"

using namespace pcpsolver;


PCPInstance *pcpsolver::read_pcp_instance_from_xml_file(const std::string &filepath) {

  xmlpp::DomParser parser;
  parser.parse_file(filepath);

  const auto doc = parser.get_document();
  if (doc == NULL) {
    throw std::runtime_error("Could not get document");
  }

  const auto pNode = doc->get_root_node();
  if (pNode == NULL) {
    throw std::runtime_error("Could not get root node");
  }

  PCPInstance *instance = new PCPInstance();

  for (const auto node : pNode->find("/PCPInstance/Pair")) {

    const auto pair = dynamic_cast<xmlpp::Element *>(node);
    if (pair == NULL) {
      throw std::runtime_error("Could not read PCP pair");
    }

    const auto nameAttr = pair->get_attribute("name");
    if (nameAttr == NULL) {
      throw std::runtime_error("Found PCP pair without attribute \"name\"");
    }

    const auto firstAttr = pair->get_attribute("first");
    if (firstAttr == NULL) {
      throw std::runtime_error("Found PCP pair without attribute \"first\"");
    }

    const auto secondAttr = pair->get_attribute("second");
    if (secondAttr == NULL) {
      throw std::runtime_error("Found PCP pair without attribute \"second\"");
    }

    const auto &index = nameAttr->get_value();
    const auto &first = firstAttr->get_value();
    const auto &second = secondAttr->get_value();

    instance->add_pair(index, first, second);
  }

  return instance;
}
