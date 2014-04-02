//===--- LangOptions.h - Language & configuration options -------*- C++ -*-===//
//
// This source file is part of the Swift.org open source project
//
// Copyright (c) 2014 - 2015 Apple Inc. and the Swift project authors
// Licensed under Apache License v2.0 with Runtime Library Exception
//
// See http://swift.org/LICENSE.txt for license information
// See http://swift.org/CONTRIBUTORS.txt for the list of Swift project authors
//
//===----------------------------------------------------------------------===//
//
//  This file defines the LangOptions class, which provides various
//  language and configuration flags.
//
//===----------------------------------------------------------------------===//

#ifndef SWIFT_LANGOPTIONS_H
#define SWIFT_LANGOPTIONS_H

#include "swift/Basic/LLVM.h"
#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/StringRef.h"
#include <string>

namespace swift {
  /// \brief A collection of options that affect the language dialect and
  /// provide compiler debugging facilities.
  class LangOptions {
  public:
    
    /// \brief Whether we are debugging the constraint solver.
    ///
    /// This option enables verbose debugging output from the constraint
    /// solver.
    bool DebugConstraintSolver = false;

    /// \brief Specific solution attempt for which the constraint
    /// solver should be debugged.
    unsigned DebugConstraintSolverAttempt = 0;

    /// \brief Perform all dynamic allocations using malloc/free instead of
    /// optimized custom allocator, so that memory debugging tools can be used.
    bool UseMalloc = false;
    
    /// \brief Enable experimental "switch" pattern-matching features.
    bool EnableExperimentalPatterns = false;

    /// \brief Enable features useful for running in the debugger.
    bool DebuggerSupport = false;

    /// \brief Keep comments during lexing and attach them to declarations.
    bool AttachCommentsToDecls = false;

    /// Enable 'availability' restrictions for App Extensions.
    bool EnableAppExtensionRestrictions = false;

    // Mangle @objc class and protocol names?
    // Note: this is *almost* an IRGen-only option, except that it affects
    // the headers we generate for Objective-C interoperability. 
    // FIXME: This option will eventually default to 'true' and go away.
    bool MangleObjCClassProtocolNames = false;

    /// Whether to split imported Objective-C selectors into Swift method names.
    bool SplitPrepositions = false;
    
    /// Implicit target configuration options.  There are currently two
    ///   supported target configuration values:
    ///     os - The active os target (OSX or IOS)
    ///     arch - The active arch target (X64, I386, ARM, ARM64)
    void addTargetConfigOption(StringRef Name, StringRef Value) {
      assert(!Name.empty() && !Value.empty());
      TargetConfigOptions.push_back(std::make_pair(Name, Value));
    }
    
    /// Returns the value for the given target configuration or an empty string.
    StringRef getTargetConfigOption(StringRef Name);
    
    /// Explicit build configuration options, initialized via the '-D'
    /// compiler flag.
    void addBuildConfigOption(StringRef Name) {
      assert(!Name.empty());
      BuildConfigOptions.push_back(Name);
    }

    /// Determines if a given build configuration has been defined.
    bool hasBuildConfigOption(StringRef Name);

    ArrayRef<std::pair<std::string, std::string>>
        getTargetConfigOptions() const {
      return TargetConfigOptions;
    }

  private:
    llvm::SmallVector<std::pair<std::string, std::string>, 2>
        TargetConfigOptions; 
    llvm::SmallVector<std::string, 2> BuildConfigOptions; 
  };
}

#endif // LLVM_SWIFT_LANGOPTIONS_H

