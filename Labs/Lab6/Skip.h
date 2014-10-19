#ifndef __SKIP_H__
#define __SKIP_H__
/************************************************************************
 Design Unit  : Lab6

 File Name    : Skip.h

 Purpose      : Header file for bst

 Note         :

 Limitations  : none known

 Errors       : none known

 Modules      :

 Dependences  : none

 Author       : David Burneau, Vancouver Island University

 System       : G++ (Linux)

------------------------------------------------------------------
 Revision List
 Version      Author  Date    Changes
 1.0          DB      Oct 06  New version Original code provide by
                              Professor Gara Pruesse
*************************************************************************/
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#define MAX_LEVEL 6
const float P = 0.5;
using namespace std;

class SkipList{
  private:
//Skip Node Declaration
struct snode {
  int value;
/*  snode **forw;
  snode(int level, int &value){
    forw = new snode * [level + 1];
    memset(forw, 0, sizeof(snode*) * (level + 1));
    this->value = value;
  }
  ~snode(){
    delete [] forw;
  } */
};
//Skip List Declaration
struct skiplist{
  snode *header;
  int value;
  int level;
/*  skiplist(){
    header = new snode(MAX_LEVEL, value);
    level = 0;
  }
  ~skiplist(){
    delete header;
  } */
};

  // private, recursive routines (used by the public methods)
  // see RBbst.cpp file for explanation
  void insert_element(int &value);
  void delete_element(int &value);
  void display();
  bool contains(int &s_value);

  public:
  //Constructors
  snode(int level, int &value){
    forw = new snode * [level + 1];
    memset(forw, 0, sizeof(snode*) * (level + 1));
    this->value = value;
  }
  ~snode(){
    delete [] forw;
  }
  skiplist(int value){
    header = new snode(MAX_LEVEL, value);
    level = 0;
  }
  ~skiplist(){
    delete header;
  }
  SkipList() {
    Sentinel = new node;
    Sentinel->parent = Sentinel;
    Sentinel->left = Sentinel;
    Sentinel->right = Sentinel;
    Sentinel->key = -99999999;
    Sentinel->data = "Sentinel";
    Sentinel->colour = BLACK;
    root = Sentinel;
  }
  ~SkipList() { deallocate(root); }

  skiplist ss;
  int choice, n;
  /*
  while (1){
    cout<<endl<<"-----------------------"<<endl;
    cout<<endl<<"Operations on Skip list"<<endl;
    cout<<endl<<"-----------------------"<<endl;
    cout<<"1.Insert Element"<<endl;
    cout<<"2.Delete Element"<<endl;
    cout<<"3.Search Element"<<endl;
    cout<<"4.Display List "<<endl;
    cout<<"5.Exit "<<endl;
    cout<<"Enter your choice : ";
    cin>>choice;
    switch(choice){
      case 1:
        cout<<"Enter the element to be inserted: ";
        cin>>n;
        ss.insert_element(n);
        if(ss.contains(n)){
          cout<<"Element Inserted"<<endl;
        }
        break;
      case 2:
        cout<<"Enter the element to be deleted: ";
        cin>>n;
        if(!ss.contains(n)){
          cout<<"Element not found"<<endl;
          break;
        }
        ss.delete_element(n);
        if(!ss.contains(n)){
          cout<<"Element Deleted"<<endl;
        }
        break;
      case 3:
        cout<<"Enter the element to be searched: ";
        cin>>n;
        if(ss.contains(n)){
          cout<<"Element "<<n<<" is in the list"<<endl;
        }
        else{
          cout<<"Element not found"<<endl;
        }
      case 4:
        cout<<"The List is: ";
        ss.display();
        break;
      case 5:
        exit(1);
        break;
      default:
        cout<<"Wrong Choice"<<endl;
    }
  }
  return 0; */
};
#endif
