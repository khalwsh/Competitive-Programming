struct Point {
    long long x, y, z;
    bool operator<(const Point& p) const {
        return x < p.x || (x == p.x && (y < p.y || (y == p.y && z < p.z)));
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
        int axis = depth % 3;
        sort(points.begin(), points.end(), [axis](Point a, Point b) {
            if (axis == 0) return a.x < b.x;
            if (axis == 1) return a.y < b.y;
            return a.z < b.z;
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
        return abs(p1.x - p2.x) + abs(p1.y - p2.y) + abs(p1.z - p2.z);
    }
    
    void nearest(Node* node, Point target, int depth, long long& bestDist) {
        if (!node) return;
        long long currentDist = dist(node->point, target);
        if (currentDist < bestDist) bestDist = currentDist;
        
        int axis = depth % 3;
        Node* next = (axis == 0 ? target.x < node->point.x : 
                      (axis == 1 ? target.y < node->point.y : target.z < node->point.z)) ? node->left : node->right;
        Node* other = next == node->left ? node->right : node->left;
        
        nearest(next, target, depth + 1, bestDist);
        
        long long axisDist = (axis == 0 ? abs(target.x - node->point.x) : 
                              (axis == 1 ? abs(target.y - node->point.y) : abs(target.z - node->point.z)));
        if (axisDist < bestDist) {
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