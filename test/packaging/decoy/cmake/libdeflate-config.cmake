# This prefix stands in for the ones that real consumers have on their search
# path, such as a Conda environment or a Homebrew installation, which ship
# packages under the same generic names that this project vendors. Blaze
# installs its own copy of every one of them, so resolving this file instead
# means a config file is searching by name rather than next to itself
message(FATAL_ERROR
  "Resolved the unrelated system 'libdeflate' package instead of the one Blaze installed")
