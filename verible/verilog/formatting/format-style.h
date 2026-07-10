// Copyright 2017-2020 The Verible Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef VERIBLE_VERILOG_FORMATTING_FORMAT_STYLE_H_
#define VERIBLE_VERILOG_FORMATTING_FORMAT_STYLE_H_

#include <iosfwd>
#include <string>
#include <string_view>

#include "verible/common/formatting/align.h"
#include "verible/common/formatting/basic-format-style.h"

namespace verilog {
namespace formatter {

// Controls what breaks alignment groups for module items, statements,
// and class items.
enum class AlignmentGroupBoundary {
  // No additional group splitting (default, current behavior).
  kNone,
  // Blank lines break alignment groups.
  kBlankLines,
  // Separator comment lines (e.g., // ----) break alignment groups.
  kSeparatorComments,
  // Both blank lines and separator comments break alignment groups.
  kBlankLinesAndSeparatorComments,
};

std::ostream &operator<<(std::ostream &, AlignmentGroupBoundary);
bool AbslParseFlag(std::string_view text, AlignmentGroupBoundary *boundary,
                   std::string *error);
std::string AbslUnparseFlag(const AlignmentGroupBoundary &boundary);

// For named connection parentheses (ports and parameters), this enum controls
// the padding spacing behavior inside the parentheses
enum class ParenthesisPaddingPolicy {
  // Do not insert any spaces inside parentheses.
  kNone,

  // Insert a space after the open paren and before the close paren (e.g. `.clk(
  // sys_clk )`)
  kSpace,

  // Infer whether user wanted none or space padding, based on original spacing.
  kInferUserIntent,
};

std::ostream &operator<<(std::ostream &, ParenthesisPaddingPolicy);
bool AbslParseFlag(std::string_view text, ParenthesisPaddingPolicy *boundary,
                   std::string *error);
std::string AbslUnparseFlag(const ParenthesisPaddingPolicy &boundary);

// For sections of code where named connection are vertically aligned, this enum
// controls the alignment behavior of the closing parenthesis.
enum class ClosingParenthesisAlignment {
  // Keep the closing parenthesis tight against the end of the inner signal
  // name.
  kFlushLeft,

  // Vertically align closing parentheses to match a unified right column.
  kAlign,

  // Infer whether user wanted flush-left or aligned closing parentheses, based
  // on original spacing.
  kInferUserIntent,
};

std::ostream &operator<<(std::ostream &, ClosingParenthesisAlignment);
bool AbslParseFlag(std::string_view text, ClosingParenthesisAlignment *boundary,
                   std::string *error);
std::string AbslUnparseFlag(const ClosingParenthesisAlignment &boundary);

// Style parameters that are specific to Verilog formatter
struct FormatStyle : public verible::BasicFormatStyle {
  using AlignmentPolicy = verible::AlignmentPolicy;
  using IndentationStyle = verible::IndentationStyle;

  FormatStyle() { over_column_limit_penalty = 10000; }

  FormatStyle(const FormatStyle &) = default;

  /*
   * InitializeFromFlags() [format_style_init.h] provides flags that are
   * named like these fields and allow configuration on the command line.
   * So field foo here can be configured with flag --foo
   */

  // TODO(hzeller): some of these are plural, some singular. Come up with
  // a consistent scheme.

  // Control indentation amount for port declarations.
  IndentationStyle port_declarations_indentation = IndentationStyle::kWrap;

  // Control how named port_declaration (e.g. in modules, interfaces) are
  // formatted.  Internal tests assume these are forced to kAlign.
  AlignmentPolicy port_declarations_alignment = AlignmentPolicy::kAlign;

  // Control how struct and union members are formatted.
  AlignmentPolicy struct_union_members_alignment = AlignmentPolicy::kAlign;

  // Control indentation amount for named parameter assignments.
  IndentationStyle named_parameter_indentation = IndentationStyle::kWrap;

  // Control how named parameters (e.g. in module instances) are formatted.
  // For internal testing purposes, this is default to kAlign.
  AlignmentPolicy named_parameter_alignment = AlignmentPolicy::kAlign;

  // Control the spacing behavior inside the parentheses of named parameters.
  ParenthesisPaddingPolicy named_parameter_parenthesis_padding =
      ParenthesisPaddingPolicy::kInferUserIntent;

  // Control the alignment behavior of the closing parenthesis for vertically
  // aligned named parameter blocks.
  ClosingParenthesisAlignment named_parameter_closing_parenthesis =
      ClosingParenthesisAlignment::kInferUserIntent;

  // Control indentation amount for named port connections.
  IndentationStyle named_port_indentation = IndentationStyle::kWrap;

  // Control how named ports (e.g. in module instances) are formatted.
  // Internal tests assume these are forced to kAlign.
  AlignmentPolicy named_port_alignment = AlignmentPolicy::kAlign;

  // Control the spacing behavior inside the parentheses of named ports.
  ParenthesisPaddingPolicy named_port_parenthesis_padding =
      ParenthesisPaddingPolicy::kInferUserIntent;

  // Control the alignment behavior of the closing parenthesis for vertically
  // aligned named port blocks.
  ClosingParenthesisAlignment named_port_closing_parenthesis =
      ClosingParenthesisAlignment::kInferUserIntent;

  // Control how module-local net/variable declarations are formatted.
  // Internal tests assume these are forced to kAlign.
  AlignmentPolicy module_net_variable_alignment = AlignmentPolicy::kAlign;

  // Control how various assignment statements should be aligned.
  // This covers: continuous assignment statements,
  // blocking, and nonblocking assignments.
  // Internal tests assume these are forced to kAlign.
  AlignmentPolicy assignment_statement_alignment = AlignmentPolicy::kAlign;

  // Assignment within enumerations.
  AlignmentPolicy enum_assignment_statement_alignment = AlignmentPolicy::kAlign;

  // Control indentation amount for formal parameter declarations.
  IndentationStyle formal_parameters_indentation = IndentationStyle::kWrap;

  // Control how formal parameters in modules/interfaces/classes are formatted.
  // Internal tests assume these are forced to kAlign.
  AlignmentPolicy formal_parameters_alignment = AlignmentPolicy::kAlign;

  // Control how class member variables are formatted.
  // Internal tests assume these are forced to kAlign.
  AlignmentPolicy class_member_variable_alignment = AlignmentPolicy::kAlign;

  // Control how case items are formatted.
  // Internal tests assume these are forced to kAlign.
  AlignmentPolicy case_items_alignment = AlignmentPolicy::kAlign;

  // Control how distribution items are formatted.
  // Internal tests assume these are forced to kAlign.
  AlignmentPolicy distribution_items_alignment = AlignmentPolicy::kAlign;

  bool port_declarations_right_align_packed_dimensions = false;
  bool port_declarations_right_align_unpacked_dimensions = false;

  // Controls what breaks alignment groups for module items, statements,
  // and class items.
  AlignmentGroupBoundary alignment_group_boundary =
      AlignmentGroupBoundary::kNone;

  // At this time line wrap optimization is problematic and risks ruining
  // otherwise reasonable code.  When set to false, this switch will make the
  // formatter give-up and leave code as-is in cases where it would otherwise
  // attempt to do line wrap optimization.  By doing nothing in those cases, we
  // reduce the risk of harming already decent code.
  bool try_wrap_long_lines = true;
  bool expand_coverpoints = true;

  // Compact binary expressions inside indexing / bit selection operators
  bool compact_indexing_and_selections = true;

  // Split with a \n end and else clauses
  bool wrap_end_else_clauses = false;

  // -- Note: when adding new fields, add them in format_style_init.cc

  // TODO(fangism): introduce the following knobs:
  //
  // Unless forced by previous line, starting a line with a comma is
  // generally discouraged.
  // int break_before_separator_penalty = 20;

  // TODO(fangism): parameter to limit number of consecutive blank lines to
  // preserve between partitions.

  int PortDeclarationsIndentation() const {
    return port_declarations_indentation == IndentationStyle::kWrap
               ? wrap_spaces
               : indentation_spaces;
  }

  int FormalParametersIndentation() const {
    return formal_parameters_indentation == IndentationStyle::kWrap
               ? wrap_spaces
               : indentation_spaces;
  }

  int NamedParameterIndentation() const {
    return named_parameter_indentation == IndentationStyle::kWrap
               ? wrap_spaces
               : indentation_spaces;
  }

  int NamedPortIndentation() const {
    return named_port_indentation == IndentationStyle::kWrap
               ? wrap_spaces
               : indentation_spaces;
  }

  void ApplyToAllAlignmentPolicies(AlignmentPolicy policy) {
    port_declarations_alignment = policy;
    named_parameter_alignment = policy;
    named_port_alignment = policy;
    module_net_variable_alignment = policy;
    formal_parameters_alignment = policy;
    class_member_variable_alignment = policy;
    case_items_alignment = policy;
    assignment_statement_alignment = policy;
    enum_assignment_statement_alignment = policy;
    distribution_items_alignment = policy;
  }
};

}  // namespace formatter
}  // namespace verilog

#endif  // VERIBLE_VERILOG_FORMATTING_FORMAT_STYLE_H_
