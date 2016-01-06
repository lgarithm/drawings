vardef direction(expr th) = (cosd th, sind th) enddef;

def draw_radius(expr th, r, R) =
  pair d;
  d := direction(th);
  draw (r * d) -- (R * d);
enddef;

def draw_arc(expr r, s, t) =
  draw r * direction(s) .. r * direction(.5 (s + t)) .. r * direction(t);
enddef;

def draw_sector(expr r, R, s, t) =
  draw_radius(s, r, R);
  draw_radius(t, r, R);
  draw_arc(r, s, t);
  draw_arc(R, s, t);
enddef;

def fill_sector(expr r, R, s, t, C) =
  tm := .5 (s + t);
  pair ds, dt;
  ds := direction(s);
  dt := direction(t);
  pair a, b, c, d, m, M;
  a := r * ds;
  b := R * ds;
  M := R * direction(tm);
  c := R * dt;
  m := r * direction(tm);
  d := r * dt;
  fill a -- b .. M .. c -- d ..m .. cycle withcolor C;
enddef;

def draw_filled_sector(expr r, R, s, t) =
  fill_sector(r, R, s, t, .8white);
  draw_sector(r, R, s, t);
enddef;

def draw_main(expr n, t) =
  draw fullcircle scaled (2 * R);
  th0 := 360 / n;
  for i = 0 upto n:
    th := i * th0;
    draw_radius(th - t, rr, r);
    draw_radius(th + t, rr, r);
    draw_arc(rr, th - t, th + t);
    draw_arc(r, th + t, th + th0 - t);
    draw fullcircle scaled 2dd shifted ((rr + 2dd) * direction(th));
    draw fullcircle scaled 1.2dd shifted ((rr + 2dd) * direction(th));
  endfor;
enddef;

def draw_filled_main(expr n, t, rr, r, R) =
  color C;
  C := red + .5green;
  th0 := 360 / n;
  for i = 0 upto n:
    s := th0 * i;
    fill_sector(r, R, s, s + th0, C);
    fill_sector(rr, R, s - t, s + t, C);
  endfor;
  draw_main(n, t);
enddef;

% common
u := 1cm;

n := 4;
th0 := 360 / n;
R := 4u;
r := 3u;
rr := 1.8u;
dd := 0.2u;
t := 9;
