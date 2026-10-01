#include <sourcemeta/blaze/documentation.h>

#include <sourcemeta/core/json.h>

#include <cassert>     // assert
#include <cctype>      // std::tolower
#include <cstddef>     // std::size_t
#include <cstdint>     // std::uint32_t
#include <map>         // std::map
#include <sstream>     // std::ostringstream
#include <string>      // std::string
#include <string_view> // std::string_view
#include <utility>     // std::move
#include <vector>      // std::vector

// This renderer reads the table format and nothing else, so it draws a page for
// a schema of any language that was converted into it. It supplies its own
// wording: the format holds facts, not sentences.

namespace {

using sourcemeta::core::JSON;

// A small writer, so that the page is a plain fragment with no styling of its
// own and the module carries no further dependency.
class Page {
public:
  auto open(const std::string_view tag) -> Page & {
    this->output_ += '<';
    this->output_ += tag;
    this->output_ += '>';
    this->stack_.emplace_back(tag);
    return *this;
  }

  auto open(const std::string_view tag, const std::string_view attribute,
            const std::string_view value) -> Page & {
    this->output_ += '<';
    this->output_ += tag;
    this->output_ += ' ';
    this->output_ += attribute;
    this->output_ += "=\"";
    this->escape(value);
    this->output_ += "\">";
    this->stack_.emplace_back(tag);
    return *this;
  }

  auto close() -> Page & {
    assert(!this->stack_.empty());
    this->output_ += "</";
    this->output_ += this->stack_.back();
    this->output_ += '>';
    this->stack_.pop_back();
    return *this;
  }

  auto text(const std::string_view content) -> Page & {
    this->escape(content);
    return *this;
  }

  auto cell(const std::string_view tag, const std::string_view content)
      -> Page & {
    this->open(tag);
    this->escape(content);
    return this->close();
  }

  [[nodiscard]] auto str() const -> const std::string & {
    return this->output_;
  }

private:
  auto escape(const std::string_view content) -> void {
    for (const auto character : content) {
      switch (character) {
        case '&':
          this->output_ += "&amp;";
          break;
        case '<':
          this->output_ += "&lt;";
          break;
        case '>':
          this->output_ += "&gt;";
          break;
        case '"':
          this->output_ += "&quot;";
          break;
        default:
          this->output_ += character;
      }
    }
  }

  std::string output_;
  std::vector<std::string> stack_;
};

auto text_of(const JSON &value, const std::string &key) -> std::string {
  if (value.is_object() && value.defines(key) && value.at(key).is_string()) {
    return value.at(key).to_string();
  }

  return "";
}

auto kind_of(const JSON &value) -> std::string {
  if (value.is_object() && value.defines("kind")) {
    return value.at("kind").to_string();
  }

  return "any";
}

// A shape identifier is opaque, so two that read alike must still get two
// anchors: what an anchor cannot hold becomes a dash, and when that loses
// something, a short mark of the identifier itself is added.
auto tidy(std::string_view identifier) -> std::string {
  std::string result;
  auto dash{false};
  for (const auto character : identifier) {
    const auto plain{(character >= 'a' && character <= 'z') ||
                     (character >= 'A' && character <= 'Z') ||
                     (character >= '0' && character <= '9')};
    if (plain) {
      if (dash && !result.empty()) {
        result += '-';
      }

      dash = false;
      result += character;
    } else {
      dash = true;
    }
  }

  return result;
}

auto mark(std::string_view identifier) -> std::string {
  std::uint32_t hash{0x811c9dc5};
  for (const auto character : identifier) {
    hash ^= static_cast<std::uint32_t>(static_cast<unsigned char>(character));
    hash *= 0x01000193;
  }

  std::string result;
  while (hash > 0) {
    const auto digit{hash % 36};
    result += static_cast<char>(digit < 10 ? '0' + digit : 'a' + digit - 10);
    hash /= 36;
  }

  return result.empty() ? "0" : result;
}

auto anchor(std::string_view identifier) -> std::string {
  if (identifier.empty()) {
    return "root";
  }

  const auto readable{tidy(identifier)};
  if (readable == identifier) {
    return "shape-" + readable;
  }

  return "shape-" + readable + "-" + mark(identifier);
}

// Whether an address from a schema is one a reader can be invited to follow.
// Anything else is written out rather than linked.
auto followable(const std::string_view address) -> bool {
  // A browser throws away tabs, newlines and control characters before it
  // reads an address, so they are thrown away here too. Otherwise an address
  // written as "java\tscript:" would pass a test that "javascript:" fails.
  std::string plain;
  plain.reserve(address.size());
  for (const auto character : address) {
    if (static_cast<unsigned char>(character) > 0x20 &&
        static_cast<unsigned char>(character) != 0x7f) {
      plain += character;
    }
  }

  const auto colon{plain.find(':')};
  const auto slash{plain.find('/')};
  if (colon == std::string::npos ||
      (slash != std::string::npos && slash < colon)) {
    // No scheme of its own, so it is read against the page it sits in.
    return !plain.starts_with("//");
  }

  auto scheme{plain.substr(0, colon)};
  for (auto &character : scheme) {
    character =
        static_cast<char>(std::tolower(static_cast<unsigned char>(character)));
  }

  return scheme == "http" || scheme == "https" || scheme == "mailto";
}

auto plain(const JSON &value) -> std::string {
  if (value.is_string()) {
    return value.to_string();
  }

  if (value.is_boolean()) {
    return value.to_boolean() ? "yes" : "no";
  }

  if (value.is_null()) {
    return "nothing";
  }

  if (value.is_integer()) {
    return std::to_string(value.to_integer());
  }

  if (value.is_real()) {
    std::ostringstream number;
    number << value.to_real();
    return number.str();
  }

  // A reader is not shown JSON, so a value with parts of its own is named
  // rather than written out.
  return value.is_array() ? "a list of values" : "a group of fields";
}

auto number_of(const JSON &value) -> std::string { return plain(value); }

// What a reader calls each kind.
auto word_for(const std::string &kind) -> std::string {
  static const std::map<std::string, std::string> WORDS{
      {"string", "text"},
      {"number", "a number"},
      {"integer", "a whole number"},
      {"boolean", "yes or no"},
      {"null", "nothing"},
      {"object", "a group of fields"},
      {"array", "a list"},
      {"enum", "one of a few values"},
      {"choice", "one of several forms"},
      {"ref", "another shape"},
      {"external", "something described elsewhere"},
      {"any", "anything"},
      {"never", "nothing at all"}};
  const auto match{WORDS.find(kind)};
  return match == WORDS.cend() ? kind : match->second;
}

struct Names {
  std::map<std::string, std::string> shapes;
};

auto name_of(const Names &names, const std::string &identifier) -> std::string {
  if (identifier.empty()) {
    return "this whole document";
  }

  const auto match{names.shapes.find(identifier)};
  return match == names.shapes.cend() ? identifier : match->second;
}

auto notes_of(const JSON &value) -> std::vector<std::string>;

auto summary_of(const JSON &value, const Names &names) -> std::string {
  const auto kind{kind_of(value)};
  if (kind == "ref") {
    return name_of(names, value.at("ref").to_string());
  }

  auto result{word_for(kind)};
  if (kind == "enum" && value.defines("values")) {
    result = "one of ";
    const auto &values{value.at("values")};
    for (std::size_t index = 0; index < values.array_size(); index++) {
      if (index > 0) {
        result += index + 1 == values.array_size() ? " or " : ", ";
      }

      result += plain(values.at(index));
    }
  }

  if (value.defines("nullable")) {
    result += ", or nothing";
  }

  return result;
}

auto notes_of(const JSON &value) -> std::vector<std::string> {
  std::vector<std::string> notes;
  if (!value.is_object()) {
    return notes;
  }

  if (value.defines("format")) {
    notes.emplace_back("written as " + value.at("format").to_string());
  }

  if (value.defines("pattern")) {
    notes.emplace_back("matches " + value.at("pattern").to_string());
  }

  if (value.defines("length")) {
    const auto &length{value.at("length")};
    if (length.defines("min") && length.defines("max")) {
      notes.emplace_back("between " + number_of(length.at("min")) + " and " +
                         number_of(length.at("max")) + " long");
    } else if (length.defines("min")) {
      notes.emplace_back("at least " + number_of(length.at("min")) + " long");
    } else if (length.defines("max")) {
      notes.emplace_back("at most " + number_of(length.at("max")) + " long");
    }
  }

  if (value.defines("range")) {
    const auto &range{value.at("range")};
    if (range.defines("min")) {
      notes.emplace_back((range.defines("minExclusive") ? "above " : "from ") +
                         number_of(range.at("min")));
    }

    if (range.defines("max")) {
      notes.emplace_back((range.defines("maxExclusive") ? "below " : "up to ") +
                         number_of(range.at("max")));
    }
  }

  if (value.defines("multipleOf")) {
    notes.emplace_back("a multiple of " + number_of(value.at("multipleOf")));
  }

  if (value.defines("unique")) {
    notes.emplace_back("no two entries the same");
  }

  if (value.defines("fieldCount")) {
    const auto &count{value.at("fieldCount")};
    if (count.defines("min") && count.defines("max")) {
      notes.emplace_back("between " + number_of(count.at("min")) + " and " +
                         number_of(count.at("max")) + " fields");
    } else if (count.defines("min")) {
      notes.emplace_back("at least " + number_of(count.at("min")) + " fields");
    } else if (count.defines("max")) {
      notes.emplace_back("at most " + number_of(count.at("max")) + " fields");
    }
  }

  if (value.defines("keys")) {
    const auto &keys{value.at("keys")};
    if (keys.is_object() && keys.defines("pattern")) {
      notes.emplace_back("every field is named like " +
                         keys.at("pattern").to_string());
    } else {
      notes.emplace_back("the field names are limited");
    }
  }

  if (value.defines("contains")) {
    const auto &contains{value.at("contains")};
    auto note{std::string{"holds "}};
    if (contains.defines("min")) {
      note += "at least " + number_of(contains.at("min")) + " ";
    }

    if (contains.defines("max")) {
      note += "and at most " + number_of(contains.at("max")) + " ";
    }

    notes.emplace_back(note + "of one kind of entry");
  }

  if (value.defines("slots")) {
    notes.emplace_back("the first " +
                       std::to_string(value.at("slots").array_size()) +
                       " entries are each described on their own");
  }

  if (value.defines("discriminator")) {
    notes.emplace_back("the field " +
                       value.at("discriminator").at("field").to_string() +
                       " says which shape the rest follows");
  }

  if (value.defines("otherTypesAllowed")) {
    notes.emplace_back("data of another type passes these rules too");
  }

  if (value.defines("closed")) {
    notes.emplace_back("no other fields");
  }

  if (value.defines("deprecated")) {
    notes.emplace_back("no longer used");
  }

  if (value.defines("access")) {
    notes.emplace_back(value.at("access").to_string() == "read"
                           ? "supplied for you to read"
                           : "written by you, never returned");
  }

  if (value.defines("default")) {
    notes.emplace_back("defaults to " + plain(value.at("default")));
  }

  if (value.defines("examples") && value.at("examples").array_size() > 0) {
    notes.emplace_back("for example " + plain(value.at("examples").at(0)));
  }

  if (value.defines("conditions")) {
    notes.emplace_back("has rules that apply in some cases");
  }

  if (value.defines("not")) {
    notes.emplace_back("must not match one form");
  }

  return notes;
}

auto write_value_cell(Page &html, const JSON &value, const Names &names)
    -> void {
  const auto kind{kind_of(value)};
  // A list of one shape reads better as the shape it holds.
  if (kind == "array" && value.is_object() && value.defines("item") &&
      kind_of(value.at("item")) == "ref") {
    html.text("a list of ");
    html.open("a", "href",
              "#" + anchor(value.at("item").at("ref").to_string()));
    html.text(name_of(names, value.at("item").at("ref").to_string()));
    html.close();
    return;
  }

  if (kind == "ref") {
    html.open("a", "href", "#" + anchor(value.at("ref").to_string()));
    html.text(summary_of(value, names));
    html.close();
    return;
  }

  if (kind == "external") {
    const auto where{text_of(value, "href")};
    if (followable(where)) {
      html.open("a", "href", where);
      html.text("described elsewhere");
      html.close();
    } else {
      // An address a reader should not be invited to follow is shown as the
      // text it is.
      html.text("described elsewhere, at " + where);
    }

    return;
  }

  html.text(summary_of(value, names));
}

auto write_notes_cell(Page &html, const JSON &value) -> void {
  const auto notes{notes_of(value)};
  for (std::size_t index = 0; index < notes.size(); index++) {
    if (index > 0) {
      html.text("; ");
    }

    html.text(notes.at(index));
  }
}

auto write_fields(Page &html, const JSON &value, const Names &names) -> void {
  html.open("table", "class", "sourcemeta-blaze-documentation");
  html.open("tr");
  html.cell("th", "Field");
  html.cell("th", "What may go in it");
  html.cell("th", "Required");
  html.cell("th", "Notes");
  html.close();

  if (value.is_object() && value.defines("fields")) {
    for (const auto &field : value.at("fields").as_array()) {
      html.open("tr");
      html.open("td");
      html.cell("code", field.at("name").to_string());
      html.close();
      html.open("td");
      if (field.defines("value")) {
        write_value_cell(html, field.at("value"), names);
      } else if (value.defines("otherFields")) {
        // Nothing is said about this name, so the rule for every other field
        // is what holds.
        write_value_cell(html, value.at("otherFields"), names);
      } else if (value.defines("closed")) {
        html.text("not described here");
      } else {
        html.text("anything");
      }

      html.close();
      html.cell("td", field.defines("required") ? "yes" : "no");
      html.open("td");
      if (field.defines("value")) {
        write_notes_cell(html, field.at("value"));
      }

      html.close();
      html.close();
    }
  }

  if (value.is_object() && value.defines("patternFields")) {
    for (const auto &entry : value.at("patternFields").as_array()) {
      html.open("tr");
      html.open("td");
      html.text("every field named like ");
      html.cell("code", entry.at("pattern").to_string());
      html.close();
      html.open("td");
      write_value_cell(html, entry.at("value"), names);
      html.close();
      html.cell("td", "no");
      html.open("td");
      write_notes_cell(html, entry.at("value"));
      html.close();
      html.close();
    }
  }

  if (value.is_object() && value.defines("otherFields")) {
    html.open("tr");
    html.cell("td", "every other field");
    html.open("td");
    write_value_cell(html, value.at("otherFields"), names);
    html.close();
    html.cell("td", "no");
    html.open("td");
    write_notes_cell(html, value.at("otherFields"));
    html.close();
    html.close();
  }

  html.close();
}

auto write_rest(Page &html, const JSON &value, const Names &names) -> void;

auto write_body(Page &html, const JSON &value, const Names &names) -> void {
  const auto kind{kind_of(value)};
  // A value that says nothing of its own beyond one further rule reads better
  // as that rule.
  if (kind == "any" && value.is_object() && value.defines("also") &&
      value.at("also").array_size() == 1 && value.size() == 2) {
    write_body(html, value.at("also").at(0), names);
    return;
  }

  if (kind == "object") {
    write_fields(html, value, names);
    write_rest(html, value, names);
    return;
  }

  if (kind == "array" && value.is_object() && value.defines("item") &&
      kind_of(value.at("item")) == "object") {
    html.cell("p", "Every entry of the list holds these fields.");
    write_fields(html, value.at("item"), names);
    write_rest(html, value, names);
    return;
  }

  const auto says_more{value.is_object() &&
                       (value.defines("also") || value.defines("options") ||
                        value.defines("not") || value.defines("conditions"))};
  if (!(kind == "any" && says_more)) {
    html.open("p");
    html.text("Holds ");
    write_value_cell(html, value, names);
    html.text(".");
    html.close();
  }

  write_rest(html, value, names);
}

// The rules a table of fields does not show: the notes, the forms a value may
// take, and everything it must also match.
auto write_rest(Page &html, const JSON &value, const Names &names) -> void {
  const auto notes{notes_of(value)};
  if (!notes.empty()) {
    html.open("p");
    write_notes_cell(html, value);
    html.close();
  }

  if (!value.is_object()) {
    return;
  }

  if (value.defines("options")) {
    html.cell("p", value.defines("overlap")
                       ? "It may take these forms, and at least one holds:"
                       : "It takes exactly one of these forms:");
    html.open("ul");
    for (const auto &option : value.at("options").as_array()) {
      html.open("li");
      write_value_cell(html, option, names);
      const auto option_notes{notes_of(option)};
      if (!option_notes.empty()) {
        html.text(", ");
        write_notes_cell(html, option);
      }

      html.close();
    }

    html.close();
  }

  if (value.defines("also")) {
    html.cell("p", "It must also match:");
    html.open("ul");
    for (const auto &other : value.at("also").as_array()) {
      html.open("li");
      write_value_cell(html, other, names);
      write_rest(html, other, names);
      html.close();
    }

    html.close();
  }

  if (value.defines("not")) {
    html.open("p");
    html.text("It must not be ");
    write_value_cell(html, value.at("not"), names);
    html.text(".");
    html.close();
  }
}

} // namespace

namespace sourcemeta::blaze {

auto to_html(const sourcemeta::core::JSON &documentation) -> std::string {
  Page html;
  Names names;
  if (documentation.is_object() && documentation.defines("shapes")) {
    for (const auto &shape : documentation.at("shapes").as_array()) {
      auto name{text_of(shape, "name")};
      if (shape.defines("value")) {
        const auto title{text_of(shape.at("value"), "title")};
        if (!title.empty()) {
          name = title;
        }
      }

      names.shapes.emplace(shape.at("id").to_string(), std::move(name));
    }
  }

  html.open("div", "class", "sourcemeta-blaze-documentation");
  html.cell("h1", text_of(documentation, "title"));
  const auto description{text_of(documentation, "description")};
  if (!description.empty()) {
    html.cell("p", description);
  }

  html.open("section", "id", anchor(""));
  html.cell("h2", "What this file holds");
  if (documentation.is_object() && documentation.defines("root")) {
    write_body(html, documentation.at("root"), names);
  }

  html.close();

  if (documentation.is_object() && documentation.defines("shapes")) {
    for (const auto &shape : documentation.at("shapes").as_array()) {
      html.open("section", "id", anchor(shape.at("id").to_string()));
      html.cell("h2", name_of(names, shape.at("id").to_string()));
      const auto &value{shape.at("value")};
      const auto shape_description{text_of(value, "description")};
      if (!shape_description.empty()) {
        html.cell("p", shape_description);
      }

      write_body(html, value, names);
      html.close();
    }
  }

  html.close();
  return html.str();
}

} // namespace sourcemeta::blaze
