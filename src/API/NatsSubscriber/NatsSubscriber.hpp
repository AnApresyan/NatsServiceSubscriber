#ifndef NATS_SUBSCRIBER_HPP
#define NATS_SUBSCRIBER_HPP

#include "INatsSubscriber.hpp"
#include <memory>
#include <nats/nats.h>

class IMessageProcessor;
class IMessageStorage;

class NatsSubscriber : public INatsSubscriber {
public:
    NatsSubscriber(std::shared_ptr<IMessageProcessor> processor,
                   std::shared_ptr<IMessageStorage> storage);
    void start() override;

	static void onMessage(natsConnection *nc, natsSubscription *sub,
                               natsMsg *msg, void *closure);

private:
    std::shared_ptr<IMessageProcessor> processor_;
    std::shared_ptr<IMessageStorage> storage_;
    natsSubscription *sub_ = nullptr;
};

#endif
