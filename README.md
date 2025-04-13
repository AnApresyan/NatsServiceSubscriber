# Nats Subscriber Project

A simple application using a clear 3-layered architecture. The application subscribes to a message bus (Nuts service), processes the incoming messages, and
persists them into a PostgreSQL database.

## Prerequisites

### General Requirements
- **C++ Compiler** (Clang, GCC, or MSVC) with C++17 support
- [**CMake**](https://cmake.org/download/)
- [**Git**](https://git-scm.com/downloads)
- [**Docker Desktop**](https://www.docker.com/products/docker-desktop)

### macOS
- Install [Homebrew](https://brew.sh/) (Optional)

Install dependencies via Homebrew:
```bash
brew install libpqxx
brew tap nats-io/nats-tools
brew install nats
```

### Windows
- Install [Visual Studio](https://visualstudio.microsoft.com/downloads/) (C++ workload)
- Install [vcpkg](https://github.com/microsoft/vcpkg) (Recommended for dependencies)

Install dependencies via vcpkg:
```bash
vcpkg install libpqxx
```

## 🐳 Docker Setup

The project uses Docker Compose for PostgreSQL and NATS:

Start Docker containers:
```bash
docker compose up -d
```

Containers:
- **PostgreSQL**: Port `25432`
- **NATS Server**: Port `4222`

## Building the Project

Clone the repository:
```bash
git clone https://github.com/AnApresyan/NatsServiceSubscriber.git
cd NatsServiceSubscriber
```

Create build directory:
```bash
mkdir build && cd build
```

Configure and build:

**macOS/Linux**:
```bash
cmake ..
cmake --build .
```

**Windows**:
```bash
cmake -DCMAKE_TOOLCHAIN_FILE=[vcpkg-root]/scripts/buildsystems/vcpkg.cmake ..
cmake --build .
```

## Running the Application

Ensure Docker containers are running:
```bash
docker compose up -d
```

Start your application:
```bash
./nats_subscriber
```

## Testing the Application

Publish a test message:
```bash
nats pub updates "Hello, World!"
```

Check logs:
```
OK : Received NATS message: Hello, World!
OK : Saved to PostgreSQL: Hello, World! @ 2025-04-13 12:00:00
```

Verify message in PostgreSQL:
```bash
docker exec -it my_postgres psql -U nuts_user -d nuts_db
```
```sql
SELECT * FROM messages;
```

