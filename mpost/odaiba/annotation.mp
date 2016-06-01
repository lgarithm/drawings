% annotation

def def_arr(suffix c) (expr l, d) =
  numeric c.arr.len;
  numeric c.arr.ag;
  c.arr.len := l;
  c.arr.ag := d;
enddef;

def_arr(g.h, 3cm, 90 + 60);
def_arr(g.b, 6cm, 90 + 40);
def_arr(g.s.l, 4cm, 90 + 60);
def_arr(g.s.r, 4cm, 90 - 60);
def_arr(g.c, 3cm, 90 + 60);

def draw_arrow(suffix c) =
  if known(c.arr.len):
    drawarrow to(c.pos, c.arr.len, c.arr.ag);
  fi
enddef;

def draw_frame(expr t) =
  pen p;
  p := pencircle scaled 2bp;
  drawarrow (origin -- up) scaled 5mm transformed t withpen p;
  drawarrow (origin -- right) scaled 5mm transformed t withpen p;
enddef;

def draw_local_frame(suffix c) = draw_frame(abs_trans(c)); enddef;

def draw_position (suffix c) =
  draw c.pos withpen pencircle scaled 2mm withcolor red;
enddef;

def draw_offset(suffix c) =
  drawarrow origin transformed abs_trans(c) -- c.pos
    withcolor blue;
enddef;

vardef range_circle(suffix c) =
  fullcircle scaled c.size shifted -c.origin
enddef;

vardef range_rect(suffix c) =
  unitsquare shifted (-.5, -.5) xscaled c.w yscaled c.h shifted -c.origin
enddef;

def draw_range(suffix c) (text f) =
  draw f(c) transformed abs_trans(c) dashed evenly;
enddef;

def draw_range_circle(suffix c) =
  if known(c.size):
    draw_range(c, range_circle);
  fi
enddef;

def draw_range_rect(suffix c) =
  if known(c.w) and known(c.h):
    draw_range(c, range_rect);
  fi
enddef;
