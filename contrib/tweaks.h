#ifndef SOURCEMETA_BLAZE_CONTRIB_TWEAKS_H_
#define SOURCEMETA_BLAZE_CONTRIB_TWEAKS_H_

#include <sourcemeta/blaze/compiler.h>

#include <sourcemeta/core/options.h>

#include <optional> // std::optional
#include <ostream>  // std::ostream

// The evaluator ports borrow this compiler rather than carrying one of their
// own, so every knob a test fixture can ask for has to be reachable from the
// command line. Registering them in one place is what keeps the tools that
// offer them from drifting apart
inline auto register_tweak_options(sourcemeta::core::Options &options) -> void {
  options.flag("format-assertion", {});
  options.option("annotations", {});
  options.flag("no-annotations", {});
}

// An allowlist that is present but empty does not mean the same as no
// allowlist: the first says to emit no annotation at all, while the second
// leaves the choice to the compilation mode. An option carries no values of
// its own to tell those apart, so the empty case needs a flag to survive the
// trip
inline auto tweaks_from_options(const sourcemeta::core::Options &options,
                                std::ostream &log)
    -> std::optional<sourcemeta::blaze::Tweaks> {
  std::optional<sourcemeta::blaze::Tweaks> tweaks;

  if (options.contains("format-assertion")) {
    tweaks.emplace().format_assertion = true;
    log << "Tweak: format assertion\n";
  }

  if (options.contains("annotations") || options.contains("no-annotations")) {
    if (!tweaks.has_value()) {
      tweaks.emplace();
    }

    // The set holds views, so these have to point at what the options own
    // rather than at a copy that dies with this scope
    auto &keywords{tweaks.value().annotations.emplace()};
    if (options.contains("annotations")) {
      for (const auto &keyword : options.at("annotations")) {
        keywords.emplace(keyword);
        log << "Tweak: annotation " << keyword << "\n";
      }
    } else {
      log << "Tweak: no annotations\n";
    }
  }

  return tweaks;
}

#endif
