//------------------------------------------------------------------------------
//
// Option parsing to use in testing system
// Alternative version (without boost)
//
//------------------------------------------------------------------------------
//
// This file is licensed after LGPL v3
// Look at: https://www.gnu.org/licenses/lgpl-3.0.en.html for details
//
//------------------------------------------------------------------------------

#pragma once

#include <cassert>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>

// value + description
using valdesc = std::pair<std::string, std::string>;

class optparser_t final {
  bool Parsed_ = false;
  // name -> valdesc
  std::unordered_map<std::string, valdesc> Values_;

public:
  optparser_t() = default;

  template <typename T>
  void add(std::string Name, T Defval, std::string Description = "") {
    std::ostringstream Os;
    Os << Defval;
    auto &ValDesc = Values_[Name];
    ValDesc.first = Os.str();
    ValDesc.second = Description;
  }

  template <typename T> T get(std::string Name) const {
    if (!Parsed_)
      throw std::runtime_error(
          "Please do not query options before they are parsed");
    if (!Values_.count(Name))
      throw std::runtime_error("Option not present in list, use add");
    const auto &ValDesc = Values_.find(Name)->second;
    std::string Val = ValDesc.first;
    std::istringstream Is{Val};
    T Ret;
    Is >> Ret;
    return Ret;
  }

  void parse(int argc, char **argv) {
    for (int I = 1; I < argc; ++I) {
      std::string_view Optview = argv[I];
      auto TrimPos = Optview.find_first_not_of('-');
      Optview.remove_prefix(TrimPos);
      TrimPos = Optview.find('=');
      if (TrimPos != Optview.npos) {
        std::string_view Valview = Optview;
        Optview.remove_suffix(Optview.size() - TrimPos);
        Valview.remove_prefix(TrimPos + 1);
        std::string Val{Valview};
        std::string Opt{Optview};
        if (!Values_.count(Opt)) {
          std::cout << "option detected: " << Opt << " : " << Val << std::endl;
          throw std::runtime_error("Option not expected, rerun with -help");
        }
        Values_[Opt].first = Val;
      }

      if (Optview.find("help") != Optview.npos) {
        std::cout << "Available options:" << std::endl;
        for (auto &&X : Values_) {
          auto &Name = X.first;
          auto &ValDesc = X.second;
          std::cout << ("-" + Name) << "( = " << ValDesc.first
                    << ") : " << ValDesc.second << std::endl;
        }
        exit(0);
      }
    }
    Parsed_ = true;
  }

  bool parsed() const noexcept { return Parsed_; }
};