#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<fstream>
#include<set>
#include<stdlib.h>
using namespace std;

int main(){
    int num_of_attributes;
    //cout<<"Enter the number of attributes: ";
    /*cin>>num_of_attributes;
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
    set <vector<int> > specific_boundary,general_boundary;
    vector<int> temp_vec(num_of_attributes),current_train(num_of_attributes+1);
    for(int i=0;i<num_of_attributes;i++)
        temp_vec[i]=-1;
    specific_boundary.insert(temp_vec);
    for(int i=0;i<num_of_attributes;i++)
        temp_vec[i]=INT_MAX;
    general_boundary.insert(temp_vec);*/
    ifstream in("zoo.data.txt");
    string str;
    while(getline(in,str)){
        int length=str.size(),first=0,offset=0,counter=0;
        string temp_str;
        for(int i=0;i<length;i++){
            if(str[i]==','||i==length-1){
                if(!first){
                    first=1;
                    offset=i+1;
                    continue;
                }
                if(i==length-1)
                    temp_str = str.substr(offset,i-offset+1);
                else
                    temp_str = str.substr(offset,i-offset);
                int temp_int = atoi(temp_str.c_str());
                current_train[counter]=temp_int;
                counter++;
                offset=i+1;
            }
        }

    }
    /*for(int i=0;i<=num_of_attributes;i++){
        for(int j=0;j<number_of_values[i];j++)
            cout<<values_of_attributes[i][j];
    }*/
    return 0;
}
