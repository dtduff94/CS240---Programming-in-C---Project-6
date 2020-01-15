/* Pseudocode: So I tried to used a stack at first but apparently the <stack.h> header isn't a default header that you can import into the file so I was thinking about making a struct for one but wasn't sure if that was what you were supposed to do given we are only supposed to submit three files and there might be an easier implementation than using an actual stack like described in the project pdf.  I still kept the code though as if I were able to make a stack.  For pseudocode however, I made three methods, the distanceSqauredTo,crossProduct, and compare methods for determining distance/polar angles between them and then comparing them amongst each other to determine if a point should be kept in or out of the convex hull.  I then determined the point with the largest y value and set that as my initial point.  I then went through the points and if two subsequent points had the same polar angle then I only kep the one with the furthest distance from the original point as well as adding the ones that should be kept to a separate array which I had trouble with.  I then printed the points and I get a funky output, unsure if the first few ones that are there are correct but I do get some sort of output followed by some points that are clearly not on the convex hull.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <stack.h>
#include "point.h"

/* implement Graham's scan
 * at the end of this function, before returning to main()
 * you should print the vertices of the convex hull counterclockwise
 * starting from the vertex with the largest y-coordinate
 */

/*
  point second(stack<point> &points) {
  point first = points.top();
  points.pop();
  point second = points.top();
  points.push(first);
  return second;
}
*/

int distanceSquaredTo(point a, point b) {
  return pow((pow((a.x - b.x), 2) + pow((a.y - b.y), 2)), 0.5);
}

int crossProduct(point a, point b, point c) {
  int polarvalue = ((b.x - a.x)*(c.y - a.y)) - ((c.x - a.x)*(b.y - a.y));

  if (polarvalue == 0) {
    return 0;
  }
  else if (polarvalue > 0) {
    return 1;
  }
  else {
    return -1;
  }
}

point p0;
int compare(const void *a, const void *b) {
  point *p1 = (point *)a;
  point *p2 = (point *)b;

  int polarangle = crossProduct(p0, *p1, *p2);

  if (polarangle == 0 && distanceSquaredTo(p0, *p2) >= distanceSquaredTo(p0, *p1)) {
    return -1;
  }
  else if (polarangle == 0 && distanceSquaredTo(p0, *p2) < distanceSquaredTo(p0, *p1)) {
    return 1;
  }
  else if (polarangle == -1) {
    return -1;
  }
  else {
    return 1;
  }
}

void graham(point dataSet[], unsigned n)
{ 
  double ymax = dataSet[0].y;
  int max = 0;
  for (int i = 1; i < n; i++) {
    int y = dataSet[i].y;
    if (y > ymax || (ymax == y && dataSet[i].x > dataSet[max].x)) {
      ymax = dataSet[i].y;
      max = i;
    }
  }
  
  point temp = dataSet[0];
  dataSet[0] = dataSet[max];
  dataSet[max] = temp;

  point p0 = dataSet[0];
  qsort(&dataSet[1], n - 1, sizeof(point), compare);
  
  int j = 1;
  for (int i = 1; i < n; i++) {
    while(i < n - 1 && crossProduct(p0, dataSet[i], dataSet[i + 1]) == 0) {
      i++;
    }
    dataSet[j] = dataSet[i];
    j++;
  }

  if (j < 3) {
    return;
  }
  
  point points[32];
  points[0] = dataSet[0];
  points[1] = dataSet[1];
  points[2] = dataSet[2];
  //stack<point> points;
  //stack.push(dataSet[0]);
  //stack.push(dataSet[1]);
  //stack.push(dataSet[2]);
  for (int i = 3; i < j; i++) {
    if (crossProduct(points[i - 2], points[i - 1], dataSet[i]) != -1) {
    //while (crossProduct(second(points), points.top(), dataSet[i]) != -1) {
      points[i - 1] = dataSet[i];
      //points.pop();
    }
    else {
      points[i] = dataSet[i];
    }
    //points[i] = dataSet[i];
    //points.push(dataSet[i]);
  }
  
  for (int i = 0; i < 32; i++) {
    if (points[i].x != 0.000000 || points[i].y != 0.000000) {
      printf("(%f, %f)", points[i].x, points[i].y);
    }
  }
  /*while (!points.empty()) {
    point p = points.top();
    printf("(%s, %s)", p.x, p.y);
    points.pop();
  }
  */
  /* print the number of vertices on the hull
   * then print the vertices
   */
}
