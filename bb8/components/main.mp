def draw_main(expr n, t) =
  draw fullcircle scaled (2 * R);
  Th := 360 / n;
  for i = 1 upto n:
    th := i * Th + th0;
    draw radius_p(th - t, rr, r);
    draw radius_p(th + t, rr, r);
    draw arc_p(rr, th - t, th + t);
    draw arc_p(r, th + t, th + Th - t);
    draw fullcircle scaled 2dd shifted ((rr + 2dd) * dir(th));
    draw fullcircle scaled 1.2dd shifted ((rr + 2dd) * dir(th));
  endfor;
enddef;

def draw_filled_main(expr n, t, rr, r, R) =
  Th := 360 / n;
  for i = 1 upto n:
    s := Th * i + th0;
    fill sector_p(r, R, s, s + Th) withcolor C_main;
    fill sector_p(rr, R, s - t, s + t) withcolor C_main;
  endfor;
  draw_main(n, t);
enddef;
