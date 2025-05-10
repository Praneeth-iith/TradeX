#ifndef ENGINE_H
#define ENGINE_H

#include <string>
#include <queue>
#include <vector>

using namespace std;

struct order {
    string type;
    int id;
    string stock;
    float price;
    int shares;
    int timestamp;
    int ticks = 2;

    int normalisedPrice() const;
};

struct BuyComp {
    bool operator()(const order &order1, const order &order2) const;
};

struct SellComp {
    bool operator()(const order &order1, const order &order2) const;
};

// Function declarations
void addBuy(priority_queue<order, vector<order>, BuyComp>& buyOrders, order buyOrder);
void addSell(priority_queue<order, vector<order>, SellComp>& sellOrders, order sellOrder);

void matchTrade(priority_queue<order, vector<order>, SellComp>& sellOrders,
                priority_queue<order, vector<order>, BuyComp>& buyOrders,
                order newOrder);

void showOrders(priority_queue<order, vector<order>, SellComp>& sellOrders,
                priority_queue<order, vector<order>, BuyComp>& buyOrders,
                string stock);

#endif 