#include <bits/stdc++.h>
#include <stdlib.h>
#include <time.h> 
 
using namespace std;
long long mod = 1e9 + 7;
double EPS = 1e-12;
typedef long long int lld;
typedef pair<lld,lld> PA;
long double tick(){static clock_t oldt; clock_t newt=clock();
	long double diff=1.0L*(newt-oldt)/CLOCKS_PER_SEC; oldt = newt; return diff; }
#define rep(i,a,n) for(long long int i = (a); i <= (n); ++i)
#define repI(i,a,n) for(int i = (a); i <= (n); ++i)
#define repD(i,a,n) for(long long int i = (a); i >= (n); --i)
#define repDI(i,a,n) for(int i = (a); i >= (n); --i)
inline lld sc() { lld a; scanf("%lld", &a); return a; }
inline int scd() { int a; scanf("%d", &a); return a; }
#define prL(a) printf("%lld\n",a)
#define prS(a) printf("%lld ",a)
#define prdL(a) printf("%d\n",a)
#define prdS(a) printf("%d ",a)
#define all(c) (c).begin(), (c).end()
#define sz(a) ((int)a.size())
#ifdef LOCAL_RUN
#define Error(x...) { cout << "(" << #x << ")" << " = ( "; printIt(x); }
#else
#define Error(x...) 42
#endif
template <typename T1> void printIt(T1 t1) { cout << t1 << " )" << endl; }
template <typename T1, typename... T2>
void printIt(T1 t1, T2... t2) { cout << t1 << " , "; printIt(t2...); }
#define popcount __builtin_popcountll

#define lim 200010
#define lim2 200010
// std::ios::sync_with_stdio(false); // Ab :)
vector<int> G[lim];
lld ans = 0;
int k1, k2;


lld Fen[lim];

lld ReadFen(lld idx) {
    Error(idx, ans);
    if (idx < 0) return 0;
    return Fen[idx];
}

void ChangeFen(lld idx, lld n, lld val) {
	Fen[idx] += val;
}

// Problem Using Centroid Decomposition

// Uses G[lim] for edges to build itself
struct CentroidDecomposition {
	vector<int> Parent;
	vector<int> Sz;
	vector<bool> Alive;
	int currNodesRem;
	CentroidDecomposition(int n) {
		Parent.resize(n + 3);
		Sz.resize(n + 3);
		Alive.resize(n + 3, true);
	}
	// intial call with root, parent sth like (1,-1) to build
	void build(int x, int par) {
		findSz(x, par);
		currNodesRem = Sz[x];
		int centroid =  findCentriod(x, par);
		Parent[centroid] = par;
		Alive[centroid] = false;

		// do sth with the centroid
		// Problem Specific Section Start
        mxDepth = 0;
		for(auto c : G[centroid]) {
            if(!Alive[c]) continue;
			findAns(c, centroid, 1, false);
			findAns(c, centroid, 1, true);
		}
        repI(i, 1, mxDepth) ChangeFen(i, lim - 1, -ReadFen(i));
        Error(centroid, ans);

		// Problem Specific Section End

		for(auto c : G[centroid]) {
			if(Alive[c]) build(c, centroid);
		}
	}

	void findSz(int x, int par) {
		Sz[x] = 1;
		for(auto c : G[x]) {
			if(c != par and Alive[c]) {
				findSz(c, x);
				Sz[x] += Sz[c];
			}
		}
	}

	int findCentriod(int x, int par) {
		for(auto c : G[x]) {
			if(c != par and Alive[c]) {
				if(Sz[c] > currNodesRem / 2) return findCentriod(c, x);
			}
		}
		return x;
	}

	// Problem Specific Variables and Functions
    int mxDepth;
	void findAns(int x, int par, int depth, bool populating) {
        if(depth > k2) return;
        mxDepth = max(mxDepth, depth);
        Error(x);
		if(populating) ChangeFen(depth, lim - 1, 1);
		else {
            ans += ReadFen(k2 - depth);
            if(k1 <= depth and depth <= k2) ans++;
        }
		for(auto c : G[x]) {
			if(c != par and Alive[c]) findAns(c, x, depth + 1, populating);
		}
	}
};


int main(){
	int n = scd();
    k1 = scd();
    // k2 = scd();
    k2 = k1;
    repI(i, 1, n - 1) {
        int u = scd();
        int v = scd();
        G[u].push_back(v);
        G[v].push_back(u);
    }
    CentroidDecomposition cd(n);
    cd.build(1, -1);
    prL(ans);
	return 0;
}