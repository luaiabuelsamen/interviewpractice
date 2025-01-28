#include <iostream>


typedef std::pair<uint32_t, uint32_t> pii;

uint32_t shortest_path(
    std::unordered_map<uint32_t, pii >& graph, 
    uint32_t start, 
    uint32_t goal){

    
    std::unordered_map<uint32_t, uint32_t> shortest_path;
    for(const auto& node: graph){
        shortest_path[node.first] = UINT32_MAX;
    }
    shortest_path[0] = 0;

    std::priority_queue<std::vector<uint32_t> > q;
    q.push({0, start});
    while(q.size()){
        std::vector<uint32_t> cur = q.top();
        q.pop();

        if(cur[0] > shortest_path[cur[1]]){
            continue;
        }

        for (auto& neighbor : graph[cur[1]]) {
            uint32_t idx = neighbor.second;
            uint32_t weight = neighbor.weight;

            if(weight + cur[0] < shortest_path[idx]){
                shortest_path[idx] += weight + cur[0];
                q.push({ weight + cur[0], idx});
            }
        }
    }

    return shortest_path[goal];
}