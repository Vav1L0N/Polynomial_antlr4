#pragma once
#include <iostream>
#include "TParserBaseListener.h"
#include "TParser.h"
#include "TLexer.h"
#include "Polynomial.h"
#include <stack> 
#include <map>

namespace antlrcpptest {
    class CalculatorInterpreter : public TParserBaseListener {

        std::stack<Polynomial> polynomial_stack;
        std::map<std::string, Polynomial> parameters;
        std::stack<std::string> var_stack;
        std::stack<int> integ;

        int X_degree;
        int Y_degree;
        int Z_degree;

        std::stack<std::string> mon_var;

    public:
        CalculatorInterpreter()
        {
            X_degree = Y_degree = Z_degree = 0;
        }
        
        void exitPlusOp(TParser::PlusOpContext* ctx) override {
            auto r = polynomial_stack.top(); polynomial_stack.pop();
            auto l = polynomial_stack.top(); polynomial_stack.pop();
            polynomial_stack.push(l + r);
        };
        void exitBinaryMinusOp(TParser::BinaryMinusOpContext* ctx) override {
            auto r = polynomial_stack.top(); polynomial_stack.pop();
            auto l = polynomial_stack.top(); polynomial_stack.pop();
            polynomial_stack.push(l - r);
        };
        void exitUnaryMinusOp(TParser::UnaryMinusOpContext* ctx) override {
            polynomial_stack.top() = polynomial_stack.top() * (-1);
        };
        void exitMultOp(TParser::MultOpContext* ctx) override {
            auto r = polynomial_stack.top(); polynomial_stack.pop();
            auto l = polynomial_stack.top(); polynomial_stack.pop();
            polynomial_stack.push(l * r);
        };
        void exitSetValue(TParser::SetValueContext* ctx) override 
        {
            Polynomial cur = polynomial_stack.top();
            std::string var_name = var_stack.top();
            std::pair<std::string, Polynomial> pair(var_name, cur);
            parameters.erase(var_name);
            parameters.insert(pair);
            polynomial_stack.pop();
            var_stack.pop();
        };

        void enterSetValue(TParser::SetValueContext* ctx) override {};
        void exitGetValue(TParser::GetValueContext* ctx) override
        {
            std::string var_name = var_stack.top();
            var_stack.pop();
            try {
                Polynomial cur = parameters.at(var_name);
                polynomial_stack.push(cur);
            }
            catch (std::out_of_range)
            {
                std::string message = var_name + " not find";
                throw std::out_of_range(message);
            }
        };
        void exitConvertToInt(TParser::ConvertToIntContext* ctx) override
        {
            integ.push(std::stoi(ctx->getText()));
        };

        void exitReadUserVar(TParser::ReadUserVarContext* ctx) override
        {
            var_stack.push(ctx->getText());
        }

        virtual void exitPrint(TParser::PrintContext* ) override
        {
            std::cout << polynomial_stack.top() << std::endl;
            polynomial_stack.pop();
        }

        void exitReadVar(TParser::ReadVarContext* ctx) override
        {
            mon_var.push(ctx->getText());
        }

        void exitPow(TParser::PowContext* ) override 
        {
            int pow = integ.top();
            std::string var = mon_var.top();
            if (var == "x")
            {
                X_degree += pow;
            }
            if (var == "y")
            {
                Y_degree += pow;
            }
            if (var == "z")
            {
                Z_degree += pow;
            }
            integ.pop();
            mon_var.pop();
        };

        void enterMonom(TParser::MonomContext* ) override
        {
            X_degree = Y_degree = Z_degree = 0;
        }
        void exitMonom(TParser::MonomContext* ) override {}

        void enterFullMonom(TParser::FullMonomContext* ) override {}

        virtual void exitFullMonom(TParser::FullMonomContext* ) override
        {
            int coeff = integ.top();
            integ.pop();
            list<Polynomial::monom> monoms;
            monoms.push(Polynomial::monom(X_degree, Y_degree, Z_degree, coeff));
            Polynomial polynom(monoms);
            polynomial_stack.push(polynom);
        }
        void exitMonomZeroPower(TParser::MonomZeroPowerContext* ) override
        {
            int coeff = integ.top();
            integ.pop();
            list<Polynomial::monom> monoms;
            monoms.push(Polynomial::monom(X_degree, Y_degree, Z_degree, coeff));
            Polynomial polynom(monoms);
            polynomial_stack.push(polynom);
        }
        void enterMonomWithouCoefficient(TParser::MonomWithouCoefficientContext* ) override
        {
            int coeff = 1;
            list<Polynomial::monom> monoms;
            monoms.push(Polynomial::monom(X_degree, Y_degree, Z_degree, coeff));
            Polynomial polynom(monoms);
            polynomial_stack.push(polynom);
        }
        void exitCalculate(TParser::CalculateContext* ) override
        {
            int x_point = integ.top();
            integ.pop();
            int y_point = integ.top();
            integ.pop();
            int z_point = integ.top();
            integ.pop();
            Polynomial cur = polynomial_stack.top();
            int result = cur.evaluate(x_point, y_point, z_point);
            std::cout << "Calculate at point B(" << x_point << ", " << y_point << ", " << z_point << ") = " << result << std::endl;
            polynomial_stack.pop();
        }
    };
}

