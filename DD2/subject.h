#ifndef SUBJECT_H
#define SUBJECT_H

#include "observer.h"

#include <vector>

template <typename InfoType, typename StateType> class Observer;

template <typename InfoType, typename StateType> class Subject {
  std::vector<Observer<InfoType, StateType>*> observers;
 public:
  void attach(Observer<InfoType, StateType> *o);
  void notifyObservers();
  virtual InfoType getInfo() = 0;
  virtual StateType getState() = 0;
  virtual void setInfo(InfoType newI) = 0;
  virtual void setState(StateType newS) = 0;
  virtual ~Subject() = 0;
};

template <typename InfoType, typename StateType>
Subject<InfoType, StateType>::~Subject() {} // required to make it an abstract class

template <typename InfoType, typename StateType>
void Subject<InfoType, StateType>::attach(Observer<InfoType, StateType> *o) {
  observers.emplace_back(o);
}

template <typename InfoType, typename StateType>
void Subject<InfoType, StateType>::notifyObservers() {
  for (auto &ob : observers) ob->notify(*this);
}

#endif