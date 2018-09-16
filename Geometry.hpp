#ifndef Geometry_hpp
#define Geometry_hpp

#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
#define F first
#define S second

template<typename T> //double or long long
class Geometry{
private:
  typedef pair<T,T> point;
  typedef point Vector;
  typedef pair<point,point> line;
  typedef vector<point> polygon;
  const double EPS=1e-9;

public:
  //from first,to second
  Vector line_Vector(line a){
    return {a.S.F-a.F.F,a.S.S-a.F.S};
  }

  T dot(line a,line b){
    return dot(line_Vector(a),line_Vector(b));
  }

  T dot(Vector a,Vector b){
    return a.F*b.F+a.S*b.S;
  }

  T cross(line a,line b){
    return cross(line_Vector(a),line_Vector(b));
  }

  T cross(Vector a,Vector b){
    return a.F*b.S-a.S*b.F;
  }

  T norm(line a){
    return dot(a,a);
  }

  T norm(Vector a){
    return dot(a,a);
  }

  T norm(point a,point b){
    return norm(line_Vector({a,b}));
  }

  double abs(line a){
    return sqrt(norm(a));
  }

  double abs(Vector a){
    return sqrt(norm(a));
  }

  double abs(point a,point b){return sqrt(norm(a,b));}

  //線分と点の距離
  double abs(line l,point p){
    if(dot(l,{l.F,p})<0){return abs(l.F,p);}
    if(dot(reverse(l),{l.S,p})<0){return abs(l.S,p);}
    return dist(l,p);
  }

  double abs(line a,line b){
    if(intersect(a,b)){return 0;}
    return min(min(abs(a,b.F),abs(a,b.S)),
	       min(abs(b,a.F),abs(b,a.S)));
  }

  point move(point p,Vector v){
    return {p.F+v.F,p.S+v.S};
  }

  Vector reverse(Vector v){return {-1*v.F,-1*v.S};}

  line reverse(line l){return {l.S,l.F};}

  Vector times(Vector v,T time){return {v.F*time,v.S*time};}

  Vector to_norm(Vector v,T norm){
    T dist=norm(v);
    return times(v,norm/dist);
  }

  //ダブル型でのみ使うこと
  Vector to_abs(Vector v,double abs){
    return to_norm(v,abs);
  }

  /*
     aが基点
     0::零ベクトルがある
     1::線分上にある
     2::直線上にある
     3::反対向き
     4::反時計回り
     5:: 時計回り
  */
  ll clockwise(Vector a,Vector b){
    T C=cross(a,b);
    T D=dot(a,b);
    if(C==0 && D==0){return 0;}
    if(C==0 && D>0){
      if(norm(a)>=norm(b)){return 1;}
      else{return 2;}
    }
    if(C==0 && D<0){return 3;}
    if(C>0){return 4;}
    return 5;
  }

  ll clockwise(line a,line b){return clockwise(line_Vector(a),line_Vector(b));}

  ll clockwise(line a,point b){return clockwise(a,{a.F,b});}

  polygon convex_hull(polygon a){
    assert(a.size()>=3);
    sort(a.begin(),a.end());
    polygon up;
    up.push_back(a[0]);
    up.push_back(a[1]);
    for(int i=2;i<a.size();i++){
      point p=a[i];
      while(up.size()>=2 && cross({up[up.size()-2],up[up.size()-1]},{up[up.size()-1],p})>=0){
	up.pop_back();
      }
      up.push_back(p);
    }
    reverse(a.begin(),a.end());
    polygon down;
    down.push_back(a[0]);
    down.push_back(a[1]);
    for(int i=2;i<a.size();i++){
      point p=a[i];
      while(down.size()>=2 && cross({down[down.size()-2],down[down.size()-1]},{down[down.size()-1],p})>=0){
	down.pop_back();
      }
      down.push_back(p);
    }
    polygon ret;
    for(int i=0;i<up.size();i++){
      ret.push_back(up[i]);
    }
    for(int i=1;i<down.size()-1;i++){
      ret.push_back(down[i]);
    }
    return ret;
  }

  template<typename U>
  U abs(U a){return a*sign(a);}

  template<typename U>
  U sign(U a){
    if(a==0){return 0;}
    if(a>0){return 1;}
    return -1;
  }

  bool is_convex(polygon a){
    if(a.size()<3){return false;}
    ll size=a.size();
    for(int i=0;i<size;i++){
      a.push_back(a[i]);
    }
    ll S=sign(cross({a[0],a[1]},{a[1],a[2]}));
    for(int i=3;i<a.size();i++){
      ll s=sign(cross({a[i-2],a[i-1]},{a[i-1],a[i]}));
      if(s==0){continue;}
      if(S==0){S=s;}
      if(S!=s){return false;}
    }
    return true;
  }

  T max_norm(){
    polygon P=convex_hull();
    T mx=0;
    ll where=0;
    for(int i=0;i<P.size();i++){
      if(norm({P[0],P[i]})>=mx){mx=norm({P[0],P[i]}); where=i;}
    }
    mx=0;
    for(int i=0;i<P.size();i++){
      while(norm({P[i],P[where]})<=norm({P[i],P[(where+1)%P.size()]})){
	where=(where+1)%P.size();
      }
      mx=max(mx,norm({P[i],P[where]}));
    }
    return mx;
  }

  double max_dist(){return sqrt(max_norm());}

  //ダブル型でのみ使うこと
  point shadow(line l,point p){
    Vector base=line_Vector(l);
    Vector P=line_Vector({l.F,p});
    double r=dot(P,base)/norm(base);
    return move(l.F,times(base,r));
  }

  //qが中心
  point reflection(point p,point q){
    Vector m=line_Vector({p,q});
    return move(q,m);
  }

  point reflection(line l,point p){
    point center=shadow(l,p);
    return reflection(p,center);
  }

  //直線と点の距離
  double dist(line l,point p){
    point q=shadow(l,p);
    return abs(p,q);
  }

  bool intersect(line a,line b){
    if(a.F==b.F || a.F==b.S || a.S==b.F || a.S==b.S){return true;}
    ll A=clockwise(a,b.F);
    ll B=clockwise(a,b.S);
    ll C=clockwise(b,a.F);
    ll D=clockwise(b,a.S);
    if(A==1 || B==1 || C==1 || D==1){return true;}
    if(A+B==9 && C+D==9){return true;}
    return false;
  }

  //a::Aからの距離 対 b::Bからの距離
  point interior_division(point A,point B,double a,double b){
    if(a==0){return A;}
    Vector vec=times(line_Vector({A,B}),a/(a+b));
    return move(A,vec);
  }

  //a::Aからの距離 対 b::Bからの距離
  point exterior_division(point A,point B,double a,double b){
    assert(a!=b);
    Vector vec=times(line_Vector({A,B}),a/(a-b));
    return move(A,vec);
  }

  //線分の交点
  point cross_point(line a,line b){
    assert(intersect(a,b));
    point A=shadow(a,b.F);
    point B=shadow(a,b.S);
    double d1=abs({A,b.F});
    double d2=abs({B,b.S});
    return interior_division(A,B,d1,d2);
  }

  point err(){return {-1e18,-1e18};}

  //直線の交点
  point X_point(line a,line b){
    point A=shadow(a,b.F);
    point B=shadow(a,b.S);
    double d1=abs({A,b.F});
    double d2=abs({B,b.S});
    if(d1==0 && d2==0){return interior_division(A,B,1,1);} //直線が等しい時の例外処理
    if(d1==0){return A;}
    if(d2==0){return B;}
    if(sign(d1)*-1==sign(d2)){return interior_division(A,B,d1,d2);}
    if(d1==d2){return err();} //直線が交わらない時の例外処理
    return exterior_division(A,B,d1,d2);
  }

  double polygon_area(polygon P){
    assert(P.size()>=3);
    point a=P[0];
    double ans=0;
    for(int i=2;i<P.size();i++){
      ans+=cross({a,P[i-1]},{P[i-1],P[i]});
    }
    ans/=2;
    return fabs(ans);
  }


  //0::false 1::is_in 2::on_line
  ll is_in_polygon(polygon P,point a){
    bool x=false;
    for(int i=1;i<=P.size();i++){
      Vector A=line_Vector({a,P[i-1]});
      Vector B=line_Vector({a,P[i%P.size()]});
      if(abs(cross(A,B))<EPS && dot(A,B)<EPS){return 2;}
      if(A.S>B.S){swap(A,B);}
      if(A.S<EPS && EPS<B.S && cross(A,B)>EPS){x=!x;}
    }
    return (x?1:0);
  }
};




#endif /*Geometry_hpp*/
