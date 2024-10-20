/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by wangyunlai on 2021/6/11.
//

#include "common/defs.h"
#include <regex>
#include <string.h>

#include "common/lang/algorithm.h"

namespace common {

int compare_int(void *arg1, void *arg2)
{
  int v1 = *(int *)arg1;
  int v2 = *(int *)arg2;
  if (v1 > v2) {
    return 1;
  } else if (v1 < v2) {
    return -1;
  } else {
    return 0;
  }
}

int compare_float(void *arg1, void *arg2)
{
  float v1  = *(float *)arg1;
  float v2  = *(float *)arg2;
  float cmp = v1 - v2;
  if (cmp > EPSILON) {
    return 1;
  }
  if (cmp < -EPSILON) {
    return -1;
  }
  return 0;
}

int compare_string(void *arg1, int arg1_max_length, void *arg2, int arg2_max_length)
{
  const char *s1     = (const char *)arg1;
  const char *s2     = (const char *)arg2;
  int         maxlen = min(arg1_max_length, arg2_max_length);
  int         result = strncmp(s1, s2, maxlen);
  if (0 != result) {
    return result < 0 ? -1 : 1;
  }

  if (arg1_max_length > maxlen) {
    return 1;
  }

  if (arg2_max_length > maxlen) {
    return -1;
  }
  return 0;
}

int compare_string_like(void *arg1, int arg1_max_length, void *arg2, int arg2_max_length)
{
  const char *s2 = (const char *)arg2;

  // Convert the SQL LIKE pattern to a regex pattern
  std::string pattern(s2, arg2_max_length);
  std::string regex_pattern;
  regex_pattern.reserve(pattern.size());
  regex_pattern += "^";

  for (char c : pattern) {
    if (c == '%') {
      regex_pattern += "[^']*";
    } else if (c == '_') {
      regex_pattern += "[^']";
    } else {
      regex_pattern += std::regex_replace(std::string(1, c), std::regex(R"([\^$.|?*+(){}\\])"), R"(\\$&)");
    }
  }
  regex_pattern += "$";

  std::regex  re(regex_pattern);
  std::string str((const char *)arg1, arg1_max_length);

  if (std::regex_match(str, re)) {
    return 0;
  } else {
    return -1;
  }
}

}  // namespace common
