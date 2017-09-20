#include<iostream>
#include<vector>
#include<map>
using namespace std;

int main(){
    int num_of_attributes;
    //cout<<"Enter the number of attributes: ";
    cin>>num_of_attributes;
    vector <int> number_of_values(num_of_attributes+1);
    vector <vector<int> > values_of_attributes(num_of_attributes+1);
    for(int i=0;i<num_of_attributes;i++){
        cin>>number_of_values[i];
        values_of_attributes[i].resize(number_of_values[i]);
        for(int j=0;j<number_of_values[i];j++)
            cin>>values_of_attributes[i][j];
    }
    cin>>number_of_values[num_of_attributes];
    values_of_attributes[num_of_attributes].resize(number_of_values[num_of_attributes]);
    for(int i=0;i<number_of_values[num_of_attributes];i++)
        cin>>values_of_attributes[num_of_attributes][i];
    /*for(int i=0;i<=num_of_attributes;i++){
        for(int j=0;j<number_of_values[i];j++)
            cout<<values_of_attributes[i][j];
    }*/
    return 0;
}
