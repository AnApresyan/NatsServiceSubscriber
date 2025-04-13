#ifndef INATS_SUBSCRIBER_HPP
#define INATS_SUBSCRIBER_HPP

class INatsSubscriber {
public:
    virtual ~INatsSubscriber() = default;
    virtual void start() = 0;
};

#endif
