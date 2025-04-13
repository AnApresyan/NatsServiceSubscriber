#include "NatsSubscriber.hpp"
#include <nats/nats.h>
#include <iostream>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
#include "../../Business/MessageProcessor/IMessageProcessor.hpp"
#include "../../Data/PostgresStorage/IMessageStorage.hpp"


std::string getCurrentTimestamp() {
    auto now = std::chrono::system_clock::now();
    std::time_t timeNow = std::chrono::system_clock::to_time_t(now);
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&timeNow), "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

NatsSubscriber::NatsSubscriber(std::shared_ptr<IMessageProcessor> processor,
                               std::shared_ptr<IMessageStorage> storage)
    : processor_(processor), storage_(storage)
{ }

void NatsSubscriber::onMessage(natsConnection *nc, natsSubscription *sub,
                               natsMsg *msg, void *closure)
{
    auto self = static_cast<NatsSubscriber*>(closure);
    std::string rawMsg = natsMsg_GetData(msg);
    std::cout << "OK : Received NATS message: " << rawMsg << std::endl;
    
    std::string processed = self->processor_->process(rawMsg);
    self->storage_->save(processed, getCurrentTimestamp());
    
    natsMsg_Destroy(msg);
}

void NatsSubscriber::start() {
    natsConnection *conn = nullptr;
    natsOptions *opts = nullptr;
    natsStatus s;

    s = natsOptions_Create(&opts);
    s = natsConnection_Connect(&conn, opts);

    if (s == NATS_OK) {
        std::cout << "OK : Connected to NATS. Subscribing to subject 'updates'..." << std::endl;
        s = natsConnection_Subscribe(&sub_, conn, "updates", &NatsSubscriber::onMessage, this);
        if (s == NATS_OK) {
            std::cout << "OK : Subscribed successfully." << std::endl;
            while (true) {
                ;
            }
        } else {
            std::cerr << "X : Subscription failed: " << natsStatus_GetText(s) << std::endl;
        }
    } else {
        std::cerr << "X : NATS connection failed: " << natsStatus_GetText(s) << std::endl;
    }

    natsOptions_Destroy(opts);
    natsConnection_Destroy(conn);
}
