#ifndef ELEMENT_H
#define ELEMENT_H

class Element 
{
public:
   Element(int x, int y, int z);

   int GetX() const;
   int GetY() const;
   int GetZ() const;

   void SetX(int x);
   void SetY(int y);
   void SetZ(int z);

private:
   int X;
   int Y;
   int Z;
};
#endif
