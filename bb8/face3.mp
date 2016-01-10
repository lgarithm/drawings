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

def draw_face_iii = 
  draw bs_p;
  draw fullcircle scaled 2dd shifted ((r - 2dd) * direction(1.5 th0));

  draw_equator(rr - dd, t);
  draw_bow(rr - dd, -t - tt, -180 + t + tt);

  draw_sector(rr + dd, r - dd, -th0 + t + 5, -t - 5);
enddef;

def draw_filled_face_iii = 
  fill bs_p withcolor C_minor;
  draw bs_p;
  draw fullcircle scaled 2dd shifted ((r - 2dd) * direction(1.5 th0));
  draw_filled_equator(rr - dd, t);
  draw_filled_bow(rr - dd, -t - tt, -180 + t + tt);
  draw_filled_sector(rr + dd, r - dd, -th0 + t + 5, -t - 5);
enddef;