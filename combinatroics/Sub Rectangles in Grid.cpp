int n,m;
int AllSubRectangles() {
    return (n * (n + 1) / 2) * (m * (m + 1) / 2);
}
int Contain(int MinX , int MaxX , int MinY , int MaxY){
    return (MinX * (n - MaxX + 1)) * (MinY) * (m - MaxY + 1);
}