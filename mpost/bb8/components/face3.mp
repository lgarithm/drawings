path bs_p;
bs_p := arc_p(rr - dd, t + tt, Th + t + tt)
  -- radius_p(Th + t + tt, rr - dd, r - 2dd)
  -- arc_p(r - 2dd, Th + t + tt, 1.5 Th - tt)
  -- (r - 2dd) * dir(1.5 Th - tt)
  -- (r - 2dd) * dir(1.5 Th - tt)
  .. (r - 4dd) * dir(1.5 Th)
  .. (r - 2dd) * dir(1.5 Th + tt)
  -- (r - 2dd) * dir(1.5 Th + tt)
  -- arc_p(r - 2dd, 1.5Th + tt, 2Th - t - tt)
  -- radius_p(2Th - t - tt, r - 2dd, rr - dd)
  -- cycle;

def draw_face_iii = 
  draw bs_p rotated th0;
  draw fullcircle scaled 2dd shifted ((r - 2dd) * dir(1.5 Th)) rotated th0;
  draw equator_p(rr - dd, t) rotated th0;
  draw bow_p(rr - dd, -t - tt, -180 + t + tt) rotated th0;
  draw sector_p(rr + dd, r - dd, -Th + t + 5, -t - 5) rotated th0;
enddef;

def draw_filled_face_iii = 
  draw_filled_p(bs_p rotated th0, C_minor);
  draw fullcircle scaled 2dd shifted ((r - 2dd) * dir(1.5 Th)) rotated th0;
  draw_filled_p(equator_p(rr - dd, t) rotated th0, C_minor);
  draw_filled_p(bow_p(rr - dd, -t - tt, -180 + t + tt) rotated th0, C_minor);
  draw_filled_p(sector_p(rr + dd, r - dd, -Th + t + 5, -t - 5) rotated th0, C_minor);
enddef;
