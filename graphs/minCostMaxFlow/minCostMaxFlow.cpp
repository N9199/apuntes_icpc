#include "../../headers/headers.h"

struct MinCostFlow
{
    struct FlowEdge
    {
        int u, v;
        ll cap, flow = 0, cost;
        FlowEdge(int u, int v, ll cap, ll cost) : u(u), v(v), cap(cap), cost(cost) {}
    };
    const ll INF = 1e18;
    vector<FlowEdge> edges;
    vector<vector<int>> adj;
    int n, m = 0;
    vector<int> parent;
    vector<ll> dist, pi;
    typedef pair<ll, int> state;
    priority_queue<state, vector<state>, greater<state>> PQ;

    MinCostFlow(int n) : n(n)
    {
        adj.resize(n);
        parent.resize(n);
        pi.resize(n);
        dist.resize(n);
    }
    void reset()
    {
        for (FlowEdge &e : edges)
            e.flow = 0;
    }
    void add_edge(int u, int v, ll cap, ll cost)
    {
        edges.emplace_back(u, v, cap, cost);
        edges.emplace_back(v, u, 0, -cost);
        adj[u].push_back(m);
        adj[v].push_back(m + 1);
        m += 2;
    }
    ll get_pi(int u)
    {
        if (pi[u] != INF)
            return pi[u];
        for (int i : adj[u])
        {
            FlowEdge &e = edges[i];
            if (e.cap == 0)
                pi[u] = min(pi[u], get_pi(e.v) - e.cost);
        }
        return pi[u];
    }
    ll min_cost_flow(int K, int s, int t)
    {
        ll flow = 0, cost = 0;
        fill(pi.begin(), pi.end(), INF);
        pi[s] = 0;
        for (int u = 0; u < n; ++u)
            pi[u] = get_pi(u);
        while (flow < K)
        {
            fill(dist.begin(), dist.end(), INF);
            dist[s] = 0;
            PQ.emplace(0, s);

            while (!PQ.empty())
            {
                state s = PQ.top();
                PQ.pop();
                int u = s.second;
                ll d = s.first;
                if (dist[u] < d)
                    continue;
                for (int i : adj[u])
                {
                    FlowEdge &e = edges[i];
                    int v = e.v;
                    if (e.cap > 0)
                    {
                        ll w = e.cost + pi[u] - pi[v];
                        assert(w >= 0);
                        if (d + w < dist[v])
                        {
                            parent[v] = i;
                            dist[v] = d + w;
                            PQ.emplace(dist[v], v);
                        }
                    }
                }
            }
            if (dist[t] == INF)
                break;

            ll f = K - flow;
            int cur = t;
            while (cur != s)
            {
                int i = parent[cur];
                f = min(f, edges[i].cap);
                cur = edges[i].u;
            }
            flow += f;
            cost += f * (dist[t] + pi[t] - pi[s]);
            cur = t;
            while (cur != s)
            {
                int i = parent[cur];
                edges[i].cap -= f;
                edges[i ^ 1].cap += f;
                cur = edges[i].u;
            }
            for (int u = 0; u < n; ++u)
                pi[u] += dist[u];
        }

        if (flow < K)
            return -1;
        else
            return cost;
    }
};