beginfig(2);
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
  draw_arc(rr - dd, t + 10, 180 - t - 10);
  draw_arc(rr - dd, -t - 10, -180 + t + 10);
  draw_arc(rr - dd, t, -t);
  draw_arc(rr - dd, 180 - t, 180 + t);

  draw (rr - dd) * direction(t + 10) -- (rr - dd) * direction(180 - t - 10);
  draw (rr - dd) * direction(t) -- (rr - dd) * direction(180 - t);
  draw (rr - dd) * direction(-t) -- (rr - dd) * direction(180 + t);
  draw (rr - dd) * direction(-t - 10) -- (rr - dd) * direction(-180 + t + 10);

  draw_sector(rr + dd, r - dd, 2th0 - t - 5, th0 + t + 5);
endfig;
