/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 19:35:43 by apaula-l          #+#    #+#             */
/*   Updated: 2026/03/08 19:24:18 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <iostream>
#include <algorithm>
#include <climits>
#include <cstdlib>
#include <ctime>

class PmergeMe
{
private:
    std::vector<int> _vector;
    std::deque<int> _deque;

    void parseInput(int argc, char **argv);
    
    template <typename T>
    void fordJohnson(T &container);
    template <typename T>
    void printContainer(const T &container);
    void printLimited(const std::vector<int>& v);

public:
    PmergeMe(int argc, char **argv);
    void sortAndMeasure();
};

#endif
