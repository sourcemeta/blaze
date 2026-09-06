# Stands in for a Core that a consumer already has on its search path, at a
# version that has nothing to do with the one Blaze bundles. Blaze installs its
# own copy next to its own config file, so resolving this one instead means
# that config searched by name rather than next to itself
message(FATAL_ERROR
  "Resolved the unrelated system 'core' package instead of the one Blaze installed")
