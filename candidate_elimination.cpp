#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<fstream>
#include<set>
#include<stdlib.h>
using namespace std;
int main(){
    bool consistent;
    int num_of_attributes;
    num_of_attributes=16;
    int multivalued_attr[6]={0,2,4,5,6,8};
    vector <int> number_of_values(num_of_attributes+1);
    vector <vector<int> > values_of_attributes(num_of_attributes+1);
    for(int i=0;i<num_of_attributes;i++){
        number_of_values[i]=2;
        if(i==12)
            number_of_values[i]=6;
        values_of_attributes[i].resize(number_of_values[i]);
        if(i==12){
            for(int j=0;j<6;j++)
                values_of_attributes[i][j]=multivalued_attr[j];
        }
        else{
            for(int j=0;j<number_of_values[i];j++)
            values_of_attributes[i][j]=j;
        }
    }
    number_of_values[num_of_attributes] = 7;
    values_of_attributes[num_of_attributes].resize(number_of_values[num_of_attributes]);
    for(int i=1;i<=number_of_values[num_of_attributes];i++)
        values_of_attributes[num_of_attributes][i]=i;
    vector<set<vector<int> > > specific_boundary(number_of_values[num_of_attributes]),general_boundary(number_of_values[num_of_attributes]);
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
		int numclass=0;
		while(numclass<7){
			vector<int> t1,t2,t3;
			set<vector<int> > temp_general,temp_specific;
			if(current_train[num_of_attributes]==numclass+1){
				temp_general=general_boundary[numclass];
				for(set<vector<int> >::iterator itr=general_boundary[numclass].begin();itr!=general_boundary[numclass].end();itr++){
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
				general_boundary[numclass] = temp_general;
				t1 = *(specific_boundary[numclass].begin());
				t2 = *(specific_boundary[numclass].begin());
				specific_boundary[numclass].erase(t2);
				for(int i=0; i<num_of_attributes; i++){
					if(t1[i]==-1){
					  t1[i] = current_train[i];
					}
					else if(t1[i]!=current_train[i]){
					  t1[i]=INT_MAX;
					}
				  }
				  specific_boundary[numclass].insert(t1);
			}
			else{
				set <vector<int> > temp_general,temp_specific;
				t2=*(specific_boundary[numclass].begin());
				for(set<vector<int> >::iterator itr=general_boundary[numclass].begin();itr!=general_boundary[numclass].end();itr++){
					t1=*itr;
					int flag=0;
					for(int i=0;i<num_of_attributes;i++){
						if(t1[i]!=INT_MAX&&t1[i]!=current_train[i]){
							flag=1;
							break;
						}
					}
					if(flag)
						temp_general.insert(t1);
					else{
						vector<int> temp_hypothesis;
						for(int i=0;i<num_of_attributes;i++){
							if(t1[i]==INT_MAX){
								temp_hypothesis=t1;
								for(int j=0;j<number_of_values[i];j++){
									if(i==12){
										if(multivalued_attr[j]==current_train[i])
											continue;
										else{
											temp_hypothesis[i]=multivalued_attr[j];
											consistent=true;
											for(int k=0;k<num_of_attributes;k++){
												if(temp_hypothesis[k]!=INT_MAX && temp_hypothesis[k]!=t2[k] && t2[k]!=-1){
													consistent=false;
													break;
												}
											}
											if(consistent)
												temp_general.insert(temp_hypothesis);
										}
									}
									else{
										if(j==current_train[i])
											continue;
										else{
											temp_hypothesis[i]=j;
											consistent=true;
											for(int k=0;k<num_of_attributes;k++){
												if(temp_hypothesis[k]!=INT_MAX && temp_hypothesis[k]!=t2[k] && t2[k]!=-1){
													consistent=false;
													break;
												}
											}
											if(consistent)
												temp_general.insert(temp_hypothesis);
										}
									}
								}
							}
						}
					}
				}
				general_boundary[numclass].clear();
				set <vector<int> > temp_general_final;
				for(set<vector<int> >::iterator itr = temp_general.begin();itr!=temp_general.end();itr++){
					t1=*itr;
					for(set<vector<int> >::iterator jtr=temp_general.begin();jtr!=temp_general.end();jtr++){
						if(itr==jtr)
							continue;
						t3=*jtr;
						consistent=true;
						for(int k=0;k<num_of_attributes;k++){
							if(t1[k]!=INT_MAX && t1[k]!=t3[k]){
								consistent=false;
								break;
							}
						}
						if(consistent)
							temp_general_final.insert(t3);
					}
				}
				for(set<vector<int> >::iterator itr=temp_general.begin();itr!=temp_general.end();itr++){
					t1=*itr;
					if(temp_general_final.find(t1)==temp_general_final.end())
						general_boundary[numclass].insert(t1);
				}
			}
		numclass++;
        }
    }
    vector<int> temp;
    fstream fout;
    fout.open("final.txt",ios::out);
    for(int i=0;i<number_of_values[num_of_attributes];i++){
        fout<<"Specific "<<i+1<<endl;
        for(set<vector<int> >::iterator itr=specific_boundary[i].begin();itr!=specific_boundary[i].end();itr++){
            temp = *itr;
            for(int j=0;j<num_of_attributes;j++){
                if(temp[j]==INT_MAX)
                    fout<<"?,";
                else
                    fout<<temp[j]<<",";
            }
            fout<<endl;
        }
        fout<<"Generic"<<endl;
        for(set<vector<int> >::iterator itr=general_boundary[i].begin();itr!=general_boundary[i].end();itr++){
            temp = *itr;
            for(int j=0;j<num_of_attributes;j++){
                if(temp[j]==INT_MAX)
                    fout<<"?,";
                else
                fout<<temp[j]<<",";
            }
            fout<<endl;
        }
    }
    fout.close();
	cout<<"Trained results in final.txt";
    return 0;
}
