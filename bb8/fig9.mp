beginfig(9);
  def f(expr r, t, d) =
    draw r * direction(t - d) -- r * direction(t + d);
  enddef;
  draw_main(n, t);
  draw fullcircle scaled 2RR;
  for i := 0 upto 3:
    f(RR, i * 90, Rth);
    f(RR, i * 90, rth);
    draw_radius(i * 90 + 45, R, RR);
  endfor;
endfig;
