/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 19:54:51 by apaula-l          #+#    #+#             */
/*   Updated: 2026/03/08 19:24:15 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
    if (argc < 2){
        std::cerr << "Error: no input" << std::endl;
        return 1;
    }

    try{
        PmergeMe sorter(argc, argv);
        sorter.sortAndMeasure();
    }
    catch (std::exception &e){
        std::cerr << e.what() << std::endl;
    }
}
