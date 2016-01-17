def draw_main(expr n, t) =
  draw fullcircle scaled (2 * R);
  th0 := 360 / n;
  for i = 1 upto n:
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
  for i = 1 upto n:
    s := th0 * i;
    fill_sector(r, R, s, s + th0, C_main);
    fill_sector(rr, R, s - t, s + t, C_main);
  endfor;
  draw_main(n, t);
enddef;
