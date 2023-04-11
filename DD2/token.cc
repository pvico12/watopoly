#include "token.h"

std::map<char, Token> charToTokenMap = {
  {'G', Token::GOOSE},
  {'B', Token::GRT_BUS},
  {'D', Token::TIM_HORTONS_DOUGHNUT},
  {'P', Token::PROFESSOR},
  {'S', Token::STUDENT},
  {'$', Token::MONEY},
  {'L', Token::LAPTOP},
  {'T', Token::PINK_TIE}
};

std::map<Token, char> tokenToCharMap = {
  {Token::GOOSE, 'G'},
  {Token::GRT_BUS, 'B'},
  {Token::TIM_HORTONS_DOUGHNUT, 'D'},
  {Token::PROFESSOR, 'P'},
  {Token::STUDENT, 'S'},
  {Token::MONEY, '$'},
  {Token::LAPTOP, 'L'},
  {Token::PINK_TIE, 'T'}
};

std::map<std::string, Token> strToTokenMap = {
  {"Goose", Token::GOOSE},
  {"GRT Bus", Token::GRT_BUS},
  {"Tim Hortons Doughnut", Token::TIM_HORTONS_DOUGHNUT},
  {"Professor", Token::PROFESSOR},
  {"Student", Token::STUDENT},
  {"Money", Token::MONEY},
  {"Laptop", Token::LAPTOP},
  {"Pink Tie", Token::PINK_TIE}
};

std::map<Token, std::string> tokenToStrMap = {
  {Token::GOOSE, "Goose"},
  {Token::GRT_BUS, "GRT Bus"},
  {Token::TIM_HORTONS_DOUGHNUT, "Tim Hortons Doughnut"},
  {Token::PROFESSOR, "Professor"},
  {Token::STUDENT, "Student"},
  {Token::MONEY, "Money"},
  {Token::LAPTOP, "Laptop"},
  {Token::PINK_TIE, "Pink Tie"}
};
