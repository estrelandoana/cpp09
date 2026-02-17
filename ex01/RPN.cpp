/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 15:07:19 by codespace         #+#    #+#             */
/*   Updated: 2026/02/17 16:58:41 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>

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

void RPN::calculate(const std::string& expression) {
    for (size_t i = 0; i < expression.length(); ++i) {
        char c = expression[i];
        if (std::isdigit(c)) {
            _stack.push(c - '0');
        } else if (isOperator(c)) {
            if (_stack.size() < 2) {
                throw std::runtime_error("Not enough operands");
            }
            int b = _stack.top(); _stack.pop();
            int a = _stack.top(); _stack.pop();
            int result = applyOperarion(a, b, c);
            _stack.push(result);
        }
    }
    if (_stack.size() != 1) {
        throw std::runtime_error("Invalid expression");
    }
    std::cout << "Result: " << _stack.top() << std::endl;
}