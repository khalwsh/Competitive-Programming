#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
using namespace __gnu_pbds;
template<class T> using ordered_set = tree<T, null_type , less_equal<T> , rb_tree_tag , tree_order_statistics_node_update> ;

struct ordered__set{

	ordered_set< int > se ;
	void erase( int val ){  
		if( se.size() == 0 || *se.find_by_order( se.size() - 1 ) < val || *se.lower_bound( val - 1 ) != val  ) return ;
		se.erase( se.lower_bound( --val ) ) ; 
	}
	int lw_bound( int val ){ // log --> return index ;
		if( se.size() == 0 || *se.find_by_order( se.size() - 1 ) < val  ) return -1;
		return se.order_of_key( *se.lower_bound( --val ) ) ;
	}
	int up_bound( int val ){ return  lw_bound( val + 1ll ) ; }
	void insert( int val ){ se.insert( val ); }
        int operator[](int idx) { return *se.find_by_order( idx ) ;}
	int size( ){ return se.size(); }
	void clr(  ){ se.clear() ; } 
}