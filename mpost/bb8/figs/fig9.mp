beginfig(9);
  % metrics
  draw (-RR, -RR) -- (-RR, RR + 2u) dashed evenly;
  draw (RR, -RR) -- (RR, RR + 2u) dashed evenly;
  drawarrow (-.5u, RR + u) -- (-RR, RR + u) dashed evenly;
  drawarrow (+.5u, RR + u) -- (+RR, RR + u) dashed evenly;
  label.top("40cm", (0, RR + u - 0.2u));

  draw (-RR, -R) -- (RR + 2u, -R) dashed evenly;
  draw (-RR, +R) -- (RR + 2u, +R) dashed evenly;
  drawarrow (RR + u, .5u) -- (RR + u, R) dashed evenly;
  drawarrow (RR + u, -.5u) -- (RR + u, -R) dashed evenly;
  label.top("20cm", (0, -.2u)) rotated -90 shifted (RR + u, 0);

  draw origin -- RR * dir(Rth) dashed evenly;
  draw origin -- RR * dir(-Rth) dashed evenly;
  draw arc_p(.5u, -Rth, Rth) dashed evenly;
  draw arc_p(.7u, -Rth, Rth) dashed evenly;
  label.rt(btex $30^\circ$ etex, (.7u, 0));

  draw_filled_main(n, t, rr, r, R);
  draw_filled_face_i;
  draw_body_projection;
endfig;
