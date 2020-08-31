/*************************************************************************
	> File Name: ExprTreeEvaluator.cc
	> Author: 
	> Mail:
	> Created Time: 一  8/24 10:24:49 2020
 ************************************************************************/
#include<ExprTreeEvaluator.h>
#include<iostream>
#include<cassert>
using namespace std;

ExprTreeEvaluator::ExprTreeEvaluator() : next(nullptr) {}

ExprTreeEvaluator::ExprTreeEvaluator(ExprTreeEvaluator *next) : next(next) {}

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
    if(tree.hasToken()){
        for(auto p = SingletonPattern::getInstance(); p; p = p->next){
            if(p->Test(tree.type())){
                return p->run(tree, tree.type(), this);
            }
        }
    }
    else{
        int r = 0;
        for(int i = 0; i < tree.size(); i++) {
            cout << "tree type :" << tree[i].type() << endl;
            for(auto p = SingletonPattern::getInstance(); p; p = p->next){
                if(p->Test(tree[i].type())){
                    r = p->run(tree[i], tree[i].type(), this);
                }
            }
            //cout << "Evaluator result: " << r << endl;
        }
        return r;
    }





    /*
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

        case OR: return run(tree[0]) || run(tree[1]);
        case AND: return run(tree[0]) && run(tree[1]);
        case GT: return run(tree[0]) > run(tree[1]);
        case LITTLE: return run(tree[0]) < run(tree[1]);
        case EQ: return run(tree[0]) == run(tree[1]);
        case GE: return run(tree[0]) >= run(tree[1]);
        case LE: return run(tree[0]) <= run(tree[1]);
        case NE: return run(tree[0]) != run(tree[1]);



        case BLOCK: {
            ExprTreeEvaluator new_this(this);
            for (int i = 0; i < tree.size(); i++) {
                int val = new_this.run(tree[i]);
                //cout << "Block Value : " << val << endl;
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
                //cout << "def param val : " << var << " = " << init_val << endl;
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
        case PRINT: {
            for (int i = 0; i < tree.size(); i++) {
                i && std::cout << " ";
                std::cout << run(tree[i]);
            }
            std::cout << std::endl;
            return 0;
        }
        case IF:{
            ExprTreeEvaluator new_this(this);
            if(new_this.run(tree[0])){
                new_this.run(tree[1]);
            }else if(tree.size() == 3){
                new_this.run(tree[2]);
            }
            return 0;
        }
        case FOR:{
            ExprTreeEvaluator new_this(this);
            for(new_this.run(tree[0]); new_this.run(tree[1]); new_this.run(tree[2])){
                new_this.run(tree[3]);
            }
            return 0;
        }

        case WHILE:{
            ExprTreeEvaluator new_this(this);
            while(new_this.run(tree[0])){
                new_this.run(tree[1]);
            }
            return 0;
        }

        case DOWHILE:{
            ExprTreeEvaluator new_this(this);
            do{
                new_this.run(tree[1]);
            }while(new_this.run(tree[0]));
            return 0;
        }

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
    return 0;*/
}
