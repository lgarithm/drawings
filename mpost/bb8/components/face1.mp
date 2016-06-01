path ss_p;
ss_p := radius_p(Th, 0, rr - dd)
  -- arc_p(rr - dd, Th, 2Th + t + ts)
  -- radius_p(2Th + t + ts, rr - dd, r - dd)
  -- arc_p(r - dd, 2Th + t + ts, 2Th + t + 20)
  -- radius_p(2Th + t + 20, r - dd, r - 2dd)
  -- arc_p(r - 2dd, 2Th + t + 20, 2Th + t + 40)
  -- radius_p(2Th + t + 40, r - dd, r - 2dd)
  -- arc_p(r - dd, 2Th + t + 40, 3Th - t - ts)
  -- radius_p(3Th - t - ts, r - dd, rr - dd)
  -- arc_p(rr - dd, 3Th - t - ts, 3Th + t - ts)
  -- radius_p(3Th + t - ts, rr - dd, 0)
  -- cycle;

def draw_face_i =
  draw sector_p(rr + dd, r - dd, Th - t, Th - t - 36) rotated th0;
  draw sector_p(rr + dd, rr + 2dd, Th - t - 36 - 5, Th - t - 36 - 15) rotated th0;
  draw sector_p(rr + 3dd , rr + 4dd, Th - t - 36 - 5, Th - t - 36 - 15) rotated th0;

  draw sector_p(rr + dd, r - dd, -Th + t + ts, -t - ts) rotated th0;
  draw sector_p(r - 2dd, r - dd, -Th + t + 5, -Th + t + 30) rotated th0;
  draw sector_p(r - 2dd, r - dd, -t - 4ts, -t - 3ts) rotated th0;
  draw sector_p(r - 2dd, r - dd, -t - 2ts, -t - ts) rotated th0;

  draw ss_p rotated th0;
  draw sector_p(rr, rr + dd, 3Th - t - 15, 3Th - t - 30) rotated th0;
enddef;

def draw_filled_face_i =
  draw_filled_p(sector_p(rr + dd, r - dd, Th - t, Th - t - 36) rotated th0, C_minor);
  draw_filled_p(sector_p(rr + dd, rr + 2dd, Th - t - 36 - 5, Th - t - 36 - 15) rotated th0, C_minor);
  draw_filled_p(sector_p(rr + 3dd , rr + 4dd, Th - t - 36 - 5, Th - t - 36 - 15) rotated th0, C_minor);

  draw_filled_p(sector_p(rr + dd, r - dd, -Th + t + ts, -t - ts) rotated th0, C_minor);
  draw sector_p(r - 2dd, r - dd, -Th + t + ts, -Th + t + ts + 5ts) rotated th0;
  draw sector_p(r - 2dd, r - dd, -t - 4ts, -t - 3ts) rotated th0;
  draw sector_p(r - 2dd, r - dd, -t - 2ts, -t - ts) rotated th0;

  draw_filled_p(ss_p rotated th0, C_minor);
  draw sector_p(rr, rr + dd, 3Th - t - 15, 3Th - t - 30) rotated th0;
enddef;
