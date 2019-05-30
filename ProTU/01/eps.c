// eps.c --- eps library implementation
#include <stdio.h>
#include "eps.h"
static FILE *fd = NULL;
static int fontid = 0;

void eps_open(char *fname, int w, int h){
  fd = fopen(fname, "wb");
  fprintf(fd, "%%!PS-Adobe-2.0\n%%%%BoundingBox: 0 0 %d %d\n", w, h);
}
void eps_close(void) {
  fprintf(fd, "showpage\n"); fclose(fd); fd = NULL;
}
void eps_cmd(char *cmd) {
  fprintf(fd, "%s\n", cmd);
}
void eps_num(double val) {
  fprintf(fd, "%.2f ", val);
}
void eps_drawline(double x0, double y0, double x1, double y1) {
  fprintf(fd, "newpath %.2f %.2f moveto %.2f %.2f lineto stroke\n",
          x0, y0, x1, y1);
}
static void rect(double x, double y, double w, double h) {
  fprintf(fd, "newpath %.2f %.2f moveto %.2f 0 rlineto\n", x, y, w);
  fprintf(fd, " 0 %.2f rlineto %.2f 0 rlineto closepath\n", h, -w, -h);
}
void eps_drawrect(double x, double y, double w, double h) {
  rect(x, y, w, h); fprintf(fd, "stroke\n");
}
void eps_fillrect(double x, double y, double w, double h) {
  rect(x, y, w, h); fprintf(fd, "fill\n");
}
static void circle(double x, double y, double r) {
  fprintf(fd, "%.2f %.2f %.2f 0 360 arc closepath\n", x, y, r);
}
void eps_drawcircle(double x, double y, double r) {
  circle(x, y, r); fprintf(fd, "stroke\n");
}
void eps_fillcircle(double x, double y, double r) {
  circle(x, y, r); fprintf(fd, "fill\n");
}
int eps_newfont(char *font, double size) {
  fprintf(fd, "/%s findfont %.2f scalefont /font%d exch def\n",
          font, size, ++fontid);
  return fontid;
}
void eps_puts(int id, double x, double y, char *s) {
  fprintf(fd, "font%d setfont %.2f %.2f moveto (%s) show\n",
          id, x, y, s);
}
