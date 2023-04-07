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

std::map<char, Token> charToTokenMap = {
  {'G', Token::GOOSE},
  {'B', Token::GRT_BUS},
  {'D', Token::TIM_HORTONS},
  {'P', Token::PINK_TIE},
  {'S', Token::STUDENT},
  {'$', Token::MONEY},
  {'L', Token::LAPTOP},
  {'T', Token::DOUGHNUT}
};

std::map<Token, char> tokenToCharMap = {
  {Token::GOOSE, 'G'},
  {Token::GRT_BUS, 'B'},
  {Token::TIM_HORTONS, 'D'},
  {Token::PINK_TIE, 'P'},
  {Token::STUDENT, 'S'},
  {Token::MONEY, '$'},
  {Token::LAPTOP, 'L'},
  {Token::TIM_HORTONS, 'T'}
};

std::map<std::string, Token> strToTokenMap = {
  {"Goose", Token::GOOSE},
  {"Grt_Bus", Token::GRT_BUS},
  {"Tim_Hortons", Token::TIM_HORTONS},
  {"Pink_Tie", Token::PINK_TIE},
  {"Student", Token::STUDENT},
  {"Money", Token::MONEY},
  {"Laptop", Token::LAPTOP},
  {"Doughnut", Token::DOUGHNUT}
};

std::map<Token, std::string> tokenToStrMap = {
  {Token::GOOSE, "Goose"},
  {Token::GRT_BUS, "Grt_Bus"},
  {Token::TIM_HORTONS, "Tim_Hortons"},
  {Token::PINK_TIE, "Pink_Tie"},
  {Token::STUDENT, "Student"},
  {Token::MONEY, "Money"},
  {Token::LAPTOP, "Laptop"},
  {Token::TIM_HORTONS, "Doughnut"}
};

#endif