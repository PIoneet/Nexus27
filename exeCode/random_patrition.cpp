#include <iostream>
#include <vector>
#include <random>
#include <algorithm>


using namespace std;
vector<int> random_partition(int parts);
vector<int> random_generate(int parts);
vector<int> random_total(int total, int parts);
vector<int> random_result(int total, int parts);

vector<int> cuts;

int main() {
    int num = 8;
    int total = 0;
    //cuts = random_partition(num);
    //cuts = random_generate(num);
    //cuts = random_total(200, num);
    cuts = random_result(500, num);
    for(int i = 0; i<num; i++){
        cout << cuts[i]<<endl;
        total = total + cuts[i];
    }

    cout << "Total: " << total << endl;
    cin.get();
    return 0;
}


vector<int> random_partition(int parts)  {
    vector<int> cuts;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(-49, 49);

    while(cuts.size() < parts -1){
        int cut = dis(gen);
        if(find(cuts.begin(), cuts.end(), cut) == cuts.end()){
            cuts.push_back(cut);
        }
    }
    int rand_num = dis(gen);
    sort(cuts.begin(), cuts.end());
    cuts.insert(cuts.begin(), rand_num);
    cuts.push_back(rand_num);

    for(int i = 0; i < cuts.size(); ++i){
        cout<< " "<< cuts[i];
    }
    cout << endl<<endl;

    vector<int> result;
    for(int i = 1; i < cuts.size(); ++i){
        result.push_back(cuts[i]- cuts[i-1]);
    }
    return result;
}

vector<int> random_generate(int parts) {
    vector<int> result;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(-49, 49);

    int sum = 0;
    for (int i = 0; i < parts - 1; ++i) {
        int val = dis(gen);
        result.push_back(val);
        sum += val;
    }
    result.push_back(-sum); // 마지막 원소를 총합이 0이 되도록 맞춤
    return result;
}

vector<int> random_total(int total, int parts) {
    vector<int> result;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(-total, total);

    int sum = 0;
    for (int i = 0; i < parts - 1; ++i) {
        int val = dis(gen);
        result.push_back(val);
        sum += val;
    }
    result.push_back(-sum); // 마지막 원소를 총합이 0이 되도록 맞춤
    return result;
}

vector<int> random_result(int total, int parts) {
    vector<int> result;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(-total, total);

    int sum = 0;
    for (int i = 0; i < parts - 1; ++i) {
        int val = dis(gen);
        result.push_back(val);
        sum += val;
    }
    int num = total - sum;
    result.push_back(num); // 마지막 원소를 총합이 0이 되도록 맞춤
    return result;
}