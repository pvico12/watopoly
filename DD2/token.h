#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <map>

enum class Token {
  GOOSE,
  GRT_BUS,
  TIM_HORTONS_DOUGHNUT,
  PROFESSOR,
  STUDENT,
  MONEY,
  LAPTOP,
  PINK_TIE
};

extern std::map<char, Token> charToTokenMap;

extern std::map<Token, char> tokenToCharMap;

extern std::map<std::string, Token> strToTokenMap;

extern std::map<Token, std::string> tokenToStrMap;

#endif
