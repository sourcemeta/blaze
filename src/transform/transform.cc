#include <sourcemeta/blaze/transform.h>

// The interpreter is split by the halves of a rule it reads, a pattern that
// says what a term has to look like and a build that says what becomes of it
#include "transform_match.h"

#include "transform_build.h"
