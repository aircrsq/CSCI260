#ifndef SKIP_HEAD_
#define SKIP_HEAD_
#include <stdlib.h>
#include <iostream>

namespace AG{
  
  typedef int num;// int, long, long long -- choose what you like

  template <typename Tkey, typename Tval>
  class skiplist{
    
  private:
    
    struct node
    {
      Tkey key_;           // the key
      Tval val_;           // the val
      num size_;           // size of array  
      node **next_;        // array of pointers

      node(const Tkey key, const Tval val, num size) :
	key_(key), val_(val), size_(size), next_(new node*[size_])
      { for ( num i = 0 ; i < size_; ++i) next_[i] = 0; 
	//std::cerr << "\t Created node key="<< key 
	//	  << " val=" << val << " num_links=" << size 
	//	  << std::endl;
      }
      
    };

    typedef node* const link;

    Tkey default_key_;     // default item in skiplist
    Tval default_val_;     // default val in skiplist
    link head_;            // head of skiplist
    
    num lgN_;              // current number of link in skiplist
    num lgNmax_;           // max number of link in skiplist
    
    // random skiplist expansion
    num rand_sl_gen__();     

    // remove a key and a val
    void remove__(link t, Tkey key, num k);

    // remove all keys
    void remove_all__(link t, num k);

    // search a key, given a link and the current level
    Tval search__(link t, const Tkey key, num k) const;

    // insert the new node pointed by link x with level k
    void insert__(link t, link x, num k);

  public: 
    
    skiplist(num lgNmax = 5) : 
      head_(new node(default_key_, default_val_, lgNmax+1)), 
      lgN_(0), lgNmax_(lgNmax) {}; 

    // TODO
    ~skiplist(){ remove_all__(head_, lgN_);};

    // search a key and get a val
    //   start from head_ and current level reached lgN_
    inline Tval search(const Tkey key) const 
    { return search__(head_, key, lgN_); };

    // insert a key and a val
    //   start from head_ and 
    //              and the new randomized node with 
    //              j=rand_sl_gen() links built with 
    //              probability 1/t^j
    //   current level is lgN_
    //
    inline void insert(const Tkey key, const Tval val) 
    { insert__(head_, new node(key, val, rand_sl_gen__()), lgN_); };

    
    inline void remove(Tkey key)
    { remove__(head_, key, lgN_-1); }

  };

  #include "skiplists.cpp"
};  

#endif
