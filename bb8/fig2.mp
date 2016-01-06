beginfig(2);
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
