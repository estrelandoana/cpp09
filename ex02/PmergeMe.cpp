/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 19:39:23 by codespace         #+#    #+#             */
/*   Updated: 2026/02/17 20:54:18 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <sys/time.h>
#include <iomanip>


PmergeMe::PmergeMe(char **argv)
{
    parseInput(argv);
}

PmergeMe::~PmergeMe() {}

void PmergeMe::parseInput(char **argv)
{
    for (int i = 1; argv[i]; i++)
    {
        std::stringstream ss(argv[i]);
        long num;

        ss >> num;

        if (ss.fail() || !ss.eof() || num < 0 || num > 2147483647)
            throw std::runtime_error("Error");

        _vector.push_back(static_cast<int>(num));
        _deque.push_back(static_cast<int>(num));
    }
}

void PmergeMe::fordJohnsonVector(std::vector<int>& arr)
{
    if (arr.size() <= 1)
        return;

    std::vector< std::pair<int,int> > pairs;
    std::vector<int> mainChain;
    std::vector<int> pending;

    size_t i = 0;

    for (; i + 1 < arr.size(); i += 2)
    {
        if (arr[i] > arr[i+1])
            pairs.push_back(std::make_pair(arr[i], arr[i+1]));
        else
            pairs.push_back(std::make_pair(arr[i+1], arr[i]));
    }

    int straggler = 0;
    bool hasStraggler = false;

    if (i < arr.size())
    {
        straggler = arr[i];
        hasStraggler = true;
    }

    std::vector<int> bigger;

    for (size_t j = 0; j < pairs.size(); j++)
        bigger.push_back(pairs[j].first);

    fordJohnsonVector(bigger);

    std::vector< std::pair<int,int> > sortedPairs;

    for (size_t j = 0; j < bigger.size(); j++)
    {
        for (size_t k = 0; k < pairs.size(); k++)
        {
            if (pairs[k].first == bigger[j])
            {
                sortedPairs.push_back(pairs[k]);
                pairs.erase(pairs.begin() + k);
                break;
            }
        }
    }

    mainChain.push_back(sortedPairs[0].second);
    mainChain.push_back(sortedPairs[0].first);

    for (size_t j = 1; j < sortedPairs.size(); j++)
    {
        mainChain.push_back(sortedPairs[j].first);
        pending.push_back(sortedPairs[j].second);
    }

    for (size_t j = 0; j < pending.size(); j++)
    {
        std::vector<int>::iterator pos =
            std::lower_bound(mainChain.begin(), mainChain.end(), pending[j]);
        mainChain.insert(pos, pending[j]);
    }

    if (hasStraggler)
    {
        std::vector<int>::iterator pos =
            std::lower_bound(mainChain.begin(), mainChain.end(), straggler);
        mainChain.insert(pos, straggler);
    }

    arr = mainChain;
}

void PmergeMe::fordJohnsonDeque(std::deque<int>& arr)
{
    if (arr.size() <= 1)
        return;

    std::deque< std::pair<int,int> > pairs;
    std::deque<int> mainChain;
    std::deque<int> pending;

    size_t i = 0;

    for (; i + 1 < arr.size(); i += 2)
    {
        if (arr[i] > arr[i+1])
            pairs.push_back(std::make_pair(arr[i], arr[i+1]));
        else
            pairs.push_back(std::make_pair(arr[i+1], arr[i]));
    }

    int straggler = 0;
    bool hasStraggler = false;

    if (i < arr.size())
    {
        straggler = arr[i];
        hasStraggler = true;
    }

    std::deque<int> bigger;

    for (size_t j = 0; j < pairs.size(); j++)
        bigger.push_back(pairs[j].first);

    fordJohnsonDeque(bigger);

    std::deque< std::pair<int,int> > sortedPairs;

    for (size_t j = 0; j < bigger.size(); j++)
    {
        for (size_t k = 0; k < pairs.size(); k++)
        {
            if (pairs[k].first == bigger[j])
            {
                sortedPairs.push_back(pairs[k]);
                pairs.erase(pairs.begin() + k);
                break;
            }
        }
    }

    mainChain.push_back(sortedPairs[0].second);
    mainChain.push_back(sortedPairs[0].first);

    for (size_t j = 1; j < sortedPairs.size(); j++)
    {
        mainChain.push_back(sortedPairs[j].first);
        pending.push_back(sortedPairs[j].second);
    }

    for (size_t j = 0; j < pending.size(); j++)
    {
        std::deque<int>::iterator pos =
            std::lower_bound(mainChain.begin(), mainChain.end(), pending[j]);
        mainChain.insert(pos, pending[j]);
    }

    if (hasStraggler)
    {
        std::deque<int>::iterator pos =
            std::lower_bound(mainChain.begin(), mainChain.end(), straggler);
        mainChain.insert(pos, straggler);
    }

    arr = mainChain;
}

void PmergeMe::process()
{
    std::cout << "Before: ";
    for (size_t i = 0; i < _vector.size(); i++)
        std::cout << _vector[i] << " ";
    std::cout << std::endl;

    std::vector<int> v = _vector;
    std::deque<int>  d = _deque;

    clock_t startV = clock();
    fordJohnsonVector(v);
    clock_t endV = clock();

    clock_t startD = clock();
    fordJohnsonDeque(d);
    clock_t endD = clock();

    long timeV = (long)((double)(endV - startV) * 1000000.0 / CLOCKS_PER_SEC);
    long timeD = (long)((double)(endD - startD) * 1000000.0 / CLOCKS_PER_SEC);

    std::cout << "After:  ";
    for (size_t i = 0; i < v.size(); i++)
        std::cout << v[i] << " ";
    std::cout << std::endl;

    std::cout << std::fixed << std::setprecision(5);

    std::cout << "Time to process a range of "
              << v.size()
              << " elements with std::vector : "
              << timeV << " us" << std::endl;

    std::cout << "Time to process a range of "
              << d.size()
              << " elements with std::deque  : "
              << timeD << " us" << std::endl;
}

