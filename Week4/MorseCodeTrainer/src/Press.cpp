#include "Press.h"

Press::Press(long start, long stop)
{
    this->start = start;
    this->duration = (stop - start);
    this->next = nullptr;
}

Press::~Press()
{
    this->deleteSequence();
}

std::shared_ptr<Press> Press::createNext(long start, long stop)
{
    this->next = std::make_shared<Press>(start, stop);
    return this->next;
}

long Press::getEndTime()
{
    return this->start + this->duration;
}

int Press::deleteSequence()
{
    int counter = 0;
    auto current = this->next;
    while (current != nullptr)
    {
        auto next = current->next;
        current->next = nullptr;
        current = next;
        counter++;
    }
        return counter;
    }

    int Press::countSequence()  {
        int counter = 0;
        std::shared_ptr<Press> current = this->next;
        counter++;
        while (current != nullptr)
        {
            counter++;
            current = current->next;
        }
        return counter;
    }

