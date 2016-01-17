def draw_head(expr hp) =
  fill subtropic_p(hr, 90, -ts, 0) -- cycle shifted hp withcolor C_minor;

  draw (arc_p(hr, -t, 45)
    .. arc_p(hr, 45, 45 * 3)
    .. arc_p(hr, 45 * 3, 180 + t)) shifted hp;

  draw (hr * dir(-t) -- RR * dir(90 - rth) shifted (0, -Hr)) shifted hp;
  draw (hr * dir(180 + t) -- RR * dir(90 + rth) shifted (0, -Hr)) shifted hp;
  draw arc_p(RR, 90 - rth, 90 + rth) shifted (0, -Hr) shifted hp;
  %draw arc_p(RR + .05u, 90 - rth, 90 + rth) shifted (0, -Hr) shifted hp;

  draw ((-hr, 0) -- (hr, 0)) shifted hp;
  draw (hr * dir(-t) -- hr * dir(180 + t)) shifted hp;

  fill subtropic_p(hr, 90, 60, 75) shifted hp -- cycle withcolor C_minor;
  fill subtropic_p(hr, 90, 45, 50) shifted hp -- cycle withcolor C_main;

  pair Ep;
  Ep := (0, hr * .6);
  fill fullcircle scaled 8dd shifted (hp + Ep) withcolor white;
  draw fullcircle scaled 6dd shifted (hp + Ep);
  fill fullcircle scaled 2dd shifted (hp + Ep + (-dd, -dd)) withcolor .5red;
  fill (fullcircle scaled 6dd -- reverse(fullcircle) scaled 7dd -- cycle) shifted (hp + Ep);

  pair ep;
  ep := (hr * .5, hr * .3);
  fill fullcircle scaled 3dd shifted (hp + ep);
  fill (fullcircle scaled 4dd -- reverse(fullcircle) scaled 5dd -- cycle) shifted (hp + ep);

  pair tp, Tp;
  Tp := hr * dir(90 - 10);
  tp := hr * dir(90 + 5);
  draw (Tp -- (Tp + (0, .6hr))) shifted hp;
  draw (tp -- (tp + (0, .3hr))) shifted hp;
enddef;
