def table_sum(m,n)
  t = 0
  m.times do |i|
    n.times do |j|
      t += ((i+1)**2 + (j+1)**2 + 2*(i+1)*(j+1) - 3*(i+1) - (j+1) + 2)/2
    end
  end
  return t
end
