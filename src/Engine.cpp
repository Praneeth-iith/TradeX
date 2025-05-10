#include "Engine.h"
#include<iostream>
#include<queue>
using namespace std;

struct order{
    string type;
    int id;
    string stock;
    float price;
    int shares;
    int timestamp;
    int ticks=2;

    int normalisedPrice() const {
        return ticks*price;
    }
};



struct BuyComp{
    bool operator()(const order &order1, const order &order2)const{
        if(order1.normalisedPrice() != order2.normalisedPrice() ){
            return order1.normalisedPrice() < order2.normalisedPrice();
        }else{
            return order1.timestamp > order2.timestamp;
        } 
    }
};

struct SellComp{
    bool operator()(const order &order1, const order &order2)const{
        if(order1.normalisedPrice() != order2.normalisedPrice() ){
            return order1.normalisedPrice() > order2.normalisedPrice();
        }else{
            return order1.timestamp > order2.timestamp;
        } 
    }
};

void addBuy(priority_queue<order,vector<order>,BuyComp> &buyOrders, order buyOrder){
    if(buyOrder.shares != 0) buyOrders.push(buyOrder);
}

void addSell(priority_queue<order,vector<order>,SellComp> &sellOrders, order sellOrder){
    if(sellOrder.shares != 0) sellOrders.push(sellOrder);
}

void matchTrade(priority_queue<order,vector<order>,SellComp> &sellOrders , priority_queue<order,vector<order>,BuyComp> &buyOrders , order newOrder){
    if(newOrder.type=="BUY"){
        if(sellOrders.empty()){
            addBuy(buyOrders,newOrder);
            cout<<"Order didn't match,added to Orderbook"<<endl;
            return;
        }
        order bestOrder = sellOrders.top();

        if( newOrder.normalisedPrice() < bestOrder.normalisedPrice()){
            addBuy(buyOrders,newOrder);
            cout<<"Order didn't match,added to Orderbook"<<endl;
        }else{
            while(!sellOrders.empty() && newOrder.shares > 0 && newOrder.normalisedPrice() >= bestOrder.normalisedPrice()){
                sellOrders.pop();
                if(newOrder.shares >= bestOrder.shares){
                    newOrder.shares -= bestOrder.shares; 
                    bestOrder.shares = 0;
                    addBuy(buyOrders,newOrder);
                }else{
                    bestOrder.shares -= newOrder.shares;
                    newOrder.shares = 0;
                    addSell(sellOrders,bestOrder);
                }
                cout<<"Trade Executed\nBuyer order ID: "<<newOrder.id<<"\nSeller order ID: "<<bestOrder.id<<"\nStock: "<<bestOrder.stock<<"\nPrice per share: "<<bestOrder.price<<endl;
                bestOrder = sellOrders.top();
            }
        }
    }else{
        if(buyOrders.empty()){
            addSell(sellOrders,newOrder);
            cout<<"Order didn't match,added to Orderbook"<<endl;
            return;
        }
        order bestOrder = buyOrders.top();

        if( newOrder.normalisedPrice() > bestOrder.normalisedPrice()){
            addSell(sellOrders,newOrder);
            cout<<"Order didn't match,added to Orderbook"<<endl;
        }else{
            while(!buyOrders.empty() && newOrder.shares > 0 && newOrder.normalisedPrice() <= bestOrder.normalisedPrice()){
                buyOrders.pop();
                if(newOrder.shares >= bestOrder.shares){
                    newOrder.shares -= bestOrder.shares; 
                    bestOrder.shares = 0;
                    addSell(sellOrders,newOrder);
                }else{
                    bestOrder.shares -= newOrder.shares;
                    newOrder.shares = 0;
                    addBuy(buyOrders,bestOrder);
                }
                cout<<"Trade Executed\nBuyer order ID: "<<newOrder.id<<"\nSeller order ID: "<<bestOrder.id<<"\nStock: "<<bestOrder.stock<<"\nPrice pre share: "<<bestOrder.price<<endl;
                bestOrder = buyOrders.top();
            }
        }
    }
}

void showOrders(priority_queue<order,vector<order>,SellComp> &sellOrders , priority_queue<order,vector<order>,BuyComp> &buyOrders,string stock){
    cout<<"Order book for Stock: "<<stock<<endl;
    if(sellOrders.empty()){
        cout<<"No sell orders\n";
    }else{
        cout<<"----Sell Orders----\n";
        priority_queue<order,vector<order>,SellComp> orders = sellOrders;
        while(!orders.empty()){
            order temp = orders.top();
            cout<<"ID: "<<temp.id<<" | Price: "<<temp.price<<" | Shares: "<<temp.shares<<endl; 
        orders.pop();
        }
    }
    if(buyOrders.empty()){
        cout<<"No buy orders\n";
    }else{
        cout<<"----Buy Orders----\n";
        priority_queue<order,vector<order>,BuyComp> orders = buyOrders;
        while(!orders.empty()){
            order temp = orders.top();
            cout<<"ID: "<<temp.id<<" | Price: "<<temp.price<<" | Shares: "<<temp.shares<<endl; 
        orders.pop();
        }
    }
}