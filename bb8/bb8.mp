def draw_main(expr n, t) =
  draw fullcircle scaled (2 * R);
  th0 := 360 / n;
  for i = 0 upto n:
    th := i * th0;
    draw_radius(th - t, rr, r);
    draw_radius(th + t, rr, r);
    draw_arc(rr, th - t, th + t);
    draw_arc(r, th + t, th + th0 - t);
    draw fullcircle scaled 2dd shifted ((rr + 2dd) * direction(th));
    draw fullcircle scaled 1.2dd shifted ((rr + 2dd) * direction(th));
  endfor;
enddef;

def draw_filled_main(expr n, t, rr, r, R) =
  th0 := 360 / n;
  for i = 0 upto n:
    s := th0 * i;
    fill_sector(r, R, s, s + th0, C_main);
    fill_sector(rr, R, s - t, s + t, C_main);
  endfor;
  draw_main(n, t);
enddef;

\input face1

path bs_p;
bs_p := arc_p(rr - dd, t + tt, th0 + t + tt)
  -- radius_p(th0 + t + tt, rr - dd, r - 2dd)
  -- arc_p(r - 2dd, th0 + t + tt, 1.5 th0 - tt)
  -- (r - 2dd) * direction(1.5 th0 - tt)
  -- (r - 2dd) * direction(1.5 th0 - tt)
  .. (r - 4dd) * direction(1.5 th0)
  .. (r - 2dd) * direction(1.5 th0 + tt)
  -- (r - 2dd) * direction(1.5 th0 + tt)
  -- arc_p(r - 2dd, 1.5th0 + tt, 2th0 - t - tt)
  -- radius_p(2th0 - t - tt, r - 2dd, rr - dd)
  -- cycle;
