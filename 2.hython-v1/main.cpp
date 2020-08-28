/*************************************************************************
	> File Name: main.cpp
	> Author: huguang
	> Mail: hug@haizeix.com
	> Created Time: 一  8/24 10:24:49 2020
 ************************************************************************/

#include <hythonLexer.h>
#include <hythonParser.h>
#include <cassert>
#include <map>
#include <string>
#include <iostream>
#include <AST.h>
using std::map;
using std::string;
using std::cout;
using std::endl;
 
class ExprTreeEvaluator {
    map<string,int> memory;
public:
    ExprTreeEvaluator() : next(nullptr) {}
    ExprTreeEvaluator(ExprTreeEvaluator *next) : next(next) {}
    int run(haizei::ASTNode);
    void def_param(string, int);
    void set_param(string, int);
    int get_param(string);
    ExprTreeEvaluator *next;
};
 
int main(int argc, char* argv[]) {
    assert(argc > 1);
    haizei::ASTNode tree(argv[1]);
    
    ExprTreeEvaluator eval;
    int rr = eval.run(tree);
    cout << "Evaluator result: " << rr << '\n';
    tree.destroy();
    return 0;
}

void ExprTreeEvaluator::def_param(string name, int val) {
    if (memory.find(name) != memory.end()) {
        #ifdef DEBUG
        for (auto x : memory) {
            cout << "debug log(memory) : " << x.first << " " << x.second << endl;
        }
        #endif
        throw std::runtime_error("param redefined : " + name);
    }
    memory[name] = val;
    return ;
}

void ExprTreeEvaluator::set_param(string name, int val) {
    if (memory.find(name) == memory.end()) {
        if (this->next) {
            this->next->set_param(name, val);
            return ;
        }
        throw std::runtime_error("unknown param : " + name);
    }
    memory[name] = val;
    return ;
}

int ExprTreeEvaluator::get_param(string name) {
    if (memory.find(name) == memory.end()) {
        if (this->next) return this->next->get_param(name);
        throw std::runtime_error("unknown param : " + name);
    }
    return memory[name];
}

int ExprTreeEvaluator::run(haizei::ASTNode tree) {
    if(tree.hasToken()) {
        switch(tree.type()) {
        case INT: {
            std::string s = tree.text();
            if(s[0] == '~') {
                return -atoi(s.c_str() + 1);
            }
            else {
                return atoi(s.c_str());
            }
        }
        case ID: {
            return get_param(tree.text());
        }
        case PLUS:
            return run(tree[0]) + run(tree[1]);
        case MINUS:
            return run(tree[0]) - run(tree[1]);
        case TIMES:
            return run(tree[0]) * run(tree[1]);
        case DIV:
            return run(tree[0]) / run(tree[1]);
        case MOD:
            return run(tree[0]) % run(tree[1]);
        case BLOCK: {
            ExprTreeEvaluator new_this(this);
            for (int i = 0; i < tree.size(); i++) {
                int val = new_this.run(tree[i]);
                cout << "Block Value : " << val << endl;
            }
            return 0;
        } break;
        case DEF: { 
            int init_val = 0;
            for (int i = 0; i < tree.size(); i++) {
                string var(tree[i].text());
                init_val = 0;
                if (tree[i].size() == 1) {
                    init_val = run(tree[i][0]);
                }
                cout << "def param val : " << var << " = " << init_val << endl;
                this->def_param(var, init_val);
            }
            return init_val;
        } break;
        case ASSIGN: {
            string var(tree[0].text());
            get_param(var);
            int val = run(tree[1]);
            set_param(var, val);
            return val;
        }
        case PRINT :{
            int val = 0;
            for (int i = 0 ; i < tree.size(); i++) {
                val = run(tree[i]);
                cout << val << endl;
            }
            return 0;
        } break;
        case IF: {
            int val = 0;
            ExprTreeEvaluator new_this(this);
            val = new_this.run(tree[0]);//拿到值
            
            if (val) {
                new_this.run(tree[1]);
            } else {
                if (tree.size() == 3) new_this.run(tree[2]);
                return 0;
            }
            return 0;
        } break;
        case FOR: {
            int val1 = 0, val2  = 0, val3 = 0, val4 = 0;
            ExprTreeEvaluator new_this(this);
            val1 = new_this.run(tree[0]);
            val2 = new_this.run(tree[1]);
            val3 = new_this.run(tree[2]);
            val4 = new_this.run(tree[3]);
            for (int i = 0; i < tree.size();i++) {
                if (val1) {
                    new_this.run(tree[1]);
                    new_this.run(tree[2]);
                    new_this.run(tree[3]);
                } 
                return 0;
            }
            return 0;
            //for
        } break;

        case WHILE: {
           //while 
        } break;

        case DOWHILE: {
            //do_while
        } break;

        case OR: {
            return run(tree[0]) || run(tree[1]);
        } break; 
        case AND: {
            return run(tree[0]) && run(tree[1]);
        } break; 
        case GE: {
            return run(tree[0]) >= run( tree[1]);
        } break; 
        case NE: {
            return run(tree[0]) != run(tree[1]);
        } break; 
        case LITTLE: {
            return run(tree[0]) < run(tree[1]);
        } break; 
        case LE: {
            return run(tree[0])<= run(tree[1]);
        } break; 
        case GT: {
            return run(tree[0]) > run (tree[1]);
        } break; 
        case EQ: {
            return run(tree[0]) == run(tree[1]);
        } break; 
        default:
            cout << "Unhandled token: #" << tree.type() << '\n';
            return -1;
        }
    } else {
        int r = 0;
        for(int i = 0; i < tree.size(); i++) {
            r = run(tree[i]);
            cout << "Evaluator result: " << r << endl;
        }
        return r;
    }
    return 0;
}
