beginfig(7);
  draw_filled_main(n, t, rr, r, R);

  draw_arc(rr - dd, t + 10, th0 + t + 15);
  draw_radius(th0 + t + 15, rr - dd, r - 2dd);
  draw_arc(r - 2dd, th0 + t + 15, th0 + t + 30);
  draw (r - 2dd) * direction(th0 + t + 30) 
    .. (r - 4dd) * direction(.5 * (3th0 + 5)) 
    .. (r - 2dd) * direction(2th0 - t - 25);
  draw fullcircle scaled 2dd shifted ((r - 2dd) * direction(.5 * (3th0 + 5)));
  draw_arc(r - 2dd, 2th0 - t - 10, 2th0 - t - 25);
  draw_radius(2th0 - t - 10, rr - dd, r - 2dd);
  draw (rr - dd) * direction(t + 10) -- (rr - dd) * direction(180 - t - 10);

  draw_filled_equator(rr - dd, t);
  draw_filled_bow(rr - dd, -t - 10, -180 + t + 10);

  draw_filled_sector(rr + dd, r - dd, -th0 + t + 5, -t - 5);
endfig;
