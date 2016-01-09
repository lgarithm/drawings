beginfig(7);
  draw_filled_main(n, t, rr, r, R);
  fill bsp withcolor .8white;
  draw bsp;
  draw fullcircle scaled 2dd shifted ((r - 2dd) * direction(1.5 th0));
  draw_filled_equator(rr - dd, t);
  draw_filled_bow(rr - dd, -t - tt, -180 + t + tt);
  draw_filled_sector(rr + dd, r - dd, -th0 + t + 5, -t - 5);
endfig;
