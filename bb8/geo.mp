vardef radius_p(expr th, r, R) = r * dir(th) -- R * dir(th) enddef;
vardef arc_p(expr r, s, t) = r * dir(s) .. r * dir(.5 (s + t)) .. r * dir(t) enddef;

vardef subtropic_p(expr r, p, s, t) =
  r * dir(p - 90 + s) ..
  r * dir(p - 90 + .5(s + t)) ..
  r * dir(p - 90 + t) --
  r * dir(p + 90 - t) ..
  r * dir(p + 90 - .5(s + t)) ..
  r * dir(p + 90 - s)
enddef;

def draw_radius(expr th, r, R) =
  pair d;
  d := dir(th);
  draw (r * d) -- (R * d);
enddef;

def draw_arc(expr r, s, t) =
  draw r * dir(s) .. r * dir(.5 (s + t)) .. r * dir(t);
enddef;

def draw_bow(expr r, s, t) =
  pair a, b, c;
  a := r * dir(s);
  b := r * dir(.5 (s + t));
  c := r * dir(t);
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
  a := r * dir(-t);
  b := r * dir(t);
  c := r * dir(180 - t);
  d := r * dir(180 + t);
  draw a .. r * dir(0) ..  b -- c .. r * dir(180) .. d -- cycle;
enddef;

def fill_bow(expr r, s, t, C) =
  pair a, b, c;
  a := r * dir(s);
  b := r * dir(.5 (s + t));
  c := r * dir(t);
  fill a .. b .. c -- cycle withcolor C;
enddef;

def fill_sector(expr r, R, s, t, C) =
  tm := .5 (s + t);
  pair ds, dt;
  ds := dir(s);
  dt := dir(t);
  pair a, b, c, d, m, M;
  a := r * ds;
  b := R * ds;
  M := R * dir(tm);
  c := R * dt;
  m := r * dir(tm);
  d := r * dt;
  fill a -- b .. M .. c -- d .. m .. cycle withcolor C;
enddef;

def fill_equator(expr r, t, C) =
  pair a, b, c, d;
  a := r * dir(-t);
  b := r * dir(t);
  c := r * dir(180 - t);
  d := r * dir(180 + t);
  fill a .. r * dir(0) ..  b -- c .. r * dir(180) .. d -- cycle withcolor C;
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
