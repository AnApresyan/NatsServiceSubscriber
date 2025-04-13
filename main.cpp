#include "src/API/NatsSubscriber/NatsSubscriber.hpp"
#include "src/Business/MessageProcessor/MessageProcessor.hpp"
#include "src/Data/PostgresStorage/PostgresStorage.hpp"
#include <iostream>
#include <memory>

int main() {
    const std::string connectionString = "dbname=nuts_db user=nuts_user password=nuts_password host=localhost port=25432";

    auto processor = std::make_shared<MessageProcessor>();
    auto storage = std::make_shared<PostgresStorage>(connectionString);

    NatsSubscriber subscriber(processor, storage);

    std::cout << "Starting NATS subscriber..." << std::endl;
    subscriber.start();
    
    return 0;
}
