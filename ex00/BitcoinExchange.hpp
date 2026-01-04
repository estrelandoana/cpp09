/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaula-l <apaula-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 20:36:29 by apaula-l          #+#    #+#             */
/*   Updated: 2026/01/03 20:48:53 by apaula-l         ###   ########.fr       */
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
        double getExchangeRate(const std::string& date) const;

    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& copy);
        BitcoinExchange& operator=(const BitcoinExchange& copy);
        ~BitcoinExchange();

        void processInputFile(const std::string& filename);
};

#endif
