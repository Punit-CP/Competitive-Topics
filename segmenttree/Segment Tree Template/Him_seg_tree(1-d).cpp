class Node {
    public:
    int len;
    int ans;

    Node() : len(1), ans(0) {};
    Node(int val) : len(1), ans(val) {};
};

Node combine(Node &a, Node &b) {
    Node c;
    c.len = a.len + b.len;
    c.ans = a.ans + b.ans;
    return c;
}

void build(vector<Node> &tree, vector<int> &a, int n) {
    for (int i = 0; i < n; i++) {
        tree[i + n] = Node(a[i]);
    }
    for (int i = n - 1; i > 0; i--) {
        tree[i] = combine(tree[(i << 1)], tree[(i << 1 | 1)]);
    }
}

Node query(vector<Node> &tree, int n, int l, int r) {
    Node ansl, ansr;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) {
            ansl = combine(ansl, tree[l]);
            l += 1;
        }
        if (r & 1) {
            r -= 1;
            ansr = combine(tree[r], ansr);
        }
    }
    return combine(ansl, ansr);
}

void update(vector<Node> &tree, int n, int p, int v) {
    tree[p += n] = Node(v);
    while (p >>= 1) {
        tree[p] = combine(tree[(p << 1)], tree[(p << 1 | 1)]);
    }
}

Node query(vector<Node> &tree, int n, int p) {
    Node ans;
    for (p += n; p > 0; p >>= 1) {
        ans = combine(ans, tree[p]);
    }
    return ans;
}

void update(vector<Node> &tree, int n, int l, int r, int v) {
    Node temp = Node(v);
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) {
            tree[l] = combine(tree[l], temp);
            l += 1;
        } else {
            r -= 1;
            tree[r] = combine(tree[r], temp);
        }
    }
}

void push(vector<Node> &tree, int n) {
    for (int i = 1; i < n; i++) {
        tree[(i << 1)] = combine(tree[(i << 1)], tree[i]);
        tree[(i << 1 | 1)] = combine(tree[(i << 1 | 1)], tree[i]);
        tree[i] = Node();
    }
}
