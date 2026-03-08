/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 19:39:23 by apaula-l          #+#    #+#             */
/*   Updated: 2026/03/08 19:24:13 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(int argc, char **argv)
{
    parseInput(argc, argv);
}

void PmergeMe::parseInput(int argc, char **argv)
{
    for (int i = 1; i < argc; i++)
    {
        char *end;
        long value = std::strtol(argv[i], &end, 10);

        if (*end != '\0' || value < 0 || value > INT_MAX)
            throw std::invalid_argument("Error");

        int num = static_cast<int>(value);

        if (std::find(_vector.begin(), _vector.end(), num) != _vector.end())
            throw std::invalid_argument("Error: duplicate");

        _vector.push_back(num);
        _deque.push_back(num);
    }
}

template <typename T>
void PmergeMe::fordJohnson(T &container)
{
    if (container.size() <= 1)
        return;

    T mainChain;
    T pending;

    for (size_t i = 0; i + 1 < container.size(); i += 2)
    {
        if (container[i] < container[i + 1])
            std::swap(container[i], container[i + 1]);

        mainChain.push_back(container[i]);
        pending.push_back(container[i + 1]);
    }

    if (container.size() % 2 != 0)
        mainChain.push_back(container.back());

    fordJohnson(mainChain);

    for (size_t i = 0; i < pending.size(); i++)
    {
        typename T::iterator pos =
            std::lower_bound(mainChain.begin(), mainChain.end(), pending[i]);

        mainChain.insert(pos, pending[i]);
    }

    container = mainChain;
}

template <typename T>
void PmergeMe::printContainer(const T &container)
{
    for (typename T::const_iterator it = container.begin(); it != container.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}

void PmergeMe::printLimited(const std::vector<int>& v)
{
    size_t limit = 4;

    for (size_t i = 0; i < v.size() && i < limit; i++)
        std::cout << v[i] << " ";

    if (v.size() > limit)
        std::cout << "[...]";

    std::cout << std::endl;
}

void PmergeMe::sortAndMeasure()
{
    std::vector<int> vec = _vector;
    std::deque<int> deq(_vector.begin(), _vector.end());

    std::cout << "Before: ";
    printLimited(_vector);

    clock_t startVec = clock();
    fordJohnson(vec);
    clock_t endVec = clock();

    clock_t startDeq = clock();
    fordJohnson(deq);
    clock_t endDeq = clock();

    std::cout << "After: ";
    printLimited(vec);

    double timeVec = (double)(endVec - startVec) / CLOCKS_PER_SEC * 1000000;
    double timeDeq = (double)(endDeq - startDeq) / CLOCKS_PER_SEC * 1000000;

    std::cout << "Time to process a range of " << vec.size()
              << " elements with std::vector : "
              << timeVec << " us" << std::endl;

    std::cout << "Time to process a range of " << deq.size()
              << " elements with std::deque : "
              << timeDeq << " us" << std::endl;
}
