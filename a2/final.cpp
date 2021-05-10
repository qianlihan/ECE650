class Point {
  int x;
  int y;
  bool inf;
  bool nac;

  Point(int _x, int _y) : x(_x), y(_y), inf(false), nac(false) {}
  Point(bool _inf, bool _pos) : inf(_inf), nac(!_inf), y(0) { x = _pos ? 1 : -1; }
public:
  bool isInf() const { return inf; }
  bool isNaC() const { return nac; }
  bool isPos() const { return x >= 1; }
  int getX() const { return x; }
  int getY() const { return y; }

  bool eq(const Point& other) const{
    //Assumption: NaC and Nac are not equal
    if(nac || other.isNaC()){
        return false;
    }
    
    //if both are inf and the sign(x) are identical
    if(inf || other.isInf()){
        return (inf && other.isInf() && x== other.getX());
    }

    return x == other.getX() && y == other.getY();
  }

  bool lt(const Point& other) const{
    //nac is the largest
    if(other.isNaC() && !nac)
        return true;
    else if(nac)
        return false;

    //other is +inf, and self is not +inf
    if(other.isInf() && other.getX() == 1 && !(inf && x ==1))
        return true;

    //if no special cases, just compare
    if(!other.isNaC() && !nac && !inf && other.isInf() )
        return other.getX() > x && other.getY() > y;

    //if self is -inf and other is not
    if((!other.isInf() || other.getX() != -1) && (inf && x ==1))
        return true;

    return false;
  }
  
  unsigned hash() const{
      return x+y;
  }
};


