/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 15:07:19 by apaula-l          #+#    #+#             */
/*   Updated: 2026/03/08 19:23:34 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>
#include <sstream>

RPN::RPN() {}

RPN::RPN(const RPN& copy) : _stack(copy._stack) {}

RPN& RPN::operator=(const RPN& copy) {
    if (this != &copy)
        _stack = copy._stack;
    return *this;
}

RPN::~RPN() {}

bool RPN::isOperator(char c) const {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int RPN::applyOperarion(int a, int b, char op) {
    switch (op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            if (b == 0)
                throw std::invalid_argument("Division by zero");
            return a / b;
        default: throw std::invalid_argument("Invalid operator");
    }
}

void RPN::calculate(const std::string& expression)
{
    std::stringstream ss(expression);
    std::string token;

    while (ss >> token){
        if (token[0] == '-' && token.size() > 1)
            throw std::invalid_argument("negative numbers not allowed");

        if (std::isdigit(token[0])){
            if (token.size() > 1)
                throw std::invalid_argument("numbers must be between 0 and 9");

            _stack.push(token[0] - '0');
        }else if (token.size() == 1 && isOperator(token[0])){
            if (_stack.size() < 2)
                throw std::runtime_error("not enough operands");

            int b = _stack.top(); _stack.pop();
            int a = _stack.top(); _stack.pop();

            int result = applyOperarion(a, b, token[0]);
            _stack.push(result);
        }else{
            throw std::invalid_argument("invalid token");
        }
    }

    if (_stack.size() != 1)
        throw std::runtime_error("invalid expression");

    std::cout << "Result: " << _stack.top() << std::endl;
}