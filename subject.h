#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>

template <typename InfoType, typename StateType> class Observer;

template <typename InfoType, typename StateType> class Subject {
  std::vector<Observer<InfoType, StateType>*> observers;
  InfoType info;
  StateType state;
 protected:
  void setState(StateType newS);
 public:
  void setInfo(InfoType newI);
  void attach(Observer<InfoType, StateType> *o);  
  void notifyObservers();
  InfoType getInfo();
  StateType getState();
  virtual ~Subject() = 0;
};

template <typename InfoType, typename StateType>
void Subject<InfoType, StateType>::attach(Observer<InfoType, StateType> *o) {
  observers.emplace_back(o);
}

template <typename InfoType, typename StateType>
void Subject<InfoType, StateType>::notifyObservers() {
  for (auto &ob : observers) ob->notify(*this);
}

template <typename InfoType, typename StateType>
void Subject<InfoType, StateType>::setInfo(InfoType newI) { info = newI; }

template <typename InfoType, typename StateType>
void Subject<InfoType, StateType>::setState(StateType newS) { state = newS; }

template <typename InfoType, typename StateType>
InfoType Subject<InfoType, StateType>::getInfo() { return info; }

template <typename InfoType, typename StateType>
StateType Subject<InfoType, StateType>::getState() { return state; }

template <typename InfoType, typename StateType>
Subject<InfoType, StateType>::~Subject() {};

#endif