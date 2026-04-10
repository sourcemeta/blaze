#include <gtest/gtest.h>

#include <sourcemeta/blaze/alterschema.h>
#include <sourcemeta/core/json.h>

#include <memory> // std::unique_ptr

#include "alterschema_transform_rules.h"

TEST(AlterSchema_transform_rule, instances_of_same_rule_are_equal) {
  const ExampleRule1 foo{};
  const ExampleRule1 bar{};
  EXPECT_EQ(foo, bar);
}

TEST(AlterSchema_transform_rule,
     instances_of_same_rule_are_equal_with_unique_ptr) {
  const std::unique_ptr<ExampleRule1> foo{};
  const std::unique_ptr<ExampleRule1> bar{};
  EXPECT_EQ(foo, bar);
}

TEST(AlterSchema_transform_rule, instances_of_different_rules_are_different) {
  const ExampleRule1 foo{};
  const ExampleRule2 bar{};
  EXPECT_NE(foo, bar);
}

TEST(AlterSchema_transform_rule, rule_message) {
  const ExampleRule7 rule{};
  EXPECT_EQ(rule.message(), "My custom message");
}
