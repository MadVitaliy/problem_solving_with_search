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
#include <random>
#include <fstream>

#include "PSWS.StateNode/StateNode.h"
#include "PSWS.StateGenerator/Generator.h"
#include "PSWS.Search/SearchTree.h"



std::vector<State> GetRandomStates(const std::size_t i_depth, const std::size_t i_sample)
{
	std::vector<State> states;

	for (std::size_t result_depth = 5; result_depth < i_depth; ++result_depth)
	{
		for (std::size_t sample = 0; sample < i_sample; ++sample)
		{
			StateGenerator st;
			st.SetDepth(result_depth);
			if (st.Generate())
				states.emplace_back(st.Get());
		}
	}
	return states;

}

void WriteStates(const std::vector<State>& i_states)
{
	std::ofstream os("./States.txt", std::fstream::trunc);
	if (!os.good())
		return;
	for (const auto& state : i_states)
	{
		for (const auto number : state.Get())
			os << static_cast<std::size_t>(number) << " ";
		os << "\n";
	}
}

std::vector<State> ReadStates()
{
	std::vector<State> states;

	std::ifstream is("./States.txt");
	if (!is.good())
		return {};

	while (!is.eof())
	{
		std::array<unsigned char, 9> state = { 0,0,0,0,0,0,0,0,0 };

		for (auto& number : state)
		{
			std::size_t temp;
			is >> temp;
			number = static_cast<unsigned char>(temp);
		}
		states.emplace_back(state);
	}
	return states;
}

void test()
{
	const auto states = GetRandomStates(20, 3);
	WriteStates(states);
	std::cout << "Generated: states:" << std::endl;
	for (const auto& state : states)
		std::cout << state << std::endl << std::endl;
}

void test2()
{

}


int main()
{
	StateGenerator st;
	st.SetDepth(4);
	const auto generated = st.Generate();
	if (!generated)
	{
		std::cout << "Pass was not generated. Run again" << std::endl;
		return 1;
	}

	auto state = st.Get();
	std::cout << state;

	DepthSearch ds;
	ds.SetInitialState(state);
	ds.SetTargetState(State({ 0,1,2,3,4,5,6,7,8 }));
	ds.SetDepth(15);
	const bool found = ds.Run();

	if (!found)
	{
		std::cout << "The solution was not found" << std::endl;
		return 1;
	}
	std::cout << "Total node count: " << ds.GetNodeTotalCount() << std::endl;
	std::cout << "Max node count in memory: " << ds.GetNodeMaxCountInMemory() << std::endl;
	std::cout << std::endl;

	const auto solution = ds.GetSolution();

	std::cout << "Solution: " << std::endl;
	for (const auto* node : solution)
		std::cout << *node << std::endl;

	return 0;
}
