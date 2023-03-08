#ifndef PRESS_H_
#define PRESS_H_
#include <memory>


struct Press {
    /* data */
    public:
    long start;
    int duration;
    std::shared_ptr<Press> next;

    Press(long, long);
    virtual ~Press();

    std::shared_ptr<Press> createNext(long, long);
    long getEndTime();
    int deleteSequence();
    int countSequence();
};  

#endif