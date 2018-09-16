#ifndef BST_hpp
#define BST_hpp

#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
#define F first
#define S second

template<typename T,typename U>
class BST{
private:
  struct node{
    ll high;
    T key;
    U a;
    node *parent;
    node *right;
    node *left;
  };

  list<node> tree;
  node* root;
  node leaf={0,T(),U(),NULL,NULL,NULL};
  ll Size;

  node* search(T key){
    if(Size==0){return err();}
    node* where=root;
    while(1){
      if((*where).key==key){return where;}
      if((*where).right!=err() && (*where).key<key){where=(*where).right; continue;}
      if((*where).left!=err() && key<(*where).key){where=(*where).left; continue;}
      return where;
    }
    return err();
  }

  node* err(){return &leaf;}

  void High(node &where){
    node* right=where.right;
    node* left=where.left;
    where.high=max((*left).high,(*right).high)+1;
  }

  void High(node* where){
    node* right=(*where).right;
    node* left=(*where).left;
    (*where).high=max((*left).high,(*right).high)+1;
  }

  void parent_change(node &P,node* from,node* to){
    if(P.right==from){P.right=to; return;}
    else if(P.left==from){P.left=to; return;}
    assert(false);
  }

  void parent_change(node* P,node* from,node* to){parent_change(*P,from,to);}

  node* rotateL(node &where){
    node* right=where.right;
    assert(right!=err());
    node* L=(*right).left;
    if(L!=err()){
      where.right=L;
      (*L).parent=&where;
    }
    else{where.right=err();}
    (*right).left=&where;
    if(where.parent==err()){
      root=right;
      (*right).parent=err();
    }
    else{
      (*right).parent=where.parent;
      parent_change((*right).parent,&where,right);
    }
    where.parent=right;
    High(where);
    High(right);
    return right;
  }

  node* rotateR(node &where){
    node* left=where.left;
    assert(left!=err());
    node* R=(*left).right;
    if(R!=err()){
      where.left=R;
      (*R).parent=&where;
    }
    else{where.left=err();}
    (*left).right=&where;
    if(where.parent==err()){
      root=left;
      (*left).parent=err();
    }
    else{
      (*left).parent=where.parent;
      parent_change((*left).parent,&where,left);
    }
    where.parent=left;
    High(where);
    High(left);
    return left;
  }

  node* rotate(node &where){
    node* right=where.right;
    node* left=where.left;
    if(left!=err() && (*(*left).left).high>(*right).high){return rotateR(where);}
    if(right!=err() && (*(*right).right).high>(*left).high){return rotateL(where);}
    return &where;
  }

  node* rotate(node* where){return rotate(*where);}

  node* Max(node* where){
    assert(where!=err());
    while(1){
      if((*where).right==err()){return where;}
      where=(*where).right;
    }
    return err();
  }

  node* Min(node* where){
    assert(where!=err());
    while(1){
      if((*where).left==err()){return where;}
      where=(*where).left;
    }
    return err();
  }

  node* erase(node* where){
    if((*where).right!=err() && (*where).left!=err()){
      node* ers=Min((*where).right);
      (*where).key=(*ers).key;
      (*where).a=(*ers).a;
      erase(ers);
      return where;
    }
    node* ret;
    if((*where).right==err() && (*where).left==err()){
      parent_change((*where).parent,where,err());
      ret=(*where).parent;
    }
    else if((*where).right!=err()){
      parent_change((*where).parent,where,(*where).right);
      (*(*where).right).parent=(*where).parent;
      ret=(*where).parent;
    }
    else{
      parent_change((*where).parent,where,(*where).left);
      (*(*where).left).parent=(*where).parent;
      ret=(*where).parent;
    }
    where=ret;
    while(where!=err()){
      High(*where);
      where=rotate(where);
      where=(*where).parent;
    }
    return err();
  }

public:
  BST(){
    Size=0;
    root=err();
  }

  void insert(T key,U a){
    if(Size==0){
      tree.push_front({1,key,a,err(),err(),err()});
      Size++;
      root=&(*tree.begin());
      return;
    }
    node* where=search(key);
    if((*where).key==key){(*where).a=a;}
    else{
      tree.push_front({1,key,a,where,err(),err()});
      node* New=&(*tree.begin());
      if((*where).key<key){(*where).right=New;}
      else{(*where).left=New;}
      while(where!=err()){
	High(*where);
	where=rotate(where);
	where=(*where).parent;
      }
      Size++;
    }
  }

  U* find(T key){
    if(Size==0){return end();}
    node* where=search(key);
    if((*where).key==key){return &(*where).a;}
    return end();
  }

  U* end(){return &leaf.a;}

  ll size(){return Size;}

  ll high(){return (*root).high;}

  U* erase(T key){
    node* where=search(key);
    if((*where).key!=key){return end();}
    Size--;
    return &(*erase(where)).a;
  }

  void print(){
    if(Size==0){return;}
    dfs(root);
  }

  void dfs(node* where){
    assert(where!=err());
    cout<<(*where).key<<" "<<(*where).high<<endl;
    if((*where).right!=err()){dfs((*where).right);}
    if((*where).left!=err()){dfs((*where).left);}
  }

  void test(){
    mid_dfs(root);
    cout<<endl;
    first_dfs(root);
    cout<<endl;
  }

  void mid_dfs(node* where){
    assert(where!=err());
    if((*where).left!=err()){mid_dfs((*where).left);}
    cout<<" "<<(*where).a;
    if((*where).right!=err()){mid_dfs((*where).right);}
  }

  void first_dfs(node* where){
    assert(where!=err());
    cout<<" "<<(*where).a;
    if((*where).left!=err()){first_dfs((*where).left);}
    if((*where).right!=err()){first_dfs((*where).right);}
  }
};




#endif /*BST_hpp*/
