#ifndef UTIL_UTIL_H
#define UTIL_UTIL_H

#include <string>
#include <vector>

std::vector<std::string> parse(const std::string str, const std::string delim) {
  char *c_str = strdup(str.c_str());
  const char *d = delim.c_str();
  char *token;

  std::vector<std::string> tokens;

  token = strtok(c_str, d);
  while (token != NULL) {
    std::string token_str(token);
    tokens.push_back(token_str);

    token = strtok(NULL, d);
  }

  free(c_str);
  return tokens;
}

#endif // UTIL_UTIL_H