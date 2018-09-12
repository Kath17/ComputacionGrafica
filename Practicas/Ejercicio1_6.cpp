#include <GL/glut.h>
#include <math.h>
#include <iostream>

/*  EJERCICIO 1.6 */
// -1 a 1
// 0 a 100

using namespace std;

void user_to_ndc(float x, float y, float xmax, float xmin, float ymax, float ymin, float &ndcx, float &ndcy)
{
  float ndcx,ndcy;

  // De -1 a 1
  ndcx= 2* ((x - xmin)/(xmax-xmin)) -1 ;
  ndcy= 2* ((y - ymin)/(ymax-ymin)) -1 ;

  // De 0 a 100
  ndcx= 100 * ((x - xmin)/(xmax-xmin)) ;
  ndcy= 100 * ((y - ymin)/(ymax-ymin)) ;

  cout<<"NDCX: "<<ndcx<<endl;
  cout<<"NDCY: "<<ndcy<<endl;
}

void ndc_to_user(float ndcx, float ndcy, float xmax, float xmin, float ymax, float ymin, float &x, float &y)
{
  // float x,y;

  // De -1 a 1
  x = xmin + (xmax - xmin) * ((1 + ndcx) /2) ;
  y = ymin + (ymax - ymin) * ((1 + ndcy) /2) ;

  // De 0 a 100
  x = xmin + (xmax - xmin) * (ndcx /100) ;
  y = ymin + (ymax - ymin) * (ndcy /100) ;

  cout<<"X: "<<x<<endl;
  cout<<"Y: "<<y<<endl;
}

void inp_to_ndc(float dcx, float dcy, float ndh, float ndv , float &ndcx, float &ndcy)
{
  // float ndcx, ndcy;

  // De -1 a 1
  ndcx = 2 * (dcx / ndh) - 1;
  ndcy = 2 * (dcy / ndv) - 1;

  // De 0 a 100
  ndcx = 100 * (dcx / ndh);
  ndcy = 100 * (dcy / ndv);

  cout<<"NDCX: "<<ndcx<<endl;
  cout<<"NDCY: "<<ndcy<<endl;
}

void ndc_to_dc(float ndh, float ndv, float ndcx, float ndcy, float &dcx, float&dcy)
{
  // float dcx,dcy;

  // De -1 a 1
  dcx = ceil(ndh * ((1 + ndcx)/2));
  dcy = ceil(ndv * ((1 + ndcx)/2));

  // De 0 a 100
  dcx = ceil(ndh * (ndcx / 100));
  dcy = ceil(ndv * (ndcy / 100));

  cout<<"DCX: "<<dcx<<endl;
  cout<<"DCY: "<<dcy<<endl;
}

int main()
{
  float ndh = 1024;
  float ndv = 720;
  float xmin = -100;
  float ymin = -100;
  float xmax = 100;
  float ymax = 100;
  float dcx = 402;
  float dcy = 180;
  float ndcx;
  float ndcy;
  float x;
  float y;

	inp_to_ndc(dcx, dcy, ndh, ndv, ndcx, ndcy);
  ndc_to_user(ndcx,ndcy, xmax, xmin, ymax, ymin, x, y);
  user_to_ndc(x, y, xmax, xmin, ymax, ymin, ndcx, ndcy);
  ndc_to_dc(ndh, ndv, ndcx, ndcy, dcx, dcy);

	return 0;
}
