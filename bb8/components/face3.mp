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
  draw bs_p;
  draw fullcircle scaled 2dd shifted ((r - 2dd) * dir(1.5 Th));

  draw_equator(rr - dd, t);
  draw_bow(rr - dd, -t - tt, -180 + t + tt);

  draw_sector(rr + dd, r - dd, -Th + t + 5, -t - 5);
enddef;

def draw_filled_face_iii = 
  fill bs_p withcolor C_minor;
  draw bs_p;
  draw fullcircle scaled 2dd shifted ((r - 2dd) * dir(1.5 Th));
  draw_filled_equator(rr - dd, t);
  draw_filled_bow(rr - dd, -t - tt, -180 + t + tt);
  draw_filled_sector(rr + dd, r - dd, -Th + t + 5, -t - 5);
enddef;