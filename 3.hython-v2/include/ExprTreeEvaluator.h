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

namespace haizei {

class ExprTreeEvaluator {
public:
    ExprTreeEvaluator();
    int run(haizei::ASTNode);
};

}

#endif
