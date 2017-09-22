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
    //cin>>num_of_attributes;
    num_of_attributes=16;
    vector <int> number_of_values(num_of_attributes+1);
    vector <vector<int> > values_of_attributes(num_of_attributes+1);
    for(int i=0;i<num_of_attributes;i++){
        //cin>>number_of_values[i];
        number_of_values[i]=2;
        if(i==12)
            number_of_values[i]=6;
        values_of_attributes[i].resize(number_of_values[i]);
        if(i==12){
            values_of_attributes[i][0]=0;
            values_of_attributes[i][0]=2;
            values_of_attributes[i][0]=4;
            values_of_attributes[i][0]=5;
            values_of_attributes[i][0]=6;
            values_of_attributes[i][0]=8;
        }
        else{
            for(int j=0;j<number_of_values[i];j++)
            //cin>>values_of_attributes[i][j];
            values_of_attributes[i][j]=j;
        }
    }
    //cin>>number_of_values[num_of_attributes];
    number_of_values[num_of_attributes] = 7;
    values_of_attributes[num_of_attributes].resize(number_of_values[num_of_attributes]);
    for(int i=1;i<=number_of_values[num_of_attributes];i++)
        //cin>>values_of_attributes[num_of_attributes][i];
        values_of_attributes[num_of_attributes][i]=i;
    set <vector<int> > specific_boundary[number_of_values[num_of_attributes]],general_boundary[number_of_values[num_of_attributes]];
    vector<int> temp_vec(num_of_attributes),current_train(num_of_attributes+1);
    for(int i=0;i<num_of_attributes;i++)
        temp_vec[i]=-1;
    for(int i=0;i<number_of_values[num_of_attributes];i++)
        specific_boundary[i].insert(temp_vec);
    for(int i=0;i<num_of_attributes;i++)
        temp_vec[i]=INT_MAX;
    for(int i=0;i<number_of_values[num_of_attributes];i++)
        general_boundary[i].insert(temp_vec);
    ifstream in("zoo.data.txt");
    string str;
    int test=1;
    while(getline(in,str)){
        /*if(test==3)
            break;
        test++;*/
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
        vector<int> t1,t2,t3;
        set<vector<int> > temp_general,temp_specific;
        switch(current_train[num_of_attributes]){
            case 1:
                temp_general=general_boundary[0];
                for(set<vector<int> >::iterator itr=general_boundary[0].begin();itr!=general_boundary[0].end();itr++){
                    t1=*itr;
                    int flag=0;
                    for(int i=0;i<num_of_attributes;i++){
                        if(t1[i]!=current_train[i] && t1[i]!=INT_MAX){
                            flag=1;
                            break;
                        }
                    }
                    if(flag)
                        temp_general.erase(t1);
                }
                general_boundary[0] = temp_general;
                t1 = *(specific_boundary[0].begin());
                t2 = *(specific_boundary[0].begin());
                specific_boundary[0].erase(t2);
                for(int i=0; i<num_of_attributes; i++){
                    if(t1[i]==-1){
                      t1[i] = current_train[i];
                    }
                    else if(t1[i]!=current_train[i]){
                      t1[i]=INT_MAX;
                    }
                  }
                specific_boundary[0].insert(t1);
                break;
            case 2:

                break;
            case 3:

                break;
            case 4:

                break;
            case 5:

                break;
            case 6:

                break;
            case 7:

                break;
        }
    }
    vector<int> temp;
    for(set<vector<int> >::iterator itr=specific_boundary[0].begin();itr!=specific_boundary[0].end();itr++){
        temp = *itr;
        for(int j=0;j<num_of_attributes;j++)
            cout<<temp[j]<<endl;
    }
    return 0;
}
