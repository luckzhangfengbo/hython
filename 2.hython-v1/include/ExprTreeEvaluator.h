/*************************************************************************
	> File Name: ExprTreeEvaluator.h
	> Author: huguang
	> Mail: hug@haizeix.com
	> Created Time: 六  8/29 09:11:57 2020
 ************************************************************************/

#ifndef _EXPRTREEEVALUATOR_H
#define _EXPRTREEEVALUATOR_H

#include <string>
#include <map>
#include <AST.h>

class ExprTreeEvaluator {
public:
    ExprTreeEvaluator();
    ExprTreeEvaluator(ExprTreeEvaluator *);
    int run(haizei::ASTNode);
    void def_param(std::string, int);
    void set_param(std::string, int);
    int get_param(std::string);
    ExprTreeEvaluator *next;

private :
    std::map<std::string,int> memory;
};

#endif
