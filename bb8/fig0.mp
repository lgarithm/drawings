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
  
  pair ep;
  ep := (hr * .5, hr * .3);
  fill fullcircle scaled 3dd shifted (hp + ep);
  draw fullcircle scaled 4dd shifted (hp + ep);
  draw fullcircle scaled 5dd shifted (hp + ep);

  draw_body_projection;
endfig;
