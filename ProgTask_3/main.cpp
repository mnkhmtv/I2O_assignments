#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>

using namespace std;

// Function to print the cost table
void printTable(const vector<vector<int>> &C, const vector<int> &S, const vector<int> &D)
{
    cout << "       |  1     2     3     4   " << "Supply\n";
    cout << "-------|";
    for (int i = 0; i < 5; ++i)
    {
        cout << setfill('-') << setw(6) << "|";
    }

    cout << endl;
    int i = 0;
    for (const auto &row : C)
    {
        cout << "     " << i + 1 << " |";
        for (int cost : row)
        {
            cout << setfill(' ') << setw(5) << cost << "|";
        }
        cout << setw(5) << S[i] << "|\n";
        ++i;
    }
    cout << "-------|";
    for (int i = 0; i < 5; ++i)
    {
        cout << setfill('-') << setw(6) << "|";
    }
    cout << endl;
    cout << "Demand:|";
    for (int d : D)
        cout << setfill(' ') << setw(5) << d << "|";
    cout << setw(7) << "|\n";
}

// Check if the problem is balanced
bool isBalanced(const vector<int> &S, const vector<int> &D)
{
    int totalSupply = accumulate(S.begin(), S.end(), 0);
    int totalDemand = accumulate(D.begin(), D.end(), 0);
    return totalSupply == totalDemand;
}

// North-West Corner Method
vector<vector<int>> northWestCornerMethod(vector<int> S, vector<int> D)
{
    int m = S.size(), n = D.size();
    vector<vector<int>> x(m, vector<int>(n, 0));
    int i = 0, j = 0;
    while (i < m && j < n)
    {
        int allocation = min(S[i], D[j]);
        x[i][j] = allocation;
        S[i] -= allocation;
        D[j] -= allocation;
        if (S[i] == 0)
            i++;
        if (D[j] == 0)
            j++;
    }
    return x;
}

// Vogel's Approximation Method
vector<vector<int>> vogelsApproximationMethod(vector<int> S, vector<int> D, vector<vector<int>> C)
{
    int m = S.size(), n = D.size();
    vector<vector<int>> x(m, vector<int>(n, 0));
    vector<bool> rowDone(m, false), colDone(n, false);

    while (any_of(rowDone.begin(), rowDone.end(), [](bool v)
                  { return !v; }) ||
           any_of(colDone.begin(), colDone.end(), [](bool v)
                  { return !v; }))
    {

        // Calculate row and column penalties
        vector<int> rowPenalty(m, 0), colPenalty(n, 0);
        for (int i = 0; i < m; ++i)
        {
            if (!rowDone[i])
            {
                vector<int> rowCosts;
                for (int j = 0; j < n; ++j)
                {
                    if (!colDone[j])
                        rowCosts.push_back(C[i][j]);
                }
                if (rowCosts.size() > 1)
                    sort(rowCosts.begin(), rowCosts.end());
                if (rowCosts.size() > 1)
                    rowPenalty[i] = rowCosts[1] - rowCosts[0];
            }
        }
        for (int j = 0; j < n; ++j)
        {
            if (!colDone[j])
            {
                vector<int> colCosts;
                for (int i = 0; i < m; ++i)
                {
                    if (!rowDone[i])
                        colCosts.push_back(C[i][j]);
                }
                if (colCosts.size() > 1)
                    sort(colCosts.begin(), colCosts.end());
                if (colCosts.size() > 1)
                    colPenalty[j] = colCosts[1] - colCosts[0];
            }
        }

        // Find max penalty
        int maxPenalty = -1, maxRow = -1, maxCol = -1;
        for (int i = 0; i < m; ++i)
        {
            if (!rowDone[i] && rowPenalty[i] > maxPenalty)
            {
                maxPenalty = rowPenalty[i];
                maxRow = i;
                maxCol = -1;
            }
        }
        for (int j = 0; j < n; ++j)
        {
            if (!colDone[j] && colPenalty[j] > maxPenalty)
            {
                maxPenalty = colPenalty[j];
                maxRow = -1;
                maxCol = j;
            }
        }

        // Allocate based on min cost in the row or column with max penalty
        if (maxRow != -1)
        {
            int minCostCol = -1, minCost = 1e9;
            for (int j = 0; j < n; ++j)
            {
                if (!colDone[j] && C[maxRow][j] < minCost)
                {
                    minCost = C[maxRow][j];
                    minCostCol = j;
                }
            }
            int allocation = min(S[maxRow], D[minCostCol]);
            x[maxRow][minCostCol] = allocation;
            S[maxRow] -= allocation;
            D[minCostCol] -= allocation;
            if (S[maxRow] == 0)
                rowDone[maxRow] = true;
            if (D[minCostCol] == 0)
                colDone[minCostCol] = true;
        }
        else
        {
            int minCostRow = -1, minCost = 1e9;
            for (int i = 0; i < m; ++i)
            {
                if (!rowDone[i] && C[i][maxCol] < minCost)
                {
                    minCost = C[i][maxCol];
                    minCostRow = i;
                }
            }
            int allocation = min(S[minCostRow], D[maxCol]);
            x[minCostRow][maxCol] = allocation;
            S[minCostRow] -= allocation;
            D[maxCol] -= allocation;
            if (S[minCostRow] == 0)
                rowDone[minCostRow] = true;
            if (D[maxCol] == 0)
                colDone[maxCol] = true;
        }
    }
    return x;
}

// Russell's Approximation Method
vector<vector<int>> russellsApproximationMethod(vector<int> S, vector<int> D, const vector<vector<int>> &C)
{
    int m = S.size(), n = D.size();
    vector<vector<int>> x(m, vector<int>(n, 0));
    vector<int> u(m), v(n);

    // Compute initial potentials
    for (int i = 0; i < m; ++i)
        u[i] = *min_element(C[i].begin(), C[i].end());
    for (int j = 0; j < n; ++j)
    {
        v[j] = 1e9;
        for (int i = 0; i < m; ++i)
            v[j] = min(v[j], C[i][j] - u[i]);
    }

    // Allocate supplies and demands
    while (accumulate(S.begin(), S.end(), 0) > 0)
    {
        int maxDifference = -1, maxI = -1, maxJ = -1;
        for (int i = 0; i < m; ++i)
        {
            if (S[i] == 0)
                continue;
            for (int j = 0; j < n; ++j)
            {
                if (D[j] == 0)
                    continue;
                int difference = C[i][j] - u[i] - v[j];
                if (difference > maxDifference)
                {
                    maxDifference = difference;
                    maxI = i;
                    maxJ = j;
                }
            }
        }
        int allocation = min(S[maxI], D[maxJ]);
        x[maxI][maxJ] = allocation;
        S[maxI] -= allocation;
        D[maxJ] -= allocation;
    }
    return x;
}

// Function to display the result
void displayResult(const vector<vector<int>> &x)
{
    for (const auto &row : x)
    {
        for (int cell : row)
        {
            cout << setw(4) << cell << " ";
        }
        cout << "\n";
    }
}

int main()
{
    // Define the supply and demand vectors, and cost matrix
    vector<int> S = {160, 140, 170};     // Example supply vector
    vector<int> D = {120, 50, 190, 110}; // Example demand vector
    vector<vector<int>> C = {
        {7, 8, 1, 2},
        {4, 5, 9, 8},
        {9, 2, 3, 6}};

    // Check if the problem is balanced
    if (!isBalanced(S, D))
    {
        cout << "The problem is not balanced!\n";
        return 0;
    }

    // Display the input table
    printTable(C, S, D);

    // Find solutions using each method
    auto nwcSolution = northWestCornerMethod(S, D);
    cout << "\nNorth-West Corner Method Solution:\n";
    displayResult(nwcSolution);

    auto vogelsSolution = vogelsApproximationMethod(S, D, C);
    cout << "\nVogel's Approximation Method Solution:\n";
    displayResult(vogelsSolution);

    auto russellsSolution = russellsApproximationMethod(S, D, C);
    cout << "\nRussell's Approximation Method Solution:\n";
    displayResult(russellsSolution);

    return 0;
}
