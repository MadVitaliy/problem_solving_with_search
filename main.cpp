//Created by Vitaliy Omelchenko 20.02.22
//Lab2: Pro
/*
 * Created by Vitaliy Omelchenko 20.02.22
 * Lab2: Problem-solving with search
 *
 * +--+---------+---------+-------+-----+
 * |# |Task     |AlgNoInf |AlgInf |Func |
 * +--+---------+---------+-------+-----+
 * |4 |8-puzzle |LDFS     |RBFS   |H1   |
 * +--+---------+---------+-------+-----+
 *
 */
#include <iostream>
#include <cstdio>
#include "State/Utils.h"

int main()
  {

//  State init_state({0,1,2,3,4,5,6,7,8});
//  State end_state({0,1,2,3,4,5,6,7,8});
//
//  std::cout << "init_state and end_state are equal: "<< (init_state == end_state) << std::endl;
//  std::cout << init_state << std::endl;
//  std::cout << "init_state.NextState(ACTION::RIGHT)"<< init_state.NextState(ACTION::RIGHT)<< std::endl;
//  std::cout << init_state << std::endl;
//  std::cout << "init_state.NextState(ACTION::LEFT)"<< init_state.NextState(ACTION::LEFT)<< std::endl;
//  std::cout << init_state << std::endl;
//  std::cout << "init_state.NextState(ACTION::UP)"<< init_state.NextState(ACTION::UP)<< std::endl;
//  std::cout << init_state << std::endl;
//  std::cout << "init_state.NextState(ACTION::DOWN)"<< init_state.NextState(ACTION::DOWN)<< std::endl;
//  std::cout << init_state << std::endl;
//
//  std::cout << "init_state and end_state are equal: "<< (init_state == end_state) << std::endl;
//
//  State new_state = init_state;
//
//  std::cout << new_state << std::endl;

DepthSearch dp;
dp.SetInitialState(State({1,0,2,3,4,5,6,7,8}));
dp.SetTargetState(State({0,1,2,3,4,5,6,7,8}));
dp.SetDepth(4);
dp.Run();


  std::getchar();
  return 0;
  }
