beginfig(1);
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

  dd := 0.2u;
  draw_sector(rr + dd, r - dd, th0 - t, th0 - t - 36);
  draw_sector(rr + dd, rr + 2dd, th0 - t - 36 - 5, th0 - t - 36 - 15);
  draw_sector(rr + 3dd , rr + 4dd, th0 - t - 36 - 5, th0 - t - 36 - 15);

  draw_sector(rr + dd, r - dd, -th0 + t + 5, -t - 5);
  draw_sector(r - 2dd, r - dd, -th0 + t + 5, -th0 + t + 30);
  draw_sector(r - 2dd, r - dd, -t - 20, -t - 15);
  draw_sector(r - 2dd, r - dd, -t - 10, -t - 5);

  % center
  draw_radius(th0, 0, rr - dd);
  draw_arc(rr - dd, th0, 2th0 + t + 5);
  draw_radius(2th0 + t + 5, rr - dd, r - dd);
  draw_arc(r - dd, 2th0 + t + 5, 2th0 + t + 20);
  draw_radius(2th0 + t + 20, r - dd, r - 2dd);
  draw_arc(r - 2dd, 2th0 + t + 20, 2th0 + t + 40);
  draw_radius(2th0 + t + 40, r - dd, r - 2dd);
  draw_arc(r - dd, 2th0 + t + 40, 3th0 - t - 5);
  draw_radius(3th0 - t - 5, r - dd, rr - dd);
  draw_arc(rr - dd, 3th0 - t - 5, 3th0 + t - 5);
  draw_radius(3th0 + t - 3, rr - dd, 0);

  draw_sector(rr, rr + dd, 3th0 - t - 15, 3th0 - t - 30);
endfig;
