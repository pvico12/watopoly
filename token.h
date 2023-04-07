#ifndef TOKEN_H
#define TOKEN_H

#include <map>

enum class Token {
  GOOSE,
  GRT_BUS,
  TIM_HORTONS,
  DOUGHNUT,
  PROFESSOR,
  STUDENT,
  MONEY,
  LAPTOP,
  PINK_TIE
};

std::map<char, Token> tokenCharMap = {
  {'G', Token::GOOSE},
  {'B', Token::GRT_BUS},
  {'D', Token::TIM_HORTONS},
  {'P', Token::PINK_TIE},
  {'S', Token::STUDENT},
  {'$', Token::MONEY},
  {'L', Token::LAPTOP},
  {'T', Token::DOUGHNUT}
};

#endif