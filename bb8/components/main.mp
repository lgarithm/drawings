def draw_main(expr n, t) =
  draw fullcircle scaled (2 * R);
  Th := 360 / n;
  for i = 1 upto n:
    th := i * Th + th0;
    draw_radius(th - t, rr, r);
    draw_radius(th + t, rr, r);
    draw_arc(rr, th - t, th + t);
    draw_arc(r, th + t, th + Th - t);
    draw fullcircle scaled 2dd shifted ((rr + 2dd) * dir(th));
    draw fullcircle scaled 1.2dd shifted ((rr + 2dd) * dir(th));
  endfor;
enddef;

def draw_filled_main(expr n, t, rr, r, R) =
  Th := 360 / n;
  for i = 1 upto n:
    s := Th * i + th0;
    fill_sector(r, R, s, s + Th, C_main);
    fill_sector(rr, R, s - t, s + t, C_main);
  endfor;
  draw_main(n, t);
enddef;
