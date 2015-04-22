#pragma once

#include "utility.h"

class edge{
public:
    int from;
    int to;
    LL cost;

    edge(){}
    edge(int f,int t,LL c)
        : from(f), to(t), cost(c)
    {
    }
    edge reverse() const
    {
        return {to,from,cost};
    }
};

class graph{
public:
    int size; //頂点数
    vector<vector<edge>> edges;
    graph(){
    }
    graph(int n)
        : edges(n), size(n)
    {
    }
    void init(int _size){
        edges.clear();
        edges.resize(_size);
        size = _size;
    }
    void push_edge(const edge& e){
        edges[e.from].push_back(e);
        edges[e.to].push_back(e.reverse());
    }
};

class dijkstra_result{
public:
    const vector<LL> cost; //最短距離
    const LL result;

    dijkstra_result(const vector<LL>& c, LL res)
        : cost(c), result(res)
    {
    }
    dijkstra_result(const vector<LL>&& c, LL res)
        : cost(c), result(res)
    {
    }
};

dijkstra_result dijkstra(const graph& g, int from, int to, bool all = false){
    asc_pqueue<pair<LL,int>> que;
    vector<LL> v(g.size);
    vector<bool> f(g.size);
    fill(v.begin(), v.end(), INF);
    que.push({0, from});
    v[from] = 0;
    while((!que.empty())){
        auto p = que.top();
        que.pop();
        int n = p.second;
        if(v[n] < p.first)
            continue;
        f[n] = true;
        for(const auto& m : g.edges[n]){
            if(v[m.to] > v[n] + m.cost){
                v[m.to] = min(v[n] + m.cost, v[m.to]);
                que.push({v[m.to], m.to});
            }
        }
    }
    int r = v[to];
    return {v, r};
}
