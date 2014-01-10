//String parser DOWNLOADED FROM http://stackoverflow.com/questions/17073979/string-calculator-substr
//String parser includes enum, numberValue and expressionValue functions
//POSTED BY Nick http://stackoverflow.com/users/1193285/nick
//EDITED BY greatwolf http://stackoverflow.com/users/234175/greatwolf

#include <cstdio>
#include <string>
#include "ppapi/cpp/instance.h"
#include "ppapi/cpp/module.h"
#include "ppapi/cpp/var.h"
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <stdio.h>
using namespace std;


double suma=0;
int operand=0;
int op1=0;

enum {PLUS='+',MINUS='-',MULT='*'};

int numberValue(string &expr)
{
    istringstream is(expr);
    int value = 0;
    is >> value;
    return value;
}

int expressionValue(string expr)
{
    for(int i=expr.length()-2; i>=0; i--)
    {
        switch(expr.at(i))
        {
        case PLUS:
            return expressionValue(expr.substr(0,i)) +
                   expressionValue(expr.substr(i+1,expr.length()-i-1));
        case MINUS:

            return  expressionValue(expr.substr(0,i)) -
                    expressionValue(expr.substr(i+1,expr.length()-i-1));
        case MULT:

            return  expressionValue(expr.substr(0,i)) *
                    expressionValue(expr.substr(i+1,expr.length()-i-1));
        }
    }
    return numberValue(expr);
}
class CalculatorInstance : public pp::Instance
{
public:
    explicit CalculatorInstance(PP_Instance instance) : pp::Instance(instance)
    {}
    virtual ~CalculatorInstance() {}

    virtual void HandleMessage(const pp::Var& msg)
    {
        std::string message = msg.AsString();
        PostMessage(expressionValue(message));
        return;
    }
};

class CalculatorModule : public pp::Module
{
public:
    CalculatorModule() : pp::Module() {}
    virtual ~CalculatorModule() {}

    virtual pp::Instance* CreateInstance(PP_Instance instance)
    {
        return new CalculatorInstance(instance);
    }
};

namespace pp
{
Module* CreateModule()
{
    return new CalculatorModule();
}
}
