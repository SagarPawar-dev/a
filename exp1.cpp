#include<bits/stdc++.h>
using namespace std;

void conversion(double n, int base){

    char digitmap[]= {'0', '1','2','3','4','5','6','7','8','9','A', 'B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R', 'S','T','U','V','W','X','Y','Z'};
    int rem[100];
    int intpart = int(n);
    double fractpart = n - int(n);
    int count = 0;

    if(intpart==0){
        cout<<0;
    }
    else{
        while(intpart>0){
            rem[count] = intpart%base;
            intpart = intpart/base;
            count++;
        }
        for(int i = count-1;i>=0;i--){
            cout<<digitmap[rem[i]];
        }
    }
    if(fractpart!=0){
        cout<<".";
        double a;
        for(int i=0;i<10;i++){
            a=fractpart*base;
            cout<<digitmap[int(a)];
            fractpart= a - int(a);
            if(fractpart==0){
                break;
            }
        }
    }

}

int main(){

    double n;
    int base;
    cout<<"Enter decimal no.: ";
    cin>>n;
    cout<<"Enter a base: ";
    cin>>base;
    conversion(n,base);
    return 0;

}