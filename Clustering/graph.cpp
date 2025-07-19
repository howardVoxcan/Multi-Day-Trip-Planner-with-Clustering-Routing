#include <bits/stdc++.h>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Location2D{
    float latitude;
    float longtitude;
};

float distance(Location2D First, Location2D Second)
{
    return sqrt(pow(First.latitude - Second.latitude, 2) + pow(First.longtitude - Second.longtitude, 2));
}

bool isSame(const Location2D& a, const Location2D& b, float eps = 1e-4) {
    return (fabs(a.latitude - b.latitude) < eps) && (fabs(a.longtitude - b.longtitude) < eps);
}

Location2D average(const vector<Location2D>& locationList){
    Location2D averageLoc;
    averageLoc.latitude = 0;
    averageLoc.longtitude = 0;

    for (int i = 0; i < locationList.size(); i++){
        averageLoc.latitude += locationList[i].latitude;
        averageLoc.longtitude += locationList[i].longtitude;
    }

    return {averageLoc.latitude / locationList.size(), averageLoc.longtitude / locationList.size()};
}

int chooseCluster(const vector<Location2D>& centerPoints, const Location2D& point) {
    int clusterChoose = 0;
    float min_distance = distance(centerPoints[0], point);

    for (int i = 1; i < centerPoints.size(); i++) {
        float d = distance(centerPoints[i], point);
        if (d < min_distance) {
            clusterChoose = i;
            min_distance = d;
        }
    }

    return clusterChoose;
}

void clustering(vector<Location2D>& locationList, int clusterNum) {
    vector<Location2D> centerPoints(clusterNum);
    vector<vector<Location2D>> clusters(clusterNum);
    int change = 1;

    for (int i = 0; i < clusterNum; i++)
        centerPoints[i] = {i + 1.0, i + 1.0};

    while (change != 0) {
        change = 0;

        for (auto& cluster : clusters) cluster.clear();

        for (const auto& point : locationList) {
            int clusterIdx = chooseCluster(centerPoints, point);
            clusters[clusterIdx].push_back(point);
        }

        vector<Location2D> oldCenters = centerPoints;

        for (int i = 0; i < clusterNum; i++) {
            if (!clusters[i].empty()) {
                centerPoints[i] = average(clusters[i]);

                if (!isSame(centerPoints[i], oldCenters[i])) {
                    change = 1;
                }
            }
        }
    }
}

int main()
{
    return 0;
}
