#include<bits/stdc++.h>
using namespace std;

int main(){

    int k,n;
    float freq;

    cout<<"Input no. of stages in pipelined proccesror = ";
    cin>>k;

    cout<<"Enter no. of instruction = ";
    cin>>n;

    cout<<"ENter clock frquency(Hz) = ";
    cin>>freq;

    float tau = 1/freq;

    int non_pipelined = n*k;
    int pipelined = k +(n-1);

    float speedup = float(non_pipelined)/pipelined;
    float efficiency = speedup/k;
    float totalTime = tau* pipelined;
    float throughput = n / totalTime;

    cout<<"Speedup = "<<speedup<<endl;
    cout<<"Efficiency = "<<efficiency*100<<endl;;
    cout<<"Throughput = "<<throughput<<endl;

    return 0;
}