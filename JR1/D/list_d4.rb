def regression(n, xarr, yarr)
  x = 0.0
  y = 0.0
  xy = 0.0
  xx = 0.0
  yy = 0.0
  n.times do |i|
    x = x + xarr[i]
  end
  n.times do |i|
    y = y + yarr[i]
  end
  n.times do |i|
    xy = xy +  xarr[i] * yarr[i]
  end
  n.times do |i|
    xx = xx + xarr[i] * xarr[i]
  end
  n.times do |i|
    yy = yy + yarr[i] * yarr[i]
  end
  a = (n*xy - x*y) / (n*xx - x**2)
  b = (xx*y - xy*x) / (n*xx - x**2)
  printf("%.3f %.3f\n", a, b)
end
