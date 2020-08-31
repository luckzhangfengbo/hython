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
//抽象语法树
class ASTNode {
public :
    ASTNode(const char *file_name);
    ASTNode(pANTLR3_BASE_TREE);
    int size();//子节点的数量
    std::string text();//返回当前节点的字符串信息
    ASTNode operator[](int);//当前节点的第i个子孩子
    bool hasToken();
    int type();
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
