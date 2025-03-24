mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
long long myRand(long long B) {
	return (unsigned long long)rng() % B;
}

struct node {
    int sz;
    int prior;
    int val;
    node* l, * r;
    bool rev;
    node() {
        l = nullptr, r = nullptr;
        sz = 0;
    }
    node(int _val) {
        l = nullptr, r = nullptr;
        val = _val;
        sz = 1, prior = myRand();
    }
};

int get_sz(node* v) {
    if (!v) return 0;
    return v->sz;
}

void update(node* v) {
    if (v) {
        v->sz = get_sz(v->l) + get_sz(v->r) + 1;
    }
}

void push(node *v) {
    if(!v) return;
    if(v->rev) {
        swap(v->l, v->r);
        if(v->l) (v->l)->rev ^= 1;
        if(v->r) (v->r)->rev ^= 1;
    }
    v->rev = 0;
}

void split(node* root, node*& l, node*& r, int k) { // after execution l will have (first k), and r (root->sz - k) elements
    push(root);
    if (!root) {
        l = r = nullptr;
        return;
    }
    if (get_sz(root->l) >= k) {
        split(root->l, l, root->l, k);
        r = root;
        update(r);
    } else {
        split(root->r, root->r, r, k - get_sz(root->l) - 1);
        l = root;
        update(l);
    }
}

void merge(node*& root, node* l, node* r) {
    push(l);
    push(r)
    if (!l || !r) {
        root = l ? l : r;
        return;
    }
    if (l->prior > r->prior) {
        merge(l->r, l->r, r);
        root = l;
    } else {
        merge(r->l, l, r->l);
        root = r;
    }
    update(root);
}
