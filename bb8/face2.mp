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
