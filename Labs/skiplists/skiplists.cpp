#include "skiplists.hpp"

/////////////////// PRIVATE //////////////////////

// generate 2^i, as side effect store max level currently reached
template <typename Tkey, typename Tval>
num skiplist<Tkey, Tval>::rand_sl_gen__()
{
  num i, j, t = rand();                    // t is in [0, RAND_MAX]

  for (i=1, j=2; i < lgNmax_; i++, j+=j)   // generate j=2, 4, ... i < lgNmax_
    if (t > RAND_MAX/j) break;             // t > RAND_MAX / 2^i 
                                           // t is a number < 1/2^i
  if (i > lgN_)                            // expand current level
    lgN_ = i;                              // this grows logaritimcally 

  return i;
}

// search skip list give the entry link, the key and the current level
template <typename Tkey, typename Tval>
Tval skiplist<Tkey, Tval>::search__(link t, const Tkey key, num k) const
{
#ifdef DEBUG
  std::cerr << "search__ " << t << " key=" << key << " level=" << k << std::endl;
#endif

  if (t == 0)                          // search failed
    return default_val_; 
#ifdef DEBUG
  std::cerr << "key =" << key << " val = " << t->val_<< std::endl;
#endif
  if (key == t->key_)                 // search success
    return t->val_; 

  link x = t->next_[k];                // link to the next level
  if ((x == 0) ||                      //   null?
      (key < x->val_))                 //   search key < next level link's key
    {
      if (k==0)                        // no more levels available
	return default_val_;

      return search__(t, key, k-1);    // try previous level
    }
                                       // key > x->val_
  return search__(x, key, k);          //   keep searching on the same level
};

//
// insert
//
template <typename Tkey, typename Tval>
void skiplist<Tkey, Tval>::insert__(link t, link x, num k) 
{
#ifdef DEBUG
  std::cerr << "insert__ " << t << " " << x << " level=" << k 
  	    << " key=" << x->key_ << " value=" << x->val_ << std::endl;
#endif

  Tkey key = x->key_;      // current key
  link tk  = t->next_[k];  // link to next level current link
  
  if ((tk == 0) ||         //   null?
      ( key < tk->key_))   //   search key < next level link's key
    {
      if (k < x->size_)    // is curr lev allowed for this node?
	{                  //   insert:
	  x->next_[k] = tk;//    new node's successor is tk
	  t->next_[k] = x; //    t'successor is x
#ifdef DEBUG
	    std::cerr << "\tdone inserted key=" << key 
		      << " value=" << x->val_ <<std::endl;
#endif
	}
      if (k==0)             // level 0 
	return;             //   return

                            // k >= x->size__
      insert__(t, x, k-1);  //  insert down a level
      return;               //  return
    }
                            // k > tk->key_
  insert__(tk, x, k);       //   stay in the same level
};


template <typename Tkey, typename Tval>
void skiplist<Tkey, Tval>::remove__(link t, Tkey key, num k) 
{
#ifdef DEBUG
  std::cerr << "remove__ " << t << " key=" << key << " level=" 
	    << k <<std::endl;
#endif
  if (t==0) return;
  link x = t->next_[k];
  
  if ((x!=0) &&
      !(x->key_ < key))            // >=
    {
      if (key == x->key_){          // found it 
	t->next_[k] = x->next_[k]; //   remove
#ifdef DEBUG
	std::cerr  << " done" <<std::endl;
#endif
      }
      
      if (k==0)                    // can delete
	{                          //   no more links in level
	  delete x; 
	  return;
	}
      remove__(t, key, k-1);   // try to remove one level below
    }
  // x->key_ >= key

  remove__(t->next_[k], key, k);// try to remove in the same level
};


template <typename Tkey, typename Tval>
void skiplist<Tkey, Tval>::remove_all__(link t, num k) 
{
#ifdef DEBUG
  std::cerr << "remove__ " << t << " level=" 
	    << k <<std::endl;
#endif
  if (t==0) return;
  link x = t->next_[k];
  
  if (x!=0)
    {
      t->next_[k] = x->next_[k];   //   remove
      
      if (k==0)                    // can delete
	{                          //   no more links in level
	  delete x; 
	  return;
	}
      remove_all__(t, k-1);   // try to remove one level below
    }
  // x->key_ >= key

  remove_all__(t->next_[k], k);// try to remove in the same level
};



/////////////////// PUBLIC ///////////////////////






