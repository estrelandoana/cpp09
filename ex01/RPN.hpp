/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:53:42 by apaula-l          #+#    #+#             */
/*   Updated: 2026/03/08 19:23:43 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP
# include <stack>
# include <string>

class RPN {
    private:
        std::stack<int> _stack;
        
        bool isOperator(char c) const;
        int applyOperarion(int a, int b, char op);

    public:
        RPN();
        RPN(const RPN& copy);
        RPN& operator=(const RPN& copy);
        ~RPN();

        void calculate(const std::string& expression);
};
#endif
