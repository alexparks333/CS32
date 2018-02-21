
//
//  eval.cpp
//  Homework_2
//
//  Created by Anirudh Balasubramaniam on 2/3/18.
//  Copyright © 2018 Anirudh Balasubramaniam. All rights reserved.
//

#include <stack>
#include <string>
#include <cassert>
#include <iostream>
#include "Map.h"
using namespace std;

void convertInfixToPostfix(string infix, string &postfix)
{
    postfix = "";
    stack<char> operatorStack;
    char ch;

    for(int i = 0; i < infix.size(); i++)
    {
        ch = infix[i];

        if(islower(ch))
        {
            postfix += ch;
            continue;
        }

        if(ch == ' ')
            continue;

        switch (ch)
        {
            case '(':
                operatorStack.push(ch);
                break;

            case ')':
                while(operatorStack.top() != '(')
                {
                    postfix += operatorStack.top();
                    operatorStack.pop();
                }
                operatorStack.pop();
                break;

            case '/':
            case '*':
            case '+':
            case '-':
                while(!operatorStack.empty() && operatorStack.top() != '(' && !((ch == '*' || ch == '/') && (operatorStack.top() == '+' || operatorStack.top() == '-')))
                {
                    postfix += operatorStack.top();
                    operatorStack.pop();
                }
                operatorStack.push(ch);
                break;

            default:
                break;
        }
    }

    while(!operatorStack.empty())
    {
        postfix += operatorStack.top();
        operatorStack.pop();
    }
}

int applyOperation(int num1, int num2, char oper)
{
    switch (oper)
    {
        case '/':
            if(num2 != 0)
                return (num1/num2);
            else
                return -42; //what to do if /0 error
            break;

        case '*':
            return (num1*num2);
            break;

        case '+':
            return (num1 + num2);
            break;

        case '-':
            return (num1 - num2);
            break;

        default:
            break;
    }

    return 1;
}

bool isOperator(char c)
{
    if(c == '/' || c == '+' || c == '-' || c == '*')
        return true;
    return false;
}

int isParanth(char c)
{
    if(c == '(')
        return -1;
    if(c == ')')
        return 1;
    return 0;
}

bool isRepeating(string infix, int i)
{
    char ch = 0;

    if(isOperator(infix[i]))
    {
        ch = infix[i+1];
        if(isOperator(ch) || (isParanth(ch) != 0 && i+2 < infix.size() && isOperator(infix[i+2])))
            return true;
    }

    if(islower(infix[i]))
    {
        ch = infix[i+1];
        if(islower(ch) || (isParanth(ch) != 0 && i+2 < infix.size() && islower(infix[i+2])))
            return true;
    }

    return false;
}

bool parenthesesBalanced(string infix)
{
    stack<char> paranthStack;

    for(int i = 0; i < infix.size(); i++)
    {
        if(isParanth(infix[i]) == -1)
            paranthStack.push(infix[i]);
        else if(isParanth(infix[i]) == 1)
        {
            if(paranthStack.empty() || isParanth(paranthStack.top()) != -1 || isParanth(infix[i]) != 1)
                return false;
            paranthStack.pop();
        }
    }

    if(paranthStack.empty())
        return true;
    return false;
}

int checkInfixSyntaxOperands(string infix, const Map& values)
{
    infix.erase(std::remove(infix.begin(),infix.end(),' '),infix.end());

    int paranthCount = 0, operands = 0, operators = 0;
    char ch;

    if(infix.size() == 0) return 1;

    for(int i = 0; i < infix.size(); i++)
    {
        ch = infix[i];
        if(!islower(ch) && !isOperator(ch) && isParanth(ch) == 0) return 1;
        if(isupper(ch)) return 1;
        if(i == 0 && (isOperator(ch) || isParanth(ch) == 1)) return 1;
        if(i == infix.size()-1 && (isOperator(ch) || isParanth(ch) == -1)) return 1;
        if(isRepeating(infix, i)) return 1;

        paranthCount += isParanth(ch);
        if(isParanth(ch) == -1 && isParanth(infix[i+1]) == 1) return 1;
        if(isParanth(ch) == -1 && isOperator(infix[i+1])) return 1;
        if(isParanth(ch) == 1 && isOperator(infix[i-1])) return 1;
        if(islower(ch)) operands++;
        if(isOperator(ch)) operators++;

        if(islower(ch) && !values.contains(ch)) return 2;
    }

    if(!parenthesesBalanced(infix)) return 1;
    if(paranthCount != 0) return 1;
    if(operators + 1 != operands) return 1;

    return 0;
}

int evaluate(string infix, const Map& values, string& postfix, int& result)
{
    int check = checkInfixSyntaxOperands(infix, values);
    if(check == 1)
        return check;
    convertInfixToPostfix(infix, postfix);
    if(check != 0)
        return check;

    stack<int> operandStack;
    int operand1, operand2;
    char ch = ' ';
    int value = 0;

    for(int i = 0; i < postfix.size(); i++)
    {
        ch = postfix[i];
        if(islower(ch))
        {
            values.get(ch, value);
            operandStack.push(value);
        }
        else
        {
            operand2 = operandStack.top();
            operandStack.pop();
            operand1 = operandStack.top();
            operandStack.pop();
            value = applyOperation(operand1, operand2, ch);
            if(value == -42)
                return 3;
            operandStack.push(value);
        }
    }

    if(!operandStack.empty())
        result = operandStack.top();

    return 0;
}

//int main()
//{
//    char vars[] = { 'a', 'e', 'i', 'o', 'u', 'y', '#' };
//    int  vals[] = {  3,  -9,   6,   2,   4,   1  };
//    Map m;
//    for (int k = 0; vars[k] != '#'; k++)
//        m.insert(vars[k], vals[k]);
//    string pf;
//    int answer;
//    assert(evaluate("a+ e", m, pf, answer) == 0  &&
//           pf == "ae+"  &&  answer == -6);
//    answer = 999;
//    assert(evaluate("", m, pf, answer) == 1  &&  answer == 999);
//    assert(evaluate("a+", m, pf, answer) == 1  &&  answer == 999);
//    assert(evaluate("a i", m, pf, answer) == 1  &&  answer == 999);
//    assert(evaluate("ai", m, pf, answer) == 1  &&  answer == 999);
//    assert(evaluate("()", m, pf, answer) == 1  &&  answer == 999);
//    assert(evaluate("y(o+u)", m, pf, answer) == 1  &&  answer == 999);
//    assert(evaluate("a+E", m, pf, answer) == 1  &&  answer == 999);
//    assert(evaluate("(a+(i-o)", m, pf, answer) == 1  &&  answer == 999);
//    // unary operators not allowed:
//    assert(evaluate("-a", m, pf, answer) == 1  &&  answer == 999);
//    assert(evaluate("a*b", m, pf, answer) == 2  &&
//           pf == "ab*"  &&  answer == 999);
//    assert(evaluate("y +o *(   a-u)  ", m, pf, answer) == 0  &&
//           pf == "yoau-*+"  &&  answer == -1);
//    answer = 999;
//    assert(evaluate("o/(y-y)", m, pf, answer) == 3  &&
//           pf == "oyy-/"  &&  answer == 999);
//    assert(evaluate(" a  ", m, pf, answer) == 0  &&
//           pf == "a"  &&  answer == 3);
//    assert(evaluate("((a))", m, pf, answer) == 0  &&
//           pf == "a"  &&  answer == 3);
//    cout << "Passed all tests" << endl;
//    return 0;
//}

