/*************************************************************************
	> File Name: master.h
	> Author: huguang
	> Mail: hug@haizeix.com
	> Created Time: 三  9/ 2 10:09:04 2020
 ************************************************************************/

#ifndef _MASTER_H
#define _MASTER_H

#include <memory>
#include <AST.h>
#include <parameter.h>

namespace haizei {

class IMaster {
public :
    virtual int run(ASTNode &, std::shared_ptr<Parameter> &) = 0;
};

class ExprMaster : public IMaster {
public :
    virtual int run(ASTNode &, std::shared_ptr<Parameter> &);
};

class ControlBlockMaster : public IMaster {
public :
    virtual int run(ASTNode &, std::shared_ptr<Parameter> &);
};

class ControlNoBlockMaster : public IMaster {
public :
    virtual int run(ASTNode &, std::shared_ptr<Parameter> &);
};

class PrintMaster : public IMaster {
public :
    virtual int run(ASTNode &, std::shared_ptr<Parameter> &);
};

} // end of namespace haizei
#endif
