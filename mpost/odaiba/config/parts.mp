% part registry

def map_lr(text f) (suffix c) =
  f(c.l);
  f(c.r);
enddef;

def map_f(text f) =
  f(g.h);
  f(g.b);
  f(g.c);
  f(g.w);

  map_lr(f)(g.s);

  map_lr(f)(g.a.u);
  map_lr(f)(g.a.l);
  map_lr(f)(g.a.j);

  map_lr(f)(g.l.u);
  map_lr(f)(g.l.l);
  map_lr(f)(g.l.j);
enddef;

map_f(def_part);

% indexes
g.h.idx := 1;
g.w.idx := 7;
g.b.idx := 2;
g.s.l.idx := 3;
g.c.idx := 18;
g.a.u.l.idx := 4;
g.a.l.l.idx := 5;
g.l.u.l.idx := 8;
g.l.l.l.idx := 9;
g.a.j.l.idx := 19;
g.l.j.l.idx := 21;
