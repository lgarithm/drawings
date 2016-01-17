def draw_face_ii = 
  draw bow_p(rr - dd, t + tt, 180 - t - tt) rotated th0;
  draw equator_p(rr - dd, t) rotated th0;
  draw bow_p(rr - dd, -t - tt, -180 + t + tt) rotated th0;
  draw sector_p(rr + dd, r - dd, 2Th - t - ts, Th + t + ts) rotated th0;
enddef;

def draw_filled_face_ii = 
  draw_filled_p(bow_p(rr - dd, t + tt, 180 - t - tt) rotated th0, C_minor);
  draw_filled_p(equator_p(rr - dd, t) rotated th0, C_minor);
  draw_filled_p(bow_p(rr - dd, -t - tt, -180 + t + tt) rotated th0, C_minor);
  draw_filled_p(sector_p(rr + dd, r - dd, 2Th - t - ts, Th + t + ts) rotated th0, C_minor);
enddef;
