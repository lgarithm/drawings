beginfig(3);
  u := 1cm;
  n := 4;
  pair o;
  o := origin;

  th0 := 360 / n;
  R := 4u;
  r := 3u;
  rr := 1.8u;
  draw fullcircle scaled (2 * R);

  t := 9;
  dd := .2u;
  draw_main(n, t);
  draw_arc(rr - dd, t + 10, th0 + t + 15);
  draw_radius(th0 + t + 15, rr - dd, r - 2dd);
  draw_arc(r - 2dd, th0 + t + 15, th0 + t + 30);
  draw (r - 2dd) * direction(th0 + t + 30) 
    .. (r - 4dd) * direction(.5 * (3th0 + 5)) 
    .. (r - 2dd) * direction(2th0 - t - 25);
  draw fullcircle scaled 2dd shifted ((r - 2dd) * direction(.5 * (3th0 + 5)));
  draw_arc(r - 2dd, 2th0 - t - 10, 2th0 - t - 25);
  draw_radius(2th0 - t - 10, rr - dd, r - 2dd);
  draw_arc(rr - dd, -t - 10, -180 + t + 10);
  draw_arc(rr - dd, t, -t);
  draw_arc(rr - dd, 180 - t, 180 + t);

  
  draw (rr - dd) * direction(t + 10) -- (rr - dd) * direction(180 - t - 10);
  draw (rr - dd) * direction(t) -- (rr - dd) * direction(180 - t);
  draw (rr - dd) * direction(-t) -- (rr - dd) * direction(180 + t);
  draw (rr - dd) * direction(-t - 10) -- (rr - dd) * direction(-180 + t + 10);

  draw_sector(rr + dd, r - dd, -th0 + t + 5, -t - 5);
endfig;
