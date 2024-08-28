struct Point {
    long long x, y;
    bool operator<(const Point& p) const {
        return x < p.x || (x == p.x && y < p.y);
    }
};
class KDTree {
private:
    struct Node {
        Point point;
        Node* left;
        Node* right;
        Node(Point p) : point(p), left(nullptr), right(nullptr) {}
    };
    Node* root;

    Node* build(vector<Point>& points, int depth) {
        if (points.empty()) return nullptr;
        int axis = depth % 2;
        sort(points.begin(), points.end(), [axis](Point a, Point b) {
            return axis ? a.y < b.y : a.x < b.x;
        });
        int mid = points.size() / 2;
        Node* node = new Node(points[mid]);
        vector<Point> leftPoints(points.begin(), points.begin() + mid);
        vector<Point> rightPoints(points.begin() + mid + 1, points.end());
        node->left = build(leftPoints, depth + 1);
        node->right = build(rightPoints, depth + 1);
        return node;
    }

    long long dist(Point p1, Point p2) {
        // change your dist to suit your calculation
        return abs(p1.x - p2.x) + abs(p1.y - p2.y);
    }

    void nearest(Node* node, Point target, int depth, long long& bestDist) {
        if (!node) return;
        long long currentDist = dist(node->point, target);
        if (currentDist < bestDist) bestDist = currentDist;

        int axis = depth % 2;
        Node* next = (axis ? target.y < node->point.y : target.x < node->point.x) ? node->left : node->right;
        Node* other = next == node->left ? node->right : node->left;

        nearest(next, target, depth + 1, bestDist);

        if ((axis ? abs(target.y - node->point.y) : abs(target.x - node->point.x)) < bestDist) {
            nearest(other, target, depth + 1, bestDist);
        }
    }

public:
    KDTree(vector<Point>& points) {
        root = build(points, 0);
    }

    long long nearest(Point target) {
        long long bestDist = numeric_limits<long long>::max();
        nearest(root, target, 0, bestDist);
        return bestDist;
    }
};