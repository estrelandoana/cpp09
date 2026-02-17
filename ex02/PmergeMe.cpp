/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 19:39:23 by codespace         #+#    #+#             */
/*   Updated: 2026/02/17 20:13:39 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>
#include <cstdlib>
#include <climits>
#include <ctime>
#include <iomanip>
#include <algorithm>

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other)
    : _vector(other._vector), _deque(other._deque) {}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
    if (this != &other)
    {
        _vector = other._vector;
        _deque = other._deque;
    }
    return *this;
}

PmergeMe::~PmergeMe() {}

void PmergeMe::parseInput(char **argv)
{
    for (int i = 1; argv[i]; i++)
    {
        std::string arg(argv[i]);

        if (arg.empty())
        {
            std::cerr << "Error" << std::endl;
            exit(1);
        }

        for (size_t j = 0; j < arg.length(); j++)
        {
            if (!std::isdigit(arg[j]))
            {
                std::cerr << "Error" << std::endl;
                exit(1);
            }
        }

        long num = std::atol(arg.c_str());

        if (num < 0 || num > INT_MAX)
        {
            std::cerr << "Error" << std::endl;
            exit(1);
        }

        _vector.push_back(static_cast<int>(num));
        _deque.push_back(static_cast<int>(num));
    }
}

void PmergeMe::fordJohnsonVector(std::vector<int>& arr)
{
    std::sort(arr.begin(), arr.end());
}

void PmergeMe::fordJohnsonDeque(std::deque<int>& arr)
{
    std::sort(arr.begin(), arr.end());
}

void PmergeMe::process()
{
    std::vector<int> vec = _vector;
    std::deque<int>  deq = _deque;

    std::cout << "Before: ";
    for (size_t i = 0; i < _vector.size(); i++)
        std::cout << _vector[i] << " ";
    std::cout << std::endl;

    clock_t startVec = clock();
    fordJohnsonVector(vec);
    clock_t endVec = clock();

    clock_t startDeq = clock();
    fordJohnsonDeque(deq);
    clock_t endDeq = clock();

    std::cout << "After:  ";
    for (size_t i = 0; i < vec.size(); i++)
        std::cout << vec[i] << " ";
    std::cout << std::endl;

    double timeVec = (double)(endVec - startVec) * 1000000.0 / CLOCKS_PER_SEC;
    double timeDeq = (double)(endDeq - startDeq) * 1000000.0 / CLOCKS_PER_SEC;

    std::cout << std::fixed << std::setprecision(5);

    std::cout << "Time to process a range of "
              << vec.size()
              << " elements with std::vector : "
              << timeVec << " us" << std::endl;

    std::cout << "Time to process a range of "
              << deq.size()
              << " elements with std::deque  : "
              << timeDeq << " us" << std::endl;
}
