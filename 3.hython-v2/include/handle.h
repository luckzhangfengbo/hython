/*************************************************************************
	> File Name: handle.h
	> Author: huguang
	> Mail: hug@haizeix.com
	> Created Time: 三  9/ 2 09:27:26 2020
 ************************************************************************/

#ifndef _HANDLE_H
#define _HANDLE_H

#include <AST.h>
#include <master.h>
#include <memory>

namespace haizei {

class IHandle {
public :
    IHandle(IHandle *);
    virtual bool Test(const ASTNode &) const = 0;
    virtual std::shared_ptr<IMaster> getMaster() const = 0;
    IHandle *next() const;

private:
    IHandle *__next;
};

class ExprHandle : public IHandle {
public :
    ExprHandle(IHandle *);
    bool Test(const ASTNode &) const ;
    virtual std::shared_ptr<IMaster> getMaster() const;
};

class ControlBlockHandle : public IHandle {
public :
    ControlBlockHandle(IHandle *);
    bool Test(const ASTNode &) const;
    virtual std::shared_ptr<IMaster> getMaster() const;
};

class ControlNoBlockHandle : public IHandle {
public :
    ControlNoBlockHandle(IHandle *);
    bool Test(const ASTNode &) const;
    virtual std::shared_ptr<IMaster> getMaster() const;
};

class PrintHandle : public IHandle {
public :
    PrintHandle(IHandle *);
    bool Test(const ASTNode &) const;
    virtual std::shared_ptr<IMaster> getMaster() const;
};

}

#endif
