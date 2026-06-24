#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include "json.hpp"
#include<chrono>
using namespace std;
struct Node{
    int y,x;
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



int main(int argc, char* argv[]){

    if (argc < 4) {
        std::cerr << "Usage: ./{executable} <graph.json> <queries.json> <output.json>\n";
        return 1;
    }

    std::string graph_json_file = argv[1];
    std::string query_json_file = argv[2];
    std::string output_file = argv[3];

    std::ifstream file1(graph_json_file);

    if (!file1.is_open()) {
        std::cerr << "Error: Could not open " << graph_json_file << '\n';
        return 1;
    }

    nlohmann::json graph_json;
    file1 >> graph_json; // reading the graph_json file into json 

	/*!!! Need changes here !!!*/ 
	
	// Create a Graph class that takes the json input
	// and stores the required graph data structures.
	// Remember to include the header file containing the class.
	// Uncomment the line below after implementing the class.
	Graph map(graph_json);
    
    std::ifstream file2(query_json_file);   

    if (!file2.is_open()) {
        std::cerr << "Error: Could not open " << query_json_file << '\n';
        return 1;
    }

    nlohmann::json query_json;
    file2 >> query_json; // reading the query_json file into json object

    nlohmann::json output_json;

    output_json["meta"] = {{"id", query_json["meta"]["id"]}};
    output_json["results"] = nlohmann::json::array();

    std::string type;

    for(auto event : query_json["events"]){

        type = event["type"];

		/* Refer to the sample code below */
        /*
        if(type == "remove_edge") {
            int edge_id = event["edge_id"];
            bool b = remove_edge(map, edge_id);
            nlohmann::json out;
            out["id"] = event["id"];
            out["done"] = b;
            std::cout << out.dump(4) << std::endl;
            output_json["results"].push_back(out);
        }
        */
    }

    return 0;
}