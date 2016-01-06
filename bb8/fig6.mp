beginfig(6);
  draw_filled_main(n, t, rr, r, R);
  draw_filled_bow(rr - dd, t + 10, 180 - t - 10);
  draw_filled_equator(rr - dd, t);
  draw_filled_bow(rr - dd, -t - 10, -180 + t + 10);
  draw_filled_sector(rr + dd, r - dd, 2th0 - t - 5, th0 + t + 5);
endfig;
