#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

string list_of_names[7] = { "L1", "L2", "L3", "L4", "T4", "T8", "B1" };
bool name_in_list(string& name)
{
    bool flag = false;
    for (const string& name_from_list : list_of_names) {
        if (name == name_from_list) {
            flag = true;
            break;
        }
    }
    return flag;
}

class Data
{
    string name;
    int len;
    int cost;
public:
    Data(string name, int len, int cost)
    {
        this->name = name;
        this->len = len;
        this->cost = cost;
    }
    Data(string& line)
    {
        std::stringstream ss(line);
        ss >> name >> len >> cost;
        if (!name_in_list(name)) {
            std::cerr << "Invalid name: " << name << std::endl;
            name = ""; 
        }
    }
};

class Route
{
    int x;
    int y;
    int v;
public:
    Route(int x, int y, int z)
    {
        this->x = x;
        this->y = y;
        this->v = v;
    }
    Route(string& line)
    {
        std::stringstream ss(line);
        ss >> x >> y >> v;
    }
};
class Order
{
    string name;
    int direction;
public:
    Order(string name, int direction) {
        this->name = name;
        this->direction = direction;
    }
    Order(string& line)
    {
        std::stringstream ss(line);
        ss >> name >> direction;
        if (!name_in_list(name)) {
            std::cerr << "Invalid name: " << name << std::endl;
            name = "";
        }
    }
};


int main() {

    string line;
    vector<string> text;
    vector<Data> data_arr;
    vector<Route> route_arr;
    vector<Order> order_arr;
    int indicator = 0;

    ifstream file("LILA_5.txt");  
    if (!file) { 
        cerr << "Не удалось открыть файл" << endl;
        return 1;
    }

    while (getline(file, line)) { 
        if (line == "/")
        {
            continue;
        }
        else if (line == "DATA")
        {
            indicator = 1;
            continue;
        }
        else if (line == "ROUTE")
        {
            indicator = 2;
            continue;
        }
        else if (line == "ORDER")
        {
            indicator = 3;
            continue;
        }
        else
        {
            switch (indicator)
            {
            case 1:
                data_arr.push_back(Data(line));
            case 2:
                route_arr.push_back(Route(line));
            case 3:
                order_arr.push_back(Order(line));
            default:
                cout << "wrong file";
                break;
            }
        }
    }
    file.close();  
    return 0;
}
