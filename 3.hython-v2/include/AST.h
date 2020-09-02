/*************************************************************************
	> File Name: AST.h
	> Author: huguang
	> Mail: hug@haizeix.com
	> Created Time: 四  8/27 16:28:23 2020
 ************************************************************************/

#ifndef _AST_H
#define _AST_H

#include <hythonLexer.h>
#include <hythonParser.h>
#include <string>

namespace haizei {

class ASTNode {
public :
    ASTNode(const char *file_name);
    ASTNode(pANTLR3_BASE_TREE);
    int size() const;
    std::string text();
    ASTNode operator[](int);
    bool hasToken() const;
    int type() const;
    void destroy();
    ~ASTNode();

private:
    pANTLR3_INPUT_STREAM input;
    phythonLexer lex;
    pANTLR3_COMMON_TOKEN_STREAM tokens;
    phythonParser parser;
    pANTLR3_BASE_TREE tree;
    pANTLR3_COMMON_TOKEN tok;
    
    void init_tree(const char *file_name);
};

} // end of namespace haizei

#endif
