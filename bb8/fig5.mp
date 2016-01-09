beginfig(5);
  draw_filled_main(n, t, rr, r, R);

  draw_filled_sector(rr + dd, r - dd, th0 - t, th0 - t - 36);
  draw_filled_sector(rr + dd, rr + 2dd, th0 - t - 36 - 5, th0 - t - 36 - 15);
  draw_filled_sector(rr + 3dd , rr + 4dd, th0 - t - 36 - 5, th0 - t - 36 - 15);

  draw_filled_sector(rr + dd, r - dd, -th0 + t + ts, -t - ts);
  draw_sector(r - 2dd, r - dd, -th0 + t + ts, -th0 + t + ts + 5ts);
  draw_sector(r - 2dd, r - dd, -t - 4ts, -t - 3ts);
  draw_sector(r - 2dd, r - dd, -t - 2ts, -t - ts);

  fill ss_p withcolor .8white;
  draw ss_p;

  draw_filled_sector(rr, rr + dd, 3th0 - t - 15, 3th0 - t - 30);
endfig;
