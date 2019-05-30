// eps.h --- eps library API
void eps_open(char *fname, int w, int h);
void eps_close(void);
void eps_cmd(char *cmd);
void eps_num(double val);
void eps_drawline(double x0, double y0, double x1, double y1);
void eps_drawrect(double x, double y, double w, double h);
void eps_fillrect(double x, double y, double w, double h);
void eps_drawcircle(double x, double y, double r);
void eps_fillcircle(double x, double y, double r);
int eps_newfont(char *font, double size);
void eps_puts(int id, double x, double y, char *s);
