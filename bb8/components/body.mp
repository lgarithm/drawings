def draw_body_projection = 
  draw fullcircle scaled 2RR;
  draw fullcircle scaled 2R;

  def f(expr r, t, d) = draw r * dir(t - d) -- r * dir(t + d); enddef;
  for i := 0 upto 3:
    f(RR, i * 90, Rth);
    f(RR, i * 90, rth);
    fill_subtropic(RR, i * 90, 90 - Rth, 90 - rth, C_main);
    draw_radius(i * 90, R, RR * cosd(Rth));
  endfor;
enddef;
