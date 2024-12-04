#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
using namespace std;
static const float PI = 3.14159265358979323846;
char list_of_names[7] = { 'L', 'T', 'B' };
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
bool correct_name(string line)
{
    bool flag = false;
    for(const char& name_from_list : list_of_names)
    {
        if(line[0] == name_from_list) { flag = true; break; }
    }
    for(int i = 1; i < line.size(); ++i)
    {
        if (line[i] > '9' || line[i] < '0') { flag = false; break;}
    }
    return flag;
}
class L
{
    int len;
    int amount;
    float cost;
public: 
    L(int len, int amount, float cost)
    {
        this->len = len;
        this->amount = amount;
        this->cost = cost;
    }
};
class T
{
    float angle;
    int amount;
    float cost;
    float len;
    float r = 3;
public: 
    T(float angle, int amount, float cost)
    {
        this->angle = angle;
        this->amount = amount;
        this->cost = cost;
        this->r = 3;
        this->len = 2 * r * PI;
    }
};
class B
{
    int amount;
    float cost;
    int len = 4;
    float center = 2;
public: 
    B(int amount, float cost)
    {
        this->amount = amount;
        this->cost = cost;
        this->len = 4;
        this->center = len/2;
    }
};

class Data
{
    string name;
    int len;
    int amount;
    int cost;
public:
    Data(string name, int len, int amount, int cost)
    {
        this->name = name;
        this->len = len;
        this->amount = amount;
        this->cost = cost;
    }
    Data(string& line)
    {
        string name_and_amount;
        std::stringstream ss(line);
        ss >> name_and_amount >> len >> cost;
        if (correct_name(name_and_amount))
        {
            name = name_and_amount[0];
            name_and_amount = stoi(name_and_amount.substr(1));
        }
        else
        {
            std::cerr << "Invalid information in Data: " << name << std::endl;
            name = ""; 
            amount = 0;
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

void skip_comment(string& line)
{
    if(line.find("--")!= std::string::npos)
    {
        line = line.erase(line.find("--"), line.size() - 1 );
        if(line.size() == 0)
        {
            line = "/";
        }
    }
}
int main() {

    string line;
    vector<string> text;
    vector<Data> data_arr;
    vector<Route> route_arr;
    vector<Order> order_arr;
    int indicator = 0;

    ifstream file("LILA_5.txt");  
    if (!file) { 
        cerr << "Невозможно открыть файл" << endl;
        return 1;
    }

    bool flag_new_block = false;
    while (getline(file, line)) { 
        skip_comment(line);
        if (line == "/" && !flag_new_block)
        {
            flag_new_block = true;
            continue;
        }
        else if (line == "DATA" && flag_new_block)
        {
            flag_new_block = false;
            indicator = 1;
            continue;
        }
        else if (line == "ROUTE" && flag_new_block)
        {
            flag_new_block = false;
            indicator = 2;
            continue;
        }
        else if (line == "ORDER" && flag_new_block)
        {
            flag_new_block = false;
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
    if(data_arr.size() == 0)
    {
        cout << "Отсутствует блок Data";
    }
    if(route_arr.size() == 0)
    {
        cout << "Отсутствует блок Route";
    }
    if(order_arr.size() == 0)
    {
        cout << "Отсутствует блок Order";
    }
    return 0;
}
