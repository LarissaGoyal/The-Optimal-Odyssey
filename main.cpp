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
#include "graph.hpp"
using namespace std;

struct Result{
    bool path_found;
    int path_length;
    int nodes_explored;
    double time_ms;
    Result(){
        path_found=false;
        path_length=0;
        nodes_explored=0;
        time_ms=0;
    }
};

double dijkstra_h(Node a, Node b){
    return 0;
}
double astar_euclidean_h(Node a, Node b){
    return sqrt((a.y-b.y)*(a.y-b.y) + (a.x-b.x)*(a.x-b.x));
}
double astar_manhattan_h(Node a, Node b){
    return abs(a.x-b.x)+abs(a.y-b.y);
}

Result search(Graph& g, Node start, Node end, double (*h)(Node,Node)){
    auto start_t=chrono::high_resolution_clock::now();
    Result result;
    map<Node,Node>parent;
    map<Node,int>distance;
    priority_queue<pair<double,Node> >q;
    parent[start]=start;
    distance[start]=0;
    q.push({0,start});
    
    while(!q.empty()){
        Node current=q.top().second;
        q.pop();
        if(current==end){
            result.path_found=true;
            break;
        }

        for(auto next: g.get_neighbors(current)){
            int new_distance= distance[current]+1;
            
            if(distance.count(next)==0 || distance[next]>new_distance){
                if(distance.count(next)==0)
                    result.nodes_explored++;
                distance[next]=new_distance;
                double priority=-(new_distance+h(next,end));
                q.push({priority,next});
                parent[next]=current;
            }
        }
    }

    if(result.path_found){
        Node curr=end;
        while(!(parent[curr]==curr)){
            result.path_length++;
            curr=parent[curr];
        }
    }

    auto end_t=chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end_t - start_t;
    result.time_ms = duration.count();
    return result;
}

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
        if(type=="find_path"){
            Node start = {event["start"]["y"],event["start"]["x"]};
            Node end = {event["goal"]["y"],event["goal"]["x"]};

            Result dijkstra_result=search(map,start,end,dijkstra_h);
            Result astar_euclidean_result=search(map,start,end,astar_euclidean_h);
            Result astar_manhattan_result=search(map,start,end,astar_manhattan_h);

            nlohmann::json out;
            out["id"] = event["id"];
            out["dijkstra"] = {
                {"path_found", dijkstra_result.path_found},
                {"path_length", dijkstra_result.path_length},
                {"nodes_explored", dijkstra_result.nodes_explored},
                {"time_ms", dijkstra_result.time_ms}
            };
            out["astar_euclidean"] = {
                {"path_found", astar_euclidean_result.path_found},
                {"path_length", astar_euclidean_result.path_length},
                {"nodes_explored", astar_euclidean_result.nodes_explored},
                {"time_ms", astar_euclidean_result.time_ms}
            };
            out["astar_manhattan"] = {
                {"path_found", astar_manhattan_result.path_found},
                {"path_length", astar_manhattan_result.path_length},
                {"nodes_explored", astar_manhattan_result.nodes_explored},
                {"time_ms", astar_manhattan_result.time_ms}
            };

            output_json["results"].push_back(out);
        }
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
    std::ofstream out_file(output_file);
    out_file << output_json.dump(4);  
    out_file.close();
    return 0;
}