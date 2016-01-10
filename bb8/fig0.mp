beginfig(0);
  pair hp;
  hp := (0, Hr);

  fill subtropic_p(hr, 90, -ts, 0) -- cycle shifted (0, Hr) withcolor C_minor;

  draw (arc_p(hr, -t, 45) 
    .. arc_p(hr, 45, 45 * 3) 
    .. arc_p(hr, 45 * 3, 180 + t)) shifted hp;
  draw hr * direction(-t) shifted hp -- RR * direction(90 - rth);
  draw hr * direction(180 + t) shifted hp -- RR * direction(90 + rth);

  draw (-hr, Hr) -- (hr, Hr);
  draw (hr * direction(-t) -- hr * direction(180 + t)) shifted hp;

  pair Ep;
  Ep := (0, hr * .6);
  draw fullcircle scaled 6dd shifted (hp + Ep);
  fill fullcircle scaled 2dd shifted (hp + Ep + (-dd, -dd)) withcolor .5red;
  fill (fullcircle scaled 6dd -- reverse(fullcircle) scaled 7dd -- cycle) shifted (hp + Ep);

  pair ep;
  ep := (hr * .5, hr * .3);
  fill fullcircle scaled 3dd shifted (hp + ep);
  fill (fullcircle scaled 4dd -- reverse(fullcircle) scaled 5dd -- cycle) shifted (hp + ep);

  pair tp, Tp;
  Tp := hr * direction(90 - 10);
  tp := hr * direction(90 + 5);
  draw (Tp -- (Tp + (0, .6hr))) shifted hp;
  draw (tp -- (tp + (0, .3hr))) shifted hp;
  
  draw_filled_main(n, t, rr, r, R);
  draw_filled_face_iii;
  draw_body_projection;
endfig;
