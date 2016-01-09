beginfig(3);
  draw_main(n, t);

  draw bs_p;
  draw fullcircle scaled 2dd shifted ((r - 2dd) * direction(1.5 th0));

  draw_equator(rr - dd, t);
  draw_bow(rr - dd, -t - tt, -180 + t + tt);

  draw_sector(rr + dd, r - dd, -th0 + t + 5, -t - 5);
endfig;
