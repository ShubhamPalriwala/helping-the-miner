#include <fstream>
#include <vector>
#include <sstream>
#define ll long long int
using namespace std;

struct Transaction
{
    string id;
    ll fee;
    ll weight;
    vector<string> parentTransaction;
};

vector<Transaction> transactions;

int main()
{

    ifstream mempoolCsv("mempool.csv");
    string blockData;

    getline(mempoolCsv, blockData);
    // to prevent csv headings from getting stored in our transactions vector

    while (getline(mempoolCsv, blockData))
    {
        Transaction tempTransaction;
        string substr;
        stringstream ss(blockData);

        for (size_t i = 0; i < 4; i++)
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
        transactions.push_back(tempTransaction);
    }
    mempoolCsv.close();
    return 0;
}