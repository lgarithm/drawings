beginfig(4);
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
  draw_main(n, t);
endfig;
