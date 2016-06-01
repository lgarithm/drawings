% macros
vardef tand(expr d) = sind(d) / cosd(d) enddef;
vardef unit(expr v) = v scaled 1 / abs(v) enddef;
vardef to(expr p, l, d) = p shifted (l * dir(d)) -- p enddef;
vardef xmirror expr e = e reflectedabout (origin, right) enddef;
vardef ymirror expr e = e reflectedabout (origin, up) enddef;

def def_list(suffix ls) (text type) =
  numeric ls.n;
  ls.n := 0;
  type ls[];
enddef;

def add_to_list(suffix ls) (expr e) =
  ls[incr(ls.n)] := e;
enddef;

def append_to_list(suffix ls, ap) (text f) =
  for i := 1 upto ap.n:
    add_to_list(ls, f(ap[i]));
  endfor;
enddef;

def add_label_to(suffix c) (expr p, l) =
  add_to_list(c.cs, p);
  add_to_list(c.ls, l);
enddef;

def add_self_label_to(suffix c) (text p) =
  add_label_to(c, p, str p);
enddef;

def def_part(suffix c) =
  numeric c.idx;
  c.idx := 0;

  numeric c.ag;
  pair c.origin;
  pair c.pos;
  c.ag := 0;
  c.origin := origin;
  c.pos := origin;

  def_list(c.ps, path);
  def_list(c.qs, path);
  def_list(c.cs, pair);
  def_list(c.ls, string);

  numeric c.scale;
  c.scale := 2;
enddef;

vardef abs_trans(suffix c) =
  identity shifted c.origin rotated c.ag shifted c.pos
enddef;

def draw_path_list_with(suffix ps) (expr t) (text h)=
  for i := 1 upto ps.n:
    draw ps[i] transformed t h;
  endfor;
enddef;

def draw_all_labels(suffix c) (expr t) =
  for i := 1 upto c.cs.n:
    path p;
    p := fullcircle scaled 4mm shifted (c.cs[i] transformed t);
    fill p withcolor white;
    draw p;
    label(c.ls[i], c.cs[i] transformed t);
  endfor;
enddef;
