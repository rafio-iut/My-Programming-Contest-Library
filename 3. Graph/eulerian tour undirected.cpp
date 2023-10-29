#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using llu = unsigned long long;

#define CEIL(x, y) ((x) + (y) - 1) / (y); 
#define print_case(tc) cout << "Case " << (tc) << ":\n"
#define all(con) begin(con), end(con)
#define sz(con) ((int)con.size())

#ifdef Pennyroyal
    #include <debug.h>
#else
    #define debug(...)
#endif

const int inf = 1e9 + 505;
const ll infll = 1e18 + 505;
const int MOD = 1000000007;

const int nmax = 205;
const int mmax = 40005;

int n, m;
vector<pair<int, int>> g[nmax];

int done[nmax], visited[mmax];
vector<int> path;

void clear() {
    for(int i = 0; i < nmax; i++) {
        done[i] = 0;
        g[i].clear();
    }
    for(int i = 0; i < mmax; i++) visited[i] = 0;
    path.clear();
}

void DFS(int u) {
    while(done[u] < sz(g[u])) {
        auto e = g[u][done[u]++];
        if(visited[e.second]) continue;
        visited[e.second] = 1;
        DFS(e.first);
    }
    path.emplace_back(u);
}

bool canTour(int n) {
    int edges = 0;
    vector<int> deg(n + 1);
    for(int u = 1; u <= n; u++) {
        for(auto e : g[u]) {
            deg[e.first]++;
            deg[u]++;
            edges++;
        }
    }

    int odd = 0, root = 0;
    for(int i = 1; i <= n; i++) {
        if(odd > 2) return false;
        if(deg[i] & 1)
            odd++, root = i;
    }

    if(root == 0) {
        for(int i = 1; i <= n; i++)
            if(deg[i]) root = i;
    }

    if(!root) return true;

    DFS(root);

    if(sz(path) != edges / 2 + 1) return false;
    
    reverse(all(path));
    return true;
}

void solve(void) {
    cin >> n >> m;

    clear();
    vector<int> deg(n + 1);

    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back({v, i});
        g[v].push_back({u, i});
        deg[u]++, deg[v]++;        
    }

    int extra = m;
    for(int i = 1; i <= n; i++) {
        if(deg[i] & 1) {
            ++extra;
            g[n + 1].push_back({i, extra});
            g[i].push_back({n + 1, extra});
        }
    }

    if(canTour(n + 1)) {
        debug(path);

        vector<int> in(n + 2), out(n + 2);
        for(int i = 0; i + 1 < sz(path); i++) {
            if(path[i] != n + 1 && path[i + 1] != n + 1) {
                out[path[i]]++;
                in[path[i + 1]]++;
            }
        }

        int ans = 0;
        for(int i = 1; i <= n; i++) {
            ans += (in[i] == out[i]);
        }

        cout << ans << '\n';
        for(int i = 0; i + 1 < sz(path); i++) {
            if(path[i] != n + 1 && path[i + 1] != n + 1) {
                cout << path[i] << ' ' << path[i + 1] << '\n';
            }
        }
    }
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int testcase = 1;
    // cin >> testcase;
    for(int tc = 1; tc <= testcase; tc++) {
        // print_case(tc);
        solve();
    }

    return 0;
}