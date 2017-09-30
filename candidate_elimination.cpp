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
    //Number of attributes the hypothesis takes
    int num_of_attributes=16;
    //Values of the multivalued attribute
    int multivalued_attr[6]={0,2,4,5,6,8};
    //Vector with number of values for each attribute
    vector <int> number_of_values(num_of_attributes+1);
    //Vector of vectors to store the values that each attribute can take
    vector <vector<int> > values_of_attributes(num_of_attributes+1);
    //Loop to populate the values of all the attributes
    for(int i=0;i<num_of_attributes;i++){
        number_of_values[i]=2;
        if(i==12)
            //The 12th attribute has 6 values
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
    //Vector of set of vectors to store specific and generic boundaries of all seven classes
    vector<set<vector<int> > > specific_boundary(number_of_values[num_of_attributes]),general_boundary(number_of_values[num_of_attributes]);
    //Vectors to hold temporary hypothesis and the current training data
    vector<int> temp_vec(num_of_attributes),current_train(num_of_attributes+1);
    for(int i=0;i<num_of_attributes;i++)
        temp_vec[i]=-1;
    //Setting all the specific boundaries to all none attributes
    for(int i=0;i<number_of_values[num_of_attributes];i++)
        specific_boundary[i].insert(temp_vec);
    //Setting all the specific boundaries to all attributes
    for(int i=0;i<num_of_attributes;i++)
        temp_vec[i]=INT_MAX;
    for(int i=0;i<number_of_values[num_of_attributes];i++)
        general_boundary[i].insert(temp_vec);
    //Read the training data
    ifstream in("zoo.data.txt");
    string str;
    int test=1;
    while(getline(in,str)){
        int length=str.size(),first=0,offset=0,counter=0;
        string temp_str;
        //Splitting the training data line to populate the current_train vector
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
		//Looping to train each class to train all classes with the given training data
		while(numclass<7){
			vector<int> t1,t2,t3;
			set<vector<int> > temp_general,temp_specific;
			//If the training example is the same as unmclass+1 it is a positive training example
			if(current_train[num_of_attributes]==numclass+1){
                //Remove inconsistent hypotheses from general border
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
			//If it is a negative example
			else{
				set <vector<int> > temp_general,temp_specific;
				t2=*(specific_boundary[numclass].begin());
				for(set<vector<int> >::iterator itr=general_boundary[numclass].begin();itr!=general_boundary[numclass].end();itr++){
					t1=*itr;
					int flag=0;
					//Check if the given example is consistent with the present general hypothesis
					for(int i=0;i<num_of_attributes;i++){
						if(t1[i]!=INT_MAX&&t1[i]!=current_train[i]){
							flag=1; //Current general hypothesis is consistent
							break;
						}
					}
					if(flag)    //If hypothesis is consistent with the training instance
						temp_general.insert(t1);
					else{   //If hypothesis isn't consistent with the training instance
						vector<int> temp_hypothesis;
						for(int i=0;i<num_of_attributes;i++){
							if(t1[i]==INT_MAX){
								temp_hypothesis=t1;
								for(int j=0;j<number_of_values[i];j++){
									if(i==12){  //12th attribute has different values stored in the multivalued_attr array
										if(multivalued_attr[j]==current_train[i])
											continue;
										else{
											temp_hypothesis[i]=multivalued_attr[j];
											//Check if the new temporary hypothesis is more general than the specific hypothesis
											consistent=true;
											for(int k=0;k<num_of_attributes;k++){
												if(temp_hypothesis[k]!=INT_MAX && temp_hypothesis[k]!=t2[k] && t2[k]!=-1){
													consistent=false;
													break;
												}
											}
											if(consistent)
												temp_general.insert(temp_hypothesis);   //New hypothesis is consistent
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
				//Remove from the set of general hypotheses any hypothesis that is more specific than another hypothesis in the general boundary
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
				//Generic boundary is the set difference between the temp_general set of vectors and the temp_general_final set of vectors
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
    //Printing results into text file
    fstream fout;
    fout.open("final.txt",ios::out);
    for(int i=0;i<number_of_values[num_of_attributes];i++){
        if(general_boundary[i].begin()==general_boundary[i].end()){
            fout<<"Concept for class "<<i+1<<" cannot be learned"<<endl<<endl;
            continue;
        }
        else{
            fout<<"Specific boundary for class "<<i+1<<endl;
            for(set<vector<int> >::iterator itr=specific_boundary[i].begin();itr!=specific_boundary[i].end();itr++){
                temp = *itr;
                fout<<"<";
                for(int j=0;j<num_of_attributes;j++){
                    if(temp[j]==INT_MAX)
                        fout<<"?";
                    else
                        fout<<temp[j];
                    if(j!=num_of_attributes-1)
                    fout<<",";
                }
                fout<<">"<<endl;
            }
            fout<<"Generic boundary for class "<<i+1<<endl;
            for(set<vector<int> >::iterator itr=general_boundary[i].begin();itr!=general_boundary[i].end();itr++){
                temp = *itr;
                fout<<"<";
                for(int j=0;j<num_of_attributes;j++){
                    if(temp[j]==INT_MAX)
                        fout<<"?";
                    else
                        fout<<temp[j];
                    if(j!=num_of_attributes-1)
                    fout<<",";
                }
                fout<<">"<<endl;
            }
        }
        fout<<endl;
    }
    fout.close();
	cout<<"Trained results in final.txt";
    return 0;
}
