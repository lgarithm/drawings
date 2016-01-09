path ss_p;
ss_p := radius_p(th0, 0, rr - dd)
  -- arc_p(rr - dd, th0, 2th0 + t + ts)
  -- radius_p(2th0 + t + ts, rr - dd, r - dd)
  -- arc_p(r - dd, 2th0 + t + ts, 2th0 + t + 20)
  -- radius_p(2th0 + t + 20, r - dd, r - 2dd)
  -- arc_p(r - 2dd, 2th0 + t + 20, 2th0 + t + 40)
  -- radius_p(2th0 + t + 40, r - dd, r - 2dd)
  -- arc_p(r - dd, 2th0 + t + 40, 3th0 - t - ts)
  -- radius_p(3th0 - t - ts, r - dd, rr - dd)
  -- arc_p(rr - dd, 3th0 - t - ts, 3th0 + t - ts)
  -- radius_p(3th0 + t - ts, rr - dd, 0)
  -- cycle;

def draw_face_i = 
  draw_sector(rr + dd, r - dd, th0 - t, th0 - t - 36);
  draw_sector(rr + dd, rr + 2dd, th0 - t - 36 - 5, th0 - t - 36 - 15);
  draw_sector(rr + 3dd , rr + 4dd, th0 - t - 36 - 5, th0 - t - 36 - 15);

  draw_sector(rr + dd, r - dd, -th0 + t + ts, -t - ts);
  draw_sector(r - 2dd, r - dd, -th0 + t + 5, -th0 + t + 30);
  draw_sector(r - 2dd, r - dd, -t - 4ts, -t - 3ts);
  draw_sector(r - 2dd, r - dd, -t - 2ts, -t - ts);

  draw ss_p;

  draw_sector(rr, rr + dd, 3th0 - t - 15, 3th0 - t - 30);
enddef;

def draw_filled_face_i = 
  draw_filled_sector(rr + dd, r - dd, th0 - t, th0 - t - 36);
  draw_filled_sector(rr + dd, rr + 2dd, th0 - t - 36 - 5, th0 - t - 36 - 15);
  draw_filled_sector(rr + 3dd , rr + 4dd, th0 - t - 36 - 5, th0 - t - 36 - 15);

  draw_filled_sector(rr + dd, r - dd, -th0 + t + ts, -t - ts);
  draw_sector(r - 2dd, r - dd, -th0 + t + ts, -th0 + t + ts + 5ts);
  draw_sector(r - 2dd, r - dd, -t - 4ts, -t - 3ts);
  draw_sector(r - 2dd, r - dd, -t - 2ts, -t - ts);

  fill ss_p withcolor .8white;
  draw ss_p;

  draw_filled_sector(rr, rr + dd, 3th0 - t - 15, 3th0 - t - 30);
enddef;
