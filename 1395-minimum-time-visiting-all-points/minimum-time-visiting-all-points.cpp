class Solution {
public:
    int minTimeToVisitAllPoints(vector<vector<int>>& points) {
        int tot = 0;
        for(int i=0;i<points.size()-1; i++){
            int x_dist = abs(points[i+1][0] - points[i][0]);
            int y_dist = abs(points[i+1][1] - points[i][1]);

            tot +=max(x_dist, y_dist);
        }
        return tot;
    }
};