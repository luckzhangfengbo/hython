/*************************************************************************
	> File Name: main.cpp
	> Author: huguang
	> Mail: hug@haizeix.com
	> Created Time: 一  8/24 10:24:49 2020
 ************************************************************************/

#include "ExprCppTreeLexer.h"
#include "ExprCppTreeParser.h"
#include <cassert>
#include <map>
#include <string>
#include <iostream>
using std::map;
using std::string;
using std::cout;
using std::endl;
 
class ExprTreeEvaluator {
    map<string,int> memory;
public:
    int run(pANTLR3_BASE_TREE);
    void set_param(string, int);
    int get_param(string);
};
 
pANTLR3_BASE_TREE getChild(pANTLR3_BASE_TREE, unsigned);
const char* getText(pANTLR3_BASE_TREE tree);
 
int main(int argc, char* argv[])
{
  pANTLR3_INPUT_STREAM input;
  pExprCppTreeLexer lex;
  pANTLR3_COMMON_TOKEN_STREAM tokens;
  pExprCppTreeParser parser;
 
  assert(argc > 1);
  input = antlr3FileStreamNew((pANTLR3_UINT8)argv[1],ANTLR3_ENC_8BIT);
  lex = ExprCppTreeLexerNew(input);
  tokens = antlr3CommonTokenStreamSourceNew(ANTLR3_SIZE_HINT,
                                            TOKENSOURCE(lex));
  parser = ExprCppTreeParserNew(tokens);
 
  ExprCppTreeParser_prog_return r = parser->prog(parser);
cout << "done" << endl;
  pANTLR3_BASE_TREE tree = r.tree;
 
  ExprTreeEvaluator eval;
  int rr = eval.run(tree);
  cout << "Evaluator result: " << rr << '\n';
 
  parser->free(parser);
  tokens->free(tokens);
  lex->free(lex);
  input->close(input);
 
  return 0;
}

void ExprTreeEvaluator::set_param(string name, int val) {
    if (memory.find(name) != memory.end()) {
        throw std::runtime_error("param redefined : " + name);//抛异常
    }
    //没有重复
    memory[name] = val;
    return ;
}

int ExprTreeEvaluator::get_param(string name) {
    if (memory.find(name) == memory.end()) {
        throw std::runtime_error("unknown param : " + name);
    }
    return memory[name];
}

int ExprTreeEvaluator::run(pANTLR3_BASE_TREE tree)
{
    pANTLR3_COMMON_TOKEN tok = tree->getToken(tree);
    if(tok) {
        switch(tok->type) {
        case INT: {
            const char* s = getText(tree);
            if(s[0] == '~') {
                return -atoi(s+1);
            }
            else {
                return atoi(s);
            }
        }
        case ID: {
            string var(getText(tree));
            return get_param(var);
        }
        case PLUS:
            return run(getChild(tree,0)) + run(getChild(tree,1));
        case MINUS:
            return run(getChild(tree,0)) - run(getChild(tree,1));
        case TIMES:
            return run(getChild(tree,0)) * run(getChild(tree,1));
        case DIV:
            return run(getChild(tree,0)) / run(getChild(tree,1));
        case MOD:
            return run(getChild(tree,0)) % run(getChild(tree,1));
        case DEF: { 
            int k = tree->getChildCount(tree);//获得子树的数量
            int init_val = 0;
            for (int i = 0; i < k; i++) {
                pANTLR3_BASE_TREE child = getChild(tree, i);//把第i颗子树提取1出来
                string var(getText(child));//获得当前子树根结点的字符串
                init_val = 0;
                if (child->getChildCount(child) == 1) {//有初始值
                    init_val = run(getChild(child, 0));//第一颗子树传进去
                }
                cout << "set param val : " << var << " = " << init_val << endl;
                this->set_param(var, init_val);//如果变量存在就报错
            }
            return init_val;
        } break;
        
        case block: {
               


        } break;


        case ASSIGN: {
            string var(getText(getChild(tree,0)));
            get_param(var);
            int val = run(getChild(tree,1));
            memory[var] = val;
            return val;
        }
        default:
            cout << "Unhandled token: #" << tok->type << '\n';
            return -1;
        }
    }
    else {
        int k = tree->getChildCount(tree);
        int r = 0;
        for(int i = 0; i < k; i++) {
            r = run(getChild(tree, i));
            cout << "Evaluator result: " << r << endl;
        }
        return r;
    }
    return 0;
}
 
pANTLR3_BASE_TREE getChild(pANTLR3_BASE_TREE tree, unsigned i)
{
    assert(i < tree->getChildCount(tree));
    return (pANTLR3_BASE_TREE) tree->getChild(tree, i);
}

const char* getText(pANTLR3_BASE_TREE tree)
{
    return (const char*) tree->getText(tree)->chars;
}
