#include "PostgresStorage.hpp"
#include <pqxx/pqxx>
#include <iostream>

PostgresStorage::PostgresStorage(const std::string& connStr)
    : connStr_(connStr)
{ }

void PostgresStorage::save(const std::string& content, const std::string& timestamp) {
    try {
        pqxx::connection conn(connStr_);
        pqxx::work txn(conn);

        // Insert the content and timestamp into the messages table.
        txn.exec(
            "INSERT INTO messages (content, timestamp) VALUES (" +
            txn.quote(content) + ", " +
            txn.quote(timestamp) + ")"
        );

        txn.commit();
        std::cout << "OK : Saved to PostgreSQL: " << content
                  << " @ " << timestamp << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "X : PostgresStorage error: " << e.what() << std::endl;
    }
}
