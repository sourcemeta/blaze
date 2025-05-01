#ifndef SOURCEMETA_BLAZE_COMPILER_TEST_UTILS_H_
#define SOURCEMETA_BLAZE_COMPILER_TEST_UTILS_H_

#define TO_POINTER(pointer_string)                                             \
  sourcemeta::core::to_pointer((pointer_string))

#define EXPECT_UNEVALUATED_STATIC(keywords, expected_pointer,                  \
                                  expected_dependencies_size)                  \
  EXPECT_EQ(keywords.at(expected_pointer).static_dependencies.size(),          \
            expected_dependencies_size);

#define EXPECT_UNEVALUATED_DYNAMIC(keywords, expected_pointer,                 \
                                   expected_dependencies_size)                 \
  EXPECT_EQ(keywords.at(expected_pointer).dynamic_dependencies.size(),         \
            expected_dependencies_size);

#define EXPECT_UNEVALUATED_UNRESOLVED(keywords, expected_pointer)              \
  EXPECT_TRUE(keywords.at(expected_pointer).unresolved);

#define EXPECT_UNEVALUATED_RESOLVED(keywords, expected_pointer)                \
  EXPECT_FALSE(keywords.at(expected_pointer).unresolved);

#define EXPECT_UNEVALUATED_STATIC_DEPENDENCY(keywords, expected_pointer,       \
                                             expected_destination)             \
  EXPECT_TRUE(                                                                 \
      keywords.at(expected_pointer)                                            \
          .static_dependencies.contains(TO_POINTER(expected_destination)));

#define EXPECT_UNEVALUATED_DYNAMIC_DEPENDENCY(keywords, expected_pointer,      \
                                              expected_destination)            \
  EXPECT_TRUE(                                                                 \
      keywords.at(expected_pointer)                                            \
          .dynamic_dependencies.contains(TO_POINTER(expected_destination)));

#endif
