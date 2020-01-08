//
//  Regex.h
//  test2
//
//  Created by Илья on 03.01.2020.
//  Copyright © 2020 Илья. All rights reserved.
//

#ifndef Regex_h
#define Regex_h

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

class Regex
{
    private:
    
    enum Operators
    {
        AnyOne = '.',
        Any = '*',
        Literal
    };

    struct State
    {
        Operators condition;
        State *next = nullptr;
        char ch;
    };
    
    static bool CheckState(char ch, State *state, vector <State*> *_nextStates)
    {
        switch (state->condition)
        {
            case '*':
            {
                _nextStates->push_back(state);
                
                if (state->next != nullptr)
                {
                    if (CheckState(ch, state->next, _nextStates))
                    {
                        if (state->next -> next != nullptr)
                        {
                             _nextStates->push_back(state->next -> next);
                        }
                    }
                }
                return true;
            } break;
                
            case '.':
            {
                return true;
            } break;
                
            case Literal:
            {
                return state->ch == ch;
            } break;
        }
    };
    
    static void Graph(string _mask, vector <State*> *_nextStates)
    {
        auto state = new State();
        
        state->ch = _mask[0];
        state->condition = GetEnum(_mask[0]);
        _nextStates->push_back(state);
        
        for (int i = 1; i < _mask.length(); i++)
        {
            state->next = new State();
            state = state->next;
            
            state->ch = _mask[i];
            state->condition = GetEnum(_mask[i]);
        } 
    }; 
    
    static Operators GetEnum (char ch)
    {
          switch (ch)
          {
              case '*':
              {
                 return Operators::Any;
              } break;
                  
              case '.':
              {
                 return Operators::AnyOne;
              } break;
               
              default:
              {
                 return Operators::Literal;
              } break;
          }
    };
    
    public:
    
    Regex() = default;
    ~Regex() = default;

    static bool IsMatch(string mask, string line)
    {
        vector <State*> *_currentStates,
                        *_nextStates;
        _currentStates = new vector<State*>();
        _nextStates = new vector<State*>();
        
        string _mask,
               str;
        
        _mask = mask;
        str = line;
        
        Graph(_mask, _nextStates);
        
        for (int i = 0; i < str.length(); i++)
        {
            swap(_currentStates, _nextStates);
            _nextStates->clear();
             
            for (int j = 0; j < _currentStates->size(); j++)
            {
                if (CheckState(str[i], (*_currentStates)[j], _nextStates))
                {
                    if ((*_currentStates)[j]->next != nullptr)
                    {
                        _nextStates->push_back((*_currentStates)[j]->next);
                    } else {
                        cout << "совпадение найдено"  << endl;
                        delete _currentStates;
                        delete _nextStates;
                        
                        return true;
                    }
                }
            }
            if (_nextStates->empty())
            {
                cout << "совпадения не найдены" << endl;
                delete _currentStates;
                delete _nextStates;
                
                return false;
            }
        }
        cout << "совпадения не найдены" << endl;
        delete _currentStates;
        delete _nextStates;
        
        return false;
    };
}; 
#endif /* Regex_h */
