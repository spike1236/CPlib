// Add or delete numbers and find maximum xor of a number with the numbers in the trie

struct node {
    node *to[2];
    int cnt;
    node () {
        to[0] = to[1] = nullptr;
        cnt = 0;
    }
};

node *root = new node();

void add(int x) {
    node *v = root;
    for(int i = 30; i >= 0; --i) {
        int bit = ((x >> i) & 1);
        if(v -> to[bit] == nullptr) v -> to[bit] = new node();
        v = v -> to[bit];
        v -> cnt++;
    }
}

void del(int x) {
    node *v = root;
    for(int i = 30; i >= 0; --i) {
        int bit = ((x >> i) & 1);
        v = v -> to[bit];
        v -> cnt--;
    }
}

int get(int x) {
    int cur = 0;
    node *v = root;
    for(int i = 30; i >= 0; --i) {
        int bit = ((x >> i) & 1);
        if(v -> to[bit ^ 1] != nullptr && (v -> to[bit ^ 1]) -> cnt) {
            if(!bit) cur |= (1 << i);
            v = v -> to[bit ^ 1];
        } else if(v -> to[bit] != nullptr && (v -> to[bit]) -> cnt) {
            if(bit) cur |= (1 << i);
            v = v -> to[bit];
        } else return (cur ^ x);
    }
    return (cur ^ x);
}

void solve() {
    add(0);
    int n;
    cin >> n;
    for(int i = 1; i <= n; ++i) {
        char type;
        cin >> type;
        int x;
        cin >> x;
        if(type == '+') add(x);
        else if(type == '-') del(x);
        else cout << get(x) << '\n';
    }
}
