beginfig(2);
  draw_main(n, t);
  draw_bow(rr - dd, t + tt, 180 - t - tt);
  draw_equator(rr - dd, t);
  draw_bow(rr - dd, -t - tt, -180 + t + tt);
  draw_sector(rr + dd, r - dd, 2th0 - t - 5, th0 + t + 5);
endfig;
