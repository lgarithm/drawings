beginfig(5);
  draw_filled_main(n, t, rr, r, R);

  draw_filled_sector(rr + dd, r - dd, th0 - t, th0 - t - 36);
  draw_filled_sector(rr + dd, rr + 2dd, th0 - t - 36 - 5, th0 - t - 36 - 15);
  draw_filled_sector(rr + 3dd , rr + 4dd, th0 - t - 36 - 5, th0 - t - 36 - 15);

  draw_filled_sector(rr + dd, r - dd, -th0 + t + 5, -t - 5);
  draw_sector(r - 2dd, r - dd, -th0 + t + 5, -th0 + t + 30);
  draw_sector(r - 2dd, r - dd, -t - 20, -t - 15);
  draw_sector(r - 2dd, r - dd, -t - 10, -t - 5);

  fill ss_p withcolor .8white;
  draw ss_p;

  draw_filled_sector(rr, rr + dd, 3th0 - t - 15, 3th0 - t - 30);
endfig;
