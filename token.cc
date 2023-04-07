#include "token.h"

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
  {"GRT Bus", Token::GRT_BUS},
  {"Tim Hortons", Token::TIM_HORTONS},
  {"Pink Tie", Token::PINK_TIE},
  {"Student", Token::STUDENT},
  {"Money", Token::MONEY},
  {"Laptop", Token::LAPTOP},
  {"Doughnut", Token::DOUGHNUT}
};

std::map<Token, std::string> tokenToStrMap = {
  {Token::GOOSE, "Goose"},
  {Token::GRT_BUS, "GRT Bus"},
  {Token::TIM_HORTONS, "Tim Hortons"},
  {Token::PINK_TIE, "Pink Tie"},
  {Token::STUDENT, "Student"},
  {Token::MONEY, "Money"},
  {Token::LAPTOP, "Laptop"},
  {Token::TIM_HORTONS, "Doughnut"}
};
