/*************************************************************************
	> File Name: ExprHandle.h
	> Author: 
	> Mail: 
	> Created Time: 一  8/31 12:04:37 2020
 ************************************************************************/

#ifndef _EXPRHANDLE_H
#define _EXPRHANDLE_H
#include <AST.h>>
#include <ExprTreeEvaluator.h>


class ExprHandler {
public:
    ExprHandler *next = nullptr;
    virtual int run(haizei::ASTNode tree, int token, ExprTreeEvaluator *temp) = 0;
    virtual bool Test(int token) = 0;
};


class VarHandler : public ExprHandler {

    virtual int run(haizei::ASTNode tree, int token, ExprTreeEvaluator *temp) override;
    virtual bool Test(int token) override;
};
class CalHandler : public ExprHandler {

    virtual int run(haizei::ASTNode tree, int token, ExprTreeEvaluator *temp) override;
    virtual bool Test(int token) override;
};
class LogHandler : public ExprHandler {

    virtual int run(haizei::ASTNode tree, int token, ExprTreeEvaluator *temp) override;
    virtual bool Test(int token) override;
};
class ProcHandler : public ExprHandler {

    virtual int run(haizei::ASTNode tree, int token, ExprTreeEvaluator *temp) override;
    virtual bool Test(int token) override;
};
class BaseHandler : public ExprHandler {

    virtual int run(haizei::ASTNode tree, int token, ExprTreeEvaluator *temp) override;
    virtual bool Test(int token) override;
};
class DefHandler : public ExprHandler { 
    virtual int run(haizei::ASTNode tree, int token, ExprTreeEvaluator *temp) override;
    virtual bool Test(int token) override;
};


class SingletonPattern {
public:
    static ExprHandler *getInstance();
private:
    static ExprHandler *head;
    static void BuildSingleton();
    SingletonPattern();
    SingletonPattern(const SingletonPattern &);
    ~SingletonPattern();

#endif
