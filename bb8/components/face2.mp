def draw_face_ii = 
  draw_bow(rr - dd, t + tt, 180 - t - tt);
  draw_equator(rr - dd, t);
  draw_bow(rr - dd, -t - tt, -180 + t + tt);
  draw_sector(rr + dd, r - dd, 2Th - t - ts, Th + t + ts);
enddef;

def draw_filled_face_ii = 
  draw_filled_bow(rr - dd, t + tt, 180 - t - tt);
  draw_filled_equator(rr - dd, t);
  draw_filled_bow(rr - dd, -t - tt, -180 + t + tt);
  draw_filled_sector(rr + dd, r - dd, 2Th - t - ts, Th + t + ts);
enddef;
