#include <iostream>
#include <queue>
#include <vector>


// Customer class
class Customer {
public:
    int number;
    int arrivalTime;
    int departureTime;

    Customer(int num, int arrival) : number(num), arrivalTime(arrival), departureTime(-1) {}
};

// CustomerQueue class
class CustomerQueue {
private:
    std::queue<Customer> queue;

public:
    bool isEmpty() const {
        return queue.empty();
    }

    void enqueue(const Customer& customer) {
        queue.push(customer);
    }

    Customer dequeue() {
        Customer front = queue.front();
        queue.pop();
        return front;
    }

    int size() const {
        return queue.size();
    }
};

// Server class
class Server {
private:
    bool busy;
    int transactionTime;
    int remainingTime;

public:
    Server(int time) : busy(false), transactionTime(time), remainingTime(0) {}

    bool isBusy() const {
        return busy;
    }

    void startTransaction() {
        busy = true;
        remainingTime = transactionTime;
    }

    void processTransaction() {
        if (busy) {
            remainingTime--;
            if (remainingTime == 0) {
                busy = false;
            }
        }
    }
};

// ServerList class
class ServerList {
private:
    std::vector<Server> servers;

public:
    ServerList(int numServers, int transactionTime) {
        for (int i = 0; i < numServers; ++i) {
            servers.emplace_back(transactionTime);
        }
    }

    Server& getAvailableServer() {
        for (Server& server : servers) {
            if (!server.isBusy()) {
                return server;
            }
        }
        throw std::runtime_error("No available servers");
    }
};

int main() {
    int simulationTime, numServers, transactionTime, arrivalTimeDifference;

    // Get simulation parameters
    std::cout << "Enter the number of time units for the simulation: ";
    std::cin >> simulationTime;

    std::cout << "Enter the number of servers: ";
    std::cin >> numServers;

    std::cout << "Enter the server transaction time units: ";
    std::cin >> transactionTime;

    std::cout << "Enter time units between customer arrivals: ";
    std::cin >> arrivalTimeDifference;

    // Initialize simulation components
    CustomerQueue customerQueue;
    ServerList serverList(numServers, transactionTime);

    int currentTime = 0;
    int customerNumber = 1;

    // Simulation loop
    while (currentTime < simulationTime) {
        // Handle customer arrivals
        if (currentTime % arrivalTimeDifference == 0) {
            Customer customer(customerNumber, currentTime);
            customerQueue.enqueue(customer);
            std::cout << "Customer number: " << customer.number << " arrived at time unit: " << currentTime << std::endl;
            customerNumber++;
        }

        // Handle server transactions
        for (Server& server : serverList) {
            if (server.isBusy()) {
                server.processTransaction();
                if (!server.isBusy()) {
                    std::cout << "From server: " << server.number << " customer " << server.currentCustomer.number
                              << " departed at time unit " << currentTime << std::endl;
                }
            } else if (!customerQueue.isEmpty()) {
                Customer customer = customerQueue.dequeue();
                server.startTransaction(customer);
                std::cout << "From server: " << server.number << " customer " << customer.number
                          << " departed at time unit " << currentTime + transactionTime << std::endl;
            }
        }

        currentTime++;
    }

    // Print simulation results
    std::cout << "Number of customers left in queue: " << customerQueue.size() << std::endl;
    std::cout << "Number of customers that arrived: " << customerNumber - 1 << std::endl;
    std::cout << "Number of customers who completed a transaction: " << customerNumber - 1 - customerQueue.size()
              << std::endl;
    // Calculate and print average wait time (if needed)
    // ...

    return 0;
}
