/*************************************************************************
	> File Name: single.h
	> Author: huguang
	> Mail: hug@haizeix.com
	> Created Time: 三  9/ 2 09:52:25 2020
 ************************************************************************/

#ifndef _SINGLE_H
#define _SINGLE_H
#include <handle.h>
#include <mutex>

namespace haizei {

class Singleton {
public :
protected:
    Singleton() = default;
    static std::mutex m_mutex;
};

class MasterChainSingle : public Singleton {
public :
    static int run(ASTNode, std::shared_ptr<Parameter> &);
private:
    static const IHandle *get();
    MasterChainSingle() = delete;
    static const IHandle *SingleInit();
    static const IHandle *object;
};

}

#endif
