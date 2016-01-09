beginfig(9);
  def f(expr r, t, d) =
    draw r * direction(t - d) -- r * direction(t + d);
  enddef;
  draw fullcircle scaled 2RR;
  for i := 0 upto 3:
    f(RR, i * 90, Rth);
    f(RR, i * 90, rth);
    fill_subtropic(RR, i * 90, 90 - Rth, 90 - rth, C_main);
    % draw_radius(i * 90 + 45, R, RR);
    draw_radius(i * 90, R, RR * cosd(Rth));
  endfor;

  draw_filled_main(n, t, rr, r, R);
  draw_filled_face_i;

  draw (-RR, -RR) -- (-RR, RR + 2u) dashed evenly;
  draw (RR, -RR) -- (RR, RR + 2u) dashed evenly;
  draw (-.5u, RR + u) -- (-RR, RR + u) dashed evenly;
  draw (+.5u, RR + u) -- (+RR, RR + u) dashed evenly;
  label.top("40cm", (0, RR + u - 0.2u));
  % drawarrow (0, 0) -- (100, 100);
endfig;
