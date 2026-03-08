/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 20:51:12 by apaula-l          #+#    #+#             */
/*   Updated: 2026/03/08 19:22:16 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <exception>
#include <iomanip>
#include <cstring>

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
        throw std::invalid_argument("Error: could not open database.");
    }
    std::getline(file, line);

    if (line != "date,exchange_rate")
        throw std::invalid_argument("Error: invalid database format.");

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string date;
        std::string valueStr;

        if (!std::getline(ss, date, ','))
            continue;
        if (!std::getline(ss, valueStr))
            continue;

        double value = std::strtod(valueStr.c_str(), NULL);
        _database[date] = value;
    }
}

bool BitcoinExchange::isValidFormat(const std::string& line) const
{
    if (line.length() < 14)
        return false;

    if (line[4] != '-' || line[7] != '-')
        return false;

    if (line[10] != ' ' || line[11] != '|' || line[12] != ' ')
        return false;

    return true;
}

bool BitcoinExchange::isValidDate(const std::string& date) const
{
    if (date.length() != 10)
        return false;

    int year = std::atoi(date.substr(0,4).c_str());
    int month = std::atoi(date.substr(5,2).c_str());
    int day = std::atoi(date.substr(8,2).c_str());

    if (year < 2009 || month < 1 || month > 12 || day < 1)
        return false;

    bool leap =
        (year % 4 == 0 && year % 100 != 0) ||
        (year % 400 == 0);

    int daysMonth[] =
    {
        31,
        28 + leap,
        31,
        30,
        31,
        30,
        31,
        31,
        30,
        31,
        30,
        31
    };

    if (day > daysMonth[month - 1])
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

double BitcoinExchange::getExchangeRate(const std::string& date) const
{
    std::map<std::string,double>::const_iterator it;
    it = _database.lower_bound(date);

    if (it == _database.end()){
        --it;
        return it->second;
    }

    if (it->first != date){
        if (it == _database.begin())
            return it->second;

        --it;
    }

    return it->second;
}

void BitcoinExchange::validateFirstLine(std::ifstream& file)
{
    std::string line;

    std::getline(file, line);

    if (!line.empty() && line[line.size() - 1] == '\r')
        line.erase(line.size() - 1);

    if (line != "date | value")
        throw std::invalid_argument("Error: invalid input file format.");
}

void BitcoinExchange::processInputFile(const std::string& filename)
{
    std::ifstream file(filename.c_str());
    std::string line;

    if (!file.is_open())
        throw std::invalid_argument("Error: could not open file.");

    validateFirstLine(file);

    while (std::getline(file, line)){
        if (!line.empty() && line[line.size() - 1] == '\r')
            line.erase(line.size() - 1);

        if (!isValidFormat(line)){
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }

        std::string date = line.substr(0,10);
        std::string valueStr = line.substr(13);

        double value = std::strtod(valueStr.c_str(), NULL);

        if (!isValidDate(date)){
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }

        if (!isValidValue(value))
            continue;

        double rate = getExchangeRate(date);

        std::cout
            << date
            << " => "
            << value
            << " = "
            << std::fixed
            << std::setprecision(2)
            << value * rate
            << std::endl;
    }
}