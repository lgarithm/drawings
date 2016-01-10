vardef direction(expr th) = (cosd th, sind th) enddef;

vardef radius_p(expr th, r, R) = r * direction(th) -- R * direction(th) enddef;
vardef arc_p(expr r, s, t) = r * direction(s) .. r * direction(.5 (s + t)) .. r * direction(t) enddef;

vardef subtropic_p(expr r, p, s, t) =
  r * direction(p - 90 + s) ..
  r * direction(p - 90 + .5(s + t)) ..
  r * direction(p - 90 + t) --
  r * direction(p + 90 - t) ..
  r * direction(p + 90 - .5(s + t)) ..
  r * direction(p + 90 - s)
enddef;

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
  fill a -- b .. M .. c -- d .. m .. cycle withcolor C;
enddef;

def fill_equator(expr r, t, C) =
  pair a, b, c, d;
  a := r * direction(-t);
  b := r * direction(t);
  c := r * direction(180 - t);
  d := r * direction(180 + t);
  fill a .. r * direction(0) ..  b -- c .. r * direction(180) .. d -- cycle withcolor C;
enddef;

def fill_subtropic(expr r, p, s, t, C) =
  fill subtropic_p(r, p, s, t) -- cycle withcolor C;
enddef;

def draw_filled_bow(expr r, s, t) =
  fill_bow(r, s, t, C_minor);
  draw_bow(r, s, t);
enddef;

def draw_filled_sector(expr r, R, s, t) =
  fill_sector(r, R, s, t, C_minor);
  draw_sector(r, R, s, t);
enddef;

def draw_filled_equator(expr r, t) =
  fill_equator(r, t, C_minor);
  draw_equator(r, t);
enddef;
