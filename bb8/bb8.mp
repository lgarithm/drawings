vardef direction(expr th) = (cosd th, sind th) enddef;

vardef radius_p(expr th, r, R) = r * direction(th) -- R * direction(th) enddef;
vardef arc_p(expr r, s, t) = r * direction(s) .. r * direction(.5 (s + t)) .. r * direction(t) enddef;

def draw_radius(expr th, r, R) =
  pair d;
  d := direction(th);
  draw (r * d) -- (R * d);
enddef;

def draw_arc(expr r, s, t) =
  draw r * direction(s) .. r * direction(.5 (s + t)) .. r * direction(t);
enddef;

def draw_bow(expr r, s, t) =
  pair a, b, c;
  a := r * direction(s);
  b := r * direction(.5 (s + t));
  c := r * direction(t);
  draw a .. b .. c -- a;
enddef;

def draw_sector(expr r, R, s, t) =
  draw_radius(s, r, R);
  draw_radius(t, r, R);
  draw_arc(r, s, t);
  draw_arc(R, s, t);
enddef;

def draw_equator(expr r, t) =
  pair a, b, c, d;
  a := r * direction(-t);
  b := r * direction(t);
  c := r * direction(180 - t);
  d := r * direction(180 + t);
  draw a .. r * direction(0) ..  b -- c .. r * direction(180) .. d -- cycle;
enddef;

def fill_bow(expr r, s, t, C) =
  pair a, b, c;
  a := r * direction(s);
  b := r * direction(.5 (s + t));
  c := r * direction(t);
  fill a .. b .. c -- cycle withcolor C;
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

def fill_equator(expr r, t, C) =
  pair a, b, c, d;
  a := r * direction(-t);
  b := r * direction(t);
  c := r * direction(180 - t);
  d := r * direction(180 + t);
  fill a .. r * direction(0) ..  b -- c .. r * direction(180) .. d -- cycle withcolor C;
enddef;

def draw_filled_bow(expr r, s, t) =
  fill_bow(r, s, t, .8white);
  draw_bow(r, s, t);
enddef;

def draw_filled_sector(expr r, R, s, t) =
  fill_sector(r, R, s, t, .8white);
  draw_sector(r, R, s, t);
enddef;

def draw_filled_equator(expr r, t) =
  fill_equator(r, t, .8white);
  draw_equator(r, t);
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

path bsp;
bsp :=
  arc_p(rr - dd, t + tt, th0 + t + tt) --
  radius_p(th0 + t + tt, rr - dd, r - 2dd) --
  arc_p(r - 2dd, th0 + t + tt, 1.5 th0 - tt)
  -- (r - 2dd) * direction(1.5 th0 - tt)
  -- (r - 2dd) * direction(1.5 th0 - tt)
  .. (r - 4dd) * direction(1.5 th0)
  .. (r - 2dd) * direction(1.5 th0 + tt)
  -- (r - 2dd) * direction(1.5 th0 + tt)
  -- arc_p(r - 2dd, 1.5th0 + tt, 2th0 - t - tt) --
  radius_p(2th0 - t - tt, r - 2dd, rr - dd)
  -- cycle;

path ss_p;
ss_p := radius_p(th0, 0, rr - dd)
  -- arc_p(rr - dd, th0, 2th0 + t + 5)
  -- radius_p(2th0 + t + 5, rr - dd, r - dd)
  -- arc_p(r - dd, 2th0 + t + 5, 2th0 + t + 20)
  -- radius_p(2th0 + t + 20, r - dd, r - 2dd)
  -- arc_p(r - 2dd, 2th0 + t + 20, 2th0 + t + 40)
  -- radius_p(2th0 + t + 40, r - dd, r - 2dd)
  -- arc_p(r - dd, 2th0 + t + 40, 3th0 - t - 5)
  -- radius_p(3th0 - t - 5, r - dd, rr - dd)
  -- arc_p(rr - dd, 3th0 - t - 5, 3th0 + t - 5)
  -- radius_p(3th0 + t - 5, rr - dd, 0)
  -- cycle;
