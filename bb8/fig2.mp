beginfig(2);
  draw_main(n, t);
  draw_bow(rr - dd, t + 10, 180 - t - 10);
  draw_equator(rr - dd, t);
  draw_bow(rr - dd, -t - 10, -180 + t + 10);
  draw_sector(rr + dd, r - dd, 2th0 - t - 5, th0 + t + 5);
endfig;
