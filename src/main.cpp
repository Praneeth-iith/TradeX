#include "Engine.h"
#include<iostream>
#include<queue>
#include<unordered_map>
using namespace std;

unordered_map<int,bool> trackID;

int main(){
    bool run = true;
    int timer = 1;
    std::cout<<"------Welcome to TradeX------\n";
    std::cout<<"Type MAN to see Manual\n";
    while(run){
        string command;
        cin>>command;
        if(command=="ADDCOMPANY"){
            std::cout<<"Name: ";
            string name;
            cin>>name;
            addCompany(name);
        }else if(command=="MAKEORDER"){
            string type ;
            cin>>type;
            int ID;
            cin>>ID;
            string stock;
            cin>>stock;
            float price;
            cin>>price;
            int shares;
            cin>>shares;
            if (price <= 0 || shares <= 0) {
                std::cout << "Price/shares must be positive.\n";
                continue;
            }
            if (type != "BUY" && type != "SELL") {
               std:: cout << "Invalid order type (use BUY/SELL).\n";
                continue;
            }            
            if(trackID.count(ID) > 0 ){
               std:: cout<<"ID already exists\n";
            }else{
                if(buyBooks.count(stock) == 0){
                    std::cout<<stock<<" is not available on TradeX\n";
                }else{
                trackID[ID]=true;
                order newOrder(type,ID,stock,price,shares,timer);
                timer++;
                matchTrade( sellBooks[stock] , buyBooks[stock], newOrder );
                }
            }
        }else if(command=="EXIT"){
            break;
        }else if(command=="SHOWCOMPANIES"){
            showCompanies();
        }
        else if(command=="MAN"){
            std::cout << "-----TradeX Manual-----\n";
            std::cout << "Welcome to TradeX, a simple order matching system for managing stock buy and sell orders.\n";
            std::cout << "The following commands are available:\n\n";
        
            // List commands
            std::cout << "1. ADDCOMPANY\n";
            std::cout << "   - Usage: ADDCOMPANY\n";
            std::cout << "   - Description: Adds a new company to the system. You will be prompted to enter the company's name.\n\n";
        
            std::cout << "2. MAKEORDER\n";
            std::cout << "   - Usage: MAKEORDER <type> <ID> <stock> <price> <shares>\n";
            std::cout << "   - Description: Creates a new order for buying or selling a stock.\n";
            std::cout << "     - <type>: Type of the order (BUY or SELL)\n";
            std::cout << "     - <ID>: Unique identifier for the order.\n";
            std::cout << "     - <stock>: Name of the stock.\n";
            std::cout << "     - <price>: Price per share for the order.\n";
            std::cout << "     - <shares>: Number of shares for the order.\n\n";
        
            std::cout << "3. SHOWORDERS\n";
            std::cout << "   - Usage: SHOWORDERS\n";
            std::cout << "   - Description: Displays all current orders for all companies, showing both buy and sell orders in the order book.\n\n";
        
            std:: cout << "4. SHOWCOMPANIES\n";
            std::cout << "   - Usage: SHOWCOMPANIES\n";
            std::cout << "   - Description: Displays all the companies currently added to the TradeX system.\n\n";
        
            std::cout << "5. EXIT\n";
            std::cout << "   - Usage: EXIT\n";
            std::cout << "   - Description: Exits the program.\n\n";
        
            std::cout << "6. MAN\n";
            std::cout << "   - Usage: MAN\n";
            std::cout << "   - Description: Displays this manual with a list of available commands and their descriptions.\n\n";
        
            std::cout << "System Behavior & Rules:\n";
            std::cout << "1. Order Matching:\n";
            std::cout << "   - A buy order will match with a sell order if the buy price is greater than or equal to the sell price.\n";
            std::cout << "   - Orders will be executed based on price and timestamp priority.\n\n";
        
            std::cout << "2. Order Book:\n";
            std::cout << "   - Each stock has its own order book.\n";
            std::cout << "   - Buy orders are sorted in descending order of price.\n";
            std::cout << "   - Sell orders are sorted in ascending order of price.\n";
            std::cout << "   - If an order does not match an existing order, it is added to the order book.\n\n";
        
            std::cout << "3. Unique Order IDs:\n";
            std:: cout << "   - Each order must have a unique ID. If you attempt to place an order with an existing ID, the system will reject it.\n\n";
        
            std::cout << "4. Order Execution:\n";
            std::cout << "   - The system automatically attempts to match buy and sell orders as soon as a new order is placed.\n\n";
            
            std::cout << "5. Stock Management:\n";
            std::cout << "   - You must add a company using the ADDCOMPANY command before placing any orders for that stock.\n\n";
            
            std::cout << "Example Scenario:\n";
            std::cout << "1. Add a Company:\n";
            std::cout << "   ADDCOMPANY\n";
            std::cout << "   Name: Apple\n\n";
            std:: cout << "2. Place Buy and Sell Orders:\n";
            std::cout << "   MAKEORDER BUY 101 Apple 150.5 100\n";
            std::cout << "   MAKEORDER SELL 102 Apple 151.0 50\n\n";
            std::cout << "3. View Current Orders:\n";
            std::cout << "   SHOWORDERS\n\n";
            std::cout << "4. View All Companies:\n";
            std::cout << "   SHOWCOMPANIES\n\n";
            std::cout << "5. Exit the System:\n";
            std::cout << "   EXIT\n\n";        
        }else if(command=="SHOWORDERS"){
            for(auto pair : buyBooks){
                showOrders(sellBooks[pair.first],buyBooks[pair.first],pair.first);
            }
        }else{
            std::cout<<"Invalid Command\n";
        }
    }
}