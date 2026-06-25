#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include "json.hpp"
#include<chrono>
#include <queue>
#include <map>
#include <vector>
#include <cmath>
using namespace std;
struct Node{
    int y,x;
    bool operator==(const Node& a) const{
        return (x==a.x)&&(y==a.y);
    }
    bool operator<(const Node& a) const{
        if(y != a.y) return y < a.y;
        return x < a.x;
    }
};

class Graph {
    public:
    int rows,cols;
    vector<vector<bool> >obstacle;
    Graph(nlohmann::json data){
        rows= data["grid_size"]["rows"];
        cols= data["grid_size"]["cols"];
        obstacle.assign(rows, vector<bool>(cols,false));
        for(auto x: data["obstacles"]){
            obstacle[x["y"]][x["x"]]=true;
        }
    }
    vector<Node> get_neighbors(Node current){
        vector<Node>neighbors(4);
        neighbors[0]={current.y+1,current.x};
        neighbors[1]={current.y-1,current.x};
        neighbors[2]={current.y,current.x+1};
        neighbors[3]={current.y,current.x-1};

        vector<Node>correct_neighbors;
        for(int i=0; i<4; i++){
            int y=neighbors[i].y;
            int x=neighbors[i].x;
            if(y>=0 && x>=0 && y<rows && x<cols && !obstacle[y][x]){
                correct_neighbors.push_back(neighbors[i]);
            }
        }
        return correct_neighbors;
    }
};