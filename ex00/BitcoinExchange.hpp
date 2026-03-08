/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 20:36:29 by apaula-l          #+#    #+#             */
/*   Updated: 2026/03/08 19:22:14 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP
# include <map>
# include <string>

class BitcoinExchange {
    private:
        std::map<std::string, double> _database;
        
        void localDatabase(const std::string& filename);
        bool isValidDate(const std::string& date) const;
        bool isValidValue(double value) const;
        bool isValidFormat(const std::string& line) const;
        double getExchangeRate(const std::string& date) const;

    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& copy);
        BitcoinExchange& operator=(const BitcoinExchange& copy);
        ~BitcoinExchange();

        void validateFirstLine(std::ifstream& file);
        void processInputFile(const std::string& filename);
};

#endif
