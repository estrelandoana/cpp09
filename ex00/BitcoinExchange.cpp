/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaula-l <apaula-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 20:51:12 by apaula-l          #+#    #+#             */
/*   Updated: 2026/01/03 21:51:34 by apaula-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>

BitcoinExchange::BitcoinExchange() {
    localDatabase("data.csv");
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& copy) : _database(copy._database) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& copy){
    if (this != &copy)
        _database = copy._database;
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::localDatabase(const std::string& filename) {
    std::ifstream file(filename.c_str());
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error: could not open database." << std::endl;
        return;
    }
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string date;
        std::string valueStr;
        double value;

        if (!std::getline(ss, date, ','))
            continue;
        if (!std::getline(ss, valueStr))
            continue;

        value = std::atof(valueStr.c_str());
        _database[date] = value;
    }
}

bool BitcoinExchange::isValidDate(const std::string& date) const {
    if (date.length() != 10)
        return false;

    if (date[4] != '-' || date[7] != '-')
        return false;

    int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());

    if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31)
        return false;
    return true;
}

bool BitcoinExchange::isValidValue(double value) const {
    if (value < 0) {
        std::cerr << "Error: not a positive number." << std::endl;
        return false;
    }

    if (value > 1000) {
        std::cerr << "Error: too large a number." << std::endl;
        return false;
    }
    return true;
}

double BitcoinExchange::getExchangeRate(const std::string& date) const {
    std::map<std::string, double>::const_iterator it;
    it = _database.lower_bound(date);

    if (it == _database.begin())
        return it->second;

    if (it == _database.end() || it->first != date)
        --it;
    return it->second;
}

void BitcoinExchange::processInputFile(const std::string& filename) {
    std::ifstream file(filename.c_str());
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string date;
        std::string valueStr;
        double value;

        if (!std::getline(ss, date, ' '))
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }
        ss.ignore(3);

        if (!std::getline(ss, valueStr))
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }
        value = std::atof(valueStr.c_str());

        if (!isValidDate(date)) {
            std::cerr << "Error: bad input => " << date << std::endl;
            continue;
        }

        if (!isValidValue(value))
            continue;
        double rate = getExchangeRate(date);
        std::cout << date << " => " << value << " = " << value * rate <<std::endl;
    }    
}
