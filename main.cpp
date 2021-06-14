#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#define ll long long int
using namespace std;

struct Transaction
{
    string id;
    ll fee;
    ll weight;
    vector<string> parentTransaction;
};

struct FeeByWeightAndOriginalIndex
{
    double feeByWeightIndividual;
    int originalIndex;
};

vector<Transaction> transactions;
map<string, ll> indexOfId;
vector<FeeByWeightAndOriginalIndex> feeByWeight;
vector<Transaction> allIncludedTransactions;
vector<bool> visited;
ll totalWeight = 0, totalFee = 0;
ll maxWeight = 4000000;

bool operator<(FeeByWeightAndOriginalIndex a, FeeByWeightAndOriginalIndex b)
{
    return a.feeByWeightIndividual > b.feeByWeightIndividual;
}

void sortTransactionsWrtWeightByFee()
{
    feeByWeight.resize(transactions.size());
    for (int i = 0; i < feeByWeight.size(); i++)
    {
        feeByWeight[i].feeByWeightIndividual = (double(transactions[i].fee) / double(transactions[i].weight));
        feeByWeight[i].originalIndex = i;
    }
    sort(feeByWeight.begin(), feeByWeight.end());
}

void getTransactionsForGivenConstraints()
{
    cout << "Calculating the transactions that are optimal for the given constraints." << endl;
    sortTransactionsWrtWeightByFee();
    bool done = false;
    visited.resize(transactions.size(), false);
    while (!done)
    {
        done = true;
        for (int i = 0; i < transactions.size(); i++)
        {
            if (totalWeight + transactions[feeByWeight[i].originalIndex].weight <= maxWeight && visited[feeByWeight[i].originalIndex] == false)
            {
                bool valid = true;
                for (auto j : transactions[feeByWeight[i].originalIndex].parentTransaction)
                {
                    if (!visited[indexOfId[j]])
                    {
                        valid = false;
                        break;
                    }
                }
                if (valid)
                {
                    totalWeight += transactions[feeByWeight[i].originalIndex].weight;
                    totalFee += transactions[feeByWeight[i].originalIndex].fee;
                    visited[feeByWeight[i].originalIndex] = true;
                    allIncludedTransactions.push_back(transactions[feeByWeight[i].originalIndex]);
                    done = false;
                    break;
                }
            }
        }
    }
    cout << "Maximum Possible Fee that can be earned by the miner is: " << totalFee << endl;
    cout << "The total block weight to get the above fee is: " << totalWeight << endl;
}

void readMempoolFile()
{
    cout << "Reading data from \"mempool.csv\"" << endl;
    ifstream mempoolCsv("mempool.csv");
    string blockData;

    getline(mempoolCsv, blockData);

    while (getline(mempoolCsv, blockData))
    {
        Transaction tempTransaction;
        string substr;
        stringstream ss(blockData);

        for (int i = 0; i < 4; i++)
        {
            getline(ss, substr, ',');
            switch (i)
            {
            case 0:
                tempTransaction.id = substr;
                break;

            case 1:
                tempTransaction.fee = atoi(substr.c_str());
                break;

            case 2:
                tempTransaction.weight = atoi(substr.c_str());
                break;

            case 3:
                stringstream ss2(substr);
                while (getline(ss2, substr, ';'))
                {
                    tempTransaction.parentTransaction.push_back(substr);
                }
                break;
            }
        }
        indexOfId[tempTransaction.id] = transactions.size();
        transactions.push_back(tempTransaction);
    }
    mempoolCsv.close();
    cout << "Data successfully read from \"mempool.csv\"" << endl;
}

void writeOutputToTxtFile()
{
    cout << "Writing transaction IDs to \"block.txt\"" << endl;
    ofstream outputTransactions("block.txt");
    for (int i = 0; i < allIncludedTransactions.size(); i++)
    {
        outputTransactions << allIncludedTransactions[i].id << endl;
    }
    outputTransactions.close();
    cout << allIncludedTransactions.size() << " have been successfully written to \"block.txt\"" << endl;
}

int main()
{
    readMempoolFile();
    getTransactionsForGivenConstraints();
    writeOutputToTxtFile();

    return 0;
}