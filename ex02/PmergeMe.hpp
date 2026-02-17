/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 19:35:43 by codespace         #+#    #+#             */
/*   Updated: 2026/02/17 20:48:23 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP
# include <vector>
# include <deque>
# include <string>
# include <iostream>
# include <sstream>
# include <algorithm>
# include <stdexcept>
# include <ctime>
# include <cstdlib>

class PmergeMe
{
private:
    std::vector<int> _vector;
    std::deque<int>  _deque;

    void fordJohnsonVector(std::vector<int>& arr);
    void fordJohnsonDeque(std::deque<int>& arr);
    void parseInput(char **argv);

public:
    PmergeMe(char **argv);
    ~PmergeMe();

    void process();
};

#endif
