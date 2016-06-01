vardef radius_p(expr th, r, R) = r * dir(th) -- R * dir(th) enddef;

vardef arc_p(expr r, s, t) = (dir(s) .. dir(.5 (s + t)) .. dir(t)) scaled r enddef;

vardef bow_p(expr r, s, t) = arc_p(r, s, t) -- cycle enddef;

vardef sector_p(expr r, R, s, t) = arc_p(r, s, t) -- arc_p(R, t, s) -- cycle enddef;

vardef equator_p(expr r, t) = arc_p(r, -t, t) -- arc_p(r, 180 - t, 180 + t) -- cycle enddef;

vardef subtropic_p(expr r, p, s, t) =
  (dir(p - 90 + s) ..
  dir(p - 90 + .5(s + t)) ..
  dir(p - 90 + t) --
  dir(p + 90 - t) ..
  dir(p + 90 - .5(s + t)) ..
  dir(p + 90 - s) -- cycle) scaled r
enddef;

def draw_filled_p(expr p, C) =
  fill p withcolor C;
  draw p;
enddef;
