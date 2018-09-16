#ifndef Matrix_hpp
#define Matrix_hpp

#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
#define F first
#define S second

template<typename T,typename R=double> //要素の型、実数の型 //両方とも実数型を推奨
class Matrix{
private:
    typedef unsigned long ul;
    typedef long long int ll;
    typedef unsigned long long int ull;
    typedef Matrix<T,R> Mat;
    typedef Matrix<R,R> RMat;
    const R EPS=1e-12;
    ul n,m;
    vector<vector<T>> M;
    
    inline bool equals(const R &a,const R &b) const {
        return fabs(a-b)<EPS;
    }
    
    //A+=B
    template<typename U>
    vector<U> & pls (vector<U> &A,const vector<U> &B,U a) const {
        assert(A.size()==B.size());
        for(int i=0;i<A.size();i++){
            A[i]+=B[i]*a;
        }
        return A;
    }
    
    //A-=B
    template<typename U>
    vector<U> & mns (vector<U> &A,const vector<U> &B,const U &a) const {
        assert(A.size()==B.size());
        for(int i=0;i<A.size();i++){
            A[i]-=B[i]*a;
        }
        return A;
    }
    
    //A/=b
    template<typename U>
    vector<U> & normalization(vector<U> &A,const U &b) const {
        for(int i=0;i<A.size();i++){
            A[i]/=b;
        }
        return A;
    }
    
    Mat & Row_Permutation(const vector<ul> &P){
        assert(P.size()==n);
        Mat cp=*this;
        for(int i=0;i<n;i++){
            if(P[i]==i){continue;}
            M[i]=cp[P[i]];
        }
        return *this;
    }
    
    Mat & Col_Permutation(const vector<ul> &P){
        assert(P.size()==m);
        Mat cp=*this;
        for(int i=0;i<m;i++){
            if(P[i]==i){continue;}
            for(int t=0;t<n;t++){
                M[t][i]=cp[t][P[i]];
            }
        }
        return *this;
    }
    
    vector<ul> inverseP(const vector<ul> &P) const {
        vector<ul> ret(P.size());
        for(int i=0;i<P.size();i++){
            ret[P[i]]=i;
        }
        return ret;
    }
    
    RMat inverseL(RMat L) const {
        RMat ret; ret=ret.I(L.size());
        for(int i=0;i<L.size();i++){
            R d=L[i][i];
            if(equals(d,0)){return RMat(L.size(),L.size(),0);}
            if(equals(d,1)){continue;}
            ret[i][i]/=d;
            for(int t=0;t<=i;t++){
                L[i][t]/=d;
            }
        }
        for(int i=0;i<L.size();i++){
            for(int t=i+1;t<n;t++){
                if(equals(L.row(t)[i],0)){continue;}
                mns(ret[t],ret[i],L.row(t)[i]);
            }
        }
        return ret;
    }
    
    RMat inverseU(RMat U) const {
        RMat ret; ret=ret.I(U.size());
        for(int i=0;i<U.size();i++){
            R d=U[i][i];
            if(equals(d,0)){return RMat(U.size(),U.size(),0);}
            if(equals(d,1)){continue;}
            ret[i][i]/=d;
            for(int t=i;t<U.size();t++){
                U[i][t]/=d;
            }
        }
        for(ll i=U.size()-1;i>=0;i--){
            for(ll t=i-1;t>=0;t--){
                if(equals(U[t][i],0)){continue;}
                mns(ret[t],ret[i],U[t][i]);
            }
        }
        return ret;
    }
    
public:
    Matrix(const ul &n=0,const ul &m=0,const T &a=T()):n(n),m(m),M(vector<vector<T>>(n,vector<T>(m,a))){}
    
    Matrix(const vector<vector<T>> &M):n(M.size()),m(M[0].size()),M(M){
        for(int i=1;i<M.size();i++){assert(M[i].size()==m);}
    }
    
    /*
     template<typename K,typename L>
     Matrix(const Matrix<K,L> &A):n(A.size()),m(A.csize()),M(vector<vector<T>>(n,vector<T>(m,T()))){
     for(int i=0;i<n;i++){
     for(int t=0;t<m;t++){
     M[i][t]=T(A.row(i)[t]);
     }
     }
     }
     */
    
    vector<T> & operator [] (ul k){
        assert(k<n);
        return M[k];
    }
    
    template<typename K,typename L>
    Mat & operator = (const Matrix<K,L> &A){
        n=A.size(); m=A.csize();
        M.resize(n);
        for(int i=0;i<n;i++){
            M[i].resize(m);
            for(int t=0;t<m;t++){
                M[i][t]=T(A.row(i)[t]);
            }
        }
        return *this;
    }
    
    Mat & operator = (const Mat &A){
        n=A.n; m=A.m;
        M=A.M;
        return *this;
    }
    
    bool operator == (const Mat &A) const {
        return A.M==M;
    }
    
    bool operator != (const Mat &A) const {
        return A.M!=M;
    }
    
    bool operator < (const Mat &A) const {
        if(n<A.n){return true;}
        if(n>A.n){return false;}
        if(m<A.m){return true;}
        if(m>A.m){return false;}
        return M<A.M;
    }
    
    bool operator <= (const Mat &A) const {
        if(n<A.n){return true;}
        if(n>A.n){return false;}
        if(m<A.m){return true;}
        if(m>A.m){return false;}
        return M<=A.M;
    }
    
    bool operator > (const Mat &A) const {
        return A<(*this);
    }
    
    bool operator >= (const Mat &A) const {
        return A<=(*this);
    }
    
    Mat & operator += (const Mat &A){
        assert(n==A.n && m==A.m);
        for(int i=0;i<n;i++){
            for(int t=0;t<m;t++){
                M[i][t]+=A[i][t];
            }
        }
        return *this;
    }
    
    Mat operator + (const Mat &A) const {
        Mat ret=*this;
        return ret+=A;
    }
    
    Mat operator += (const T &a){
        for(int i=0;i<n;i++){
            for(int t=0;t<m;t++){
                M[i][t]+=a;
            }
        }
        return *this;
    }
    
    Mat operator + (const T &a) const {
        Mat ret=*this;
        return ret+=a;
    }
    
    Mat operator -= (const Mat &A){
        assert(n==A.n && m==A.m);
        for(int i=0;i<n;i++){
            for(int t=0;t<m;t++){
                M[i][t]-=A[i][t];
            }
        }
        return *this;
    }
    
    Mat operator - (const Mat &A) const {
        Mat ret=*this;
        return ret-=A;
    }
    
    Mat operator -= (const T &a){
        for(int i=0;i<n;i++){
            for(int t=0;t<m;t++){
                M[i][t]-=a;
            }
        }
        return *this;
    }
    
    Mat operator - (const T &a) const {
        Mat ret=*this;
        return ret-=a;
    }
    
    Mat & operator *= (const Mat &B){
        (*this)=(*this)*B;
        return *this;
    }
    
    Mat operator * (const Mat &B) const {
        assert(m==B.n);
        Mat ret(n,B.m);
        for(int i=0;i<n;i++){
            for(int t=0;t<B.m;t++){
                for(int h=0;h<m;h++){
                    ret[i][t]+=M[i][h]*B.row(h)[t];
                }
            }
        }
        return ret;
    }
    
    Mat operator *= (const T &a){
        for(int i=0;i<n;i++){
            for(int t=0;t<m;t++){
                M[i][t]*=a;
            }
        }
        return *this;
    }
    
    Mat operator * (const T &a) const {
        Mat ret=*this;
        return ret*=a;
    }
    
    Mat operator /= (const T &a){
        for(int i=0;i<n;i++){
            for(int t=0;t<m;t++){
                M[i][t]/=a;
            }
        }
        return *this;
    }
    
    Mat operator / (const T &a) const {
        Mat ret=*this;
        return ret/=a;
    }
    
    Mat operator %= (const T &a){
        for(int i=0;i<n;i++){
            for(int t=0;t<m;t++){
                M[i][t]%=a;
            }
        }
        return *this;
    }
    
    Mat operator % (const T &a) const {
        Mat ret=*this;
        return ret%=a;
    }
    
    ul size() const {return n;}
    
    ul csize() const {return m;}
    
    void resize(const ul &x,const ul &y){
        n=x; m=y;
        M.resize(n);
        for(int i=0;i<n;i++){
            M[i].resize(y);
        }
    }
    
    void clear(){
        n=0; m=0;
        M.clear();
    }
    
    const vector<T> & row(ul x) const {
        assert(x<n);
        return M[x];
    }
    
    R det() const {
        //*
        //LUPD
        return LUPD().F.F;
        //*/
        
        /*
         //Gaussian_Elimination
         assert(n==m);
         return Gaussian_Elimination(RMat(n,0)).S;
         //*/
    }
    
    RMat inverse() const {
        //*
        //LUPD
        pair<pair<R,vector<ul>>,pair<RMat,RMat>> ret=LUPD();
        ret.S.F=inverseL(ret.S.F);
        ret.S.S=inverseU(ret.S.S);
        ret.F.S=inverseP(ret.F.S);
        return (ret.S.S*ret.S.F).Col_Permutation(ret.F.S);
        //*/
        
        /*
         //Gaussian_Elimination
         assert(n==m);
         RMat y; y=y.I(n);
         return Gaussian_Elimination(y).F;
         //*/
    }
    
    Mat I(const ul &size) const {
        Mat ret(size,size,(T)0);
        for(int i=0;i<size;i++){
            ret[i][i]=(T)1;
        }
        return ret;
    }
    
    Mat mod_pow(ull x,const T &mod) const {
        assert(n==m);
        Mat ret=I(n);
        Mat A=*this;
        for(ul i=0;i<64;i++){
            if(x&1){ret*=A;}
            x>>=1;
            if(x==0){break;}
            A*=A;
            A%=mod;
        }
        return ret;
    }
    
    RMat equation(const RMat &Y) const {
        return inverse()*Y;
        //return Gaussian_Elimination(Y).F;
    }
    
    pair<RMat,RMat> LUD() const {
        assert(n==m);
        RMat A; A=(*this);
        RMat L; L=L.I(n);
        RMat U(n,n);
        for(int i=0;i<n;i++){
            for(int t=0;t<n;t++){
                for(int h=0;h<min(i,t);h++){
                    A[i][t]-=L[i][h]*U[h][t];
                }
                if(i>t){
                    if(equals(A[i][t],0)){L[i][t]=0;}
                    else{L[i][t]=A[i][t]/U[t][t];}
                }
                else{U[i][t]=A[i][t];}
            }
        }
        return {L,U};
    }
    
    //det,P,L,U
    pair<pair<R,vector<ul>>,pair<RMat,RMat>> LUPD() const {
        assert(n==m);
        RMat A; A=(*this);
        RMat L(n,n,(R)0);
        RMat U; U=U.I(n);
        vector<ul> P(n);
        R det=(R)1;
        for(int i=0;i<n;i++){P[i]=i;}
        for(int i=0;i<n;i++){
            for(int t=i;t<n;t++){
                for(int h=0;h<i;h++){
                    A[t][i]-=L[t][h]*U[h][i];
                }
            }
            R mx=fabs(A[i][i]);
            ll w=i;
            for(int t=i+1;t<n;t++){
                if(mx<fabs(A[t][i])){mx=fabs(A[t][i]); w=t;}
            }
            if(equals(mx,0)){return {{0,P},{RMat(n,n,(R)0),U.I(n)}};}
            if(i!=w){
                det*=(R)-1;
                swap(P[i],P[w]);
                swap(A[i],A[w]);
                swap(L[i],L[w]);
            }
            for(int t=i;t<n;t++){
                L[t][i]=A[t][i];
            }
            det*=L[i][i];
            for(int t=i+1;t<n;t++){
                for(int h=0;h<i;h++){
                    A[i][t]-=L[i][h]*U[h][t];
                }
                U[i][t]=A[i][t]/L[i][i];
            }
        }
        return {{det,P},{L,U}};
    }
    
    pair<RMat,R> Gaussian_Elimination(RMat y) const {
        RMat A=*this;
        R k=(R)1;
        for(int i=0;i<n;i++){
            R mx=fabs(A[i][i]);
            ll w=i;
            for(int t=i+1;t<n;t++){
                if(mx<fabs(A[t][i])){mx=fabs(A[t][i]); w=t;}
            }
            if(w!=i){
                swap(A[i],A[w]);
                swap(y[i],y[w]);
                k*=(R)-1;
            }
            R d=A[i][i];
            k*=d;
            if(!equals(d,0)){
                normalization(y[i],d);
                normalization(A[i],d);
                for(int t=0;t<n;t++){
                    if(i==t){continue;}
                    R e=A[t][i];
                    if(equals(e,0)){continue;}
                    mns(y[t],y[i],e);
                    mns(A[t],A[i],e);
                }
            }
            else{
                return {RMat(y.size(),y.csize(),R(0)),(R)0};
            }
        }
        return {y,k};
    }
    
    void show() const {
        for(int i=0;i<n;i++){
            for(int t=0;t<m;t++){
                if(equals(M[i][t],0)){cout<<0;}
                else{cout<<M[i][t];}
                if(t!=m-1){cout<<" ";}
            }
            cout<<endl;
        }
    }
};




#endif /*Matrix_hpp*/
