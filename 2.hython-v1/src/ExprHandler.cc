#include <ExprHandler.h>
#include <iostream>


bool VarHandler::Test(int token){
    return token == INT || token == ID;
}
int VarHandler::run(haizei::ASTNode tree, int token, ExprTreeEvaluator *tmp){
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
            return tmp->get_param(tree.text());
        }
    }
}

bool CalHandler::Test(int token){
    return token == PLUS || token == MINUS || token == TIMES || token == DIV || token == MOD;
}
int CalHandler::run(haizei::ASTNode tree, int token, ExprTreeEvaluator *tmp){
    switch(tree.type()) {
        case PLUS:
            return tmp->run(tree[0]) + tmp->run(tree[1]);
        case MINUS:
            return tmp->run(tree[0]) - tmp->run(tree[1]);
        case TIMES:
            return tmp->run(tree[0]) * tmp->run(tree[1]);
        case DIV:
            return tmp->run(tree[0]) / tmp->run(tree[1]);
        case MOD:
            return tmp->run(tree[0]) % tmp->run(tree[1]);
    }
}

bool LogHandler::Test(int token){
    return token == OR || token == AND || token == GT || token == LITTLE || token == EQ || token == GE || token == LE || token == NE;
}
int LogHandler::run(haizei::ASTNode tree, int token, ExprTreeEvaluator *tmp){
    switch(tree.type()) {
        case OR: return tmp->run(tree[0]) || tmp->run(tree[1]);
        case AND: return tmp->run(tree[0]) && tmp->run(tree[1]);
        case GT: return tmp->run(tree[0]) > tmp->run(tree[1]);
        case LITTLE: return tmp->run(tree[0]) < tmp->run(tree[1]);
        case EQ: return tmp->run(tree[0]) == tmp->run(tree[1]);
        case GE: return tmp->run(tree[0]) >= tmp->run(tree[1]);
        case LE: return tmp->run(tree[0]) <= tmp->run(tree[1]);
        case NE: return tmp->run(tree[0]) != tmp->run(tree[1]);
    }
}

bool ProcHandler::Test(int token){
    return token == PRINT || token == IF || token == FOR || token == WHILE || token == DOWHILE;
}
int ProcHandler::run(haizei::ASTNode tree, int token, ExprTreeEvaluator *tmp){
    switch(tree.type()) {
        case PRINT: {
            for (int i = 0; i < tree.size(); i++) {
                i && std::cout << " ";
                std::cout << tmp->run(tree[i]);
            }
            std::cout << std::endl;
            return 0;
        }
        case IF:{
            ExprTreeEvaluator new_this(tmp);
            if(new_this.run(tree[0])){
                new_this.run(tree[1]);
            }else if(tree.size() == 3){
                new_this.run(tree[2]);
            }
            return 0;
        }
        case FOR:{
            ExprTreeEvaluator new_this(tmp);
            for(new_this.run(tree[0]); new_this.run(tree[1]); new_this.run(tree[2])){
                new_this.run(tree[3]);
            }
            return 0;
        }

        case WHILE:{
            ExprTreeEvaluator new_this(tmp);
            while(new_this.run(tree[0])){
                new_this.run(tree[1]);
            }
            return 0;
        }

        case DOWHILE:{
            ExprTreeEvaluator new_this(tmp);
            do{
                new_this.run(tree[1]);
            }while(new_this.run(tree[0]));
            return 0;
        }
    }
}

bool BaseHandler::Test(int token){
    return token == BLOCK || token == DEF || token == ASSIGN;
}
int BaseHandler::run(haizei::ASTNode tree, int token, ExprTreeEvaluator *tmp){
    switch(tree.type()) {
        case BLOCK: {
            ExprTreeEvaluator new_this(tmp);
            for (int i = 0; i < tree.size(); i++) {
                int val = new_this.run(tree[i]);
                //cout << "Block Value : " << val << endl;
            }
            return 0;
        } break;
        case DEF: {
            //std::cout << "DEF" << std::endl;
            int init_val = 0;
            for (int i = 0; i < tree.size(); i++) {
                std::string var(tree[i].text());
                init_val = 0;
                if (tree[i].size() == 1) {
                    init_val = tmp->run(tree[i][0]);
                }
                //cout << "def param val : " << var << " = " << init_val << endl;
                tmp->def_param(var, init_val);
            }
            return init_val;
        } break;
        case ASSIGN: {
            std::string var(tree[0].text());
            tmp->get_param(var);
            int val = tmp->run(tree[1]);
            tmp->set_param(var, val);
            return val;
        }
    }
}

bool DefHandler::Test(int token){
    return true;
}
int DefHandler::run(haizei::ASTNode tree, int token, ExprTreeEvaluator *tmp){
    std::cout << "Unhandled token: #" << tree.type() << '\n';
    return -1;
}



ExprHandler *SingletonPattern::head = nullptr;

ExprHandler *SingletonPattern::getInstance(){
    if(head == nullptr){
        BuildSingleton();
    }
    return head;
}

void SingletonPattern::BuildSingleton(){
    head = new VarHandler();
    head->next = new BaseHandler();
    head->next->next = new CalHandler();
    head->next->next->next = new LogHandler();
    head->next->next->next->next = new ProcHandler();
    head->next->next->next->next->next = new DefHandler();
    return;
}

SingletonPattern::SingletonPattern() = default;
SingletonPattern::SingletonPattern(const SingletonPattern &a) = default;
SingletonPattern::~SingletonPattern(){}
